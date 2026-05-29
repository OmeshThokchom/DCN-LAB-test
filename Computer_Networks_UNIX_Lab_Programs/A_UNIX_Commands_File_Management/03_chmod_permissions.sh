#!/bin/sh

# Aim: Change read, write, and execute permissions using chmod.

touch permission_demo.sh
echo "echo Permission demo file" > permission_demo.sh

echo "Initial permissions:"
ls -l permission_demo.sh

echo "Adding execute permission:"
chmod +x permission_demo.sh
ls -l permission_demo.sh

echo "Setting permission to rwxr-xr-x:"
chmod 755 permission_demo.sh
ls -l permission_demo.sh

