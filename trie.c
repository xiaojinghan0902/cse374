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

// Structure for Trie node
typedef struct TrieNode {
    char* word;  // The word associated with the Trie node
    struct TrieNode* children[CHILDREN];  // Pointers to child nodes
} Trie;

// Function to create a new Trie node
Trie* createNode(char* word) {
    Trie* n = (Trie*)malloc(sizeof(Trie));
    n->word = word;
    for (int i = 0; i < CHILDREN; i++) {
        n->children[i] = NULL;
    }
    return n;
}

// Function to insert a word into the Trie
void insert(Trie* root, char* word) {
    int digit;
    int i = 0;
    Trie* current = root;

    // Traverse through each character in the word
    while (i < strlen(word) && (word[i] != '\0' && word[i] != '\n')) {
        digit = convert(word[i]);
        if (digit == -1) {
            return;
        } else {
            if (current->children[digit - 2] == NULL) {
                current->children[digit - 2] = createNode(NULL);
            }
            current = current->children[digit - 2];
        }
        i++;
    }
    
    // Check if the current Trie node already has a word associated with it
    if (current->word == NULL) {
        current->word = word;
    } else {
        // Find the first available child node to store the word
        while (current->children[8] != NULL) {
            current = current->children[8];
        }
        current->children[8] = createNode(word);
    }
}

// Function to search for a word in the Trie
char* search(Trie* root, char* input) {
    if (root == NULL || input[0] == '#') {
        return "Invalid input\n";
    }

    Trie* cur = root;
    int character;

    // Traverse through each character in the input
    while (*input != '\0' && *input != '\n') {
        if (*input == '#') {
            if (cur->children[8] == NULL) {
                return "There are no more T9onyms\n";
            }
            cur = cur->children[8];
        } else {
            character = *input - '0' - 2;
            if (character < 0 || character > 7) {
                return "Invalid input\n";
            } else if (cur->children[character] == NULL) {
                return "Not found in current dictionary\n";
            }
            cur = cur->children[character];
        }
        input++;
    }

    // Check if a word is associated with the current Trie node
    if (cur->word == NULL) {
        return "Not found in current dictionary\n";
    }
    return cur->word;
}

// Function to convert a letter to its corresponding T9 digit
int convert(char letter) {
    int t9[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8,
                  8, 8, 9, 9, 9, 9};
    if (letter == '#') {
        return 1;
    } else {
        return t9[letter - 'a'];
    }
}

void freeMem(Trie* root) {
    for (int i = 0; i < CHILDREN; i++) {
        if (root->children[i] != NULL) {
        freeMem(root->children[i]);
        }
    }
    free(root->word);
    free(root);
}