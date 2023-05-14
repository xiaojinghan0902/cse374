/* tnine is a program that drives a trie / t9 program.  This code
   will build a trie, according to trienode.  It will also run
   an interactive session where the user can retrieve words using
   t9 sequences.
   CSE374, HW5, 22wi 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "trienode.h"

// read words from dictionary to build the trie and output the search result of
// the corresponding word after the user type the digit sequence
int main(int argc, char* argv[]) {
  FILE * fp;
  char line[100];
  Node_t * root = CreateTrieNode();
  // read file
  fp = fopen(argv[1], "r");
  if (fp != NULL) {
    while (fgets(line, 100, fp) != NULL) {
      BuildTrie(root, line);
    }
  } else {
    fprintf(stderr, "%s", "Could not open the file.\n");
    return 1;
  }
  fclose(fp);
  printf("Enter \"exit\" to quit.\n");
  char number[100];  // store the enter digits
  int control = 1;  // control the status of interactive session
  Node_t * current = root;  // used to store the traverse result in order to
  // handle the next enter begins with "#"
  while (control) {
    printf("Enter Key Sequence (or \"#\" for next word): \n");
    scanf("%s", number);
    if (strcmp("exit", number) != 0) {
      if (number[0] != '#') {
      current = FindNode(root, number);
      } else {
      current = FindNode(current, number);
      }
      if (current != NULL) {
        if (current -> word) {
          printf("\'%s\'\n", current -> word);
        } else {
          printf("Not found in current dictionary.\n");
        }
      } else {
        if (number[strlen(number) - 1] == '#') {
          printf("There are no more T9onyms\n");
        } else {
          printf("Not found in current dictionary.\n");
        }
      }
    } else {
      control = 0;
    }
  }
  // free all the malloced space from heap
  malfree(root);
  free(root);
  return 0;
}

