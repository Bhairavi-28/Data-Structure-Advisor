#ifndef RULE_ENGINE_H
#define RULE_ENGINE_H

#include <stdio.h>
#include <string.h>

void decisionDS(char dataSize[], char operation[], char order[], char priority[], char recommendation[], char reason[]) 
{

    if (strcmp(dataSize, "small") == 0) {
        if (strcmp(operation, "insert") == 0 || strcmp(operation, "delete") == 0) {
            strcpy(recommendation, "Linked List");
            strcpy(reason, "Small data, easy insertion/deletion without shifting elements.");
        } else {
            strcpy(recommendation, "Array");
            strcpy(reason, "Small data, sequential access is fast.");
        }
    } 

    else if (strcmp(dataSize, "medium") == 0) {
        if (strcmp(operation, "search") == 0) {
            strcpy(recommendation, "Binary Search Tree");
            strcpy(reason, "Moderate data, faster search than linear structures.");
        } else if (strcmp(operation, "sort") == 0) {
            strcpy(recommendation, "Heap");
            strcpy(reason, "Heap efficiently supports sorting medium datasets.");
        } else {
            strcpy(recommendation, "Linked List");
            strcpy(reason, "Balanced choice for moderate data insertion/deletion.");
        }
    } 

    else if (strcmp(dataSize, "large") == 0) {
        if (strcmp(priority, "speed") == 0) {
            if (strcmp(operation, "search") == 0)
                strcpy(recommendation, "Hash Table");
            else if (strcmp(order, "yes") == 0)
                strcpy(recommendation, "Balanced Tree (AVL/Red-Black)");
            else
                strcpy(recommendation, "Graph / Trie");
        } else {
            strcpy(recommendation, "Compressed Data Structures");
        }
        strcpy(reason, "Large data, optimized for performance or memory depending on priority.");
    } 

    else 
    {
        strcpy(recommendation, "Unknown");
        strcpy(reason, "Invalid data size entered.");
    }
    
}

#endif