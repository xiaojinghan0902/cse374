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

// Function to create a Trie data structure by reading words from a file
Trie* createTrie(char* file);

// Function to start the interactive session with the user
void startIOSession(Trie* root);

int main(int argc, char* argv[]) {
    // Check if the correct number of command line arguments was provided
    if (argc != 2) {
        fprintf(stderr, "Two arguments are required.\n");
        exit(1);
    }

    // Get the file name from the command line argument
    char* file = argv[1];

    // Create the Trie data structure using the provided file
    Trie* root = createTrie(file);

    // If the Trie was successfully created, start the interactive session
    if (root != NULL) {
        startIOSession(root);

        // Free the memory allocated for the Trie
        freeMem(root);
    }

    return 0;
}

// Function to create a Trie data structure by reading words from a file
Trie* createTrie(char* file) {
    Trie* root;
    char line[MAX_LENGTH];
    char* buffer;

    // Open the file for reading
    FILE* f = fopen(file, "r");
    if (f == NULL) {
        fprintf(stderr, "File: %s was not found:\n", file);
        return NULL;
    } else {
        // Create the root node of the Trie
        root = createNode(NULL);

        // Read each line from the file and insert it into the Trie
        while (fgets(line, MAX_LENGTH, f)) {
            // Allocate memory for the buffer and copy the line into it
            buffer = malloc(sizeof(char) * (strlen(line) + 1));
            strncpy(buffer, line, sizeof(char) * (strlen(line) + 1));

            // Insert the buffer (word) into the Trie
            insert(root, buffer);
        }
    }

    // Close the file
    fclose(f);

    return root;
}

// Function to start the interactive session with the user
void startIOSession(Trie* root) {
    char stdin[MAX_LENGTH + 1];
    char prev[MAX_LENGTH + 1];

    // Display initial instructions to the user
    printf("Enter \"exit\" to quit.\n");
    printf("Enter Key Sequence (or \"#\" for next word):\n");
    printf("> ");

    // Read user input
    scanf("%s", stdin);

    // Continue the interactive session until the user enters "exit"
    while (strcmp(stdin, "exit") != 0) {
        if (strncmp(stdin, "#", 1) == 0) {
            // User entered a number sequence starting with "#"
            // Append "#" to the previous input and search for the corresponding word
            int len = sizeof(prev + strlen(prev));
            snprintf(prev + strlen(prev), len + 1, "#");
            printf("        %s", search(root, prev));
        } else {
            // User entered a number sequence
            // Search for the corresponding word and update the previous input
            printf("        %s", search(root, stdin));
            snprintf(prev, strlen(stdin) + 1, "%s", stdin);
        }

        // Prompt the user for the next input
        printf("Enter Key Sequence (or \"#\" for next word):\n");
        printf("> ");

        // Read user input
        scanf("%s", stdin);
    }
}
