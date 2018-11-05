#pragma once

#define INIT_HEADER_VECTOR(T, N)                                               \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                size_t _max;                                                   \
                T *_data;                                                      \
        };                                                                     \
                                                                               \
        typedef struct N N;                                                    \
                                                                               \
        void N##_set_init_size(size_t init_size);                              \
                                                                               \
        void N##_set_growth_scale(double growth_scale);                        \
                                                                               \
        /* =================== */                                              \
        /*  ELEMENT FUNCTIONS  */                                              \
        /* =================== */                                              \
                                                                               \
        void N##_set_copy(void (*copy)(T *, const T *const));                  \
                                                                               \
        void N##_set_share(int is_shared);                                     \
                                                                               \
        /* ================== */                                               \
        /*  VECTOR FUNCTIONS  */                                               \
        /* ================== */                                               \
                                                                               \
        void N##_init(struct N *v);                                            \
                                                                               \
        size_t N##_size(const struct N *v);                                    \
                                                                               \
        void N##_free(struct N *v);                                            \
                                                                               \
        int N##_equal(const struct N *const first,                             \
                      const struct N *const second);                           \
                                                                               \
        void N##_copy(struct N *__restrict__ dst,                              \
                      const struct N *__restrict__ const src);                 \
                                                                               \
        void N##_from_array(struct N *v, const T *const arr,                   \
                            const size_t size);                                \
                                                                               \
        void N##_shrink(struct N *v);                                          \
                                                                               \
        void N##_push_back(struct N *v, T el);                                 \
                                                                               \
        void N##_pop_back(struct N *v);                                        \
                                                                               \
        void N##_insert(struct N *v, const size_t at, T el);                   \
                                                                               \
        void N##_push_front(struct N *v, T el);                                \
                                                                               \
        T *N##_at(struct N *v, size_t at);                                     \
                                                                               \
        void N##_set_at(struct N *v, size_t at, T new_el);                     \
                                                                               \
        T *N##_back(struct N *v);                                              \
                                                                               \
        void N##_set_back(struct N *v, T new_el);                              \
                                                                               \
        T *N##_front(struct N *v);                                             \
                                                                               \
        void N##_set_front(struct N *v, T new_el);                             \
                                                                               \
        void N##_erase_at(struct N *v, const size_t at);                       \
                                                                               \
        int N##_empty(const struct N *const d);                                \
                                                                               \
        T *N##_array(struct N *d);                                             \
                                                                               \
        /* ================= */                                                \
        /*  VECTOR ITERATOR  */                                                \
        /* ================= */                                                \
                                                                               \
        struct N##_iterator                                                    \
        {                                                                      \
                T *_curr;                                                      \
                T *_end;                                                       \
                T *_begin;                                                     \
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
        void N##_iterator_begin(struct N *v, struct N##_iterator *i);          \
                                                                               \
        void N##_iterator_cbegin(const struct N *const v,                      \
                                 struct N##_iterator *i);                      \
                                                                               \
        struct N##_iterator N##_begin(struct N *v);                            \
                                                                               \
        struct N##_iterator N##_cbegin(const struct N *const v);               \
                                                                               \
        void N##_iterator_end(struct N *v, struct N##_iterator *i);            \
                                                                               \
        void N##_iterator_cend(const struct N *const v,                        \
                               struct N##_iterator *i);                        \
                                                                               \
        struct N##_iterator N##_end(struct N *v);                              \
                                                                               \
        struct N##_iterator N##_cend(const struct N *const v);                 \
                                                                               \
        void N##_iterator_from(struct N *v, struct N##_iterator *i,            \
                               size_t at);                                     \
                                                                               \
        void N##_iterator_cfrom(const struct N *const v,                       \
                                struct N##_iterator *i, size_t at);            \
                                                                               \
        struct N##_iterator N##_from(struct N *v, size_t at);                  \
                                                                               \
        struct N##_iterator N##_cfrom(const struct N *const v, size_t at);     \
                                                                               \
        void N##_iterator_jump(struct N##_iterator *i, ssize_t range);         \
                                                                               \
        int N##_iterator_equal(const struct N##_iterator first,                \
                               const struct N##_iterator second);              \
                                                                               \
        ssize_t N##_iterator_range(const struct N##_iterator first,            \
                                   const struct N##_iterator second);
\
