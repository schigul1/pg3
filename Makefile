CFLAGS=-g -Wall -std=c99
LDFLAGS=
LDLIBS=-lcunit
ARFLAGS= rcs

all: demo test

%.a : %.o
	$(AR) $(ARFLAGS) $@ $^

% : %.c functions.c solutions.a
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

# Removes any files/directories 
# created using student files as prerequisites
.PHONY: clean
clean:
	rm -fv *.o demo test $(USER).tar
	rm -rfv $(USER)
	rm -fv *~ \#*\# *.swp 

# Secret grader Makefile additions ;)
# Just kidding! It's not secret, but you can safely ignore it.
include grading.make