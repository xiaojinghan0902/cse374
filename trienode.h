 /* trienode.h contains structure and function declarations for 
   a trie implementation 
   CSE374, HW5, 22Wi 
*/

#ifndef TRIENODE_H
#define TRIENODE_H

#include <stdio.h>

#define MAXLEN 50
#define BRANCHES 9

// trieNode is one node in an 9-tree, where branches correspond to
// # and the T9 alphabet.
typedef struct trieNode {
  struct trieNode *branches[BRANCHES];
  char *word;
} trieNode;

Node_t * CreateTrieNode();
int getDigit(char letter);
void BuildTrie(Node_t * root, char * s);
Node_t * FindNode(Node_t * root, char * number);
void malfree(Node_t * root);


#endif
