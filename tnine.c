/*
 * t9.c - the main program uses the trieNode for T9 predictive text implementation
 * CSE 374 HW 5
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "trienode.h"

#define MAX_LENGTH 100 

#define T9_CHARS "23456789#" 
#define MAX_WORD 100           

void create_table(int *table);
void user_interface(TrieNode *root);
void get_T9_code(char *word, char *code, int *table);
int check_valid_code(char *code);

int main(int argc, char**argv) {
  FILE *file = fopen(argv[1], "r");
  if (!file) {
    fprintf(stderr, "unable to open dictionary");
    exit(EXIT_FAILURE);
  }

  int *table = (int *) malloc(26 * sizeof(int));
  check_malloc(table);
  create_table(table);
  TrieNode *root = make_node(-1, "");
  char line[MAX_WORD];
  char code[MAX_WORD];
  code[0] ='\0';
  while (fgets(line, MAX_WORD, file)) {
    line[strlen(line) - 1] = '\0';
    get_T9_code(line, code, table);
    if (!check_valid_code(code)) {
      continue;
    }
    add_word(root, code, line);
  }

  user_interface(root);

  free(table);
  free_memory(root);
  fclose(file);
  return EXIT_SUCCESS;
}

void user_interface(TrieNode *root) {

  TrieNode *current_word = root;
  char *input = (char *) malloc(MAX_WORD * sizeof(char));
  check_malloc(input);
  printf("Enter \"exit\" to quit.\n");
  while (1) {
    printf("Enter Key Sequence (or \"#\" for next word):\n>");
    fgets(input, MAX_WORD, stdin);
    input[strlen(input) - 1] = '\0';
    if (strstr(input, "exit")) {
      break;
    } else if (check_valid_code(input) == 0) {
      printf("Invalid T9 code\n");
      continue;
    }
    int pounds_count = 0;
    char *pounds = strstr(input, "#");
    if (pounds) {
      pounds_count = strlen(pounds);
    }
    input[strlen(input) - pounds_count] = '\0';

    if (strlen(input) != 0) {
      current_word = get_word_node(root, input);
      if (current_word == NULL || strlen(current_word->word) == 0) {
        printf("Not found in current dictionary.\n");
        continue;
      }
    }

    while (pounds_count > 0 && current_word != NULL) {
      current_word = current_word->children[10];
      pounds_count--;
    }

    if (current_word != NULL) {
      printf("%s\n", current_word->word);
    } else {
      printf("%s\n", "There are no more T9onyms");
    }
  }
  free(input);
}

void create_table(int *table) {
  int i = 2;
  int k = 0;
  while (i < 8) {
    for (int j = 0; j < 3; j++) {
      table[k] = i;
      k++;
    }
    i++;
  }
  table[k] = i - 1;
  k++;
  while (i < 10) {
    for (int j = 0; j < 3; j++) {
      table[k] = i;
      k++;
    }
    i++;
  }
  table[k] = 9;
}

void get_T9_code(char *word, char *code, int *table) {
  int invalid = 0;
  for (int i = 0; i < strlen(word); i++) {
    int index = ((int) word[i]) - 97;
    if (index < 0 || index > 25) {
      invalid = 1;
      break;
    }
    int code_number = table[index];
    code[i] = code_number + '0';
  }
  if (invalid) {
    code[0] = '\0';
  } else {
    code[strlen(word)] = '\0';
  }
}

int check_valid_code(char *code) {
  if (strlen(code) == 0) {
    return 0;
  }
  for (int i = 0; i < strlen(code); i++) {
    if (strchr(T9_CHARS, code[i]) == NULL) {
      return 0;
    }
  }
  return 1;
}