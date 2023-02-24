#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    char *name;
    char *sex;
    char *age;
    char *height;
    char *weight;
    struct node *next;
} node;