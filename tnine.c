
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"


// run_session run the on-going decoding interaction with the
// user.  It requires a previously build wordTrie to work.
void run_session(trieNode *wordTrie);

int main(int argc, char **argv) {
  FILE *dictionary = NULL;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s [DICTIONARY]\n", argv[0]);
    return EXIT_FAILURE;
  } else {
    dictionary = fopen(argv[1], "r");
    if (!dictionary) {
      fprintf(stderr, "Error: Cannot open %s\n", argv[1]);
      return EXIT_FAILURE;
    }
  }

  trieNode* root = makeNode();
  int bufferLength = 255;
  char buffer[bufferLength]; 
  while(fgets(buffer, bufferLength, dictionary)) {
    insert(buffer,root);
  }
  run_session(root);
  printf("session end\n");
  free_tree(root);
  return(EXIT_SUCCESS);
}

void run_session(trieNode *root) {
    char input[MAXLEN];  // Buffer to store user input
    printf("Enter \"exit\" to quit.\n");
    trieNode* curr;  // Variable to keep track of the current node in the trie

    while (1) {
        printf("Enter Key Sequence (or \"#\" for next word):\n> ");
        scanf("%s", input);  // Read user input

        if (strcmp(input, "exit") == 0) {
            break;  // Break the loop and exit the session if the user enters "exit"
        } else {
            if (strcmp(input, "#") != 0) {
                curr = search(root, input);  // Search for the node corresponding to the input in the trie
            } else {
                curr = search(curr, input);  // Search for the next word starting from the current node
            }  
        }
    }
}

