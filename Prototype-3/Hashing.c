#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 10

//Structure to hold rule mapping 
struct Rule {
    char key[10];
    char recommendation[200];
};

struct Rule *hashTable[TABLE_SIZE];

int hashFunction(char *key) {
    int sum = 0;
    for (int i=0; key[i]!='\0'; i++)
        sum += key[i];
    return sum % TABLE_SIZE;
}

void insertRule(char *key, char *recommendation) {
    int index = hashFunction(key);
    struct Rule *newRule = (struct Rule *)malloc(sizeof(struct Rule));
    strcpy(newRule->key, key);
    strcpy(newRule->recommendation, recommendation);
    hashTable[index] = newRule;
}

char *getRecommendation(char *key) {
    int index = hashFunction(key);
    if(hashTable[index] != NULL && strcmp(hashTable[index]->key, key)==0)
        return hashTable[index]->recommendation;
    return "No matching rule found.";
}

int main() {
    insertRule("yy", "Use a Stack (LIFO)");
    insertRule("yn", "Use a Queue (FIFO)");
    insertRule("ny", "Use an Array");
    insertRule("nn", "Use a Linked List");

    char a1, a2;
    printf("Do you need your data in a specific order? (y/n)");
    scanf("%c", &a1);
    printf("Do you insert and remove from the sma end? (y/n)");
    scanf("%c", &a2);

    char key[10];
    key[0] = tolower(a1);
    key[1] = tolower(a2);
    key[2] = '\0';

    printf("\nRecommendation: %s \n", getRecommendation(key));

    for(int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != NULL)
            free(hashTable[i]);
    }

    return 0;
    
}