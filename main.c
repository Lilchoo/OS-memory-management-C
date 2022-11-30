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
    Node* temp = malloc(sizeof(char) * 20);
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

        if(head->limit == NULL) {
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

void runProgram(int option) {
    int readStatus = 0;
    FILE *fptr;
    Node *head = malloc(sizeof(Node));
//    Node *temp;
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
//                    temp = head;
//                    while (temp != NULL) {
//                        printf("Node %d: %s, Index: %d, Size: %d\n", num, temp->name, temp->base, temp->limit);
//                        temp = temp->next;
//                    }
                    readStatus = 1;
                } else {
                    printf("File already loaded.");
                }
                break;
            case 2:
                printf("merge holes");
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