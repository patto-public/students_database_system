# Makefile for STUDENTS_DATABASE_SYSTEM

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Werror

# Target executable
TARGET = output/main.exe

# Source files
SRC = main.c

# Build target
all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p output
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean target
clean:
	rm -f $(TARGET)
