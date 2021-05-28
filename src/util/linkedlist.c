/**
 * Simple linked list implementation
 *
 * @author      Yohann THEPAUT (ythepaut) <contact@ythepaut.com>
 * @license     GNU GPL v3.0
 * @see         https://github.com/ythepaut/blockchain
 */

#include "linkedlist.h"

Element *createElement(void *value) {
    Element *element = (Element *) malloc(sizeof(Element));
    element->value = value;
    element->next = NULL;
    return element;
}

void linkedListInit(LinkedList *linkedList) {
    linkedList->size = 0;
    linkedList->head = NULL;
}

Element *linkedListGet(LinkedList *linkedList, int i) {
    assert(linkedList->size > i);
    Element *current = linkedList->head;
    for (int j = 0 ; j < i ; ++j)
        current = current->next;
    return current;
}

int linkedListGetIndex(LinkedList *linkedList, Element *element) {
    int result = 0;
    Element *current = linkedList->head;
    while (current != NULL && current != element)
        ++result;
    return result < linkedList->size ? result : -1;
}

void linkedListAdd(LinkedList *linkedList, Element *element, int i) {
    assert(i >= 0);
    if (i > 0) {
        Element *previous = linkedListGet(linkedList, i - 1);
        element->next = previous->next;
        previous->next = element;
    } else {
        element->next =linkedList->head;
        linkedList->head = element;
    }
    ++linkedList->size;
}

void linkedListRemove(LinkedList *linkedList, int i) {
    assert(i >= 0);
    if (i > 0) {
        Element *previous = linkedListGet(linkedList, i - 1);
        Element *toFree = previous->next;
        previous->next = previous->next->next;
        free(toFree);
    } else {
        linkedList->head = linkedList->head->next;
    }
    --linkedList->size;
}

void linkedListDisplay(LinkedList *linkedList) {
    Element *current = linkedList->head;
    while (current != NULL) {
        printf("%s\n", (char *) current->value);
        current = current->next;
    }
}

void linkedListDestroy(LinkedList *linkedList) {
    Element *previous;
    Element *current = linkedList->head;
    while (current != NULL) {
        previous = current;
        free(previous);
        current = current->next;
    }
}
