/**
 * Blockchain test program
 *
 * @author      Yohann THEPAUT (ythepaut) <contact@ythepaut.com>
 * @license     GNU GPL v3.0
 * @see         https://github.com/ythepaut/blockchain
 */

#include <stdio.h>
#include <time.h>
#include "blockchain.h"

void test() {

    Blockchain blockchain;
    blockchainInit(&blockchain, 4);

    // Add a first block
    char data1[] = "bonjour";
    Block block = {
            .timestamp = time(NULL),
            .data = (void *) &data1,
            .size = sizeof(char) * (strlen(data1) + 1),
            .previousHash = "",
            .hash = "",
            .nonce = 0
    };
    blockchainAddBlock(&blockchain, &block);

    // Add a second block
    char data2[] = "bonsoir";
    block.data = (void *) &data2;
    block.size = sizeof(char) * (strlen(data2) + 1),
            block.timestamp = time(NULL);
    blockchainAddBlock(&blockchain, &block);

    blockchainDisplay(&blockchain);

    assert(blockchainValidate(&blockchain));

    printf("Tampering with the blockchain :\n");

    blockchain.blocks[1].data = "salut";        // Modify block data
    //blockchain.blocks[2].previousHash = "af4d85fd8d23b3c07366ae29c0e3a85b7d5c82f6edb4a6c11e20d88b9f7e19b6";     // Modify block link
    blockchainDisplay(&blockchain);
    assert(blockchainValidate(&blockchain) == 0);

    blockchainDestroy(&blockchain);
}

int main() {

    test();

    return 0;
}
