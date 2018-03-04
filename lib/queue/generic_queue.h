#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_QUEUE(T)                                                          \
                                                                               \
        struct queue_##T                                                       \
        {                                                                      \
                size_t size;                                                   \
                size_t max;                                                    \
                size_t back;                                                   \
                size_t front;                                                  \
                T *data;                                                       \
                void (*copy)(T *, const T *);                                  \
                void (*free)(T *);                                             \
                int (*equ)(const T *, const T *);                              \
        };                                                                     \
                                                                               \
        static void queue_flat_copy_##T(T *dst, const T *src)                  \
        {                                                                      \
                *dst = *src;                                                   \
        }                                                                      \
                                                                               \
        static int queue_flat_equ_##T(const T *first, const T *second)         \
        {                                                                      \
                return memcmp(first, second, sizeof(T)) == 0;                  \
        }                                                                      \
                                                                               \
        size_t queue_size_##T(const struct queue_##T *q)                       \
        {                                                                      \
                return q->size;                                                \
        }                                                                      \
                                                                               \
        struct queue_##T queue_new_##T()                                       \
        {                                                                      \
                struct queue_##T q = {0,    0,                                 \
                                      0,    0,                                 \
                                      NULL, queue_flat_copy_##T,               \
                                      NULL, queue_flat_equ_##T};               \
                return q;                                                      \
        }                                                                      \
                                                                               \
        void queue_set_copy_##T(struct queue_##T *q,                           \
                                void (*copy)(T *, const T *))                  \
        {                                                                      \
                q->copy = copy;                                                \
        }                                                                      \
                                                                               \
        void queue_set_free_##T(struct queue_##T *q, void (*free_)(T *))       \
        {                                                                      \
                q->free = free_;                                               \
        }                                                                      \
                                                                               \
        void queue_set_equ_##T(struct queue_##T *q,                            \
                               int (*equ)(const T *, const T *))               \
        {                                                                      \
                q->equ = equ;                                                  \
        }                                                                      \
                                                                               \
        void queue_init_##T(struct queue_##T *q)                               \
        {                                                                      \
                q->size = q->max = q->back = q->front = 0;                     \
                q->data = NULL;                                                \
                q->copy = queue_flat_copy_##T;                                 \
                q->free = NULL;                                                \
                q->equ = queue_flat_equ_##T;                                   \
        }                                                                      \
                                                                               \
        static void queue_move_##T(size_t *flag, const size_t max)             \
        {                                                                      \
                if(*flag + 1 == max)                                           \
                {                                                              \
                        *flag = 0;                                             \
                }                                                              \
                else                                                           \
                {                                                              \
                        ++*flag;                                               \
                }                                                              \
        }                                                                      \
                                                                               \
        void queue_free_##T(struct queue_##T *q)                               \
        {                                                                      \
                if(!q->data)                                                   \
                {                                                              \
                        return;                                                \
                }                                                              \
                if(q->free)                                                    \
                {                                                              \
                        size_t i = q->back;                                    \
                        while(i != q->front)                                   \
                        {                                                      \
                                q->free(&q->data[i]);                          \
                                queue_move_##T(&i, q->max);                    \
                        }                                                      \
                }                                                              \
                free(q->data);                                                 \
        }                                                                      \
                                                                               \
        int queue_equ_##T(struct queue_##T *first, struct queue_##T *second)   \
        {                                                                      \
                int equal = (first == second);                                 \
                if(equal == 0 && first->size == second->size)                  \
                {                                                              \
                        equal = 1;                                             \
                        size_t i = first->front;                               \
                        size_t j = second->front;                              \
                        for(size_t k = 0; k < first->size; ++k)                \
                        {                                                      \
                                if(!first->equ(&first->data[i],                \
                                               &second->data[j]))              \
                                {                                              \
                                        equal = 0;                             \
                                        break;                                 \
                                }                                              \
                                queue_move_##T(&i, first->max);                \
                                queue_move_##T(&j, second->max);               \
                        }                                                      \
                }                                                              \
                return equal;                                                  \
        }                                                                      \
                                                                               \
        void queue_copy_##T(struct queue_##T *restrict dst,                    \
                            const struct queue_##T *restrict src)              \
        {                                                                      \
                if(src->size != 0)                                             \
                {                                                              \
                        dst->data = (T *)malloc(src->size * sizeof(T));        \
                        size_t i = src->front;                                 \
                        for(size_t j = 0; j < src->size; ++j)                  \
                        {                                                      \
                                src->copy(&dst->data[j], &src->data[i]);       \
                                queue_move_##T(&i, src->max);                  \
                        }                                                      \
                }                                                              \
                                                                               \
                dst->size = dst->max = src->size;                              \
                dst->back = src->size - 1;                                     \
                dst->front = 0;                                                \
                                                                               \
                dst->copy = src->copy;                                         \
                dst->free = src->free;                                         \
                dst->equ = src->equ;                                           \
        }                                                                      \
                                                                               \
        static void queue_resize_##T(struct queue_##T *q)                      \
        {                                                                      \
                if(q->size == q->max)                                          \
                {                                                              \
                        q->max = (q->max == 0) ? 1 : q->max * 2;               \
                                                                               \
                        if(q->front == 0)                                      \
                        {                                                      \
                                q->data =                                      \
                                    (T *)realloc(q->data, sizeof(T) * q->max); \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                T *new_data = (T *)malloc(sizeof(T) * q->max); \
                                size_t i = q->back;                            \
                                size_t j = 0;                                  \
                                while(i != q->front)                           \
                                {                                              \
                                        new_data[j] = q->data[i];              \
                                        queue_move_##T(&i, q->max);            \
                                        ++j;                                   \
                                }                                              \
                                free(q->data);                                 \
                                q->data = new_data;                            \
                                q->front = 0;                                  \
                                q->back = q->size;                             \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void queue_push_##T(struct queue_##T *q, T el)                         \
        {                                                                      \
                queue_resize_##T(q);                                           \
                queue_move_##T(&q->back, q->max);                              \
                q->copy(&q->data[q->back], &el);                               \
                ++q->size;                                                     \
        }                                                                      \
                                                                               \
        T queue_front_##T(const struct queue_##T *q)                           \
        {                                                                      \
                if(q->size)                                                    \
                {                                                              \
                        return q->data[q->front];                              \
                }                                                              \
                else                                                           \
                {                                                              \
                        fprintf(stderr,                                        \
                                "QUEUE ERROR :: THE QUEUE IS EMPTY\n");        \
                        exit(1);                                               \
                }                                                              \
        }                                                                      \
                                                                               \
        T queue_back_##T(const struct queue_##T *q)                            \
        {                                                                      \
                if(q->size)                                                    \
                {                                                              \
                        return q->data[q->back];                               \
                }                                                              \
                else                                                           \
                {                                                              \
                        fprintf(stderr,                                        \
                                "QUEUE ERROR :: THE QUEUE IS EMPTY\n");        \
                        exit(1);                                               \
                }                                                              \
        }                                                                      \
                                                                               \
        void queue_pop_##T(struct queue_##T *q)                                \
        {                                                                      \
                if(q->size)                                                    \
                {                                                              \
                        queue_move_##T(&q->front, q->max);                     \
                        --q->size;                                             \
                }                                                              \
        }                                                                      \
                                                                               \
        int queue_empty_##T(const struct queue_##T *q)                         \
        {                                                                      \
                return q->size == 0;                                           \
        }
