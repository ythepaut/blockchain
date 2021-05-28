/**
 * Blockchain usage example : Cryptocurrency
 *
 * @author      Yohann THEPAUT (ythepaut) <contact@ythepaut.com>
 * @license     GNU GPL v3.0
 * @see         https://github.com/ythepaut/blockchain
 */

#ifndef BLOCKCHAIN_CRYPTOCURRENCY_H
#define BLOCKCHAIN_CRYPTOCURRENCY_H

#include "../../src/blockchain.h"
#include "../../src/util/linkedlist.h"

#define ECOIN_MINING_DIFFICULTY 3
#define ECOIN_MINING_REWARD 0.01

/**
 * Transaction type
 */
typedef struct {
    char *from;
    char *to;
    double amount;
} Transaction;

/**
 * Cryptocurrency (Ecoin)
 */
typedef struct {
    Blockchain blockchain;
    LinkedList pendingTransactions;
    double miningReward;
} Ecoin;

/**
 * Initializes the Ecoin
 * @param ecoin         Ecoin*          (in-out)    Ecoin to initialize
 */
void ecoinInit(Ecoin *ecoin);

/**
 * Adds a pending transaction to the Ecoin
 * @param ecoin         Ecoin*          (in-out)    Ecoin to add the transaction to
 * @param transaction   Transaction*    (in)        Transaction to add
 */
void ecoinAddPendingTransaction(Ecoin *ecoin, Transaction *transaction);

/**
 * Mine new transaction to add to the blockchain
 * @param ecoin         Ecoin*          (in-out)    Ecoin currency
 * @param minerAddress  char*           (in)        Mining reward address
 */
void minePendingTransactions(Ecoin *ecoin, char *minerAddress);

#endif //BLOCKCHAIN_CRYPTOCURRENCY_H
