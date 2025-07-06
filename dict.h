#ifndef DICT_H
#define DICT_H

#include "dict_adt.h"

#define ALPHABET_SIZE 26  // Only lowercase English letters

typedef struct trie_node {
    struct trie_node *children[ALPHABET_SIZE];  // One for each letter 'a' to 'z'
    int is_terminal;  // 1 if this node represents the end of a valid key
    int value;        // The integer value associated with the key
} trie_node;

#endif