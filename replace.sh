#!/bin/sh

set -x

for MEMBER in "shared_key" "size" "max" "data" "shared" "next" "prev" "head" \
    "tail" "parent" "left" "right" "color" "root" "is_valid" "curr_bucket" \
    "curr" "back" "front" "value" "state"; do
    SUB0="s|\Q _${MEMBER} \E| ${MEMBER} |g"
    SUB1="s|\Q._${MEMBER}\E|.${MEMBER}_|g"
    SUB2="s|\Q->_${MEMBER}\E|->${MEMBER}_|g"
    SUB3="s|\Q _${MEMBER};\E| ${MEMBER}_;|g"
    SUB4="s|\Q _${MEMBER}[\E| ${MEMBER}_[|g"

    echo $SUB1
    echo $SUB2
    echo $SUB3

    for i in $(find -type f -name "*.h"); do
        perl -pe "${SUB0}" -i ${i}
        perl -pe "${SUB1}" -i ${i}
        perl -pe "${SUB2}" -i ${i}
        perl -pe "${SUB3}" -i ${i}
        perl -pe "${SUB4}" -i ${i}
    done
done
