#include "file_handler.h"
#include "sort.h"

int selectOption() {
    int option = 0;
    printf("1) load an input\n2) merge holes\n"
           "3) compact memory\n4) print memory view\n"
           "5) Exit the program\n");
    scanf("%d", &option);
    fflush(stdin);
    return option;
}

/**
 * Read Input
 * @param fp
 * @param head
 * @return
 */
Node* readInput(FILE* fp, Node* head) {
    Node* temp;
    Node* last;
    int nodeNum = 1;
    char* str = malloc(sizeof(char) * 20);
    while(fgets(str, 20, fp) != NULL) {
        if (*str == '\n') {
            continue;
        }
        Node* newNode = malloc(sizeof(Node));
        char* token = strtok(str, " ");
        for (int i = 0; i < strlen(token); i++) {
            if (token[0] != 'P' && token[0] != 'H') {
                printf("Node %d has incorrect name.", nodeNum);
                exit(1);
            }
            if (i > 0) {
                if (isdigit(token[i]) == 0 || token[0] == 'H') {
                    printf("Node %d has incorrect name.", nodeNum);
                    exit(1);
                }
            }
        }
        strcpy(newNode -> name, token);

        token = strtok(NULL, " ");
        for (int i = 0; i < strlen(token); i++) {
            if (isdigit(token[i]) == 0) {
                printf("Node %d has invalid base.", nodeNum);
                exit(1);
            }
        }
        newNode -> base = atoi(token);

        token = strtok(NULL, " \n");
        for (int i = 0; i < strlen(token); i++) {
            if (isdigit(token[i]) == 0) {
                printf("Node %d has invalid limit.", nodeNum);
                exit(1);
            }
        }
        newNode->limit = atoi(token);
        newNode -> next = 0;

        if(head == NULL) {
            head = newNode;
            temp = newNode;
        } else {
            last = temp;
            if (newNode->base != last->base + last->limit) {
                printf("Overlapping memory.");
                exit(1);
            }
            temp->next = newNode;
            temp = newNode;
        }
        nodeNum++;
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

Node* mergeHoles(Node* head) {
    Node* temp = head;
    Node* last = NULL;
    Node* newHole;
    int newLimit = 0;

    while (temp != NULL) {

        if (temp->name[0] == 'H') {
            newHole = temp;

            while (temp != NULL && temp->name[0] == 'H') {
                newLimit += temp->limit;
                temp = temp->next;
            }
            newHole->limit = newLimit;
            newLimit = 0;

            if (last != NULL) {
                last->next = newHole;
            }
            newHole->next = temp;
        }
        if (temp != NULL) {
            last = temp;
            temp = temp->next;
        }
    }
    return head;
}

Node* compaction(Node* head) {
    Node* temp = head;
    Node* last;
    Node* nextNode;
    int holeLimit = 0;
    int numP = 0;
    int numPCount = 0;

    while(temp != NULL) {
        if(temp -> name[0] == 'H') {
            holeLimit += temp -> limit;
        } else {
            numP++;
        }
        temp = temp -> next;
    }

    temp = head;
    numPCount = numP;

    while(temp != NULL) {
        if(temp -> name[0] != 'H' && numP == numPCount) {
            last = temp;
            head = last;
            last -> base = 0;
            numP--;
        } else if(temp -> name[0] != 'H' && numP > 0) {
            nextNode = temp;
            nextNode->base = last->base + last->limit;
            last->next = nextNode;
            last = nextNode;
            numP--;
        }
        temp = temp -> next;
    }
    Node* hole = malloc(sizeof(Node));
    hole -> name[0] = 'H';
    hole -> base = last ->base + last -> limit;
    hole -> limit = holeLimit;
    hole -> next = NULL;
    last -> next = hole;

    return head;
}
