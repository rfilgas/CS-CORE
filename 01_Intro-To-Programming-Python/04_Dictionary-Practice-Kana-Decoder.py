
# Introduction to Automatic Translation

# In this assignment your job is to translate words from the english alphabet (called romanji)
# into the japanese alphabet (called katakana).

# If you don't know japanese, that's OK.
# The rules of translating an english word into japanese are straightforward.
# Every word is made up of characters, and each katakana character is either
# a vowel, a consonant vowel pair, or the character n.
# the translation is given by the following chart.

#     a  i  u  e  o  n
# --+-------------------
#   | ア イ ウ エ オ ン
# k | カ キ ク ケ コ
# g | ガ ギ グ ゲ ゴ
# s | サ シ ス セ ソ
# z | ザ ジ ズ ゼ ゾ
# t | タ チ ツ テ ト
# d | ダ ヂ ヅ デ ド
# h | ハ ヒ フ ヘ ホ
# b | バ ビ ブ ベ ボ
# p | パ ピ プ ペ ポ
# n | ナ ニ ヌ ネ ノ
# m | マ ミ ム メ モ
# r | ラ リ ル レ ロ
# y | ヤ    ユ    ヨ
# w | ワ          ヲ

# For examle the japanese word for "programming" is "puroguramingu"
# so, breaking this appart we have "puroguramingu" "pu","ro","gu","ra","mi","n","gu"
# "pu" プ
# "ro" ロ
# "gu" グ
# "ra" ラ
# "mi" ミ
# "n"  ン
# "gu" グ
# or "プログラミング"

# fortunately you don't need to know this chart.
# I have given you a function that will translate any valid string into a katakana character.

def toKana(rom):
    vowels =       dict (a="ア", i="イ", u="ウ", e="エ", o="オ", n="ン")
    rows = dict (k=dict (a="カ", i="キ", u="ク", e="ケ", o="コ"),
                 g=dict (a="ガ", i="ギ", u="グ", e="ゲ", o="ゴ"),
                 s=dict (a="サ", i="シ", u="ス", e="セ", o="ソ"),
                 z=dict (a="ザ", i="ジ", u="ズ", e="ゼ", o="ゾ"),
                 t=dict (a="タ", i="チ", u="ツ", e="テ", o="ト"),
                 d=dict (a="ダ", i="ヂ", u="ヅ", e="デ", o="ド"),
                 h=dict (a="ハ", i="ヒ", u="フ", e="ヘ", o="ホ"),
                 b=dict (a="バ", i="ビ", u="ブ", e="ベ", o="ボ"),
                 p=dict (a="パ", i="ピ", u="プ", e="ペ", o="ポ"),
                 n=dict (a="ナ", i="ニ", u="ヌ", e="ネ", o="ノ"),
                 m=dict (a="マ", i="ミ", u="ム", e="メ", o="モ"),
                 r=dict (a="ラ", i="リ", u="ル", e="レ", o="ロ"),
                 y=dict (a="ヤ", i="・", u="ユ", e="・", o="ヨ"),
                 w=dict (a="ワ", i="・", u="・", e="・", o="ヲ"))
    if len(rom) == 1 and rom in vowels:
        return vowels[rom]
    if len(rom) == 2 and rom[0] in rows and rom[1] in rows[rom[0]] \
       and rows[rom[0]][rom[1]] != "・":
        return rows[rom[0]][rom[1]]

# to use this function you simply call toKana(<string>)
# example: toKana("pu") returns プ.
# example: toKana("a") returns ア.

# if you call toKana with an invalid string then it will not return a valid string
# example: toKana("ex") + "string" crashes

# your job is to translate a string from romanji into katakana.

# Your translation function should obey the following rules.
# All spaces should be left alone.
# If the romanji isn't valid (i.e. it can't be translated) then put a "・" instead of the character.
# If there are two possible translations you should choose the one with the fewest characters.

# for example the string "piano" should be translated "pi","a","no" ("ピアノ") not "pi","a","n","o" ("ピアンオ")
# also, the string "hams" couldn't be translated, so it should give the partial translation "ha","・","・" ("ハ・・")

# tips:
# you have 4 different possibilities here.
# 1. the character is a space
# 2. the character is a vowel or the letter n
# 3. the character is a consonant vowel pair
# 4. it is not a valid character

# we are accumulating a new string, but we don't have to look one character at a time.

def translate(romanji):

    i = 0
    memory = ""

    while i < len(romanji):
#Spaces
        if romanji[i] == " ":
            memory += " "
            i += 1
#Consonants + "shi"
        elif i + 1 < len(romanji) and \
        romanji[i] in "kgsztdhbpnmrwy" and romanji[i+1] in "aeiou":
            memory += toKana(romanji[i:i+2])
            i += 2
        elif i + 2 < len(romanji) and \
            romanji[i:i+3] == "shi":
            memory += toKana("si")
            i += 3
#Vowels
        elif romanji[i] in "aeioun":
            memory += toKana(romanji[i])
            i += 1
        else:
            memory += "・"
            i += 1
    romanji = memory
    return romanji
    

def translateTest():
    """
    Test all of the following words

    English    | Romanji | katakana
    -----------+---------+----------
    Lettuce    | retasu  | レタス
    Tent       | tento   | テント
    PC         | pankon  | パンコン
    Ping Pong  | pinpon  | ピンポン
    Drama      | dorama  | ドラマ
    Button     | butan   | ブタン
    Piano      | piano   | ピアノ
    Vitamins   | bitamin | ビタミン
    Plum       | puramu  | プラム
    Hong Kong  | honkon  | ホンコン
    London     | rondon  | ロンドン
    Software   | sohuto  | ソフト
    Spain      | supain  | スパイン
    Wife       | waihu   | ワイフ
    Microphone | maiku   | マイク
    India      | indo    | インド
    Thailand   | tai     | タイ
    Kiosk      | kiosuke | キオスケ
    Robot      | roboto  | ロボト
    Glass      | garasu  | ガラス
    Polygon    | porigon | ポリゴン
    taxi       | takushi | タクシ

    >>> translate("retasu")
    'レタス'
    >>> translate("tento")
    'テント'
    >>> translate("pankon")
    'パンコン'
    >>> translate("pinpon")
    'ピンポン'
    >>> translate("dorama")
    'ドラマ'
    >>> translate("butan")
    'ブタン'
    >>> translate("piano")
    'ピアノ'
    >>> translate("bitamin")
    'ビタミン'
    >>> translate("puramu")
    'プラム'
    >>> translate("honkon")
    'ホンコン'
    >>> translate("rondon")
    'ロンドン'
    >>> translate("sohuto")
    'ソフト'
    >>> translate("supain")
    'スパイン'
    >>> translate("waihu")
    'ワイフ'
    >>> translate("maiku")
    'マイク'
    >>> translate("indo")
    'インド'
    >>> translate("tai")
    'タイ'
    >>> translate("kiosuke")
    'キオスケ'
    >>> translate("roboto")
    'ロボト'
    >>> translate("garasu")
    'ガラス'
    >>> translate("porigon")
    'ポリゴン'
    """
    pass


if __name__ == "__main__":
    import doctest
    doctest.testmod()

