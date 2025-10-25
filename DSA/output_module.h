#ifndef OUTPUT_MODULE_H
#define OUTPUT_MODULE_H

#include <stdio.h>

void showOutput(char recommendation[], char reason[])
{
    printf("\n");

    printf("\n=== Data Structure Recommendation ===\n");
    printf("Based on your input, we recommend the following:\n");
    printf("Data Structure: %c\n", recommendation);
    printf("Reason: %s\n", reason);
    printf("Thank you for using our DS Advisor Demo system!\n");

    printf("\n\n\n");

}

#endif