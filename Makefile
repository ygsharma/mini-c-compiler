# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = build

# Target executable
TARGET = mylexer

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files (replace src/foo.cpp → build/foo.o)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
all: $(TARGET)

# Link object files to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each .cpp to .o inside build/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the lexer on a test file (default test1.c)
run: $(TARGET)
	./$(TARGET) test/test1.c

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
