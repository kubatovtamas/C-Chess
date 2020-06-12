# -*- MakeFile -*-
#target: dependencies
#	action

sakk: main.o libsakk.o
	gcc main.o libsakk.o -o sakk

libsakk.o: ./Lib/libsakk.c
	gcc -c ./Lib/libsakk.c -o libsakk.o

main.o: main.c
	gcc -c main.c -o main.o

clean:
	rm -rf sakk *.o
