# Xiaojing Han
# Makefile for t9/trieNode program
# CSE 374 HW 5

#build the executable file named "t9."
all: t9

t9: tnine.o trie.o
	gcc -Wall -std=c11 -o t9 tnine.o trie.o

tnine.o: tnine.c trienode.h
	gcc -Wall -std=c11 -c tnine.c

trie.o: trie.c trienode.h
	gcc -Wall -std=c11 -c trie.c

clean:
	rm -f *.o output *~ 

