#!/bin/bash

CASES=(
    "MAP INSERT SMALL"
    "MAP INSERT MEDIUM"
    "MAP INSERT LARGE"
    "MAP ITERATE"
    "UNORDERED MAP INSERT SMALL"
    "UNORDERED MAP INSERT MEDIUM"
    "UNORDERED MAP INSERT LARGE"
    "UNORDERED MAP ITERATE"
    "VECTOR ITERATE"
    "DEQUE INSERT SMALL"
    "DEQUE INSERT LARGE"
    "DEQUE ITERATE"
    "UNORDERED MAP OF VECTORS"
    "PRIORITY QUEUE PUSH POP SMALL"
    "PRIORITY QUEUE PUSH POP LARGE"
)

for i in "${!CASES[@]}"; do 
    DESC="${CASES[$i]}"
    echo "========================="
    echo "========================="
    echo "## $DESC"
    echo "========================="
    echo "c sgc:"
    hyperfine -s basic -u millisecond -- "./sgc ${i}"
    echo "c++ stl:"
    hyperfine -s basic -u millisecond -- "./std ${i}"
done
