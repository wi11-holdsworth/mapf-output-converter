CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99
SRC_DIR = src
EXEC_DIR = bin

all: $(EXEC_DIR)/converter $(EXEC_DIR)/encoder $(EXEC_DIR)/formatter $(EXEC_DIR)/impute

$(EXEC_DIR)/converter: $(SRC_DIR)/converter.c | $(EXEC_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(EXEC_DIR)/encoder: $(SRC_DIR)/encoder.c | $(EXEC_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(EXEC_DIR)/formatter: $(SRC_DIR)/formatter.c | $(EXEC_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(EXEC_DIR)/impute: $(SRC_DIR)/impute.c | $(EXEC_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(EXEC_DIR):
	mkdir -p $(EXEC_DIR)

clean:
	rm -rf $(EXEC_DIR)