#pragma once

#define SGC_INIT_N(_1, _2, _3, _4, _5, _6, _7, NAME, ...) NAME
#define SGC_INIT(...)                                                          \
        SGC_INIT_N(__VA_ARGS__, SGC_INIT7, SGC_INIT6, SGC_INIT5, SGC_INIT4,    \
                   SGC_INIT3, SGC_INIT2)                                       \
        (__VA_ARGS__)

#define SGC_INIT2(C, N) SGC_INIT_##C(N);

#define SGC_INIT3(C, T, N) SGC_INIT_##C(T, N);

#define SGC_INIT4(C, T, N, A1)                                                 \
        SGC_INIT_##C(T, N);                                                    \
        SGC_INIT_##A1(N);

#define SGC_INIT5(C, T, N, A1, A2)                                             \
        SGC_INIT_##C(T, N);                                                    \
        SGC_INIT_##A1(N);                                                      \
        SGC_INIT_##A2(N);

#define SGC_INIT6(C, T, N, A1, A2, A3)                                         \
        SGC_INIT_##C(T, N);                                                    \
        SGC_INIT_##A1(N);                                                      \
        SGC_INIT_##A2(N);                                                      \
        SGC_INIT_##A3(N);

#define SGC_INIT7(C, T, N, A1, A2, A3, A4)                                     \
        SGC_INIT_##C(T, N);                                                    \
        SGC_INIT_##A1(N);                                                      \
        SGC_INIT_##A2(N);                                                      \
        SGC_INIT_##A3(N);                                                      \
        SGC_INIT_##A4(N);

#define SGC_INIT_STATIC_N(_1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME
#define SGC_INIT_STATIC(...)                                                   \
        SGC_INIT_STATIC_N(__VA_ARGS__, SGC_INIT_STATIC8, SGC_INIT_STATIC7,     \
                          SGC_INIT_STATIC6, SGC_INIT_STATIC5,                  \
                          SGC_INIT_STATIC4, SGC_INIT_STATIC3)                  \
        (__VA_ARGS__)

#define SGC_INIT_STATIC4(C, T, S, N) SGC_INIT_STATIC_##C(T, S, N);

#define SGC_INIT_STATIC5(C, T, S, N, A1)                                       \
        SGC_INIT_STATIC_##C(T, S, N);                                          \
        SGC_INIT_##A1(N);

#define SGC_INIT_STATIC6(C, T, S, N, A1, A2)                                   \
        SGC_INIT_STATIC_##C(T, S, N);                                          \
        SGC_INIT_##A1(N);                                                      \
        SGC_INIT_##A2(N);

#define SGC_INIT_STATIC7(C, T, S, N, A1, A2, A3)                               \
        SGC_INIT_STATIC_##C(T, S, N);                                          \
        SGC_INIT_##A1(N);                                                      \
        SGC_INIT_##A2(N);                                                      \
        SGC_INIT_##A3(N);

#define SGC_INIT_STATIC8(C, T, S, N, A1, A2, A3, A4)                           \
        SGC_INIT_STATIC_##C(T, S, N);                                          \
        SGC_INIT_##A1(N);                                                      \
        SGC_INIT_##A2(N);                                                      \
        SGC_INIT_##A3(N);                                                      \
        SGC_INIT_##A4(N);

#define SGC_INIT_PAIR_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, NAME, ...) NAME
#define SGC_INIT_PAIR(...)                                                     \
        SGC_INIT_PAIR_N(__VA_ARGS__, SGC_INIT_PAIR9, SGC_INIT_PAIR8,           \
                        SGC_INIT_PAIR7, SGC_INIT_PAIR6, SGC_INIT_PAIR5,        \
                        SGC_INIT_PAIR4)                                        \
        (__VA_ARGS__)

#define SGC_INIT_PAIR4(C, K, V, N) SGC_INIT_##C(K, V, N);

#define SGC_INIT_PAIR5(C, K, V, N, A1)                                         \
        SGC_INIT_##C(K, V, N);                                                 \
        SGC_INIT_##A1(N);

#define SGC_INIT_PAIR6(C, K, V, N, A1, A2)                                     \
        SGC_INIT_##C(K, V, N);                                                 \
        SGC_INIT_##A1(N);                                                      \
        SGC_INIT_##A2(N);

#define SGC_INIT_PAIR7(C, K, V, N, A1, A2, A3)                                 \
        SGC_INIT_##C(K, V, N);                                                 \
        SGC_INIT_##A1(N);                                                      \
        SGC_INIT_##A2(N);                                                      \
        SGC_INIT_##A3(N);

#define SGC_INIT_PAIR8(C, K, V, N, A1, A2, A3, A4)                             \
        SGC_INIT_##C(K, V, N);                                                 \
        SGC_INIT_##A1(N);                                                      \
        SGC_INIT_##A2(N);                                                      \
        SGC_INIT_##A3(N);                                                      \
        SGC_INIT_##A4(N);

#define SGC_INIT_PAIR9(C, K, V, N, A1, A2, A3, A4, A5)                         \
        SGC_INIT_##C(K, V, N);                                                 \
        SGC_INIT_##A1(N);                                                      \
        SGC_INIT_##A2(N);                                                      \
        SGC_INIT_##A3(N);                                                      \
        SGC_INIT_##A4(N);                                                      \
        SGC_INIT_##A5(N);

#define SGC_INIT_STATIC_PAIR_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NAME, ...)  \
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
        SGC_INIT_##A1(N);

#define SGC_INIT_STATIC_PAIR7(C, K, V, S, N, A1, A2)                           \
        SGC_INIT_STATIC_##C(K, V, S, N);                                       \
        SGC_INIT_##A1(N);                                                      \
        SGC_INIT_##A2(N);

#define SGC_INIT_STATIC_PAIR8(C, K, V, S, N, A1, A2, A3)                       \
        SGC_INIT_STATIC_##C(K, V, S, N);                                       \
        SGC_INIT_##A1(N);                                                      \
        SGC_INIT_##A2(N);                                                      \
        SGC_INIT_##A3(N);

#define SGC_INIT_STATIC_PAIR9(C, K, V, S, N, A1, A2, A3, A4)                   \
        SGC_INIT_STATIC_##C(K, V, S, N);                                       \
        \ SGC_INIT_##A1(N);                                                    \
        SGC_INIT_##A2(N);                                                      \
        SGC_INIT_##A3(N);                                                      \
        SGC_INIT_##A4(N);

#define SGC_INIT_STATIC_PAIR10(C, K, V, S, N, A1, A2, A3, A4, A5)              \
        SGC_INIT_STATIC_##C(K, V, S, N);                                       \
        SGC_INIT_##A1(N);                                                      \
        SGC_INIT_##A2(N);                                                      \
        SGC_INIT_##A3(N);                                                      \
        SGC_INIT_##A4(N);                                                      \
        SGC_INIT_##A5(N);

#define SGC_INIT_ITERATE(N)                                                    \
        void N##_fold_range(                                                   \
            struct N##_iterator begin, struct N##_iterator end,                \
            void (*fun)(const N##_type *const, void *), void *argout)          \
        {                                                                      \
                if(!N##_iterator_valid(begin) || !N##_iterator_valid(end))     \
                {                                                              \
                        return;                                                \
                }                                                              \
                fun(N##_iterator_value(begin), argout);                        \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_next(&begin);                             \
                        fun(N##_iterator_value(begin), argout);                \
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
                fun(N##_iterator_value(begin));                                \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_next(&begin);                             \
                        fun(N##_iterator_value(begin));                        \
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
                fprintf(file, format, *N##_iterator_value(begin));             \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_next(&begin);                             \
                        fprintf(file, format, *N##_iterator_value(begin));     \
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
                sprintf(buff, format, *N##_iterator_value(begin));             \
                buff += strlen(buff);                                          \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_next(&begin);                             \
                        sprintf(buff, format, *N##_iterator_value(begin));     \
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
                fun(N##_iterator_value(end), argout);                          \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_prev(&end);                               \
                        fun(N##_iterator_value(end), argout);                  \
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
                fun(N##_iterator_value(end));                                  \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_prev(&end);                               \
                        fun(N##_iterator_value(end));                          \
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
                fprintf(file, format, *N##_iterator_value(end));               \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_prev(&end);                               \
                        fprintf(file, format, *N##_iterator_value(end));       \
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
                sprintf(buff, format, *N##_iterator_value(end));               \
                buff += strlen(buff);                                          \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_prev(&end);                               \
                        sprintf(buff, format, *N##_iterator_value(end));       \
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

#define SGC_INIT_FIND(N)                                                       \
        N##_type *N##_find_el_range(struct N##_iterator begin,                 \
                                    struct N##_iterator end,                   \
                                    const N##_type el)                         \
        {                                                                      \
                N##_type *ret = NULL;                                          \
                if(N##_iterator_valid(begin) || N##_iterator_valid(end))       \
                {                                                              \
                        if(N##_element_equal(&el, N##_iterator_value(begin)))  \
                        {                                                      \
                                ret = N##_iterator_value(begin);               \
                        }                                                      \
                        while(!ret && !N##_iterator_equal(begin, end))         \
                        {                                                      \
                                N##_iterator_next(&begin);                     \
                                if(N##_element_equal(                          \
                                       &el, N##_iterator_value(begin)))        \
                                {                                              \
                                        ret = N##_iterator_value(begin);       \
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
                if(!N##_element_equal(&el, N##_iterator_value(begin)))         \
                {                                                              \
                        while(!N##_iterator_equal(begin, end))                 \
                        {                                                      \
                                ++ret;                                         \
                                N##_iterator_next(&begin);                     \
                                if(N##_element_equal(                          \
                                       &el, N##_iterator_value(begin)))        \
                                {                                              \
                                        found = 1;                             \
                                        break;                                 \
                                }                                              \
                        }                                                      \
                }                                                              \
                if(!N##_element_equal(&el, N##_iterator_value(begin)))         \
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
                        if(N##_element_equal(&el, N##_iterator_value(begin)))  \
                        {                                                      \
                                ++ret;                                         \
                        }                                                      \
                        while(!N##_iterator_equal(begin, end))                 \
                        {                                                      \
                                N##_iterator_next(&begin);                     \
                                if(N##_element_equal(                          \
                                       &el, N##_iterator_value(begin)))        \
                                {                                              \
                                        ++ret;                                 \
                                }                                              \
                        }                                                      \
                }                                                              \
                return ret;                                                    \
        }

#define SGC_INIT_FIND_ITERATOR(N)                                              \
        struct N##_iterator N##_find_range(struct N##_iterator begin,          \
                                           struct N##_iterator end,            \
                                           const N##_type el)                  \
        {                                                                      \
                struct N##_iterator ret = end;                                 \
                int done = 0;                                                  \
                if(N##_iterator_valid(begin) || N##_iterator_valid(end))       \
                {                                                              \
                        if(N##_element_equal(&el, N##_iterator_value(begin)))  \
                        {                                                      \
                                ret = begin;                                   \
                                done = 1;                                      \
                        }                                                      \
                        while(!done && !N##_iterator_equal(begin, end))        \
                        {                                                      \
                                N##_iterator_next(&begin);                     \
                                if(N##_element_equal(                          \
                                       &el, N##_iterator_value(begin)))        \
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
                                if(N##_element_equal(curr, &el))               \
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
                                if(N##_element_equal(curr, &el))               \
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

#define SGC_INIT_ITERATE_PAIR(N)                                               \
        void N##_fold_range_pair(                                              \
            struct N##_iterator begin, struct N##_iterator end,                \
            void (*fun)(const N##_key *const, const N##_value *const, void *), \
            void *argout)                                                      \
        {                                                                      \
                if(!N##_iterator_valid(begin) || !N##_iterator_valid(end))     \
                {                                                              \
                        return;                                                \
                }                                                              \
                fun(N##_iterator_key(begin), N##_iterator_value(begin),        \
                    argout);                                                   \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_next(&begin);                             \
                        fun(N##_iterator_key(begin),                           \
                            N##_iterator_value(begin), argout);                \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_fold_pair(                                                    \
            const N *const c,                                                  \
            void (*fun)(const N##_key *const, const N##_value *const, void *), \
            void *argout)                                                      \
        {                                                                      \
                N##_fold_range_pair(N##_cbegin(c), N##_cend(c), fun, argout);  \
        }                                                                      \
                                                                               \
        void N##_execute_range_pair(                                           \
            struct N##_iterator begin, struct N##_iterator end,                \
            void (*fun)(const N##_key *const, const N##_value *const))         \
        {                                                                      \
                if(!N##_iterator_valid(begin) || !N##_iterator_valid(end))     \
                {                                                              \
                        return;                                                \
                }                                                              \
                fun(N##_iterator_key(begin), N##_iterator_value(begin));       \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_next(&begin);                             \
                        fun(N##_iterator_key(begin),                           \
                            N##_iterator_value(begin));                        \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_execute_pair(                                                 \
            const N *const c,                                                  \
            void (*fun)(const N##_key *const, const N##_value *const))         \
        {                                                                      \
                N##_execute_range_pair(N##_cbegin(c), N##_cend(c), fun);       \
        }                                                                      \
                                                                               \
        void N##_fprintf_range_pair(struct N##_iterator begin,                 \
                                    struct N##_iterator end,                   \
                                    const char *const format, FILE *file)      \
        {                                                                      \
                if(!N##_iterator_valid(begin) || !N##_iterator_valid(end))     \
                {                                                              \
                        return;                                                \
                }                                                              \
                fprintf(file, format, *N##_iterator_key(begin),                \
                        *N##_iterator_value(begin));                           \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_next(&begin);                             \
                        fprintf(file, format, *N##_iterator_key(begin),        \
                                *N##_iterator_value(begin));                   \
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
                sprintf(buff, format, *N##_iterator_key(begin),                \
                        *N##_iterator_value(begin));                           \
                buff += strlen(buff);                                          \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_next(&begin);                             \
                        sprintf(buff, format, *N##_iterator_key(begin),        \
                                *N##_iterator_value(begin));                   \
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
        void N##_fold_range_reverse_pair(                                      \
            struct N##_iterator begin, struct N##_iterator end,                \
            void (*fun)(const N##_key *const, const N##_value *const, void *), \
            void *argout)                                                      \
        {                                                                      \
                if(!N##_iterator_valid(begin) || !N##_iterator_valid(end))     \
                {                                                              \
                        return;                                                \
                }                                                              \
                fun(N##_iterator_key(end), N##_iterator_value(end), argout);   \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_prev(&end);                               \
                        fun(N##_iterator_key(end), N##_iterator_value(end),    \
                            argout);                                           \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_fold_reverse_pair(                                            \
            const N *const c,                                                  \
            void (*fun)(const N##_key *const, const N##_value *const, void *), \
            void *argout)                                                      \
        {                                                                      \
                N##_fold_range_reverse_pair(N##_cbegin(c), N##_cend(c), fun,   \
                                            argout);                           \
        }                                                                      \
                                                                               \
        void N##_execute_range_reverse_pair(                                   \
            struct N##_iterator begin, struct N##_iterator end,                \
            void (*fun)(const N##_key *const, const N##_value *const))         \
        {                                                                      \
                if(!N##_iterator_valid(begin) || !N##_iterator_valid(end))     \
                {                                                              \
                        return;                                                \
                }                                                              \
                fun(N##_iterator_key(end), N##_iterator_value(end));           \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_prev(&end);                               \
                        fun(N##_iterator_key(end), N##_iterator_value(end));   \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_execute_reverse_pair(                                         \
            const N *const c,                                                  \
            void (*fun)(const N##_key *const, const N##_value *const))         \
        {                                                                      \
                N##_execute_range_reverse_pair(N##_cbegin(c), N##_cend(c),     \
                                               fun);                           \
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
                fprintf(file, format, *N##_iterator_key(end),                  \
                        *N##_iterator_value(end));                             \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_prev(&end);                               \
                        fprintf(file, format, *N##_iterator_key(end),          \
                                *N##_iterator_value(end));                     \
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
                sprintf(buff, format, *N##_iterator_key(end),                  \
                        *N##_iterator_value(end));                             \
                buff += strlen(buff);                                          \
                while(!N##_iterator_equal(begin, end))                         \
                {                                                              \
                        N##_iterator_prev(&end);                               \
                        sprintf(buff, format, *N##_iterator_key(end),          \
                                *N##_iterator_value(end));                     \
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
