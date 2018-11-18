#pragma once

#define INIT_HEADER_FORWARD_LIST(T, N)                                         \
        struct N##_node                                                        \
        {                                                                      \
                T _data;                                                       \
                struct N##_node *_next;                                        \
        };                                                                     \
                                                                               \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                struct N##_node *_head;                                        \
                struct N##_node *_tail;                                        \
        };                                                                     \
                                                                               \
        typedef struct N N;                                                    \
	typedef T N##_type;                                                    \
        typedef T N##_value;                                                   \
        typedef T N##_key;                                                     \
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
        /* ================ */                                                 \
        /*  LIST FUNCTIONS  */                                                 \
        /* ================ */                                                 \
                                                                               \
        size_t N##_size(const struct N *const l);                              \
                                                                               \
        void N##_init(struct N *l);                                            \
                                                                               \
        void N##_free(struct N *l);                                            \
                                                                               \
        int N##_equal(const struct N *const first,                             \
                      const struct N *const second);                           \
                                                                               \
        void N##_copy(struct N *__restrict__ dst,                              \
                      const struct N *__restrict__ const src);                 \
                                                                               \
        void N##_push_back(struct N *l, T el);                                 \
                                                                               \
        T *N##_back(struct N *l);                                              \
                                                                               \
        void N##_set_back(struct N *l, T new_el);                              \
                                                                               \
        void N##_pop_back(struct N *l);                                        \
                                                                               \
        void N##_push_front(struct N *l, const T el);                          \
                                                                               \
        T *N##_front(struct N *l);                                             \
                                                                               \
        T *N##_set_front(struct N *l, T new_el);                               \
                                                                               \
        void N##_pop_front(struct N *l);                                       \
                                                                               \
        T *N##_at(struct N *l, const size_t at);                               \
                                                                               \
        void N##_set_at(struct N *l, const size_t at, T new_el);               \
                                                                               \
        int N##_erase(struct N *l, const T el);                                \
                                                                               \
        int N##_erase_at(struct N *l, size_t at);                              \
                                                                               \
        int N##_empty(const struct N *l);                                      \
                                                                               \
        void N##_insert(struct N *l, const size_t at, const T el);             \
                                                                               \
        int N##_insert_sorted(struct N *l, const T el,                         \
                              int (*compare)(const T *const, const T *const)); \
                                                                               \
        void N##_sort(struct N *l, int (*comp)(const void *, const void *));   \
                                                                               \
        /* =============== */                                                  \
        /*  LIST ITERATOR  */                                                  \
        /* =============== */                                                  \
                                                                               \
        struct N##_iterator                                                    \
        {                                                                      \
                struct N##_node *_curr;                                        \
                struct N##_node *_head;                                        \
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
        void N##_iterator_begin(struct N *l, struct N##_iterator *i);          \
                                                                               \
        void N##_iterator_cbegin(const struct N *const l,                      \
                                 struct N##_iterator *i);                      \
                                                                               \
        struct N##_iterator N##_begin(struct N *l);                            \
                                                                               \
        struct N##_iterator N##_cbegin(const struct N *const l);               \
                                                                               \
        void N##_iterator_end(struct N *l, struct N##_iterator *i);            \
                                                                               \
        void N##_iterator_cend(const struct N *const l,                        \
                               struct N##_iterator *i);                        \
                                                                               \
        struct N##_iterator N##_end(struct N *l);                              \
                                                                               \
        struct N##_iterator N##_cend(const struct N *const l);                 \
                                                                               \
        int N##_iterator_equal(const struct N##_iterator first,                \
                               const struct N##_iterator second);
\
