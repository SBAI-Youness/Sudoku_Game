# Detect OS
OS := $(shell uname -s)

# Compiler and common flags
CC = gcc
CFLAGS = -Iinclude -Wall -Werror -Wextra -Wpedantic

# Directories and source files
SRC := $(wildcard ./source/*.c)
BUILD = build

# Platform-specific settings
ifeq ($(OS),Linux)
  LDFLAGS = -Llibraries -lraylib -lm -ldl -lpthread -lGL -lX11
  TARGET = $(BUILD)/main
  MKDIR = mkdir -p $(BUILD)
  RMDIR = rm -rf $(BUILD)
  RUN = ./$(TARGET)
else
  # Assume Windows (for MSYS/MinGW)
  LDFLAGS = -Llibraries -lraylib -lopengl32 -lgdi32 -lwinmm
  TARGET = $(BUILD)/main.exe
  MKDIR = if not exist $(BUILD) mkdir $(BUILD)
  RMDIR = rmdir /S /Q $(BUILD)
  RUN = $(TARGET)
endif

# Default target
all: $(TARGET)

# Create the build directory if it doesn't exist
$(BUILD):
	$(MKDIR)

# Build target for app
$(TARGET): $(SRC) | $(BUILD)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Run the program after building
run: $(TARGET)
	@$(RUN)

# Clean the build directory
clean:
	$(RMDIR)

.PHONY: all clean run
