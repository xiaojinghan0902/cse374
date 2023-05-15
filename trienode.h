 /* trienode.h contains structure and function declarations for 
   a trie implementation 
   CSE374, HW5, 22Wi 
*/
#ifndef TRIENODE_H
#define TRIENODE_H

#include <stdio.h>

#define MAXLEN 50
#define BRANCHES 9

typedef struct trieNode {
  struct trieNode *branches[BRANCHES]; // Array of child nodes for each digit (0-8)
  char *word; // Pointer to the word stored at the trie node
} trieNode;

trieNode* makeNode(); // Function to create a new trie node

void insert(char* word, trieNode* root); // Function to insert a word into the trie

int charToInt(char ch); // Function to convert a character digit to an integer

trieNode* search(trieNode* trie, char* input); // Function to search for a word in the trie based on a given input sequence

void freetree(trieNode *root); // Function to free the memory occupied by the trie

#endif
