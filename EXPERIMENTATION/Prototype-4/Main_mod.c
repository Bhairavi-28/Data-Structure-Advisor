#include <stdio.h>
#include "Input.h"
#include "Rule_Engine.h"
#include "Output.h"

int main()
{
    char dataSize[10], operation[20], order[5], priority[10], recommendation[50], reason[200];
    printf("\n");
    printf("======DATA STRUCTURE ADVISOR (demo)=====\n");
    getInput(dataSize, operation, order, priority);
    decisionDS(dataSize, operation, order, priority, recommendation, reason);
    showOutput(recommendation, reason);
    
    return 0;
}