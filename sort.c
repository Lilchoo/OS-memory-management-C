#include "file_handler.h"
#include "sort.h"

/**
 * Merge Sort
 * @param source
 * @param frontRef
 * @param backRef
 */
void FrontBackSplit(struct Node *source,
                    struct Node **frontRef, struct Node **backRef) {
    struct Node *fast;
    struct Node *slow;
    slow = source;
    fast = source->next;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

/**
 * Compares and sorts two void nodes based on their data types.
 * (a-z for chars, largest to smallest for numerical values)
 */
struct Node *SortedMerge(struct Node *a, struct Node *b) {
    struct Node *head = malloc(sizeof(Node *));
    struct Node *temp = head;
    while (a != NULL && b != NULL) {
        /* Pick either a or b */
        if (a->base < b->base) {
            temp->next = a;
            a = a->next;
        } else {
            temp->next = b;
            b = b->next;
        }
        temp = temp->next;
    }
    if (a != NULL) {
        temp->next = a;
    }
    if (b != NULL) {
        temp->next = b;
    }
    return head->next;
}

//Node* check(Node* head) {
//    Node* temp = head;
//    int index = 0;
//    while(temp != NULL) {
//        index +=
//    }
//}
/**
 * Sorts the void node linked list based on their data types.
 */
void nodeSort(struct Node **headRef) {
    struct Node *head = *headRef;
    struct Node *a;
    struct Node *b;
    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    FrontBackSplit(head, &a, &b);

    nodeSort(&a);
    nodeSort(&b);

    *headRef = SortedMerge(a, b);
}
