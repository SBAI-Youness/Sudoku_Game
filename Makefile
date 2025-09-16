# Detect OS
OS := $(shell uname -s)

# Compiler and common flags
CC = gcc
CFLAGS = -Iinclude

# Directories and source files
SRC := $(wildcard ./source/*.c)
BUILD = build

# Platform-specific settings
ifeq ($(OS),Linux)
  LDFLAGS = -Llibraries -lraylib -lm -ldl -lpthread -lGL -lX11
  TARGET = main
  MKDIR = mkdir -p $(BUILD)
  RMDIR = rm -rf $(BUILD)
else
  # Assume Windows (for MSYS/MinGW)
  LDFLAGS = -Llibraries -lraylib -lopengl32 -lgdi32 -lwinmm
  TARGET = main.exe
  MKDIR = if not exist $(BUILD) mkdir $(BUILD)
  RMDIR = rmdir /S /Q $(BUILD)
endif

# Default target
all: $(BUILD)/$(TARGET)

# Create the build directory if it doesn't exist
$(BUILD):
	$(MKDIR)

# Build target for app
$(BUILD)/$(TARGET): $(SRC) | $(BUILD)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Run the program after building
run: $(BUILD)/$(TARGET)
	cd $(BUILD) && ./$(TARGET)

# Clean the build directory
clean:
	$(RMDIR)

.PHONY: all clean run
