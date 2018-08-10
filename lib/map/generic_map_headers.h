#pragma once
#include "generic_types.h"
#include <stdlib.h>

#define INIT_MAP_HEADERS(K, V)                                                 \
                                                                               \
        struct node_##K##_##V                                                  \
        {                                                                      \
                struct node_##K##_##V *_parent;                                \
                struct node_##K##_##V *_left;                                  \
                struct node_##K##_##V *_right;                                 \
                K _key;                                                        \
                V _value;                                                      \
                enum map_color _color;                                         \
        };                                                                     \
                                                                               \
        struct map_##K##_##V                                                   \
        {                                                                      \
                size_t _size;                                                  \
                struct node_##K##_##V *_root;                                  \
        };                                                                     \
                                                                               \
        void map_set_init_##K##_##V(void (*init)(V *));                        \
        void map_set_copy_##K##_##V(void (*copy)(V *, const V *));             \
        void map_set_copy_key_##K##_##V(void (*copy)(K *, const K *));         \
        void map_set_equal_##K##_##V(int (*equal)(const V *, const V *));      \
        void map_set_equal_key_##K##_##V(int (*equal)(const K *, const K *));  \
                                                                               \
        void map_set_compare_##K##_##V(                                        \
            int (*compare)(const void *, const void *));                       \
                                                                               \
        void map_set_free_##K##_##V(void (*free)(K *, V *));                   \
                                                                               \
        struct map_iterator_##K##_##V                                          \
        {                                                                      \
                struct node_##K##_##V *curr;                                   \
                struct node_##K##_##V *next;                                   \
        };                                                                     \
                                                                               \
        K *map_iterator_key_##K##_##V(struct map_iterator_##K##_##V);          \
        V *map_iterator_value_##K##_##V(struct map_iterator_##K##_##V);        \
                                                                               \
        void map_iterator_next_##K##_##V(struct map_iterator_##K##_##V *);     \
        void map_iterator_begin_##K##_##V(struct map_##K##_##V *,              \
                                          struct map_iterator_##K##_##V *);    \
                                                                               \
        void map_iterator_prev_##K##_##V(struct map_iterator_##K##_##V *i);    \
        void map_iterator_end_##K##_##V(struct map_##K##_##V *,                \
                                        struct map_iterator_##K##_##V *);      \
        struct map_iterator_##K##_##V map_begin_##K##_##V(                     \
            struct map_##K##_##V *);                                           \
                                                                               \
        struct map_iterator_##K##_##V map_end_##K##_##V(                       \
            struct map_##K##_##V *);                                           \
                                                                               \
        int map_iterator_equal_##K##_##V(struct map_iterator_##K##_##V,        \
                                         struct map_iterator_##K##_##V);       \
                                                                               \
        struct map_fast_iterator_##K##_##V                                     \
        {                                                                      \
                struct node_##K##_##V *curr;                                   \
                struct node_##K##_##V *next;                                   \
                struct node_##K##_##V **stack;                                 \
                size_t stack_size;                                             \
        };                                                                     \
                                                                               \
        void map_fast_iterator_free_##K##_##V(                                 \
            struct map_fast_iterator_##K##_##V *);                             \
                                                                               \
        void map_fast_iterator_next_##K##_##V(                                 \
            struct map_fast_iterator_##K##_##V *);                             \
        void map_fast_iterator_prev_##K##_##V(                                 \
            struct map_fast_iterator_##K##_##V *);                             \
                                                                               \
        void map_fast_iterator_begin_##K##_##V(                                \
            struct map_##K##_##V *, struct map_fast_iterator_##K##_##V *);     \
        void map_fast_iterator_end_##K##_##V(                                  \
            struct map_##K##_##V *, struct map_fast_iterator_##K##_##V *);     \
                                                                               \
        int map_fast_iterator_equal_##K##_##V(                                 \
            struct map_fast_iterator_##K##_##V,                                \
            struct map_fast_iterator_##K##_##V);                               \
                                                                               \
        size_t map_size_##K##_##V(const struct map_##K##_##V *);               \
                                                                               \
        void map_init_##K##_##V(struct map_##K##_##V *,                        \
                                int (*comp)(const void *, const void *));      \
                                                                               \
        void map_default_init_##K##_##V(struct map_##K##_##V *);               \
                                                                               \
        void map_free_##K##_##V(struct map_##K##_##V *);                       \
                                                                               \
        int map_equal_##K##_##V(struct map_##K##_##V *,                        \
                                struct map_##K##_##V *);                       \
                                                                               \
        void map_copy_##K##_##V(struct map_##K##_##V *__restrict__,            \
                                const struct map_##K##_##V *__restrict__);     \
                                                                               \
        void map_operate_##K##_##V(struct map_##K##_##V *,                     \
                                   void (*operate)(const K *, V *));           \
                                                                               \
        void map_operate_inverted_##K##_##V(struct map_##K##_##V *,            \
                                            void (*operate)(const K *, V *));  \
                                                                               \
        void map_operate_to_##K##_##V(struct map_##K##_##V *,                  \
                                      void (*operate)(const K *, V *, void *), \
                                      void *);                                 \
                                                                               \
        void map_operate_inverted_to_##K##_##V(                                \
            struct map_##K##_##V *, void (*operate)(const K *, V *, void *),   \
            void *);                                                           \
                                                                               \
        struct map_##K##_##V *map_set_##K##_##V(struct map_##K##_##V *m, K k,  \
                                                V v);                          \
                                                                               \
        struct map_iterator_##K##_##V map_find_##K##_##V(                      \
            struct map_##K##_##V *, K);                                        \
                                                                               \
        static struct node_##K##_##V *map_find_node_##K##_##V(                 \
            struct map_##K##_##V *, K);                                        \
        V *map_at_##K##_##V(struct map_##K##_##V *, K);                        \
                                                                               \
        int map_erase_##K##_##V(struct map_##K##_##V *, const K);              \
        int map_iterator_erase_##K##_##V(struct map_##K##_##V *,               \
                                         struct map_iterator_##K##_##V *);
