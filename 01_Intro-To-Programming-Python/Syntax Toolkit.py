"""
Toolkit:

defining a function ------------------------

def function(function input):
    conditions
        body
    return

defining a class:--------------------------

class runner(object):
    def left():
        code for go left
    def right (): code for go right

Test Code:
    runner.left() - turns left.

Operators:---------------------------------

#  - +
#  - -
#  - *
#  - /
#  - // --- integer division keeps the result and throws out the remainder
#  - % ---- percent (mod) symbol takes the remainder of a divisor
#  - ** --- exponential functions
#  - and
#  - or
#  - not
#  - ==
#  - !=
#  - <
#  - >
#  - <=
#  - >=

Booleans:----------------------------------

if
elif
else

and
or
in ----- "i" in  "igloo" returns True

True
False


Input types--------------------------------

tuple = ()
string = ""
variable = 0
list = []
matrix (list of lists): [[],[],[],[],[,]]

Loops-------------------------------------

def whileLoop():
    i = 0
    count = 0
    while i < n:
        if this is true, do that\
            count += 1
        i += 1
    return count

def forLoop(string):
    memory = ""
    for letter in string:
        do this
    return memory

recursion:--------------------------------

def recursion(input):
    if len(input) == 1:
        return input
    #this is the base case - what does the last chunk look like, or what's the finish?
    do something, or don't
    return recursion[0] + recursion[1:].

    - the important thing here is that the input gets smaller /
    or at least we're headed to our base case.
    
if syntax error:--------------------------
    check the previous line for () or:
    check that proper input type is used



Truth Tables:

d'morgans law: not (a or b) == not a and not b

# -------------------
# | a | b | a and b |
# |---+---+---------|
# | T | T |    T    |
# | T | F |    F    |
# | F | T |    F    |
# | F | F |    F    |
# -------------------

# -------------------
# | a | b | a  or b |
# |---+---+---------|
# | T | T |    T    |
# | T | F |    T    |
# | F | T |    T    |
# | F | F |    F    |
# -------------------

# -------------------
# | a | b | a ==  b |
# |---+---+---------|
# | T | T |    T    |
# | T | F |    F    |
# | F | T |    F    |
# | F | F |    T    |
# -------------------

# -------------------
# | a | b | a !=  b |
# |---+---+---------|
# | T | T |    F    |
# | T | F |    T    |
# | F | T |    T    |
# | F | F |    F    |
# -------------------

# -------------------
# | a | b | not a   |
# |---+---+---------|
# | T | T |    F    |
# | T | F |    F    |
# | F | T |    T    |
# | F | F |    T    |
# -------------------
