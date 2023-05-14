/* tnine is a program that drives a trie / t9 program.  This code
   will build a trie, according to trienode.  It will also run
   an interactive session where the user can retrieve words using
   t9 sequences.
   CSE374, HW5, 22wi 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"

// run_session run the on-going decoding interaction with the
// user.  It requires a previously build wordTrie to work.
void run_session(trieNode *wordTrie);

int main(int argc, char **argv) {
  FILE *dictionary = NULL;
  trieNode *wordTrie = NULL;

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

  // build the trie
  wordTrie = buildTrie(dictionary);
  fclose(dictionary);

  // Run interactive session
  run_session(wordTrie);

  // Clean up
  freeTrie(wordTrie);

  
  return(EXIT_SUCCESS);
}


void run_session(trieNode *wordTrie) {
    printf("Enter \"exit\" to quit.\n");
    char number[100]; // Store the entered digits
    int control = 1; // Control the status of the interactive session
    trieNode *current = wordTrie; // Used to store the traversal result in order to handle the next entry beginning with "#"

    while (control) {
        printf("Enter Key Sequence (or \"#\" for next word):\n");
        scanf("%s", number);

        if (strcmp("exit", number) == 0) {
            control = 0;
        } else {
            if (number[0] != '#') {
                current = findNode(wordTrie, number);
            } else {
                current = findNode(current, number);
            }

            if (current != NULL) {
                if (current->word != NULL) {
                    printf("\'%s\'\n", current->word);
                } else {
                    printf("Not found in current dictionary.\n");
                }
            } else {
                if (number[strlen(number) - 1] == '#') {
                    printf("There are no more T9onyms.\n");
                } else {
                    printf("Not found in current dictionary.\n");
                }
            }
        }
    }
}



