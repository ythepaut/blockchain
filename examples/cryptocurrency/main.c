/**
 * Cryptocurrency test program
 *
 * @author      Yohann THEPAUT (ythepaut) <contact@ythepaut.com>
 * @license     GNU GPL v3.0
 * @see         https://github.com/ythepaut/blockchain
 */

#include "cryptocurrency.h"

void printHelp() {
    printf("Help :\n");
    printf("\tmakeTransaction\t\t-\tMake a Ecoin transaction\n");
    printf("\tlistPendingTransactions\t-\tList all pending transactions\n");
    printf("\tlistBlocks\t\t\t\t-\tList Ecoin blocks\n");
    printf("\tmine\t\t\t\t\t-\tMine a block\n");
    printf("\thelp\t\t\t\t\t-\tPrints this message\n");
    printf("\texit\t\t\t\t\t-\tExit the program\n");
}

void makeTransaction(Ecoin *ecoin) {
    char input[101];
    printf("How many Ecoin do you want to transfer ?\n> ");
    scanf("%100s", input);
    double amount = strtod(input, NULL);

    printf("To which address do you wish to transfer these Ecoins ?\n> ");
    scanf("%100s", input);
    char to[100];
    strcpy(to, input);

    Transaction *transaction = ecoinCreateTransaction(amount, "qAM3akYA6oEErNiMgao4cm3GCFt5naCL", to);

    ecoinAddPendingTransaction(ecoin, transaction);

    printf("Done.\n");
}

void processCommand(char* cmd, Ecoin *ecoin) {
    if (strcmp(cmd, "help") == 0) {
        printHelp();
    } else if (strcmp(cmd, "makeTransaction") == 0) {
        makeTransaction(ecoin);
    } else if (strcmp(cmd, "listPendingTransactions") == 0) {
        ecoinDisplayTransactionFromList(&ecoin->pendingTransactions);
    } else if (strcmp(cmd, "listBlocks") == 0) {
        blockchainDisplay(&ecoin->blockchain);
    } else if (strcmp(cmd, "mine") == 0) {
        printf("Mining block No %d...\n", ecoin->blockchain.n);
        minePendingTransactions(ecoin, "qAM3akYA6oEErNiMgao4cm3GCFt5naCL");
        printf("Block mined !");
    } else if (strcmp(cmd, "exit") != 0) {
        printf("Unknown command. Type \"help\" for help\n");
    }
}

int main() {

    // Ecoin initialization
    Ecoin ecoin;
    ecoinInit(&ecoin);

    // Command prompt
    printf("Welcome to Ecoin !\n");
    char cmd[101];
    do {

        printf("\n> ");
        scanf("%100s", cmd);
        processCommand(cmd, &ecoin);

    } while (strcmp(cmd, "exit") != 0);
    printf("Goodbye !");

    ecoinDestroy(&ecoin);

    return 0;
}
