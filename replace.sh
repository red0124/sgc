#!/bin/sh

set -x

SUB="s|\Qstruct N* \E|N* |g"
echo $SUB

for i in $(find -type f -name "*.h"); do
    perl -pe "${SUB}" -i ${i}
done
