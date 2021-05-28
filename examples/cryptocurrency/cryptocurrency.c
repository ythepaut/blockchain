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

void minePendingTransactions(Ecoin *ecoin, char *minerAddress) {
    Block block = {
            .timestamp = time(NULL),
            .data = (void *) &ecoin->pendingTransactions,
            .size = sizeof(ecoin->pendingTransactions),
            .previousHash = "",
            .hash = "",
            .nonce = 0
    };
    blockchainAddBlock(&ecoin->blockchain, &block);
}