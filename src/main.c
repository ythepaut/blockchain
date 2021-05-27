/**
 * Blockchain test program
 *
 * @author      Yohann THEPAUT (ythepaut) <contact@ythepaut.com>
 * @license     GNU GPL v3.0
 * @see         https://github.com/ythepaut/blockchain
 */

#include <stdio.h>
#include "blockchain.h"

void test() {

    Blockchain blockchain;

    blockchainInit(&blockchain);

    char data[] = "bonjour";
    Block block = {
            .timestamp = 0,
            .data = (void *) &data,
            .size = sizeof(char) * (strlen(data) + 1),
            .previousHash = NULL,
            .hash = ""
    };

    char str[MAX_BLOCK_DESCRIPTION_SIZE + block.size];
    blockToString(&block, str);
    char hash[65] = "";
    blockHash(&block, hash);
    printf("Block desc : %s\n", str);
    printf("Block hash : %s\n", hash);

    blockchainDisplay(&blockchain);

    blockchainAddBlock(&blockchain, &block);

    blockchainDisplay(&blockchain);

    blockchainAddBlock(&blockchain, &block);

    blockchainDisplay(&blockchain);

    blockchainDestroy(&blockchain);
}

int main() {

    test();

    return 0;
}
