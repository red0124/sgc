#pragma once

#ifndef SGC_ST
#define SGC_ST
#warning                                                                       \
    "header contains function definitions whitch may cause multiple definition errors, define SGC_STATIC_TYPES to kill warning"
#endif

#define SGC_INIT_STATIC(T, N)                                                      \
                                                                               \
        void N##_init(T *el)                                                   \
        {                                                                      \
                *el = 0;                                                       \
        }                                                                      \
                                                                               \
        void N##_free(T *el)                                                   \
        {                                                                      \
                (void)el;                                                      \
        }                                                                      \
                                                                               \
        void N##_copy(T *dst, const T *const src)                              \
        {                                                                      \
                *dst = *src;                                                   \
        }                                                                      \
                                                                               \
        int N##_equal(const T *const first, const T *const second)             \
        {                                                                      \
                return *first == *second;                                      \
        }                                                                      \
                                                                               \
        int N##_compare(const T *const first, const T *const second)           \
        {                                                                      \
                return (int)(*first - *second);                                \
        }                                                                      \
                                                                               \
        int N##_void_compare(const void *const first,                          \
                             const void *const second)                         \
        {                                                                      \
                return (int)(*(T *)first - *(T *)second);                      \
        }

SSGC_INIT_STATIC(char, char);
SSGC_INIT_STATIC(unsigned char, unsigned_char);
SSGC_INIT_STATIC(short, short);
SSGC_INIT_STATIC(unsigned short, unsigned_short);
SSGC_INIT_STATIC(int, int);
SSGC_INIT_STATIC(unsigned int, unsigned_int);
SSGC_INIT_STATIC(long, long);
SSGC_INIT_STATIC(unsigned long, unsigned_long);
SSGC_INIT_STATIC(float, float);
SSGC_INIT_STATIC(double, double);
SSGC_INIT_STATIC(long double, long_double);

#define SGC_INIT_HASH(T, N)                                                        \
                                                                               \
        size_t N##_hash(const T *const el)                                     \
        {                                                                      \
                return (size_t)*el;                                            \
        }

SSGC_INIT_HASH(char, char);
SSGC_INIT_HASH(unsigned char, unsigned_char);
SSGC_INIT_HASH(short, short);
SSGC_INIT_HASH(unsigned short, unsigned_short);
SSGC_INIT_HASH(int, int);
SSGC_INIT_HASH(unsigned int, unsigned_int);
SSGC_INIT_HASH(long, long);
SSGC_INIT_HASH(unsigned long, unsigned_long);

#define SGC_INIT_STATIC_STRUCT(T, N)                                               \
                                                                               \
        void N##_init(T *el)                                                   \
        {                                                                      \
                memset(el, 0, sizeof(T));                                      \
        }                                                                      \
                                                                               \
        void N##_free(T *el)                                                   \
        {                                                                      \
                (void)el;                                                      \
        }                                                                      \
                                                                               \
        void N##_copy(T *dst, const T *const src)                              \
        {                                                                      \
                *dst = *src;                                                   \
        }                                                                      \
                                                                               \
        int N##_equal(const T *const first, const T *const second)             \
        {                                                                      \
                return memcmp(first, second, sizeof(T)) == 0;                  \
        }\

