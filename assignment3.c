#include "file_handler.h"
#include "sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Runs the program to display main menu to read input file, merge memory holes,
 * compact memory, print current memory view, and exit program.
 * @param option is the selected option as an int between 1-5
 */
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

/*
 * Runs the program.
 */
int main(int argc, char **argv) {

    int option = selectOption();
    runProgram(option);
    return 0;

}