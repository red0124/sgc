#pragma once
#include <stdlib.h>
#include <string.h>

// ==============
// INIT HEADERS
// ==============
#define _SGC_INIT_HEADERS_N(_1, _2, _3, _4, _5, _6, _7, NAME, ...) NAME

#define SGC_INIT_HEADERS(...)                                                  \
    _SGC_INIT_HEADERS_N(__VA_ARGS__, _SGC_INIT_HEADERS7, _SGC_INIT_HEADERS6,   \
                        _SGC_INIT_HEADERS5, _SGC_INIT_HEADERS4,                \
                        _SGC_INIT_HEADERS3)                                    \
    (__VA_ARGS__)

#define _SGC_INIT_HEADERS3(C, T, N) SGC_INIT_HEADERS_##C(T, N)

#define _SGC_INIT_HEADERS4(C, T, N, A1)                                        \
    _SGC_INIT_HEADERS3(C, T, N) SGC_INIT_HEADERS_##A1(T, N)

#define _SGC_INIT_HEADERS5(C, T, N, A1, A2)                                    \
    _SGC_INIT_HEADERS4(C, T, N, A1) SGC_INIT_HEADERS_##A2(T, N)

#define _SGC_INIT_HEADERS6(C, T, N, A1, A2, A3)                                \
    _SGC_INIT_HEADERS5(C, T, N, A1, A2) SGC_INIT_HEADERS_##A3(T, N)

#define _SGC_INIT_HEADERS7(C, T, N, A1, A2, A3, A4)                            \
    _SGC_INIT_HEADERS6(C, T, N, A1, A2, A3) SGC_INIT_HEADERS_##A4(T, N)

// ==============
// INIT HEADERS FS
// ==============
#define _SGC_INIT_HEADERS_FS_N(_1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME

#define SGC_INIT_HEADERS_FS(...)                                               \
    _SGC_INIT_HEADERS_FS_N(__VA_ARGS__, _SGC_INIT_HEADERS_FS8,                 \
                           _SGC_INIT_HEADERS_FS7, _SGC_INIT_HEADERS_FS6,       \
                           _SGC_INIT_HEADERS_FS5, _SGC_INIT_HEADERS_FS4, )     \
    (__VA_ARGS__)

#define _SGC_INIT_HEADERS_FS4(C, T, S, N) SGC_INIT_HEADERS_##C(T, S, N)

#define _SGC_INIT_HEADERS_FS5(C, T, S, N, A1)                                  \
    _SGC_INIT_HEADERS_FS4(C, T, S, N) SGC_INIT_##A1(T, N)

#define _SGC_INIT_HEADERS_FS6(C, T, S, N, A1, A2)                              \
    _SGC_INIT_HEADERS_FS5(C, T, S, N, A1) SGC_INIT_##A2(T, N)

#define _SGC_INIT_HEADERS_FS7(C, T, S, N, A1, A2, A3)                          \
    _SGC_INIT_HEADERS_FS6(C, T, S, N, A1, A2) SGC_INIT_##A3(T, N)

#define _SGC_INIT_HEADERS_FS8(C, T, S, N, A1, A2, A3, A4)                      \
    _SGC_INIT_HEADERS_FS7(C, T, S, N, A1, A2, A3) SGC_INIT_##A4(T, N)

// ==============
// INIT HEADERS PAIR
// ==============
#define _SGC_INIT_HEADERS_PAIR_N(_1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME

#define SGC_INIT_HEADERS_PAIR(...)                                             \
    _SGC_INIT_HEADERS_PAIR_N(__VA_ARGS__, _SGC_INIT_HEADERS_PAIR8,             \
                             _SGC_INIT_HEADERS_PAIR7, _SGC_INIT_HEADERS_PAIR6, \
                             _SGC_INIT_HEADERS_PAIR5, _SGC_INIT_HEADERS_PAIR4) \
    (__VA_ARGS__)

#define _SGC_INIT_HEADERS_PAIR4(C, K, V, N) SGC_INIT_HEADERS_##C(K, V, N)

#define _SGC_INIT_HEADERS_PAIR5(C, K, V, N, A1)                                \
    _SGC_INIT_HEADERS_PAIR4(C, K, V, N) SGC_INIT_HEADERS_##A1(V, N)

#define _SGC_INIT_HEADERS_PAIR6(C, K, V, N, A1, A2)                            \
    _SGC_INIT_HEADERS_PAIR5(C, K, V, N, A1) SGC_INIT_HEADERS_##A2(V, N)

#define _SGC_INIT_HEADERS_PAIR7(C, K, V, N, A1, A2, A3)                        \
    _SGC_INIT_HEADERS_PAIR6(C, K, V, N, A1, A2) SGC_INIT_HEADERS_##A3(V, N)

#define _SGC_INIT_HEADERS_PAIR8(C, K, V, N, A1, A2, A3, A4)                    \
    _SGC_INIT_HEADERS_PAIR7(C, K, V, N, A1, A2, A3) SGC_INIT_HEADERS_##A4(V, N)

// ==============
// INIT HEADERS FS PAIR
// ==============
#define _SGC_INIT_HEADERS_FS_PAIR_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, NAME,  \
                                    ...)                                       \
    NAME

#define SGC_INIT_HEADERS_FS_PAIR(...)                                          \
    _SGC_INIT_HEADERS_FS_PAIR_N(__VA_ARGS__, _SGC_INIT_HEADERS_FS_PAIR9,       \
                                _SGC_INIT_HEADERS_FS_PAIR8,                    \
                                _SGC_INIT_HEADERS_FS_PAIR7,                    \
                                _SGC_INIT_HEADERS_FS_PAIR6,                    \
                                _SGC_INIT_HEADERS_FS_PAIR5, )                  \
    (__VA_ARGS__)

#define _SGC_INIT_HEADERS_FS_PAIR5(C, K, V, S, N)                              \
    SGC_INIT_HEADERS_##C(K, V, S, N)

#define _SGC_INIT_HEADERS_FS_PAIR6(C, K, V, S, N, A1)                          \
    _SGC_INIT_HEADERS_FS_PAIR5(C, K, V, S, N) SGC_HEADERS_INIT_##A1(V, N)

#define _SGC_INIT_HEADERS_FS_PAIR7(C, K, V, S, N, A1, A2)                      \
    _SGC_INIT_HEADERS_FS_PAIR6(C, K, V, S, N, A1) SGC_INIT_##A2(V, N)

#define _SGC_INIT_HEADERS_FS_PAIR8(C, K, V, S, N, A1, A2, A3)                  \
    _SGC_INIT_HEADERS_FS_PAIR7(C, K, V, S, N, A1, A2) SGC_INIT_##A3(V, N)

#define _SGC_INIT_HEADERS_FS_PAIR9(C, K, V, S, N, A1, A2, A3, A4)              \
    _SGC_INIT_HEADERS_FS_PAIR8(C, K, V, S, N, A1, A2, A3) SGC_INIT_##A4(V, N)

// ==============
// INIT
// ==============
#define _SGC_INIT_N(_1, _2, _3, _4, _5, _6, _7, NAME, ...) NAME

#define SGC_INIT(...)                                                          \
    _SGC_INIT_N(__VA_ARGS__, _SGC_INIT7, _SGC_INIT6, _SGC_INIT5, _SGC_INIT4,   \
                _SGC_INIT3, )                                                  \
    (__VA_ARGS__)

#define _SGC_INIT3(C, T, N) SGC_INIT_##C(T, N)

#define _SGC_INIT4(C, T, N, A1) _SGC_INIT3(C, T, N) SGC_INIT_##A1(T, N)

#define _SGC_INIT5(C, T, N, A1, A2) _SGC_INIT4(C, T, N, A1) SGC_INIT_##A2(T, N)

#define _SGC_INIT6(C, T, N, A1, A2, A3)                                        \
    _SGC_INIT5(C, T, N, A1, A2) SGC_INIT_##A3(T, N)

#define _SGC_INIT7(C, T, N, A1, A2, A3, A4)                                    \
    _SGC_INIT6(C, T, N, A1, A2, A3) SGC_INIT_##A4(T, N)

// ==============
// INIT FS
// ==============
#define _SGC_INIT_FS_N(_1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME

#define SGC_INIT_FS(...)                                                       \
    _SGC_INIT_FS_N(__VA_ARGS__, _SGC_INIT_FS8, _SGC_INIT_FS7, _SGC_INIT_FS6,   \
                   _SGC_INIT_FS5, _SGC_INIT_FS4, )                             \
    (__VA_ARGS__)

#define _SGC_INIT_FS4(C, T, S, N) SGC_INIT_##C(T, S, N)

#define _SGC_INIT_FS5(C, T, S, N, A1)                                          \
    _SGC_INIT_FS4(C, T, S, N) SGC_INIT_##A1(T, N)

#define _SGC_INIT_FS6(C, T, S, N, A1, A2)                                      \
    _SGC_INIT_FS5(C, T, S, N, A1) SGC_INIT_##A2(T, N)

#define _SGC_INIT_FS7(C, T, S, N, A1, A2, A3)                                  \
    _SGC_INIT_FS6(C, T, S, N, A1, A2) SGC_INIT_##A3(T, N)

#define _SGC_INIT_FS8(C, T, S, N, A1, A2, A3, A4)                              \
    _SGC_INIT_FS7(C, T, S, N, A1, A2, A3) SGC_INIT_##A4(T, N)

// ==============
// INIT PAIR
// ==============
#define _SGC_INIT_DICT_N(_1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME

#define SGC_INIT_DICT(...)                                                     \
    _SGC_INIT_DICT_N(__VA_ARGS__, _SGC_INIT_DICT8, _SGC_INIT_DICT7,            \
                     _SGC_INIT_DICT6, _SGC_INIT_DICT5, _SGC_INIT_DICT4, )      \
    (__VA_ARGS__)

#define _SGC_INIT_DICT4(C, K, V, N) SGC_INIT_##C(K, V, N)

#define _SGC_INIT_DICT5(C, K, V, N, A1)                                        \
    _SGC_INIT_DICT4(C, K, V, N) SGC_INIT_##A1(V, N)

#define _SGC_INIT_DICT6(C, K, V, N, A1, A2)                                    \
    _SGC_INIT_DICT5(C, K, V, N, A1) SGC_INIT_##A2(V, N)

#define _SGC_INIT_DICT7(C, K, V, N, A1, A2, A3)                                \
    _SGC_INIT_DICT6(C, K, V, N, A1, A2) SGC_INIT_##A3(V, N)

#define _SGC_INIT_DICT8(C, K, V, N, A1, A2, A3, A4)                            \
    _SGC_INIT_DICT7(C, K, V, N, A1, A2, A3) SGC_INIT_##A4(V, N)

// ==============
// INIT FS_PAIR
// ==============
#define _SGC_INIT_FS_DICT_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, NAME, ...) NAME

#define SGC_INIT_FS_DICT(...)                                                  \
    _SGC_INIT_FS_DICT_N(__VA_ARGS__, _SGC_INIT_FS_DICT9, _SGC_INIT_FS_DICT8,   \
                        _SGC_INIT_FS_DICT7, _SGC_INIT_FS_DICT6,                \
                        _SGC_INIT_FS_DICT5, )                                  \
    (__VA_ARGS__)

#define _SGC_INIT_FS_DICT5(C, K, V, S, N) SGC_INIT_##C(K, V, S, N)

#define _SGC_INIT_FS_DICT6(C, K, V, S, N, A1)                                  \
    _SGC_INIT_FS_DICT5(C, K, V, S, N) SGC_INIT_##A1(V, N)

#define _SGC_INIT_FS_DICT7(C, K, V, S, N, A1, A2)                              \
    _SGC_INIT_FS_DICT6(C, K, V, S, N, A1) SGC_INIT_##A2(V, N)

#define _SGC_INIT_FS_DICT8(C, K, V, S, N, A1, A2, A3)                          \
    _SGC_INIT_FS_DICT7(C, K, V, S, N, A1, A2) SGC_INIT_##A3(V, N)

#define _SGC_INIT_FS_DICT9(C, K, V, S, N, A1, A2, A3, A4)                      \
    _SGC_INIT_FS_DICT8(C, K, V, S, N, A1, A2, A3) SGC_INIT_##A4(V, N)

// ==============
// COMMON MACROS
// ==============
#define _SGC_COPY(N, DST, SRC, SHARED)                                         \
    if (!SHARED) {                                                             \
        N##_copy(&DST, &SRC);                                                  \
    } else {                                                                   \
        DST = SRC;                                                             \
    }

#define _SGC_REPLACE(N, DST, SRC, SHARED)                                      \
    if (!SHARED) {                                                             \
        N##_free(&DST);                                                        \
        N##_copy(&DST, &SRC);                                                  \
    } else {                                                                   \
        DST = SRC;                                                             \
    }

#define _SGC_FREE(N, SRC, SHARED)                                              \
    if (!SHARED) {                                                             \
        N##_free(&SRC);                                                        \
    }

#define _SGC_ARRAY_COPY(T, DST, SRC, SIZE, SHARED)                             \
    if (SHARED) {                                                              \
        memcpy(DST, SRC, SIZE * sizeof(T));                                    \
    } else {                                                                   \
        for (size_t i = 0; i < SIZE; ++i) {                                    \
            T##_copy(&DST[i], &SRC[i]);                                        \
        }                                                                      \
    }

#define _SGC_ARRAY_FREE(T, SRC, SIZE, SHARED)                                  \
    if (!SHARED) {                                                             \
        for (size_t i = 0; i < SIZE; ++i) {                                    \
            T##_free(&SRC[i]);                                                 \
        }                                                                      \
    }

// ==============
// RANGE LOOPS
// ==============
#define _SGC_TOKENPASTE(x, y) x##y
#define _SGC_TOKENPASTE2(x, y) _SGC_TOKENPASTE(x, y)
#define _SGC_UNIQUE(x) _SGC_TOKENPASTE2(_sgc_unique_##x, __LINE__)

#define sgc_for_each(...) _SGC_FOR_EACH(__VA_ARGS__)

#define _SGC_FOR_EACH(EL, C, N)                                                \
    N##_it _SGC_UNIQUE(curr) = N##_cbegin(&C);                                 \
    for (N##_type* EL = (N##_type*)N##_it_data(&_SGC_UNIQUE(curr));            \
         N##_it_valid(&_SGC_UNIQUE(curr)); N##_it_go_next(&_SGC_UNIQUE(curr)), \
                   EL = (N##_type*)N##_it_data(&_SGC_UNIQUE(curr)))

#define sgc_for_each_reverse(...) _SGC_FOR_EACH_REVERSE(__VA_ARGS__)

#define _SGC_FOR_EACH_REVERSE(EL, C, N)                                        \
    N##_it _SGC_UNIQUE(curr) = N##_cend(&C);                                   \
    for (N##_type* EL = (N##_type*)N##_it_data(&_SGC_UNIQUE(curr));            \
         N##_it_valid(&_SGC_UNIQUE(curr)); N##_it_go_prev(&_SGC_UNIQUE(curr)), \
                   EL = (N##_type*)N##_it_data(&_SGC_UNIQUE(curr)))

// ==============
// USER MACROS
// ==============

#define SGC_MOVE(N, DS, ...)                                                   \
    N##_set_sharing(&DS);                                                      \
    __VA_ARGS__;                                                               \
    N##_set_owning(&DS);

#ifndef SGC_NO_KEYWORDS

#define IN ,
#define AS ,
#define for_each sgc_for_each
#define for_each_reverse sgc_for_each_reverse

#endif
