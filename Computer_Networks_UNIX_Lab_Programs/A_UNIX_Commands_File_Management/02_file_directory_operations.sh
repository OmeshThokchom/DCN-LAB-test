#!/bin/sh

# Aim: Demonstrate file and directory operations.

mkdir -p lab_demo
cd lab_demo || exit 1

echo "Creating files..."
touch file1.txt file2.txt

echo "Copying file1.txt to copy_file1.txt..."
cp file1.txt copy_file1.txt

echo "Moving file2.txt to moved_file2.txt..."
mv file2.txt moved_file2.txt

echo "Creating and removing a directory..."
mkdir sample_directory
rmdir sample_directory

echo "Deleting copied file..."
rm copy_file1.txt

echo "Remaining files:"
ls -l

