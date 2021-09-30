# | Makefile for the Rose project (github.com/anarchuser/rose)

# Compiler
CC = gcc

# Ensure make still works if someone creates a file named like follows:
.PHONY: build clean run

# Default target (invoked by `make` or `make build`). Produces 'kernel8.img' which can then be booted from
build: sender

clean:
	rm sender

sender:
	$(CC) -o sender sender.c

run: sender
	./sender