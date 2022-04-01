#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_utils.h"

#ifndef SGC_STRING_BUFF_SIZE
#define SGC_STRING_BUFF_SIZE 128
#endif

#define SGC_INIT_STRING_N(_1, _2, NAME, ...) NAME
#define SGC_INIT_STRING(...)                                                   \
    SGC_INIT_STRING_N(__VA_ARGS__, SGC_INIT_STRING2, SGC_INIT_STRING1, )       \
    (__VA_ARGS__)

#define SGC_INIT_STRING2(S, N) SGC_INIT_STRING_WITH_BUFFER(N, S)
#define SGC_INIT_STRING1(N) SGC_INIT_STRING_WITH_BUFFER(N, SGC_STRING_BUFF_SIZE)

#define SGC_INIT_HEADERS_STRING_N(_1, _2, NAME, ...) NAME
#define SGC_INIT_HEADERS_STRING(...)                                           \
    SGC_INIT_HEADERS_STRING_N(__VA_ARGS__, SGC_INIT_HEADERS_STRING2,           \
                              SGC_INIT_HEADERS_STRING1)                        \
    (__VA_ARGS__)

#define SGC_INIT_HEADERS_STRING2(S, N) SGC_INIT_HEADERS_STRING_WITH_BUFFER(N, S)

#define SGC_INIT_HEADERS_STRING1(N)                                            \
    SGC_INIT_HEADERS_STRING_WITH_BUFFER(N, SGC_STRING_BUFF_SIZE)

#define _SGC_INIT_PP_STRING_WITH_BUFFER(N, S)                     \
    static int N##_char_find(const char* const del, char c);

#define SGC_INIT_HEADERS_STRING_WITH_BUFFER(N, S)                              \
    typedef char* N;                                                           \
    typedef char N##_type;                                                     \
    typedef char static_##N[S];                                                \
    typedef char* N##_it;                                                \
                                                                               \
    void N##_copy(N* first, const N* const second);                            \
    void N##_init(N* s);                                                       \
    void N##_free(N* s);                                                       \
    size_t N##_size(N* s);                                                     \
    int N##_equal(const N* const first, const N* const second);                \
    int N##_compare(const N* const first, const N* const second);              \
    int N##_void_compare(const void* const first, const void* const second);   \
    size_t N##_hash(const N* const s);                                         \
    void N##_push_back(N* s, const char c);                                    \
    void N##_pop_back(N* s);                                                   \
    void N##_from_cstring(N* first, const char* const second);                 \
    N N##_buffer_read_until(N s, FILE* f, const char* const del);              \
    N N##_buffer_read(N s, FILE* f);                                           \
    N N##_read_until(N* s, FILE* f, const char* const del);                    \
    N N##_read(N* s, FILE* f);                                                 \
    N N##_read_file(N* s, const char* const file_name);                        \
    N##_type* N##_array(N*);                                                   \
                                                                               \
    char* N##_it_data(N##_it i);                                   \
    const char* N##_it_cdata(const N##_it i);                      \
    void N##_it_go_next(N##_it* i);                                   \
    void N##_it_go_prev(N##_it* i);                                   \
    void N##_it_begin(N* s, N##_it* i);                            \
    void N##_it_cbegin(const N* const s, N##_it* i);               \
    N##_it N##_begin(N* s);                                              \
    N##_it N##_cbegin(const N* const s);                                 \
    void N##_it_end(N* s, N##_it* i);                              \
    void N##_it_cend(const N* const s, N##_it* i);                 \
    N##_it N##_end(N* s);                                                \
    N##_it N##_cend(const N* const s);                                   \
    void N##_it_from(N* s, N##_it* i, size_t at);                  \
    void N##_it_cfrom(const N* const s, N##_it* i, size_t at);     \
    N##_it N##_from(N* s, size_t at);                                    \
    N##_it N##_cfrom(const N* const s, size_t at);                       \
    void N##_it_jump(N##_it* i, int range);                    \
    int N##_it_equal(const N##_it first,                           \
                           const N##_it second);                         \
    int N##_it_diff(const N##_it first,                       \
                               const N##_it second);                     \
    int N##_it_valid(const N##_it i);

#define SGC_INIT_STRING_WITH_BUFFER(N, S)                                      \
    SGC_INIT_HEADERS_STRING_WITH_BUFFER(N, S)                                  \
    _SGC_INIT_PP_STRING_WITH_BUFFER(N, S)                         \
                                                                               \
    void N##_copy(N* first, const N* const second) {                           \
        *first = NULL;                                                         \
        if (*second) {                                                         \
            size_t size = strlen(*second) + 1;                                 \
            *first = (N)sgc_malloc(sizeof(char) * size);                       \
            memcpy(*first, *second, size);                                     \
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
    int N##_equal(const N* const first, const N* const second) {               \
        int ret = (*first == *second);                                         \
        if (ret == 0 && *first && *second) {                                   \
            ret = strcmp(*first, *second) == 0;                                \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    int N##_compare(const N* const first, const N* const second) {             \
        return strcmp(*first, *second);                                        \
    }                                                                          \
                                                                               \
    int N##_void_compare(const void* const first, const void* const second) {  \
        return strcmp(*(N*)first, *(N*)second);                                \
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
    void N##_push_back(N* s, const char c) {                                   \
        size_t len = (*s) ? strlen(*s) : 0;                                    \
        *s = (N)sgc_realloc(*s, sizeof(char) * (len + 2));                     \
        (*s)[len] = c;                                                         \
        (*s)[len + 1] = '\0';                                                  \
    }                                                                          \
                                                                               \
    void N##_pop_back(N* s) {                                                  \
        size_t len = strlen(*s);                                               \
        if (len) {                                                             \
            (*s)[len - 1] = '\0';                                              \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_from_cstring(N* first, const char* const second) {                \
        if (*second) {                                                         \
            char* const second_p = (char*)second;                              \
            N##_copy(first, &second_p);                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    N N##_read(N* s, FILE* f) {                                                \
        *s = NULL;                                                             \
        char buff[S] = "\0";                                                   \
        if (fgets(buff, S - 1, f)) {                                           \
            size_t size = strlen(buff);                                        \
            *s = (N)sgc_malloc(sizeof(char) * (size + 1));                     \
            memcpy(*s, buff, sizeof(char) * (size + 1));                       \
        }                                                                      \
        return *s;                                                             \
    }                                                                          \
                                                                               \
    static int N##_char_find(const char* const del, char c) {                  \
        int ret = 0;                                                           \
        size_t size = strlen(del);                                             \
        for (size_t i = 0; i < size; ++i) {                                    \
            if (del[i] == c) {                                                 \
                ret = 1;                                                       \
                break;                                                         \
            }                                                                  \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    N N##_buffer_read_until(N s, FILE* f, const char* const del) {             \
        char c;                                                                \
        size_t size = 0;                                                       \
        while (1) {                                                            \
            c = fgetc(f);                                                      \
            if (c == EOF || N##_char_find(del, c)) {                           \
                break;                                                         \
            }                                                                  \
            s[size++] = c;                                                     \
        }                                                                      \
        s[size] = '\0';                                                        \
        return (size == 0) ? NULL : s;                                         \
    }                                                                          \
                                                                               \
    N N##_buffer_read(N buff, FILE* f) {                                       \
        buff[0] = '\0';                                                        \
        return fgets(buff, S - 1, f);                                          \
    }                                                                          \
                                                                               \
    N N##_read_until(N* s, FILE* f, const char* const del) {                   \
        *s = NULL;                                                             \
        char c;                                                                \
        size_t size = 0;                                                       \
        char buff[S] = "\0";                                                   \
        while (1) {                                                            \
            c = fgetc(f);                                                      \
            if (c == EOF || N##_char_find(del, c)) {                           \
                break;                                                         \
            }                                                                  \
            buff[size++] = c;                                                  \
        }                                                                      \
        if (size) {                                                            \
            buff[size] = '\0';                                                 \
            size_t size = strlen(buff);                                        \
            *s = (N)sgc_malloc(sizeof(char) * (size + 1));                     \
            memcpy(s, buff, sizeof(char) * (size + 1));                        \
        }                                                                      \
        return *s;                                                             \
    }                                                                          \
                                                                               \
    N N##_read_file(N* s, const char* const file_name) {                       \
        *s = NULL;                                                             \
        FILE* f = fopen(file_name, "r");                                       \
        /* forgot to check to evade undefined behavior!*/                      \
        if (f) {                                                               \
            *s = N##_read_until(s, f, "");                                     \
            fclose(f);                                                         \
        }                                                                      \
        return *s;                                                             \
    }                                                                          \
                                                                               \
    N##_type* N##_array(N* s) {                                                \
        return *s;                                                             \
    }                                                                          \
                                                                               \
    char* N##_it_data(N##_it i) {                                  \
        return i;                                                              \
    }                                                                          \
                                                                               \
    const char* N##_it_cdata(const N##_it i) {                     \
        return i;                                                              \
    }                                                                          \
                                                                               \
    void N##_it_go_next(N##_it* i) {                                  \
        ++*i;                                                                  \
    }                                                                          \
                                                                               \
    void N##_it_go_prev(N##_it* i) {                                  \
        --*i;                                                                  \
    }                                                                          \
                                                                               \
    void N##_it_begin(N* s, N##_it* i) {                           \
        *i = *s;                                                               \
    }                                                                          \
                                                                               \
    void N##_it_cbegin(const N* const s, N##_it* i) {              \
        *i = *s;                                                               \
    }                                                                          \
                                                                               \
    N##_it N##_begin(N* s) {                                             \
        N##_it i;                                                        \
        N##_it_begin(s, &i);                                             \
        return i;                                                              \
    }                                                                          \
                                                                               \
    N##_it N##_cbegin(const N* const s) {                                \
        N##_it i;                                                        \
        N##_it_cbegin(s, &i);                                            \
        return i;                                                              \
    }                                                                          \
                                                                               \
    void N##_it_end(N* s, N##_it* i) {                             \
        *i = *s + strlen(*s) - 1;                                              \
    }                                                                          \
                                                                               \
    void N##_it_cend(const N* const s, N##_it* i) {                \
        *i = *s + strlen(*s) - 1;                                              \
    }                                                                          \
                                                                               \
    N##_it N##_end(N* s) {                                               \
        N##_it i;                                                        \
        N##_it_end(s, &i);                                               \
        return i;                                                              \
    }                                                                          \
                                                                               \
    N##_it N##_cend(const N* const s) {                                  \
        N##_it i;                                                        \
        N##_it_cend(s, &i);                                              \
        return i;                                                              \
    }                                                                          \
                                                                               \
    void N##_it_from(N* s, N##_it* i, size_t at) {                 \
        *i = *s + at;                                                          \
    }                                                                          \
                                                                               \
    void N##_it_cfrom(const N* const s, N##_it* i, size_t at) {    \
        *i = *s + at;                                                          \
    }                                                                          \
                                                                               \
    N##_it N##_from(N* s, size_t at) {                                   \
        N##_it i;                                                        \
        N##_it_from(s, &i, at);                                          \
        return i;                                                              \
    }                                                                          \
                                                                               \
    N##_it N##_cfrom(const N* const s, size_t at) {                      \
        N##_it i;                                                        \
        N##_it_cfrom(s, &i, at);                                         \
        return i;                                                              \
    }                                                                          \
                                                                               \
    void N##_it_jump(N##_it* i, int range) {                   \
        *i = *i + range;                                                       \
    }                                                                          \
                                                                               \
    int N##_it_equal(const N##_it first,                           \
                           const N##_it second) {                        \
        return *first == *second;                                              \
    }                                                                          \
                                                                               \
    int N##_it_diff(const N##_it first,                       \
                               const N##_it second) {                    \
        return *second - *first;                                               \
    }                                                                          \
                                                                               \
    int N##_it_valid(const N##_it i) {                             \
        (void)i;                                                               \
        return 1;                                                              \
    }
