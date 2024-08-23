#!/bin/bash

# Compile the program
gcc -o cbpc main.c

# Move the binary to /usr/local/bin
sudo mv cbpc /usr/local/bin/

echo "Installation complete. You can run the app by typing 'cbpc'."

