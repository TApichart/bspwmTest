all: main

main: bspwmTest.c
		gcc -lncurses -o bspwmTest bspwmTest.c
