CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99

all: converter encoder formatter

converter: converter.c
encoder: encoder.c
formatter: formatter.c

clean:
	rm -f converter encoder
