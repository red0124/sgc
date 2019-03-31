#pragma once

#define SGC_INIT_HEADER_STATIC(T, N)                                               \
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
        int N##_void_compare(const void *const first, const void *const second);

SSGC_INIT_HEADER_STATIC(char, char);
SSGC_INIT_HEADER_STATIC(unsigned char, unsigned_char);
SSGC_INIT_HEADER_STATIC(short, short);
SSGC_INIT_HEADER_STATIC(unsigned short, unsigned_short);
SSGC_INIT_HEADER_STATIC(int, int);
SSGC_INIT_HEADER_STATIC(unsigned int, unsigned_int);
SSGC_INIT_HEADER_STATIC(long, long);
SSGC_INIT_HEADER_STATIC(unsigned long, unsigned_long);
SSGC_INIT_HEADER_STATIC(float, float);
SSGC_INIT_HEADER_STATIC(double, double);
SSGC_INIT_HEADER_STATIC(long double, long_double);

#define SGC_INIT_HEADER_HASH(T, N) size_t N##_hash(const T *const el);

SSGC_INIT_HEADER_HASH(char, char);
SSGC_INIT_HEADER_HASH(unsigned char, unsigned_char);
SSGC_INIT_HEADER_HASH(short, short);
SSGC_INIT_HEADER_HASH(unsigned short, unsigned_short);
SSGC_INIT_HEADER_HASH(int, int);
SSGC_INIT_HEADER_HASH(unsigned int, unsigned_int);
SSGC_INIT_HEADER_HASH(long, long);
SSGC_INIT_HEADER_HASH(unsigned long, unsigned_long);

#define SGC_INIT_HEADER_STATIC_STRUCT(T, N)                                        \
                                                                               \
        void N##_init(T *el);                                                  \
                                                                               \
        void N##_free(T *el);                                                  \
                                                                               \
        void N##_copy(T *dst, const T *const src);                             \
                                                                               \
        int N##_equal(const T *const first, const T *const second);
\
