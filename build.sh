#!/bin/bash

# Create bin directory if it doesn't exist
mkdir -p bin

# Compile all .cpp files in src directory
make

# Check if compilation succeeded
if [ $? -eq 0 ]; then
    echo "Compilation successful, running application..."
    ./bin/myapp
else
    echo "Compilation failed."
fi
