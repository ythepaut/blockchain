/**
 * Simple linked list implementation
 *
 * @author      Yohann THEPAUT (ythepaut) <contact@ythepaut.com>
 * @license     GNU GPL v3.0
 * @see         https://github.com/ythepaut/blockchain
 */

#ifndef BLOCKCHAIN_LINKEDLIST_H
#define BLOCKCHAIN_LINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct SElement;

/**
 * Element definition
 */
typedef struct SElement {
    void *value;
    struct SElement *next;
} Element;

typedef struct {
    Element *head;
    int size;
} LinkedList;

/**
 * Create an element
 * @param value         void*           (in)        Element value
 */
Element *createElement(void *value);

/**
 * Initializes the linked list
 * @param linkedList    LinkedList*     (in-out)    Linked list to initialize
 */
void linkedListInit(LinkedList *linkedList);

/**
 * Gets the i-th element of the linked list
 * @param linkedList    LinkedList*     (in)        Linked list to browse
 * @param i             int             (in)        Element index
 * @return Pointer to the i-th element of the list
 */
Element *linkedListGet(LinkedList *linkedList, int i);

/**
 * Gets the index of an element in the linked list
 * @param linkedList    LinkedList*     (in)        Linked list to browse
 * @param element       Element*        (in)        Element to search
 * @return index of the element in the linked list, -1 if not in the list
 */
int linkedListGetIndex(LinkedList *linkedList, Element *element);

/**
 * Adds an element to the linked list
 * @param linkedList    LinkedList*     (in-out)    Linked list to modify
 * @param element       Element*        (in)        Element to add
 * @param i             int             (in)        Index to insert the element
 */
void linkedListAdd(LinkedList *linkedList, Element *element, int i);

/**
 * Removes an element from the linked list
 * @param linkedList    LinkedList*     (in-out)    Linked list to modify
 * @param i             int             (in)        Index of the element to remove
 */
void linkedListRemove(LinkedList *linkedList, int i);

/**
 * Displays the linked list elements
 * @param linkedList    LinkedList*     (in)        Linked list to display
 */
void linkedListDisplay(LinkedList *linkedList);

/**
 * Frees the linked list's allocated memory
 * @param linkedList    LinkedList*     (in-out)    Linked list to destroy
 */
void linkedListDestroy(LinkedList *linkedList);

#endif //BLOCKCHAIN_LINKEDLIST_H
