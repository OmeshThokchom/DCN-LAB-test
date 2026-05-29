#!/bin/sh

# Aim: Demonstrate ownership control using chown and chgrp.
# Note: chown usually requires superuser permission.

touch ownership_demo.txt

echo "Current file details:"
ls -l ownership_demo.txt

echo
echo "Example commands:"
echo "sudo chown new_user ownership_demo.txt"
echo "sudo chgrp new_group ownership_demo.txt"

