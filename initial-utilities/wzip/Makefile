EXEC = wzip
TEST_SCRIPT = test-$(EXEC).sh
SRC = $(EXEC).c
CC = gcc
CFLAGS = -Wall -Werror -g -std=c11 -Wshadow -Wvla -pedantic

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

time: $(SRC)
	$(CC) $(CFLAGS) -DTIME -o $(EXEC) $(SRC)
test: $(EXEC)
	./$(TEST_SCRIPT)


clean:
	rm -f $(EXEC)

.PHONY: clean test time

