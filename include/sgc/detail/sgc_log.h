#pragma once
#include <stdlib.h>

static size_t sgc_log_two(size_t n) {
    size_t ret = 2;
    while ((n >>= 1)) {
        ++ret;
    }
    return ret;
}
