#pragma once

#include <stdlib.h>
#include <string.h>

#ifndef _STACK_MACRO_
#define _STACK_MACRO_

#define STACKSIZE 64

#define PREPARE_STACK                                                          \
        char *stack[STACKSIZE];                                                \
        char **stackptr = stack

#define PUSH(array, limit)                                                     \
        stackptr[0] = array;                                                   \
        stackptr[1] = limit;                                                   \
        stackptr += 2

#define POP(array, limit)                                                      \
        stackptr -= 2;                                                         \
        array = stackptr[0];                                                   \
        limit = stackptr[1]
#endif

#define THRESH 7

#define INIT_VECTOR(T)                                                         \
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
        static void flat_copy_##T(T *dst, const T *src)                        \
        {                                                                      \
                *dst = *src;                                                   \
        }                                                                      \
                                                                               \
        static int flat_equ_##T(const T *first, const T *second)               \
        {                                                                      \
                return memcmp(first, second, sizeof(T)) == 0;                  \
        }                                                                      \
                                                                               \
        static int flat_comp_##T(const void *first, const void *second)        \
        {                                                                      \
                return memcmp(first, second, sizeof(T)) > 0;                   \
        }                                                                      \
                                                                               \
        size_t vector_size_##T(const struct vector_##T *v)                     \
        {                                                                      \
                return v->size;                                                \
        }                                                                      \
                                                                               \
        struct vector_##T vector_new_##T()                                     \
        {                                                                      \
                struct vector_##T v = {                                        \
                    0,           0, NULL, flat_copy_##T, NULL, flat_comp_##T,  \
                    flat_equ_##T};                                             \
                return v;                                                      \
        }                                                                      \
                                                                               \
        void vector_set_copy_##T(struct vector_##T *v,                         \
                                 void (*copy)(T *, const T *))                 \
        {                                                                      \
                v->copy = copy;                                                \
        }                                                                      \
                                                                               \
        void vector_set_free_##T(struct vector_##T *v, void (*free_)(T *))     \
        {                                                                      \
                v->free = free_;                                               \
        }                                                                      \
                                                                               \
        void vector_set_comp_##T(struct vector_##T *v,                         \
                                 int (*comp)(const void *, const void *))      \
        {                                                                      \
                v->comp = comp;                                                \
        }                                                                      \
                                                                               \
        void vector_set_equ_##T(struct vector_##T *v,                          \
                                int (*equ)(const T *, const T *))              \
        {                                                                      \
                v->equ = equ;                                                  \
        }                                                                      \
                                                                               \
        void vector_init_##T(struct vector_##T *v)                             \
        {                                                                      \
                v->size = 0;                                                   \
                v->max = 0;                                                    \
                v->data = NULL;                                                \
                v->copy = flat_copy_##T;                                       \
                v->free = NULL;                                                \
                v->comp = flat_comp_##T;                                       \
                v->equ = flat_equ_##T;                                         \
        }                                                                      \
                                                                               \
        void vector_free_##T(struct vector_##T *v)                             \
        {                                                                      \
                if(v->data)                                                    \
                {                                                              \
                        if(v->free)                                            \
                        {                                                      \
                                for(size_t i = 0; i < v->size; ++i)            \
                                {                                              \
                                        v->free(&v->data[i]);                  \
                                }                                              \
                        }                                                      \
                        free(v->data);                                         \
                }                                                              \
        }                                                                      \
                                                                               \
        int vector_equ_##T(struct vector_##T *first,                           \
                           struct vector_##T *second)                          \
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
        void vector_copy_##T(struct vector_##T *restrict dst,                  \
                             const struct vector_##T *restrict src)            \
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
                dst->comp = src->comp;                                         \
                dst->equ = src->equ;                                           \
        }                                                                      \
                                                                               \
        void vector_from_array_##T(struct vector_##T *v, const T *arr,         \
                                   const size_t size)                          \
        {                                                                      \
                v->max = v->size = size;                                       \
                v->data = (T *)malloc(sizeof(T *) * size);                     \
                for(size_t i = 0; i < v->size; ++i)                            \
                {                                                              \
                        v->copy(&v->data[i], &arr[i]);                         \
                }                                                              \
        }                                                                      \
                                                                               \
        static void vector_resize_##T(struct vector_##T *v)                    \
        {                                                                      \
                if(v->size == v->max)                                          \
                {                                                              \
                        if(v->max == 0)                                        \
                        {                                                      \
                                v->max = 1;                                    \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                v->max *= 2;                                   \
                        }                                                      \
                        v->data = (T *)realloc(v->data, sizeof(T) * v->max);   \
                }                                                              \
        }                                                                      \
                                                                               \
        void vector_set_##T(struct vector_##T *v, const size_t at, T el)       \
        {                                                                      \
                if(at < v->size)                                               \
                {                                                              \
                        v->copy(&v->data[at], &el);                            \
                }                                                              \
        }                                                                      \
                                                                               \
        void vector_operate_##T(struct vector_##T *v, void (*operate)(T *))    \
        {                                                                      \
                for(size_t i = 0; i < v->size; ++i)                            \
                {                                                              \
                        operate(&v->data[i]);                                  \
                }                                                              \
        }                                                                      \
        void vector_operate_to_##T(struct vector_##T *v,                       \
                                   void (*operate)(T *, void *), void *argout) \
        {                                                                      \
                for(size_t i = 0; i < v->size; ++i)                            \
                {                                                              \
                        operate(&v->data[i], argout);                          \
                }                                                              \
        }                                                                      \
                                                                               \
        void vector_operate_inverted_##T(struct vector_##T *v,                 \
                                         void (*operate)(void *))              \
        {                                                                      \
                for(size_t i = v->size; i > 0; --i)                            \
                {                                                              \
                        operate(&v->data[i - 1]);                              \
                }                                                              \
        }                                                                      \
                                                                               \
        void vector_assign_##T(struct vector_##T *v, size_t begin, size_t end, \
                               T el)                                           \
        {                                                                      \
                if(v->size > end && end > begin)                               \
                {                                                              \
                        for(size_t i = begin; i < end; ++i)                    \
                        {                                                      \
                                v->copy(&v->data[i], &el);                     \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void vector_push_back_##T(struct vector_##T *v, T el)                  \
        {                                                                      \
                vector_resize_##T(v);                                          \
                v->copy(&v->data[v->size], &el);                               \
                ++v->size;                                                     \
        }                                                                      \
                                                                               \
        T vector_pop_back_##T(struct vector_##T *v)                            \
        {                                                                      \
                if(v->size)                                                    \
                {                                                              \
                        --v->size;                                             \
                        return v->data[v->size];                               \
                }                                                              \
                else                                                           \
                {                                                              \
                        fprintf(stderr,                                        \
                                "VECTOR ERROR :: THE VECTOR IS EMPTY\n");      \
                        exit(1);                                               \
                }                                                              \
        }                                                                      \
                                                                               \
        T vector_back_##T(const struct vector_##T *v)                          \
        {                                                                      \
                if(v->size)                                                    \
                {                                                              \
                        return v->data[v->size];                               \
                }                                                              \
                else                                                           \
                {                                                              \
                        fprintf(stderr,                                        \
                                "VECTOR ERROR :: THE VECTOR IS EMPTY\n");      \
                        exit(1);                                               \
                }                                                              \
        }                                                                      \
                                                                               \
        void vector_insert_##T(struct vector_##T *v, const size_t at, T el)    \
        {                                                                      \
                if(at < v->size)                                               \
                {                                                              \
                        vector_resize_##T(v);                                  \
                        for(size_t i = v->size - 1; i > at; --i)               \
                        {                                                      \
                                v->copy(&v->data[i], &v->data[i - 1]);         \
                                v->copy(&v->data[at], &el);                    \
                                ++v->size;                                     \
                        }                                                      \
                }                                                              \
                else                                                           \
                {                                                              \
                        vector_push_back_##T(v, el);                           \
                }                                                              \
        }                                                                      \
                                                                               \
        T vector_at_##T(const struct vector_##T *v, const size_t at)           \
        {                                                                      \
                if(at < v->size)                                               \
                {                                                              \
                        return v->data[at];                                    \
                }                                                              \
                else                                                           \
                {                                                              \
                        fprintf(stderr,                                        \
                                "VECTOR ERROR :: POSITION OUT OF RANGE\n");    \
                        exit(1);                                               \
                }                                                              \
        }                                                                      \
                                                                               \
        void vector_push_front_##T(struct vector_##T *v, T el)                 \
        {                                                                      \
                vector_insert_##T(v, 0, el);                                   \
        }                                                                      \
                                                                               \
        T vector_front_##T(const struct vector_##T *v)                         \
        {                                                                      \
                return vector_at_##T(v, 0);                                    \
        }                                                                      \
                                                                               \
        long long vector_locate_##T(const struct vector_##T *v, const T el)    \
        {                                                                      \
                long long position = -1;                                       \
                for(size_t i = 0; i < v->size; ++i)                            \
                {                                                              \
                        if(v->equ(&v->data[i], &el))                           \
                        {                                                      \
                                position = i;                                  \
                                break;                                         \
                        }                                                      \
                }                                                              \
                return position;                                               \
        }                                                                      \
                                                                               \
        int vector_find_##T(const struct vector_##T *v, const T el)            \
        {                                                                      \
                return vector_locate_##T(v, el) >= 0;                          \
        }                                                                      \
                                                                               \
        size_t vector_count_##T(const struct vector_##T *v, const T el)        \
        {                                                                      \
                size_t count = 0;                                              \
                for(size_t i = 0; i < v->size; ++i)                            \
                {                                                              \
                        if(v->equ(&v->data[i], &el))                           \
                        {                                                      \
                                count++;                                       \
                        }                                                      \
                }                                                              \
                return count;                                                  \
        }                                                                      \
                                                                               \
        void vector_erase_at_##T(struct vector_##T *v, const size_t at)        \
        {                                                                      \
                if(at < v->size)                                               \
                {                                                              \
                        for(size_t i = at; i < v->size - 1; ++i)               \
                        {                                                      \
                                v->copy(&v->data[i], &v->data[i + 1]);         \
                        }                                                      \
                        --v->size;                                             \
                }                                                              \
        }                                                                      \
                                                                               \
        int vector_erase_##T(struct vector_##T *v, const T el)                 \
        {                                                                      \
                long long position = vector_locate_##T(v, el);                 \
                if(position != -1)                                             \
                {                                                              \
                        vector_erase_at_##T(v, position);                      \
                }                                                              \
                return (int)position;                                          \
        }                                                                      \
                                                                               \
        int vector_erase_all_##T(struct vector_##T *v, const T el)             \
        {                                                                      \
                int erase = 0;                                                 \
                while(vector_erase_##T(v, el) != -1)                           \
                {                                                              \
                        erase = 1;                                             \
                }                                                              \
                return erase;                                                  \
        }                                                                      \
                                                                               \
        int vector_is_sorted_##T(const struct vector_##T *v,                   \
                                 int (*comp)(const void *, const void *))      \
        {                                                                      \
                int sorted = 1;                                                \
                for(size_t i = 0; i < v->size - 1; ++i)                        \
                {                                                              \
                        if(comp(&v->data[i], &v->data[i + 1]))                 \
                        {                                                      \
                                sorted = 0;                                    \
                                break;                                         \
                        }                                                      \
                }                                                              \
                return sorted;                                                 \
        }                                                                      \
                                                                               \
        static inline void vector_memswp_##T(char *i, char *j)                 \
        {                                                                      \
                T tmp;                                                         \
                                                                               \
                memcpy(&tmp, i, sizeof(T));                                    \
                memcpy(i, j, sizeof(T));                                       \
                memcpy(j, &tmp, sizeof(T));                                    \
        }                                                                      \
                                                                               \
        static void vector_qsort_##T(void *array, size_t array_size,           \
                                     int (*comp)(const void *, const void *))  \
        {                                                                      \
                char *i, *j;                                                   \
                size_t thresh = THRESH * sizeof(T);                            \
                char *array_ = (char *)array;                                  \
                char *limit = array_ + array_size * sizeof(T);                 \
                PREPARE_STACK;                                                 \
                                                                               \
                while(1)                                                       \
                {                                                              \
                        if((size_t)(limit - array_) > thresh)                  \
                        {                                                      \
                                i = array_ + sizeof(T);                        \
                                j = limit - sizeof(T);                         \
                                vector_memswp_##T(                             \
                                    ((((size_t)(limit - array_)) /             \
                                      sizeof(T)) /                             \
                                     2) * sizeof(T) +                          \
                                        array_,                                \
                                    array_);                                   \
                                if(comp(i, j) > 0)                             \
                                {                                              \
                                        vector_memswp_##T(i, j);               \
                                }                                              \
                                if(comp(array_, j) > 0)                        \
                                {                                              \
                                        vector_memswp_##T(array_, j);          \
                                }                                              \
                                if(comp(i, array_) > 0)                        \
                                {                                              \
                                        vector_memswp_##T(i, array_);          \
                                }                                              \
                                while(1)                                       \
                                {                                              \
                                        do                                     \
                                        {                                      \
                                                i += sizeof(T);                \
                                        } while(comp(array_, i) > 0);          \
                                        do                                     \
                                        {                                      \
                                                j -= sizeof(T);                \
                                        } while(comp(j, array_) > 0);          \
                                        if(i > j)                              \
                                        {                                      \
                                                break;                         \
                                        }                                      \
                                        vector_memswp_##T(i, j);               \
                                }                                              \
                                vector_memswp_##T(array_, j);                  \
                                if(j - array_ > limit - i)                     \
                                {                                              \
                                        PUSH(array_, j);                       \
                                        array_ = i;                            \
                                }                                              \
                                else                                           \
                                {                                              \
                                        PUSH(i, limit);                        \
                                        limit = j;                             \
                                }                                              \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                for(j = array_, i = j + sizeof(T); i < limit;  \
                                    j = i, i += sizeof(T))                     \
                                {                                              \
                                        for(; comp(j, j + sizeof(T)) > 0;      \
                                            j -= sizeof(T))                    \
                                        {                                      \
                                                vector_memswp_##T(             \
                                                    j, j + sizeof(T));         \
                                                if(j == array_)                \
                                                {                              \
                                                        break;                 \
                                                }                              \
                                        }                                      \
                                }                                              \
                                if(stackptr != stack)                          \
                                {                                              \
                                        POP(array_, limit);                    \
                                }                                              \
                                else                                           \
                                {                                              \
                                        break;                                 \
                                }                                              \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void vector_sort_##T(struct vector_##T *v,                             \
                             int (*comp)(const void *, const void *))          \
        {                                                                      \
                if(comp == NULL)                                               \
                {                                                              \
                        comp = v->comp;                                        \
                }                                                              \
                vector_qsort_##T(v->data, v->size, comp);                      \
        }\
