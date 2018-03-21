#pragma once
#include "generic_types.h"
#include <stdlib.h>

#define INIT_VECTOR_HEADERS(T)                                                 \
                                                                               \
        struct vector_##T                                                      \
        {                                                                      \
                size_t _size;                                                  \
                size_t _max;                                                   \
                T *_data;                                                      \
                void (*_copy)(T *, const T *);                                 \
                void (*_free)(T *);                                            \
                int (*_comp)(const void *, const void *);                      \
                int (*_equ)(const T *, const T *);                             \
                size_t (*size)(const struct vector_##T *);                     \
                void (*set_copy)(struct vector_##T *,                          \
                                 void (*copy)(T *, const T *));                \
                void (*set_free)(struct vector_##T *, void (*free)(T *));      \
                void (*set_comp)(struct vector_##T *,                          \
                                 int (*comp)(const void *, const void *));     \
                void (*set_equ)(struct vector_##T *,                           \
                                int (*equ)(const T *, const T *));             \
                void (*free)(struct vector_##T *);                             \
                int (*equ)(const struct vector_##T *,                          \
                           const struct vector_##T *);                         \
                void (*copy)(struct vector_##T * restrict,                     \
                             const struct vector_##T *restrict);               \
                void (*from_array)(struct vector_##T *, const T *,             \
                                   const size_t);                              \
                void (*set)(struct vector_##T *, const size_t, T);             \
                void (*operate)(struct vector_##T *, void (*operate)(T *));    \
                void (*operate_to)(struct vector_##T *,                        \
                                   void (*operate)(T *, void *), void *);      \
                void (*operate_inverted)(struct vector_##T *,                  \
                                         void (*operate)(T *));                \
                void (*assign)(struct vector_##T *, size_t, size_t, T);        \
                void (*push_back)(struct vector_##T *, T);                     \
                void (*push_front)(struct vector_##T *, T);                    \
                T *(*pop_back)(struct vector_##T *);                           \
                void (*insert)(struct vector_##T *, const size_t, T);          \
                T *(*at)(struct vector_##T *, const size_t);                   \
                T *(*back)(struct vector_##T *);                               \
                T *(*front)(struct vector_##T *);                              \
                ssize_t (*locate)(const struct vector_##T *, const T);         \
                int (*find)(const struct vector_##T *, const T);               \
                size_t (*count)(const struct vector_##T *, const T);           \
                void (*erase_at)(struct vector_##T *, const size_t);           \
                int (*erase)(struct vector_##T *, const T);                    \
                int (*erase_all)(struct vector_##T *, const T);                \
                int (*is_sorted)(const struct vector_##T *,                    \
                                 int (*comp)(const void *, const void *));     \
                void (*sort)(struct vector_##T *,                              \
                             int (*comp)(const void *, const void *));         \
                struct vector_##T (*new)();                                    \
                void (*init)(struct vector_##T *);                             \
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
        int vector_equ_##T(const struct vector_##T *,                          \
                           const struct vector_##T *);                         \
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
                                         void (*operate)(T *));                \
                                                                               \
        void vector_assign_##T(struct vector_##T *, size_t, size_t, T);        \
                                                                               \
        void vector_push_back_##T(struct vector_##T *, T);                     \
        T *vector_pop_back_##T(struct vector_##T *);                           \
        T *vector_back_##T(struct vector_##T *);                               \
                                                                               \
        void vector_insert_##T(struct vector_##T *, const size_t, T);          \
        T *vector_at_##T(struct vector_##T *, const size_t);                   \
                                                                               \
        void vector_push_front_##T(struct vector_##T *, T);                    \
        T *vector_front_##T(struct vector_##T *);                              \
                                                                               \
        ssize_t vector_locate_##T(const struct vector_##T *, const T);         \
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
