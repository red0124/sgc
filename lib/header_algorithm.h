#pragma once

#define SGC_INIT_HEADER_N(_1, _2, _3, _4, _5, _6, _7, NAME, ...) NAME
#define SGC_INIT_HEADER(...)                                                   \
        SGC_INIT_HEADER_N(__VA_ARGS__, SGC_INIT_HEADER7, SGC_INIT_HEADER6,     \
                          SGC_INIT_HEADER5, SGC_INIT_HEADER4,                  \
                          SGC_INIT_HEADER3)                                    \
        (__VA_ARGS__)

#define SGC_INIT_HEADER3(C, T, N) SGC_INIT_HEADER_##C(T, N);

#define SGC_INIT_HEADER4(C, T, N, A1)                                          \
        SGC_INIT_HEADER_##C(T, N);                                             \
        SGC_INIT_HEADER_##A1(N);

#define SGC_INIT_HEADER5(C, T, N, A1, A2)                                      \
        SGC_INIT_HEADER_##C(T, N);                                             \
        SGC_INIT_HEADER_##A1(N);                                               \
        SGC_INIT_HEADER_##A2(N);

#define SGC_INIT_HEADER6(C, T, N, A1, A2, A3)                                  \
        SGC_INIT_HEADER_##C(T, N);                                             \
        SGC_INIT_HEADER_##A1(N);                                               \
        SGC_INIT_HEADER_##A2(N);                                               \
        SGC_INIT_HEADER_##A3(N);

#define SGC_INIT_HEADER7(C, T, N, A1, A2, A3, A4)                              \
        SGC_INIT_HEADER_##C(T, N);                                             \
        SGC_INIT_HEADER_##A1(N);                                               \
        SGC_INIT_HEADER_##A2(N);                                               \
        SGC_INIT_HEADER_##A3(N);                                               \
        SGC_INIT_HEADER_##A4(N);

#define SGC_INIT_HEADER_PAIR_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, NAME, ...)  \
        NAME

#define SGC_INIT_HEADER_PAIR(...)                                              \
        SGC_INIT_HEADER_PAIR_N(__VA_ARGS__, SGC_INIT_HEADER_PAIR9,             \
                               SGC_INIT_HEADER_PAIR8, SGC_INIT_HEADER_PAIR7,   \
                               SGC_INIT_HEADER_PAIR6, SGC_INIT_HEADER_PAIR5,   \
                               SGC_INIT_HEADER_PAIR4)                          \
        (__VA_ARGS__)

#define SGC_INIT_HEADER_PAIR4(C, K, V, N) SGC_INIT_HEADER_##C(K, V, N);

#define SGC_INIT_HEADER_PAIR5(C, K, V, N, A1)                                  \
        SGC_INIT_HEADER_##C(K, V, N);                                          \
        SGC_INIT_HEADER_##A1(N);

#define SGC_INIT_HEADER_PAIR6(C, K, V, N, A1, A2)                              \
        SGC_INIT_HEADER_##C(K, V, N);                                          \
        SGC_INIT_HEADER_##A1(N);                                               \
        SGC_INIT_HEADER_##A2(N);

#define SGC_INIT_HEADER_PAIR7(C, K, V, N, A1, A2, A3)                          \
        SGC_INIT_HEADER_##C(K, V, N);                                          \
        SGC_INIT_HEADER_##A1(N);                                               \
        SGC_INIT_HEADER_##A2(N);                                               \
        SGC_INIT_HEADER_##A3(N);

#define SGC_INIT_HEADER_PAIR8(C, K, V, N, A1, A2, A3, A4)                      \
        SGC_INIT_HEADER_##C(K, V, N);                                          \
        SGC_INIT_HEADER_##A1(N);                                               \
        SGC_INIT_HEADER_##A2(N);                                               \
        SGC_INIT_HEADER_##A3(N);                                               \
        SGC_INIT_HEADER_##A4(N);

#define SGC_INIT_HEADER_PAIR9(C, K, V, N, A1, A2, A3, A4, A5)                  \
        SGC_INIT_HEADER_##C(K, V, N);                                          \
        SGC_INIT_HEADER_##A1(N);                                               \
        SGC_INIT_HEADER_##A2(N);                                               \
        SGC_INIT_HEADER_##A3(N);                                               \
        SGC_INIT_HEADER_##A4(N);                                               \
        SGC_INIT_HEADER_##A5(N);

#define SGC_INIT_HEADER_ITERATE(N)                                             \
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
        void N##_printf_range(struct N##_iterator begin,                       \
                              struct N##_iterator end,                         \
                              const char *const format, FILE *file);           \
                                                                               \
        void N##_printf(const struct N *const c, const char *const format,     \
                        FILE *file);                                           \
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
        void N##_printf_range_reverse(struct N##_iterator begin,               \
                                      struct N##_iterator end,                 \
                                      const char *const format, FILE *file);   \
                                                                               \
        void N##_printf_reverse(const struct N *const c,                       \
                                const char *const format, FILE *file);

#define SGC_INIT_HEADER_FIND(N)                                                \
        N##_type *N##_find_el_range(struct N##_iterator begin,                 \
                                    struct N##_iterator end,                   \
                                    const N##_type el);                        \
                                                                               \
        N##_type *N##_find_el(const struct N *const c, const N##_type el);     \
                                                                               \
        ssize_t N##_find_index(const struct N *const c, const N##_type el);    \
                                                                               \
        size_t N##_count(const N *const c, const N##_type el);

#define SGC_INIT_HEADER_FIND_ITERATOR(N)                                       \
        struct N##_iterator N##_find_range(struct N##_iterator begin,          \
                                           struct N##_iterator end,            \
                                           const N##_type el);                 \
                                                                               \
        struct N##_iterator N##_find(const struct N *const c,                  \
                                     const N##_type el);

#define SGC_INIT_HEADER_BINARY_FIND(T, N)                                      \
        N##_type *N##_binary_find_el(struct N *c, const N##_type el);          \
                                                                               \
        size_t N##_binary_find_index(struct N *c, const N##_type el);

#define SGC_INIT_HEADER_ITERATE_PAIR(N)                                        \
        void N##_fold_range_pair(                                              \
            struct N##_iterator begin, struct N##_iterator end,                \
            void (*fun)(const N##_key *const, const N##_value *const, void *), \
            void *argout);                                                     \
                                                                               \
        void N##_fold_pair(                                                    \
            const struct N *const c,                                           \
            void (*fun)(const N##_key *const, const N##_value *const, void *), \
            void *argout);                                                     \
                                                                               \
        void N##_execute_range_pair(                                           \
            struct N##_iterator begin, struct N##_iterator end,                \
            void (*fun)(const N##_key *const, const N##_value *const));        \
                                                                               \
        void N##_execute_pair(                                                 \
            const struct N *const c,                                           \
            void (*fun)(const N##_key *const, const N##_value *const));        \
                                                                               \
        void N##_printf_range_pair(struct N##_iterator begin,                  \
                                   struct N##_iterator end,                    \
                                   const char *const format, FILE *file);      \
                                                                               \
        void N##_printf_pair(const struct N *const c,                          \
                             const char *const format, FILE *file);            \
                                                                               \
        void N##_fold_range_reverse_pair(                                      \
            struct N##_iterator begin, struct N##_iterator end,                \
            void (*fun)(const N##_key *const, const N##_value *const, void *), \
            void *argout);                                                     \
                                                                               \
        void N##_fold_reverse_pair(                                            \
            const struct N *const c,                                           \
            void (*fun)(const N##_key *const, const N##_value *const, void *), \
            void *argout);                                                     \
                                                                               \
        void N##_execute_range_reverse_pair(                                   \
            struct N##_iterator begin, struct N##_iterator end,                \
            void (*fun)(const N##_key *const, const N##_value *const));        \
                                                                               \
        void N##_execute_reverse_pair(                                         \
            const struct N *const c,                                           \
            void (*fun)(const N##_key *const, const N##_value *const));        \
                                                                               \
        void N##_printf_range_reverse_pair(                                    \
            struct N##_iterator begin, struct N##_iterator end,                \
            const char *const format, FILE *file);                             \
                                                                               \
        void N##_printf_reverse_pair(const struct N *const c,                  \
                                     const char *const format, FILE *file);

#define SGC_INIT_HEADER_QSORT(N)                                               \
        void N##_sort(N *c, int (*comp)(const void *, const void *));

#define SGC_FOR_EACH(N, C, EL, ACT)                                            \
        do                                                                     \
        {                                                                      \
                N##_type *EL;                                                  \
                struct N##_iterator __sgc_it_begin = N##_cbegin(&C);           \
                struct N##_iterator __sgc_it_end = N##_cend(&C);               \
                if(!N##_iterator_valid(__sgc_it_begin) ||                      \
                   !N##_iterator_valid(__sgc_it_end))                          \
                {                                                              \
                        break;                                                 \
                }                                                              \
                if(!N##_iterator_equal(__sgc_it_begin, __sgc_it_end))          \
                {                                                              \
                        EL = N##_iterator_value(__sgc_it_begin);               \
                        do                                                     \
                        {                                                      \
                                ACT;                                           \
                        } while(0);                                            \
                }                                                              \
                while(!N##_iterator_equal(__sgc_it_begin, __sgc_it_end))       \
                {                                                              \
                        N##_iterator_next(&__sgc_it_begin);                    \
                        EL = N##_iterator_value(__sgc_it_begin);               \
                        do                                                     \
                        {                                                      \
                                ACT;                                           \
                        } while(0);                                            \
                }                                                              \
        } while(0);

#define SGC_FOR_EACH_PAIR(N, C, K, V, ACT)                                     \
        do                                                                     \
        {                                                                      \
                const N##_key *K;                                              \
                N##_value *V;                                                  \
                struct N##_iterator __sgc_it_begin = N##_cbegin(&C);           \
                struct N##_iterator __sgc_it_end = N##_cend(&C);               \
                if(!N##_iterator_valid(__sgc_it_begin) ||                      \
                   !N##_iterator_valid(__sgc_it_end))                          \
                {                                                              \
                        break;                                                 \
                }                                                              \
                if(!N##_iterator_equal(__sgc_it_begin, __sgc_it_end))          \
                {                                                              \
                        V = N##_iterator_value(__sgc_it_begin);                \
                        K = N##_iterator_key(__sgc_it_begin);                  \
                        do                                                     \
                        {                                                      \
                                ACT;                                           \
                        } while(0);                                            \
                }                                                              \
                while(!N##_iterator_equal(__sgc_it_begin, __sgc_it_end))       \
                {                                                              \
                        N##_iterator_next(&__sgc_it_begin);                    \
                        V = N##_iterator_value(__sgc_it_begin);                \
                        K = N##_iterator_key(__sgc_it_begin);                  \
                        do                                                     \
                        {                                                      \
                                ACT;                                           \
                        } while(0);                                            \
                }                                                              \
        } while(0);

#ifndef SGC_HELPERS
#define SGC_HELPERS
#define SGC_LC7(OUT_C, OUT, IN_C, IN, V, ACT, COND)                            \
        struct OUT_C OUT;                                                      \
        do                                                                     \
        {                                                                      \
                OUT_C##_init(&OUT);                                            \
                IN_C##_value V;                                                \
                struct IN_C##_iterator begin = IN_C##_cbegin(&IN);             \
                struct IN_C##_iterator end = IN_C##_cend(&IN);                 \
                if(!IN_C##_iterator_equal(begin, end))                         \
                {                                                              \
                        V = *IN_C##_iterator_value(begin);                     \
                        if(COND)                                               \
                        {                                                      \
                                OUT_C##_default_insert(&OUT, ACT);             \
                        }                                                      \
                }                                                              \
                while(!IN_C##_iterator_equal(begin, end))                      \
                {                                                              \
                        IN_C##_iterator_next(&begin);                          \
                        V = *IN_C##_iterator_value(begin);                     \
                        if(COND)                                               \
                        {                                                      \
                                OUT_C##_default_insert(&OUT, ACT);             \
                        }                                                      \
                }                                                              \
        } while(0);

#define SGC_LC6(OUT_C, OUT, IN_C, IN, V, ACT)                                  \
        struct OUT_C OUT;                                                      \
        do                                                                     \
        {                                                                      \
                OUT_C##_init(&OUT);                                            \
                IN_C##_value V;                                                \
                struct IN_C##_iterator begin = IN_C##_cbegin(&IN);             \
                struct IN_C##_iterator end = IN_C##_cend(&IN);                 \
                if(!IN_C##_iterator_equal(begin, end))                         \
                {                                                              \
                        V = *IN_C##_iterator_value(begin);                     \
                        OUT_C##_default_insert(&OUT, ACT);                     \
                }                                                              \
                while(!IN_C##_iterator_equal(begin, end))                      \
                {                                                              \
                        IN_C##_iterator_next(&begin);                          \
                        V = *IN_C##_iterator_value(begin);                     \
                        OUT_C##_default_insert(&OUT, ACT);                     \
                }                                                              \
        } while(0);

#define SGC_LC4(OUT_C, OUT, IN_C, IN)                                          \
        struct OUT_C OUT;                                                      \
        do                                                                     \
        {                                                                      \
                OUT_C##_init(&OUT);                                            \
                struct IN_C##_iterator begin = IN_C##_cbegin(&IN);             \
                struct IN_C##_iterator end = IN_C##_cend(&IN);                 \
                if(!IN_C##_iterator_equal(begin, end))                         \
                {                                                              \
                        OUT_C##_default_insert(&OUT,                           \
                                               *IN_C##_iterator_value(begin)); \
                }                                                              \
                while(!IN_C##_iterator_equal(begin, end))                      \
                {                                                              \
                        IN_C##_iterator_next(&begin);                          \
                        OUT_C##_default_insert(&OUT,                           \
                                               *IN_C##_iterator_value(begin)); \
                }                                                              \
        } while(0);

#define GET_MACRO(_1, _2, _3, _4, _5, _6, _7, NAME, ...) NAME
#define SGC_LC(...)                                                            \
        GET_MACRO(__VA_ARGS__, SGC_LC7, SGC_LC6, NONE, SGC_LC4)                \
        (__VA_ARGS__)

#define SGC_SPLIT(OUT_C, OUT, STR, S, DEL)                                     \
        OUT_C OUT;                                                             \
        do                                                                     \
        {                                                                      \
                OUT_C##_init(&OUT);                                            \
                STR __sgc_str_tmp = strtok(S, DEL);                            \
                while(__sgc_str_tmp)                                           \
                {                                                              \
                        OUT_C##_default_insert(&OUT, __sgc_str_tmp);           \
                        __sgc_str_tmp = strtok(NULL, DEL);                     \
                }                                                              \
        } while(0);

#endif
