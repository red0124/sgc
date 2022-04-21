#pragma once
#include "sgc_utils.h"
#include <stdbool.h>
#include <stdlib.h>

#define SGC_SET_ALLOCATOR(MALLOC, REALLOC, FREE)                               \
    static inline void* sgc_malloc(size_t size) {                              \
        return MALLOC(size);                                                   \
    }                                                                          \
                                                                               \
    static inline void* sgc_realloc(void* ptr, size_t size) {                  \
        return REALLOC(ptr, size);                                             \
    }                                                                          \
                                                                               \
    static inline void sgc_free(void* ptr) {                                   \
        FREE(ptr);                                                             \
    }

#ifndef SGC_USE_CUSTOM_ALLOCATOR
#ifdef SGC_STRICT_ALLOCATOR

/*
 * invokes exit(EXIT_FAILURE) on failed allocation
 */

static inline void* sgc_malloc(size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        exit(EXIT_FAILURE);
    }
    return ptr
}

static inline void* sgc_realloc(void* ptr, size_t size) {
    void* new_ptr = realloc(ptr, size);
    if (!new_ptr) {
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

static inline void sgc_free(void* ptr) {
    free(ptr);
}

#else

#ifdef SGC_FLAG_ALLOCATOR

/*
 * sets flag on failed allocation
 */

bool _sgc_flag_allocation_failed = false;

static inline void* sgc_malloc(size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        _sgc_flag_allocation_failed = true;
    }
    return ptr
}

static inline void* sgc_realloc(void* ptr, size_t size) {
    void* new_ptr = realloc(ptr, size);
    if (!new_ptr) {
        _sgc_flag_allocation_failed = true;
    }
    return new_ptr;
}

static inline void sgc_free(void* ptr) {
    free(ptr);
}

static inline bool sgc_failed_allocation(void) {
    return _sgc_flag_allocation_failed;
}

static inline bool sgc_clear_allocation_flag(void) {
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
