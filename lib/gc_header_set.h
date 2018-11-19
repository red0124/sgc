#pragma once

#ifndef GC_MAP_COLOR
#define GC_MAP_COLOR
enum map_color
{
        MAP_RED,
        MAP_BLACK,
};
#endif

#define INIT_HEADER_SET(V, N)                                                  \
        struct N##_node                                                        \
        {                                                                      \
                struct N##_node *_parent;                                      \
                struct N##_node *_left;                                        \
                struct N##_node *_right;                                       \
                V _value;                                                      \
                enum map_color _color;                                         \
        };                                                                     \
                                                                               \
        typedef struct N N;                                                    \
	typedef V N##_type;                                                    \
        typedef V N##_value;                                                   \
        typedef V N##_key;                                                     \
                                                                               \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                struct N##_node *_root;                                        \
        };                                                                     \
                                                                               \
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
        /* ================ */                                                 \
        /*  NODE FUNCTIONS  */                                                 \
        /* ================ */                                                 \
                                                                               \
        /* ========== */                                                       \
        /*  ITERATOR  */                                                       \
        /* ========== */                                                       \
                                                                               \
        struct N##_iterator                                                    \
        {                                                                      \
                struct N##_node *_curr;                                        \
                struct N##_node *_next;                                        \
                int _is_valid;                                                 \
        };                                                                     \
                                                                               \
        V *N##_iterator_value(struct N##_iterator i);                          \
                                                                               \
        const V *N##_iterator_cvalue(struct N##_iterator i);                   \
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
        /*  MAP FUNCTIONS  */                                                  \
        /* =============== */                                                  \
                                                                               \
        size_t N##_size(const struct N *const m);                              \
                                                                               \
        void N##_init(struct N *m);                                            \
                                                                               \
        void N##_free(struct N *m);                                            \
                                                                               \
        int N##_equal(const struct N *const first,                             \
                      const struct N *const second);                           \
                                                                               \
        void N##_copy(struct N *__restrict__ dst,                              \
                      const struct N *__restrict__ const src);                 \
                                                                               \
        void N##_default_insert(struct N *m, V v);                             \
                                                                               \
        void N##_insert(struct N *m, V v);                                     \
                                                                               \
        void N##_insert_multiple(struct N *m, V v);                            \
                                                                               \
        struct N##_iterator N##_find(struct N *m, V v);                        \
                                                                               \
        int N##_erase(struct N *m, const V value);                             \
                                                                               \
        int N##_iterator_erase(struct N *m, struct N##_iterator *i);
\
