# Define compiler
CC = gcc
# Define compiler flags
CFLAGS = -Wall -Wextra
# Define source files
SOURCES = BFS_binary_tree.c ../headers/Deque.c
# Define output binary name
OUTPUT = BFS_binary_tree

# Default target
all: $(OUTPUT)

# Rule to build the binary
$(OUTPUT): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(OUTPUT)
	make run
	make clean

# Target to run the executable
run: $(OUTPUT)
	./$(OUTPUT)

# Clean target
clean:
	rm -f $(OUTPUT)

.PHONY: all clean
