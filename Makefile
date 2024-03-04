# Compiler
CC := gcc

# Directories
SRC_DIR := src
BUILD_DIR := build

# Source files
SRC := ./src/main.c ./src/**/*.c

# Object files
OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

# Compiler flags
CFLAGS := -Wall -Wextra # -lubsan -fsanitize=undefined -fsanitize=address

# Build target
TARGET := $(BUILD_DIR)/ias

# Default target
all: $(TARGET)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -g

# Link object files
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Clean build directory
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
