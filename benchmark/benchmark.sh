#!/usr/bin/env bash

COMMAND="hyperfine -w 1 -s basic -u millisecond --"

if [ "$1" == "time" ]; then
    unset COMMAND
elif [ $# -ne 0 ]; then
    echo "Error: unknown arguments, exiting..."
    exit
elif ! [ -x "$(command -v hyperfine)" ]; then
    echo "Warning: hyperfine not found"
    unset COMMAND
fi

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
    echo ""
    echo "==============================="
    echo "## $DESC"
    echo "==============================="
    if [ "$1" == "time" ]; then
        echo "c sgc:"
        time ./sgc ${i} > /dev/null
        echo "c++ stl:"
        time ./std ${i} > /dev/null
    else
        echo "c sgc:"
        sh -c "${COMMAND} './sgc ${i}' || true"
        echo "c++ stl:"
        sh -c "${COMMAND} './std ${i}' || true"
    fi
done
