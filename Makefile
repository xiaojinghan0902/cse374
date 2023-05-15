# Xiaojing Han
# Makefile for t9/trieNode program
# CSE 374 HW 5

#build the executable file named "t9."
all: t9

t9: main.o trie.o
	gcc -Wall -std=c11 -o t9 main.o trie.o

main.o: main.c trie.h
	gcc -Wall -std=c11 -c main.c

trie.o: trie.c trie.h
	gcc -Wall -std=c11 -c trie.c

clean:
	rm -f *.o output *~ 
