#pragma once

#define INIT_HEADER_STACK(T, N)                                                \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                size_t _max;                                                   \
                T *_data;                                                      \
        };                                                                     \
                                                                               \
        void N##_set_growth_scale(double growth_scale);                        \
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
        /* ================= */                                                \
        /*  STACK FUNCTIONS  */                                                \
        /* ================= */                                                \
                                                                               \
        size_t N##_size(const struct N *const s);                              \
                                                                               \
        void N##_init(struct N *const s);                                      \
                                                                               \
        void N##_free(struct N *s);                                            \
                                                                               \
        int N##_equal(const struct N *const first,                             \
                      const struct N *const second);                           \
                                                                               \
        void N##_copy(struct N *__restrict__ dst,                              \
                      const struct N *__restrict__ const src);                 \
                                                                               \
        void N##_push(struct N *s, T el);                                      \
                                                                               \
        void N##_pop(struct N *s);                                             \
                                                                               \
        T *N##_top(struct N *s);                                               \
                                                                               \
        void N##_set_top(struct N *s, T new_el);
\
