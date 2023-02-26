#Ryan Filgas

from typing import List, Tuple

# Grading Midterms:
# 
# Oh no!
# It has taken a lot longer to grade the midterms then I expected.
# I'm almost done, but I need your help!

# If you'll recall, There were 10 questions on the midterm.
# However, I only took the top 8.
# I've graded all of the questions, but I need to calculate everyone's final grades.

# Here's where you come in.
# I have a list with everyone's name, and the grade they got on each question
# (Note: names and/or grades have been changed to protect the innocent)
# I have all of this information in the following data structure.

# students is a list of pairs of a string and a list of numbers
# from the notation in lecture
Test = List[int]
Student = Tuple[str, Test]
Class = List[Student]

# so, what does this actually look like?

# example:
exampleStudents : Class = [("Allison", [10, 10, 10,  8, 10, 10,  9, 10, 10,  6]), \
                           ("Daniel",  [ 9,  9,  9,  8,  8,  8,  7,  7,  7,  0]), \
                           ("Tristan", [ 7,  7,  7,  7,  7,  7,  7,  7,  0,  7]), \
                           ("Yubin",   [ 1,  2,  3,  4,  5,  6,  7,  8,  9, 10]), \
                           ("Steven",  [ 9,  8,  7,  6,  5,  4,  3,  2, 10, 10])]

# each problem is 10 points, so the maximum possible number of points is 100.
# However, I only count the 8 highest scores, so the real maximum is out of 80.
# The grading scale is stil 90% for an A, 80% for a B, 70% for a C, 60% for a D, and 50% for an F.

# You're job is to make a new list where each element is a list of students who got a certain grade.
# The list should be in the order:
# [Everyone who got A's, Everyone who got B's, Everyone who got C's, Everyone who got D's, Everyone who got F's]
# So, from our example we have
# grade(students) == [["Allison"], ["Daniel"], ["Tristan", "Steven"], ["Yubin"], []]

# Again from class the function grade should return a list of lists of strings
# grade(Examplestudents) : List[List[str]]

# I suggest you break this assignment up into two parts.
# The first part is to write a function for grading an individual student,
# i.e. gradeStudent(scores : Test) will return 0 for an A, 1 for a B, and so on.
# Then write a function to split the students up by grade.

# a function that grades each student, 
# and sorts them into categories based on their final grade

def grade(students : Class) -> List[List[str]]:
    graded = [[],[],[],[],[]]
    i = 0
    while i < len(students):
        Student = students[i]
        name = Student[0]
        Test = Student[1]
        grade = gradeStudent(Test)
        graded[grade] += [name]
        i += 1
    return graded

def gradeStudent(Test : List[int]) -> int:
    Test.sort()
    Test = Test[2:]
    percentage = sum(Test)/8
    if percentage >= 9:
        grade = 0
    elif percentage >= 8:
        grade = 1
    elif percentage >= 7:
        grade = 2
    elif percentage >= 6:
        grade = 3
    else:
        grade = 4
    return grade



###################################################################
# Testing code
###################################################################

def test():
    """
    >>> test_case_mario = [("mario",      [10, 10, 10, 10, 10, 10, 10, 10, 10, 10]), \
                           ("Donky Kong", [ 9,  5,  9,  8,  8,  8,  7,  7,  8,  0]), \
                           ("Bowser",     [ 7,  7,  7,  7,  7,  7,  7,  7,  0,  7]), \
                           ("Yoshi",      [ 1,  4,  3,  7,  5,  6,  4,  7,  9, 10]), \
                           ("Peach",      [ 4,  8,  9,  3,  5,  8,  5,  7, 10, 10])]
    >>> test_case_1 = [("Aplus", [10, 10, 10, 10, 10, 10, 10, 10, 10, 10]), \
                       ("Bplus", [ 8,  8,  8,  8,  8,  8,  8,  8,  8, 8]), \
                       ("Cplus", [ 7,  7,  7,  7,  7,  7,  7,  7,  7, 8]), \
                       ("Dplus", [ 6,  6,  6,  6,  6,  6,  6,  6,  6, 8]), \
                       ("Fplus", [ 5,  5,  5,  5,  5,  5,  5,  5,  5, 8]), \
                       ]
    >>> test_case_2 = [("Amid1", [ 9,  9,  9,  9,  9,  9,  9,  9,  9, 9]), \
                       ("Amid2", [ 9,  9,  9,  9,  9,  9,  9,  9,  9, 4]), \
                       ("Bmid1", [ 8,  8,  8,  8,  8,  8,  8,  8,  8, 3]), \
                       ("Cmid1", [ 7,  7,  7,  7,  7,  7,  7,  7,  7, 5]), \
                       ("Cmid2", [10, 10, 10, 10, 10,  5,  0,  0,  0, 5]), \
                       ("Dmid1", [ 6,  6,  6,  6,  6,  6,  6,  6,  6, 6]), \
                       ("Fmid1", [ 1,  2,  3,  4,  5,  6,  7,  8,  9, 0]), \
                       ("Fmid2", [ 0,  0,  0,  0,  0,  0,  0, 10, 10, 10]), \
                       ("Fmid3", [ 0,  0,  3,  3,  3,  3,  3,  3,  3, 3]), \
                       ]
    >>> test_case_3 = [("Aminus", [ 9,  9,  9,  9,  9,  9,  9,  9,  9, 0]), \
                       ("Bminus", [ 8,  8,  8,  8,  8,  8,  8,  8,  8, 0]), \
                       ("Cminus", [ 7,  7,  7,  7,  7,  7,  7,  7,  7, 0]), \
                       ("Dminus", [ 6,  6,  6,  6,  6,  6,  6,  6,  6, 0]), \
                       ("Fminus", [ 0,  0,  0,  0,  0,  0,  0,  0,  0, 0]), \
                       ]
    >>> test_case_rand = [ \
          ('rand000', [ 3,  2,  5,  7, 10,  1, 10,  6,  2,  1]), ('rand001', [ 5,  4,  7,  4,  2,  1,  4,  1,  0,  4]), \
          ('rand002', [ 5,  9,  3,  6,  2,  3, 10,  9,  0,  2]), ('rand003', [ 9,  6,  0,  4,  5,  6,  5,  9,  8,  9]), \
          ('rand004', [10,  9,  1,  0,  9,  1,  7, 10,  4,  1]), ('rand005', [ 8,  1, 10,  3,  8,  7,  4,  3,  0,  6]), \
          ('rand006', [ 0,  8,  8, 10,  6,  6,  6,  9,  3,  6]), ('rand007', [10,  4,  1, 10,  6, 10,  9,  9,  8,  6]), \
          ('rand008', [ 5,  6,  4, 10,  2,  9,  4,  9,  8,  5]), ('rand009', [ 6,  8,  0,  9,  9,  3,  7,  1,  9,  3]), \
          ('rand010', [ 4,  7,  1,  4,  8,  2, 10,  9,  0, 10]), ('rand011', [ 5,  0,  8,  1,  4,  4,  7,  3, 10,  6]), \
          ('rand012', [ 9,  9,  1,  5,  0, 10,  5,  1,  5,  0]), ('rand013', [ 3,  5,  0,  1,  3, 10,  1,  5, 10,  2]), \
          ('rand014', [ 0,  4,  2,  7,  0,  7,  8,  8,  2,  2]), ('rand015', [ 0,  7,  3,  2,  7,  6,  0,  9, 10,  4]), \
          ('rand016', [ 8, 10,  2,  8,  6,  5,  4,  3,  4,  7]), ('rand017', [ 0, 10,  9,  1,  6,  4,  1,  4, 10,  4]), \
          ('rand018', [ 7,  7,  0,  9,  6,  4, 10,  8,  7,  2]), ('rand019', [ 9,  6,  8,  1,  1,  3,  4,  0,  3,  3]), \
          ('rand020', [ 7,  8,  4,  2,  4,  6,  7,  0,  8,  3]), ('rand021', [ 1,  8,  4,  1,  4,  8,  8,  8, 10,  8]), \
          ('rand022', [ 8,  7,  0,  4, 10,  0,  6, 10,  2,  0]), ('rand023', [ 6,  5,  6,  1,  2,  7, 10,  7,  6,  4]), \
          ('rand024', [ 0,  2,  0,  7,  2,  3,  8,  1,  4,  1]), ('rand025', [10,  8,  1,  0,  0,  6, 10,  4,  1,  1]), \
          ('rand026', [ 9,  9,  7,  9,  8,  1,  4,  2,  1,  6]), ('rand027', [ 9,  0,  7,  8,  6, 10,  7,  3,  8,  2]), \
          ('rand028', [ 5,  9,  5,  0,  7, 10,  2,  9,  2,  3]), ('rand029', [ 3,  7,  0,  4,  5, 10,  2,  9,  3,  2]), \
          ('rand030', [ 5, 10, 10,  7,  5,  0,  5,  6,  1,  6]), ('rand031', [ 5,  5,  2,  8, 10, 10,  2,  0,  0,  4]), \
          ('rand032', [ 6,  1,  8,  9,  6,  5,  4,  1,  0,  0]), ('rand033', [ 6,  2,  7,  0,  5,  5,  1,  0,  7,  4]), \
          ('rand034', [ 2,  8,  0,  3,  8,  7,  5,  2,  8,  1]), ('rand035', [ 8,  0, 10,  8,  3,  6,  4,  3,  4,  7]), \
          ('rand036', [ 0,  3,  2,  4,  6,  7,  5,  8,  6,  8]), ('rand037', [ 5,  1,  1,  1,  0,  1,  5,  2,  3,  8]), \
          ('rand038', [ 2,  7,  2,  7,  3,  0,  3,  7,  9,  4]), ('rand039', [ 1, 10,  3,  5,  2,  8,  6,  7, 10,  6]), \
          ('rand040', [ 2,  0,  0,  2,  7,  7,  6,  7,  2,  6]), ('rand041', [ 3,  9,  5,  0,  3,  2,  5,  4,  0,  9]), \
          ('rand042', [ 1,  2,  1, 10,  5,  2,  2,  3,  2,  5]), ('rand043', [ 5,  9,  3,  9,  8,  2,  5,  1,  4,  5]), \
          ('rand044', [ 6,  2,  3, 10,  5,  7,  4,  9,  7,  1]), ('rand045', [ 4,  4,  9,  1,  2,  6,  5,  6,  5,  9]), \
          ('rand046', [ 5,  6,  5, 10,  2,  4,  0,  8,  9,  3]), ('rand047', [10, 10,  9,  3,  4,  5,  9,  3,  4,  0]), \
          ('rand048', [ 1,  0,  2,  0,  9,  3,  6,  4,  6,  5]), ('rand049', [ 8,  0,  0,  2,  6,  4,  5, 10,  0,  0]), \
          ('rand050', [ 6,  2,  2,  1,  7,  0,  2,  2,  0,  9]), ('rand051', [ 7,  3,  8,  5, 10,  0,  7,  8,  4,  5]), \
          ('rand052', [ 2, 10,  8,  5,  5,  6,  6, 9 ,  1,  4]), ('rand053', [ 8,  8,  2,  9,  2,  9,  7,  7, 10,  0]), \
          ('rand054', [ 7,  3,  6,  9,  8,  4,  0, 10,  9,  5]), ('rand055', [ 9,  9,  9, 10,  7,  9,  9,  3,  5,  8]), \
          ('rand056', [ 5,  3,  4,  5,  0,  4,  5,  2,  4,  0]), ('rand057', [ 4,  3,  2,  2, 10,  3,  0,  2,  8,  7]), \
          ('rand058', [10,  3,  7,  9,  6,  1,  3, 10,  5,  9]), ('rand059', [ 9, 10,  8,  7,  8,  2,  8,  9,  2,  9]), \
          ('rand060', [4 ,  9,  0, 10,  5,  2,  1,  3,  9,  9]), ('rand061', [10,  6,  1,  4,  3,  1,  3, 10,  8,  7]), \
          ('rand062', [ 3,  4,  9,  0,  9, 10,  1,  0,  2,  3]), ('rand063', [ 6,  6,  8,  5,  4,  1,  8,  4,  7, 10]), \
          ('rand064', [ 4,  7,  1,  0,  4, 10,  8,  3,  7,  0]), ('rand065', [ 9,  9,  5,  6,  2,  2,  1,  4,  8, 10]), \
          ('rand066', [ 7,  2,  7,  5,  6,  2,  0,  7,  4,  8]), ('rand067', [ 3,  6,  7,  5,  6, 10,  3,  9,  9,  0]), \
          ('rand068', [ 4,  1,  0,  2,  7,  3,  5,  0,  7,  1]), ('rand069', [ 4,  8,  0,  9,  1,  5,  9,  6,  7,  5]), \
          ('rand070', [ 2,  6,  9,  1,  1,  4,  6,  8,  4,  4]), ('rand071', [ 3,  2,  2,  4,  3,  9, 10,  6,  8,  2]), \
          ('rand072', [ 9,  0,  2,  9,  2,  5,  8,  0,  8,  6]), ('rand073', [ 6,  2,  2,  0,  6,  1,  7, 10,  5, 10]), \
          ('rand074', [ 4,  2, 10,  5,  5,  8,  7,  1,  6,  1]), ('rand075', [ 1, 10,  7,  6,  6,  5,  9,  6,  2,  3]), \
          ('rand076', [ 8,  8,  9,  1,  8,  5,  0, 10, 10,  3]), ('rand077', [ 1,  7,  9, 10,  8,  9,  5,  3,  0,  4]), \
          ('rand078', [ 4,  1,  3,  1, 10,  1, 10,  7,  2,  3]), ('rand079', [10,  7,  3,  5,  9,  8,  2,  0,  2,  6]), \
          ('rand080', [ 0,  2,  9,  6,  3,  8,  7,  3,  0,  1]), ('rand081', [ 6,  8,  9,  9,  9,  1,  9,  1,  3,  7]), \
          ('rand082', [ 0,  3,  9,  5,  2,  0,  8,  0,  8,  6]), ('rand083', [ 8,  7,  2,  4,  2,  5, 10,  4,  9,  8]), \
          ('rand084', [ 2,  8,  1,  6,  7,  6,  4,  1,  7,  0]), ('rand085', [ 3,  5,  5, 10,  5,  9,  3,  6,  7,  2]), \
          ('rand086', [ 0,  7,  6,  2,  1,  2,  3,  3, 10, 10]), ('rand087', [10, 10,  3,  6,  0,  4,  5,  9,  7,  1]), \
          ('rand088', [ 1,  1,  9,  2,  0,  2,  4,  2,  9,  5]), ('rand089', [ 8,  9,  6, 10,  1,  4,  4,  9,  1,  8]), \
          ('rand090', [ 5,  0,  7,  1,  1,  1,  2,  6,  9,  5]), ('rand091', [ 2,  9, 10,  6, 10, 10,  0,  4,  0,  1]), \
          ('rand092', [ 1,  9,  3,  5,  2,  4,  9,  6,  4,  6]), ('rand093', [10,  4,  3,  1,  2,  1,  4,  1,  0,  0]), \
          ('rand094', [ 8, 10,  2,  0,  5,  5,  6,  9,  8,  5]), ('rand095', [ 7,  8, 10,  0,  0,  5,  8,  2,  8,  5]), \
          ('rand096', [ 4,  6,  4,  2,  7,  9,  0,  4,  9,  1]), ('rand097', [ 4,  9,  2,  3,  1, 10,  9,  0,  0,  6]), \
          ('rand098', [ 0, 10,  4,  2,  8, 10,  6,  9,  2,  7]), ('rand099', [ 7,  8,  4,  5,  4,  4,  5,  0,  9,  6])]
    >>> grade(test_case_1)
    [['Aplus'], ['Bplus'], ['Cplus'], ['Dplus'], ['Fplus']]
    >>> grade(test_case_2)
    [['Amid1', 'Amid2'], ['Bmid1'], ['Cmid1', 'Cmid2'], ['Dmid1'], ['Fmid1', 'Fmid2', 'Fmid3']]
    >>> grade(test_case_3)
    [['Aminus'], ['Bminus'], ['Cminus'], ['Dminus'], ['Fminus']]
    >>> grade(test_case_mario)
    [['mario'], ['Donky Kong'], ['Bowser', 'Peach'], ['Yoshi'], []]
    >>> grade(test_case_rand)
    [[], ['rand007', 'rand055', 'rand059'], ['rand003', 'rand006', 'rand008', 'rand018', 'rand021', 'rand027', 'rand053', 'rand054', 'rand058', 'rand076', 'rand081', 'rand089', 'rand094', 'rand098'], ['rand004', 'rand005', 'rand009', 'rand010', 'rand015', 'rand016', 'rand017', 'rand023', 'rand026', 'rand028', 'rand030', 'rand035', 'rand039', 'rand043', 'rand044', 'rand045', 'rand046', 'rand047', 'rand051', 'rand052', 'rand060', 'rand061', 'rand063', 'rand065', 'rand067', 'rand069', 'rand072', 'rand073', 'rand075', 'rand077', 'rand079', 'rand083', 'rand085', 'rand087', 'rand091', 'rand095', 'rand099'], ['rand000', 'rand001', 'rand002', 'rand011', 'rand012', 'rand013', 'rand014', 'rand019', 'rand020', 'rand022', 'rand024', 'rand025', 'rand029', 'rand031', 'rand032', 'rand033', 'rand034', 'rand036', 'rand037', 'rand038', 'rand040', 'rand041', 'rand042', 'rand048', 'rand049', 'rand050', 'rand056', 'rand057', 'rand062', 'rand064', 'rand066', 'rand068', 'rand070', 'rand071', 'rand074', 'rand078', 'rand080', 'rand082', 'rand084', 'rand086', 'rand088', 'rand090', 'rand092', 'rand093', 'rand096', 'rand097']]
    """


if __name__ == "__main__":
    import doctest
    doctest.testmod()

