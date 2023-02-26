from typing import TypeVar, List, Dict, Set

T = TypeVar("T")

#############################################

# Split a list into k element sublists
# example:
# split([1,2,3,4,5,6], 2) == [[1,2],[3,4],[5,6]]

def split(l : List[T], k : int) -> List[List[T]]:
    if len(l) < k and len(l) % k == 0:
        return []
    if len(l) == 1 and len(l) % k != 0:
        return[l]
    listEnd = split(l[k:], k)
    listStart = l[:k]
    return [listStart] + listEnd

def split_prof(l : List[T], k : int) -> List[List[T]]:
    out = []
    i = 0
    chunks = len(l) // k
    while i < len(l):
        out.append(l[i:i+k])
        i += k
    return out

#############################################

# In class we learned how to do an insertion sort
# write the insert function from this
# example:
# insert([1,2,4,5], 3) == [1,2,3,4,5]

def insert(l : List[T], x : T) -> List[T]:
    listStart = []
    listEnd =[]
    listMid = []
    for i in l:
        if i < x:
            listStart = listStart + [i]
    for u in l:
        if u > x:
            listEnd =  listEnd + [u]
    for v in l:
        if v == x:
            listMid = listMid + [v]
    listMid = listMid + [x]
    return listStart + listMid + listEnd

def insert_prof(l : List[T], x : T) -> List[T]:
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
    
def insert_cheat(l : List[T], x : T) -> List[T]:
    return merge(l, [x])

########################################### 

# return the dot product of two lists
# the dot product is defined by multiplying corresponding values in the lists, and adding all the elements together
# example:
# dot([1,2,3],[4,5,6]) == 1*4 + 2*5 + 3*6 == 4+10+18 == 32


def dot(v1 : List[int],v2 : List[int]) -> int:
    total = 0
    i = 0
    while i < len(v1):
        total += (v1[i] * v2[i])
        i += 1
    return total


# Now, do it recursively.

def dotRecursive(v1 : List[int],v2 : List[int]) -> int:
    if len(v1) < 1:
        return 0
    return (v1[0] * v2[0]) + dotRecursive(v1[1:], v2[1:])

########################################### 

# find the square root of a number (without using math.sqrt() or **(.5))
# you can assume all numbers have an integer square root

def sqrt(n : int) -> int:
    i = 1
    while i*i <= n:
        i += 1
    return i-1

###########################################

# we already did insert, why not finish insertion sort?

def isort(l):
    newList = []
    i = 0
    while len(l) != len(newList):
        newList = insert(newList, l[i])
        i += 1
    return newList

###########################################

# Given two sorted lists, merge them together into a single sorted list.
# Note: without using sort() (or sorted() or any other function to sort a list)

# example:
# merge([1,3,5], [2,4,6]) == [1,2,3,4,5,6]
# merge([1,3], [2,4,6,7]) == [1,2,3,4,6,7]
#/////////////////////////////////////////////////////////////////////////////////////////////////

def merge(l1 : List[T], l2 : List[T]) -> List[T]:
    out = []
    i1 = 0
    i2 = 0
    while i1 < len(l1) and i2 < len(l2):
        if l1[i1] < l2[i2]:
            out.append(l1[i1])
            i1 += 1
        else:
            out.append(l2[i2])
            i2 += 1
    #merge ([1,2,3], [4,5,6])
    if i1 < len(l1):
        return out + l1[i1:]
    else:
        return out + l2[i2:]
    
    return out

###########################################

# We can use our merge function to make a new sorting method.
# The idea is pretty simple.
# Image I have a deck of cards.  How do I sort them?
# I split the deck in half, sort the halves, and merge the two halves back to gether.
# This is the merge sort.

def msort(l : List[T]) -> List[T]:
    splitDeck = split(l, (len(l)//2))
    if len(l) % 2 != 0:
        splitDeck[1].append(l[-1])
    sortedDecks = isort(splitDeck[0]), isort(splitDeck[1])
    mergedDeck = merge(sortedDecks[0], sortedDecks[1])
    return mergedDeck

def msort_recursive(l : List[T]) -> List[T]:
    if len(l) <= 1:
        return l
    else:
        n = len(l)//2
        lower = l[:n]
        higher = l[n:]
        sortedLower = msort(lower)
        sortedHigher = msort(higher)
        return merge(sortedLower, sortedHigher)

###########################################

# create a dictionary that converts digits to words
# so "1" is "one"
#    "2" is "two" and so on

def wordDict() -> Dict[str,str]:
    return{0 : "zero",
           "1" : "one",
           "2" : "two",
           "3" : "three",
           "4" : "four",
           "5" : "five",
           "6" : "six",
           "7" : "seven",
           "8" : "eight",
           "9" : "nine"}

###########################################

# we can define n^2 with the following series
# n^2 == 1 + 3 + 5 + ... + 2*n-1

# write a recursive function to calculate n^2 using this series

def iter_square(n : int) -> int:
    out = 0
    k = 1
    while k < 2*n:
        out += k
        k += 2
    return out

def recursive_square(n : int) -> int:
    if n == 1:
        return 1
    else:
        return recursive_square(n-1) + 2*n - 1

###########################################

# I have a Student class
# Each student has a name, and a list of grades
class Student:
    def __init__(self, name, grades):
        self.name = name
        self.grades = grades

# Write a function that takes a list of students
# and returns the name of the student with the highest grade.

harry    = Student("harry",    [10, 8, 6, 8, 9, 8,10, 7, 8,10])
ron      = Student("ron",      [ 9, 7, 5, 7, 9, 7,10, 6, 6, 8])
neville  = Student("neville",  [ 6, 8, 7, 6, 7, 8, 9, 8, 8, 7])
hermione = Student("hermione", [10,10,10,10,10,10, 9,10,10,10])
fred     = Student("fred",     [ 2, 5, 3, 7, 4, 5, 4, 3,10, 2])
george   = Student("george",   [ 2, 5, 3, 7, 4, 5, 4, 3,10, 2])
students = [harry,ron,neville,hermione,fred,george]

def bestStudent(students : List[Student]) -> str:
    """
    >>> harry    = Student("harry",    [10, 8, 6, 8, 9, 8,10, 7, 8,10])
    >>> ron      = Student("ron",      [ 9, 7, 5, 7, 9, 7,10, 6, 6, 8])
    >>> neville  = Student("neville",  [ 6, 8, 7, 6, 7, 8, 9, 8, 8, 7])
    >>> hermione = Student("hermione", [10,10,10,10,10,10, 9,10,10,10])
    >>> fred     = Student("fred",     [ 2, 5, 3, 7, 4, 5, 4, 3,10, 2])
    >>> george   = Student("george",   [ 2, 5, 3, 7, 4, 5, 4, 3,10, 2])
    >>> bestStudent([harry,ron,neville,hermione,fred,george])
    'hermione'
    """
    pass

    best = students[0]
    for s in students:
        if grade(s) > grade(best):
            best = s
    return best.name

def largest(l : List[int]) -> int:
    large = l[0]
    i = 1
    while i < len(l):
        if l[i] > large:
            large = l[i]
        i += 1
    return large

def grade(s : Student) -> int:
    return sum(s.grades) / len(s.grades)


###########################################

# Find all of the students that got exactly the same grade.
# Hint: a dictionary might be helpful here.

def sameGrade(students : List[Student]) -> List[List[str]]:
    """
    >>> harry    = Student("harry",    [10, 8, 6, 8, 9, 8,10, 7, 8,10])
    >>> ron      = Student("ron",      [ 9, 7, 5, 7, 9, 7,10, 6, 6, 8])
    >>> neville  = Student("neville",  [ 6, 8, 7, 6, 7, 8, 9, 8, 8, 7])
    >>> hermione = Student("hermione", [10,10,10,10,10,10, 9,10,10,10])
    >>> fred     = Student("fred",     [ 2, 5, 3, 7, 4, 5, 4, 3,10, 2])
    >>> george   = Student("george",   [ 2, 5, 3, 7, 4, 5, 4, 3,10, 2])
    >>> sameGrade([harry,ron,neville,hermione,fred,george])
    [['ron', 'neville'], ['fred', 'george']]
    """
    
    gradeDict = {}
    for s in students:
        if grade(s) in gradeDict:
            gradeDict[grade(s)] += [s.name]
        else:
            gradeDict[grade(s)] = [s.name]

    out = []
    for g in gradeDict:
        if len(gradeDict[g]) > 1:
            out.append(gradeDict[g])
            return out
    
