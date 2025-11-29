#include <stdio.h>

#include "input.h"
#include "output.h"
#include "rule_engine.h"

int main() {
    char dataSize[10], operation[20], order[10], priority[10];

    LogContext log;
    log.count = 0;

    printf("\n====== DATA STRUCTURE ADVISOR ======\n");

    getInput(dataSize, operation, order, priority);

    Node *root = buildDecisionTree();
    Node *leaf = traverseTree(root, dataSize, operation, order, priority, &log);

    if (leaf != NULL)
        showOutput(leaf->recommendation, leaf->reason);
    else
        printf("\nNo matching rule found!\n");

    return 0;
}