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

void processHash(Block *block, int difficulty)
{
    block->nonce = 0;
    do {
        ++block->nonce;
        char hash[HASH_DIGEST_SIZE + 1] = "";
        blockHash(block, hash);
        strcpy(block->hash, hash);
    } while (!blockValidate(block, difficulty));
}

void toString(void *data, size_t size, char* dest)
{
    assert(data != NULL && size > 0);
    memcpy(dest, data, size);
}

void blockToString(Block *block, char* str)
{
    const char* separator = ":";

    char timestamp[32];
    sprintf(timestamp, "%lu", block->timestamp);

    char nonce[INT32_MAX % 10];
    sprintf(nonce, "%d", block->nonce);

    char data[block->size];
    if (block->data != NULL && block->size > 0) {
        toString(block->data, block->size, data);
    }

    strcpy(str, timestamp);
    strcat(str, separator);
    strcat(str, block->previousHash);
    strcat(str, separator);
    strcat(str, block->data != NULL && block->size > 0 ? data : "NULL");
    strcat(str, separator);
    strcat(str, nonce);
}

int blockValidate(Block *block, int difficulty)
{
    assert(difficulty < HASH_DIGEST_SIZE);
    for (int i = 0 ; i < difficulty ; ++i)
        if (block->hash[i] != '0')
            return 0;
    return 1;
}

void blockchainInit(Blockchain *blockchain, int difficulty)
{
    // Initialize blockchain
    blockchain->n = 1;
    blockchain->blocks = (Block *) malloc(sizeof(Block) * 2);
    blockchain->difficulty = difficulty;

    // Create genesis block
    Block genesis = {
            .timestamp = time(NULL),
            .data = NULL,
            .size = 0,
            .previousHash = "",
            .hash = "",
            .nonce = 0
    };
    processHash(&genesis, blockchain->difficulty);

    // Add the genesis block to the blockchain
    blockchain->blocks[0] = genesis;
}

void blockchainAddBlock(Blockchain *blockchain, Block *block)
{
    strcpy(block->previousHash, blockchain->blocks[blockchain->n - 1].hash);
    char hash[HASH_DIGEST_SIZE + 1] = "";
    blockHash(block, hash);
    processHash(block, blockchain->difficulty);
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

int blockchainValidate(Blockchain *blockchain)
{
    for (int i = 0 ; i < blockchain->n ; ++i) {
        Block *block = &blockchain->blocks[i];

        // All block hashes must be valid
        if (!blockValidate(block, blockchain->difficulty)) {
            return 0;
        }

        // Each block hash correspond the block calculated hash
        char hash[HASH_DIGEST_SIZE + 1] = "";
        blockHash(block, hash);
        if (strcmp(block->hash, hash) != 0) {
            return 0;
        }

        // All blocks, except the genesis block must point to the previous block
        if (i > 0 && strcmp(block->previousHash, blockchain->blocks[i-1].hash) != 0) {
            return 0;
        }

    }
    return 1;
}

void blockchainDestroy(Blockchain *blockchain)
{
    free(blockchain->blocks);
}
