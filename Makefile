# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -O2

# Source and build directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Output executable
TARGET = $(BIN_DIR)/sim

# Find all .c files in src/
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Convert .c files to .o files in obj/
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Compile .c files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories if they don't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean up build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets (not files)
.PHONY: all clean
