#!/bin/bash

# WARNING: This is not a makefile! It is provided only to give a sense of the commands
# necessary to build this whole project. 

set -e

echo "Cleaning all .sw* files"

find . -name \*.sw* -type f -delete

set +e
