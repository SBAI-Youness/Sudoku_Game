# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall -Werror -Wextra -Wpedantic
LDFLAGS = -Llibraries -lraylib -lopengl32 -lgdi32 -lwinmm

# Directories and source files
SRC := $(wildcard ./source/*.c)
BUILD = build

# Target executable
TARGET = $(BUILD)/main.exe

# Default target
all: $(TARGET)

# Create the build directory if it doesn't exist
$(BUILD):
	@if not exist $(BUILD) mkdir $(BUILD)

# Build target for app
$(TARGET): $(SRC) | $(BUILD)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Run the program after building
run: $(TARGET)
	@$(TARGET)

clean:
	rmdir /S /Q $(BUILD)

.PHONY: all clean run