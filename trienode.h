/*
 * trieNode.h - interfece to routine to contstruct a trie to realize T9 predictive text
 * CSE 374 HW 5
 */
#ifndef TRIE_H
#define TRIE_H

typedef struct TrieNode {
  int number;
  char *word;
  struct TrieNode *children[11];
} TrieNode;

TrieNode *make_node(int number, char *word);

void add_word(TrieNode *root, char *code, char *word);
TrieNode *get_word_node(TrieNode *root, char *code);
void free_memory(TrieNode *root);
void print_tree(TrieNode *root);

void check_malloc(void *pointer);

#endif 