/*
 * trieNode.c - implementation of a trie node struct used for contstructing a trie to realize T9 predictive text
 * CSE 374 HW 5
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "trienode.h"

#define CHILDREN 10

// Creates a new TrieNode with the given number and word.
// Allocates memory for the node and the word.
TrieNode *make_node(int number, char *word) {
  TrieNode *node = (TrieNode *) malloc(sizeof(TrieNode));
  check_malloc(node);
  char *word_cpy = (char *) malloc(sizeof(char) * (strlen(word) + 1));
  check_malloc(word_cpy);
  strncpy(word_cpy, word, strlen(word) + 1);
  if (node) {
    node->number = number;
    node->word = word_cpy;
    for (int i = 0; i < 11; i++) {
      node->children[i] = NULL;
    }
  }
  return node;
}

// Adds a word with the given code to the Trie.
// Traverses the Trie based on the code and adds nodes as necessary.
// Allocates memory for new nodes and copies the word.
void add_word(TrieNode *root, char *code, char *word) {
  TrieNode *curr = root;
  int i = 0;
  while (code[i] != '\0') {
    int number = code[i] - '0';
    TrieNode *next = curr->children[number];
    if (next == NULL) {
      curr->children[number] = make_node(number, "");
    }
    curr = curr->children[number];
    i++;
  }

  if (strlen(curr->word) == 0) {
    free(curr->word);
    char *word_cpy = (char *) malloc(sizeof(char) * (strlen(word) + 1));
    check_malloc(word_cpy);
    strncpy(word_cpy, word, strlen(word) + 1);
    curr->word = word_cpy;
  } else {
    while (curr->children[10] != NULL) {
      curr = curr->children[10];
    }
    curr->children[10] = make_node(10, word);
  }
}

// Retrieves the TrieNode for the word with the given code.
// Traverses the Trie based on the code and returns the corresponding node.
TrieNode *get_word_node(TrieNode *root, char *code) {
  TrieNode *curr = root;
  int i = 0;
  while (code[i] != '\0') {
    int number = code[i] - '0';
    if (curr->children[number] == NULL) {
      return NULL;
    } else {
      curr = curr->children[number];
    }
    i++;
  }
  return curr;
}

// Frees the memory allocated for the Trie.
// Recursively frees the memory for each node and its children.
void free_memory(TrieNode *root) {
  if (root != NULL) {
    free(root->word);
    for (int i = 0; i < 11; i++) {
      free_memory(root->children[i]);
    }
    free(root);
  }
}

// Prints the Trie in a pre-order traversal.
// Prints the number and word of each node.
void print_tree(TrieNode *root) {
  if (root != NULL) {
    int number = root->number;
    char *word = root->word;
    printf("(%d, %s) ", number, word);
    for (int i = 0; i < 11; i++) {
      print_tree(root->children[i]);
    }
  }
}

// Checks if a malloc operation was successful.
// Prints an error message and exits if malloc failed.
void check_malloc(void *pointer) {
  if (!pointer) {
    fprintf(stderr, "Malloc failed, not enough space in heap\n");
    exit(EXIT_FAILURE);
  }
}
