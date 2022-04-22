#pragma once
#include "sgc_utils.h"
#include <stdbool.h>
#include <stdlib.h>

#define SGC_SET_NO_SPACE_LEFT_HANDLER(HANDLER)                                 \
    static inline void _sgc_no_space_left_handler() {                          \
    }

#ifndef SGC_USE_CUSTOM_NO_SPACE_LEFT_HANDLER
static inline void _sgc_no_space_left_default_handler(void) {
}

SGC_SET_NO_SPACE_LEFT_HANDLER(_sgc_no_space_left_default_handler)
#endif

#undef _MAYBE_UNUSED
