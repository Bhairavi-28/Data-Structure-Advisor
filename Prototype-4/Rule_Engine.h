#ifndef RULE_ENGINE_H
#define RULE_ENGINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*hash table*/
#define TABLE_SIZE 101

struct Rule {
    char key[50];
    char explanation[300];
};
struct Rule *hashTable[TABLE_SIZE];

int hashFunction(const char *key) {
    int hash = 0;
    for (int i = 0; key[i]; i++)
        hash += key[i];
    return hash % TABLE_SIZE;
}

void insertRule(const char *key, const char *explanation) {
    int index = hashFunction(key);
    struct Rule *entry = (struct Rule *)malloc(sizeof(struct Rule));
    strcpy(entry->key, key);
    strcpy(entry->explanation, explanation);
    hashTable[index] = entry;
}

char *getExplanation(const char *key) {
    int index = hashFunction(key);
    if (hashTable[index] && strcmp(hashTable[index]->key, key) == 0)
        return hashTable[index]->explanation;
    return "No specific explanation found.";
}

/*decision tree*/
struct Node {
    char key[50];
    char recommendation[100];
    struct Node *yes;
    struct Node *no;
};

struct Node *createNode(const char *key, const char *recommendation) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node)); // ✅ Fixed
    strcpy(node->key, key);
    strcpy(node->recommendation, recommendation);
    node->yes = node->no = NULL;
    return node;
}



struct Node *buildDecisionTree() {
    struct Node *root = createNode("root", "");

    // small
    struct Node *small = createNode("small", "");
    struct Node *small_insert = createNode("small-insert", "Linked List");
    struct Node *small_delete = createNode("small-delete", "Linked List");
    struct Node *small_search = createNode("small-search", "Array");
    struct Node *small_sort   = createNode("small-sort", "Array");

    small->yes = small_insert;
    small_insert->no = small_delete;
    small_delete->no = small_search;
    small_search->no = small_sort;

    // medium
    struct Node *medium = createNode("medium", "");
    struct Node *med_search = createNode("medium-search", "Binary Search Tree");
    struct Node *med_sort   = createNode("medium-sort", "Heap");
    struct Node *med_other  = createNode("medium-other", "Linked List");

    medium->yes = med_search;
    med_search->no = med_sort;
    med_sort->no = med_other;

    // large
    struct Node *large = createNode("large", "");
    struct Node *large_speed = createNode("large-speed", "");
    struct Node *large_space = createNode("large-space", "Compressed Data Structures");

    struct Node *large_speed_search   = createNode("large-speed-search", "Hash Table");
    struct Node *large_speed_order_yes = createNode("large-speed-order-yes", "Balanced Tree (AVL/Red-Black)");
    struct Node *large_speed_order_no  = createNode("large-speed-order-no", "Graph / Trie");

    large_speed->yes = large_speed_search;
    large_speed_search->no = large_speed_order_yes;
    large_speed_order_yes->no = large_speed_order_no;

    large->yes = large_speed;
    large_speed->no = large_space;

    // linking all
    root->yes = small;
    small->no = medium;
    medium->no = large;

    return root;
}

/*DFS*/
void dfsFind(struct Node *node, const char *targetKey, char *recommendation, char *foundKey) {
    if (!node) return;

    if (strcmp(node->key, targetKey) == 0) {
        strcpy(recommendation, node->recommendation);
        strcpy(foundKey, node->key);
        return;
    }

    dfsFind(node->yes, targetKey, recommendation, foundKey);
    dfsFind(node->no, targetKey, recommendation, foundKey);
}

/*Rule engine start*/

void decisionDS(char dataSize[], char operation[], char order[], char priority[],
                char recommendation[], char reason[]) {
    //Build Decision Tree
    struct Node *root = buildDecisionTree();

    //adding to Hash Table (Reason Database)
    insertRule("small-insert", "Linked List suits frequent inserts for small datasets.");
    insertRule("small-delete", "Linked List allows O(1) deletions without shifting.");
    insertRule("small-search", "Array provides direct sequential access for small data.");
    insertRule("small-sort", "Array works well when sorting small datasets.");

    insertRule("medium-search", "Binary Search Tree improves search time for medium data.");
    insertRule("medium-sort", "Heap efficiently handles sorting and priority queues.");
    insertRule("medium-other", "Linked List balances performance for mixed operations.");

    insertRule("large-speed-search", "Hash Table ensures O(1) lookups for large datasets.");
    insertRule("large-speed-order-yes", "Balanced Trees maintain sorted data efficiently.");
    insertRule("large-speed-order-no", "Graph or Trie suits large, unstructured relationships.");
    insertRule("large-space", "Compressed Data Structures minimize memory for large-scale storage.");

    //Generating key based on onput
    char key[100] = "";
    strcat(key, dataSize);
    strcat(key, "-");
    strcat(key, priority);
    strcat(key, "-");
    strcat(key, operation);

    if (strcmp(dataSize, "large") == 0 && strcmp(priority, "speed") == 0 &&
        strcmp(operation, "search") != 0) {
        strcat(key, "-order-");
        strcat(key, order);
    }

    //DFS Decision Tree search
    char foundKey[100] = "";
    dfsFind(root, key, recommendation, foundKey);

    //Default & Reason
    if (strlen(recommendation) == 0) {
        strcpy(recommendation, "Linked List");
        strcpy(reason, "No exact match found. Defaulted to a flexible linear structure.");
    } else {
        strcpy(reason, getExplanation(foundKey));
    }
}

#endif
