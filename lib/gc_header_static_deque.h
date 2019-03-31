#pragma once

#define SGC_INIT_HEADER_STATIC_DEQUE(T, S, N)                                      \
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
        /* ================= */                                                \
        /*  DEQUE FUNCTIONS  */                                                \
        /* ================= */                                                \
                                                                               \
        size_t N##_size(const struct N *const d);                              \
                                                                               \
        void N##_init(struct N *d);                                            \
                                                                               \
        void N##_free(struct N *d);                                            \
                                                                               \
        int N##_equal(const struct N *const first,                             \
                      const struct N *const second);                           \
                                                                               \
        void N##_copy(struct N *restrict dst,                                  \
                      const struct N *__restrict__ const src);                 \
                                                                               \
        void N##_default_insert(struct N *d, T el);                            \
                                                                               \
        void N##_push_back(struct N *d, T el);                                 \
                                                                               \
        void N##_push_front(struct N *d, T el);                                \
                                                                               \
        T *N##_front(struct N *d);                                             \
                                                                               \
        void N##_set_front(struct N *d, T new_el);                             \
                                                                               \
        T *N##_back(struct N *d);                                              \
                                                                               \
        void N##_set_back(struct N *d, T new_el);                              \
                                                                               \
        void N##_pop_front(struct N *d);                                       \
                                                                               \
        void N##_pop_back(struct N *d);                                        \
                                                                               \
        void N##_insert(struct N *d, const size_t at, T el);                   \
                                                                               \
        void N##_erase_at(struct N *d, const size_t at);                       \
                                                                               \
        T *N##_at(struct N *d, size_t at);                                     \
                                                                               \
        void N##_set_at(struct N *d, size_t at, T new_el);                     \
                                                                               \
        int N##_empty(const struct N *const d);                                \
                                                                               \
        T *N##_array(struct N *d);                                             \
                                                                               \
        /* ================ */                                                 \
        /*  DEQUE ITERATOR  */                                                 \
        /* ================ */                                                 \
                                                                               \
        struct N##_iterator                                                    \
        {                                                                      \
                size_t _curr;                                                  \
                T *_data;                                                      \
                int _is_valid;                                                 \
        };                                                                     \
                                                                               \
        T *N##_iterator_value(struct N##_iterator i);                          \
                                                                               \
        const T *N##_iterator_cvalue(const struct N##_iterator i);             \
                                                                               \
        void N##_iterator_next(struct N##_iterator *i);                        \
                                                                               \
        void N##_iterator_prev(struct N##_iterator *i);                        \
                                                                               \
        void N##_iterator_begin(struct N *d, struct N##_iterator *i);          \
                                                                               \
        void N##_iterator_cbegin(const struct N *const d,                      \
                                 struct N##_iterator *i);                      \
                                                                               \
        struct N##_iterator N##_begin(struct N *d);                            \
                                                                               \
        struct N##_iterator N##_cbegin(const struct N *const d);               \
                                                                               \
        void N##_iterator_end(struct N *d, struct N##_iterator *i);            \
                                                                               \
        void N##_iterator_cend(const struct N *const d,                        \
                               struct N##_iterator *i);                        \
                                                                               \
        struct N##_iterator N##_end(struct N *d);                              \
                                                                               \
        struct N##_iterator N##_cend(const struct N *const d);                 \
                                                                               \
        void N##_iterator_from(struct N *d, struct N##_iterator *i,            \
                               size_t at);                                     \
                                                                               \
        void N##_iterator_cfrom(const struct N *const d,                       \
                                struct N##_iterator *i, size_t at);            \
                                                                               \
        struct N##_iterator N##_from(struct N *d, size_t at);                  \
                                                                               \
        struct N##_iterator N##_cfrom(const struct N *const d, size_t at);     \
                                                                               \
        void N##_iterator_jump(struct N##_iterator *i, ssize_t range);         \
                                                                               \
        int N##_iterator_equal(const struct N##_iterator first,                \
                               const struct N##_iterator second);              \
                                                                               \
        ssize_t N##_iterator_range(const struct N##_iterator first,            \
                                   const struct N##_iterator second);
\
