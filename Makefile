# Compiler
CXX := g++

# Directories
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := obj
BIN_DIR := build

# Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra -I$(INCLUDE_DIR) $(shell sdl2-config --cflags)
LDFLAGS := $(shell sdl2-config --libs) -lSDL2_image

# Find all source files
SRC_FILES := $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Target executable
TARGET := $(BIN_DIR)/mon-jeu

# Rules
all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean
