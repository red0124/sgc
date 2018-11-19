#pragma once

#ifndef GC_ST
#define GC_ST
#warning                                                                       \
    "header contains function definitions whitch may cause multiple definition errors, define GC_STATIC_TYPES to kill warning"
#endif

#define INIT_STATIC(T, N)                                                      \
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

INIT_STATIC(char, char);
INIT_STATIC(unsigned char, unsigned_char);
INIT_STATIC(short, short);
INIT_STATIC(unsigned short, unsigned_short);
INIT_STATIC(int, int);
INIT_STATIC(unsigned int, unsigned_int);
INIT_STATIC(long, long);
INIT_STATIC(unsigned long, unsigned_long);
INIT_STATIC(float, float);
INIT_STATIC(double, double);
INIT_STATIC(long double, long_double);

#define INIT_HASH(T, N)                                                        \
                                                                               \
        size_t N##_hash(const T *const el)                                     \
        {                                                                      \
                return (size_t)*el;                                            \
        }

INIT_HASH(char, char);
INIT_HASH(unsigned char, unsigned_char);
INIT_HASH(short, short);
INIT_HASH(unsigned short, unsigned_short);
INIT_HASH(int, int);
INIT_HASH(unsigned int, unsigned_int);
INIT_HASH(long, long);
INIT_HASH(unsigned long, unsigned_long);

#define INIT_STATIC_STRUCT(T, N)                                               \
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
