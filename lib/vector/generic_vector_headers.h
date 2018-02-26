#pragma once
#include "generic_types.h"
#include <stdlib.h>

#define INIT_VECTOR_HEADERS(T)                                                 \
                                                                               \
        struct vector_##T                                                      \
        {                                                                      \
                size_t size;                                                   \
                size_t max;                                                    \
                T *data;                                                       \
                void (*copy)(T *, const T *);                                  \
                void (*free)(T *);                                             \
                int (*comp)(const void *, const void *);                       \
                int (*equ)(const T *, const T *);                              \
        };                                                                     \
                                                                               \
        size_t vector_size_##T(const struct vector_##T *);                     \
                                                                               \
        void vector_set_copy_##T(struct vector_##T *,                          \
                                 void (*copy)(T *, const T *));                \
        void vector_set_free_##T(struct vector_##T *, void (*free_)(T *));     \
        void vector_set_comp_##T(struct vector_##T *,                          \
                                 int (*comp)(const void *, const void *));     \
        void vector_set_equ_##T(struct vector_##T *,                           \
                                int (*equ)(const T *, const T *));             \
                                                                               \
        void vector_init_##T(struct vector_##T *);                             \
        void vector_free_##T(struct vector_##T *);                             \
        int vector_equ_##T(struct vector_##T *, struct vector_##T *);          \
        void vector_copy_##T(struct vector_##T *restrict,                      \
                             const struct vector_##T *restrict);               \
                                                                               \
        void vector_from_array_##T(struct vector_##T *, const T *,             \
                                   const size_t);                              \
                                                                               \
        void vector_set_##T(struct vector_##T *, const size_t, T);             \
                                                                               \
        void vector_operate_##T(struct vector_##T *, void (*operate)(T *));    \
        void vector_operate_to_##T(struct vector_##T *,                        \
                                   void (*operate)(T *, void *), void *);      \
        void vector_operate_inverted_##T(struct vector_##T *,                  \
                                         void (*operate)(void *));             \
                                                                               \
        void vector_assign_##T(struct vector_##T *, size_t, size_t, T);        \
                                                                               \
        void vector_push_back_##T(struct vector_##T *, T);                     \
        T vector_pop_back_##T(struct vector_##T *);                            \
        T vector_back_##T(const struct vector_##T *);                          \
                                                                               \
        void vector_insert_##T(struct vector_##T *, const size_t, T);          \
        T vector_at_##T(const struct vector_##T *, const size_t);              \
                                                                               \
        void vector_push_front_##T(struct vector_##T *, T);                    \
        T vector_front_##T(const struct vector_##T *);                         \
                                                                               \
        long long vector_locate_##T(const struct vector_##T *, const T);       \
        int vector_find_##T(const struct vector_##T *, const T);               \
        size_t vector_count_##T(const struct vector_##T *, const T);           \
                                                                               \
        void vector_erase_at_##T(struct vector_##T *, const size_t);           \
        int vector_erase_##T(struct vector_##T *, const T);                    \
        int vector_erase_all_##T(struct vector_##T *, const T);                \
                                                                               \
        int vector_is_sorted_##T(const struct vector_##T *,                    \
                                 int (*comp)(const void *, const void *));     \
                                                                               \
        void vector_sort_##T(struct vector_##T *,                              \
                             int (*comp)(const void *, const void *));\
\
