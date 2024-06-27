CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99

converter: converter.c
	$(CC) $(CFLAGS) converter.c -o converter

clean:
	rm -f converter
