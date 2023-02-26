
#############################################################
#MATH:#######################################################
"""
1. AVERAGE
2. MIN
3. MAX
4. FACTORIAL
5. FIBONACCI
6. PRIME FACTORS
7. IS PRIME
8. OMEGA (COUNT DIVISORS)
9. INTEGER SQUARE ROOT
10. SUM OF ROOTS
11. PYTHAG
12. SOLVE POLYNOMIAL (FIND ZEROS)
13. ABSOLUTE VALUE
14. IS EVEN AND IS ODD

1.---------------------------------- AVERAGE
def average(x, y, z):
    average = (x + y + z)/3
    return average

2. ---------------------------------- MIN
def min3(x,y,z):
    if x < y and x < z:
        min3 = x
    elif y < x and y < z:
        min3 = y
    elif z < x and z < y:
        min3 = z
    return min3
3. ---------------------------------- MAX
def max3(x,y,z):
    if x > y and x > z:
        max3 = x
    elif y > x and y > z:
        max3 = y
    elif z > x and z > y:
        max3 = z
    return max3
4. ---------------------------------- FACTORIAL

def fac(n):
    i = 1
    product = 1
    while i <= n:
        product = product * i
        i += 1 
    return product

5. ------------------------------------ FIBONACCI
def fib(n):
    count = 1
    fib1 = 1
    fib2 = 1
    while count < n:
        fibnext = fib1 + fib2
        fib1 = fib2
        fib2 = fibnext
        count += 1
    return fib1

6. ----------------------------------PRIME FACTORS AS TUPLE
"""

def primeFactor(n):
    factors = ()
    while n != 1:
        guess = 2
        while n % guess != 0:
            guess += 1
        factors += (guess,)
        print(n)
        n = n // guess
    return factors
"""
7. --------------------------------- IS PRIME
def isPrime(n):
    i = 2
    prime = True
    while i < n:
        if n % i == 0:
            prime = False
        i += 1
    return prime

8. -------------------------------OMEGA (COUNT DIVISORS)
def omega(n):
    factors = 0
    guess = 1
    while guess < n:
        if n % guess == 0:
            factors += 1
        guess += 1
    return factors
    
9. ------------------------------ INTEGER SQUARE ROOT
def isqrt(n):
    i = 1
    while i*i <= n:
        i += 1
    return i-1
10.----------------------------- SUM OF ROOTS
def sumOfRoots(n):
    count = 1
    mem = 0
    while count <= n:
        mem += isqrt(count)
        count += 1
    return mem
11.--------------------------- PYTHAG
def pythag(a, b):
    import math as m
    return m.sqrt(a**2 + b**2)
12.--------------------------------SOLVE POLYNOMIAL(FIND ZEROS)
import math as m

def f(x):
    return x**5 + 15*x**4 + 85*x**3 + 225*x**2 + 274*x + 120
for x in range(-10, 10):
    if f(x) == 0:
        print(x)
        
13.--------------------------------ABSOLUTE VALUE
def abs(x):
    if x <= 0:
        return -x
    return x
14.---------------------------------IS EVEN AND IS ODD
def isEven(x):
    return (x % 2) == 0

def isOdd(x):
    return not evenOdd(x)


"""

###########################################################################################################
###########################################################################################################
#LANGUAGE / STRING MANIPULATION############################################################################
"""
1. IS PROGRESSIVE (VERB)
2. ADD COMMAS
3. REMOVE WHITE SPACE
4. COUNT VOWELS
5. COUNT CHARACTARS WITHOUT USING LEN
6. CAESAR CYPHER
7. WORD COUNT
8. LONGEST WORD
9. IS SUB IN SUBSTRING
10. IS IN
11. INDEX OF i
12. LONGEST SUBSTRING IN ALPHABETICAL ORDER

1.---------------------------------- IS PROGRESSIVE (VERB)
def isProgressive(verb):
    if verb[-3:] == "ing":
        return True
    return False

2.--------------------------------------- ADD COMMAS
def addCommas(sentence):
    count = 0
    memory = ""
    while count < len(sentence):
        if sentence[count] == " ":
            memory += ","
        else:
            memory += sentence[count]
        count += 1
    sentence = memory
    return sentence

3.----------------------------------------REMOVE WHITE SPACE
def removeWhitespace(sentence):
    i = 0
    mem = ''
    while i < len(sentence):
        if sentence[i] not in " \t \n ":
            mem += sentence[i]
            i += 1
        else:
            i += 1
    sentence = mem
    return sentence

4.--------------------------------------- COUNT VOWELS
def countVowels(word):
    count = 0
    numVowels = 0
    while count < len(word):
        if word[count] == "a" or word[count] == "e" or word[count] == "i" \
or word[count] == "o" or word[count] == "u":
            numVowels += 1
        count += 1
    return numVowels
    
5.------------------------------------ COUNT WITHOUT LEN
def charCount(string):
    length = 0
    copy = ""
    while copy != string:
        copy += string[length]
        length += 1
    return length
6.----------------------------------- CEASER CYPHER
def toNumber(letter):
    return ord(letter) - ord('a')

def toLetter(number):
    return chr(number + ord('a'))


def ceaser(message, key):
    enc = ""
    Text = ""
    i = 0
    while i < len(message):
        num = toNumber(message[i])
        num += key
        num = num % 25
        enc = toLetter(num)
        Text += enc
        i += 1
    return Text
    
7.------------------------------------- WORD COUNT
def wordCount(sentence):
    count = 0
    space = 1
    while count < len(sentence):
        if sentence[count] == " " and sentence[count-1] != " ":
            space += 1
        count += 1
    return space

8.------------------------------------ LONGEST WORD
def longest(sentence):
    count = 0
    word = ""
    longestWord = ""
    while count < len(sentence):
        if sentence[count] != " "
            word += sentence[count]
        if len(word) > len(longestWord):
            longestWord = word
        if sentence[count] == " ":
                word = ""
        count += 1
    return longestWord
9.-------------------------------------- IS SUB IN SUBSTRING
def substring(string,sub):
    i = 0
    while i <= len(string) - len(sub):
        temp = ""
        j = 0
        while j < len(sub):
            temp += string[i + j]
            j += 1
        if temp == sub:
            return True
        # using a string section we can get the characters from string[i] up to string[i + len(sub)]
        # This would be the same substring as temp
        #if string[i: i + len(sub)] == sub:
        #    return True
        i += 1
    return False


10.----------------------------------------- IS IN
def isIn(string, charactar):
    count = 0
    current = ''
    isFalse = False
    while count < len(string):

        current = string[count]
        if current == charactar:
            isFalse = True
            break
        count += 1
    return isFalse

    
11,----------------------------------------- INDEX OF i
def index(string, letter):
    length = len(string) 
    n = 0
    while n < length:
        if string[n] == char:
            return n
        n += 1
    return -1

12.--------------------- - LONGEST SUBSTRING IN ALPHABETICAL ORDER
def longestSub(s)
    large, temp, = s[0], ""
    for i in range(len(s)):
        if s[i] >= s[i-1]:
            temp += s[i]
        elif len(temp) > len(large):
            large = temp
        if s[i] < s[i-1]:
            temp = s[i]
    if len(temp) > len(large):
        longest = str(temp)
    else: longest = str(large)
    return longest
    
"""
###########################################################
###########################################################
#PROBLEMS & GAMES SOLVED:##################################
"""
1. GRADE -- ROCK PAPER SCISSORS
2. ROCK PAPER SCISSORS
3. Make Change - Screwups
4. Fizz Buzz
5. Secret Number
1.---------------------------------------------GRADE
def grade(score):
    if grade >= 90:
        grade = "A"
    elif grade >= 80:
        grade = "B"
    elif grade >= 70:
        grade = "C"
    elif grade >= 60:
        grade = "D"
    else:
        grade = "F"
    return grade
    
2.-------------------------------------------ROCK PAPER SCISSORS
def rps(player1, player2):
    if player1 == player2:
        winner = "tie"
    elif (player1, player2) == ("rock", "scissors"):
        winner = "player1"
    elif (player1, player2) == ("scissors", "paper"):
        winner = "player1"
    elif (player1, player2) == ("paper", "rock"):
        winner = "player1"
    else:
        winner = "player2"
    return winner

3.-----------------------------------------------MAKE CHANGE WITH SCREWUPS
def makeChange(amount):
    temp = amount
    pennies  = 0
    nickels  = 0
    dimes    = 0
    screwups = 0
    quarters = 0
    while amount != 0:
        if amount % 17 == 0:
            tempScrewups = amount // 17
            tempAmount = amount % 17
            answerA = tempScrewups
        amount = temp
        screwups
        quarters = amount // 25
        amount = amount % 25
        screwups = amount // 17
        amount = amount % 17
        dimes = amount // 10
        amount = amount % 10
        nickels = amount // 5
        amount = amount % 5
        pennies = amount
        amount = 0
        answerB = (pennies + nickels + dimes + screwups + quarters)
        if answerA < answerB:
            pennies = 0
            nickels = 0
            dimes = 0
            screwups = answerA
            quarters = 0
    return (pennies,nickels,dimes,screwups,quarters)
4.--------------------------------------------------------------- FIZZ BUZZ
def fizzbuzz(n):
    x = 1
    while x <= n:
        if x % 15 == 0:
            print("fizzbuzz")
        elif x % 5 == 0:
            print("buzz")
        elif x % 3 == 0:
            print("fizz")
        else:
            print(x)
        x += 1
5.---------------------------------------------------------SECRET NUMBER
def secretNumber():
    user=0
    guess=50
    high=100
    low=0
    correct = 0
    print("Please think of a number between 0 and 100!")

    while correct == 0:
        print("Is your secret number ", str(guess) + "?")
        user = input("Enter 'h' to indicate the guess is too high. Enter 'l' to indicate the guess is too low. Enter 'c' to indicate I guessed correctly. ")
        if user == str("h"):
            high = guess
            guess =int((high+low)/2)
        if user == str("l"):
            if guess == 99:
                guess = 100
            low = guess
            guess = int((high+guess)/2)
        if user == str("c"):
            break
        if user != str("h") and user != str("l") and user != str("c"):
            print("Sorry, I did not understand your input.")

    print("Game over. Your secret number was: " + str(guess))

"""
