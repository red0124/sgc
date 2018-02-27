#pragma once
#include <stdlib.h>
#include <string.h>

#define INIT_STACK(T)                                                          \
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
        static void stack_flat_copy_##T(T *dst, const T *src)                  \
        {                                                                      \
                *dst = *src;                                                   \
        }                                                                      \
                                                                               \
        static int stack_flat_equ_##T(const T *first, const T *second)         \
        {                                                                      \
                return memcmp(first, second, sizeof(T)) == 0;                  \
        }                                                                      \
                                                                               \
        size_t stack_size_##T(const struct stack_##T *s)                       \
        {                                                                      \
                return s->size;                                                \
        }                                                                      \
                                                                               \
        struct stack_##T stack_new_##T()                                       \
        {                                                                      \
                struct stack_##T s = {0,    0,                                 \
                                      NULL, stack_flat_copy_##T,               \
                                      NULL, stack_flat_equ_##T};               \
                return s;                                                      \
        }                                                                      \
                                                                               \
        void stack_set_copy_##T(struct stack_##T *s,                           \
                                void (*copy)(T *, const T *))                  \
        {                                                                      \
                s->copy = copy;                                                \
        }                                                                      \
                                                                               \
        void stack_set_free_##T(struct stack_##T *s, void (*free_)(T *))       \
        {                                                                      \
                s->free = free_;                                               \
        }                                                                      \
                                                                               \
        void stack_set_equ_##T(struct stack_##T *s,                            \
                               int (*equ)(const T *, const T *))               \
        {                                                                      \
                s->equ = equ;                                                  \
        }                                                                      \
                                                                               \
        void stack_init_##T(struct stack_##T *s)                               \
        {                                                                      \
                s->size = 0;                                                   \
                s->max = 0;                                                    \
                s->data = NULL;                                                \
                s->copy = stack_flat_copy_##T;                                 \
                s->free = NULL;                                                \
                s->equ = stack_flat_equ_##T;                                   \
        }                                                                      \
                                                                               \
        void stack_free_##T(struct stack_##T *s)                               \
        {                                                                      \
                if(s->data)                                                    \
                {                                                              \
                        if(s->free)                                            \
                        {                                                      \
                                for(size_t i = 0; i < s->size; ++i)            \
                                {                                              \
                                        s->free(&s->data[i]);                  \
                                }                                              \
                        }                                                      \
                        free(s->data);                                         \
                }                                                              \
        }                                                                      \
                                                                               \
        int stack_equ_##T(struct stack_##T *first, struct stack_##T *second)   \
        {                                                                      \
                int equal = (first == second);                                 \
                if(equal == 0 && first->size == second->size)                  \
                {                                                              \
                        equal = 1;                                             \
                        for(size_t i = 0; i < first->size; ++i)                \
                        {                                                      \
                                if(!first->equ(&first->data[i],                \
                                               &second->data[i]))              \
                                {                                              \
                                        equal = 0;                             \
                                        break;                                 \
                                }                                              \
                        }                                                      \
                }                                                              \
                return equal;                                                  \
        }                                                                      \
                                                                               \
        void stack_copy_##T(struct stack_##T *restrict dst,                    \
                            const struct stack_##T *restrict src)              \
        {                                                                      \
                if(src->size != 0)                                             \
                {                                                              \
                        dst->size = src->size;                                 \
                        dst->max = src->size;                                  \
                        dst->data = (T *)malloc(dst->max * sizeof(T));         \
                        for(size_t i = 0; i < dst->size; ++i)                  \
                        {                                                      \
                                src->copy(&dst->data[i], &src->data[i]);       \
                        }                                                      \
                }                                                              \
                dst->copy = src->copy;                                         \
                dst->free = src->free;                                         \
                dst->equ = src->equ;                                           \
        }                                                                      \
                                                                               \
        static void stack_resize_##T(struct stack_##T *s)                      \
        {                                                                      \
                if(s->size == s->max)                                          \
                {                                                              \
                        if(s->max == 0)                                        \
                        {                                                      \
                                s->max = 1;                                    \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                s->max *= 2;                                   \
                        }                                                      \
                        s->data = (T *)realloc(s->data, sizeof(T) * s->max);   \
                }                                                              \
        }                                                                      \
                                                                               \
        void stack_push_##T(struct stack_##T *s, T el)                         \
        {                                                                      \
                stack_resize_##T(s);                                           \
                s->copy(&s->data[s->size], &el);                               \
                ++s->size;                                                     \
        }                                                                      \
                                                                               \
        void stack_pop_##T(struct stack_##T *s)                                \
        {                                                                      \
                if(s->size)                                                    \
                {                                                              \
                        --s->size;                                             \
                }                                                              \
        }                                                                      \
                                                                               \
        T stack_top_##T(struct stack_##T *s)                                   \
        {                                                                      \
                if(s->size)                                                    \
                {                                                              \
                        return s->data[s->size - 1];                           \
                }                                                              \
                else                                                           \
                {                                                              \
                        fprintf(stderr,                                        \
                                "STACK ERROR :: THE STACK IS EMPTY\n");        \
                        exit(1);                                               \
                }                                                              \
        }                                                                      \
                                                                               \
        int stack_empty_##T(struct stack_##T *s)                               \
        {                                                                      \
                return s->size == 0;                                           \
        }
