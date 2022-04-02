#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_sort_stack.h"
#include "detail/sgc_utils.h"

#define SGC_INIT_HEADERS_ITERATE(T, N)                                         \
    void N##_fold_range(N##_it begin, N##_it end,                              \
                        void (*fun)(const N##_type* const, void*),             \
                        void* argout);                                         \
                                                                               \
    void N##_fold(const N* const c, void (*fun)(const N##_type* const, void*), \
                  void* argout);                                               \
                                                                               \
    void N##_execute_range(N##_it begin, N##_it end,                           \
                           void (*fun)(const N##_type* const));                \
                                                                               \
    void N##_execute(const N* const c, void (*fun)(const N##_type* const));    \
                                                                               \
    void N##_fprintf_range(N##_it begin, N##_it end, const char* const format, \
                           FILE* file);                                        \
                                                                               \
    void N##_fprintf(const N* const c, const char* const format, FILE* file);  \
                                                                               \
    void N##_fold_range_reverse(N##_it begin, N##_it end,                      \
                                void (*fun)(const N##_type* const, void*),     \
                                void* argout);                                 \
                                                                               \
    void N##_fold_reverse(const N* const c,                                    \
                          void (*fun)(const N##_type* const, void*),           \
                          void* argout);                                       \
                                                                               \
    void N##_execute_range_reverse(N##_it begin, N##_it end,                   \
                                   void (*fun)(const N##_type* const));        \
                                                                               \
    void N##_execute_reverse(const N* const c,                                 \
                             void (*fun)(const N##_type* const));              \
                                                                               \
    void N##_fprintf_range_reverse(N##_it begin, N##_it end,                   \
                                   const char* const format, FILE* file);      \
                                                                               \
    void N##_fprintf_reverse(const N* const c, const char* const format,       \
                             FILE* file);

#define SGC_INIT_HEADERS_FIND(T, N)                                            \
    N##_type* N##_find_el_range(N##_it begin, N##_it end, const N##_type el);  \
                                                                               \
    N##_type* N##_find_el(const N* const c, const N##_type el);                \
                                                                               \
    int N##_find_index(const N* const c, const N##_type el);                   \
                                                                               \
    size_t N##_count(const N* const c, const N##_type el);

#define SGC_INIT_HEADERS_FIND_IT(T, N)                                         \
    N##_it N##_find_range_it(N##_it begin, N##_it end, const N##_type el);     \
                                                                               \
    N##_it N##_find_it(const N* const c, const N##_type el);

#define SGC_INIT_HEADERS_BINARY_FIND(T, N)                                     \
    N##_type* N##_binary_find_el(N* c, const N##_type el);                     \
                                                                               \
    size_t N##_binary_find_index(N* c, const N##_type el);

#define SGC_INIT_HEADERS_ITERATE_PAIR(V, N)                                    \
    void N##_fprintf_range_pair(N##_it begin, N##_it end,                      \
                                const char* const format, FILE* file);         \
                                                                               \
    void N##_fprintf_pair(const N* const c, const char* const format,          \
                          FILE* file);                                         \
                                                                               \
    void N##_fprintf_range_reverse_pair(N##_it begin, N##_it end,              \
                                        const char* const format, FILE* file); \
                                                                               \
    void N##_fprintf_reverse_pair(const N* const c, const char* const format,  \
                                  FILE* file);

#define _SGC_INIT_PP_QSORT(T, N)                                               \
    static void _p_##N##_memswp(char* i, char* j);                             \
    static void _p_##N##_qsort(void* array, size_t array_size,                 \
                               int (*comp)(const void*, const void*));

#define SGC_INIT_HEADERS_QSORT(T, N)                                           \
    void N##_sort(N* c, int (*comp)(const void*, const void*));

#define SGC_INIT_ITERATE(T, N)                                                 \
    SGC_INIT_HEADERS_ITERATE(T, N)                                             \
    void N##_fold_range(N##_it begin, N##_it end,                              \
                        void (*fun)(const N##_type* const, void*),             \
                        void* argout) {                                        \
        if (!N##_it_valid(begin) || !N##_it_valid(end)) {                      \
            return;                                                            \
        }                                                                      \
        fun(N##_it_data(begin), argout);                                       \
        while (!N##_it_equal(begin, end)) {                                    \
            N##_it_go_next(&begin);                                            \
            fun(N##_it_data(begin), argout);                                   \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_fold(const N* const c, void (*fun)(const N##_type* const, void*), \
                  void* argout) {                                              \
        N##_fold_range(N##_cbegin(c), N##_cend(c), fun, argout);               \
    }                                                                          \
                                                                               \
    void N##_execute_range(N##_it begin, N##_it end,                           \
                           void (*fun)(const N##_type* const)) {               \
        if (!N##_it_valid(begin) || !N##_it_valid(end)) {                      \
            return;                                                            \
        }                                                                      \
        fun(N##_it_data(begin));                                               \
        while (!N##_it_equal(begin, end)) {                                    \
            N##_it_go_next(&begin);                                            \
            fun(N##_it_data(begin));                                           \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_execute(const N* const c, void (*fun)(const N##_type* const)) {   \
        N##_execute_range(N##_cbegin(c), N##_cend(c), fun);                    \
    }                                                                          \
                                                                               \
    void N##_fprintf_range(N##_it begin, N##_it end, const char* const format, \
                           FILE* file) {                                       \
        if (!N##_it_valid(begin) || !N##_it_valid(end)) {                      \
            return;                                                            \
        }                                                                      \
        fprintf(file, format, *N##_it_data(begin));                            \
        while (!N##_it_equal(begin, end)) {                                    \
            N##_it_go_next(&begin);                                            \
            fprintf(file, format, *N##_it_data(begin));                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_fprintf(const N* const c, const char* const format, FILE* file) { \
        N##_fprintf_range(N##_cbegin(c), N##_cend(c), format, file);           \
    }                                                                          \
                                                                               \
    void N##_sprintf_range(N##_it begin, N##_it end, const char* const format, \
                           char* buff) {                                       \
        if (!N##_it_valid(begin) || !N##_it_valid(end)) {                      \
            return;                                                            \
        }                                                                      \
        sprintf(buff, format, *N##_it_data(begin));                            \
        buff += strlen(buff);                                                  \
        while (!N##_it_equal(begin, end)) {                                    \
            N##_it_go_next(&begin);                                            \
            sprintf(buff, format, *N##_it_data(begin));                        \
            buff += strlen(buff);                                              \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_sprintf(const N* const c, const char* const format, char* buff) { \
        N##_sprintf_range(N##_cbegin(c), N##_cend(c), format, buff);           \
    }                                                                          \
                                                                               \
    void N##_fold_range_reverse(N##_it begin, N##_it end,                      \
                                void (*fun)(const N##_type* const, void*),     \
                                void* argout) {                                \
        if (!N##_it_valid(begin) || !N##_it_valid(end)) {                      \
            return;                                                            \
        }                                                                      \
        fun(N##_it_data(end), argout);                                         \
        while (!N##_it_equal(begin, end)) {                                    \
            N##_it_go_prev(&end);                                              \
            fun(N##_it_data(end), argout);                                     \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_fold_reverse(const N* const c,                                    \
                          void (*fun)(const N##_type* const, void*),           \
                          void* argout) {                                      \
        N##_fold_range_reverse(N##_cbegin(c), N##_cend(c), fun, argout);       \
    }                                                                          \
                                                                               \
    void N##_execute_range_reverse(N##_it begin, N##_it end,                   \
                                   void (*fun)(const N##_type* const)) {       \
        if (!N##_it_valid(begin) || !N##_it_valid(end)) {                      \
            return;                                                            \
        }                                                                      \
        fun(N##_it_data(end));                                                 \
        while (!N##_it_equal(begin, end)) {                                    \
            N##_it_go_prev(&end);                                              \
            fun(N##_it_data(end));                                             \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_execute_reverse(const N* const c,                                 \
                             void (*fun)(const N##_type* const)) {             \
        N##_execute_range_reverse(N##_cbegin(c), N##_cend(c), fun);            \
    }                                                                          \
                                                                               \
    void N##_fprintf_range_reverse(N##_it begin, N##_it end,                   \
                                   const char* const format, FILE* file) {     \
        if (!N##_it_valid(begin) || !N##_it_valid(end)) {                      \
            return;                                                            \
        }                                                                      \
        fprintf(file, format, *N##_it_data(end));                              \
        while (!N##_it_equal(begin, end)) {                                    \
            N##_it_go_prev(&end);                                              \
            fprintf(file, format, *N##_it_data(end));                          \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_fprintf_reverse(const N* const c, const char* const format,       \
                             FILE* file) {                                     \
        N##_fprintf_range_reverse(N##_cbegin(c), N##_cend(c), format, file);   \
    }                                                                          \
                                                                               \
    void N##_sprintf_range_reverse(N##_it begin, N##_it end,                   \
                                   const char* const format, char* buff) {     \
        if (!N##_it_valid(begin) || !N##_it_valid(end)) {                      \
            return;                                                            \
        }                                                                      \
        sprintf(buff, format, *N##_it_data(end));                              \
        buff += strlen(buff);                                                  \
        while (!N##_it_equal(begin, end)) {                                    \
            N##_it_go_prev(&end);                                              \
            sprintf(buff, format, *N##_it_data(end));                          \
            buff += strlen(buff);                                              \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_sprintf_reverse(const N* const c, const char* const format,       \
                             char* buff) {                                     \
        N##_sprintf_range_reverse(N##_cbegin(c), N##_cend(c), format, buff);   \
    }

#define SGC_INIT_FIND(T, N)                                                    \
    SGC_INIT_HEADERS_FIND(T, N)                                                \
    N##_type* N##_find_el_range(N##_it begin, N##_it end, const N##_type el) { \
        if (N##_it_valid(begin) || N##_it_valid(end)) {                        \
            if (T##_equal(&el, N##_it_data(begin))) {                          \
                return N##_it_data(begin);                                     \
            }                                                                  \
            while (!N##_it_equal(begin, end)) {                                \
                N##_it_go_next(&begin);                                        \
                if (T##_equal(&el, N##_it_data(begin))) {                      \
                    return N##_it_data(begin);                                 \
                }                                                              \
            }                                                                  \
        }                                                                      \
        return NULL;                                                           \
    }                                                                          \
                                                                               \
    N##_type* N##_find_el(const N* const c, const N##_type el) {               \
        return N##_find_el_range(N##_cbegin(c), N##_cend(c), el);              \
    }                                                                          \
                                                                               \
    int N##_find_index(const N* const c, const N##_type el) {                  \
        int ret = -1;                                                          \
        int found = 0;                                                         \
        N##_it begin = N##_cbegin(c);                                          \
        N##_it end = N##_cend(c);                                              \
        if (!T##_equal(&el, N##_it_data(begin))) {                             \
            while (!N##_it_equal(begin, end)) {                                \
                ++ret;                                                         \
                N##_it_go_next(&begin);                                        \
                if (T##_equal(&el, N##_it_data(begin))) {                      \
                    found = 1;                                                 \
                    break;                                                     \
                }                                                              \
            }                                                                  \
        }                                                                      \
        if (!T##_equal(&el, N##_it_data(begin))) {                             \
            ++ret;                                                             \
            found = 1;                                                         \
        }                                                                      \
        ret = (found == 1) ? ret + 1 : -1;                                     \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    size_t N##_count(const N* const c, const N##_type el) {                    \
        size_t ret = 0;                                                        \
        N##_it begin = N##_cbegin(c);                                          \
        N##_it end = N##_cend(c);                                              \
        if (N##_it_valid(begin) || N##_it_valid(end)) {                        \
            if (T##_equal(&el, N##_it_data(begin))) {                          \
                ++ret;                                                         \
            }                                                                  \
            while (!N##_it_equal(begin, end)) {                                \
                N##_it_go_next(&begin);                                        \
                if (T##_equal(&el, N##_it_data(begin))) {                      \
                    ++ret;                                                     \
                }                                                              \
            }                                                                  \
        }                                                                      \
        return ret;                                                            \
    }

#define SGC_INIT_FIND_IT(T, N)                                                 \
    SGC_INIT_HEADERS_FIND_IT(T, N)                                             \
    N##_it N##_find_range_it(N##_it begin, N##_it end, const N##_type el) {    \
        if (N##_it_valid(begin) || N##_it_valid(end)) {                        \
            if (T##_equal(&el, N##_it_data(begin))) {                          \
                return begin;                                                  \
            }                                                                  \
            while (!N##_it_equal(begin, end)) {                                \
                N##_it_go_next(&begin);                                        \
                if (T##_equal(&el, N##_it_data(begin))) {                      \
                    return begin;                                              \
                }                                                              \
            }                                                                  \
        }                                                                      \
        return begin;                                                          \
    }                                                                          \
                                                                               \
    N##_it N##_find_it(const N* const c, const N##_type el) {                  \
        return N##_find_range_it(N##_cbegin(c), N##_cend(c), el);              \
    }

#define SGC_INIT_BINARY_FIND(T, N)                                             \
    SGC_INIT_HEADERS_BINARY_FIND(T, N)                                         \
    N##_type* N##_binary_find_el(N* c, const N##_type el) {                    \
        N##_type* ret = NULL;                                                  \
        if (!N##_empty(c)) {                                                   \
            int l = 0;                                                         \
            int r = N##_size(c) - 1;                                           \
            int m;                                                             \
            while (l <= r) {                                                   \
                m = l + (r - l) / 2;                                           \
                N##_type* curr = N##_at(c, m);                                 \
                if (T##_equal(curr, &el)) {                                    \
                    ret = N##_at(c, m);                                        \
                    break;                                                     \
                }                                                              \
                                                                               \
                if (T##_compare(curr, &el) < 0) {                              \
                    l = m + 1;                                                 \
                } else {                                                       \
                    r = m - 1;                                                 \
                }                                                              \
            }                                                                  \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    size_t N##_binary_find_index(N* c, const N##_type el) {                    \
        size_t ret = N##_size(c) + 1;                                          \
        if (!N##_empty(c)) {                                                   \
            int l = 0;                                                         \
            int r = N##_size(c) - 1;                                           \
            int m;                                                             \
            while (l <= r) {                                                   \
                m = l + (r - l) / 2;                                           \
                N##_type* curr = N##_at(c, m);                                 \
                if (T##_equal(curr, &el)) {                                    \
                    ret = m;                                                   \
                    break;                                                     \
                }                                                              \
                                                                               \
                if (T##_compare(curr, &el) < 0) {                              \
                    l = m + 1;                                                 \
                } else {                                                       \
                    r = m - 1;                                                 \
                }                                                              \
            }                                                                  \
        }                                                                      \
        return ret;                                                            \
    }

#define SGC_INIT_ITERATE_PAIR(T, N)                                            \
    SGC_INIT_HEADERS_ITERATE_PAIR(T, N)                                        \
    void N##_fprintf_range_pair(N##_it begin, N##_it end,                      \
                                const char* const format, FILE* file) {        \
        if (!N##_it_valid(begin) || !N##_it_valid(end)) {                      \
            return;                                                            \
        }                                                                      \
        fprintf(file, format, N##_it_data(begin)->key,                         \
                N##_it_data(begin)->value);                                    \
        while (!N##_it_equal(begin, end)) {                                    \
            N##_it_go_next(&begin);                                            \
            fprintf(file, format, N##_it_data(begin)->key,                     \
                    N##_it_data(begin)->value);                                \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_fprintf_pair(const N* const c, const char* const format,          \
                          FILE* file) {                                        \
        N##_fprintf_range_pair(N##_cbegin(c), N##_cend(c), format, file);      \
    }                                                                          \
                                                                               \
    void N##_sprintf_range_pair(N##_it begin, N##_it end,                      \
                                const char* const format, char* buff) {        \
        if (!N##_it_valid(begin) || !N##_it_valid(end)) {                      \
            return;                                                            \
        }                                                                      \
        sprintf(buff, format, N##_it_data(begin)->key,                         \
                N##_it_data(begin)->value);                                    \
        buff += strlen(buff);                                                  \
        while (!N##_it_equal(begin, end)) {                                    \
            N##_it_go_next(&begin);                                            \
            sprintf(buff, format, N##_it_data(begin)->key,                     \
                    N##_it_data(begin)->value);                                \
            buff += strlen(buff);                                              \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_sprintf_pair(const N* const c, const char* const format,          \
                          char* buff) {                                        \
        N##_sprintf_range_pair(N##_cbegin(c), N##_cend(c), format, buff);      \
    }                                                                          \
                                                                               \
    void N##_fprintf_range_reverse_pair(N##_it begin, N##_it end,              \
                                        const char* const format,              \
                                        FILE* file) {                          \
        if (!N##_it_valid(begin) || !N##_it_valid(end)) {                      \
            return;                                                            \
        }                                                                      \
        fprintf(file, format, N##_it_data(end)->key, N##_it_data(end)->value); \
        while (!N##_it_equal(begin, end)) {                                    \
            N##_it_go_prev(&end);                                              \
            fprintf(file, format, N##_it_data(end)->key,                       \
                    N##_it_data(end)->value);                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_fprintf_reverse_pair(const N* const c, const char* const format,  \
                                  FILE* file) {                                \
        N##_fprintf_range_reverse_pair(N##_cbegin(c), N##_cend(c), format,     \
                                       file);                                  \
    }                                                                          \
                                                                               \
    void N##_sprintf_range_reverse_pair(N##_it begin, N##_it end,              \
                                        const char* const format,              \
                                        char* buff) {                          \
        if (!N##_it_valid(begin) || !N##_it_valid(end)) {                      \
            return;                                                            \
        }                                                                      \
        sprintf(buff, format, N##_it_data(end)->value, N##_it_data(end)->key); \
        buff += strlen(buff);                                                  \
        while (!N##_it_equal(begin, end)) {                                    \
            N##_it_go_prev(&end);                                              \
            sprintf(buff, format, N##_it_data(end)->key,                       \
                    N##_it_data(end)->value);                                  \
            buff += strlen(buff);                                              \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_sprintf_reverse_pair(const N* const c, const char* const format,  \
                                  char* buff) {                                \
        N##_sprintf_range_reverse_pair(N##_cbegin(c), N##_cend(c), format,     \
                                       buff);                                  \
    }

#define SGC_INIT_QSORT(T, N)                                                   \
    SGC_INIT_HEADERS_QSORT(T, N)                                               \
    _SGC_INIT_PP_QSORT(T, N)                                                   \
    static void _p_##N##_memswp(char* i, char* j) {                            \
        N##_type tmp;                                                          \
                                                                               \
        memcpy(&tmp, i, sizeof(N##_type));                                     \
        memcpy(i, j, sizeof(N##_type));                                        \
        memcpy(j, &tmp, sizeof(N##_type));                                     \
    }                                                                          \
                                                                               \
    static void _p_##N##_qsort(void* array, size_t array_size,                 \
                               int (*comp)(const void*, const void*)) {        \
        char *i, *j;                                                           \
        size_t thresh = SGC_STACK_THRESH * sizeof(N##_type);                   \
        char* array_ = (char*)array;                                           \
        char* limit = array_ + array_size * sizeof(N##_type);                  \
        SGC_PREPARE_STACK;                                                     \
                                                                               \
        while (1) {                                                            \
            if ((size_t)(limit - array_) > thresh) {                           \
                i = array_ + sizeof(N##_type);                                 \
                j = limit - sizeof(N##_type);                                  \
                _p_##N##_memswp(((((size_t)(limit - array_)) /                 \
                                  sizeof(N##_type)) /                          \
                                 2) * sizeof(N##_type) +                       \
                                    array_,                                    \
                                array_);                                       \
                if (comp(i, j) > 0) {                                          \
                    _p_##N##_memswp(i, j);                                     \
                }                                                              \
                if (comp(array_, j) > 0) {                                     \
                    _p_##N##_memswp(array_, j);                                \
                }                                                              \
                if (comp(i, array_) > 0) {                                     \
                    _p_##N##_memswp(i, array_);                                \
                }                                                              \
                while (1) {                                                    \
                    do {                                                       \
                        i += sizeof(N##_type);                                 \
                    } while (comp(array_, i) > 0);                             \
                    do {                                                       \
                        j -= sizeof(N##_type);                                 \
                    } while (comp(j, array_) > 0);                             \
                    if (i > j) {                                               \
                        break;                                                 \
                    }                                                          \
                    _p_##N##_memswp(i, j);                                     \
                }                                                              \
                _p_##N##_memswp(array_, j);                                    \
                if (j - array_ > limit - i) {                                  \
                    SGC_STACK_PUSH(array_, j);                                 \
                    array_ = i;                                                \
                } else {                                                       \
                    SGC_STACK_PUSH(i, limit);                                  \
                    limit = j;                                                 \
                }                                                              \
            } else {                                                           \
                for (j = array_, i = j + sizeof(N##_type); i < limit;          \
                     j = i, i += sizeof(N##_type)) {                           \
                    for (; comp(j, j + sizeof(N##_type)) > 0;                  \
                         j -= sizeof(N##_type)) {                              \
                        _p_##N##_memswp(j, j + sizeof(N##_type));              \
                        if (j == array_) {                                     \
                            break;                                             \
                        }                                                      \
                    }                                                          \
                }                                                              \
                if (stackptr != stack) {                                       \
                    SGC_STACK_POP(array_, limit);                              \
                } else {                                                       \
                    break;                                                     \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
    void N##_sort(N* c, int (*comp)(const void*, const void*)) {               \
        if (comp == NULL) {                                                    \
            comp = T##_void_compare;                                           \
        }                                                                      \
        _p_##N##_qsort(N##_array(c), N##_size(c), comp);                       \
    }
