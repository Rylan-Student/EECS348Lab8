#   make             # builds both executables
#   make P1_Lab8     # builds only the first program
#   make P2_Lab8     # builds only the second program
#   make run_P1      # run the first program 
#   make run_P2      # run the second program
#   make clean       # remove executables and object files

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2
LDFLAGS =

P1_SRC = P1_Lab8.c
P2_SRC = P2_Lab8.c

P1_BIN = P1_Lab8
P2_BIN = P2_Lab8

.PHONY: all clean run_P1 run_P2

all: $(P1_BIN) $(P2_BIN)

$(P1_BIN): $(P1_SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

$(P2_BIN): $(P2_SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

# Convenience aliases
p1: $(P1_BIN)
p2: $(P2_BIN)

# Run targets (interactive)
run_P1: $(P1_BIN)
	./$(P1_BIN)

run_P2: $(P2_BIN)
	./$(P2_BIN)

clean:
	-rm -f $(P1_BIN) $(P2_BIN) *.o
