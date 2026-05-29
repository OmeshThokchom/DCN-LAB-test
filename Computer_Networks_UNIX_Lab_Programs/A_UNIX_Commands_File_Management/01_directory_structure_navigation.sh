#!/bin/sh

# Aim: Demonstrate UNIX directory structure and navigation commands.

echo "Current working directory:"
pwd

echo
echo "Files and folders in current directory:"
ls

echo
echo "Detailed listing:"
ls -l

echo
echo "Move to parent directory and print path:"
cd ..
pwd

