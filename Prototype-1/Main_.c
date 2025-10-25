#include <stdio.h>
#include <string.h>

// ===== Input Function =====
void getInput(char dataSize[], char operation[], char order[], char priority[]) {
    printf("=== DATA STRUCTURE ADVISOR (Demo) ===\n\n");

    printf("Enter approximate data size (small / medium / large): ");
    scanf("%s", dataSize);

    printf("Main operation? (insert / delete / search / sort / access): ");
    scanf("%s", operation);

    printf("Need elements in specific order? (yes / no): ");
    scanf("%s", order);

    printf("Priority? (speed / space): ");
    scanf("%s", priority);
}

// ===== Rule Engine =====
void decideDS(char dataSize[], char operation[], char order[], char priority[],
              char recommendation[], char reason[]) {

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
    else {
        strcpy(recommendation, "Unknown");
        strcpy(reason, "Invalid data size entered.");
    }
}

// ===== Output Function =====
void showOutput(char recommendation[], char reason[]) {
    printf("\n--- Recommendation ---\n");
    printf("Data Structure: %s\n", recommendation);
    printf("Reason: %s\n", reason);
    printf("\nThank you for using DS Advisor Demo!\n");
}

// ===== Main =====
int main() {
    char dataSize[10], operation[20], order[5], priority[10];
    char recommendation[50], reason[200];

    getInput(dataSize, operation, order, priority);
    decideDS(dataSize, operation, order, priority, recommendation, reason);
    showOutput(recommendation, reason);

    return 0;
}