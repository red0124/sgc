#pragma once

#define INIT_HEADER_STRING(N)                                                  \
        typedef char *N;                                                       \
                                                                               \
        int N##_is_static();                                                   \
                                                                               \
        void N##_copy(N *first, const N *const second);                        \
                                                                               \
        void N##_init(N *s);                                                   \
                                                                               \
        void N##_free(N *s);                                                   \
                                                                               \
        int N##_equal(const N *const first, const N *const second);            \
                                                                               \
        int N##_compare(const N *const first, const N *const second);          \
                                                                               \
        int N##_void_compare(const void *const first,                          \
                             const void *const second);                        \
                                                                               \
        size_t N##_hash(const string *const s);                                \
                                                                               \
        int N##_read_buffer(N *s, FILE *f, char *buff, size_t buff_size);      \
                                                                               \
        int N##_read_untill(N *s, FILE *f, char *del);                         \
                                                                               \
        int N##_read(N *s, FILE *f);                                           \
                                                                               \
        int N##_read_file(N *s, const char *const file_name);                  \
                                                                               \
        struct N##_array                                                       \
        {                                                                      \
                N *data;                                                       \
                size_t size;                                                   \
                size_t max;                                                    \
        };                                                                     \
	                                                                       \
        typedef struct N##_array N##_array;                                    \
                                                                               \
        static void N##_array_push_back(N##_array *a, N el);                   \
                                                                               \
        N##_array N##_split(N s, const char *const del);
\
