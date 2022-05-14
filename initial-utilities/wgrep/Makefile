EXEC = wgrep
TEST_SCRIPT = test-$(EXEC).sh
SRC = $(EXEC).c
CC = gcc
CFLAGS = -Wall -Werror -g -std=c11 -Wshadow -Wvla -pedantic

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

test: $(EXEC)
	./$(TEST_SCRIPT)

clean:
	rm -f $(EXEC)

.PHONY: clean test

