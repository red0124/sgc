#pragma once
#include <stdbool.h>
#include <stdlib.h>

#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
#define _MAYBE_UNUSED __attribute__((unused))
#else
#define _MAYBE_UNUSED
#endif

#define SGC_SET_NO_SPACE_LEFT_HANDLER(HANDLER)                                 \
    _MAYBE_UNUSED static inline void _sgc_no_space_left_handler(size_t size,   \
                                                                size_t max) {  \
        HANDLER(size, max);                                                    \
    }

#ifndef SGC_USE_CUSTOM_NO_SPACE_LEFT_HANDLER
_MAYBE_UNUSED static inline void _sgc_no_space_left_default_handler(
    size_t size, size_t max) {
    (void)size;
    (void)max;
}

SGC_SET_NO_SPACE_LEFT_HANDLER(_sgc_no_space_left_default_handler)
#endif

#undef _MAYBE_UNUSED
