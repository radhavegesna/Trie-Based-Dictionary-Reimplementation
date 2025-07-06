#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dict.h"

// Helper function to create a new Trie node
static trie_node *create_node() {
    trie_node *node = (trie_node *) malloc(sizeof(trie_node));
    if (node != NULL) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            node->children[i] = NULL;
        }
        node->is_terminal = 0;
        node->value = 0;
    }
    return node;
}

// Create an empty Dict (Trie)
Dict make_dict() {
    return (Dict) create_node();  // Root node of the Trie
}

// Free all memory allocated to the Trie (including keys)
void free_dict(Dict dict_adt) {
    trie_node *node = (trie_node *) dict_adt;
    if (node == NULL) {
        return;
    }

    // Recursively free all child nodes
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            free_dict((Dict) node->children[i]);
        }
    }

    // Free the current node
    free(node);
}

// Get the value associated with the key
int *get(Dict dict_adt, const char *key) {
    trie_node *node = (trie_node *) dict_adt;
    if (node == NULL) {
        return NULL;
    }

    // Traverse the Trie to find the key
    for (int i = 0; key[i] != '\0'; i++) {
        int index = key[i] - 'a';  // Convert char to index (0-25)
        if (node->children[index] == NULL) {
            return NULL;  // Key not found
        }
        node = node->children[index];
    }

    // Check if we have a valid key at the end of the Trie path
    if (node != NULL && node->is_terminal) {
        return &(node->value);  // Return a pointer to the value
    }

    return NULL;  // Key not found
}

// Set the value associated with the key
int set(Dict dict_adt, const char *key, int value) {
    trie_node *node = (trie_node *) dict_adt;
    if (node == NULL) {
        return 0;  // Failed to insert
    }

    // Traverse the Trie and insert nodes as needed
    for (int i = 0; key[i] != '\0'; i++) {
        int index = key[i] - 'a';  // Convert char to index (0-25)
        if (node->children[index] == NULL) {
            node->children[index] = create_node();  // Create a new node
            if (node->children[index] == NULL) {
                return 0;  // Failed to allocate memory
            }
        }
        node = node->children[index];
    }

    // Set the value and mark the node as terminal
    node->is_terminal = 1;
    node->value = value;
    return 1;  // Successfully inserted
}

// Print the Trie contents (for debugging)
void print_trie(trie_node *node, char *prefix, int length) {
    if (node->is_terminal) {
        prefix[length] = '\0';
        printf("%s: %d\n", prefix, node->value);
    }

    // Recursively print all child nodes
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            prefix[length] = 'a' + i;
            print_trie(node->children[i], prefix, length + 1);
        }
    }
}

// Print the contents of the dictionary
void print_dict(Dict dict_adt) {
    trie_node *root = (trie_node *) dict_adt;
    char prefix[MAX_KEY_LENGTH + 1];
    print_trie(root, prefix, 0);
}