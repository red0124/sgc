#!/bin/sh

set -x

SUB="s|\Q_equal\E|_eq|g"
echo $SUB

for i in $(find -type f -name "*.h"); do
    perl -pe "${SUB}" -i ${i}
    clang-format -i ${i}
done
