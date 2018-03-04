#pragma once
#include "generic_types.h"
#include <stdlib.h>

#define INIT_STACK_HEADERS(T)                                                  \
                                                                               \
        struct stack_##T                                                       \
        {                                                                      \
                size_t size;                                                   \
                size_t max;                                                    \
                T *data;                                                       \
                void (*copy)(T *, const T *);                                  \
                void (*free)(T *);                                             \
                int (*equ)(const T *, const T *);                              \
        };                                                                     \
                                                                               \
        size_t stack_size_##T(const struct stack_##T *);                       \
        struct stack_##T stack_new_##T();                                      \
                                                                               \
        void stack_set_copy_##T(struct stack_##T *,                            \
                                void (*copy)(T *, const T *));                 \
        void stack_set_comp_##T(struct stack_##T *,                            \
                                int (*comp)(const void *, const void *));      \
        void stack_set_equ_##T(struct stack_##T *,                             \
                               int (*equ)(const T *, const T *));              \
                                                                               \
        void stack_init_##T(struct stack_##T *);                               \
        void stack_free_##T(struct stack_##T *);                               \
        int stack_equ_##T(struct stack_##T *, struct stack_##T *);             \
                                                                               \
        void stack_copy_##T(struct stack_##T *restrict,                        \
                            const struct stack_##T *restrict);                 \
                                                                               \
        void stack_push_##T(struct stack_##T *, T);                            \
        void stack_pop_##T(struct stack_##T *);                                \
        T stack_top_##T(const struct stack_##T *);                             \
        int stack_empty_##T(struct stack_##T *);
