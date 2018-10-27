#pragma once

#define INIT_HEADER_STATIC_QUEUE(T, S, N)                                      \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                size_t _back;                                                  \
                size_t _front;                                                 \
                T _data[S];                                                    \
        };                                                                     \
                                                                               \
        typedef struct N N;                                                    \
                                                                               \
        int N##_is_static();                                                   \
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
        /* ================= */                                                \
        /*  QUEUE FUNCTIONS  */                                                \
        /* ================= */                                                \
                                                                               \
        size_t N##_size(const struct N *const q);                              \
                                                                               \
        void N##_init(struct N *q);                                            \
                                                                               \
        void N##_free(struct N *q);                                            \
                                                                               \
        int N##_equal(const struct N *const first,                             \
                      const struct N *const second);                           \
                                                                               \
        void N##_copy(struct N *restrict dst,                                  \
                      const struct N *__restrict__ const src);                 \
                                                                               \
        void N##_push(struct N *q, T el);                                      \
                                                                               \
        T *N##_front(struct N *q);                                             \
                                                                               \
        void N##_set_front(struct N *q, T new_el);                             \
                                                                               \
        T *N##_back(struct N *q);                                              \
                                                                               \
        void N##_set_back(struct N *q, T new_el);                              \
                                                                               \
        void N##_pop(struct N *q);
\
