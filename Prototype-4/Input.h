#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>

void getInput(char dataSize[], char operation[], char order[], char priority[]) 
{
    printf("Enter approximate data size (small / medium / large): ");
    scanf("%s", dataSize);

    printf("Main operation? (insert / delete / search / sort / access): ");
    scanf("%s", operation);

    printf("Need elements in specific order? (yes / no): ");
    scanf("%s", order);

    printf("Priority? (speed / space): ");
    scanf("%s", priority);
}

#endif 