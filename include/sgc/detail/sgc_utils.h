#pragma once
#include <stdlib.h>
#include <string.h>

#define SGC_INIT_HEADERS_N(_1, _2, _3, _4, _5, _6, _7, NAME, ...) NAME
#define SGC_INIT_HEADERS(...)                                                  \
    SGC_INIT_HEADERS_N(__VA_ARGS__, SGC_INIT_HEADER7, SGC_INIT_HEADER6,        \
                       SGC_INIT_HEADER5, SGC_INIT_HEADER4, SGC_INIT_HEADER3)   \
    (__VA_ARGS__)

#define SGC_INIT_HEADER3(C, T, N) SGC_INIT_HEADERS_##C(T, N)

#define SGC_INIT_HEADER4(C, T, N, A1)                                          \
    SGC_INIT_HEADERS_##C(T, N) SGC_INIT_HEADERS_##A1(T, N)

#define SGC_INIT_HEADER5(C, T, N, A1, A2)                                      \
    SGC_INIT_HEADERS_##C(T, N) SGC_INIT_HEADERS_##A1(T, N)                     \
        SGC_INIT_HEADERS_##A2(T, N)

#define SGC_INIT_HEADER6(C, T, N, A1, A2, A3)                                  \
    SGC_INIT_HEADERS_##C(T, N) SGC_INIT_HEADERS_##A1(T, N)                     \
        SGC_INIT_HEADERS_##A2(T, N) SGC_INIT_HEADERS_##A3(T, N)

#define SGC_INIT_HEADER7(C, T, N, A1, A2, A3, A4)                              \
    SGC_INIT_HEADERS_##C(T, N) SGC_INIT_HEADERS_##A1(T, N)                     \
        SGC_INIT_HEADERS_##A2(T, N) SGC_INIT_HEADERS_##A3(T, N)                \
            SGC_INIT_HEADERS_##A4(T, N)

#define SGC_INIT_HEADERS_PAIR_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, NAME, ...) \
    NAME

#define SGC_INIT_HEADERS_PAIR(...)                                             \
    SGC_INIT_HEADERS_PAIR_N(__VA_ARGS__, SGC_INIT_HEADERS_PAIR9,               \
                            SGC_INIT_HEADERS_PAIR8, SGC_INIT_HEADERS_PAIR7,    \
                            SGC_INIT_HEADERS_PAIR6, SGC_INIT_HEADERS_PAIR5,    \
                            SGC_INIT_HEADERS_PAIR4)                            \
    (__VA_ARGS__)

#define SGC_INIT_HEADERS_PAIR4(C, K, V, N) SGC_INIT_HEADERS_##C(K, V, N)

#define SGC_INIT_HEADERS_PAIR5(C, K, V, N, A1)                                 \
    SGC_INIT_HEADERS_##C(K, V, N) SGC_INIT_HEADERS_##A1(V, N)

#define SGC_INIT_HEADERS_PAIR6(C, K, V, N, A1, A2)                             \
    SGC_INIT_HEADERS_##C(K, V, N) SGC_INIT_HEADERS_##A1(V, N)                  \
        SGC_INIT_HEADERS_##A2(V, N)

#define SGC_INIT_HEADERS_PAIR7(C, K, V, N, A1, A2, A3)                         \
    SGC_INIT_HEADERS_##C(K, V, N) SGC_INIT_HEADERS_##A1(V, N)                  \
        SGC_INIT_HEADERS_##A2(V, N) SGC_INIT_HEADERS_##A3(V, N)

#define SGC_INIT_HEADERS_PAIR8(C, K, V, N, A1, A2, A3, A4)                     \
    SGC_INIT_HEADERS_##C(K, V, N) SGC_INIT_HEADERS_##A1(V, N)                  \
        SGC_INIT_HEADERS_##A2(V, N) SGC_INIT_HEADERS_##A3(V, N)                \
            SGC_INIT_HEADERS_##A4(V, N)

#define SGC_INIT_HEADERS_PAIR9(C, K, V, N, A1, A2, A3, A4, A5)                 \
    SGC_INIT_HEADERS_##C(K, V, N) SGC_INIT_HEADERS_##A1(V, N)                  \
        SGC_INIT_HEADERS_##A2(V, N) SGC_INIT_HEADERS_##A3(V, N)                \
            SGC_INIT_HEADERS_##A4(V, N) SGC_INIT_HEADERS_##A5(V, N)

#define SGC_INIT_N(_1, _2, _3, _4, _5, _6, _7, NAME, ...) NAME
#define SGC_INIT(...)                                                          \
    SGC_INIT_N(__VA_ARGS__, SGC_INIT7, SGC_INIT6, SGC_INIT5, SGC_INIT4,        \
               SGC_INIT3, SGC_INIT2, )                                         \
    (__VA_ARGS__)

#define SGC_INIT2(C, N) SGC_INIT_##C(N)

#define SGC_INIT3(C, T, N) SGC_INIT_##C(T, N)

#define SGC_INIT4(C, T, N, A1) SGC_INIT_##C(T, N) SGC_INIT_##A1(T, N)

#define SGC_INIT5(C, T, N, A1, A2)                                             \
    SGC_INIT_##C(T, N) SGC_INIT_##A1(T, N) SGC_INIT_##A2(T, N)

#define SGC_INIT6(C, T, N, A1, A2, A3)                                         \
    SGC_INIT_##C(T, N) SGC_INIT_##A1(T, N) SGC_INIT_##A2(T, N)                 \
        SGC_INIT_##A3(T, N)

#define SGC_INIT7(C, T, N, A1, A2, A3, A4)                                     \
    SGC_INIT_##C(T, N) SGC_INIT_##A1(T, N) SGC_INIT_##A2(T, N)                 \
        SGC_INIT_##A3(T, N) SGC_INIT_##A4(T, N)

#define SGC_INIT_SN(_1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME
#define SGC_INIT_STATIC(...)                                                   \
    SGC_INIT_SN(__VA_ARGS__, SGC_INIT_STATIC8, SGC_INIT_STATIC7,               \
                SGC_INIT_STATIC6, SGC_INIT_STATIC5, SGC_INIT_STATIC4,          \
                SGC_INIT_STATIC3)                                              \
    (__VA_ARGS__)

#define SGC_INIT_STATIC3(C, S, N) SGC_INIT_S##C(S, N)

#define SGC_INIT_STATIC4(C, T, S, N) SGC_INIT_S##C(T, S, N)

#define SGC_INIT_STATIC5(C, T, S, N, A1)                                       \
    SGC_INIT_S##C(T, S, N) SGC_INIT_##A1(T, N)

#define SGC_INIT_STATIC6(C, T, S, N, A1, A2)                                   \
    SGC_INIT_S##C(T, S, N) SGC_INIT_##A1(T, N) SGC_INIT_##A2(T, N)

#define SGC_INIT_STATIC7(C, T, S, N, A1, A2, A3)                               \
    SGC_INIT_S##C(T, S, N) SGC_INIT_##A1(T, N) SGC_INIT_##A2(T, N)             \
        SGC_INIT_##A3(T, N)

#define SGC_INIT_STATIC8(C, T, S, N, A1, A2, A3, A4)                           \
    SGC_INIT_S##C(T, S, N) SGC_INIT_##A1(T, N) SGC_INIT_##A2(T, N)             \
        SGC_INIT_##A3(T, N) SGC_INIT_##A4(T, N)

#define SGC_INIT_PAIR_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, NAME, ...) NAME
#define SGC_INIT_PAIR(...)                                                     \
    SGC_INIT_PAIR_N(__VA_ARGS__, SGC_INIT_PAIR9, SGC_INIT_PAIR8,               \
                    SGC_INIT_PAIR7, SGC_INIT_PAIR6, SGC_INIT_PAIR5,            \
                    SGC_INIT_PAIR4)                                            \
    (__VA_ARGS__)

#define SGC_INIT_PAIR4(C, K, V, N) SGC_INIT_##C(K, V, N)

#define SGC_INIT_PAIR5(C, K, V, N, A1) SGC_INIT_##C(K, V, N) SGC_INIT_##A1(V, N)

#define SGC_INIT_PAIR6(C, K, V, N, A1, A2)                                     \
    SGC_INIT_##C(K, V, N) SGC_INIT_##A1(V, N) SGC_INIT_##A2(V, N)

#define SGC_INIT_PAIR7(C, K, V, N, A1, A2, A3)                                 \
    SGC_INIT_##C(K, V, N) SGC_INIT_##A1(V, N) SGC_INIT_##A2(V, N)              \
        SGC_INIT_##A3(V, N)

#define SGC_INIT_PAIR8(C, K, V, N, A1, A2, A3, A4)                             \
    SGC_INIT_##C(K, V, N) SGC_INIT_##A1(V, N) SGC_INIT_##A2(V, N)              \
        SGC_INIT_##A3(V, N) SGC_INIT_##A4(V, N)

#define SGC_INIT_PAIR9(C, K, V, N, A1, A2, A3, A4, A5)                         \
    SGC_INIT_##C(K, V, N) SGC_INIT_##A1(V, N) SGC_INIT_##A2(V, N)              \
        SGC_INIT_##A3(V, N) SGC_INIT_##A4(V, N) SGC_INIT_##A5(V, N)

#define SGC_INIT_SPAIR_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NAME, ...)   \
    NAME
#define SGC_INIT_SPAIR(...)                                                    \
    SGC_INIT_SPAIR_N(__VA_ARGS__, SGC_INIT_SPAIR10, SGC_INIT_SPAIR9,           \
                     SGC_INIT_SPAIR8, SGC_INIT_SPAIR7, SGC_INIT_SPAIR6,        \
                     SGC_INIT_SPAIR5)                                          \
    (__VA_ARGS__)

#define SGC_INIT_SPAIR5(C, K, V, S, N) SGC_INIT_S##C(K, V, S, N)

#define SGC_INIT_SPAIR6(C, K, V, S, N, A1)                                     \
    SGC_INIT_S##C(K, V, S, N) SGC_INIT_##A1(V, N)

#define SGC_INIT_SPAIR7(C, K, V, S, N, A1, A2)                                 \
    SGC_INIT_S##C(K, V, S, N) SGC_INIT_##A1(V, N) SGC_INIT_##A2(V, N)

#define SGC_INIT_SPAIR8(C, K, V, S, N, A1, A2, A3)                             \
    SGC_INIT_S##C(K, V, S, N) SGC_INIT_##A1(V, N) SGC_INIT_##A2(V, N)          \
        SGC_INIT_##A3(V, N)

#define SGC_INIT_SPAIR9(C, K, V, S, N, A1, A2, A3, A4)                         \
    SGC_INIT_S##C(K, V, S, N) SGC_INIT_##A1(V, N) SGC_INIT_##A2(V, N)          \
        SGC_INIT_##A3(V, N) SGC_INIT_##A4(V, N)

#define SGC_INIT_SPAIR10(C, K, V, S, N, A1, A2, A3, A4, A5)                    \
    SGC_INIT_S##C(K, V, S, N) SGC_INIT_##A1(V, N) SGC_INIT_##A2(V, N)          \
        SGC_INIT_##A3(V, N) SGC_INIT_##A4(V, N) SGC_INIT_##A5(V, N)

// TODO update
#define SGC_COPY(COPY_FUN, DST, SRC, IS_SHARED)                                \
    if (!IS_SHARED) {                                                          \
        COPY_FUN(&DST, &SRC);                                                  \
    } else {                                                                   \
        DST = SRC;                                                             \
    }

// TODO update
#define SGC_REPLACE(COPY_FUN, FREE_FUN, DST, SRC, IS_SHARED)                   \
    if (!IS_SHARED) {                                                          \
        FREE_FUN(&DST);                                                        \
        COPY_FUN(&DST, &SRC);                                                  \
    } else {                                                                   \
        DST = SRC;                                                             \
    }

// TODO update
#define SGC_FREE(FREE_FUN, SRC, SHARED)                                        \
    if (!SHARED) {                                                             \
        FREE_FUN(&SRC);                                                        \
    }

#define SGC_ARRAY_COPY(T, DST, SRC, SIZE, SHARED)                              \
    {                                                                          \
        if (!SHARED) {                                                         \
            memcpy(DST, SRC, SIZE * sizeof(T));                                \
        } else {                                                               \
            for (size_t i = 0; i < SIZE; ++i) {                                \
                T##_copy(&DST[i], &SRC[i]);                                    \
            }                                                                  \
        }                                                                      \
    }

#define SGC_ARRAY_FREE(T, SRC, SIZE, SHARED)                                   \
    {                                                                          \
        if (!SHARED) {                                                         \
            for (size_t i = 0; i < SIZE; ++i) {                                \
                T##_free(&SRC[i]);                                             \
            }                                                                  \
        }                                                                      \
    }

#define SGC_TOKENPASTE(x, y) x##y
#define SGC_TOKENPASTE2(x, y) SGC_TOKENPASTE(x, y)
#define SGC_UNIQUE(x) SGC_TOKENPASTE2(__sgc_unique_##x, __LINE__)

#define SGC_NONE() (void*)NULL;

#define SGC_FOR_EACH_N(_1, _2, _3, _4, _5, _6, _7, NAME, ...) NAME
#define sgc_for_each(...)                                                      \
    SGC_FOR_EACH_N(__VA_ARGS__, SGC_NONE, SGC_NONE, SGC_NONE, SGC_NONE,        \
                   SGC_FOR_EACH, )                                             \
    (__VA_ARGS__)

#define SGC_FOR_EACH(EL, C, N)                                                 \
    int SGC_UNIQUE(valid) = 0;                                                 \
    int SGC_UNIQUE(tmp) = 0;                                                   \
    N##_it SGC_UNIQUE(curr) = N##_begin(&C);                                   \
    N##_it SGC_UNIQUE(end) = N##_end(&C);                                      \
    SGC_UNIQUE(valid) =                                                        \
        N##_it_valid(SGC_UNIQUE(curr)) && N##_it_valid(SGC_UNIQUE(end));       \
    for (N##_type* EL = (N##_type*)N##_it_data(SGC_UNIQUE(curr));              \
         SGC_UNIQUE(valid);                                                    \
         SGC_UNIQUE(tmp) = !N##_it_equal(SGC_UNIQUE(curr), SGC_UNIQUE(end)),   \
                   SGC_UNIQUE(valid) = SGC_UNIQUE(tmp),                        \
                   N##_it_go_next(&SGC_UNIQUE(curr)),                          \
                   EL = (N##_type*)N##_it_data(SGC_UNIQUE(curr)))

#define SGC_FOR_EACH_REVERSE_N(_1, _2, _3, _4, _5, _6, _7, NAME, ...) NAME
#define sgc_for_each_reverse(...)                                              \
    SGC_FOR_EACH_REVERSE_N(__VA_ARGS__, SGC_NONE, SGC_NONE, SGC_NONE,          \
                           SGC_NONE, SGC_FOR_EACH_REVERSE, )                   \
    (__VA_ARGS__)

#define SGC_FOR_EACH_REVERSE(EL, C, N)                                         \
    int SGC_UNIQUE(valid) = 0;                                                 \
    int SGC_UNIQUE(tmp) = 0;                                                   \
    N##_it SGC_UNIQUE(curr) = N##_end(&C);                                     \
    N##_it SGC_UNIQUE(begin) = N##_begin(&C);                                  \
    SGC_UNIQUE(valid) =                                                        \
        N##_it_valid(SGC_UNIQUE(curr)) && N##_it_valid(SGC_UNIQUE(begin));     \
    for (N##_type* EL = (N##_type*)N##_it_data(SGC_UNIQUE(curr));              \
         SGC_UNIQUE(valid);                                                    \
         SGC_UNIQUE(tmp) = !N##_it_equal(SGC_UNIQUE(curr), SGC_UNIQUE(begin)), \
                   SGC_UNIQUE(valid) = SGC_UNIQUE(tmp),                        \
                   N##_it_go_prev(&SGC_UNIQUE(curr)),                          \
                   EL = (N##_type*)N##_it_data(SGC_UNIQUE(curr)))

#ifndef SGC_NO_KEYWORDS

#define IN ,
#define AS ,
#define for_each sgc_for_each
#define for_each_reverse sgc_for_each_reverse

#endif
