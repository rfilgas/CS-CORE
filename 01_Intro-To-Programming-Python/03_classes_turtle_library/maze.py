import random as rng
import turtle as t

DOWN  = 0
RIGHT = 1
UP    = 2
LEFT  = 3

class maze(object):
    def __init__(self,r,c):
        self.rows = r
        self.cols = c
        #walls[dir][row][col]
        self.walls = [[[False for d in [DOWN,RIGHT]] \
                              for j in range(c)]     \
                              for i in range(r)]
        self.gen()
        self.draw()
        self.dir = RIGHT
        self.row = 0
        self.col = 0
        self.valid = True

    def gen(self):
        """
        Generate a random maze using a depth first search.
        Because we're using a depth first search, we'll generate a tree.
        This means our maze will only have one solution.
        """

        seen = [[False for j in range(self.cols)] \
                       for i in range(self.rows)]
        self.gen_maze(seen, 0, 0)

    def gen_maze(self, seen, r, c):
        """
        Actually performs the DFS for generating the maze.

        Parameters:
        self: the maze
        seen: a boolean grid of the squares we've seen
        r: current row
        c: current column
        """

        # we've seen the current square, we don't want to go to it again.
        seen[r][c] = True;

        # shuffel the directions, so we actually go in a random direction
        #        UP           LEFT          DOWN        RIGHT
        order = [(-1,0,DOWN), (0,-1,RIGHT), (0,0,DOWN), (0,0,RIGHT)]
        rng.shuffle(order)

        # for each possible direction check if we can go there
        # we use order to randomly permute the directions.
        for (dr,dc,d) in order:

            nr = r + (d == DOWN)  * (2*dr + 1)
            nc = c + (d == RIGHT) * (2*dc + 1)

            # if we are within the bounds of our maze
            # AND we haven't visited the square above us yet.
            if 0 <= nr < self.rows and \
               0 <= nc < self.cols and \
               not seen[nr][nc]:
                # kill the wall between this square and next square
                self.walls[r+dr][c+dc][d] = True

                # continue from the next square.
                self.gen_maze(seen, nr, nc);
            # end if
        # end for
    # end gen_maze

    def draw(self):
        """
        Draws the maze using turtle graphics.
        The maze will go from (-200,-200) to (200,200)
        Having a size of (400,400)
        """

        #setup
        col = 400/self.cols
        row = 400/self.rows
        t.ht()
        t.speed("fastest")
        t.penup()
        t.goto(-200,200)

        # draw boarder
        t.pendown()
        t.forward(400)
        t.backward(400)
        t.right(90)
        t.forward(400)
        t.backward(400)

        #draw vertical lines
        for c in range(self.cols):
            t.penup()
            t.goto((c+1)*col - 200, 200)
            for r in range(self.rows):
                if self.walls[r][c][RIGHT]:
                    t.penup()
                else:
                    t.pendown()
                t.forward(row)
            #end for
        #end for

        t.left(90)

        #draw horizontal lines
        for r in range(self.rows):
            t.penup()
            t.goto(-200, 200 - (r+1)*row)
            for c in range(self.cols):
                if self.walls[r][c][DOWN]:
                    t.penup()
                else:
                    t.pendown()
                t.forward(row)
            #end for
        #end for

        #put us at the start facing right
        t.penup()
        t.goto(-200+col/2,200-row/2)
        t.st()
        t.speed("normal")
        t.color("blue")
        t.pendown()

    def down(self):
        """
        Can we move down in the maze?
        """
        return self.row < self.rows and self.walls[self.row][self.col][DOWN]

    def right(self):
        """
        Can we move right in the maze?
        """
        return self.col < self.cols and self.walls[self.row][self.col][RIGHT]

    def up(self):
        """
        Can we move up in the maze?
        """
        return self.row > 0 and self.walls[self.row-1][self.col][DOWN]

    def left(self):
        """
        Can we move left in the maze?
        """
        return self.col > 0 and self.walls[self.row][self.col-1][RIGHT]

# global variable to hold the maze.
# this shouldn't be touched by anything outside of this file.
theMaze = None

def start(rows, cols):
    """
    Generate the maze.
    Must be called before any other function.
    """
    global theMaze
    theMaze = maze(rows,cols)

def canGoLeft():
    """
    Returns true if there is no wall to the left of the cursor.
    """
    return theMaze.dir == DOWN  and theMaze.right() or \
           theMaze.dir == RIGHT and theMaze.up()    or \
           theMaze.dir == UP    and theMaze.left()  or \
           theMaze.dir == LEFT  and theMaze.down()

def canGoForward():
    """
    Returns true if there is no wall ahead of the cursor.
    """
    return theMaze.dir == DOWN  and theMaze.down()  or \
           theMaze.dir == RIGHT and theMaze.right() or \
           theMaze.dir == UP    and theMaze.up()    or \
           theMaze.dir == LEFT  and theMaze.left()

def canGoRight():
    """
    Returns true if there is no wall to the right of the cursor.
    """
    return theMaze.dir == DOWN  and theMaze.left()  or \
           theMaze.dir == RIGHT and theMaze.down()  or \
           theMaze.dir == UP    and theMaze.right() or \
           theMaze.dir == LEFT  and theMaze.up()

def canGo(square, dir):
    (row,col) = square
    if dir == DOWN:
        return row < theMaze.rows and theMaze.walls[row][col][DOWN]
    if dir == RIGHT:
        return col < theMaze.cols and theMaze.walls[row][col][RIGHT]
    if dir == UP:
        return row > 0            and theMaze.walls[row-1][col][DOWN]
    if dir == LEFT:
        return col > 0            and theMaze.walls[row][col-1][RIGHT]


def forward():
    """
    move the cursor forward one square.
    """
    if not canGoForward():
        theMaze.valid = False
        t.color("red")
    if theMaze.dir == DOWN:
        t.forward(400/theMaze.rows)
        theMaze.row += 1
    if theMaze.dir == RIGHT:
        t.forward(400/theMaze.cols)
        theMaze.col += 1
    if theMaze.dir == UP:
        t.forward(400/theMaze.rows)
        theMaze.row -= 1
    if theMaze.dir == LEFT:
        t.forward(400/theMaze.cols)
        theMaze.col -= 1


def right():
    """
    Turn the cursor to the right.
    """
    theMaze.dir = (theMaze.dir + 3) % 4
    t.right(90)

def left():
    """
    Turn the cursor to the left.
    """
    theMaze.dir = (theMaze.dir + 1) % 4
    t.left(90)

def finish():
    """
    return True if we are in the lower right corner.
    """
    return theMaze.row == theMaze.rows - 1 and \
           theMaze.col == theMaze.cols - 1

def solved():
    """
    return True if we're in the lower right corner, and we've found a valid path.
    """
    return finish() and theMaze.valid
