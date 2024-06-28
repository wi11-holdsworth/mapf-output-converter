CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99

all: converter encoder

converter: converter.c
encoder: encoder.c

clean:
	rm -f converter encoder
