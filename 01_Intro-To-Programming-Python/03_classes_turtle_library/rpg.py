
# Name: Ryan Filgas
# Due: 7/7

########################################################
# Part 2
########################################################

# Making an RPG engine
#
# Imagine that you are on the team working on the hit new mobile game
# "Rock, Paper, Scissors: The Videogame"
# Your job is to write the battle system.
#
# Each character in this game has 4 stats
#
# HP: Hit points, the amount of health you have remaining
# Str: Strength, how much damage your attack does
# Def: Defense, how much you resist attacks
# Type: Your character's Type, this can be one of "rock", "paper", or "scissors"
#
# This game has very complex rules for types which I will demonstrate with this diagram
#
#             scissors
#             /      ^
#            /        \
#           /          \
#          /            \
#         v              \
#       paper --------> rock
#
# type A is weak to type B if there is an arrow pointing from B to A
# example: Paper is weak to Scissors
#
# type A is Strong against type B if the is an arrow pointing from A to B
# example: Paper is strong against Rock
#
# Now, you need to  calculate the amount of remaining hp after an attack.
#
# the formula for this is 
# hp_remaining = hp - ((attack - defense) * typeEffectiveness)
#
# typeEffectiveness is 0.5 if the attack type is weak to the defense type.
# typeEffectiveness is 2 if the attack type is strong against the defense type.

# You need to write the function
# attack(player1, player2)
# Player1 and player2 are tuples
# (type, str, def, hp)

# Examples:

# If paper has 20 strength, and attacks rock with 50 hp and 10 defense,
# then rock should have 50 - ((20 - 10) * 2) == 30
# so 
# player1 = ("paper", 20, 0, 11)
# player2 = ("rock", 111, 10, 50)
# attack(player1, player2) should return 30

# If scissors has 100 strength, and attacks rock with 30 hp and 10 defense,
# then rock should have 30 - ((100 - 10) // 2) == -15
# but rock can't have less than 0 hp
# player1 = ("scissors", 100, 0, 11)
# player2 = ("rock", 111, 10, 30)
# attack(player1, player2) should return 0

# If paper has 10 strength, and attacks rock with 30 hp and 30 defense,
# then rock should have 30 - ((10 - 30) * 2) == 70
# It looks like paper did negative damage with that attack,
# but rock can't gain hp from an attack, so we return the starting hp.
# player1 = ("paper", 10, 20, 30)
# player2 = ("rock", 111, 30, 30)
# attack(player1, player2) should return 30


#
# Things to keep in mind:
# An attack should never do less than 0 damage
# An opponent should never have less than 0 hp after an attack
#
# tips:
# The calculation to determine if a type is strong or weak to another type is complicated.
# Consider splitting this calculation into it's own function.

def attack(player1,player2):
    
    p1Type = (player1[0])
    p1Str = (player1[1])
    p1Def = (player1[2])
    p1hp_remaining = (player1[3])
    p2Type = (player2[0])
    p2Str = (player2[1])
    p2Def = (player2[2])
    hp_remaining = (player2[3])
    p1_vs_p2 = (p1Str - p2Def)
    
    def rps():
        if p1Type == p2Type:
            advantage = 1
        elif p1Type == "rock" and p2Type == "paper":
            advantage = .5
        elif p1Type == "scissors" and p2Type == "rock":
            advantage = .5  
        elif p1Type == "paper" and p2Type == "scissors":
            advantage = .5
        else: 
            advantage = 2
        return (advantage)
    
    typeEffectiveness = rps()
  

    #exception for Strength - Defense when answer is < 0
    if p1_vs_p2 < 0:
        p1_vs_p2 = 0
     
    
    hp_remaining = (hp_remaining - (p1_vs_p2) * typeEffectiveness)
    
    #exception if hp <0, hp will read as zero
    if hp_remaining < 0:
        hp_remaining = 0
        
    return int(hp_remaining)


########################################################
# Part 2
########################################################

# Solveing a maze

import maze as m

# I've made a python file that draws a maze.
# You start in the upper left corner facing right,
# and your goal is to get to the lower right corner.
# Just like turtle graphics, you have 
# m.left() turns left 90 degrees
# m.right() turns right 90 degrees
# m.forward() moves forward 1 square.
#
# But this time we have a few more commands.
# m.canGoLeft() returns True if you can go left. (there's no wall there)
# m.canGoRight() returns True if you can go right.
# m.canGoForward() returns True if you can go forward.
# 
# Your job is to write a function solve() which will find a path
# from the top left square to the bottom right without crossing any walls.
# 
# This seems hard, but we can use the left wall trick for solving a maze.
# You'll always get to the end of a maze if you follow the left wall.
#
# You may find that you end up retracing your steps in your solution.
# That's ok.  We'll learn how to deal with that later.


def solve():
    
    """
    Before each step, must check if maze is completed. If not, take a step.
    For each step, must first check left, then forward, then right.
    If no direction is open, turn around, and take a step.
    """
    def step():
        if m.canGoLeft():
            m.left()
            m.forward()
        elif m.canGoForward():
            m.forward()
        elif m.canGoRight():
            m.right()
            m.forward()
        else:
             m.left()
             m.left()
    def check():
        while not m.finish():
            step()
        else:
            return ()
    check()
    
    
########################################################
# Code for testing attack()
########################################################
def testAttack():
    """
    >>> rocky       = ("rock",     100, 20,  80)
    >>> peter       = ("rock",      40, 60,  60)
    >>> rockMonster = ("rock",      60, 30, 100)
    >>> paperMan    = ("paper",     40, 20, 100)
    >>> paperMario  = ("paper",     80, 10, 100)
    >>> gutenberg   = ("paper",     20, 70, 100)
    >>> kartana     = ("scissors", 130, 10,  40)
    >>> nightblood  = ("scissors", 150,  0,  20)
    >>> fi          = ("scissors",  20, 80,  20)
    >>> attack(paperMan,rockMonster)
    80
    >>> attack(rocky,fi)
    0
    >>> attack(gutenberg,fi)
    20
    >>> attack(peter,gutenberg)
    100
    >>> attack(paperMario,fi)
    20
    >>> attack(kartana,rocky)
    25
    >>> attack(kartana,paperMario)
    0
    >>> attack(gutenberg,rocky)
    80
    >>> attack(peter,nightblood)
    0
    >>> attack(rockMonster,rocky)
    40
    >>> attack(paperMario,gutenberg)
    90
    >>> attack(kartana,fi)
    0
    >>> m.start(10,10)
    >>> solve()
    >>> m.solved()
    True
    """

if __name__ == "__main__":
    import doctest
    doctest.testmod()
