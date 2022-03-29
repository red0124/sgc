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

#define SGC_INIT_STATIC_N(_1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME
#define SGC_INIT_STATIC(...)                                                   \
    SGC_INIT_STATIC_N(__VA_ARGS__, SGC_INIT_STATIC8, SGC_INIT_STATIC7,         \
                      SGC_INIT_STATIC6, SGC_INIT_STATIC5, SGC_INIT_STATIC4,    \
                      SGC_INIT_STATIC3)                                        \
    (__VA_ARGS__)

#define SGC_INIT_STATIC3(C, S, N) SGC_INIT_STATIC_##C(S, N)

#define SGC_INIT_STATIC4(C, T, S, N) SGC_INIT_STATIC_##C(T, S, N)

#define SGC_INIT_STATIC5(C, T, S, N, A1)                                       \
    SGC_INIT_STATIC_##C(T, S, N) SGC_INIT_##A1(T, N)

#define SGC_INIT_STATIC6(C, T, S, N, A1, A2)                                   \
    SGC_INIT_STATIC_##C(T, S, N) SGC_INIT_##A1(T, N) SGC_INIT_##A2(T, N)

#define SGC_INIT_STATIC7(C, T, S, N, A1, A2, A3)                               \
    SGC_INIT_STATIC_##C(T, S, N) SGC_INIT_##A1(T, N) SGC_INIT_##A2(T, N)       \
        SGC_INIT_##A3(T, N)

#define SGC_INIT_STATIC8(C, T, S, N, A1, A2, A3, A4)                           \
    SGC_INIT_STATIC_##C(T, S, N) SGC_INIT_##A1(T, N) SGC_INIT_##A2(T, N)       \
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

#define SGC_INIT_STATIC_PAIR_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NAME,  \
                               ...)                                            \
    NAME
#define SGC_INIT_STATIC_PAIR(...)                                              \
    SGC_INIT_STATIC_PAIR_N(__VA_ARGS__, SGC_INIT_STATIC_PAIR10,                \
                           SGC_INIT_STATIC_PAIR9, SGC_INIT_STATIC_PAIR8,       \
                           SGC_INIT_STATIC_PAIR7, SGC_INIT_STATIC_PAIR6,       \
                           SGC_INIT_STATIC_PAIR5)                              \
    (__VA_ARGS__)

#define SGC_INIT_STATIC_PAIR5(C, K, V, S, N) SGC_INIT_STATIC_##C(K, V, S, N)

#define SGC_INIT_STATIC_PAIR6(C, K, V, S, N, A1)                               \
    SGC_INIT_STATIC_##C(K, V, S, N) SGC_INIT_##A1(V, N)

#define SGC_INIT_STATIC_PAIR7(C, K, V, S, N, A1, A2)                           \
    SGC_INIT_STATIC_##C(K, V, S, N) SGC_INIT_##A1(V, N) SGC_INIT_##A2(V, N)

#define SGC_INIT_STATIC_PAIR8(C, K, V, S, N, A1, A2, A3)                       \
    SGC_INIT_STATIC_##C(K, V, S, N) SGC_INIT_##A1(V, N) SGC_INIT_##A2(V, N)    \
        SGC_INIT_##A3(V, N)

#define SGC_INIT_STATIC_PAIR9(C, K, V, S, N, A1, A2, A3, A4)                   \
    SGC_INIT_STATIC_##C(K, V, S, N) SGC_INIT_##A1(V, N) SGC_INIT_##A2(V, N)    \
        SGC_INIT_##A3(V, N) SGC_INIT_##A4(V, N)

#define SGC_INIT_STATIC_PAIR10(C, K, V, S, N, A1, A2, A3, A4, A5)              \
    SGC_INIT_STATIC_##C(K, V, S, N) SGC_INIT_##A1(V, N) SGC_INIT_##A2(V, N)    \
        SGC_INIT_##A3(V, N) SGC_INIT_##A4(V, N) SGC_INIT_##A5(V, N)

#define SGC_COPY(COPY_FUN, DST, SRC, IS_SHARED)                                \
    if (!IS_SHARED) {                                                          \
        COPY_FUN(&DST, &SRC);                                                  \
    } else {                                                                   \
        DST = SRC;                                                             \
    }

#define SGC_REPLACE(COPY_FUN, FREE_FUN, DST, SRC, IS_SHARED)                   \
    if (!IS_SHARED) {                                                          \
        FREE_FUN(&DST);                                                        \
        COPY_FUN(&DST, &SRC);                                                  \
    } else {                                                                   \
        DST = SRC;                                                             \
    }

#define SGC_FREE(FREE_FUN, SRC, IS_SHARED)                                     \
    if (!IS_SHARED) {                                                          \
        FREE_FUN(&SRC);                                                        \
    }

#define SGC_TOKENPASTE(x, y) x##y
#define SGC_TOKENPASTE2(x, y) SGC_TOKENPASTE(x, y)
#define SGC_UNIQUE(x) SGC_TOKENPASTE2(__sgc_unique_##x, __LINE__)

#define SGC_NONE() (void*)NULL;

#define SGC_FOR_EACH_N(_1, _2, _3, _4, _5, _6, _7, NAME, ...) NAME
#define sgc_for_each(...)                                                      \
    SGC_FOR_EACH_N(__VA_ARGS__, SGC_FOR_EACH3, SGC_NONE, SGC_FOR_EACH2,        \
                   SGC_FOR_EACH_SAME2, SGC_FOR_EACH1, )                        \
    (__VA_ARGS__)

#define SGC_FOR_EACH1(EL, C, N)                                                \
    int SGC_UNIQUE(valid) = 0;                                                 \
    int SGC_UNIQUE(tmp) = 0;                                                   \
    N##_iterator SGC_UNIQUE(curr) = N##_begin(&C);                             \
    N##_iterator SGC_UNIQUE(end) = N##_end(&C);                                \
    SGC_UNIQUE(valid) = N##_iterator_valid(SGC_UNIQUE(curr)) &&                \
                        N##_iterator_valid(SGC_UNIQUE(end));                   \
    for (N##_type* EL = N##_iterator_data(SGC_UNIQUE(curr));                   \
         SGC_UNIQUE(valid);                                                    \
         SGC_UNIQUE(tmp) =                                                     \
             !N##_iterator_equal(SGC_UNIQUE(curr), SGC_UNIQUE(end)),           \
                   SGC_UNIQUE(valid) = SGC_UNIQUE(tmp),                        \
                   N##_iterator_next(&SGC_UNIQUE(curr)),                       \
                   EL = N##_iterator_data(SGC_UNIQUE(curr)))

#define SGC_FOR_EACH_SAME2(EL, C1, C2, N) SGC_FOR_EACH2(EL, C1, N, C2, N)

#define SGC_FOR_EACH2(EL, C1, N1, C2, N2)                                      \
    int SGC_UNIQUE(valid1) = 0;                                                \
    int SGC_UNIQUE(tmp1) = 0;                                                  \
    int SGC_UNIQUE(valid2) = 0;                                                \
    int SGC_UNIQUE(tmp2) = 0;                                                  \
    N1##_iterator SGC_UNIQUE(curr1) = N1##_begin(&C1);                         \
    N1##_iterator SGC_UNIQUE(end1) = N1##_end(&C1);                            \
    N2##_iterator SGC_UNIQUE(curr2) = N2##_begin(&C2);                         \
    N2##_iterator SGC_UNIQUE(end2) = N2##_end(&C2);                            \
    SGC_UNIQUE(valid1) = N1##_iterator_valid(SGC_UNIQUE(curr1)) &&             \
                         N1##_iterator_valid(SGC_UNIQUE(end1));                \
    SGC_UNIQUE(valid2) = N2##_iterator_valid(SGC_UNIQUE(curr2)) &&             \
                         N2##_iterator_valid(SGC_UNIQUE(end2));                \
    struct SGC_UNIQUE(pair) {                                                  \
        N1##_type* first;                                                      \
        N2##_type* second;                                                     \
    };                                                                         \
    for (struct SGC_UNIQUE(pair)                                               \
             EL = {N1##_iterator_data(SGC_UNIQUE(curr1)),                      \
                   N2##_iterator_data(SGC_UNIQUE(curr2))};                     \
         SGC_UNIQUE(valid1) && SGC_UNIQUE(valid2);                             \
         SGC_UNIQUE(tmp1) =                                                    \
             !N1##_iterator_equal(SGC_UNIQUE(curr1), SGC_UNIQUE(end1)),        \
             SGC_UNIQUE(tmp2) =                                                \
                 !N2##_iterator_equal(SGC_UNIQUE(curr2), SGC_UNIQUE(end2)),    \
             SGC_UNIQUE(valid1) = SGC_UNIQUE(tmp1),                            \
             SGC_UNIQUE(valid2) = SGC_UNIQUE(tmp2),                            \
             N1##_iterator_next(&SGC_UNIQUE(curr1)),                           \
             N2##_iterator_next(&SGC_UNIQUE(curr2)),                           \
             EL = (struct SGC_UNIQUE(                                          \
                 pair)){N1##_iterator_data(SGC_UNIQUE(curr1)),                 \
                        N2##_iterator_data(SGC_UNIQUE(curr2))})

#define SGC_FOR_EACH3(EL, C1, N1, C2, N2, C3, N3)                              \
    int SGC_UNIQUE(valid1) = 0;                                                \
    int SGC_UNIQUE(tmp1) = 0;                                                  \
    int SGC_UNIQUE(valid2) = 0;                                                \
    int SGC_UNIQUE(tmp2) = 0;                                                  \
    int SGC_UNIQUE(valid3) = 0;                                                \
    int SGC_UNIQUE(tmp3) = 0;                                                  \
    N1##_iterator SGC_UNIQUE(curr1) = N1##_begin(&C1);                         \
    N1##_iterator SGC_UNIQUE(end1) = N1##_end(&C1);                            \
    N2##_iterator SGC_UNIQUE(curr2) = N2##_begin(&C2);                         \
    N2##_iterator SGC_UNIQUE(end2) = N2##_end(&C2);                            \
    N3##_iterator SGC_UNIQUE(curr3) = N3##_begin(&C3);                         \
    N3##_iterator SGC_UNIQUE(end3) = N3##_end(&C3);                            \
    SGC_UNIQUE(valid1) = N1##_iterator_valid(SGC_UNIQUE(curr1)) &&             \
                         N1##_iterator_valid(SGC_UNIQUE(end1));                \
    SGC_UNIQUE(valid2) = N2##_iterator_valid(SGC_UNIQUE(curr2)) &&             \
                         N2##_iterator_valid(SGC_UNIQUE(end2));                \
    SGC_UNIQUE(valid3) = N3##_iterator_valid(SGC_UNIQUE(curr3)) &&             \
                         N3##_iterator_valid(SGC_UNIQUE(end3));                \
    struct SGC_UNIQUE(pair) {                                                  \
        N1##_type* first;                                                      \
        N2##_type* second;                                                     \
        N3##_type* third;                                                      \
    };                                                                         \
    for (struct SGC_UNIQUE(pair)                                               \
             EL = {N1##_iterator_data(SGC_UNIQUE(curr1)),                      \
                   N2##_iterator_data(SGC_UNIQUE(curr2)),                      \
                   N3##_iterator_data(SGC_UNIQUE(curr3))};                     \
         SGC_UNIQUE(valid1) && SGC_UNIQUE(valid2) && SGC_UNIQUE(valid3);       \
         SGC_UNIQUE(tmp1) =                                                    \
             !N1##_iterator_equal(SGC_UNIQUE(curr1), SGC_UNIQUE(end1)),        \
             SGC_UNIQUE(tmp2) =                                                \
                 !N2##_iterator_equal(SGC_UNIQUE(curr2), SGC_UNIQUE(end2)),    \
             SGC_UNIQUE(tmp3) =                                                \
                 !N3##_iterator_equal(SGC_UNIQUE(curr3), SGC_UNIQUE(end3)),    \
             SGC_UNIQUE(valid1) = SGC_UNIQUE(tmp1),                            \
             SGC_UNIQUE(valid2) = SGC_UNIQUE(tmp2),                            \
             SGC_UNIQUE(valid3) = SGC_UNIQUE(tmp3),                            \
             N1##_iterator_next(&SGC_UNIQUE(curr1)),                           \
             N2##_iterator_next(&SGC_UNIQUE(curr2)),                           \
             N3##_iterator_next(&SGC_UNIQUE(curr3)),                           \
             EL = (struct SGC_UNIQUE(                                          \
                 pair)){N1##_iterator_data(SGC_UNIQUE(curr1)),                 \
                        N2##_iterator_data(SGC_UNIQUE(curr2)),                 \
                        N3##_iterator_data(SGC_UNIQUE(curr3))})

#define SGC_FOR_EACH_REVERSE_N(_1, _2, _3, _4, _5, _6, _7, NAME, ...) NAME
#define sgc_for_each_reverse(...)                                              \
    SGC_FOR_EACH_REVERSE_N(__VA_ARGS__, SGC_FOR_EACH_REVERSE3,                 \
                           SGC_FOR_EACH_SAME_REVERSE2, SGC_FOR_EACH_REVERSE2,  \
                           SGC_NONE, SGC_FOR_EACH_REVERSE1)                    \
    (__VA_ARGS__)

#define SGC_FOR_EACH_REVERSE(EL, C, N)                                         \
    int SGC_UNIQUE(valid) = 0;                                                 \
    int SGC_UNIQUE(tmp) = 0;                                                   \
    N##_iterator SGC_UNIQUE(curr) = N##_end(&C);                               \
    N##_iterator SGC_UNIQUE(begin) = N##_begin(&C);                            \
    SGC_UNIQUE(valid) = N##_iterator_valid(SGC_UNIQUE(curr)) &&                \
                        N##_iterator_valid(SGC_UNIQUE(begin));                 \
    for (N##_type* EL = N##_iterator_data(SGC_UNIQUE(curr));                   \
         SGC_UNIQUE(valid);                                                    \
         SGC_UNIQUE(tmp) =                                                     \
             !N##_iterator_equal(SGC_UNIQUE(curr), SGC_UNIQUE(begin)),         \
                   SGC_UNIQUE(valid) = SGC_UNIQUE(tmp),                        \
                   N##_iterator_prev(&SGC_UNIQUE(curr)),                       \
                   EL = N##_iterator_data(SGC_UNIQUE(curr)))

#define SGC_FOR_EACH_SAME_REVERSE2(EL, C1, C2, N)                              \
    SGC_FOR_EACH_REVERSE2(EL, C1, N, C2, N)

#define SGC_FOR_EACH_REVERSE2(EL, C1, N1, C2, N2)                              \
    int SGC_UNIQUE(valid1) = 0;                                                \
    int SGC_UNIQUE(tmp1) = 0;                                                  \
    int SGC_UNIQUE(valid2) = 0;                                                \
    int SGC_UNIQUE(tmp2) = 0;                                                  \
    N1##_iterator SGC_UNIQUE(curr1) = N1##_end(&C1);                           \
    N1##_iterator SGC_UNIQUE(begin1) = N1##_begin(&C1);                        \
    N2##_iterator SGC_UNIQUE(curr2) = N2##_end(&C2);                           \
    N2##_iterator SGC_UNIQUE(begin2) = N2##_begin(&C2);                        \
    SGC_UNIQUE(valid1) = N1##_iterator_valid(SGC_UNIQUE(curr1)) &&             \
                         N1##_iterator_valid(SGC_UNIQUE(begin1));              \
    SGC_UNIQUE(valid2) = N2##_iterator_valid(SGC_UNIQUE(curr2)) &&             \
                         N2##_iterator_valid(SGC_UNIQUE(begin2));              \
    struct SGC_UNIQUE(pair) {                                                  \
        N1##_type* first;                                                      \
        N2##_type* second;                                                     \
    };                                                                         \
    for (struct SGC_UNIQUE(pair)                                               \
             EL = {N1##_iterator_data(SGC_UNIQUE(curr1)),                      \
                   N2##_iterator_data(SGC_UNIQUE(curr2))};                     \
         SGC_UNIQUE(valid1) && SGC_UNIQUE(valid2);                             \
         SGC_UNIQUE(tmp1) =                                                    \
             !N1##_iterator_equal(SGC_UNIQUE(curr1), SGC_UNIQUE(begin1)),      \
             SGC_UNIQUE(tmp2) =                                                \
                 !N2##_iterator_equal(SGC_UNIQUE(curr2), SGC_UNIQUE(begin2)),  \
             SGC_UNIQUE(valid1) = SGC_UNIQUE(tmp1),                            \
             SGC_UNIQUE(valid2) = SGC_UNIQUE(tmp2),                            \
             N1##_iterator_prev(&SGC_UNIQUE(curr1)),                           \
             N2##_iterator_prev(&SGC_UNIQUE(curr2)),                           \
             EL = (struct SGC_UNIQUE(                                          \
                 pair)){N1##_iterator_data(SGC_UNIQUE(curr1)),                 \
                        N2##_iterator_data(SGC_UNIQUE(curr2))})

#define SGC_FOR_EACH_REVERSE3(EL, C1, N1, C2, N2, C3, N3)                      \
    int SGC_UNIQUE(valid1) = 0;                                                \
    int SGC_UNIQUE(tmp1) = 0;                                                  \
    int SGC_UNIQUE(valid2) = 0;                                                \
    int SGC_UNIQUE(tmp2) = 0;                                                  \
    int SGC_UNIQUE(valid3) = 0;                                                \
    int SGC_UNIQUE(tmp3) = 0;                                                  \
    N1##_iterator SGC_UNIQUE(curr1) = N1##_end(&C1);                           \
    N1##_iterator SGC_UNIQUE(begin1) = N1##_begin(&C1);                        \
    N2##_iterator SGC_UNIQUE(curr2) = N2##_end(&C2);                           \
    N2##_iterator SGC_UNIQUE(begin2) = N2##_begin(&C2);                        \
    N3##_iterator SGC_UNIQUE(curr3) = N3##_end(&C3);                           \
    N3##_iterator SGC_UNIQUE(begin3) = N3##_begin(&C3);                        \
    SGC_UNIQUE(valid1) = N1##_iterator_valid(SGC_UNIQUE(curr1)) &&             \
                         N1##_iterator_valid(SGC_UNIQUE(begin1));              \
    SGC_UNIQUE(valid2) = N2##_iterator_valid(SGC_UNIQUE(curr2)) &&             \
                         N2##_iterator_valid(SGC_UNIQUE(begin2));              \
    SGC_UNIQUE(valid3) = N3##_iterator_valid(SGC_UNIQUE(curr3)) &&             \
                         N3##_iterator_valid(SGC_UNIQUE(begin3));              \
    struct SGC_UNIQUE(pair) {                                                  \
        N1##_type* first;                                                      \
        N2##_type* second;                                                     \
        N3##_type* third;                                                      \
    };                                                                         \
    for (struct SGC_UNIQUE(pair)                                               \
             EL = {N1##_iterator_data(SGC_UNIQUE(curr1)),                      \
                   N2##_iterator_data(SGC_UNIQUE(curr2)),                      \
                   N3##_iterator_data(SGC_UNIQUE(curr3))};                     \
         SGC_UNIQUE(valid1) && SGC_UNIQUE(valid2) && SGC_UNIQUE(valid3);       \
         SGC_UNIQUE(tmp1) =                                                    \
             !N1##_iterator_equal(SGC_UNIQUE(curr1), SGC_UNIQUE(begin1)),      \
             SGC_UNIQUE(tmp2) =                                                \
                 !N2##_iterator_equal(SGC_UNIQUE(curr2), SGC_UNIQUE(begin2)),  \
             SGC_UNIQUE(tmp3) =                                                \
                 !N3##_iterator_equal(SGC_UNIQUE(curr3), SGC_UNIQUE(begin3)),  \
             SGC_UNIQUE(valid1) = SGC_UNIQUE(tmp1),                            \
             SGC_UNIQUE(valid2) = SGC_UNIQUE(tmp2),                            \
             SGC_UNIQUE(valid3) = SGC_UNIQUE(tmp3),                            \
             N1##_iterator_prev(&SGC_UNIQUE(curr1)),                           \
             N2##_iterator_prev(&SGC_UNIQUE(curr2)),                           \
             N3##_iterator_prev(&SGC_UNIQUE(curr3)),                           \
             EL = (struct SGC_UNIQUE(                                          \
                 pair)){N1##_iterator_data(SGC_UNIQUE(curr1)),                 \
                        N2##_iterator_data(SGC_UNIQUE(curr2)),                 \
                        N3##_iterator_data(SGC_UNIQUE(curr3))})

#define SGC_FOR_EACH_INTERSECT_N(_1, _2, _3, _4, _5, NAME, ...) NAME
#define sgc_for_each_intersect(...)                                            \
    SGC_FOR_EACH_INTERSECT_N(__VA_ARGS__, sgc_for_each_intersect1,             \
                             SGC_FOR_EACH_SAME_INTERSECT, SGC_NONE)            \
    (__VA_ARGS__)

#define SGC_FOR_EACH_SAME_INTERSECT(EL, C1, C2, N)                             \
    sgc_for_each_intersect1(EL, C1, N, C2, N)

#define sgc_for_each_intersect1(EL, C1, N1, C2, N2)                            \
    int SGC_UNIQUE(valid1) = 0;                                                \
    int SGC_UNIQUE(tmp1) = 0;                                                  \
    int SGC_UNIQUE(valid2) = 0;                                                \
    int SGC_UNIQUE(tmp2) = 0;                                                  \
    N1##_iterator SGC_UNIQUE(curr1) = N1##_begin(&C1);                         \
    N1##_iterator SGC_UNIQUE(end1) = N1##_end(&C1);                            \
    N2##_iterator SGC_UNIQUE(curr2) = N2##_end(&C2);                           \
    N2##_iterator SGC_UNIQUE(begin2) = N2##_begin(&C2);                        \
    SGC_UNIQUE(valid1) = N1##_iterator_valid(SGC_UNIQUE(curr1)) &&             \
                         N1##_iterator_valid(SGC_UNIQUE(end1));                \
    SGC_UNIQUE(valid2) = N2##_iterator_valid(SGC_UNIQUE(curr2)) &&             \
                         N2##_iterator_valid(SGC_UNIQUE(begin2));              \
    struct SGC_UNIQUE(pair) {                                                  \
        N1##_type* first;                                                      \
        N2##_type* second;                                                     \
    };                                                                         \
    for (struct SGC_UNIQUE(pair)                                               \
             EL = {N1##_iterator_data(SGC_UNIQUE(curr1)),                      \
                   N2##_iterator_data(SGC_UNIQUE(curr2))};                     \
         SGC_UNIQUE(valid1) && SGC_UNIQUE(valid2);                             \
         SGC_UNIQUE(tmp1) =                                                    \
             !N1##_iterator_equal(SGC_UNIQUE(curr1), SGC_UNIQUE(end1)),        \
             SGC_UNIQUE(tmp2) =                                                \
                 !N2##_iterator_equal(SGC_UNIQUE(curr2), SGC_UNIQUE(begin2)),  \
             SGC_UNIQUE(valid1) = SGC_UNIQUE(tmp1),                            \
             SGC_UNIQUE(valid2) = SGC_UNIQUE(tmp2),                            \
             N1##_iterator_next(&SGC_UNIQUE(curr1)),                           \
             N2##_iterator_prev(&SGC_UNIQUE(curr2)),                           \
             EL = (struct SGC_UNIQUE(                                          \
                 pair)){N1##_iterator_data(SGC_UNIQUE(curr1)),                 \
                        N2##_iterator_data(SGC_UNIQUE(curr2))})

#ifndef SGC_NO_KEYWORDS

#define in ,
#define as ,
#define for_each sgc_for_each
#define for_each_reverse sgc_for_each_reverse
#define for_eachr sgc_for_each_reverse
#define for_each_intersect sgc_for_each_intersect
#define for_eachi sgc_for_each_intersect
#define fore sgc_for_each
#define fori sgc_for_each_intersect
#define forr sgc_for_each_reverse

#endif
