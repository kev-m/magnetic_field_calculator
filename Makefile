# Makefile for a C project

# Application name
APP_NAME := magnetic_field_calculator

# Directories
SRC_DIR := src
OBJ_DIR := obj

# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -std=c99 -lm -O3

# Source files and object files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Default target
all: $(APP_NAME)

# Linking
$(APP_NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Compiling
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean
clean:
	rm -rf $(OBJ_DIR) $(APP_NAME)

.PHONY: all clean
