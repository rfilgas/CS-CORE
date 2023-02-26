# Ryan Filgas:
# Due: 6/30

# part 1: Making Change
#
# You are a merchant in the town of skytown.
# skytown uses a new currency called the rupy
# Rupys come in several colors, and have different values.
# The exchange rate is listed below
#
# Green Rupy  : 1 Green Rupy
# Blue Rupy   : 5 Green Rupys
# Red Rupy    : 20 Green Rupys
# Silver Rupy : 100 Green Rupys
# Gold Rupy   : 300 Green Rupys
#
# Unfortunately, you have one customer who always pays in green rupys.
# He's not a very good customer.
#
# Your job is to make change for customers using the fewest rupys possible.
#
# You should return a tuple (green,blue,red,silver,gold) 
# Where gold is the number of gold rupys, silver is the number silver rupys, and so on.

# example:
# makeChange(465, 1000) should return (0,3,1,2,1)
# money back: 535
# 1 gold rupy    : 300
# money back: 235
# 2 silver rupy  : 200
# money back: 35
# 1 red rupy     :  20
# money back: 15
# 3 blue rupy    :  15
# money back: 0
# 0 green rupy   :   0
# total change   : 535


# 1 dollar  = 100 pennies
# 1 quarter = 25 pennies
# 1 dime    = 10 pennies
# 1 nickle  = 5 pennies
# cost $7.16
# paid $10.00
# money back: $2.84
# coins back: (2 dollar, ? quarters, ? dimes, ? nickles, ? pennies)
# money back: $.84
# coins back: (2 dollar, 3 quarters, ? dimes, ? nickles, ? pennies)
# money back: $.9
# coins back: (2 dollar, 3 quarters, ? dimes, ? nickles, ? pennies)
# money back: $.9
# coins back: (2 dollar, 3 quarters, 0 dimes, 1 nickles, ? pennies)
# money back: $.4
# coins back: (2 dollar, 3 quarters, 0 dimes, 1 nickles, 4 pennies)

def makeChange(price, payment):
    # get the amount of change we need.
    change = payment - price

    #To find the number of rupys we divide the total by the value
    #Then the total % the value gives what is left over.
    gold   = change // 300
    change = change %  300

    silver = change // 100
    change = change %  100

    red    = change // 20
    change = change %  20

    blue   = change // 5

    #since green is only worth 1 rupy we don't need to divide again
    green  = change %  5

    return (green,blue,red,silver,gold)




# part 2: drawing a flag
#
# using turtle graphics, draw a flag for some country.
# You can pick whatever country you want, although, I wouldn't recommend Nepal.
# This is only assignment 1.
#
# You may find it helpful to write some simpler functions like drawRectangle.

import turtle as t

# forward and backward are just a quick way to move so I don't have to type
# t.penup() and t.pendown() all the time
def forward(size):
    t.penup()
    t.forward(size)
    t.pendown()

def backward(size):
    t.penup()
    t.backward(size)
    t.pendown()

def drawStar(size):
    """
    Draw a star.  Assume that we are facing to the right.
    """
    t.color("white")
    t.begin_fill()
    t.forward(size)
    # When drawing a star, we will make a total of 2 full rotations.
    # since there are 5 turns, we turn a total of (360 * 2) / 5 degrees.
    t.right(144)
    t.forward(size)
    t.right(144)
    t.forward(size)
    t.right(144)
    t.forward(size)
    t.right(144)
    t.forward(size)
    t.right(144)
    t.end_fill()

def draw5StarRow(size, hspace, vspace):
    t.right(90)
    forward(size+vspace)
    t.left(90)
    forward(hspace + size + hspace)
    drawStar(size)
    forward(2*(size + hspace))
    drawStar(size)
    forward(2*(size + hspace))
    drawStar(size)
    forward(2*(size + hspace))
    drawStar(size)
    forward(2*(size + hspace))
    drawStar(size)
    backward(9*size + 10*hspace)

def draw6StarRow(size, hspace, vspace):
    t.right(90)
    forward(size+vspace)
    t.left(90)
    forward(hspace)
    drawStar(size)
    forward(2*(size + hspace))
    drawStar(size)
    forward(2*(size + hspace))
    drawStar(size)
    forward(2*(size + hspace))
    drawStar(size)
    forward(2*(size + hspace))
    drawStar(size)
    forward(2*(size + hspace))
    drawStar(size)
    backward(10*size + 11*hspace)

def drawRect(length,width, color):
    """
    Draw a stripe.  Assume we are facing to the right.
    """
    t.color(color)
    t.begin_fill()
    t.forward(length)
    t.right(90)
    t.forward(width)
    t.right(90)
    t.forward(length)
    t.right(90)
    t.forward(width)
    t.right(90)
    t.end_fill()

def drawStars(size, hspace, vspace):
    drawRect(11*size + 12*hspace, 9*size + 10*vspace, "blue")
    t.left(90)
    forward(size)
    t.right(90)
    draw6StarRow(size, hspace, vspace)
    draw5StarRow(size, hspace, vspace)
    draw6StarRow(size, hspace, vspace)
    draw5StarRow(size, hspace, vspace)
    draw6StarRow(size, hspace, vspace)
    draw5StarRow(size, hspace, vspace)
    draw6StarRow(size, hspace, vspace)
    draw5StarRow(size, hspace, vspace)
    draw6StarRow(size, hspace, vspace)
    t.left(90)
    forward(8*size + 9*vspace)
    t.right(90)

def drawSideStripes(length, width):
    drawRect(length, width, "red")
    t.right(90)
    forward(width)
    t.left(90)
    drawRect(length, width, "white")
    t.right(90)
    forward(width)
    t.left(90)
    drawRect(length, width, "red")
    t.right(90)
    forward(width)
    t.left(90)
    drawRect(length, width, "white")
    t.right(90)
    forward(width)
    t.left(90)
    drawRect(length, width, "red")
    t.right(90)
    forward(width)
    t.left(90)
    drawRect(length, width, "white")
    t.right(90)
    forward(width)
    t.left(90)
    drawRect(length, width, "red")
    t.left(90)
    forward(6*width)
    t.right(90)

def drawBottomStripes(length, width):
    drawRect(length, width, "white")
    t.right(90)
    forward(width)
    t.left(90)
    drawRect(length, width, "red")
    t.right(90)
    forward(width)
    t.left(90)
    drawRect(length, width, "white")
    t.right(90)
    forward(width)
    t.left(90)
    drawRect(length, width, "red")
    t.right(90)
    forward(width)
    t.left(90)
    drawRect(length, width, "white")
    t.right(90)
    forward(width)
    t.left(90)
    drawRect(length, width, "red")
    t.left(90)
    forward(5*width)
    t.right(90)

def drawFlag():
    # flag has a 4:3 ratio
    flagWidth = 416
    flagHeight = 312

    # found a good size for the stas and gaps between the by guess and check
    starSize = 11
    starVerticalSpace = 7
    starHorizontalSpace = 5

    # there are 5 or 6 stars in each row, but there's space for all 11 stars
    # + the gaps on the left and right
    boxWidth = 11 * starSize + 12*starHorizontalSpace
    # There are 9 rows of stars + gaps on either side
    boxHeight = 9 * starSize + 10*starVerticalSpace

    #We want the 7 stripes to add up to the box height
    # 7*24 == 168
    # 9*11 + 10*7 = 169
    # Well, this is close, and it'll be hidden by the white stripe below it
    StripeHeight = 24


    # move to the top left corner of the flag
    t.penup()
    t.right(180)
    t.forward(flagWidth//2)
    t.right(90)
    t.forward(flagHeight//2)
    t.right(90)
    t.pendown()

    drawStars(starSize, starHorizontalSpace, starVerticalSpace)

    # move to the right side of the box to start drawing stripes
    forward(181)
    drawSideStripes(flagSize - boxWidth, 24)

    # move back below the box to start drawing the vertical stripes
    t.penup()
    backward(boxWidth)
    t.right(90)
    forward(boxWidth)
    t.left(90)
    t.pendown()
    drawBottomStripes(416, 24)

t.speed(0)
drawFlag()
