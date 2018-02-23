#pragma once

#include <stdlib.h>
#include <string.h>

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
        static void flat_free_##T(T *data)                                     \
        {                                                                      \
                (void)data;                                                    \
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
                    0, 0, NULL, flat_copy_##T, flat_free_##T, NULL, NULL};     \
                return v;                                                      \
        }                                                                      \
                                                                               \
        void vector_set_copy_##T(struct vector_##T *v,                         \
                                 void (*copy)(T *, const T *))                 \
        {                                                                      \
                v->copy = copy;                                                \
        }                                                                      \
                                                                               \
        void vector_set_free_##T(struct vector_##T *v, void (*free)(T *))      \
        {                                                                      \
                v->free = free;                                                \
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
                v->free = flat_free_##T;                                       \
                v->comp = NULL;                                                \
                v->equ = NULL;                                                 \
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
                if(equal == 0 && first->equ == NULL)                           \
                {                                                              \
                        fprintf(stderr, "VECTOR WARNING :: UNDEFINED "         \
                                        "EQUALITY CONDITION\n");               \
                        return 0;                                              \
                }                                                              \
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
        void vector_operate_##T(struct vector_##T *v, void (*operate)(void *)) \
        {                                                                      \
                for(size_t i = 0; i < v->size; ++i)                            \
                {                                                              \
                        operate(&v->data[i]);                                  \
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
        T vector_back_##T(struct vector_##T *v)                                \
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
        T vector_at_##T(struct vector_##T *v, const size_t at)                 \
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
        T vector_front_##T(struct vector_##T *v)                               \
        {                                                                      \
                return vector_at_##T(v, 0);                                    \
        }                                                                      \
                                                                               \
        long long vector_find_##T(struct vector_##T *v, const T el)            \
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
                long long position = vector_find_##T(v, el);                   \
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
        int vector_is_sorted_##T(struct vector_##T *v,                         \
                                 int (*comp)(const void *, const void *))      \
        {                                                                      \
                if(comp == NULL)                                               \
                {                                                              \
                        comp = v->comp;                                        \
                }                                                              \
                if(comp == NULL)                                               \
                {                                                              \
                        fprintf(                                               \
                            stderr,                                            \
                            "VECTOR WARNING :: NO SORT CONDITION GIVEN\n");    \
                        return 0;                                              \
                }                                                              \
                int sorted = 1;                                                \
                for(size_t i = 0; i < v->size - 1; ++i)                        \
                {                                                              \
                        if(!comp(&v->data[i], &v->data[i + 1]))                \
                        {                                                      \
                                sorted = 0;                                    \
                                break;                                         \
                        }                                                      \
                }                                                              \
                return sorted;                                                 \
        }                                                                      \
                                                                               \
        void vector_sort_##T(struct vector_##T *v,                             \
                             int (*comp)(const void *, const void *))          \
        {                                                                      \
                qsort(v->data, v->size, sizeof(T), comp);                      \
        }                                                                      \
                                                                               \
        void swap_##T(T *a, T *b)                                              \
        {                                                                      \
                T tmp = *a;                                                    \
                *a = *b;                                                       \
                *b = tmp;                                                      \
        }                                                                      \
                                                                               \
        void vector_quick_sort_interval_##T(struct vector_##T *v,              \
                                            int (*comp)(const T, const T),     \
                                            int begin, int end)                \
        {                                                                      \
                int p = begin;                                                 \
                int l = begin;                                                 \
                int r = end;                                                   \
                                                                               \
                while(l < r)                                                   \
                {                                                              \
                        while(!comp(v->data[p], v->data[l]) && l < end)        \
                        {                                                      \
                                ++l;                                           \
                        }                                                      \
                                                                               \
                        while(comp(v->data[p], v->data[r]))                    \
                        {                                                      \
                                --r;                                           \
                        }                                                      \
                                                                               \
                        if(l < r)                                              \
                        {                                                      \
                                swap_##T(&v->data[l], &v->data[r]);            \
                        }                                                      \
                }                                                              \
                                                                               \
                swap_##T(&v->data[p], &v->data[r]);                            \
                                                                               \
                vector_quick_sort_interval_##T(v, comp, begin, r - 1);         \
                vector_quick_sort_interval_##T(v, comp, r + 1, end);           \
        }                                                                      \
                                                                               \
        void vector_qsort_##T(struct vector_##T *v,                            \
                              int (*comp)(const T, const T))                   \
        {                                                                      \
                vector_quick_sort_interval_##T(v, comp, 0, v->size);           \
        }\
