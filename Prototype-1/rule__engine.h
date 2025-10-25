#ifndef RULE__ENGINE_H
#define RULE__ENGINE_H

#include <stdio.h>
#include <string.h>

typedef enum
{
    PARAM_DATA_SIZE,
    PARAM_OPERATION,
    PARAM_ORDER,
    PARAM_PRIORITY,
    PARAM_NONE
} ParameterType;

typedef struct DecisionNode
{
    ParameterType check_param; 
    const char *compare_value;
    const char *recommendation;
    const char *reason;
    struct DecisionNode *next_true;
    struct DecisionNode *next_false;
} DecisionNode;

void decisionDS_Tree(const char dataSize[], const char operation[], const char order[], const char priority[], char recommendation[], char reason[], const DecisionNode *root)
{
    const DecisionNode *current_node = root;
    const char *param_value = '\0';
    int condition_met = 0;

    while(current_node && current_node->check_param != PARAM_NONE)
    {
        switch(current_node->check_param) {
            case PARAM_DATA_SIZE:
                param_value = dataSize;
                break;
            case PARAM_OPERATION:
                param_value = operation;
                break;
            case PARAM_ORDER:
                param_value = order;
                break;
            case PARAM_PRIORITY:
                param_value = priority;
                break;
            case PARAM_NONE:
                break;
        }
        if (param_value && current_node->compare_value) 
            condition_met = (strcmp(param_value, current_node->compare_value) == 0);
        else 
            condition_met = 0;
    }
}

#endif