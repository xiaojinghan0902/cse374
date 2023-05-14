# Makefile for t9/trieNode program
# CSE 374 HW 5

# This target is the final executable that will be created.
# It depends on the object files tnine.o and trie.o.
tnine: tnine.o trie.o
	gcc -Wall -g -std=c11 -o t9 tnine.o trie.o

# This target is responsible for compiling trie.c into the object file trie.o.
# It depends on trie.c and trienode.h.
trie.o: trie.c trienode.h
	gcc -Wall -g -std=c11 -c trie.c

tnine.o: tnine.c trienode.h
	gcc -Wall -g -std=c11 -c tnine.c

# This target removes all object files and any temporary files.
clean:
	rm -f *.o t9 *~
