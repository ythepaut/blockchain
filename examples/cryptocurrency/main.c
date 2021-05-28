/**
 * Cryptocurrency test program
 *
 * @author      Yohann THEPAUT (ythepaut) <contact@ythepaut.com>
 * @license     GNU GPL v3.0
 * @see         https://github.com/ythepaut/blockchain
 */

#include "cryptocurrency.h"
#include "../../src/util/linkedlist.h"

int main() {

    LinkedList linkedList;
    linkedListInit(&linkedList);

    linkedListAdd(&linkedList, createElement("test0"), linkedList.size);
    linkedListAdd(&linkedList, createElement("test1"), linkedList.size);
    linkedListAdd(&linkedList, createElement("test2"), linkedList.size);
    linkedListAdd(&linkedList, createElement("test3"), linkedList.size);
    linkedListAdd(&linkedList, createElement("test4"), linkedList.size);
    linkedListAdd(&linkedList, createElement("testX"), 2);
    linkedListRemove(&linkedList, 2);

    linkedListDisplay(&linkedList);

    linkedListDestroy(&linkedList);

    return 0;
}
