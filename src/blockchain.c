/**
 * Blockchain
 *
 * @author      Yohann THEPAUT (ythepaut) <contact@ythepaut.com>
 * @license     GNU GPL v3.0
 * @see         https://github.com/ythepaut/blockchain
 */

#include "blockchain.h"

void blockHash(Block *block, char *hash) {
    char blockStr[MAX_BLOCK_DESCRIPTION_SIZE + block->size + 1];
    blockToString(block, blockStr);

    unsigned char *d = SHA256((const unsigned char *) blockStr, strlen(blockStr), 0);

    char currentByte[3];
    sprintf(currentByte, "%02x", d[0]);
    strcpy(hash, currentByte);
    for (int i = 1; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(currentByte, "%02x", d[i]);
        strcat(hash, currentByte);
    }
}

void processHash(MinerParams *params) {
    Block *block = &params->block;
    const int difficulty = params->difficulty;
    const int threadCount = params->threadCount;
    const int offset = params->offset;

    // Loop while hash doesn't start with enough zeros
    block->nonce = offset - threadCount;
    do {
        block->nonce += threadCount;
        char hash[HASH_DIGEST_SIZE + 1] = "";
        blockHash(block, hash);
        strcpy(block->hash, hash);

        char str2[200];
        blockToString(block, str2);
        printf("[Thread %d]: %s   %s\n", offset, str2, block->hash);
    } while (!blockValidate(block, difficulty) && params->result->nonce == -1);

    // Setting return parameter
    if (blockValidate(block, difficulty)) {
        *params->result = *block;

        char tmp[200];
        blockToString(block, tmp);
        printf("\n[Thread %d]: FOUND ! nonce=%d, hash=%s, toStr=%s\n", offset, block->nonce, block->hash, tmp);
    }
}

void mineBlock(Block *block, int difficulty, int threadCount) {
    pthread_t threads[threadCount];
    block->nonce = -1;

    // Setting up thread parameters
    MinerParams params[threadCount];
    for (int i = 0; i < threadCount; ++i) {
        MinerParams param = {
                .block = *block,
                .difficulty = difficulty,
                .threadCount = threadCount,
                .offset = i,
                .threads = threads,
                .result = block
        };
        params[i] = param;
    }

    // Creating the threads
    for (int i = 0; i < threadCount; ++i)
        pthread_create(&threads[i], NULL, (void *) processHash, (void *) &params[i]);

    // Wait for the threads to finish
    for (int i = 0; i < threadCount; ++i)
        pthread_join(threads[i], NULL);
}

void blockToString(Block *block, char *str) {
    const char *separator = ":";

    char timestamp[32];
    sprintf(timestamp, "%lu", block->timestamp);

    char nonce[INT32_MAX % 10];
    sprintf(nonce, "%d", block->nonce);

    strcpy(str, timestamp);
    strcat(str, separator);
    strcat(str, block->previousHash);
    strcat(str, separator);
    strcat(str, (block->data != NULL) ? (char *) block->data : "NULL");
    strcat(str, separator);
    strcat(str, nonce);
}

int blockValidate(Block *block, int difficulty) {
    assert(difficulty < HASH_DIGEST_SIZE);
    for (int i = 0; i < difficulty; ++i)
        if (block->hash[i] != '0')
            return 0;
    return 1;
}

void blockchainInit(Blockchain *blockchain, int difficulty, int threadCount) {
    // Initialize blockchain
    blockchain->n = 1;
    blockchain->blocks = (Block *) malloc(sizeof(Block) * 2);
    blockchain->difficulty = difficulty;

    // Create genesis block
    Block genesis = {
            .timestamp = time(NULL),
            .data = NULL,
            .size = 0,
            .previousHash = "0000000000000000000000000000000000000000000000000000000000000000",
            .hash = "",
            .nonce = 0
    };
    mineBlock(&genesis, blockchain->difficulty, threadCount);

    // Add the genesis block to the blockchain
    blockchain->blocks[0] = genesis;
}

void blockchainAddBlock(Blockchain *blockchain, Block *block, int threadCount) {
    strcpy(block->previousHash, blockchain->blocks[blockchain->n - 1].hash);
    mineBlock(block, blockchain->difficulty, threadCount);
    blockchain->blocks = (Block *) realloc(blockchain->blocks, ++blockchain->n * sizeof(Block));
    blockchain->blocks[blockchain->n - 1] = *block;
}

void blockchainDisplay(Blockchain *blockchain) {
    printf("No.\tHash\t\t\t\t\t\t\t\t\tPrev. hash\t\t\t\t\t\t\t\tNonce\t\tData\n");
    for (int i = 0; i < blockchain->n; ++i) {
        Block *block = &blockchain->blocks[i];
        printf("%04d\t%s\t%s\t%d\t\t%s\n", i, block->hash, block->previousHash, block->nonce,
               (block->data != NULL) ? (char *) block->data : "NULL");
    }
}

int blockchainValidate(Blockchain *blockchain) {
    for (int i = 0; i < blockchain->n; ++i) {
        Block *block = &blockchain->blocks[i];

        // All block hashes must be valid
        if (!blockValidate(block, blockchain->difficulty)) {
            printf("1\n");
            return 0;
        }

        // Each block hash correspond the block calculated hash
        char hash[HASH_DIGEST_SIZE + 1] = "";
        blockHash(block, hash);
        if (strcmp(block->hash, hash) != 0) {
            printf("2 : %s != %s\n", block->hash, hash);
            return 0;
        }

        // All blocks, except the genesis block must point to the previous block
        if (i > 0 && strcmp(block->previousHash, blockchain->blocks[i - 1].hash) != 0) {
            printf("3\n");
            return 0;
        }

    }
    return 1;
}

void blockchainDestroy(Blockchain *blockchain) {
    for (int i = 0; i < blockchain->n; ++i)
        free(blockchain->blocks[i].data);
    free(blockchain->blocks);
}
