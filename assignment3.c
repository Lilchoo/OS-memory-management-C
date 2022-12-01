#include "file_handler.h"
#include "sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



//typedef struct Node {
//    char name[10];
//    int base;
//    int limit;
//    struct Node* next;
//} Node;

//int selectOption() {
//    int option = 0;
//    printf("1) load an input\n2) merge holes\n"
//           "3) compact memory\n4) print memory view\n"
//           "5) Exit the program\n");
//    scanf("%d", &option);
//    fflush(stdin);
//    return option;
//}

/**
 * Merge Sort
 * @param source
 * @param frontRef
 * @param backRef
 */
//void FrontBackSplit(struct Node *source,
//                    struct Node **frontRef, struct Node **backRef) {
//    struct Node *fast;
//    struct Node *slow;
//    slow = source;
//    fast = source->next;
//
//    /* Advance 'fast' two nodes, and advance 'slow' one node */
//    while (fast != NULL) {
//        fast = fast->next;
//        if (fast != NULL) {
//            slow = slow->next;
//            fast = fast->next;
//        }
//    }
//
//    /* 'slow' is before the midpoint in the list, so split it in two
//    at that point. */
//    *frontRef = source;
//    *backRef = slow->next;
//    slow->next = NULL;
//}

/**
 * Compares and sorts two void nodes based on their data types.
 * (a-z for chars, largest to smallest for numerical values)
 */
//struct Node *SortedMerge(struct Node *a, struct Node *b) {
//    struct Node *head = malloc(sizeof(Node *));
//    struct Node *temp = head;
//    while (a != NULL && b != NULL) {
//        /* Pick either a or b */
//        if (a->base < b->base) {
//            temp->next = a;
//            a = a->next;
//        } else {
//            temp->next = b;
//            b = b->next;
//        }
//        temp = temp->next;
//    }
//    if (a != NULL) {
//        temp->next = a;
//    }
//    if (b != NULL) {
//        temp->next = b;
//    }
//    return head->next;
//}

/**
 * Sorts the void node linked list based on their data types.
 */
//void nodeSort(struct Node **headRef) {
//    struct Node *head = *headRef;
//    struct Node *a;
//    struct Node *b;
//    /* Base case -- length 0 or 1 */
//    if ((head == NULL) || (head->next == NULL)) {
//        return;
//    }
//
//    FrontBackSplit(head, &a, &b);
//
//    nodeSort(&a);
//    nodeSort(&b);
//
//    *headRef = SortedMerge(a, b);
//}

/**
 * Read Input
 * @param fp
 * @param head
 * @return
 */
//Node* readInput(FILE* fp, Node* head) {
//    Node* temp;
//    int nodeNum = 1;
//    char* str = malloc(sizeof(char) * 20);
//    while(fgets(str, 20, fp) != NULL && !isspace(*str)) {
//        if (*str == 'n') {
//            continue;
//        }
//        Node* newNode = malloc(sizeof(Node));
//        char* token = strtok(str, " ");
//        for (int i = 1; i < strlen(token); i++) {
//            if (token[0] != 'P' && token[0] != 'H' || isdigit(token[i]) == 0) {
//                printf("Node %d has incorrect name.", nodeNum);
//                exit(1);
//            }
//        }
//        strcpy(newNode -> name, token);
//
//        token = strtok(NULL, " ");
//        for (int i = 0; i < strlen(token); i++) {
//            if (isdigit(token[i]) == 0) {
//                printf("Node %d has invalid base.", nodeNum);
//                exit(1);
//            }
//        }
//        newNode -> base = atoi(token);
//
//        token = strtok(NULL, " \n");
//        for (int i = 0; i < strlen(token); i++) {
//            if (isdigit(token[i]) == 0) {
//                printf("Node %d has invalid limit.", nodeNum);
//                exit(1);
//            }
//        }
//        newNode->limit = atoi(token);
//        newNode -> next = 0;
//
//        if(head == NULL) {
//            head = newNode;
//            temp = newNode;
//        } else {
//            temp->next = newNode;
//            temp = newNode;
//        }
//        nodeNum++;
//    }
//    return head;
//}

//FILE* readFile() {
//    printf("Enter the file name: ");
//    char* fileName = malloc(sizeof(20));
//    scanf("%s", fileName);
//    FILE *fptr = fopen(fileName, "r");
//    return fptr;
//}

//void printMemory(Node* node) {
//    int number = 1;
//    while (node != NULL) {
//        printf("Node %d: %s, base = %d, limit = %d\n", number, node->name, node->base, node->limit);
//        node = node -> next;
//        number++;
//    }
//}

//Node* mergeHoles(Node* head) {
//    Node* temp = head;
//    Node* last = NULL;
//    Node* newHole;
//    int newLimit = 0;
//
//    while (temp != NULL) {
//
//        if (temp->name[0] == 'H') {
//            newHole = temp;
//
//            while (temp != NULL && temp->name[0] == 'H') {
//                newLimit += temp->limit;
//                temp = temp->next;
//            }
//            newHole->limit = newLimit;
//            newLimit = 0;
//
//            if (last != NULL) {
//                last->next = newHole;
//            }
//            newHole->next = temp;
//        }
//        if (temp != NULL) {
//            last = temp;
//            temp = temp->next;
//        }
//    }
//    return head;
//}


//Node* compaction(Node* head) {
//    Node* temp = head;
//    Node* last;
//    Node* nextNode;
//    int holeLimit = 0;
//    int numP = 0;
//    int numPCount = 0;
//
//    while(temp != NULL) {
//        if(temp -> name[0] == 'H') {
//            holeLimit += temp -> limit;
//        } else {
//            numP++;
//        }
//        temp = temp -> next;
//    }
//
//    temp = head;
//    numPCount = numP;
//
//    while(temp != NULL) {
//        if(temp -> name[0] != 'H' && numP == numPCount) {
//            last = temp;
//            head = last;
//            last -> base = 0;
//            numP--;
//        } else if(temp -> name[0] != 'H' && numP > 0) {
//            nextNode = temp;
//            nextNode->base = last->base + last->limit;
//            last->next = nextNode;
//            last = nextNode;
//            numP--;
//        }
//        temp = temp -> next;
//    }
//    Node* hole = malloc(sizeof(Node));
//    hole -> name[0] = 'H';
//    hole -> base = last ->base + last -> limit;
//    hole -> limit = holeLimit;
//    hole -> next = NULL;
//    last -> next = hole;
//
//    return head;
//}

void runProgram(int option) {
    int readStatus = 0;
    FILE *fptr;
    Node *head = NULL;
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
//                    checkData(head);
                    nodeSort(&head);
                    readStatus = 1;
                } else {
                    printf("File already loaded.");
                }
                break;
            case 2:
                printf("merge holes\n");
                head = mergeHoles(head);
                break;
            case 3:
                printf("compact memory\n");
                head = compaction(head);
                break;
            case 4:
                if (readStatus == 0) {
                    printf("No data inserted yet");
                    continue;
                } else {
                    printf("print memory view\n");
                    printMemory(head);
                }
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
//    Node* head = malloc(sizeof(Node));
    runProgram(option);
    return 0;

}