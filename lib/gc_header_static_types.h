#pragma once

#define INIT_HEADER_STATIC(T, N)                                               \
        void N##_init(T *el);                                                  \
                                                                               \
        void N##_free(T *el);                                                  \
                                                                               \
        void N##_copy(T *dst, const T *const src);                             \
                                                                               \
        int N##_equal(const T *const first, const T *const second);            \
                                                                               \
        int N##_compare(const T *const first, const T *const second);          \
                                                                               \
        int N##_void_compare(const void *const first,                          \
                             const void *const second);                        \
                                                                               \
        int N##_is_static();                                                   \

INIT_HEADER_STATIC(char, char);
INIT_HEADER_STATIC(unsigned char, unsigned_char);
INIT_HEADER_STATIC(short, short);
INIT_HEADER_STATIC(unsigned short, unsigned_short);
INIT_HEADER_STATIC(int, int);
INIT_HEADER_STATIC(unsigned int, unsigned_int);
INIT_HEADER_STATIC(long, long);
INIT_HEADER_STATIC(unsigned long, unsigned_long);
INIT_HEADER_STATIC(float, float);
INIT_HEADER_STATIC(double, double);
INIT_HEADER_STATIC(long double, long_double);

#define INIT_HEADER_HASH(T, N) size_t N##_hash(const T *const el);

INIT_HEADER_HASH(char, char);
INIT_HEADER_HASH(unsigned char, unsigned_char);
INIT_HEADER_HASH(short, short);
INIT_HEADER_HASH(unsigned short, unsigned_short);
INIT_HEADER_HASH(int, int);
INIT_HEADER_HASH(unsigned int, unsigned_int);
INIT_HEADER_HASH(long, long);
INIT_HEADER_HASH(unsigned long, unsigned_long);

#define INIT_HEADER_STATIC_STRUCT(T, N)                                        \
                                                                               \
        void N##_init(T *el);                                                  \
                                                                               \
        void N##_free(T *el);                                                  \
                                                                               \
        void N##_copy(T *dst, const T *const src);                             \
                                                                               \
        int N##_equal(const T *const first, const T *const second);            \
                                                                               \
        int N##_is_static();\
\
