#pragma once

#define INIT_HEADER_STATIC_PRIORITY_QUEUE(T, S, N)                             \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                T _data[S];                                                    \
        };                                                                     \
        typedef struct N N;                                                    \
                                                                               \
        size_t N##_max();                                                      \
                                                                               \
        int N##_is_static();                                                   \
                                                                               \
        /* =================== */                                              \
        /*  ELEMENT FUNCTIONS  */                                              \
        /* =================== */                                              \
                                                                               \
        void N##_set_copy(void (*copy)(T *, const T *const));                  \
                                                                               \
        void N##_set_share(int is_shared);                                     \
                                                                               \
        void N##_set_compare(int (*compare)(const T *const, const T *const));  \
                                                                               \
        /* ==========================*/                                        \
        /*  PRIOITY QUEUE FUNCTIONS  */                                        \
        /* ==========================*/                                        \
                                                                               \
        void N##_init(struct N *p);                                            \
                                                                               \
        size_t N##_size(const struct N *p);                                    \
                                                                               \
        void N##_free(struct N *p);                                            \
                                                                               \
        int N##_equal(const struct N *const first,                             \
                      const struct N *const second);                           \
                                                                               \
        void N##_copy(struct N *__restrict__ dst,                              \
                      const struct N *__restrict__ const src);                 \
                                                                               \
        void N##_push(struct N *p, T el);                                      \
                                                                               \
        void N##_pop(struct N *p);                                             \
                                                                               \
        T *N##_top(struct N *p);                                               \
                                                                               \
        int N##_empty(const struct N *const d);                                \
                                                                               \
        T *N##_array(struct N *d);
\
