meridian: main.c structs.h
	gcc -ggdb3 -O0 -std=c99 -Wall -Werror -o meridian main.c -lm

clean:
	rm -f *.o a.out core main
