all: meme.o
	gcc meme.o

main.o: meme.c
	gcc -c meme.c

run:
	./a.out
