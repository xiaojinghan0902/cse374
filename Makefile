# Xiaojing Han
# Makefile for t9/trieNode program
# CSE 374 HW 5

#build the executable file named "t9."
tnine: tnine.o trie.o
	gcc -Wall -g -std=c11 -o t9 tnine.o trie.o


trie.o: trie.c trienode.h
	gcc -Wall -g -std=c11 -c trie.c

tnine.o: tnine.c trienode.h
	gcc -Wall -g -std=c11 -c tnine.c

clean:
	rm -f *.o t9 *~

