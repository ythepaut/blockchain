/**
 * Blockchain
 *
 * @author      Yohann THEPAUT (ythepaut) <contact@ythepaut.com>
 * @license     GNU GPL v3.0
 * @see         https://github.com/ythepaut/blockchain
 */

#ifndef BLOCKCHAIN_BLOCKCHAIN_H
#define BLOCKCHAIN_BLOCKCHAIN_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "openssl/sha.h"
#include <assert.h>
#include <time.h>
#include <pthread.h>

#define MAX_BLOCK_DESCRIPTION_SIZE sizeof(Block)
#define HASH_DIGEST_SIZE 64

/**
 * Block type
 */
typedef struct {
    time_t timestamp;
    void *data;
    size_t size;
    char previousHash[HASH_DIGEST_SIZE + 1];
    char hash[HASH_DIGEST_SIZE + 1];
    int nonce;
} Block;

/**
 * Blockchain type
 */
typedef struct {
    Block *blocks;
    int n;
    int difficulty;
} Blockchain;

/**
 * Block mining parameters (used for the multi-threading)
 */
typedef struct {
    Block block;
    int difficulty;
    int threadCount;
    int offset;
    pthread_t *threads;
    Block *result;
} MinerParams;

/**
 * Generates the block's hash
 * @param block         block*          (in)        Block to get the hash from
 * @param hash          char*           (out)       Block hash
 */
void blockHash(Block *block, char *hash);

/**
 * Thread : Calculates the hash until it begins with n zeros, where n is the difficulty
 * @param params        MinerParams*    (in-out)    Parameters to mine the block
 */
void processHash(MinerParams *params);

/**
 * Proof of work algorithm : Process the hash on multiple threads
 * @param block         block*          (in-out)    Block to mine
 * @param difficulty    int             (in)        Mining difficulty
 * @param threadCount   int             (in)        Number of threads to launch
 */
void mineBlock(Block *block, int difficulty, int threadCount);

/**
 * Generates a string based on the block's data.
 * @param block         block*          (in)        Block to get the description from
 * @param str           char*           (out)       Block as string
 */
void blockToString(Block *block, char *str);

/**
 * Verifies if a block is valid.
 * @param block         block*          (in)        Block to validate
 * @param difficulty    int             (in)        Difficulty (i.e. number of tailing zeros in the hash)
 * @return True (1) if block is valid, False (0) otherwise
 */
int blockValidate(Block *block, int difficulty);

/**
 * Initializes the blockchain
 * @param blockchain    Blockchain*     (in-out)    Blockchain to initialize
 * @param difficulty    int             (in)        Mining difficulty
 * @param threadCount   int             (in)        Number of thread used to mine the genesis block
 */
void blockchainInit(Blockchain *blockchain, int difficulty, int threadCount);

/**
 * Add a block to the blockchain
 * @param blockchain    Blockchain*     (in-out)    Blockchain to modify
 * @param block         Block*          (in-out)    Block to add
 * @param threadCount   int             (in)        Number of thread used to mine the block
 */
void blockchainAddBlock(Blockchain *blockchain, Block *block, int threadCount);

/**
 * Prints all blocks
 * @param blockchain    Blockchain*     (in)        Blockchain to display
 */
void blockchainDisplay(Blockchain *blockchain);

/**
 * Verifies if the blockchain is valid
 * @param blockchain    Blockchain*     (in)        Blockchain to validate
 * @return True (1) if blockchain is valid, False (0) if it has been tampered with
 */
int blockchainValidate(Blockchain *blockchain);

/**
 * Frees the blockchain's allocated memory
 * @param blockchain    Blockchain*     (in-out)    Blockchain to destroy
 */
void blockchainDestroy(Blockchain *blockchain);

#endif //BLOCKCHAIN_BLOCKCHAIN_H
