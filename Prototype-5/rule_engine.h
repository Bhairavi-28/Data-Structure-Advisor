#ifndef RULE_ENGINE_H
#define RULE_ENGINE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Decision Tree Node Structure
typedef struct Node {
    char condition[50];        
    char value[50];            
    
    char recommendation[50];   
    char reason[200];          

    struct Node* yes;          
    struct Node* no;           
} Node;

// Create a node
Node* createNode(const char *condition, const char *value,
                 const char *recommendation, const char *reason) 
{
    Node* n = (Node*)malloc(sizeof(Node));
    strcpy(n->condition, condition);
    strcpy(n->value, value);

    if (recommendation) strcpy(n->recommendation, recommendation);
    else strcpy(n->recommendation, "");

    if (reason) strcpy(n->reason, reason);
    else strcpy(n->reason, "");

    n->yes = NULL;
    n->no = NULL;
    return n;
}

// Build the simple decision tree
Node* buildDecisionTree() 
{
    // Root: data size?
    Node* root = createNode("dataSize", "small", NULL, NULL);

    // SMALL →
    root->yes = createNode("operation", "insert", NULL, NULL);
        root->yes->yes = createNode("", "",
            "Linked List",
            "Small data → insertion/deletion is easy.");
        root->yes->no  = createNode("", "",
            "Array",
            "Small data → sequential access fast.");

    // MEDIUM & LARGE → handled in root->no
    root->no = createNode("dataSize", "medium", NULL, NULL);

    // MEDIUM →
    root->no->yes = createNode("operation", "search", NULL, NULL);
        root->no->yes->yes = createNode("", "",
            "Binary Search Tree",
            "Medium data → fast search.");
        root->no->yes->no  = createNode("operation", "sort", NULL, NULL);

    root->no->yes->no->yes = createNode("", "",
        "Heap", "Medium data → good for sorting.");
    root->no->yes->no->no = createNode("", "",
        "Linked List", "Moderate data → good for insertion/deletion.");

    // LARGE →
    root->no->no = createNode("priority", "speed", NULL, NULL);

    Node* largeSpeed = root->no->no->yes = createNode("operation", "search", NULL, NULL);
        largeSpeed->yes = createNode("", "",
            "Hash Table", "Large data → fastest search.");
        largeSpeed->no  = createNode("order", "yes", NULL, NULL);

    largeSpeed->no->yes = createNode("", "",
        "Balanced Tree (AVL)",
        "Large data → ordered + fast.");
    largeSpeed->no->no = createNode("", "",
        "Graph / Trie",
        "Large structured data.");

    root->no->no->no = createNode("", "",
        "Compressed Data Structures",
        "Large data → optimized for memory.");

    return root;
}

// DFS Traversal
void dfs(Node* node)
{
    if (!node) return;

    if (strlen(node->recommendation) > 0)
        printf("Leaf → %s : %s\n", node->recommendation, node->reason);
    else
        printf("Condition → %s == %s ?\n", node->condition, node->value);

    dfs(node->yes);
    dfs(node->no);
}

// Evaluate the decision tree
void evaluate(Node* node, char dataSize[], char operation[],
              char order[], char priority[],
              char recommendation[], char reason[]) 
{
    if (!node) return;

    // Leaf reached
    if (strlen(node->recommendation) > 0) {
        strcpy(recommendation, node->recommendation);
        strcpy(reason, node->reason);
        return;
    }

    // Compare based on node->condition
    char* inputValue;

    if (strcmp(node->condition, "dataSize") == 0) inputValue = dataSize;
    else if (strcmp(node->condition, "operation") == 0) inputValue = operation;
    else if (strcmp(node->condition, "order") == 0) inputValue = order;
    else if (strcmp(node->condition, "priority") == 0) inputValue = priority;
    else return;

    // Follow yes/no based on match
    if (strcmp(inputValue, node->value) == 0)
        evaluate(node->yes, dataSize, operation, order, priority, recommendation, reason);
    else
        evaluate(node->no, dataSize, operation, order, priority, recommendation, reason);
}

#endif
