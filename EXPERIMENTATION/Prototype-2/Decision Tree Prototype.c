#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node {
    char question[200];
    struct Node* yes;
    struct Node* no;
    
};

struct Node* createNode(char* question) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->question, question);

    newNode->yes = NULL;
    newNode->no = NULL;

    return newNode;
}

void traverse(struct Node* node) {
    if(node==NULL)  return;

    if(node->yes==NULL && node->no==NULL) {
        printf("\n %s\n", node->question);
        return;
    }

    char answer;
    printf("\n%s (y/n): ", node->question);
    scanf(" %c", &answer);

    if(answer=='y' || answer=='Y')
        traverse(node->yes);
    else
        traverse(node->no);
}

int main() {
    struct Node* root = createNode("Do you need your data in a specific order? ");
    root->yes = createNode("Do you insert and remove from the same end? ");
    root->no = createNode("Do you want random access? ");

    root->yes->yes = createNode("Use a Stack (LIFO).");
    root->yes->no = createNode("Use a Queue (FIFO).");

    root->no->yes = createNode("Use an Array.");
    root->no->no = createNode("Use a Linked List.");

    printf("=====DATA STRUCTURE ADVISOR=====");
    traverse(root);

    return 0;
}