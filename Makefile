# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Target executable
TARGET = bitmap

# Object files
OBJ = main.o bitmap.o

# Rule to build the final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Rule to build main.o
main.o: main.c bitmap.h
	$(CC) $(CFLAGS) -c main.c

# Rule to build bitmap.o
bitmap.o: bitmap.c bitmap.h
	$(CC) $(CFLAGS) -c bitmap.c

# Clean rule to remove object files and executable
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets
.PHONY: clean
