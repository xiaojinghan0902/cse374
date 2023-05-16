/*
 * trieNode.h - interfece to routine to contstruct a trie to realize T9 predictive text
 * CSE 374 HW 5
 */
#ifndef TRIE_H
#define TRIE_H

typedef struct Trie {
    char* word;
    struct Trie *children[10];
} trie;

trie* createNode(char* word);
void insert(trie* root, char* word);
char* search(trie* root, char* word);
int convert(char letter);
void freeMem(trie* root);

#endif 