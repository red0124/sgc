#!/bin/sh

set -x

SUB="s|\Q_p_##_p_\E|_p_|g"
echo $SUB

for i in $(find -type f -name "*.h"); do
    perl -pe "${SUB}" -i ${i}
done
