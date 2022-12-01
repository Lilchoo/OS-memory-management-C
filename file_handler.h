#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char name[10];
    int base;
    int limit;
    struct Node* next;
} Node;

int selectOption();
Node* readInput(FILE* fp, Node* head);
FILE* readFile();
void printMemory(Node* node);
Node* mergeHoles(Node* head);
Node* compaction(Node* head);
