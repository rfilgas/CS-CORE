# This Makefile is set up for CS201 A1
# copy to your MCECS account with:
# cp ~markem/public_html/CS201/homework/Makefile .
# NOTE: All indented lines are indented with a tab character.
#       This is required.

CC=gcc
CFLAGS=
DFLAGS=
PROGS=a4

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $< -o $@ -lm -g -Wall

clean:
	rm -f $(PROGS) *.o ~*


