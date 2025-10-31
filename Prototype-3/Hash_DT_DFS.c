#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 20
#define MAX_STACK 100

//Hash Table for Explanations
struct Rule {
    char key[10];
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
    return "No detailed explanation found for this path.";
}

//Decision Tree
struct Node {
    char question[200];
    char key[10];
    struct Node *yes;
    struct Node *no;
};

struct Node* createNode(char *question, char *key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); // ✅ Fixed
    strcpy(newNode->question, question);
    if (key != NULL)
        strcpy(newNode->key, key);
    else
        strcpy(newNode->key, "");
    newNode->yes = NULL;
    newNode->no = NULL;
    return newNode;
}

// ---------- DFS Stack ----------
typedef struct {
    struct Node *node;
    char path[10];
} StackFrame;

StackFrame stack[MAX_STACK];
int top = -1;

void push(struct Node *node, char *path) {
    if (top >= MAX_STACK - 1) {
        printf("Stack overflow!\n");
        return;
    }
    top++;
    stack[top].node = node;
    strcpy(stack[top].path, path);
}

StackFrame pop() {
    StackFrame empty = {NULL, ""};
    if (top < 0) return empty;
    return stack[top--];
}

// ---------- DFS Traversal ----------
void dfsTraversal(struct Node *root) {
    char path[10] = "";
    push(root, path);

    while (top >= 0) {
        StackFrame frame = pop();
        struct Node *current = frame.node;

        if (current == NULL) continue;

        if (current->yes == NULL && current->no == NULL) {
            printf("\nRecommendation: %s\n", current->question);
            printf("Reason: %s\n", getExplanation(frame.path));
            continue;
        }

        char answer;
        printf("\n%s (y/n): ", current->question);
        scanf(" %c", &answer);
        answer = tolower(answer);

        while (answer != 'y' && answer != 'n') {
            printf("Please enter 'y' or 'n': ");
            scanf(" %c", &answer);
            answer = tolower(answer);
        }

        char newPath[10];
        strcpy(newPath, frame.path);
        int len = strlen(newPath);
        newPath[len] = answer;
        newPath[len + 1] = '\0';

        if (answer == 'y')
            push(current->yes, newPath);
        else
            push(current->no, newPath);
    }
}

// ---------- Cleanup ----------
void freeTree(struct Node *node) {
    if (node == NULL) return;
    freeTree(node->yes);
    freeTree(node->no);
    free(node);
}

// ---------- Main ----------
int main() {
    // Initialize hash table with explanations
    insertRule("yy", "Stack is suitable when operations follow LIFO — last in, first out.");
    insertRule("yn", "Queue fits FIFO patterns where elements are processed in order.");
    insertRule("ny", "Array offers direct random access when order is needed but operations are predictable.");
    insertRule("nn", "Linked List is ideal for dynamic data with flexible insertion and no random access.");

    // Build decision tree
    struct Node *root = createNode("Do you need your data in a specific order?", "");
    root->yes = createNode("Do you insert and remove from the same end?", "");
    root->no = createNode("Do you want random access?", "");

    root->yes->yes = createNode("Use a Stack (LIFO).", "yy");
    root->yes->no  = createNode("Use a Queue (FIFO).", "yn");
    root->no->yes  = createNode("Use an Array.", "ny");
    root->no->no   = createNode("Use a Linked List.", "nn");

    printf("\n=== DS Advisor: Prototype 3 (Hash + DFS + Tree) ===\n");
    dfsTraversal(root);

    // Free memory
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != NULL) free(hashTable[i]);
    }
    freeTree(root);

    return 0;
}
