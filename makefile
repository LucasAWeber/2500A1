weberLucasA1: weberLucasA1.o weberLucasA1Main.o
	gcc -Wall -std=c99 weberLucasA1.o weberLucasA1Main.o -o weberLucasA1
weberLucasA1Main.o: weberLucasA1Main.c weberLucasA1.h
	gcc -Wall -std=c99 -c weberLucasA1Main.c
weberLucasA1.o: weberLucasA1.c weberLucasA1.h
	gcc -Wall -std=c99 -c weberLucasA1.c
clean:
	rm *.o weberLucasA1