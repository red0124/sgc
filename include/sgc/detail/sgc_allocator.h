#pragma once
#include <stdbool.h>
#include <stdlib.h>

#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
#define _MAYBE_UNUSED __attribute__((unused))
#else
#define _MAYBE_UNUSED
#endif

#define SGC_SET_ALLOCATOR(MALLOC, REALLOC, FREE)                               \
    _MAYBE_UNUSED static inline void* sgc_malloc(size_t size) {                \
        return MALLOC(size);                                                   \
    }                                                                          \
                                                                               \
    _MAYBE_UNUSED static inline void* sgc_realloc(void* ptr, size_t size) {    \
        return REALLOC(ptr, size);                                             \
    }                                                                          \
                                                                               \
    _MAYBE_UNUSED static inline void sgc_free(void* ptr) {                     \
        FREE(ptr);                                                             \
    }

#ifndef SGC_USE_CUSTOM_ALLOCATOR
#ifdef SGC_STRICT_ALLOCATOR

/*
 * invokes exit(EXIT_FAILURE) on failed allocation
 */

_MAYBE_UNUSED static inline void* sgc_malloc(size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        exit(EXIT_FAILURE);
    }
    return ptr
}

_MAYBE_UNUSED static inline void* sgc_realloc(void* ptr, size_t size) {
    void* new_ptr = realloc(ptr, size);
    if (!new_ptr) {
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

_MAYBE_UNUSED static inline void sgc_free(void* ptr) {
    free(ptr);
}

#else

#ifdef SGC_FLAG_ALLOCATOR

/*
 * sets flag on failed allocation
 */

bool _sgc_flag_allocation_failed = false;

_MAYBE_UNUSED static inline void* sgc_malloc(size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        _sgc_flag_allocation_failed = true;
    }
    return ptr
}

_MAYBE_UNUSED static inline void* sgc_realloc(void* ptr, size_t size) {
    void* new_ptr = realloc(ptr, size);
    if (!new_ptr) {
        _sgc_flag_allocation_failed = true;
    }
    return new_ptr;
}

_MAYBE_UNUSED static inline void sgc_free(void* ptr) {
    free(ptr);
}

_MAYBE_UNUSED static inline bool sgc_failed_allocation(void) {
    return _sgc_flag_allocation_failed;
}

_MAYBE_UNUSED static inline bool sgc_clear_allocation_flag(void) {
    _sgc_flag_allocation_failed = false;
}

#else

/*
 * use default allocators - malloc, realloc, free
 */

SGC_SET_ALLOCATOR(malloc, realloc, free)

#endif /* ifdef SGC_FLAG_ALLOCATOR */
#endif /* ifdef SGC_STRICT_ALLOCATOR */
#endif /* ifndef SGC_USE_CUSTOM_ALLOCATOR */
