#!/bin/bash

# Create necessary directories
sudo mkdir -p /usr/local/share/cbpc/assets

# Copy assets to the shared directory
sudo cp -r assets/* /usr/local/share/cbpc/assets/

# Compile the program
gcc -o cbpc src/main.c

# Move the binary to /usr/local/bin
sudo mv cbpc /usr/local/bin/

echo "Installation complete. You can now run the app with 'cbpc'."
