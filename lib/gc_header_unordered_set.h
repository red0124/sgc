#pragma once

#define SGC_INIT_HEADER_UNORDERED_SET(V, N)                                        \
        struct N##_node                                                        \
        {                                                                      \
                V _value;                                                      \
                struct N##_node *_next;                                        \
        };                                                                     \
                                                                               \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                size_t _max;                                                   \
                struct N##_node **_data;                                       \
        };                                                                     \
                                                                               \
        typedef struct N N;                                                    \
	typedef V N##_type;                                                    \
        typedef V N##_value;                                                   \
        typedef V N##_key;                                                     \
                                                                               \
        /* =================== */                                              \
        /*  ELEMENT FUNCTIONS  */                                              \
        /* =================== */                                              \
									       \
        void N##_set_copy(void (*copy)(V *, const V *const));                  \
                                                                               \
        void N##_set_share(int is_shared);                                     \
                                                                               \
        void N##_set_equal(int (*equal)(const V *const, const V *const));      \
                                                                               \
        void N##_set_compare(int (*compare)(const V *const, const V *const));  \
                                                                               \
        void N##_set_free(void (*free)(V *));                                  \
                                                                               \
        void N##_insert(struct N *, V);                                        \
                                                                               \
        void N##_set_default_insert(void (*insert)(N *, V));                   \
                                                                               \
        void N##_default_insert(struct N *d, V el);                            \
                                                                               \
	void N##_set_hash(size_t (*hash)(const K *const));                     \
                                                                               \
        /* ================== */                                               \
        /*  BUCKET FUNCTIONS  */                                               \
        /* ================== */                                               \
                                                                               \
        struct N##_node *N##_node_new(const V *const value);                   \
                                                                               \
        size_t N##_bucket_count(const struct N *const u);                      \
                                                                               \
        size_t N##_bucket_size(const struct N *const u, size_t n);             \
                                                                               \
        size_t N##_buckets_used(const struct N *const u);                      \
                                                                               \
        /* ========== */                                                       \
        /*  ITERATOR  */                                                       \
        /* ========== */                                                       \
                                                                               \
        struct N##_iterator                                                    \
        {                                                                      \
                struct N##_node **_data;                                       \
                struct N##_node *_curr;                                        \
                size_t _curr_bucket;                                           \
                size_t _max;                                                   \
                int _is_valid;                                                 \
        };                                                                     \
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
        void N##_rehash(struct N *u, size_t new_max);                          \
                                                                               \
        void N##_defaulti_nsert(struct N *u, const V v);                       \
                                                                               \
        void N##_insert(struct N *u, const V v);                               \
                                                                               \
        void N##_insert_multiple(struct N *u, const V v);                      \
                                                                               \
        void N##_erase(struct N *u, const V v);                                \
                                                                               \
        void N##_iterator_erase(struct N *u, struct N##_iterator *i);
\
