#pragma once

#ifndef SGC_ST
#define SGC_ST
#warning "contains function definitions, define SGC_ST kill warning"
#endif

#define SGC_INIT_HEADERS_STATIC_TYPE(T, N)                                     \
                                                                               \
        void N##_init(T *el);                                                  \
        void N##_free(T *el);                                                  \
        void N##_copy(T *dst, const T *const src);                             \
        int N##_equal(const T *const first, const T *const second);            \
        int N##_compare(const T *const first, const T *const second);          \
        int N##_void_compare(const void *const first, const void *const second);

#define SGC_INIT_STATIC_TYPE(T, N)                                             \
        SGC_INIT_HEADERS_STATIC_TYPE(T, N);                                    \
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
                *dst = *(T *)src;                                              \
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

#define SGC_INIT_HEADERS_HASH(T, N) size_t N##_hash(const T *const el);

#define SGC_INIT_HASH(T, N)                                                    \
        SGC_INIT_HEADERS_HASH(T, N);                                           \
                                                                               \
        size_t N##_hash(const T *const el)                                     \
        {                                                                      \
                return (size_t)*el;                                            \
        }

#define SGC_INIT_HEADERS_STATIC_STRUCT(T, N)                                   \
        typedef T N;                                                           \
        void N##_init(T *el);                                                  \
        void N##_free(T *el);                                                  \
        void N##_copy(T *dst, const T *const src);                             \
        int N##_equal(const T *const first, const T *const second);

#define SGC_INIT_STATIC_STRUCT(T, N)                                           \
        SGC_INIT_HEADERS_STATIC_STRUCT(T, N);                                  \
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
        }

SGC_INIT_STATIC_TYPE(char, char);
SGC_INIT_STATIC_TYPE(unsigned char, unsigned_char);
SGC_INIT_STATIC_TYPE(short, short);
SGC_INIT_STATIC_TYPE(unsigned short, unsigned_short);
SGC_INIT_STATIC_TYPE(int, int);
SGC_INIT_STATIC_TYPE(unsigned int, unsigned_int);
SGC_INIT_STATIC_TYPE(long, long);
SGC_INIT_STATIC_TYPE(unsigned long, unsigned_long);
SGC_INIT_STATIC_TYPE(float, float);
SGC_INIT_STATIC_TYPE(double, double);
SGC_INIT_STATIC_TYPE(long double, long_double);

SGC_INIT_HASH(char, char);
SGC_INIT_HASH(unsigned char, unsigned_char);
SGC_INIT_HASH(short, short);
SGC_INIT_HASH(unsigned short, unsigned_short);
SGC_INIT_HASH(int, int);
SGC_INIT_HASH(unsigned int, unsigned_int);
SGC_INIT_HASH(long, long);
SGC_INIT_HASH(unsigned long, unsigned_long);
