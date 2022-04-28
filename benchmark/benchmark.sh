#!/usr/bin/env sh

hyperfine -w 1  -s basic  -u millisecond --export-json out.json \
        -L exe sgc,std \
        -L test_num 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14   \
        -- "./{exe} {test_num}"
