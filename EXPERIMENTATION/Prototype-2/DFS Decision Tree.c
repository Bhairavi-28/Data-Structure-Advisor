#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_QA 100

//decision tree node
struct Node {
    char question[200];
    struct Node* yes;
    struct Node* no;
};

//stack for DFS
typedef struct {
    char question[200];
    char answer; //y or n
} QnA;

QnA stack[100];
int top = -1;

void pushQnA(char* question, char answer) {
    if(top<MAX_QA-1) {
        strcpy(stack[++top].question, question);
        stack[top].answer = answer;
    }
}

//create new node
struct Node* createNode(char* question) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if(newNode==NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(newNode->question, question);

    newNode->yes = NULL;
    newNode->no = NULL;

    return newNode;
}

void traverse(struct Node* node){
    if(node==NULL)  return;
    if(node->yes==NULL && node->no==NULL) {
        printf("Recommendation: %s\n", node->question);

        printf("\nDecision Path: \n");
        for (int i = 0; i <= top; i++)
            printf("%d. %s: %c\n", i+1, stack[i].question, stack[i].answer);
        return;
    }

    char answer;
    int valid=0;

    while(!valid) {
        printf("\n%s (y/n): ", node->question);
        scanf(" %c", &answer);

        if(answer=='y'||answer=='Y'||answer=='n'||answer=='N')
            valid=1;
        else
            printf("Invalid input. Please enter 'y' or 'n'.\n");

    }

    pushQnA(node->question, answer);

    if(answer=='y'||answer=='n')    traverse(node->yes);
    else    traverse(node->no);
}

void freeTree(struct Node* node) {
    if(node==NULL)  return;
    freeTree(node->yes);
    freeTree(node->no);
    free(node);
}

int main() {
    struct Node* root = createNode("Do you need your data in a specific order? ");
    root->yes = createNode("Do you insert and remove from the same end? ");
    root->no = createNode("Do you want random access? ");

    root->yes->yes = createNode("Use a Stack (LIFO).");
    root->yes->no = createNode("Use a Queue (FIFO).");

    root->no->yes = createNode("Use an Array.");
    root->no->no = createNode("Use a Linked List.");

    traverse(root);
    freeTree(root);

    return 0;
}