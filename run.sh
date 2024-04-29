#!/bin/bash

# Compile C programs
gcc -o a regular_request_generator.c
gcc -o b random_request_generator.c
gcc -o OS_Project OS_Project.c

# Run request generator programs in the background
./a &
./b &

# Wait for the background processes to finish
wait

# Run the main program
./OS_Project

# Clean up compiled files (optional)
rm a b OS_Project