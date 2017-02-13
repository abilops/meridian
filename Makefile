#
# Makefile
#
# copied from Computer Science 50 Problem Set 5
# 
#


# compiler to use
CC = clang

# flags to pass compiler
CFLAGS = -ggdb3 -O3 -Qunused-arguments -std=c99 -Wall -Werror -lm

# name for executable
EXE = meridian

# space-separated list of header files
HDRS = meridian.h

# space-separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS =

# space-separated list of source files
SRCS = main.c functions.c

# automatically generated list of object files
OBJS = $(SRCS:.c=.o)


# default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# dependencies 
$(OBJS): $(HDRS) Makefile

# housekeeping
clean:
	rm -f core $(EXE) *.o .tempsorted sandbox/* dem/*
