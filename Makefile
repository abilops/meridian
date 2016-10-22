meridian: main.c structs.h
	clang-3.8 -ggdb3 -O0 -std=c99 -Wall -Werror -o meridian main.c -lm

clean:
	rm -f *.o a.out core main
