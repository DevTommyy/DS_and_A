# Define compiler
CC = gcc
# Define compiler flags
CFLAGS = -Wall -Wextra
# Define source files
SOURCES = hash_map.c ../headers/LinkedList.c
# Define output binary name
OUTPUT = hash_map

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
