/**
 * Simple blockchain program
 *
 * @author      Yohann THEPAUT (ythepaut) <contact@ythepaut.com>
 * @license     GNU GPL v3.0
 * @see         https://github.com/ythepaut/blockchain
 */

#include "../../src/blockchain.h"

void printHelp() {
    printf("Help :\n");
    printf("\tdisplay\t\t\t\t\t-\tDisplay the blockchain\n");
    printf("\tcreate\t\t\t\t\t-\tCreate a new block\n");
    printf("\tedit\t\t\t\t\t-\tModify a block's data\n");
    printf("\tvalidate\t\t\t\t-\tCheck if the blockchain is valid\n");
    printf("\thelp\t\t\t\t\t-\tPrint this message\n");
    printf("\texit\t\t\t\t\t-\tExit the program\n");
}

void createBlock(Blockchain *blockchain) {
    char *input = calloc(1024, sizeof(char));
    printf("What string would you like to store ?\n> ");
    scanf("%1023s", input);

    Block block = {
            .timestamp = time(NULL),
            .data = (void *) input,
            .size = sizeof(*input),
            .previousHash = "",
            .hash = "",
            .nonce = 0
    };
    printf("Mining and adding block to the blockchain...\n");
    blockchainAddBlock(blockchain, &block);
    printf("Done.\n");
}

void editBlock(Blockchain *blockchain) {
    char buffer[10];
    printf("Which block would you like to modify ?\n> ");
    scanf("%9s", buffer);
    int i = (int) strtol(buffer, NULL, 10);

    char *input = calloc(1024, sizeof(char));
    printf("What string would you like to store ?\n> ");
    scanf("%1023s", input);
    Block block = blockchain->blocks[i];
    strcpy(block.data, input);
    block.size = sizeof(*input);
    free(input);
    printf("Done.\n");
}

void processCommand(char *cmd, Blockchain *blockchain) {
    if (strcmp(cmd, "help") == 0) {
        printHelp();
    } else if (strcmp(cmd, "display") == 0) {
        blockchainDisplay(blockchain);
    } else if (strcmp(cmd, "create") == 0) {
        createBlock(blockchain);
    } else if (strcmp(cmd, "edit") == 0) {
        editBlock(blockchain);
    } else if (strcmp(cmd, "validate") == 0) {
        printf("%s\n", blockchainValidate(blockchain) ? "Blockchain is valid" : "Blockchain has been tampered with");
    } else if (strcmp(cmd, "exit") != 0) {
        printf("Unknown command. Type \"help\" for help\n");
    }
}

int main(int argc, char *argv[]) {

    int difficulty = 3;
    if (argc == 2) {
        difficulty = (int) strtol(argv[1], NULL, 10);
    }

    printf("Initializing blockchain...\n");

    Blockchain blockchain;
    blockchainInit(&blockchain, difficulty);

    // Command prompt
    printf("Welcome !\n");
    char cmd[101];
    do {

        printf("\n> ");
        scanf("%100s", cmd);
        processCommand(cmd, &blockchain);

    } while (strcmp(cmd, "exit") != 0);
    printf("Goodbye !\n");

    blockchainDestroy(&blockchain);

    return 0;
}
