##
# Blockchain Makefile
#
# Yohann THEPAUT (ythepaut) <contact@ythepaut.com>
# GNU GPL v3.0
# https://github.com/ythepaut/blockchain

CFLAGS = -Wall -Wextra -pedantic -std=gnu99 -O3 -Wno-unused-parameter -Werror -lssl -lcrypto

CC = gcc $(CFLAGS)
#CC = clang $(CFLAGS)

all: blockchain simple cryptocurrency

cryptocurrency: src/blockchain.o examples/cryptocurrency/cryptocurrency.o
	$(CC) -o $@ $^

simple: src/blockchain.o examples/simple/main.o
	$(CC) -o $@ $^

blockchain: src/main.o src/blockchain.o
	$(CC) -o $@ $^

%.o: src/%.c src/%.h
	$(CC) -c $< -o $@

clean:
	rm -f src/main src/*.o src/a.out examples/cryptocurrency/*.o
