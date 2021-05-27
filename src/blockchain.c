/**
 * Blockchain
 *
 * @author      Yohann THEPAUT (ythepaut) <contact@ythepaut.com>
 * @license     GNU GPL v3.0
 * @see         https://github.com/ythepaut/blockchain
 */

#include "blockchain.h"

void blockHash(Block *block, char *hash)
{
    char blockStr[MAX_BLOCK_DESCRIPTION_SIZE + block->size + 1];
    blockToString(block, blockStr);

    unsigned char *d = SHA256((const unsigned char*) blockStr, strlen(blockStr), 0);

    char currentByte[3];
    sprintf(currentByte, "%02x", d[0]);
    strcpy(hash, currentByte);
    for (int i = 1 ; i < SHA256_DIGEST_LENGTH ; ++i) {
        sprintf(currentByte, "%02x", d[i]);
        strcat(hash, currentByte);
    }
}

void toString(void *data, size_t size, char* dest)
{
    assert(data != NULL && size > 0);
    memcpy(dest, data, size);
}

void blockToString(Block *block, char* str)
{
    const char* separator = ":";

    char timestamp[11];
    sprintf(timestamp, "%010d", block->timestamp);

    char data[block->size];
    if (block->data != NULL && block->size > 0) {
        toString(block->data, block->size, data);
    }

    strcpy(str, timestamp);
    strcat(str, separator);
    strcat(str, block->previousHash != NULL ? block->previousHash : "NULL");
    strcat(str, separator);
    strcat(str, block->data != NULL && block->size > 0 ? data : "NULL");
}

void blockchainInit(Blockchain *blockchain)
{
    // Initialize blockchain
    blockchain->n = 1;
    blockchain->blocks = (Block *) malloc(sizeof(Block) * 2);

    // Create genesis block
    Block genesis = {
            .timestamp = 0,
            .data = NULL,
            .size = 0,
            .previousHash = NULL,
            .hash = ""
    };
    char hash[HASH_DIGEST_SIZE + 1] = "";
    blockHash(&genesis, hash);
    strcpy(genesis.hash, hash);

    // Add the genesis block to the blockchain
    blockchain->blocks[0] = genesis;
}

void blockchainAddBlock(Blockchain *blockchain, Block *block)
{
    block->previousHash = blockchain->blocks[blockchain->n - 1].hash;
    char hash[HASH_DIGEST_SIZE + 1] = "";
    blockHash(block, hash);
    strcpy(block->hash, hash);
    blockchain->blocks = (Block *) realloc(blockchain->blocks, ++blockchain->n * sizeof(Block));
    blockchain->blocks[blockchain->n - 1] = *block;
}

void blockchainDisplay(Blockchain *blockchain)
{
    for (int i = 0 ; i < blockchain->n ; ++i) {
        Block *block = &blockchain->blocks[i];
        char str[MAX_BLOCK_DESCRIPTION_SIZE + block->size];
        blockToString(block, str);
        printf("%04d\t%s\t%s\n", i, block->hash, str);
    }
}

void blockchainDestroy(Blockchain *blockchain)
{
    free(blockchain->blocks);
}
