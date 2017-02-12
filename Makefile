NAME = meridian
CSRCS = *.c
CHDRS = $(CSRCS):.c=.h
LIBS = -lm -lcs50
#CC = clang
#SET THE CC yourself in ~/.bashrc or right now
#with "export CC=gcc"
CFLAGS = -Wall -Werror -ggdb3

all:$(NAME)

#$(CSRCS) : $(CHDRS)

$(NAME):$(CSRCS)
	$(CC) $(CFLAGS) -o $(NAME) $(CSRCS) $(LIBS)

clean :
	 rm -If $(NAME) .tempsorted sandbox/* dem/*

distclean:
	clean
