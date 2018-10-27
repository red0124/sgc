#pragma once

#define INIT_HEADER_STATIC_UNORDERED_SET(V, S, N)                              \
        struct N##_node                                                        \
        {                                                                      \
                V _value;                                                      \
                char _state;                                                   \
        };                                                                     \
                                                                               \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                struct N##_node _data[S];                                      \
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
        void N##_set_init(void (*init)(V *));                                  \
                                                                               \
        void N##_set_share(int is_shared);                                     \
                                                                               \
        /* ========== */                                                       \
        /*  ITERATOR  */                                                       \
        /* ========== */                                                       \
                                                                               \
        struct N##_iterator                                                    \
        {                                                                      \
                size_t _curr;                                                  \
                struct N##_node *_data;                                        \
                int _is_valid;                                                 \
        };                                                                     \
                                                                               \
        const V *N##_iterator_cvalue(struct N##_iterator i);                   \
                                                                               \
        V *N##_iterator_value(struct N##_iterator i);                          \
                                                                               \
        void N##_iterator_next(struct N##_iterator *i);                        \
                                                                               \
        void N##_iterator_begin(struct N *m, struct N##_iterator *i);          \
                                                                               \
        void N##_iterator_cbegin(const struct N *const m,                      \
                                 struct N##_iterator *i);                      \
                                                                               \
        void N##_iterator_prev(struct N##_iterator *i);                        \
                                                                               \
        void N##_iterator_end(struct N *m, struct N##_iterator *i);            \
                                                                               \
        void N##_iterator_cend(const struct N *const m,                        \
                               struct N##_iterator *i);                        \
                                                                               \
        struct N##_iterator N##_begin(struct N *m);                            \
                                                                               \
        struct N##_iterator N##_cbegin(const struct N *const m);               \
                                                                               \
        struct N##_iterator N##_end(struct N *m);                              \
                                                                               \
        struct N##_iterator N##_cend(const struct N *const m);                 \
                                                                               \
        int N##_iterator_equal(const struct N##_iterator first,                \
                               const struct N##_iterator second);              \
                                                                               \
        int N##_iterator_valid(const struct N##_iterator i);                   \
                                                                               \
        /* =============== */                                                  \
        /*  SET FUNCTIONS  */                                                  \
        /* =============== */                                                  \
                                                                               \
        size_t N##_size(const struct N *const u);                              \
                                                                               \
        void N##_init(struct N *u);                                            \
                                                                               \
        int N##_equal(const N *const first, const N *const second);            \
                                                                               \
        void N##_copy(N *__restrict__ dst, const N *__restrict__ const src);   \
                                                                               \
        void N##_free(struct N *u);                                            \
                                                                               \
        struct N##_iterator N##_find(struct N *u, const V v);                  \
                                                                               \
        void N##_insert(struct N *u, const V v);                               \
                                                                               \
        void N##_insert_multiple(struct N *u, const V v);                      \
                                                                               \
        void N##_iterator_erase(struct N *u, struct N##_iterator *i);          \
                                                                               \
        void N##_erase(struct N *u, const V v);
\
