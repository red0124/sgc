#!/bin/sh

set -x

SUB="s|\Qvoid N##_set_share(N* u, bool shared);\E|void N##_set_shareing(N* u); void N##_set_owning(N* u);|g"
echo $SUB

for i in $(find -type f -name "*.h"); do
    perl -pe "${SUB}" -i ${i}
    clang-format -i ${i}
done
