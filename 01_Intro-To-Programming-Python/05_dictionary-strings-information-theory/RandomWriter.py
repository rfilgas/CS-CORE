from typing import List, Tuple, Dict, TypeVar
import random as r

################################
# Random Writer: Ryan Filgas
# Due: 8/4/20
#
# In this assignment we're going to learn a little bit about 
# information theory by learning how to plagiarize!
# 
# Information theory is all about how we communicate and send information.
# It turns out that English isn't a very efficient language for communication.
# The redundancy of the English language is about 54%.
# This sounds like a bad thing, but it's really not.
# It's what allows different authors to have their own style.
# We can use this to study language phenomena, determine original authorship,
# or we could create the next Pride and Prejudice and Zombies.
#
# We're going to do that last one, because it sounds more fun.

# In this assignment I want you to take a string of text,
# and randomly generate a new string that "looks like" the old one.
# This sounds complicated so we'll take it one step at a time.
#
# Level 0:
# The first thing to notice is that some letters occurs more 
# frequently than others.
# For example 'e' and ' ' occurs a lot, but 'q' and 'x' really don't.
# So, we could start by generating a string with the with correct character frequency.
# We can do that by just randomly picking a character from the text.
#
# So, given the sentence
# "the quick brown fox jumped over the lazy dog"
# We might get the following strings out.
# ' ja iuyfcwpmethya yj'
# 'rgeoothe uddtfeeoont'
# 'om i mn  mwkow qah e'
# 'eobzeofnv io dn  ejo'
# 'eu mor uojhe qogiphn'
#
# These don't really look like English, but the character frequency is about right.

# Level 1:
# Ok, we can clearly do better.
# We don't just need to get roughly the right number of 'e's, 
# but we also need to put them in the right place.
# If the current letter is a 't', then the next letter is more likely to be an 'h', then a 'd'.
# This time we'll make a dictionary of following characters in the string.
# For every 'e' in the text, we want to find all of the characters that could follow 'e'.
#
# In the case of 
# "the quick brown fox jumped over the lazy dog"
# 'e' is followed by a ' ' in but times "the" appears.
# It's also followed by 'd' in "jumped", and 'r' in "over".
# So the following characters for 'e' are [' ', 'd', 'r', ' ']
#
# We can make a dictionary for the entire string.
# 't' => ['h', 'h']
# 'h' => ['e', 'e']
# 'e' => [' ', 'd', 'r', ' ']
# ' ' => ['q', 'b', 'f', 'j', 'o', 't', 'l', 'd']
# 'q' => ['u']
# 'u' => ['i', 'm']
# 'i' => ['c']
# 'c' => ['k']
# 'k' => [' ']
# 'b' => ['r']
# 'r' => ['o', ' ']
# 'o' => ['w', 'x', 'v', 'g']
# 'w' => ['n']
# 'n' => [' ']
# 'f' => ['o']
# 'x' => [' ']
# 'j' => ['u']
# 'm' => ['p']
# 'p' => ['e']
# 'd' => [' ', 'o']
# 'v' => ['e']
# 'l' => ['a']
# 'a' => ['z']
# 'z' => ['y']
# 'y' => [' ']
#
# For most characters, there's only one character that could follow
# but for ' ' and 'e', there are a few choices.
# This isn't too surprising.  'e' is a common character, and almost every word has a ' ' before it.
#
# Now we can generate a string.
# Start with a random character in the dictionary.
# Suppose we started with 'o'
# Then we'll look up 'o' in our dictionary, and pick a random character.
# We repeat this process until we've made a string that's the desired length.
# 
# When I used the dictionary to generate a string of 20 characters I got:
# "quick quick juick jui"
# 
# This is better "quick" is actually a word, but what about "juick"
# Well, 'j' is followed by 'u' in "jumped", and 'u' is followed by 'i' in "quick".
# So, this si better, but it's still not perfect.


# Level 2:
# This time we're not doing anything different,
# we're just making the keys in our dictionary 2 characters long.
# The idea is the same.
# If we have the characters "th" we expect to find an 'e' more often than a 'q'.
# I made a dictionary for our string
# "th" => ['e', 'e']
# "he" => [' ', ' ']
# "e " => ['q', 'l']
# " q" => ['u']
# "qu" => ['i']
# "ui" => ['c']
# "ic" => ['k']
# "ck" => [' ']
# "k " => ['b']
# " b" => ['r']
# "br" => ['o']
# "ro" => ['w']
# "ow" => ['n']
# "wn" => [' ']
# "n " => ['f']
# " f" => ['o']
# "fo" => ['x']
# "ox" => [' ']
# "x " => ['j']
# " j" => ['u']
# "ju" => ['m']
# "um" => ['p']
# "mp" => ['e']
# "pe" => ['d']
# "ed" => [' ']
# "d " => ['o']
# " o" => ['v']
# "ov" => ['e']
# "ve" => ['r']
# "er" => [' ']
# "r " => ['t']
# " t" => ['h']
# " l" => ['a']
# "la" => ['z']
# "az" => ['y']
# "zy" => [' ']
# "y " => ['d']
# " d" => ['o']
# "do" => ['g']
#
# Now this time the next letter is almost completely determined.
# The only choice we have is for the string "e ".
# This meanst that we'll almost always get out the same string.

# I got the sentence.
#'fox jumped over the qu'
# This isn't exactly part of the origonal text, but it's pretty close.
# We're also getting full words at this point, so that's encouraging.

# Level k
# Unfortunately in order to take this idea further we just need more text.
# I recomend downloading books from Project Gutenberg.
# some books you might want to try
# Pride and Prejiduice: https://www.gutenberg.org/files/42671/42671.txt
# Hound of the Baskervilles: https://www.gutenberg.org/files/2852/2852-0.txt
# Grimms' fairy talse: https://www.gutenberg.org/files/2591/2591-0.txt
# Dracula: http://www.gutenberg.org/cache/epub/345/pg345.txt

# When you make a dictionary out of an entire book, you'll notice that you don't always get full words with 2 characters.
# So, we're going to generalize this.
# Write a function makeDict that takes the text, and a positive integer k
# This should return the dictionary where the keys are words of length k
# The values in the dictionary should be every letter that follows that key in the text.

def makeDict(text : str, k : int) -> Dict[str,List[str]]:
    newtext = text
    #I could add readFiles into this if desired by replacing text and calling the \
    # readFiles function.
    newDict = {}
    i = 0
    while i < len(newtext)-k:
    # dictionary will never generate a word without a charactar following it
            if newtext[i:i+k] in newDict:
                newDict[(newtext[i:i+k])] += [newtext[i+k]]
            else:
                newDict[newtext[i]+(newtext[i+1:i+k])] = [newtext[i+k]]
            i += 1
    return newDict


# Finally we need to generate a random string.
# make a function randomWriter that takes 3 parameters.
# text is a string.  It's the text we'll use to make our dictionary
# k is the length of words in our dictionary
# outputLen is the length of the final output
# 
# Start by making a dictionary out of text with words of length k.
# let word be a randomly chosen word from the dictionary.
#
# Now let c be a randomly selected character following word.
# add c to the output
# Drop the first character from word, and add c to the end.
# Repeat this process until the output is long enough.
#
# If the dictionary doesn't have a character following the current word
# (because it was at the very end of text),
# then randomly pick a new word and keep going.


def randomWriter(text : str, k : int, outputLen : int) -> str:
    textDict = makeDict(text, k)
    #since randomWriter is supposed to take string as an input, I didn't \
    #have it read in the files as part of the function since a string doesn't \
    #allow for multiple texts to be read in like the example showed in class.
    word = r.choice(list(textDict))
    out = ""
    for x in range(int(outputLen)):
        c = r.choice(list(textDict[word]))
        out += c
        word = word[1:] + c
        if word not in(list(textDict)):
            word = r.choice(list(textDict))
    return out

# This function will read in a list of files in the same directory
# and return a string with the files' text.

def readFiles(files : List[str]) -> str:
    text = ""
    for fileName in files:
        f = open(fileName, 'r')
        text += f.read()
        f.close()
    return text

