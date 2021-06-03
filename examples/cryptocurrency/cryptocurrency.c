/**
 * Blockchain usage example : Cryptocurrency
 *
 * @author      Yohann THEPAUT (ythepaut) <contact@ythepaut.com>
 * @license     GNU GPL v3.0
 * @see         https://github.com/ythepaut/blockchain
 */

#include "cryptocurrency.h"

void ecoinInit(Ecoin *ecoin) {
    blockchainInit(&ecoin->blockchain, ECOIN_MINING_DIFFICULTY);
    linkedListInit(&ecoin->pendingTransactions);
    ecoin->miningReward = ECOIN_MINING_REWARD;
}

void ecoinAddPendingTransaction(Ecoin *ecoin, Transaction *transaction) {
    linkedListAdd(&ecoin->pendingTransactions, createElement(transaction), ecoin->pendingTransactions.size);
}

Transaction *ecoinCreateTransaction(double amount, char* from, char* to) {
    Transaction *transaction = malloc(sizeof(Transaction));
    transaction->amount = amount;
    transaction->from = from;
    transaction->to = to;
    return transaction;
}

void minePendingTransactions(Ecoin *ecoin, char *minerAddress) {
    // Create a block from all pending transactions
    Block block = {
            .timestamp = time(NULL),
            .data = (void *) &ecoin->pendingTransactions,
            .size = sizeof(ecoin->pendingTransactions),
            .previousHash = "",
            .hash = "",
            .nonce = 0
    };
    blockchainAddBlock(&ecoin->blockchain, &block);

    // Reset the transaction list
    LinkedList linkedList;
    linkedListInit(&linkedList);
    ecoin->pendingTransactions = linkedList;

    // Add a transaction for the mining reward
    Transaction *reward = ecoinCreateTransaction(ECOIN_MINING_REWARD, "00000000000000000000000000000000", minerAddress);
    ecoinAddPendingTransaction(ecoin, reward);
}

void ecoinDisplayTransactionFromList(LinkedList *list) {
    Element *current = list->head;
    int i = 0;
    printf("No.\t\tAmount\t\t\tFrom adress\t\t\t\t\t\t\tTo adress\n");
    while (current != NULL) {
        Transaction *transaction = (Transaction *) current->value;
        printf("%04d\t%05f\t\t%32s\t%32s\n", i, transaction->amount, transaction->from, transaction->to);
        current = current->next;
        ++i;
    }
    printf("--\n");
}

void ecoinDestroy(Ecoin *ecoin) {

    // Destroy all transactions within blocks
    for (int i = 1 ; i < ecoin->blockchain.n ; ++i) {
        Block *block = &ecoin->blockchain.blocks[i];
        if ((LinkedList *) block == NULL)
            continue;

        Element *current = ((LinkedList *) block)->head;
        while (current != NULL) {
            free((Transaction *) current->value); // FIXME : SEGFAULT
            current = current->next;
        }
    }
    // Destroy pending transaction list
    linkedListDestroy(&ecoin->pendingTransactions);
    // Destroy blockchain
    blockchainDestroy(&ecoin->blockchain);
}
