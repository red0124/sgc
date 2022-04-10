#pragma once
#include <stdlib.h>
#include <string.h>

#define SGC_INIT_HEADERS_PRIMITIVE_TYPE(T, N, F)                               \
    F void N##_init(T* el);                                                    \
    F void N##_free(T* el);                                                    \
    F void N##_copy(T* dst, const T* const src);                               \
    F int N##_eq(const T* const first, const T* const second);                 \
    F int N##_compare(const T* const first, const T* const second);            \
    F int N##_void_compare(const void* const first, const void* const second);

#define SGC_INIT_PRIMITIVE_TYPE(T, N, F)                                       \
    SGC_INIT_HEADERS_PRIMITIVE_TYPE(T, N, F)                                   \
    F void N##_init(T* el) {                                                   \
        *el = 0;                                                               \
    }                                                                          \
                                                                               \
    F void N##_free(T* el) {                                                   \
        (void)el;                                                              \
    }                                                                          \
                                                                               \
    F void N##_copy(T* dst, const T* const src) {                              \
        *dst = *(T*)src;                                                       \
    }                                                                          \
                                                                               \
    F int N##_eq(const T* const first, const T* const second) {                \
        return *first == *second;                                              \
    }                                                                          \
                                                                               \
    F int N##_compare(const T* const first, const T* const second) {           \
        return (int)(*first - *second);                                        \
    }                                                                          \
                                                                               \
    F int N##_void_compare(const void* const first,                            \
                           const void* const second) {                         \
        return (int)(*(T*)first - *(T*)second);                                \
    }

#define SGC_INIT_HEADERS_PRIMITIVE_HASH(T, N, F)                               \
    F size_t N##_hash(const T* const el);

#define SGC_INIT_PRIMITIVE_HASH(T, N, F)                                       \
    SGC_INIT_HEADERS_PRIMITIVE_HASH(T, N, F)                                   \
    size_t N##_hash(const T* const el) {                                       \
        return (size_t)*el;                                                    \
    }

#define SGC_INIT_HEADERS_PRIMITIVE_STRUCT(T, N)                                \
    typedef T N;                                                               \
    void N##_init(T* el);                                                      \
    void N##_free(T* el);                                                      \
    void N##_copy(T* dst, const T* const src);                                 \
    int N##_eq(const T* const first, const T* const second);

#define SGC_INIT_PRIMITIVE_STRUCT(T, N)                                        \
    SGC_INIT_HEADERS_PRIMITIVE_STRUCT(T, N)                                    \
    void N##_init(T* el) {                                                     \
        memset(el, 0, sizeof(T));                                              \
    }                                                                          \
                                                                               \
    void N##_free(T* el) {                                                     \
        (void)el;                                                              \
    }                                                                          \
                                                                               \
    void N##_copy(T* dst, const T* const src) {                                \
        *dst = *src;                                                           \
    }                                                                          \
                                                                               \
    int N##_eq(const T* const first, const T* const second) {                  \
        return memcmp(first, second, sizeof(T)) == 0;                          \
    }

#ifndef SGC_NO_PRIMITIVE_TYPES
#ifndef SGC_PRIMITIVE_TYPES_HEADERS
#ifndef SGC_PRIMITIVE_TYPES_EXTERN
SGC_INIT_PRIMITIVE_TYPE(char, char, static inline)
SGC_INIT_PRIMITIVE_TYPE(unsigned char, unsigned_char, static inline)
SGC_INIT_PRIMITIVE_TYPE(short, short, static inline)
SGC_INIT_PRIMITIVE_TYPE(unsigned short, unsigned_short, static inline)
SGC_INIT_PRIMITIVE_TYPE(int, int, static inline)
SGC_INIT_PRIMITIVE_TYPE(unsigned int, unsigned_int, static inline)
SGC_INIT_PRIMITIVE_TYPE(long, long, static inline)
SGC_INIT_PRIMITIVE_TYPE(unsigned long, unsigned_long, static inline)
SGC_INIT_PRIMITIVE_TYPE(float, float, static inline)
SGC_INIT_PRIMITIVE_TYPE(double, double, static inline)
SGC_INIT_PRIMITIVE_TYPE(long double, long_double, static inline)

SGC_INIT_PRIMITIVE_HASH(char, char, static inline)
SGC_INIT_PRIMITIVE_HASH(unsigned char, unsigned_char, static inline)
SGC_INIT_PRIMITIVE_HASH(short, short, static inline)
SGC_INIT_PRIMITIVE_HASH(unsigned short, unsigned_short, static inline)
SGC_INIT_PRIMITIVE_HASH(int, int, static inline)
SGC_INIT_PRIMITIVE_HASH(unsigned int, unsigned_int, static inline)
SGC_INIT_PRIMITIVE_HASH(long, long, static inline)
SGC_INIT_PRIMITIVE_HASH(unsigned long, unsigned_long, static inline)
#else
SGC_INIT_PRIMITIVE_TYPE(char, char, extern)
SGC_INIT_PRIMITIVE_TYPE(unsigned char, unsigned_char, extern)
SGC_INIT_PRIMITIVE_TYPE(short, short, extern)
SGC_INIT_PRIMITIVE_TYPE(unsigned short, unsigned_short, extern)
SGC_INIT_PRIMITIVE_TYPE(int, int, extern)
SGC_INIT_PRIMITIVE_TYPE(unsigned int, unsigned_int, extern)
SGC_INIT_PRIMITIVE_TYPE(long, long, extern)
SGC_INIT_PRIMITIVE_TYPE(unsigned long, unsigned_long, extern)
SGC_INIT_PRIMITIVE_TYPE(float, float, extern)
SGC_INIT_PRIMITIVE_TYPE(double, double, extern)
SGC_INIT_PRIMITIVE_TYPE(long double, long_double, extern)

SGC_INIT_PRIMITIVE_HASH(char, char, static inline)
SGC_INIT_PRIMITIVE_HASH(unsigned char, unsigned_char, static inline)
SGC_INIT_PRIMITIVE_HASH(short, short, static inline)
SGC_INIT_PRIMITIVE_HASH(unsigned short, unsigned_short, static inline)
SGC_INIT_PRIMITIVE_HASH(int, int, static inline)
SGC_INIT_PRIMITIVE_HASH(unsigned int, unsigned_int, static inline)
SGC_INIT_PRIMITIVE_HASH(long, long, static inline)
SGC_INIT_PRIMITIVE_HASH(unsigned long, unsigned_long, static inline)
#endif
#else

SGC_INIT_HEADERS_PRIMITIVE_TYPE(char, char, extern)
SGC_INIT_HEADERS_PRIMITIVE_TYPE(unsigned char, unsigned_char, extern)
SGC_INIT_HEADERS_PRIMITIVE_TYPE(short, short, extern)
SGC_INIT_HEADERS_PRIMITIVE_TYPE(unsigned short, unsigned_short, extern)
SGC_INIT_HEADERS_PRIMITIVE_TYPE(int, int, extern)
SGC_INIT_HEADERS_PRIMITIVE_TYPE(unsigned int, unsigned_int, extern)
SGC_INIT_HEADERS_PRIMITIVE_TYPE(long, long, extern)
SGC_INIT_HEADERS_PRIMITIVE_TYPE(unsigned long, unsigned_long, extern)
SGC_INIT_HEADERS_PRIMITIVE_TYPE(float, float, extern)
SGC_INIT_HEADERS_PRIMITIVE_TYPE(double, double, extern)
SGC_INIT_HEADERS_PRIMITIVE_TYPE(long double, long_double, extern)

SGC_INIT_HEADERS_PRIMITIVE_HASH(char, char, extern)
SGC_INIT_HEADERS_PRIMITIVE_HASH(unsigned char, unsigned_char, extern)
SGC_INIT_HEADERS_PRIMITIVE_HASH(short, short, extern)
SGC_INIT_HEADERS_PRIMITIVE_HASH(unsigned short, unsigned_short, extern)
SGC_INIT_HEADERS_PRIMITIVE_HASH(int, int, extern)
SGC_INIT_HEADERS_PRIMITIVE_HASH(unsigned int, unsigned_int, extern)
SGC_INIT_HEADERS_PRIMITIVE_HASH(long, long, extern)
SGC_INIT_HEADERS_PRIMITIVE_HASH(unsigned long, unsigned_long, extern)
#endif
#endif
