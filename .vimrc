" Index: use the search functionality to skip around by typing
" 		:/insert_setting_name  in normal mode and hit 'n' to continue.
"
" 		NEXT: skip to the next section
" 		BOILERPLATE: some basic config provided by vim repo
" 		BASICS: skip to config supported by vim without any plugins
" 		IDE: skip to the section that mimics some ide features
" 		PLUGINS: skip to the plugin section


" Notes:
" - To use backups a directory needs to be made for ~/.vim/backup
" - The line shifting mapping should be toggled for mac vs unixr.
" - <Leader> is currently the space bar.
"   Intellij does not have visual mode - surround mappings will not work in
"   ideavim.


" DISCLAIMER:
" - These settings are NOT 100% in the spirit of vim. They enable occasional
"   cheating with the mouse and classic keyboard use not normally afforded by
"   vim. They also erase annoyances born from not being fully acclimated to vim,
"   but still needing to get work done in a production environment.
"  	
"  	User 1: uses an ide and occasionally ***cringe*** uses a mouse to make up
"  	for vim actions they don't yet have committed to muscle memory.
"
"  	User 2: uses vim almost exclusively and wants to steal some IDE tricks
"  	without a boatload of plugins like line/block shifting, bracket completion, and
"  	auto-commenting with <leader> + /.
"
"  	User 3: Some combination of the above. If you are fanatical about vim
"  	there may be something here to grab, but you should also be caught up
"  	on neovim and might be far past this.
" Added IDE motions to classic vim
" -----------------------------------------
" - line/block shifting up/down
" - comment lines/blocks with <leader> + /
" - Hitting enter after a first curly brace puts cursor in the code block
" - Indenting highlighted code with tab and shift tab is supported


" Custom Mappings
" --------------------------------------------
" - Screen splitting with control + movement keys
" - tn toggles relative vs absolute numbering
" - Adding two quotes or brackets etc. will place cursor in the center
" - Y yanks from cursor to end of line
" - jj exits normal mode like <esc>
" - exiting with contol z is turned off to prevent accidental exits when undoing
" - mouse selections are allowed in normal mode
" - backspacing to delete is allowed in normal mode
" - :DiffOrig is native to vim as a default usually, but worth mentioning nonetheless.
" - Lots of splitscreen mapping, investigate down below.


" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
" ======== NEXT | BOILERPLATE ==============================================
" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
"
" Start Defaults: From vim documentation.
" https://github.com/vim/vim/blob/master/runtime/defaults.vim


" Prefer vim over vi for settings
 if &compatible
  set nocompatible
endif

" When the +eval feature is missing, the set command above will be skipped.
" Use a trick to reset compatible only when the +eval feature is missing.
silent! while 0
  set nocompatible
silent! endwhile

" Show @@@ in the last line if it is truncated.
set display=truncate

" Show a few lines of context around the cursor.  Note that this makes the
" text scroll if you mouse-click near the start or end of the window.
set scrolloff=5

" In many terminal emulators the mouse works just fine.  By enabling it you
" can position the cursor, Visually select and scroll with the mouse.
" Only xterm can grab the mouse events when using the shift key, for other
" terminals use ":", select text and press Esc.
if has('mouse')
  if &term =~ 'xterm'
    set mouse=a
  else
    set mouse=nvi
  endif
endif

" Only do this part when Vim was compiled with the +eval feature.
if 1

  " Enable file type detection.
  " Use the default filetype settings, so that mail gets 'tw' set to 72,
  " 'cindent' is on in C files, etc.
  " Also load indent files, to automatically do language-dependent indenting.
  " Revert with ":filetype off".
  filetype plugin indent on

  " Put these in an autocmd group, so that you can revert them with:
  " ":autocmd! vimStartup"
  augroup vimStartup
    autocmd!

    " When editing a file, always jump to the last known cursor position.
    " Don't do it when the position is invalid, when inside an event handler
    " (happens when dropping a file on gvim), for a commit or rebase message
    " (likely a different one than last time), and when using xxd(1) to filter
    " and edit binary files (it transforms input files back and forth, causing
    " them to have dual nature, so to speak)
    autocmd BufReadPost *
      \ let line = line("'\"")
      \ | if line >= 1 && line <= line("$") && &filetype !~# 'commit'
      \      && index(['xxd', 'gitrebase'], &filetype) == -1
      \ |   execute "normal! g`\""
      \ | endif

  augroup END

  " Quite a few people accidentally type "q:" instead of ":q" and get confused
  " by the command line window.  Give a hint about how to get out.
  " If you don't like this you can put this in your vimrc:
  " ":autocmd! vimHints"
  augroup vimHints
    au!
    autocmd CmdwinEnter *
	  \ echohl Todo |
	  \ echo gettext('You discovered the command-line window! You can close it with ":q".') |
	  \ echohl None
  augroup END

endif


" Convenient command to see the difference between the current buffer and the
" file it was loaded from, thus the changes you made.
" Only define it when not defined already.
" Revert with: ":delcommand DiffOrig".
if !exists(":DiffOrig")
  command DiffOrig vert new | set bt=nofile | r ++edit # | 0d_ | diffthis
		  \ | wincmd p | diffthis
endif


" END Defaults:


" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
" ============== NEXT | BASICS =============================================
" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

" filetype off " required for some plugins


" color settings (if terminal/gui supports it)
if &t_Co > 2 || has("gui_running")
  syntax on
  color desert
  set hlsearch
  set incsearch
  let c_comment_strings=1
endif


" If Vim version is equal to or greater than 7.3 enable undofile.
" This allows you to undo changes to a file even after saving it.
if version >= 703
    set undodir=~/.vim/backup
    set undofile
    set undoreload=10000
endif


" ----style---------
set background=dark
hi CursorLine term=bold cterm=bold guibg=Grey40 ctermbg=none ctermfg=none


" ----general----
set lazyredraw          " no redraws in macros
set confirm             " get a dialog when :q, :w, or :wq fails
set nobackup            " no backup~ files.
set viminfo='20,\"500   " remember copy registers after quitting in the .viminfo file -- 20 jump links, regs up to 500 lines'
set hidden              " make a buffer hidden while editing another one.
set history=200			" keep 200 lines of command line history
set ttimeout			" time out for key codes
set ttimeoutlen=100		" wait up to 100ms after Esc for special key


" ----input----
set mouse=a				 " Allow selections in normal mode.
set esckeys				 " map missed escape sequences (enables keypad keys)


" ----notification----
set title				" add file name at top
set showmode			" show mode in status bar
set showcmd				" show commands in status bar
set visualbell			" no sound on error, just flashing
set laststatus=2		" use 2 lines for the status bar


" ----search----
set showmatch 			" show matching bracket


"  ----cases----
set ignorecase 			" case insensitive searching
set smartcase 			" become case insensitive for upper case searches
set backspace=indent,eol,start " allow backspacing over everything in insert mode
set nostartofline
set laststatus=2 		" always display status
set confirm


" ----indent----
set smartindent			" adjust auto indentation based on context
set autoindent			" auto indentation
set smarttab			" tab based on context
set tabstop=4			" a tab counts for x spaces
set shiftwidth=4		" spaces for autoindent


" paste mode toggle (needed when using autoindent/smartindent)
map <F10> :set paste<CR>
map <F11> :set nopaste<CR>
imap <F10> <C-O>:set paste<CR>
imap <F11> <nop>
set pastetoggle=<F11>


" ----motion---------
" Make cursor keys ignore wrapping
inoremap <silent> <Down> <C-R>=pumvisible() ? "\<lt>Down>" : "\<lt>C-O>gj"<CR>
inoremap <silent> <Up> <C-R>=pumvisible() ? "\<lt>Up>" : "\<lt>C-O>gk"<CR>

" go to the class definition
nmap gh gg<Action>(MethodDown)mxz<CR>5<C-y>`X


" ----lines----
set ruler 		" add ruler
set nowrap 		" don't wrap lines
set cursorline  " higlights the current line
set number 		" line numbers


" ----screen splits----
" split navigation
set splitbelow
set splitright
" navigate to the window below with cntrl + j
nnoremap <C-J> <C-W><C-J>
" navigate to the window above with ctrl + k
nnoremap <C-K> <C-W><C-K>
" move to the window on the right with ctrl + l
nnoremap <C-L> <C-W><C-L>
" move to the window on the left with ctrl h
nnoremap <C-H> <C-W><C-H>





" *********************
" *****Keymapping******
" *********************
"
" Map leader defines the initializer for custom keymappings
let mapleader = "\<space>"


" **** Disabled ****
" no closing vim with control z - commonly used for undo and can corrupt files.
nnoremap <c-z> <nop>

" when text is selected tabbing will indent the whole block by a single tab.
" This is useful in vim, but needed for intellij as it can tab backwards with
" a shift + tab, but not forwards.
"
" While this file allows mouse selection, you can hit gv to select the last
" text grabbed in visual mode in order to do the tabbing in normal mode.
xnoremap <Tab> >gv

" This is the same, but for de-denting to replicate the action in vscode and
" intellij for shift + tab.
xnoremap <S-Tab> <gv

" Typing tn toggles relative vs absolute numbers.
nnoremap tn :call ToggleNumber()<CR>
function! ToggleNumber()
  if &number || &relativenumber
    set invrelativenumber
  else
    set relativenumber
  endif
endfunction


" ********* General Additions *******
"
" Yank from cursor to the end of line.
nnoremap Y y$

" Type jj to exit insert mode quickly.
inoremap jj <Esc>

" this is for logging a variable with info.log in java. Activate by typing jl in insert
" mode for 'java log'. || is to know if the var is empty.
inoremap jl  info.log("var= \|{}\|", );

" Backspace/delete works now in normal mode like x
nnoremap <BS> x




" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
" =========== NEXT | IDE ===================================================
" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

" IMPORTANT: Use this for ideavim so that selecting text in insert mode
" doesn't kick the editor back into normal mode.
" set selectmode=mouse,key,cmd,ideaselection

" ******************************************
" ***** Intellij or VScode disclaimer ******
" **** Comment out these auto-completes ****
" ******************************************

" For a method block in c++ or java this will auto complete
" brackets in intellij after typing the left curly brace and 
" hitting return or enter in quick succession.
inoremap {<CR> {<CR>}<Esc>O

" **** AUTO INSERT ****
" Basic bracket completion. Often full auto-completion gets in
" the way here. This will just place your cursor in after typing
" rather than completing the other bracket etc.
inoremap "" ""<left>
inoremap '' ''<left>
inoremap () ()<left>
inoremap [] []<left>
inoremap {} {}<left>


" Enter visual mode and type $ + ______ then enter to surround"
" 1: ()
" 2: []
" 3: {}
" 4: |{}|
" $: ""
" q: ''
" e: ``
"
" These will  not work in ideavim as it has no visual mode.
" To use them in classic vim select text in visual mode and
" use the keys below.
vnoremap 11 <esc>`>a)<esc>`<i(<esc>
vnoremap 22 <esc>`>a]<esc>`<i[<esc>
vnoremap 33 <esc>`>a}<esc>`<i{<esc>
vnoremap $$ <esc>`>a"<esc>`<i"<esc>
vnoremap $q <esc>`>a'<esc>`<i'<esc>
noremap $e <esc>`>a`<esc>`<i`<esc>


" ----- custom file config -------
autocmd FileType yaml setlocal ts=2 sts=2 sw=2 expandtab indentkeys-=0# indentkeys-=<:> foldmethod=indent nofoldenable
autocmd FileType js setlocal ts=2 sts=2 sw=2 expandtab indentkeys-=0# indentkeys-=<:> foldmethod=indent nofoldenable
" --------------------------------

" *********  IDE DUPES (Not useful in intellij or vscode, strictly vim) ***********
"
" Toggle comments with <leader> + /
" CREDIT: https://stackoverflow.com/questions/1676632/whats-a-quick-way-to-comment-uncomment-lines-in-vim

let s:comment_map = { 
    \   "c": '\/\/',
    \   "cpp": '\/\/',
    \   "go": '\/\/',
    \   "java": '\/\/',
    \   "javascript": '\/\/',
    \   "lua": '--',
    \   "scala": '\/\/',
    \   "php": '\/\/',
    \   "python": '#',
    \   "ruby": '#',
    \   "rust": '\/\/',
    \   "sh": '#',
    \   "desktop": '#',
    \   "fstab": '#',
    \   "conf": '#',
    \   "profile": '#',
    \   "bashrc": '#',
    \   "bash_profile": '#',
    \   "mail": '>',
    \   "eml": '>',
    \   "bat": 'REM',
    \   "ahk": ';',
    \   "vim": '"',
    \   "tex": '%',
    \ }

function! ToggleComment()
    if has_key(s:comment_map, &filetype)
        let comment_leader = s:comment_map[&filetype]
        if getline('.') =~ "^\\s*" . comment_leader . " " 
            " Uncomment the line
            execute "silent s/^\\(\\s*\\)" . comment_leader . " /\\1/"
        else 
            if getline('.') =~ "^\\s*" . comment_leader
                " Uncomment the line
                execute "silent s/^\\(\\s*\\)" . comment_leader . "/\\1/"
            else
                " Comment the line
                execute "silent s/^\\(\\s*\\)/\\1" . comment_leader . " /"
            end
        end
    else
        echo "No comment leader found for filetype"
	end
endfunction
nnoremap <leader>/ :call ToggleComment()<cr>
vnoremap <leader>/ :call ToggleComment()<cr>


" **** Shift Lines or blocks in visual modeof code up or down on MAC ONLY ****
" **** Not needed in intellij or vscode - they have built in shortcuts. ******
"
" Swaps lines on mac only alt + k or j for up/down
" CREDIT: https://stackoverflow.com/questions/741814/move-entire-line-up-and-down-in-vim
nnoremap ∆ :m .+1<CR>==
nnoremap ˚ :m .-2<CR>==
inoremap ∆ <Esc>:m .+1<CR>==gi
inoremap ˚ <Esc>:m .-2<CR>==gi
vnoremap ∆ :m '>+1<CR>gv=gv
vnoremap ˚ :m '<-2<CR>gv=gv


" This works for normal linux systems using control instead of alt.
" nnoremap <C-K> :m .-2<CR>==
" inoremap <C-J> <Esc>:m .+1<CR>==gi
" inoremap <C-K> <Esc>:m .-2<CR>==gi
" vnoremap <C-J> :m '>+1<CR>gv=gv
" nnoremap <C-J> :m .+1<CR>==
" vnoremap <C-K> :m '<-2<CR>gv=gv


" Auto complete
" Enable auto completion menu after pressing TAB.
set wildmenu

" Make wildmenu behave like similar to Bash completion.
set wildmode=list:longest

" There are certain files that we would never want to edit with Vim.
" Wildmenu will ignore files with these extensions.
set wildignore=*.docx,*.jpg,*.png,*.gif,*.pdf,*.pyc,*.exe,*.flv,*.img,*.xlsx


" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
" =========== NEXT | PLUGINS ==============================================
" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

"" Install vim-plug if not found

" *****************************************************
" plugin configs for coc*******************************
" *****************************************************
"
" May need for Vim (not Neovim) since coc.nvim calculates byte offset by count
" utf-8 byte sequence
set encoding=utf-8
" Some servers have issues with backup files, see #649
set nobackup
set nowritebackup

" Having longer updatetime (default is 4000 ms = 4s) leads to noticeable
" delays and poor user experience
set updatetime=300

" Always show the signcolumn, otherwise it would shift the text each time
" diagnostics appear/become resolved
set signcolumn=yes

" Use tab for trigger completion with characters ahead and navigate
" NOTE: There's always complete item selected by default, you may want to enable
" no select by `"suggest.noselect": true` in your configuration file
" NOTE: Use command ':verbose imap <tab>' to make sure tab is not mapped by
" other plugin before putting this into your config
inoremap <silent><expr> <TAB>
      \ coc#pum#visible() ? coc#pum#next(1) :
      \ CheckBackspace() ? "\<Tab>" :
      \ coc#refresh()
inoremap <expr><S-TAB> coc#pum#visible() ? coc#pum#prev(1) : "\<C-h>"

" Make <CR> to accept selected completion item or notify coc.nvim to format
" <C-g>u breaks current undo, please make your own choice
inoremap <silent><expr> <CR> coc#pum#visible() ? coc#pum#confirm()

