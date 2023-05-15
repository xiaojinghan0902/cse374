/* trie implements a trie, made of trieNodes. This includes
   code to build, search, and delete a trie
   CSE374, HW5, 22wi 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"

#define BRANCHES 9

trieNode* makeNode(){
   // Allocate memory for a new trie node
   trieNode* node = (trieNode*) malloc(sizeof(trieNode));

   // Check if memory allocation was successful
   if (node == NULL){
      fprintf(stderr,"run out of space while allocating memory\n");
      EXIT_FAILURE;
   }

   // Initialize the word pointer to NULL
   node ->word = NULL;

   // Initialize each branch pointer to NULL
   for(int i = 0; i < BRANCHES; i++){
      node -> branches[i] = NULL;
   }

   // Return the newly created node
   return node;
}


void insert(char* word, trieNode* root){
   trieNode* current = root;
   int length = strlen(word) - 1;

   // Traverse through each character in the word
   for(int i = 0; i < length; i++){
      int index = charToInt(word[i]) - 2;

      // Create a new node if the current branch is NULL
      if (current ->branches[index] == NULL){
         current ->branches[index] = makeNode();
      }
      current = current -> branches[index];
   }

   // Check if the current node already has a word
   if (current -> word == NULL){
      // Allocate memory for the word and copy it
      current->word = (char*) malloc(strlen(word)*sizeof(char));
      if (current->word == NULL){
         fprintf(stderr,"run out of space while allocating memory\n");
         EXIT_FAILURE;
      }else{
         strncpy(current->word,word,strlen(word));
      }
   }else{
      // If the current node already has a word, traverse to the last branch node
      while(current->word != NULL){
         if(current->branches[BRANCHES-1]==NULL){
            current->branches[BRANCHES-1] = makeNode();
         }
         current = current->branches[BRANCHES-1];
      }

      // Allocate memory for the word and copy it
      current->word = (char*) malloc(strlen(word)*sizeof(char));
      if (current->word == NULL){
         fprintf(stderr,"run out of space while allocating memory\n");
         EXIT_FAILURE;
      }else{
         strncpy(current->word,word,strlen(word));
      }
   }
}

int charToInt(char ch){
   int res = 0;
   // Map characters to their corresponding digit on a phone keypad
   if (ch == 'a'|| ch == 'b' || ch == 'c'){
      res = 2;
   }else if (ch == 'd'|| ch == 'e' || ch == 'f'){
      res = 3;
   }else if (ch == 'g'|| ch == 'h' || ch == 'i'){
      res = 4;
   }else if (ch == 'j'|| ch == 'k' || ch == 'l'){
      res = 5;
   }else if (ch == 'm'|| ch == 'n' || ch == 'o'){
      res = 6;
   }else if (ch == 'p'|| ch == 'q' || ch == 'r' || ch =='s'){
      res = 7;
   }else if (ch == 't'|| ch == 'u' || ch == 'v'){
      res = 8;
   }else if (ch == 'w'|| ch == 'x' || ch == 'y' || ch =='z'){
      res = 9;
   }
   return res;
}

trieNode* search(trieNode* node, char* input) {
  int flag = 0;
  for (int i = 0; i < strlen(input); i++) {
    int branch_index;
    // Handle the special case when '#' is encountered
    if (input[i] == '#') {
      branch_index = 8;
      flag = 1;
    } else {
      // Calculate the branch index based on the input character
      branch_index = input[i] - '0' - 2;
      if (branch_index < 0) {
        printf("invalid input\n");
        return NULL;
      }
    }
    // Traverse to the next branch
    if (node != NULL) {
      node = node->branches[branch_index];
    }
  }
   if (node != NULL && node->word != NULL) {
      // If a word is found in the node, print it
      printf("%s", node->word);
      return node;
   } else {
      if (flag == 1) {
         // Handle the case when '#' is encountered but no more T9onyms are available
         printf("There are no more T9onyms.\n");
      } else {
         // Handle the case when no word is found in the current dictionary
         printf("Not found in current dictionary.\n");
      }
   }
   return NULL;
}

void freetree(trieNode *root){
   // Recursively free the tree nodes and words
   for (int i = 0; i < BRANCHES;i++){
      if(root ->branches[i] != NULL){
         free_tree(root->branches[i]);
      }
   }
   // Free the word associated with the root node
   if (root->word != NULL){
      free(root->word);
   }
   // Free the root node
   free(root);
}
