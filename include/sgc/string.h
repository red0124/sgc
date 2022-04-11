#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>
#include <string.h>

#define SGC_INIT_HEADERS_STRING(N)                                             \
    typedef char* N;                                                           \
    typedef char N##_type;                                                     \
                                                                               \
    void N##_copy(N* first, const N* const second);                            \
    void N##_init(N* s);                                                       \
    void N##_free(N* s);                                                       \
    size_t N##_size(N* s);                                                     \
    bool N##_eq(const N* const first, const N* const second);                  \
    bool N##_compare(const N* const first, const N* const second);             \
    int N##_void_compare(const void* const first, const void* const second);   \
    size_t N##_hash(const N* const s);                                         \
    N##_type* N##_array(N*);

#define SGC_INIT_STRING(N)                                                     \
    SGC_INIT_HEADERS_STRING(N)                                                 \
                                                                               \
    void N##_copy(N* first, const N* const second) {                           \
        if (*second) {                                                         \
            /* TODO replace with sgc_malloc */                                 \
            *first = strdup(*second);                                          \
        } else {                                                               \
            *first = NULL;                                                     \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_init(N* s) {                                                      \
        *s = NULL;                                                             \
    }                                                                          \
                                                                               \
    void N##_free(N* s) {                                                      \
        sgc_free(*s);                                                          \
    }                                                                          \
                                                                               \
    size_t N##_size(N* s) {                                                    \
        return strlen(*s);                                                     \
    }                                                                          \
                                                                               \
    bool N##_eq(const N* const first, const N* const second) {                 \
        if (first && second && *first && *second) {                            \
            return strcmp(*first, *second) == 0;                               \
        }                                                                      \
        return false;                                                          \
    }                                                                          \
                                                                               \
    bool N##_compare(const N* const first, const N* const second) {            \
        if (first && second && *first && *second) {                            \
            return strcmp(*first, *second);                                    \
        }                                                                      \
        return false;                                                          \
    }                                                                          \
                                                                               \
    int N##_void_compare(const void* const first, const void* const second) {  \
        if (first && second && *(N*)first && *(N*)second) {                    \
            return strcmp(*(N*)first, *(N*)second);                            \
        }                                                                      \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    size_t N##_hash(const N* const s) {                                        \
        size_t hash = 5381;                                                    \
        N str = *s;                                                            \
        int c;                                                                 \
                                                                               \
        while ((c = *str++)) {                                                 \
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */               \
        }                                                                      \
                                                                               \
        return hash;                                                           \
    }                                                                          \
                                                                               \
    N##_type* N##_array(N* s) {                                                \
        return *s;                                                             \
    }
