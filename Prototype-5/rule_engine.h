#ifndef RULE_ENGINE_H
#define RULE_ENGINE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// -------------------------
// Log Structure
// -------------------------
typedef struct {
    char question[128];
    char answer[128];
} QAEntry;

typedef struct {
    QAEntry entries[50];
    int count;
} LogContext;

void addLog(LogContext *log, const char *q, const char *a) {
    strcpy(log->entries[log->count].question, q);
    strcpy(log->entries[log->count].answer, a);
    log->count++;
}

// -------------------------
// Decision Tree Node
// -------------------------
typedef struct Node {
    char conditionName[128]; 
    char matchValue[32];     

    char recommendation[128];
    char reason[256];

    struct Node *children[10];
    int childCount;
} Node;

// Create a normal (condition) node
Node* createNode(const char *condition, const char *match) {
    Node *n = (Node*)malloc(sizeof(Node));
    strcpy(n->conditionName, condition);
    strcpy(n->matchValue, match);
    n->childCount = 0;
    n->recommendation[0] = '\0';
    n->reason[0] = '\0';
    return n;
}

// Create leaf node
Node* createLeaf(const char *match, const char *rec, const char *reason) {
    Node *n = createNode("", match);
    strcpy(n->recommendation, rec);
    strcpy(n->reason, reason);
    return n;
}

// Add child
void addChild(Node *parent, Node *child) {
    parent->children[parent->childCount++] = child;
}

// -------------------------
// Traversal
// -------------------------
Node* traverseTree(Node *root,
                   const char *dataSize,
                   const char *operation,
                   const char *order,
                   const char *priority,
                   LogContext *log)
{
    Node *current = root;

    while (current->childCount > 0) {
        const char *value = NULL;

        if (strcmp(current->conditionName, "dataSize") == 0) value = dataSize;
        else if (strcmp(current->conditionName, "operation") == 0) value = operation;
        else if (strcmp(current->conditionName, "order") == 0) value = order;
        else if (strcmp(current->conditionName, "priority") == 0) value = priority;

        addLog(log, current->conditionName, value);

        int found = 0;
        for (int i = 0; i < current->childCount; i++) {
            if (strcmp(current->children[i]->matchValue, value) == 0) {
                current = current->children[i];
                found = 1;
                break;
            }
        }

        if (!found) return NULL; 
    }

    return current;
}

// -------------------------
// Build the tree
// -------------------------
Node* buildDecisionTree() {
    Node *root = createNode("dataSize", "");

    // SMALL
    Node *small = createNode("operation", "small");
    addChild(root, small);

    addChild(small, createLeaf("insert", "Linked List", "Small data, insertion/deletion fast."));
    addChild(small, createLeaf("delete", "Linked List", "Small data, insertion/deletion fast."));
    addChild(small, createLeaf("search", "Array", "Sequential access is fast for small data."));
    addChild(small, createLeaf("sort", "Array", "Sorting is simple with small size."));

    // MEDIUM
    Node *medium = createNode("operation", "medium");
    addChild(root, medium);

    addChild(medium, createLeaf("search", "Binary Search Tree", "Good search performance."));
    addChild(medium, createLeaf("sort", "Heap", "Heap sort efficient for medium data."));
    addChild(medium, createLeaf("insert", "Linked List", "Balanced for moderate insert/delete."));
    addChild(medium, createLeaf("delete", "Linked List", "Balanced for moderate insert/delete."));

    // LARGE
    Node *large = createNode("priority", "large");
    addChild(root, large);

    // large → speed
    Node *speed = createNode("operation", "speed");
    addChild(large, speed);

    addChild(speed, createLeaf("search", "Hash Table", "Fastest average-case search."));

    Node *orderNode = createNode("order", "other");
    addChild(speed, orderNode);

    addChild(orderNode, createLeaf("yes", "Balanced Tree (AVL/RB)", "Maintains ordering."));
    addChild(orderNode, createLeaf("no", "Graph / Trie", "Efficient for unordered large data."));

    // large → space
    addChild(large, createLeaf("space", "Compressed Data Structures", "Memory optimized."));

    return root;
}

#endif
