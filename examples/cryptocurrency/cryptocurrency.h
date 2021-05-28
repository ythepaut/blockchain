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

#define ECOIN_MINING_DIFFICULTY 5
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
 * Create a transaction
 * @param amount        double          (in)        Amount to send
 * @param from          char*           (in)        From address
 * @param to            char*           (in)        To address
 * @return Created transaction
 */
Transaction *ecoinCreateTransaction(double amount, char* from, char* to);

/**
 * Mine new transaction to add to the blockchain
 * @param ecoin         Ecoin*          (in-out)    Ecoin currency
 * @param minerAddress  char*           (in)        Mining reward address
 */
void minePendingTransactions(Ecoin *ecoin, char *minerAddress);

/**
 * Displays transactions from a list (e.g. block, pending transactions)
 * @param list          LinkedList*     (in)        Linked list that contains transactions
 */
void ecoinDisplayTransactionFromList(LinkedList *list);

/**
 * Frees the ecoin's allocated memory
 * @param ecoin         Ecoin*          (in-out)    Ecoin to destroy
 */
void ecoinDestroy(Ecoin *ecoin);

#endif //BLOCKCHAIN_CRYPTOCURRENCY_H
