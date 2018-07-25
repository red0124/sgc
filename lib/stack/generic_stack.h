#pragma once
#include <stdlib.h>
#include <string.h>

#ifndef STACK_KILL_WARNINGS
#warning "STACK: define 'STACK_KILL_WARNINGS' to remove all warnings"

#ifndef STACK_KILL_COPY_WARNING
#warning "STACK: using '=' as default stack element copy"
#warning "STACK: define 'STACK_KILL_COPY_WARNING' to remove warning"
#endif

#ifndef STACK_KILL_EQUAL_WARNING
#warning "STACK: using 'memcmp' as default stack element equal"
#warning "STACK: define 'STACK_KILL_EQUAL_WARNING' to remove warning"
#endif

#ifndef STACK_KILL_FREE_WARNING
#warning "STACK: using 'void' as default stack element free"
#warning "STACK: define 'STACK_KILL_FREE_WARNING' to remove warning"
#endif

#endif

#define INIT_STACK(T)                                                          \
                                                                               \
        struct stack_##T                                                       \
        {                                                                      \
                size_t _size;                                                  \
                size_t _max;                                                   \
                T *_data;                                                      \
        };                                                                     \
                                                                               \
        static void stack_element_default_copy_##T(T *dst, const T *src)       \
        {                                                                      \
                *dst = *src;                                                   \
        }                                                                      \
                                                                               \
        void (*stack_element_copy_##T)(T *, const T *) =                       \
            stack_element_default_copy_##T;                                    \
                                                                               \
        void stack_set_copy_##T(void (*copy)(T *, const T *))                  \
        {                                                                      \
                stack_element_copy_##T = copy;                                 \
        }                                                                      \
                                                                               \
        static int stack_element_default_equal_##T(const T *first,             \
                                                   const T *second)            \
        {                                                                      \
                return memcmp(first, second, sizeof(T)) == 0;                  \
        }                                                                      \
                                                                               \
        int (*stack_element_equal_##T)(const T *, const T *) =                 \
            stack_element_default_equal_##T;                                   \
                                                                               \
        void stack_set_equal_##T(int (*equal)(const T *, const T *))           \
        {                                                                      \
                stack_element_equal_##T = equal;                               \
        }                                                                      \
                                                                               \
        static void stack_element_default_free_##T(T *el)                      \
        {                                                                      \
                (void)el;                                                      \
        }                                                                      \
                                                                               \
        void (*stack_element_free_##T)(T *) = stack_element_default_free_##T;  \
                                                                               \
        void stack_set_free_##T(void (*free)(T *))                             \
        {                                                                      \
                stack_element_free_##T = free;                                 \
        }                                                                      \
                                                                               \
        size_t stack_size_##T(const struct stack_##T *s)                       \
        {                                                                      \
                return s->_size;                                               \
        }                                                                      \
                                                                               \
        void stack_init_##T(struct stack_##T *s)                               \
        {                                                                      \
                s->_size = s->_max = 0;                                        \
                s->_data = NULL;                                               \
        }                                                                      \
                                                                               \
        void stack_free_##T(struct stack_##T *s)                               \
        {                                                                      \
                if(s->_data)                                                   \
                {                                                              \
                        if(stack_element_free_##T !=                           \
                           stack_element_default_free_##T)                     \
                        {                                                      \
                                for(size_t i = 0; i < s->_size; ++i)           \
                                {                                              \
                                        stack_element_free_##T(&s->_data[i]);  \
                                }                                              \
                        }                                                      \
                        free(s->_data);                                        \
                }                                                              \
        }                                                                      \
                                                                               \
        int stack_equal_##T(struct stack_##T *first, struct stack_##T *second) \
        {                                                                      \
                int equal = (first == second);                                 \
                if(equal == 0 && first->_size == second->_size)                \
                {                                                              \
                        equal = 1;                                             \
                        for(size_t i = 0; i < first->_size; ++i)               \
                        {                                                      \
                                if(stack_element_equal_##T(&first->_data[i],   \
                                                           &second->_data[i])) \
                                {                                              \
                                        equal = 0;                             \
                                        break;                                 \
                                }                                              \
                        }                                                      \
                }                                                              \
                return equal;                                                  \
        }                                                                      \
                                                                               \
        void stack_copy_##T(struct stack_##T *__restrict__ dst,                \
                            const struct stack_##T *__restrict__ src)          \
        {                                                                      \
                dst->_size = src->_size;                                       \
                dst->_max = src->_size;                                        \
                if(src->_size != 0)                                            \
                {                                                              \
                        dst->_data = (T *)malloc(dst->_max * sizeof(T));       \
                        if(stack_element_copy_##T ==                           \
                           stack_element_default_copy_##T)                     \
                        {                                                      \
                                memcpy(dst->_data, src->_data,                 \
                                       sizeof(T) * src->_size);                \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                for(size_t i = 0; i < dst->_size; ++i)         \
                                {                                              \
                                        stack_element_copy_##T(                \
                                            &dst->_data[i], &src->_data[i]);   \
                                }                                              \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        static void stack_resize_##T(struct stack_##T *s)                      \
        {                                                                      \
                if(s->_size == s->_max)                                        \
                {                                                              \
                        s->_max = (s->_max == 0) ? 1 : s->_max * 2;            \
                        s->_data =                                             \
                            (T *)realloc(s->_data, sizeof(T) * s->_max);       \
                }                                                              \
        }                                                                      \
                                                                               \
        void stack_push_##T(struct stack_##T *s, T el)                         \
        {                                                                      \
                stack_resize_##T(s);                                           \
                stack_element_copy_##T(&s->_data[s->_size], &el);              \
                ++s->_size;                                                    \
        }                                                                      \
                                                                               \
        void stack_pop_##T(struct stack_##T *s)                                \
        {                                                                      \
                if(s->_size)                                                   \
                {                                                              \
                        --s->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        T stack_top_##T(const struct stack_##T *s)                             \
        {                                                                      \
                if(s->_size)                                                   \
                {                                                              \
                        return s->_data[s->_size - 1];                         \
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
                return s->_size == 0;                                          \
        }
