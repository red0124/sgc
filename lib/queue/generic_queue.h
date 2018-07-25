#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef QUEUE_KILL_WARNINGS
#warning "QUEUE: define 'QUEUE_KILL_WARNINGS' to remove all warnings"

#ifndef QUEUE_KILL_COPY_WARNING
#warning "QUEUE: using '=' as default vector element copy"
#warning "QUEUE: define 'QUEUE_KILL_COPY_WARNING' to remove warning"
#endif

#ifndef QUEUE_KILL_EQUAL_WARNING
#warning "QUEUE: using 'memcmp' as default vector element equal"
#warning "QUEUE: define 'QUEUE_KILL_EQUAL_WARNING' to remove warning"
#endif

#ifndef QUEUE_KILL_FREE_WARNING
#warning "QUEUE: using 'void' as default vector element free"
#warning "QUEUE: define 'QUEUE_KILL_FREE_WARNING' to remove warning"
#endif

#endif

#define INIT_QUEUE(T)                                                          \
                                                                               \
        struct queue_##T                                                       \
        {                                                                      \
                size_t _size;                                                  \
                size_t _max;                                                   \
                size_t _back;                                                  \
                size_t _front;                                                 \
                T *_data;                                                      \
        };                                                                     \
                                                                               \
        void queue_init_##T(struct queue_##T *q)                               \
        {                                                                      \
                q->_size = q->_max = q->_back = q->_front = 0;                 \
                q->_data = NULL;                                               \
        }                                                                      \
                                                                               \
        static void queue_element_default_copy_##T(T *dst, const T *src)       \
        {                                                                      \
                *dst = *src;                                                   \
        }                                                                      \
                                                                               \
        void (*queue_element_copy_##T)(T *, const T *) =                       \
            queue_element_default_copy_##T;                                    \
                                                                               \
        void queue_set_copy_##T(void (*copy)(T *, const T *))                  \
        {                                                                      \
                queue_element_copy_##T = copy;                                 \
        }                                                                      \
                                                                               \
        static int queue_element_default_equal_##T(const T *first,             \
                                                   const T *second)            \
        {                                                                      \
                return memcmp(first, second, sizeof(T)) == 0;                  \
        }                                                                      \
                                                                               \
        int (*queue_element_equal_##T)(const T *, const T *) =                 \
            queue_element_default_equal_##T;                                   \
                                                                               \
        void queue_set_equal_##T(int (*equal)(const T *, const T *))           \
        {                                                                      \
                queue_element_equal_##T = equal;                               \
        }                                                                      \
                                                                               \
        static void queue_element_default_free_##T(T *el)                      \
        {                                                                      \
                (void)el;                                                      \
        }                                                                      \
                                                                               \
        void (*queue_element_free_##T)(T *) = queue_element_default_free_##T;  \
                                                                               \
        void queue_set_free_##T(void (*free)(T *))                             \
        {                                                                      \
                queue_element_free_##T = free;                                 \
        }                                                                      \
                                                                               \
        size_t queue_size_##T(const struct queue_##T *q)                       \
        {                                                                      \
                return q->_size;                                               \
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
                if(!q->_data)                                                  \
                {                                                              \
                        return;                                                \
                }                                                              \
                if(queue_element_free_##T != queue_element_default_free_##T)   \
                {                                                              \
                        for(size_t i = q->_back; i != q->_front;)              \
                        {                                                      \
                                queue_element_free_##T(&q->_data[i]);          \
                                queue_move_##T(&i, q->_max);                   \
                        }                                                      \
                }                                                              \
                free(q->_data);                                                \
        }                                                                      \
                                                                               \
        int queue_equal_##T(struct queue_##T *first, struct queue_##T *second) \
        {                                                                      \
                int equal = (first == second);                                 \
                if(equal == 0 && first->_size == second->_size)                \
                {                                                              \
                        equal = 1;                                             \
                        size_t i = first->_front;                              \
                        size_t j = second->_front;                             \
                        for(size_t k = 0; k < first->_size; ++k)               \
                        {                                                      \
                                if(queue_element_equal_##T(&first->_data[i],   \
                                                           &second->_data[j])) \
                                {                                              \
                                        equal = 0;                             \
                                        break;                                 \
                                }                                              \
                                queue_move_##T(&i, first->_max);               \
                                queue_move_##T(&j, second->_max);              \
                        }                                                      \
                }                                                              \
                return equal;                                                  \
        }                                                                      \
                                                                               \
        void queue_copy_##T(struct queue_##T *restrict dst,                    \
                            const struct queue_##T *restrict src)              \
        {                                                                      \
                if(src->_size != 0)                                            \
                {                                                              \
                        dst->_data = (T *)malloc(src->_size * sizeof(T));      \
                        size_t i = src->_front;                                \
                        for(size_t j = 0; j < src->_size; ++j)                 \
                        {                                                      \
                                queue_element_copy_##T(&dst->_data[j],         \
                                                       &src->_data[i]);        \
                                queue_move_##T(&i, src->_max);                 \
                        }                                                      \
                }                                                              \
                                                                               \
                dst->_size = dst->_max = src->_size;                           \
                dst->_back = src->_size - 1;                                   \
                dst->_front = 0;                                               \
        }                                                                      \
                                                                               \
        static void queue_resize_##T(struct queue_##T *q)                      \
        {                                                                      \
                if(q->_size == q->_max)                                        \
                {                                                              \
                        size_t max = q->_max;                                  \
                        q->_max = (q->_max == 0) ? 1 : q->_max * 2;            \
                                                                               \
                        if(q->_front == 0)                                     \
                        {                                                      \
                                q->_data = (T *)realloc(q->_data,              \
                                                        sizeof(T) * q->_max);  \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                T *new_data =                                  \
                                    (T *)malloc(sizeof(T) * q->_max);          \
                                size_t i = q->_front;                          \
                                size_t j = 0;                                  \
                                do                                             \
                                {                                              \
                                        new_data[j] = q->_data[i];             \
                                        queue_move_##T(&i, max);               \
                                        ++j;                                   \
                                } while(i != q->_back);                        \
                                new_data[j] = q->_data[i];                     \
                                queue_free_##T(q);                             \
                                q->_data = new_data;                           \
                                q->_front = 0;                                 \
                                q->_back = q->_size - 1;                       \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void queue_push_##T(struct queue_##T *q, T el)                         \
        {                                                                      \
                queue_resize_##T(q);                                           \
                queue_move_##T(&q->_back, q->_max);                            \
                queue_element_copy_##T(&q->_data[q->_back], &el);              \
                ++q->_size;                                                    \
        }                                                                      \
                                                                               \
        T *queue_front_##T(const struct queue_##T *q)                          \
        {                                                                      \
                T *ret = NULL;                                                 \
                if(q->_size)                                                   \
                {                                                              \
                        ret = &q->_data[q->_front];                            \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        T *queue_back_##T(const struct queue_##T *q)                           \
        {                                                                      \
                T *ret = NULL;                                                 \
                if(q->_size)                                                   \
                {                                                              \
                        ret = &q->_data[q->_back];                             \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        void queue_pop_##T(struct queue_##T *q)                                \
        {                                                                      \
                if(q->_size)                                                   \
                {                                                              \
                        queue_move_##T(&q->_front, q->_max);                   \
                        --q->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        int queue_empty_##T(const struct queue_##T *q)                         \
        {                                                                      \
                return q->_size == 0;                                          \
        }
