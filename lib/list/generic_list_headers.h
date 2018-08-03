#pragma once
#include "generic_types.h"
#include <stdlib.h>

#define INIT_LIST_HEADERS(T)                                                   \
                                                                               \
        struct node_##T                                                        \
        {                                                                      \
                T data;                                                        \
                struct node_##T *next;                                         \
                struct node_##T *prev;                                         \
        };                                                                     \
                                                                               \
        struct list_##T                                                        \
        {                                                                      \
                size_t size;                                                   \
                struct node_##T *head;                                         \
                struct node_##T *tail;                                         \
        };                                                                     \
                                                                               \
        size_t list_size_##T(const struct list_##T *);                         \
                                                                               \
        void list_set_init_##T(void (*init)(T *));                             \
        void list_set_copy_##T(void (*copy)(T *, const T *));                  \
        void list_set_free_##T(void (*free)(T *));                             \
        void list_set_compare_##T(int (*compare)(const void *, const void *)); \
        void list_set_equal_##T(int (*equal)(const T *, const T *));           \
                                                                               \
        void list_init_##T(struct list_##T *);                                 \
        void list_free_##T(struct list_##T *);                                 \
        int list_equal_##T(const struct list_##T *, const struct list_##T *);  \
        void list_copy_##T(struct list_##T *restrict,                          \
                           const struct list_##T *restrict);                   \
                                                                               \
        void list_push_back_##T(struct list_##T *, const T);                   \
        void list_push_front_##T(struct list_##T *, const T);                  \
                                                                               \
        T *list_back_##T(const struct list_##T *l);                            \
        T *list_pop_back_##T(struct list_##T *);                               \
                                                                               \
        T *list_front_##T(const struct list_##T *);                            \
        T *list_pop_front_##T(struct list_##T *);                              \
        T *list_at_##T(const struct list_##T *, const size_t at);              \
                                                                               \
        int list_find_##T(const struct list_##T *, const T);                   \
                                                                               \
        void list_operate_##T(struct list_##T *, void (*operate)(T *));        \
        void list_operate_to_##T(struct list_##T *,                            \
                                 void (*operate)(T *, void *), void *);        \
        void list_operate_inverted_##T(struct list_##T *,                      \
                                       void (*operate)(T *));                  \
        void list_operate_inverted_to_##T(struct list_##T *,                   \
                                 void (*operate)(T *, void *), void *);        \
                                                                               \
        int list_erase_##T(struct list_##T *, const T);                        \
        int list_erase_all_##T(struct list_##T *, const T);                    \
        int list_erase_at_##T(struct list_##T *, size_t at);                   \
                                                                               \
        int list_is_empty_##T(const struct list_##T *);                        \
        int list_is_sorted_##T(const struct list_##T *,                        \
                               int (*compare)(const void *, const void *));    \
                                                                               \
        void list_insert_##T(struct list_##T *, const size_t, const T);        \
        int list_insert_sorted_##T(struct list_##T *, const T);                \
                                                                               \
        void list_sort_primitive_##T(                                          \
            struct list_##T *, int (*compare)(const void *, const void *));    \
        void list_sort_##T(struct list_##T *,                                  \
                           int (*compare)(const void *, const void *));\
