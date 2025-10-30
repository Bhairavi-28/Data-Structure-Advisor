#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 20

// ---------- Hash Table for Explanations ----------
struct Rule {
    char key[20];
    char explanation[300];
};
struct Rule *hashTable[TABLE_SIZE];

int hashFunction(char *key) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) sum += key[i];
    return sum % TABLE_SIZE;
}

void insertRule(char *key, char *explanation) {
    int index = hashFunction(key);
    struct Rule *newRule = (struct Rule *)malloc(sizeof(struct Rule));
    strcpy(newRule->key, key);
    strcpy(newRule->explanation, explanation);
    hashTable[index] = newRule;
}

char *getExplanation(char *key) {
    int index = hashFunction(key);
    if (hashTable[index] != NULL && strcmp(hashTable[index]->key, key) == 0)
        return hashTable[index]->explanation;
    return "No detailed explanation found.";
}

// ---------- Decision Tree Structure ----------
struct Node {
    char question[200];
    char key[10]; // pattern used for hashing
    struct Node *yes;
    struct Node *no;
};

struct Node* createNode(char *question, char *key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->question, question);
    if (key != NULL) strcpy(newNode->key, key);
    else strcpy(newNode->key, "");
    newNode->yes = NULL;
    newNode->no = NULL;
    return newNode;
}

// ---------- Tree Traversal ----------
void traverse(struct Node *node, char *path) {
    if (node == NULL) return;

    if (node->yes == NULL && node->no == NULL) {
        printf("\nRecommendation: %s\n", node->question);
        printf("Reason: %s\n", getExplanation(path));
        return;
    }

    char answer;
    printf("\n%s (y/n): ", node->question);
    scanf(" %c", &answer);
    answer = tolower(answer);

    int len = strlen(path);
    path[len] = answer;
    path[len + 1] = '\0';

    if (answer == 'y')
        traverse(node->yes, path);
    else
        traverse(node->no, path);
}

void freeTree(struct Node *node) {
    if (node == NULL) return;
    freeTree(node->yes);
    freeTree(node->no);
    free(node);
}

// ---------- Main ----------
int main() {
    // 1. Insert explanations in hash table
    insertRule("yy", "Stack is ideal because you insert and remove from the same end (LIFO).");
    insertRule("yn", "Queue suits when order matters but operations happen at opposite ends (FIFO).");
    insertRule("ny", "Array allows random access when order is required but insertion/removal is predictable.");
    insertRule("nn", "Linked List is flexible for dynamic data where random access isn’t needed.");

    // 2. Build decision tree
    struct Node *root = createNode("Do you need your data in a specific order?", "");
    root->yes = createNode("Do you insert and remove from the same end?", "");
    root->no = createNode("Do you want random access?", "");

    root->yes->yes = createNode("Use a Stack (LIFO).", "yy");
    root->yes->no  = createNode("Use a Queue (FIFO).", "yn");
    root->no->yes  = createNode("Use an Array.", "ny");
    root->no->no   = createNode("Use a Linked List.", "nn");

    // 3. Start traversal
    char path[10] = "";
    traverse(root, path);

    // 4. Cleanup
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != NULL) free(hashTable[i]);
    }
    freeTree(root);

    return 0;
}
