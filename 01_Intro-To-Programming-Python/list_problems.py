from typing import List, TypeVar, Tuple


T = TypeVar("T")
Matrix = List[List[T]]


################################
# standard list functions
################################

def contains(l : List[T], x : T) -> bool:
    for part in l:
        if part == x:
            return True
    return False

def rec_contains(l,x):
    if l == []:
        return False
    if x == l[0]:
        return True
    return rec_contains(l[1:], x)
    

def minimum(l : List[T]) -> T:
    small = l[0]
    i = 1
    while i < len(l):
        if l[i] < small:
            small = l[i]
        i += 1
    return small

def min_recursive(l):
    newMin = l[0]
    if len(l) == 1:
        return newMin
    if l[0] > l[1]:
        newMin = l[1]
    return min_recursive([newMin] + l[2:])


def maximum(l : List[T]) -> T:
    large = l[0]
    i = 1
    while i < len(l):
        if l[i] > large:
            large = l[i]
        i += 1
    return large


def max_recursive(l):
    newMax = l[0]
    if len(l) == 1:
        return newMax
    if l[0] < l[1]:
        newMax = l[1]
    return max_recursive([newMax] + l[2:])


# l[index(l,x)] == x
def index(l : List[T], x : T) -> int:
    newList = []
    for i in l:
        if len(newList) == x-1:
            return [i]
        newList = newList + [i]
        if len(newList) == len(l):
            return("error: out of index range")
            
#not possible to do recursively.

def count(l : List[T], x : T) -> int:
    count = 0
    for thing in l:
        if x == thing:
            count += 1
    return count

def count_recursive(l : List[T], x : T) -> int:
        if len(l) == 0:
            return 0
        if l[0] == x:
            return 1 + count_recursive(l[1:], x)
        else:
            return count_recursive(l[1:], x)


def remove(l : List[T], x : T) -> List[T]:
    newList = []
    for thing in l:
        if x != thing:
            newList +=[thing]
    return newList

def remove_recursive(l : List[T], x : T) -> List[T]:
    if len(l) == 0:
        return []
    if l[0] != x:
        return [l[0]] + remove_recursive(l[1:],x)
    else:
        return remove_recursive(l[1:],x)
        

def insert(l : List[T], x : T) -> List[T]:
    out = []
    i = 0
    while i < len(l) and l[i] < x:
        i += 1
    if i < len(l):
        return l[:i] + [x] + l[i:]
    return l + [x]

def insert_recursive(l : List[T], x : T) -> List[T]:
    if l == []:
        return[x]
    if x <= l[0]:
        return [x] + l
    if x > l[0]:
        return [l[0]] + insert_rec(l[1:], x)

def reverse(l : List[T]) -> List[T]:
    i = -1
    listNew = []
    while len(listNew) < len(l):
        listNew += [l[i]]
        i -= 1
    return listNew

def reverse_rec(l : List[T]) -> List[T]:
    if l == []:
        return []
    return [l[-1]] + reverse_rec(l[:-1])

        
def copy(l : List[T]) -> List[T]:
    listNew = []
    for i in l:
        listNew = listNew + [i]
    return listNew

def copy_rec(l : List[T]) -> List[T]:
    if l == []:
        return []
    return [l[0]] + copy(l[1:])


def orderInsert(l : List[T], x : T) -> List[T]:
    pass

#uses insert
def isort(l):
    newList = []
    i = 0
    while len(l) != len(newList):
        newList = insert(newList, l[i])
        i += 1
    return newList


######################
# strings
######################

def lines(text : str) -> List[str]:
    newList = ["|"]
    for x in text:
        newList += [x] + ["|"]
    return newList

def lines_rec(text : str) -> List[str]:
    if len(text) == 1:
        return text[0] + ["|"]
    return ["|"] + [text[0]] + lines(text[1:])


def words(text : str) -> List[str]:
    wordList = []
    newWord = ""
    for x in text:
        if x != " ":
            newWord = newWord + x
        if x == " ":
            wordList  += [newWord]
            newWord = ""
    wordList += [newWord]
    return wordList

def words_rec():
    pass #don't know!

def unlines_rec(lines : List[str]) -> str:
    if lines == []:
        return ""
    if lines[0] != "|":
        return str(lines[0]) + unlines(lines[1:])
    if lines[0] == "|":
        return unlines(lines[1:])

def unwords(words : List[str]) -> str:
    if len(words) == 1:
        return str(words[0])
    return str(words[0]) + " " + unwords(words[1:])


def split(l : List[T], k : int) -> List[List[T]]:
    if len(l) < k and len(l) % k == 0:
        return []
    if len(l) == 1 and len(l) % k != 0:
        return[l]
    listEnd = split(l[k:], k)
    listStart = l[:k]
    return [listStart] + listEnd

def join(l : List[str], char : str) -> str:
    if len(l) == 1:
        return str(l[0])
    return l[0] + char + join(l[1:], char)

def removeChars(string : str, chars : str) -> str:
    if string == "":
        return ""
    if string[0] != chars:
        return str(string[0]) + removeChars(string[1:], chars)
    if string[0] == chars:
        return removeChars(string[1:], chars)

def frequency(l : List[str]) -> List[Tuple[str,int]]:
    listNew = []
    seen = []
    for i in l:
        if not i in seen:
            listNew += [(i, count(l, i))]
            seen += [i]
    return listNew


#uses words
#uses isort
def encyclopedia(text : str) -> List[str]:
    wordList = words(text)
    listNew = isort(wordList)
    return listNew


#uses word program
def parseCSV(text : str) -> List[List[str]]:
    temp = words(text)
    tempNew = []
    for i in temp:
        tempNew += [[i]]
    return tempNew


######################
# Statistics
######################

def mean(X : List[float]) -> float:
    return sum(X)/len(X)

def variance(X : List[float]) -> float:
    average = mean(X)
    diffList = []
    for number in X:
        diffList += [(average - number)**2]
    return mean(diffList)

#uses variance
def stddev(X : List[float]) -> float:
    return (variance(X))**.5


# https://en.wikipedia.org/wiki/Chi-squared_test
def chiSquare(X : List[float], E : List[float]) -> float:
    chiValues = []
    i = 0
    while i < len(X):
        chiValues += [((X[i] - E[i])**2)/E[i]]
        i += 1
    return sum(chiValues)

# https://en.wikipedia.org/wiki/Student%27s_t-test
def ttest(X : List[float], mu : float, var : float) -> float:
    answer = (mean(X) - mu)/var
    tValue = abs(answer)
    df = (len(X)*2)-2
    testDict = {1 : 12.71,
                 2 : 4.30,
                 3 : 3.18,
                 4 : 2.78,
                 5 : 2.57,
                 6 : 2.45,
                 7 : 2.36,
                 8 : 2.31,
                 9 : 2.26,
                 10 : 2.23,
                 11 : 2.20,
                 12 : 2.18,
                 13 : 2.16,
                 14 : 2.14,
                 15 : 2.13,
                 16 : 2.12,
                 17 : 2.11,
                 18 : 2.10,
                 19 : 2.09,
                 20 : 2.09,
                 21 : 2.08,
                 22 : 2.07,
                 23 : 2.07,
                 24 : 2.06,
                 25 : 2.06,
                 26 : 2.06,
                 27 : 2.05,
                 28 : 2.05,
                 29 : 2.04,
                 30 : 2.04}
    if df > 30:
        return ("T value is", tValue, "Sample size is higher than stored values, consult chart")
    if tValue > testDict[df]:
        significant = "statistically significant"
    else:
        significant = "not statistically significant"
    return (abs(answer), significant)


#uses mean
def ttest_value(X : List[float], mu : float, var : float) -> float:
    answer = (mean(X) - mu)/var
    tValue = abs(answer)
    return tValue

######################
# Linear algebra
######################


#reverse list
#trade lists
#trade first and last lists
#if number of lists is odd, just reverse middle list

def reverseList(l):
    i = -1
    listNew = []
    while len(listNew) < len(l):
        listNew += [l[i]]
        i -= 1
    return listNew

def tradeList(l,m):
    return [m,l]

#uses reverseList
#uses tradeList
def transpose(m):
    if len(m) == 2:
        return [reverseList(m[1]), reverseList(m[0])]
    if len(m) == 1:
        return [reverseList(m[0])]
    temp = tradeList(reverseList(m[0]), reverseList(m[-1]))
    return [temp[0]] + transpose(m[1:-1]) + [temp[-1]]


#addMatrix:
#add lists from matrix 1 to matrix 2
#add to new matrix
#add next row of lists
#add to new matrix
#return new matrix

def listAdd(m : List,l : List) -> List:
    listNew = []
    counter = 0
    
    if len(m) > len(l):
        temp = m
        m = l
        l = temp
    
    while counter < len(l)-1 and counter < len(m)-1:
        for i in m:
            listNew += [i+l[counter]]
            counter += 1
        return listNew + l[counter:]

#uses listAdd
def addMatrix(a : Matrix[T], b : Matrix[T]) -> Matrix[T]:
    matrixC = []
    i = 0
    for l in a:
        matrixC += [listAdd(l,b[i])]
        i += 1
    return matrixC

def listSubtract(m : List,l : List) -> List:
    listNew = []
    counter = 0
    
    if len(m) > len(l):
        temp = m
        m = l
        l = temp
    
    while counter < len(l)-1 and counter < len(m)-1:
        for i in m:
            listNew += [i-l[counter]]
            counter += 1
        return listNew + l[counter:]

#uses list subtract
def sub(a : Matrix[T], b : Matrix[T]) -> Matrix[T]:
    matrixC = []
    i = 0
    for l in a:
        matrixC += [listSubtract(l,b[i])]
        i += 1
    return matrixC

def listMultiply(m : List,l : List) -> List:
    listNew = []
    counter = 0
    
    if len(m) > len(l):
        temp = m
        m = l
        l = temp
    
    while counter < len(l)-1 and counter < len(m)-1:
        for i in m:
            listNew += [i*l[counter]]
            counter += 1
        return listNew + l[counter:]

#uses listMultiply
def mul(a : Matrix[T], b : Matrix[T]) -> Matrix[T]:
    matrixC = []
    i = 0
    for l in a:
        matrixC += [listMultiply(l,b[i])]
        i += 1
    return matrixC

def zeros(zero : T, rows : int, cols : int) -> Matrix[T]:
    matrixRows = [[[zero]]*rows]
    matrixNew = matrixRows*cols
    return matrixNew






#DRAFT
    """
    >>> mostCommon(["This", "is", "is", "a", "list"])
    'is'
    >>> mostCommon(["a", "b", "c", "b", "c", "d", "b"])
    'b'
    """
    newList = frequency(words)
    count_memory = newList[0][1]
    largest = newList[0][0]
    for word in newList:
        if newList[word][1] > count_memory:
            largest = newList[word][0]
    return largest
            

    """>>> frequency([1,2,3,4,1,1,1])
    [(1, 4), (2, 1), (3, 1), (4, 1)]
    """

def frequency(l : List[str]) -> List[Tuple[str,int]]:
    listNew = []
    seen = []
    for i in l:
        if not i in seen:
            listNew += [[i], [count(l, i)]]
            seen += [i]
    return listNew

def count(l : List[T], x : T) -> int:
    count = 0
    for thing in l:
        if x == thing:
            count += 1
    return count
