#pragma once

#pragma once

#define SGC_INIT_HEADERS_N(_1, _2, _3, _4, _5, _6, _7, NAME, ...) NAME
#define SGC_INIT_HEADER(...)                                                   \
        SGC_INIT_HEADERS_N(__VA_ARGS__, SGC_INIT_HEADER7, SGC_INIT_HEADER6,    \
                           SGC_INIT_HEADER5, SGC_INIT_HEADER4,                 \
                           SGC_INIT_HEADER3)                                   \
        (__VA_ARGS__)

#define SGC_INIT_HEADER3(C, T, N) SGC_INIT_HEADERS_##C(T, N);

#define SGC_INIT_HEADER4(C, T, N, A1)                                          \
        SGC_INIT_HEADERS_##C(T, N);                                            \
        SGC_INIT_HEADERS_##A1(T, N);

#define SGC_INIT_HEADER5(C, T, N, A1, A2)                                      \
        SGC_INIT_HEADERS_##C(T, N);                                            \
        SGC_INIT_HEADERS_##A1(T, N);                                           \
        SGC_INIT_HEADERS_##A2(T, N);

#define SGC_INIT_HEADER6(C, T, N, A1, A2, A3)                                  \
        SGC_INIT_HEADERS_##C(T, N);                                            \
        SGC_INIT_HEADERS_##A1(T, N);                                           \
        SGC_INIT_HEADERS_##A2(T, N);                                           \
        SGC_INIT_HEADERS_##A3(T, N);

#define SGC_INIT_HEADER7(C, T, N, A1, A2, A3, A4)                              \
        SGC_INIT_HEADERS_##C(T, N);                                            \
        SGC_INIT_HEADERS_##A1(T, N);                                           \
        SGC_INIT_HEADERS_##A2(T, N);                                           \
        SGC_INIT_HEADERS_##A3(T, N);                                           \
        SGC_INIT_HEADERS_##A4(T, N);

#define SGC_INIT_HEADERS_PAIR_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, NAME, ...) \
        NAME

#define SGC_INIT_HEADERS_PAIR(...)                                             \
        SGC_INIT_HEADERS_PAIR_N(                                               \
            __VA_ARGS__, SGC_INIT_HEADERS_PAIR9, SGC_INIT_HEADERS_PAIR8,       \
            SGC_INIT_HEADERS_PAIR7, SGC_INIT_HEADERS_PAIR6,                    \
            SGC_INIT_HEADERS_PAIR5, SGC_INIT_HEADERS_PAIR4)                    \
        (__VA_ARGS__)

#define SGC_INIT_HEADERS_PAIR4(C, K, V, N) SGC_INIT_HEADERS_##C(K, V, N);

#define SGC_INIT_HEADERS_PAIR5(C, K, V, N, A1)                                 \
        SGC_INIT_HEADERS_##C(K, V, N);                                         \
        SGC_INIT_HEADERS_##A1(V, N);

#define SGC_INIT_HEADERS_PAIR6(C, K, V, N, A1, A2)                             \
        SGC_INIT_HEADERS_##C(K, V, N);                                         \
        SGC_INIT_HEADERS_##A1(V, N);                                           \
        SGC_INIT_HEADERS_##A2(V, N);

#define SGC_INIT_HEADERS_PAIR7(C, K, V, N, A1, A2, A3)                         \
        SGC_INIT_HEADERS_##C(K, V, N);                                         \
        SGC_INIT_HEADERS_##A1(V, N);                                           \
        SGC_INIT_HEADERS_##A2(V, N);                                           \
        SGC_INIT_HEADERS_##A3(V, N);

#define SGC_INIT_HEADERS_PAIR8(C, K, V, N, A1, A2, A3, A4)                     \
        SGC_INIT_HEADERS_##C(K, V, N);                                         \
        SGC_INIT_HEADERS_##A1(V, N);                                           \
        SGC_INIT_HEADERS_##A2(V, N);                                           \
        SGC_INIT_HEADERS_##A3(V, N);                                           \
        SGC_INIT_HEADERS_##A4(V, N);

#define SGC_INIT_HEADERS_PAIR9(C, K, V, N, A1, A2, A3, A4, A5)                 \
        SGC_INIT_HEADERS_##C(K, V, N);                                         \
        SGC_INIT_HEADERS_##A1(V, N);                                           \
        SGC_INIT_HEADERS_##A2(V, N);                                           \
        SGC_INIT_HEADERS_##A3(V, N);                                           \
        SGC_INIT_HEADERS_##A4(V, N);                                           \
        SGC_INIT_HEADERS_##A5(V, N);

#define SGC_INIT_HEADERS_ITERATE(T, N)                                         \
        void N##_fold_range(                                                   \
            struct N##_iterator begin, struct N##_iterator end,                \
            void (*fun)(const N##_type *const, void *), void *argout);         \
                                                                               \
        void N##_fold(const struct N *const c,                                 \
                      void (*fun)(const N##_type *const, void *),              \
                      void *argout);                                           \
                                                                               \
        void N##_execute_range(struct N##_iterator begin,                      \
                               struct N##_iterator end,                        \
                               void (*fun)(const N##_type *const));            \
                                                                               \
        void N##_execute(const struct N *const c,                              \
                         void (*fun)(const N##_type *const));                  \
                                                                               \
        void N##_fprintf_range(struct N##_iterator begin,                      \
                               struct N##_iterator end,                        \
                               const char *const format, FILE *file);          \
                                                                               \
        void N##_fprintf(const struct N *const c, const char *const format,    \
                         FILE *file);                                          \
                                                                               \
        void N##_fold_range_reverse(                                           \
            struct N##_iterator begin, struct N##_iterator end,                \
            void (*fun)(const N##_type *const, void *), void *argout);         \
                                                                               \
        void N##_fold_reverse(const struct N *const c,                         \
                              void (*fun)(const N##_type *const, void *),      \
                              void *argout);                                   \
                                                                               \
        void N##_execute_range_reverse(struct N##_iterator begin,              \
                                       struct N##_iterator end,                \
                                       void (*fun)(const N##_type *const));    \
                                                                               \
        void N##_execute_reverse(const struct N *const c,                      \
                                 void (*fun)(const N##_type *const));          \
                                                                               \
        void N##_fprintf_range_reverse(struct N##_iterator begin,              \
                                       struct N##_iterator end,                \
                                       const char *const format, FILE *file);  \
                                                                               \
        void N##_fprintf_reverse(const struct N *const c,                      \
                                 const char *const format, FILE *file);

#define SGC_INIT_HEADERS_FIND(T, N)                                            \
        N##_type *N##_find_el_range(struct N##_iterator begin,                 \
                                    struct N##_iterator end,                   \
                                    const N##_type el);                        \
                                                                               \
        N##_type *N##_find_el(const struct N *const c, const N##_type el);     \
                                                                               \
        ssize_t N##_find_index(const struct N *const c, const N##_type el);    \
                                                                               \
        size_t N##_count(const N *const c, const N##_type el);

#define SGC_INIT_HEADERS_FIND_ITERATOR(T, N)                                   \
        struct N##_iterator N##_find_range(struct N##_iterator begin,          \
                                           struct N##_iterator end,            \
                                           const N##_type el);                 \
                                                                               \
        struct N##_iterator N##_find(const struct N *const c,                  \
                                     const N##_type el);

#define SGC_INIT_HEADERS_BINARY_FIND(T, N)                                     \
        N##_type *N##_binary_find_el(struct N *c, const N##_type el);          \
                                                                               \
        size_t N##_binary_find_index(struct N *c, const N##_type el);

#define SGC_INIT_HEADERS_ITERATE_PAIR(V, N)                                    \
                                                                               \
        void N##_fprintf_range_pair(struct N##_iterator begin,                 \
                                    struct N##_iterator end,                   \
                                    const char *const format, FILE *file);     \
                                                                               \
        void N##_fprintf_pair(const struct N *const c,                         \
                              const char *const format, FILE *file);           \
                                                                               \
        void N##_fprintf_range_reverse_pair(                                   \
            struct N##_iterator begin, struct N##_iterator end,                \
            const char *const format, FILE *file);                             \
                                                                               \
        void N##_fprintf_reverse_pair(const struct N *const c,                 \
                                      const char *const format, FILE *file);

#define SGC_INIT_STATIC_FUNCTIONS_QSORT(T, N)                                  \
        static void N##_memswp(char *i, char *j);                              \
        static void N##_qsort(void *array, size_t array_size,                  \
                              int (*comp)(const void *, const void *));

#define SGC_INIT_HEADERS_QSORT(T, N)                                           \
        void N##_sort(N *c, int (*comp)(const void *, const void *));

#define SGC_INIT_N(_1, _2, _3, _4, _5, _6, _7, NAME, ...) NAME
#define SGC_INIT(...)                                                          \
        SGC_INIT_N(__VA_ARGS__, SGC_INIT7, SGC_INIT6, SGC_INIT5, SGC_INIT4,    \
                   SGC_INIT3, SGC_INIT2)                                       \
        (__VA_ARGS__)

#define SGC_INIT2(C, N) SGC_INIT_##C(N);

#define SGC_INIT3(C, T, N) SGC_INIT_##C(T, N);

#define SGC_INIT4(C, T, N, A1)                                                 \
        SGC_INIT_##C(T, N);                                                    \
        SGC_INIT_##A1(T, N);

#define SGC_INIT5(C, T, N, A1, A2)                                             \
        SGC_INIT_##C(T, N);                                                    \
        SGC_INIT_##A1(T, N);                                                   \
        SGC_INIT_##A2(T, N);

#define SGC_INIT6(C, T, N, A1, A2, A3)                                         \
        SGC_INIT_##C(T, N);                                                    \
        SGC_INIT_##A1(T, N);                                                   \
        SGC_INIT_##A2(T, N);                                                   \
        SGC_INIT_##A3(T, N);

#define SGC_INIT7(C, T, N, A1, A2, A3, A4)                                     \
        SGC_INIT_##C(T, N);                                                    \
        SGC_INIT_##A1(T, N);                                                   \
        SGC_INIT_##A2(T, N);                                                   \
        SGC_INIT_##A3(T, N);                                                   \
        SGC_INIT_##A4(T, N);

#define SGC_INIT_STATIC_N(_1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME
#define SGC_INIT_STATIC(...)                                                   \
        SGC_INIT_STATIC_N(__VA_ARGS__, SGC_INIT_STATIC8, SGC_INIT_STATIC7,     \
                          SGC_INIT_STATIC6, SGC_INIT_STATIC5,                  \
                          SGC_INIT_STATIC4, SGC_INIT_STATIC3)                  \
        (__VA_ARGS__)

#define SGC_INIT_STATIC3(C, S, N) SGC_INIT_STATIC_##C(S, N);

#define SGC_INIT_STATIC4(C, T, S, N) SGC_INIT_STATIC_##C(T, S, N);

#define SGC_INIT_STATIC5(C, T, S, N, A1)                                       \
        SGC_INIT_STATIC_##C(T, S, N);                                          \
        SGC_INIT_##A1(T, N);

#define SGC_INIT_STATIC6(C, T, S, N, A1, A2)                                   \
        SGC_INIT_STATIC_##C(T, S, N);                                          \
        SGC_INIT_##A1(T, N);                                                   \
        SGC_INIT_##A2(T, N);

#define SGC_INIT_STATIC7(C, T, S, N, A1, A2, A3)                               \
        SGC_INIT_STATIC_##C(T, S, N);                                          \
        SGC_INIT_##A1(T, N);                                                   \
        SGC_INIT_##A2(T, N);                                                   \
        SGC_INIT_##A3(T, N);

#define SGC_INIT_STATIC8(C, T, S, N, A1, A2, A3, A4)                           \
        SGC_INIT_STATIC_##C(T, S, N);                                          \
        SGC_INIT_##A1(T, N);                                                   \
        SGC_INIT_##A2(T, N);                                                   \
        SGC_INIT_##A3(T, N);                                                   \
        SGC_INIT_##A4(T, N);

#define SGC_INIT_PAIR_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, NAME, ...) NAME
#define SGC_INIT_PAIR(...)                                                     \
        SGC_INIT_PAIR_N(__VA_ARGS__, SGC_INIT_PAIR9, SGC_INIT_PAIR8,           \
                        SGC_INIT_PAIR7, SGC_INIT_PAIR6, SGC_INIT_PAIR5,        \
                        SGC_INIT_PAIR4)                                        \
        (__VA_ARGS__)

#define SGC_INIT_PAIR4(C, K, V, N) SGC_INIT_##C(K, V, N);

#define SGC_INIT_PAIR5(C, K, V, N, A1)                                         \
        SGC_INIT_##C(K, V, N);                                                 \
        SGC_INIT_##A1(V, N);

#define SGC_INIT_PAIR6(C, K, V, N, A1, A2)                                     \
        SGC_INIT_##C(K, V, N);                                                 \
        SGC_INIT_##A1(V, N);                                                   \
        SGC_INIT_##A2(V, N);

#define SGC_INIT_PAIR7(C, K, V, N, A1, A2, A3)                                 \
        SGC_INIT_##C(K, V, N);                                                 \
        SGC_INIT_##A1(V, N);                                                   \
        SGC_INIT_##A2(V, N);                                                   \
        SGC_INIT_##A3(V, N);

#define SGC_INIT_PAIR8(C, K, V, N, A1, A2, A3, A4)                             \
        SGC_INIT_##C(K, V, N);                                                 \
        SGC_INIT_##A1(V, N);                                                   \
        SGC_INIT_##A2(V, N);                                                   \
        SGC_INIT_##A3(V, N);                                                   \
        SGC_INIT_##A4(V, N);

#define SGC_INIT_PAIR9(C, K, V, N, A1, A2, A3, A4, A5)                         \
        SGC_INIT_##C(K, V, N);                                                 \
        SGC_INIT_##A1(V, N);                                                   \
        SGC_INIT_##A2(V, N);                                                   \
        SGC_INIT_##A3(V, N);                                                   \
        SGC_INIT_##A4(V, N);                                                   \
        SGC_INIT_##A5(V, N);

#define SGC_INIT_STATIC_PAIR_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NAME,  \
                               ...)                                            \
        NAME
#define SGC_INIT_STATIC_PAIR(...)                                              \
        SGC_INIT_STATIC_PAIR_N(__VA_ARGS__, SGC_INIT_STATIC_PAIR10,            \
                               SGC_INIT_STATIC_PAIR9, SGC_INIT_STATIC_PAIR8,   \
                               SGC_INIT_STATIC_PAIR7, SGC_INIT_STATIC_PAIR6,   \
                               SGC_INIT_STATIC_PAIR5)                          \
        (__VA_ARGS__)

#define SGC_INIT_STATIC_PAIR5(C, K, V, S, N) SGC_INIT_STATIC_##C(K, V, S, N);

#define SGC_INIT_STATIC_PAIR6(C, K, V, S, N, A1)                               \
        SGC_INIT_STATIC_##C(K, V, S, N);                                       \
        SGC_INIT_##A1(V, N);

#define SGC_INIT_STATIC_PAIR7(C, K, V, S, N, A1, A2)                           \
        SGC_INIT_STATIC_##C(K, V, S, N);                                       \
        SGC_INIT_##A1(V, N);                                                   \
        SGC_INIT_##A2(V, N);

#define SGC_INIT_STATIC_PAIR8(C, K, V, S, N, A1, A2, A3)                       \
        SGC_INIT_STATIC_##C(K, V, S, N);                                       \
        SGC_INIT_##A1(V, N);                                                   \
        SGC_INIT_##A2(V, N);                                                   \
        SGC_INIT_##A3(V, N);

#define SGC_INIT_STATIC_PAIR9(C, K, V, S, N, A1, A2, A3, A4)                   \
        SGC_INIT_STATIC_##C(K, V, S, N);                                       \
        SGC_INIT_##A1(V, N);                                                   \
        SGC_INIT_##A2(V, N);                                                   \
        SGC_INIT_##A3(V, N);                                                   \
        SGC_INIT_##A4(V, N);

#define SGC_INIT_STATIC_PAIR10(C, K, V, S, N, A1, A2, A3, A4, A5)              \
        SGC_INIT_STATIC_##C(K, V, S, N);                                       \
        SGC_INIT_##A1(V, N);                                                   \
        SGC_INIT_##A2(V, N);                                                   \
        SGC_INIT_##A3(V, N);                                                   \
        SGC_INIT_##A4(V, N);                                                   \
        SGC_INIT_##A5(V, N);

#define SGC_INIT_ITERATE(T, N)                                                 \
        SGC_INIT_HEADERS_ITERATE(T, N);                                        \
        void N##_fold_range(                                                   \
            struct N##_iterator begin, struct N##_iterator end,                \
            void (*fun)(const N##_type *const, void *), void *argout)          \
        {                                                                      \
                if(!N##_iterator_valid(begin) || !N##_iterator_valid(end))     \
                {                                                              \
                        return;                                                \
                }                                                              \
                fun(N##_iterator_data(begin), argout);                         \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_next(&begin);                             \
                        fun(N##_iterator_data(begin), argout);                 \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_fold(const N *const c,                                        \
                      void (*fun)(const N##_type *const, void *),              \
                      void *argout)                                            \
        {                                                                      \
                N##_fold_range(N##_cbegin(c), N##_cend(c), fun, argout);       \
        }                                                                      \
                                                                               \
        void N##_execute_range(struct N##_iterator begin,                      \
                               struct N##_iterator end,                        \
                               void (*fun)(const N##_type *const))             \
        {                                                                      \
                if(!N##_iterator_valid(begin) || !N##_iterator_valid(end))     \
                {                                                              \
                        return;                                                \
                }                                                              \
                fun(N##_iterator_data(begin));                                 \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_next(&begin);                             \
                        fun(N##_iterator_data(begin));                         \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_execute(const N *const c, void (*fun)(const N##_type *const)) \
        {                                                                      \
                N##_execute_range(N##_cbegin(c), N##_cend(c), fun);            \
        }                                                                      \
                                                                               \
        void N##_fprintf_range(struct N##_iterator begin,                      \
                               struct N##_iterator end,                        \
                               const char *const format, FILE *file)           \
        {                                                                      \
                if(!N##_iterator_valid(begin) || !N##_iterator_valid(end))     \
                {                                                              \
                        return;                                                \
                }                                                              \
                fprintf(file, format, *N##_iterator_data(begin));              \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_next(&begin);                             \
                        fprintf(file, format, *N##_iterator_data(begin));      \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_fprintf(const N *const c, const char *const format,           \
                         FILE *file)                                           \
        {                                                                      \
                N##_fprintf_range(N##_cbegin(c), N##_cend(c), format, file);   \
        }                                                                      \
                                                                               \
        void N##_sprintf_range(struct N##_iterator begin,                      \
                               struct N##_iterator end,                        \
                               const char *const format, char *buff)           \
        {                                                                      \
                if(!N##_iterator_valid(begin) || !N##_iterator_valid(end))     \
                {                                                              \
                        return;                                                \
                }                                                              \
                sprintf(buff, format, *N##_iterator_data(begin));              \
                buff += strlen(buff);                                          \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_next(&begin);                             \
                        sprintf(buff, format, *N##_iterator_data(begin));      \
                        buff += strlen(buff);                                  \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_sprintf(const N *const c, const char *const format,           \
                         char *buff)                                           \
        {                                                                      \
                N##_sprintf_range(N##_cbegin(c), N##_cend(c), format, buff);   \
        }                                                                      \
                                                                               \
        void N##_fold_range_reverse(                                           \
            struct N##_iterator begin, struct N##_iterator end,                \
            void (*fun)(const N##_type *const, void *), void *argout)          \
        {                                                                      \
                if(!N##_iterator_valid(begin) || !N##_iterator_valid(end))     \
                {                                                              \
                        return;                                                \
                }                                                              \
                fun(N##_iterator_data(end), argout);                           \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_prev(&end);                               \
                        fun(N##_iterator_data(end), argout);                   \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_fold_reverse(const N *const c,                                \
                              void (*fun)(const N##_type *const, void *),      \
                              void *argout)                                    \
        {                                                                      \
                N##_fold_range_reverse(N##_cbegin(c), N##_cend(c), fun,        \
                                       argout);                                \
        }                                                                      \
                                                                               \
        void N##_execute_range_reverse(struct N##_iterator begin,              \
                                       struct N##_iterator end,                \
                                       void (*fun)(const N##_type *const))     \
        {                                                                      \
                if(!N##_iterator_valid(begin) || !N##_iterator_valid(end))     \
                {                                                              \
                        return;                                                \
                }                                                              \
                fun(N##_iterator_data(end));                                   \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_prev(&end);                               \
                        fun(N##_iterator_data(end));                           \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_execute_reverse(const N *const c,                             \
                                 void (*fun)(const N##_type *const))           \
        {                                                                      \
                N##_execute_range_reverse(N##_cbegin(c), N##_cend(c), fun);    \
        }                                                                      \
                                                                               \
        void N##_fprintf_range_reverse(struct N##_iterator begin,              \
                                       struct N##_iterator end,                \
                                       const char *const format, FILE *file)   \
        {                                                                      \
                if(!N##_iterator_valid(begin) || !N##_iterator_valid(end))     \
                {                                                              \
                        return;                                                \
                }                                                              \
                fprintf(file, format, *N##_iterator_data(end));                \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_prev(&end);                               \
                        fprintf(file, format, *N##_iterator_data(end));        \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_fprintf_reverse(const N *const c, const char *const format,   \
                                 FILE *file)                                   \
        {                                                                      \
                N##_fprintf_range_reverse(N##_cbegin(c), N##_cend(c), format,  \
                                          file);                               \
        }                                                                      \
                                                                               \
        void N##_sprintf_range_reverse(struct N##_iterator begin,              \
                                       struct N##_iterator end,                \
                                       const char *const format, char *buff)   \
        {                                                                      \
                if(!N##_iterator_valid(begin) || !N##_iterator_valid(end))     \
                {                                                              \
                        return;                                                \
                }                                                              \
                sprintf(buff, format, *N##_iterator_data(end));                \
                buff += strlen(buff);                                          \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_prev(&end);                               \
                        sprintf(buff, format, *N##_iterator_data(end));        \
                        buff += strlen(buff);                                  \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_sprintf_reverse(const N *const c, const char *const format,   \
                                 char *buff)                                   \
        {                                                                      \
                N##_sprintf_range_reverse(N##_cbegin(c), N##_cend(c), format,  \
                                          buff);                               \
        }

#define SGC_INIT_FIND(T, N)                                                    \
        SGC_INIT_HEADERS_FIND(T, N);                                           \
        N##_type *N##_find_el_range(struct N##_iterator begin,                 \
                                    struct N##_iterator end,                   \
                                    const N##_type el)                         \
        {                                                                      \
                N##_type *ret = NULL;                                          \
                if(N##_iterator_valid(begin) || N##_iterator_valid(end))       \
                {                                                              \
                        if(T##_equal(&el, N##_iterator_data(begin)))           \
                        {                                                      \
                                ret = N##_iterator_data(begin);                \
                        }                                                      \
                        while(!ret && !N##_iterator_equal(begin, end))         \
                        {                                                      \
                                N##_iterator_next(&begin);                     \
                                if(T##_equal(&el, N##_iterator_data(begin)))   \
                                {                                              \
                                        ret = N##_iterator_data(begin);        \
                                }                                              \
                        }                                                      \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        N##_type *N##_find_el(const N *const c, const N##_type el)             \
        {                                                                      \
                return N##_find_el_range(N##_cbegin(c), N##_cend(c), el);      \
        }                                                                      \
                                                                               \
        ssize_t N##_find_index(const N *const c, const N##_type el)            \
        {                                                                      \
                ssize_t ret = -1;                                              \
                int found = 0;                                                 \
                struct N##_iterator begin = N##_cbegin(c);                     \
                struct N##_iterator end = N##_cend(c);                         \
                if(!T##_equal(&el, N##_iterator_data(begin)))                  \
                {                                                              \
                        while(!N##_iterator_equal(begin, end))                 \
                        {                                                      \
                                ++ret;                                         \
                                N##_iterator_next(&begin);                     \
                                if(T##_equal(&el, N##_iterator_data(begin)))   \
                                {                                              \
                                        found = 1;                             \
                                        break;                                 \
                                }                                              \
                        }                                                      \
                }                                                              \
                if(!T##_equal(&el, N##_iterator_data(begin)))                  \
                {                                                              \
                        ++ret;                                                 \
                        found = 1;                                             \
                }                                                              \
                ret = (found == 1) ? ret + 1 : -1;                             \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        size_t N##_count(const N *const c, const N##_type el)                  \
        {                                                                      \
                size_t ret = 0;                                                \
                struct N##_iterator begin = N##_cbegin(c);                     \
                struct N##_iterator end = N##_cend(c);                         \
                if(N##_iterator_valid(begin) || N##_iterator_valid(end))       \
                {                                                              \
                        if(T##_equal(&el, N##_iterator_data(begin)))           \
                        {                                                      \
                                ++ret;                                         \
                        }                                                      \
                        while(!N##_iterator_equal(begin, end))                 \
                        {                                                      \
                                N##_iterator_next(&begin);                     \
                                if(T##_equal(&el, N##_iterator_data(begin)))   \
                                {                                              \
                                        ++ret;                                 \
                                }                                              \
                        }                                                      \
                }                                                              \
                return ret;                                                    \
        }

#define SGC_INIT_FIND_ITERATOR(T, N)                                           \
        SGC_INIT_HEADERS_FIND_ITERATOR(T, N);                                  \
        struct N##_iterator N##_find_range(struct N##_iterator begin,          \
                                           struct N##_iterator end,            \
                                           const N##_type el)                  \
        {                                                                      \
                struct N##_iterator ret = end;                                 \
                int done = 0;                                                  \
                if(N##_iterator_valid(begin) || N##_iterator_valid(end))       \
                {                                                              \
                        if(T##_equal(&el, N##_iterator_data(begin)))           \
                        {                                                      \
                                ret = begin;                                   \
                                done = 1;                                      \
                        }                                                      \
                        while(!done && !N##_iterator_equal(begin, end))        \
                        {                                                      \
                                N##_iterator_next(&begin);                     \
                                if(T##_equal(&el, N##_iterator_data(begin)))   \
                                {                                              \
                                        ret = begin;                           \
                                        done = 1;                              \
                                }                                              \
                        }                                                      \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_find(const N *const c, const N##_type el)      \
        {                                                                      \
                return N##_find_range(N##_cbegin(c), N##_cend(c), el);         \
        }

#define SGC_INIT_BINARY_FIND(T, N)                                             \
        SGC_INIT_HEADERS_BINARY_FIND(T, N);                                    \
        N##_type *N##_binary_find_el(N *c, const N##_type el)                  \
        {                                                                      \
                N##_type *ret = NULL;                                          \
                if(!N##_empty(c))                                              \
                {                                                              \
                        ssize_t l = 0;                                         \
                        ssize_t r = N##_size(c) - 1;                           \
                        ssize_t m;                                             \
                        while(l <= r)                                          \
                        {                                                      \
                                m = l + (r - l) / 2;                           \
                                N##_type *curr = N##_at(c, m);                 \
                                if(T##_equal(curr, &el))                       \
                                {                                              \
                                        ret = N##_at(c, m);                    \
                                        break;                                 \
                                }                                              \
                                                                               \
                                if(T##_compare(curr, &el) < 0)                 \
                                {                                              \
                                        l = m + 1;                             \
                                }                                              \
                                else                                           \
                                {                                              \
                                        r = m - 1;                             \
                                }                                              \
                        }                                                      \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        size_t N##_binary_find_index(N *c, const N##_type el)                  \
        {                                                                      \
                size_t ret = N##_size(c) + 1;                                  \
                if(!N##_empty(c))                                              \
                {                                                              \
                        ssize_t l = 0;                                         \
                        ssize_t r = N##_size(c) - 1;                           \
                        ssize_t m;                                             \
                        while(l <= r)                                          \
                        {                                                      \
                                m = l + (r - l) / 2;                           \
                                N##_type *curr = N##_at(c, m);                 \
                                if(T##_equal(curr, &el))                       \
                                {                                              \
                                        ret = m;                               \
                                        break;                                 \
                                }                                              \
                                                                               \
                                if(T##_compare(curr, &el) < 0)                 \
                                {                                              \
                                        l = m + 1;                             \
                                }                                              \
                                else                                           \
                                {                                              \
                                        r = m - 1;                             \
                                }                                              \
                        }                                                      \
                }                                                              \
                return ret;                                                    \
        }

#define SGC_INIT_ITERATE_PAIR(T, N)                                            \
        SGC_INIT_HEADERS_ITERATE_PAIR(T, N);                                   \
                                                                               \
        void N##_fprintf_range_pair(struct N##_iterator begin,                 \
                                    struct N##_iterator end,                   \
                                    const char *const format, FILE *file)      \
        {                                                                      \
                if(!N##_iterator_valid(begin) || !N##_iterator_valid(end))     \
                {                                                              \
                        return;                                                \
                }                                                              \
                fprintf(file, format, N##_iterator_data(begin)->key,           \
                        N##_iterator_data(begin)->value);                      \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_next(&begin);                             \
                        fprintf(file, format, N##_iterator_data(begin)->key,   \
                                N##_iterator_data(begin)->value);              \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_fprintf_pair(const N *const c, const char *const format,      \
                              FILE *file)                                      \
        {                                                                      \
                N##_fprintf_range_pair(N##_cbegin(c), N##_cend(c), format,     \
                                       file);                                  \
        }                                                                      \
                                                                               \
        void N##_sprintf_range_pair(struct N##_iterator begin,                 \
                                    struct N##_iterator end,                   \
                                    const char *const format, char *buff)      \
        {                                                                      \
                if(!N##_iterator_valid(begin) || !N##_iterator_valid(end))     \
                {                                                              \
                        return;                                                \
                }                                                              \
                sprintf(buff, format, N##_iterator_data(begin)->key,           \
                        N##_iterator_data(begin)->value);                      \
                buff += strlen(buff);                                          \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_next(&begin);                             \
                        sprintf(buff, format, N##_iterator_data(begin)->key,   \
                                N##_iterator_data(begin)->value);              \
                        buff += strlen(buff);                                  \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_sprintf_pair(const N *const c, const char *const format,      \
                              char *buff)                                      \
        {                                                                      \
                N##_sprintf_range_pair(N##_cbegin(c), N##_cend(c), format,     \
                                       buff);                                  \
        }                                                                      \
                                                                               \
        void N##_fprintf_range_reverse_pair(                                   \
            struct N##_iterator begin, struct N##_iterator end,                \
            const char *const format, FILE *file)                              \
        {                                                                      \
                if(!N##_iterator_valid(begin) || !N##_iterator_valid(end))     \
                {                                                              \
                        return;                                                \
                }                                                              \
                fprintf(file, format, N##_iterator_data(end)->key,             \
                        N##_iterator_data(end)->value);                        \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_prev(&end);                               \
                        fprintf(file, format, N##_iterator_data(end)->key,     \
                                N##_iterator_data(end)->value);                \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_fprintf_reverse_pair(const N *const c,                        \
                                      const char *const format, FILE *file)    \
        {                                                                      \
                N##_fprintf_range_reverse_pair(N##_cbegin(c), N##_cend(c),     \
                                               format, file);                  \
        }                                                                      \
                                                                               \
        void N##_sprintf_range_reverse_pair(                                   \
            struct N##_iterator begin, struct N##_iterator end,                \
            const char *const format, char *buff)                              \
        {                                                                      \
                if(!N##_iterator_valid(begin) || !N##_iterator_valid(end))     \
                {                                                              \
                        return;                                                \
                }                                                              \
                sprintf(buff, format, N##_iterator_data(end)->value,           \
                        N##_iterator_data(end)->key);                          \
                buff += strlen(buff);                                          \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_prev(&end);                               \
                        sprintf(buff, format, N##_iterator_data(end)->key,     \
                                N##_iterator_data(end)->value);                \
                        buff += strlen(buff);                                  \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_sprintf_reverse_pair(const N *const c,                        \
                                      const char *const format, char *buff)    \
        {                                                                      \
                N##_sprintf_range_reverse_pair(N##_cbegin(c), N##_cend(c),     \
                                               format, buff);                  \
        }

#ifndef SGC_STACK
#define SGC_STACK
#define SGC_STACK_SIZE 64

#define SGC_PREPARE_STACK                                                      \
        char *stack[SGC_STACK_SIZE];                                           \
        char **stackptr = stack

#define SGC_STACK_PUSH(array, limit)                                           \
        stackptr[0] = array;                                                   \
        stackptr[1] = limit;                                                   \
        stackptr += 2

#define SGC_STACK_POP(array, limit)                                            \
        stackptr -= 2;                                                         \
        array = stackptr[0];                                                   \
        limit = stackptr[1]

#define SGC_STACK_THRESH 7

#endif

#define SGC_INIT_QSORT(T, N)                                                   \
        SGC_INIT_HEADERS_QSORT(T, N);                                          \
        SGC_INIT_STATIC_FUNCTIONS_QSORT(T, N);                                 \
        static void N##_memswp(char *i, char *j)                               \
        {                                                                      \
                N##_type tmp;                                                  \
                                                                               \
                memcpy(&tmp, i, sizeof(N##_type));                             \
                memcpy(i, j, sizeof(N##_type));                                \
                memcpy(j, &tmp, sizeof(N##_type));                             \
        }                                                                      \
                                                                               \
        static void N##_qsort(void *array, size_t array_size,                  \
                              int (*comp)(const void *, const void *))         \
        {                                                                      \
                char *i, *j;                                                   \
                size_t thresh = SGC_STACK_THRESH * sizeof(N##_type);           \
                char *array_ = (char *)array;                                  \
                char *limit = array_ + array_size * sizeof(N##_type);          \
                SGC_PREPARE_STACK;                                             \
                                                                               \
                while(1)                                                       \
                {                                                              \
                        if((size_t)(limit - array_) > thresh)                  \
                        {                                                      \
                                i = array_ + sizeof(N##_type);                 \
                                j = limit - sizeof(N##_type);                  \
                                N##_memswp(((((size_t)(limit - array_)) /      \
                                             sizeof(N##_type)) /               \
                                            2) * sizeof(N##_type) +            \
                                               array_,                         \
                                           array_);                            \
                                if(comp(i, j) > 0)                             \
                                {                                              \
                                        N##_memswp(i, j);                      \
                                }                                              \
                                if(comp(array_, j) > 0)                        \
                                {                                              \
                                        N##_memswp(array_, j);                 \
                                }                                              \
                                if(comp(i, array_) > 0)                        \
                                {                                              \
                                        N##_memswp(i, array_);                 \
                                }                                              \
                                while(1)                                       \
                                {                                              \
                                        do                                     \
                                        {                                      \
                                                i += sizeof(N##_type);         \
                                        } while(comp(array_, i) > 0);          \
                                        do                                     \
                                        {                                      \
                                                j -= sizeof(N##_type);         \
                                        } while(comp(j, array_) > 0);          \
                                        if(i > j)                              \
                                        {                                      \
                                                break;                         \
                                        }                                      \
                                        N##_memswp(i, j);                      \
                                }                                              \
                                N##_memswp(array_, j);                         \
                                if(j - array_ > limit - i)                     \
                                {                                              \
                                        SGC_STACK_PUSH(array_, j);             \
                                        array_ = i;                            \
                                }                                              \
                                else                                           \
                                {                                              \
                                        SGC_STACK_PUSH(i, limit);              \
                                        limit = j;                             \
                                }                                              \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                for(j = array_, i = j + sizeof(N##_type);      \
                                    i < limit; j = i, i += sizeof(N##_type))   \
                                {                                              \
                                        for(;                                  \
                                            comp(j, j + sizeof(N##_type)) > 0; \
                                            j -= sizeof(N##_type))             \
                                        {                                      \
                                                N##_memswp(                    \
                                                    j, j + sizeof(N##_type));  \
                                                if(j == array_)                \
                                                {                              \
                                                        break;                 \
                                                }                              \
                                        }                                      \
                                }                                              \
                                if(stackptr != stack)                          \
                                {                                              \
                                        SGC_STACK_POP(array_, limit);          \
                                }                                              \
                                else                                           \
                                {                                              \
                                        break;                                 \
                                }                                              \
                        }                                                      \
                }                                                              \
        }                                                                      \
        void N##_sort(N *c, int (*comp)(const void *, const void *))           \
        {                                                                      \
                if(comp == NULL)                                               \
                {                                                              \
                        comp = T##_void_compare;                               \
                }                                                              \
                N##_qsort(N##_array(c), N##_size(c), comp);                    \
        }

#ifndef SGC_HELPERS
#define SGC_HELPERS

#define SGC_TOKENPASTE(x, y) x##y
#define SGC_TOKENPASTE2(x, y) SGC_TOKENPASTE(x, y)
#define SGC_UNIQUE(x) SGC_TOKENPASTE2(__sgc_unique_##x, __LINE__)

#define SGC_NONE() (void *)NULL;

#define SGC_FOR_EACH_N(_1, _2, _3, _4, _5, _6, _7, NAME, ...) NAME
#define sgc_for_each(...)                                                      \
        SGC_FOR_EACH_N(__VA_ARGS__, SGC_FOR_EACH3, SGC_FOR_EACH_SAME2,         \
                       SGC_FOR_EACH2, SGC_NONE, SGC_FOR_EACH1)                 \
        (__VA_ARGS__)

#define SGC_FOR_EACH1(EL, C, N)                                                \
        int SGC_UNIQUE(valid) = 0;                                             \
        int SGC_UNIQUE(tmp) = 0;                                               \
        struct N##_iterator SGC_UNIQUE(curr) = N##_begin(&C);                  \
        struct N##_iterator SGC_UNIQUE(end) = N##_end(&C);                     \
        SGC_UNIQUE(valid) = N##_iterator_valid(SGC_UNIQUE(curr)) &&            \
                            N##_iterator_valid(SGC_UNIQUE(end));               \
        for(N##_type *EL = N##_iterator_data(SGC_UNIQUE(curr));                \
            SGC_UNIQUE(valid); SGC_UNIQUE(tmp) = !N##_iterator_equal(          \
                                   SGC_UNIQUE(curr), SGC_UNIQUE(end)),         \
                     SGC_UNIQUE(valid) = SGC_UNIQUE(tmp),                      \
                     N##_iterator_next(&SGC_UNIQUE(curr)),                     \
                     EL = N##_iterator_data(SGC_UNIQUE(curr)))

#define SGC_FOR_EACH_SAME2(EL, C1, C2, N) SGC_FOR_EACH2(EL, C1, N, C2, N)

#define SGC_FOR_EACH2(EL, C1, N1, C2, N2)                                      \
        int SGC_UNIQUE(valid1) = 0;                                            \
        int SGC_UNIQUE(tmp1) = 0;                                              \
        int SGC_UNIQUE(valid2) = 0;                                            \
        int SGC_UNIQUE(tmp2) = 0;                                              \
        struct N1##_iterator SGC_UNIQUE(curr1) = N1##_begin(&C1);              \
        struct N1##_iterator SGC_UNIQUE(end1) = N1##_end(&C1);                 \
        struct N2##_iterator SGC_UNIQUE(curr2) = N2##_begin(&C2);              \
        struct N2##_iterator SGC_UNIQUE(end2) = N2##_end(&C2);                 \
        SGC_UNIQUE(valid1) = N1##_iterator_valid(SGC_UNIQUE(curr1)) &&         \
                             N1##_iterator_valid(SGC_UNIQUE(end1));            \
        SGC_UNIQUE(valid2) = N2##_iterator_valid(SGC_UNIQUE(curr2)) &&         \
                             N2##_iterator_valid(SGC_UNIQUE(end2));            \
        struct SGC_UNIQUE(pair)                                                \
        {                                                                      \
                N1##_type *first;                                              \
                N2##_type *second;                                             \
        };                                                                     \
        for(struct SGC_UNIQUE(pair)                                            \
                EL = {N1##_iterator_data(SGC_UNIQUE(curr1)),                   \
                      N2##_iterator_data(SGC_UNIQUE(curr2))};                  \
            SGC_UNIQUE(valid1) && SGC_UNIQUE(valid2);                          \
            SGC_UNIQUE(tmp1) =                                                 \
                !N1##_iterator_equal(SGC_UNIQUE(curr1), SGC_UNIQUE(end1)),     \
                SGC_UNIQUE(tmp2) =                                             \
                    !N2##_iterator_equal(SGC_UNIQUE(curr2), SGC_UNIQUE(end2)), \
                SGC_UNIQUE(valid1) = SGC_UNIQUE(tmp1),                         \
                SGC_UNIQUE(valid2) = SGC_UNIQUE(tmp2),                         \
                N1##_iterator_next(&SGC_UNIQUE(curr1)),                        \
                N2##_iterator_next(&SGC_UNIQUE(curr2)),                        \
                EL = (struct SGC_UNIQUE(pair)){                                \
                    N1##_iterator_data(SGC_UNIQUE(curr1)),                     \
                    N2##_iterator_data(SGC_UNIQUE(curr2))})

#define SGC_FOR_EACH3(EL, C1, N1, C2, N2, C3, N3)                              \
        int SGC_UNIQUE(valid1) = 0;                                            \
        int SGC_UNIQUE(tmp1) = 0;                                              \
        int SGC_UNIQUE(valid2) = 0;                                            \
        int SGC_UNIQUE(tmp2) = 0;                                              \
        int SGC_UNIQUE(valid3) = 0;                                            \
        int SGC_UNIQUE(tmp3) = 0;                                              \
        struct N1##_iterator SGC_UNIQUE(curr1) = N1##_begin(&C1);              \
        struct N1##_iterator SGC_UNIQUE(end1) = N1##_end(&C1);                 \
        struct N2##_iterator SGC_UNIQUE(curr2) = N2##_begin(&C2);              \
        struct N2##_iterator SGC_UNIQUE(end2) = N2##_end(&C2);                 \
        struct N3##_iterator SGC_UNIQUE(curr3) = N3##_begin(&C3);              \
        struct N3##_iterator SGC_UNIQUE(end3) = N3##_end(&C3);                 \
        SGC_UNIQUE(valid1) = N1##_iterator_valid(SGC_UNIQUE(curr1)) &&         \
                             N1##_iterator_valid(SGC_UNIQUE(end1));            \
        SGC_UNIQUE(valid2) = N2##_iterator_valid(SGC_UNIQUE(curr2)) &&         \
                             N2##_iterator_valid(SGC_UNIQUE(end2));            \
        SGC_UNIQUE(valid3) = N3##_iterator_valid(SGC_UNIQUE(curr3)) &&         \
                             N3##_iterator_valid(SGC_UNIQUE(end3));            \
        struct SGC_UNIQUE(pair)                                                \
        {                                                                      \
                N1##_type *first;                                              \
                N2##_type *second;                                             \
                N3##_type *third;                                              \
        };                                                                     \
        for(struct SGC_UNIQUE(pair)                                            \
                EL = {N1##_iterator_data(SGC_UNIQUE(curr1)),                   \
                      N2##_iterator_data(SGC_UNIQUE(curr2)),                   \
                      N3##_iterator_data(SGC_UNIQUE(curr3))};                  \
            SGC_UNIQUE(valid1) && SGC_UNIQUE(valid2) && SGC_UNIQUE(valid3);    \
            SGC_UNIQUE(tmp1) =                                                 \
                !N1##_iterator_equal(SGC_UNIQUE(curr1), SGC_UNIQUE(end1)),     \
                SGC_UNIQUE(tmp2) =                                             \
                    !N2##_iterator_equal(SGC_UNIQUE(curr2), SGC_UNIQUE(end2)), \
                SGC_UNIQUE(tmp3) =                                             \
                    !N3##_iterator_equal(SGC_UNIQUE(curr3), SGC_UNIQUE(end3)), \
                SGC_UNIQUE(valid1) = SGC_UNIQUE(tmp1),                         \
                SGC_UNIQUE(valid2) = SGC_UNIQUE(tmp2),                         \
                SGC_UNIQUE(valid3) = SGC_UNIQUE(tmp3),                         \
                N1##_iterator_next(&SGC_UNIQUE(curr1)),                        \
                N2##_iterator_next(&SGC_UNIQUE(curr2)),                        \
                N3##_iterator_next(&SGC_UNIQUE(curr3)),                        \
                EL = (struct SGC_UNIQUE(pair)){                                \
                    N1##_iterator_data(SGC_UNIQUE(curr1)),                     \
                    N2##_iterator_data(SGC_UNIQUE(curr2)),                     \
                    N3##_iterator_data(SGC_UNIQUE(curr3))})

#define SGC_FOR_EACH_REVERSE_N(_1, _2, _3, _4, _5, _6, _7, NAME, ...) NAME
#define sgc_for_each_reverse(...)                                              \
        SGC_FOR_EACH_REVERSE_N(                                                \
            __VA_ARGS__, SGC_FOR_EACH_REVERSE3, SGC_FOR_EACH_SAME_REVERSE2,    \
            SGC_FOR_EACH_REVERSE2, SGC_NONE, SGC_FOR_EACH_REVERSE1)            \
        (__VA_ARGS__)

#define SGC_FOR_EACH_REVERSE(EL, C, N)                                         \
        int SGC_UNIQUE(valid) = 0;                                             \
        int SGC_UNIQUE(tmp) = 0;                                               \
        struct N##_iterator SGC_UNIQUE(curr) = N##_end(&C);                    \
        struct N##_iterator SGC_UNIQUE(begin) = N##_begin(&C);                 \
        SGC_UNIQUE(valid) = N##_iterator_valid(SGC_UNIQUE(curr)) &&            \
                            N##_iterator_valid(SGC_UNIQUE(begin));             \
        for(N##_type *EL = N##_iterator_data(SGC_UNIQUE(curr));                \
            SGC_UNIQUE(valid); SGC_UNIQUE(tmp) = !N##_iterator_equal(          \
                                   SGC_UNIQUE(curr), SGC_UNIQUE(begin)),       \
                     SGC_UNIQUE(valid) = SGC_UNIQUE(tmp),                      \
                     N##_iterator_prev(&SGC_UNIQUE(curr)),                     \
                     EL = N##_iterator_data(SGC_UNIQUE(curr)))

#define SGC_FOR_EACH_SAME_REVERSE2(EL, C1, C2, N)                              \
        SGC_FOR_EACH_REVERSE2(EL, C1, N, C2, N)

#define SGC_FOR_EACH_REVERSE2(EL, C1, N1, C2, N2)                              \
        int SGC_UNIQUE(valid1) = 0;                                            \
        int SGC_UNIQUE(tmp1) = 0;                                              \
        int SGC_UNIQUE(valid2) = 0;                                            \
        int SGC_UNIQUE(tmp2) = 0;                                              \
        struct N1##_iterator SGC_UNIQUE(curr1) = N1##_end(&C1);                \
        struct N1##_iterator SGC_UNIQUE(begin1) = N1##_begin(&C1);             \
        struct N2##_iterator SGC_UNIQUE(curr2) = N2##_end(&C2);                \
        struct N2##_iterator SGC_UNIQUE(begin2) = N2##_begin(&C2);             \
        SGC_UNIQUE(valid1) = N1##_iterator_valid(SGC_UNIQUE(curr1)) &&         \
                             N1##_iterator_valid(SGC_UNIQUE(begin1));          \
        SGC_UNIQUE(valid2) = N2##_iterator_valid(SGC_UNIQUE(curr2)) &&         \
                             N2##_iterator_valid(SGC_UNIQUE(begin2));          \
        struct SGC_UNIQUE(pair)                                                \
        {                                                                      \
                N1##_type *first;                                              \
                N2##_type *second;                                             \
        };                                                                     \
        for(struct SGC_UNIQUE(pair)                                            \
                EL = {N1##_iterator_data(SGC_UNIQUE(curr1)),                   \
                      N2##_iterator_data(SGC_UNIQUE(curr2))};                  \
            SGC_UNIQUE(valid1) && SGC_UNIQUE(valid2);                          \
            SGC_UNIQUE(tmp1) =                                                 \
                !N1##_iterator_equal(SGC_UNIQUE(curr1), SGC_UNIQUE(begin1)),   \
                SGC_UNIQUE(tmp2) = !N2##_iterator_equal(SGC_UNIQUE(curr2),     \
                                                        SGC_UNIQUE(begin2)),   \
                SGC_UNIQUE(valid1) = SGC_UNIQUE(tmp1),                         \
                SGC_UNIQUE(valid2) = SGC_UNIQUE(tmp2),                         \
                N1##_iterator_prev(&SGC_UNIQUE(curr1)),                        \
                N2##_iterator_prev(&SGC_UNIQUE(curr2)),                        \
                EL = (struct SGC_UNIQUE(pair)){                                \
                    N1##_iterator_data(SGC_UNIQUE(curr1)),                     \
                    N2##_iterator_data(SGC_UNIQUE(curr2))})

#define SGC_FOR_EACH_REVERSE3(EL, C1, N1, C2, N2, C3, N3)                      \
        int SGC_UNIQUE(valid1) = 0;                                            \
        int SGC_UNIQUE(tmp1) = 0;                                              \
        int SGC_UNIQUE(valid2) = 0;                                            \
        int SGC_UNIQUE(tmp2) = 0;                                              \
        int SGC_UNIQUE(valid3) = 0;                                            \
        int SGC_UNIQUE(tmp3) = 0;                                              \
        struct N1##_iterator SGC_UNIQUE(curr1) = N1##_end(&C1);                \
        struct N1##_iterator SGC_UNIQUE(begin1) = N1##_begin(&C1);             \
        struct N2##_iterator SGC_UNIQUE(curr2) = N2##_end(&C2);                \
        struct N2##_iterator SGC_UNIQUE(begin2) = N2##_begin(&C2);             \
        struct N3##_iterator SGC_UNIQUE(curr3) = N3##_end(&C3);                \
        struct N3##_iterator SGC_UNIQUE(begin3) = N3##_begin(&C3);             \
        SGC_UNIQUE(valid1) = N1##_iterator_valid(SGC_UNIQUE(curr1)) &&         \
                             N1##_iterator_valid(SGC_UNIQUE(begin1));          \
        SGC_UNIQUE(valid2) = N2##_iterator_valid(SGC_UNIQUE(curr2)) &&         \
                             N2##_iterator_valid(SGC_UNIQUE(begin2));          \
        SGC_UNIQUE(valid3) = N3##_iterator_valid(SGC_UNIQUE(curr3)) &&         \
                             N3##_iterator_valid(SGC_UNIQUE(begin3));          \
        struct SGC_UNIQUE(pair)                                                \
        {                                                                      \
                N1##_type *first;                                              \
                N2##_type *second;                                             \
                N3##_type *third;                                              \
        };                                                                     \
        for(struct SGC_UNIQUE(pair)                                            \
                EL = {N1##_iterator_data(SGC_UNIQUE(curr1)),                   \
                      N2##_iterator_data(SGC_UNIQUE(curr2)),                   \
                      N3##_iterator_data(SGC_UNIQUE(curr3))};                  \
            SGC_UNIQUE(valid1) && SGC_UNIQUE(valid2) && SGC_UNIQUE(valid3);    \
            SGC_UNIQUE(tmp1) =                                                 \
                !N1##_iterator_equal(SGC_UNIQUE(curr1), SGC_UNIQUE(begin1)),   \
                SGC_UNIQUE(tmp2) = !N2##_iterator_equal(SGC_UNIQUE(curr2),     \
                                                        SGC_UNIQUE(begin2)),   \
                SGC_UNIQUE(tmp3) = !N3##_iterator_equal(SGC_UNIQUE(curr3),     \
                                                        SGC_UNIQUE(begin3)),   \
                SGC_UNIQUE(valid1) = SGC_UNIQUE(tmp1),                         \
                SGC_UNIQUE(valid2) = SGC_UNIQUE(tmp2),                         \
                SGC_UNIQUE(valid3) = SGC_UNIQUE(tmp3),                         \
                N1##_iterator_prev(&SGC_UNIQUE(curr1)),                        \
                N2##_iterator_prev(&SGC_UNIQUE(curr2)),                        \
                N3##_iterator_prev(&SGC_UNIQUE(curr3)),                        \
                EL = (struct SGC_UNIQUE(pair)){                                \
                    N1##_iterator_data(SGC_UNIQUE(curr1)),                     \
                    N2##_iterator_data(SGC_UNIQUE(curr2)),                     \
                    N3##_iterator_data(SGC_UNIQUE(curr3))})

#define SGC_FOR_EACH_INTERSECT_N(_1, _2, _3, _4, _5, NAME, ...) NAME
#define sgc_for_each_intersect(...)                                            \
        SGC_FOR_EACH_INTERSECT_N(__VA_ARGS__, sgc_for_each_intersect1,         \
                                 SGC_FOR_EACH_SAME_INTERSECT, SGC_NONE)        \
        (__VA_ARGS__)

#define SGC_FOR_EACH_SAME_INTERSECT(EL, C1, C2, N)                             \
        sgc_for_each_intersect1(EL, C1, N, C2, N)

#define sgc_for_each_intersect1(EL, C1, N1, C2, N2)                            \
        int SGC_UNIQUE(valid1) = 0;                                            \
        int SGC_UNIQUE(tmp1) = 0;                                              \
        int SGC_UNIQUE(valid2) = 0;                                            \
        int SGC_UNIQUE(tmp2) = 0;                                              \
        struct N1##_iterator SGC_UNIQUE(curr1) = N1##_begin(&C1);              \
        struct N1##_iterator SGC_UNIQUE(end1) = N1##_end(&C1);                 \
        struct N2##_iterator SGC_UNIQUE(curr2) = N2##_end(&C2);                \
        struct N2##_iterator SGC_UNIQUE(begin2) = N2##_begin(&C2);             \
        SGC_UNIQUE(valid1) = N1##_iterator_valid(SGC_UNIQUE(curr1)) &&         \
                             N1##_iterator_valid(SGC_UNIQUE(end1));            \
        SGC_UNIQUE(valid2) = N2##_iterator_valid(SGC_UNIQUE(curr2)) &&         \
                             N2##_iterator_valid(SGC_UNIQUE(begin2));          \
        struct SGC_UNIQUE(pair)                                                \
        {                                                                      \
                N1##_type *first;                                              \
                N2##_type *second;                                             \
        };                                                                     \
        for(struct SGC_UNIQUE(pair)                                            \
                EL = {N1##_iterator_data(SGC_UNIQUE(curr1)),                   \
                      N2##_iterator_data(SGC_UNIQUE(curr2))};                  \
            SGC_UNIQUE(valid1) && SGC_UNIQUE(valid2);                          \
            SGC_UNIQUE(tmp1) =                                                 \
                !N1##_iterator_equal(SGC_UNIQUE(curr1), SGC_UNIQUE(end1)),     \
                SGC_UNIQUE(tmp2) = !N2##_iterator_equal(SGC_UNIQUE(curr2),     \
                                                        SGC_UNIQUE(begin2)),   \
                SGC_UNIQUE(valid1) = SGC_UNIQUE(tmp1),                         \
                SGC_UNIQUE(valid2) = SGC_UNIQUE(tmp2),                         \
                N1##_iterator_next(&SGC_UNIQUE(curr1)),                        \
                N2##_iterator_prev(&SGC_UNIQUE(curr2)),                        \
                EL = (struct SGC_UNIQUE(pair)){                                \
                    N1##_iterator_data(SGC_UNIQUE(curr1)),                     \
                    N2##_iterator_data(SGC_UNIQUE(curr2))})

#endif
