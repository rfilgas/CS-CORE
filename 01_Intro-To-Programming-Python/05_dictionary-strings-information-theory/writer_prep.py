from typing import List, Tuple, Dict, TypeVar
import random as r


def birthday(people : List[int]) -> int:
    bdays = set()
    for person in people:
        if person in bdays:
            return person
        else:
            bdays = bdays | {person}
    return 0

#start with an empty dictionary
#loop through the data
#add/modify to dictionary

def birthdayCount(people : List[int]) -> Dict[int,int]:
    bdays = {}
    for person in people:
        if person in bdays:
            bdays[person] = bdays[person] + 1
        else:
            bdays[person] = 1
    return bdays



def randList(n : int) -> List[int]:
    out = []
    for x in range(n):
        out += [r.choice(range(1,366))]
    return out
        
d = birthdayCount(randList(50))
for x in d:
    if d[x] > 1:
        print(x, d[x])
