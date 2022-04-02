#!/bin/sh

set -x

SUB="s|\Q const size_t \E| size_t |g"
echo $SUB

for i in $(find -type f -name "*.h"); do
    perl -pe "${SUB}" -i ${i}
done
