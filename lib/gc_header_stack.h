#pragma once

#define SGC_INIT_HEADER_STACK(T, N)                                                \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                size_t _max;                                                   \
                T *_data;                                                      \
        };                                                                     \
                                                                               \
        typedef struct N N;                                                    \
        typedef T N##_type;                                                    \
        typedef T N##_value;                                                   \
        typedef T N##_key;                                                     \
                                                                               \
        void N##_set_growth_scale(double growth_scale);                        \
	void N##_set_init_size(size_t init_size);                              \
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
