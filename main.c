#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char name[10];
    int base;
    int limit;
    struct Node* next;

};
int selectOption() {
    int option = 0;
    printf("1) load an input\n2) merge holes\n"
           "3) compact memory\n4) print memory view\n"
           "5) Exit the program");
    scanf("%d", &option);
    fflush(stdin);
    return option;
}

int main(int argc, char **argv) {

    int option = selectOption();

    while (1) {
        switch(option) {
            case 1:
                printf("load an input");
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






    return 0;
}