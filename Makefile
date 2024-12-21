# Makefile

# Compiler and flags
CXX := g++

CXXFLAGS := -std=c++11 -OO
INCLUDES := -I include

# Make a variable for the source directory
SRC_DIR := jrx

# Find all .cpp source files recursively in src directory
SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')

# Generate the list of object files, mapping src/ to build/
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, build/%.o, $(SOURCES))

# Target executable
TARGET := bin/myapp

# Default target
all: $(TARGET)

# Link object files to create the final executable
$(TARGET): $(OBJECTS)
	@echo "Linking $@..."
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

# Compile source files to object files
build/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<..."
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up build and bin directories
clean:
	@echo "Cleaning up..."
	@rm -rf build bin

# Run the application
run: $(TARGET)
	@echo "Running application..."
	@./$(TARGET)

.PHONY: all clean run