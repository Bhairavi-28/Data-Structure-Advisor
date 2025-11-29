#include <stdio.h>
#include "input.h"
#include "rule_engine.h"
#include "output.h"

int main()
{
    char dataSize[10], operation[20], order[5], priority[10];
    char recommendation[50], reason[200];

    printf("\n====== DATA STRUCTURE ADVISOR ======\n\n");

    getInput(dataSize, operation, order, priority);
    Node* tree = buildDecisionTree();
    evaluate(tree, dataSize, operation, order, priority, recommendation, reason);
    showOutput(recommendation, reason);

    printf("\n--- Decision Tree DFS Traversal ---\n");
    dfs(tree);

    return 0;
}
