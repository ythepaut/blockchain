##
# Blockchain Makefile
#
# Yohann THEPAUT (ythepaut) <contact@ythepaut.com>
# GNU GPL v3.0
# https://github.com/ythepaut/blockchain

CFLAGS = -Wall -Wextra -pedantic -std=gnu99 -O3 -Wno-unused-parameter -Werror -lssl -lcrypto

CC = gcc $(CFLAGS)
#CC = clang $(CFLAGS)

all: main

main: main.o blockchain.o
	$(CC) -o $@ $^

%.o: %.c %.h
	$(CC) -c $< -o $@

clean:
	rm -f main *.o a.out
