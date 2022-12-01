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
int selectOption() {
    int option = 0;
    printf("1) load an input\n2) merge holes\n"
           "3) compact memory\n4) print memory view\n"
           "5) Exit the program\n");
    scanf("%d", &option);
    fflush(stdin);
    return option;
}

Node* readInput(FILE* fp, Node* head) {
    Node* temp;
    char* str = malloc(sizeof(char) * 20);
    while(fgets(str, 20, fp) != NULL && !isspace(*str)) {
        Node* newNode = malloc(sizeof(Node));
        char* token = strtok(str, " ");
        strcpy(newNode -> name, token);

        token = strtok(NULL, " ");
        newNode -> base = atoi(token);

        token = strtok(NULL, " ");
        newNode->limit = atoi(token);
        newNode -> next = 0;

        if(head == NULL) {
            head = newNode;
            temp = newNode;
        } else {
            temp->next = newNode;
            temp = newNode;
        }
    }
    return head;
}

FILE* readFile() {
    printf("Enter the file name: ");
    char* fileName = malloc(sizeof(20));
    scanf("%s", fileName);
    FILE *fptr = fopen(fileName, "r");
    return fptr;
}

void printMemory (Node* node) {
    int number = 1;
    while (node != NULL) {
        printf("Node %d: %s, base = %d, limit = %d\n", number, node->name, node->base, node->limit);
        node = node -> next;
        number++;
    }
}

/*
 * if(H)
 *  ptr1 = H;
 *  Holecount++;
 *
 *
 *  while(temp->next == H)
 *     ptr2 = H;
 *     limitsum += ptr2 -> limit
 *
 *
 */

Node* mergeHoles(Node* head) {
    Node* temp = head;
    Node* last;
    Node* newHole;
    int newLimit = 0;
    while (temp != NULL) {
        if (temp->name[0] == 'H') {
            newHole = temp;
            while (temp->name[0] == "H") {
                newLimit += temp->limit;
                temp = temp->next;
            }
            newHole->limit = newLimit;
            newLimit = 0;
            last->next = newHole;
            newHole->next = temp;
        }
        last = temp;
        temp = temp->next;
    }
}

/*
 * Compaction sort
 *
 * lets assume mergeHole is completed.
 * Therefore - P1 H P17 H
 *
 * make a new linkedlist and only insert if is not H
 *
 * two option - a pointer to all individual holes
 * or a hole struct that contains all hole data
 *
 *
 *
 *
 */





void runProgram(int option) {
    int readStatus = 0;
    FILE *fptr;
    Node *head = NULL;
    Node *temp;
    int num = 1;
    while(1) {
        switch(option) {
            case 1:
                if (readStatus == 0 ) {
                    fptr = readFile();
                    if (fptr == NULL) {
                        printf("File not entered.\n");
                        continue;
                    }
                    head = readInput(fptr, head);
                    nodeSort(&head);
                    temp = head;
                    while (temp != NULL) {
                        printf("Node %d: %s, Index: %d, Size: %d\n", num, temp->name, temp->base, temp->limit);
                        temp = temp->next;
                    }
                    readStatus = 1;
                } else {
                    printf("File already loaded.");
                }
                break;
            case 2:
                printf("merge holes");
                head = mergeHoles(head);
//                temp = head;
//                while (temp != NULL) {
//                    printf("Node %d: %s, Index: %d, Size: %d\n", num, temp->name, temp->base, temp->limit);
//                    temp = temp->next;
//                    num++;
//                }
                break;
            case 3:
                printf("compact memory");
                break;
            case 4:
                printf("print memory view");
                break;
            case 5:
                printf("Exit program");
                exit(0);
            default:
                printf("Not a valid option.");
        }
        printf("\n");
        option = selectOption();
    }

}

int main(int argc, char **argv) {

    int option = selectOption();
    Node* head = malloc(sizeof(Node));
    runProgram(option);
    return 0;

}