#pragma once

#define SGC_INIT_HEADER_STATIC_QUEUE(T, S, N)                                      \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                size_t _back;                                                  \
                size_t _front;                                                 \
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
        void N##_default_insert(struct N *q, T el);                            \
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
