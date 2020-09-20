map1: map1.o tree.o format.o
	gcc -o map1 map1.o tree.o format.o -lm

map2: map2.o tree2.o format.o
	gcc -o map2 map2.o tree2.o format.o -lm

map1.o: map1.c tree.h
	gcc -c -Wall map1.c -lm

map2.o: map2.c tree2.h
	gcc -c -Wall map2.c -lm

tree.o: tree.c tree.h
	gcc -c -Wall tree.c -lm

format.o: format.c format.h
	gcc -c -Wall format.c -lm

tree2.o: tree2.c tree2.h
	gcc -c -Wall tree2.c -lm

