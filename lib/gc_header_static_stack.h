#pragma once

#define INIT_HEADER_STATIC_STACK(T, S, N)                                      \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                T _data[S];                                                    \
        };                                                                     \
                                                                               \
        typedef struct N N;                                                    \
        typedef T N##_type;                                                    \
        typedef T N##_value;                                                   \
        typedef T N##_key;                                                     \
                                                                               \
        size_t N##_max();                                                      \
                                                                               \
        /* =================== */                                              \
        /*  ELEMENT FUNCTIONS  */                                              \
        /* =================== */                                              \
									       \
        void N##_set_copy(void (*copy)(T *, const T *const));                  \
                                                                               \
        void N##_set_share(int is_shared);                                     \
                                                                               \
        void N##_set_equal(int (*equal)(const T *const, const T *const));      \
                                                                               \
        void N##_set_free(int (*free)(T *));                                   \
                                                                               \
        void N##_set_default_insert(void (*insert)(N *, T));                   \
                                                                               \
        /* ======================== */                                         \
        /*  STATIC STACK FUNCTIONS  */                                         \
        /* ======================== */                                         \
                                                                               \
        void N##_init(struct N *s);                                            \
                                                                               \
        size_t N##_size(const struct N *s);                                    \
                                                                               \
        void N##_free(struct N *s);                                            \
                                                                               \
        int N##_equal(const struct N *first, const struct N *second);          \
                                                                               \
        void N##_copy(struct N *__restrict__ dst,                              \
                      const struct N *__restrict__ const src);                 \
                                                                               \
        void N##_default_insert(struct N *s, T el);                            \
                                                                               \
        void N##_push(struct N *s, T el);                                      \
                                                                               \
        void N##_pop(struct N *s);                                             \
                                                                               \
        T *N##_top(struct N *s);                                               \
                                                                               \
        void N##_set_top(struct N *s, T new_el);
\
