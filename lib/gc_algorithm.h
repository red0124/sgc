#pragma once

#define INIT_NONE(N)

#define INIT_ITERATE(N)                                                        \
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
        void N##_fold(const struct N *const c,                                 \
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
        void N##_execute(const struct N *const c,                              \
                         void (*fun)(const N##_type *const))                   \
        {                                                                      \
                N##_execute_range(N##_cbegin(c), N##_cend(c), fun);            \
        }                                                                      \
                                                                               \
        void N##_write_range(struct N##_iterator begin,                        \
                             struct N##_iterator end,                          \
                             const char *const format, FILE *file)             \
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
        void N##_write(const struct N *const c, const char *const format,      \
                       FILE *file)                                             \
        {                                                                      \
                N##_write_range(N##_cbegin(c), N##_cend(c), format, file);     \
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
        void N##_fold_reverse(const struct N *const c,                         \
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
        void N##_execute_reverse(const struct N *const c,                      \
                                 void (*fun)(const N##_type *const))           \
        {                                                                      \
                N##_execute_range_reverse(N##_cbegin(c), N##_cend(c), fun);    \
        }                                                                      \
                                                                               \
        void N##_write_range_reverse(struct N##_iterator begin,                \
                                     struct N##_iterator end,                  \
                                     const char *const format, FILE *file)     \
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
        void N##_write_reverse(const struct N *const c,                        \
                               const char *const format, FILE *file)           \
        {                                                                      \
                N##_write_range_reverse(N##_cbegin(c), N##_cend(c), format,    \
                                        file);                                 \
        }

#define INIT_FIND(N)                                                           \
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
        N##_type *N##_find_el(const struct N *const c, const N##_type el)      \
        {                                                                      \
                return N##_find_el_range(N##_cbegin(c), N##_cend(c), el);      \
        }                                                                      \
                                                                               \
        ssize_t N##_find_index(const struct N *const c, const N##_type el)     \
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

#define INIT_ALGORITHM(N)                                                      \
        INIT_ITERATE(N)                                                        \
        INIT_FIND(N)

#define INIT_FIND_ITERATOR(N)                                                  \
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
        struct N##_iterator N##_find(const struct N *const c,                  \
                                     const N##_type el)                        \
        {                                                                      \
                return N##_find_range(N##_cbegin(c), N##_cend(c), el);         \
        }

#define INIT_BINARY_FIND(T, N)                                                 \
        N##_type *N##_binary_find_el(struct N *c, const N##_type el)           \
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
        size_t N##_binary_find_index(struct N *c, const N##_type el)           \
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

#define INIT_ITERATE_PAIR(N)                                                   \
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
            const struct N *const c,                                           \
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
            const struct N *const c,                                           \
            void (*fun)(const N##_key *const, const N##_value *const))         \
        {                                                                      \
                N##_execute_range_pair(N##_cbegin(c), N##_cend(c), fun);       \
        }                                                                      \
                                                                               \
        void N##_write_range_pair(struct N##_iterator begin,                   \
                                  struct N##_iterator end,                     \
                                  const char *const format, FILE *file)        \
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
        void N##_write_pair(const struct N *const c, const char *const format, \
                            FILE *file)                                        \
        {                                                                      \
                N##_write_range_pair(N##_cbegin(c), N##_cend(c), format,       \
                                     file);                                    \
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
            const struct N *const c,                                           \
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
            const struct N *const c,                                           \
            void (*fun)(const N##_key *const, const N##_value *const))         \
        {                                                                      \
                N##_execute_range_reverse_pair(N##_cbegin(c), N##_cend(c),     \
                                               fun);                           \
        }                                                                      \
                                                                               \
        void N##_write_range_reverse_pair(                                     \
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
        void N##_write_reverse_pair(const struct N *const c,                   \
                                    const char *const format, FILE *file)      \
        {                                                                      \
                N##_write_range_reverse_pair(N##_cbegin(c), N##_cend(c),       \
                                             format, file);                    \
        }

#ifndef GC_STACK
#define GC_STACK
#define GC_STACK_SIZE 64

#define GC_PREPARE_STACK                                                       \
        char *stack[GC_STACK_SIZE];                                            \
        char **stackptr = stack

#define GC_STACK_PUSH(array, limit)                                            \
        stackptr[0] = array;                                                   \
        stackptr[1] = limit;                                                   \
        stackptr += 2

#define GC_STACK_POP(array, limit)                                             \
        stackptr -= 2;                                                         \
        array = stackptr[0];                                                   \
        limit = stackptr[1]

#define GC_STACK_THRESH 7

#endif

#define INIT_QSORT(T, N)                                                       \
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
                size_t thresh = GC_STACK_THRESH * sizeof(N##_type);            \
                char *array_ = (char *)array;                                  \
                char *limit = array_ + array_size * sizeof(N##_type);          \
                GC_PREPARE_STACK;                                              \
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
                                        GC_STACK_PUSH(array_, j);              \
                                        array_ = i;                            \
                                }                                              \
                                else                                           \
                                {                                              \
                                        GC_STACK_PUSH(i, limit);               \
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
                                        GC_STACK_POP(array_, limit);           \
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

#define GC_FOR_EACH(N, C, EL, ACT)                                             \
        do                                                                     \
        {                                                                      \
                N##_type* EL;                                                  \
                struct N##_iterator __gc_it_begin = N##_cbegin(&C);            \
                struct N##_iterator __gc_it_end = N##_cend(&C);                \
                if(!N##_iterator_valid(__gc_it_begin) || 		       \
				!N##_iterator_valid(__gc_it_end))              \
                {                                                              \
                        break;                                                 \
                }                                                              \
                if(!N##_iterator_equal(__gc_it_begin, __gc_it_end))            \
                {                                                              \
                        EL = N##_iterator_value(__gc_it_begin);                \
                        do                                                     \
                        {                                                      \
                                ACT;                                           \
                        } while(0);                                            \
                }                                                              \
                while(!N##_iterator_equal(__gc_it_begin, __gc_it_end))         \
                {                                                              \
                        N##_iterator_next(&__gc_it_begin);                     \
                        EL = N##_iterator_value(__gc_it_begin);                \
                        do                                                     \
                        {                                                      \
                                ACT;                                           \
                        } while(0);                                            \
                }                                                              \
        } while(0);

#define GC_FOR_EACH_PAIR(N, C, K, V, ACT)                                      \
        do                                                                     \
        {                                                                      \
                const N##_key* K;                                              \
                N##_value* V;                                                  \
                struct N##_iterator __gc_it_begin = N##_cbegin(&C);            \
                struct N##_iterator __gc_it_end = N##_cend(&C);                \
                if(!N##_iterator_valid(__gc_it_begin) || 		       \
				!N##_iterator_valid(__gc_it_end))              \
                {                                                              \
                        break;                                                 \
                }                                                              \
                if(!N##_iterator_equal(__gc_it_begin, __gc_it_end))            \
                {                                                              \
                        V = N##_iterator_value(__gc_it_begin);                 \
                        K = N##_iterator_key(__gc_it_begin);                   \
                        do                                                     \
                        {                                                      \
                                ACT;                                           \
                        } while(0);                                            \
                }                                                              \
                while(!N##_iterator_equal(__gc_it_begin, __gc_it_end))         \
                {                                                              \
                        N##_iterator_next(&__gc_it_begin);                     \
                        V = N##_iterator_value(__gc_it_begin);                 \
                        K = N##_iterator_key(__gc_it_begin);                   \
                        do                                                     \
                        {                                                      \
                                ACT;                                           \
                        } while(0);                                            \
                }                                                              \
        } while(0);

#define GC_LC7(OUT_C, OUT, IN_C, IN, V, ACT, COND)                             \
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

#define GC_LC6(OUT_C, OUT, IN_C, IN, V, ACT)                                   \
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

#define GC_LC4(OUT_C, OUT, IN_C, IN)                                           \
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
#define GC_LC(...)                                                             \
        GET_MACRO(__VA_ARGS__, GC_LC7, GC_LC6, NONE, GC_LC4)                   \
        (__VA_ARGS__)


#define GC_SPLIT(OUT_C, OUT, STR, S, DEL)                                      \
        OUT_C OUT;                                                             \
        do                                                                     \
        {                                                                      \
		OUT_C##_init(&OUT);                                            \
                STR __gc_str_tmp = strtok(S, DEL);                         \
                while(__gc_str_tmp)                                        \
                {                                                              \
                        OUT_C##_default_insert(&OUT, __gc_str_tmp);        \
                        __gc_str_tmp = strtok(NULL, DEL);                  \
                }                                                              \
        } while(0);
