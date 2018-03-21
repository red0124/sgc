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
        static void vector_set_methods_##T(struct vector_##T *v);              \
                                                                               \
        static void vector_flat_copy_##T(T *dst, const T *src)                 \
        {                                                                      \
                *dst = *src;                                                   \
        }                                                                      \
                                                                               \
        static int vector_flat_equ_##T(const T *first, const T *second)        \
        {                                                                      \
                return memcmp(first, second, sizeof(T)) == 0;                  \
        }                                                                      \
                                                                               \
        static int vector_flat_comp_##T(const void *first, const void *second) \
        {                                                                      \
                return memcmp(first, second, sizeof(T)) > 0;                   \
        }                                                                      \
                                                                               \
        size_t vector_size_##T(const struct vector_##T *v)                     \
        {                                                                      \
                return v->_size;                                               \
        }                                                                      \
                                                                               \
        void vector_set_copy_##T(struct vector_##T *v,                         \
                                 void (*copy)(T *, const T *))                 \
        {                                                                      \
                v->_copy = copy;                                               \
        }                                                                      \
                                                                               \
        void vector_set_free_##T(struct vector_##T *v, void (*free)(T *))      \
        {                                                                      \
                v->_free = free;                                               \
        }                                                                      \
                                                                               \
        void vector_set_comp_##T(struct vector_##T *v,                         \
                                 int (*comp)(const void *, const void *))      \
        {                                                                      \
                v->_comp = comp;                                               \
        }                                                                      \
                                                                               \
        void vector_set_equ_##T(struct vector_##T *v,                          \
                                int (*equ)(const T *, const T *))              \
        {                                                                      \
                v->_equ = equ;                                                 \
        }                                                                      \
                                                                               \
        void vector_free_##T(struct vector_##T *v)                             \
        {                                                                      \
                if(v->_data)                                                   \
                {                                                              \
                        if(v->_free)                                           \
                        {                                                      \
                                for(size_t i = 0; i < v->_size; ++i)           \
                                {                                              \
                                        v->_free(&v->_data[i]);                \
                                }                                              \
                        }                                                      \
                        free(v->_data);                                        \
                }                                                              \
        }                                                                      \
                                                                               \
        int vector_equ_##T(const struct vector_##T *first,                     \
                           const struct vector_##T *second)                    \
        {                                                                      \
                int equal = (first == second);                                 \
                if(equal == 0 && first->_size == second->_size)                \
                {                                                              \
                        equal = 1;                                             \
                        for(size_t i = 0; i < first->_size; ++i)               \
                        {                                                      \
                                if(!first->_equ(&first->_data[i],              \
                                                &second->_data[i]))            \
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
                if(src->_size != 0)                                            \
                {                                                              \
                        dst->_size = src->_size;                               \
                        dst->_max = src->_size;                                \
                        dst->_data = (T *)malloc(dst->_max * sizeof(T));       \
                        for(size_t i = 0; i < dst->_size; ++i)                 \
                        {                                                      \
                                src->_copy(&dst->_data[i], &src->_data[i]);    \
                        }                                                      \
                }                                                              \
                dst->_copy = src->_copy;                                       \
                dst->_free = src->_free;                                       \
                dst->_comp = src->_comp;                                       \
                dst->_equ = src->_equ;                                         \
                vector_set_methods_##T(dst);                                   \
        }                                                                      \
                                                                               \
        void vector_from_array_##T(struct vector_##T *v, const T *arr,         \
                                   const size_t size)                          \
        {                                                                      \
                v->_max = v->_size = size;                                     \
                v->_data = (T *)malloc(sizeof(T) * size);                      \
                for(size_t i = 0; i < v->_size; ++i)                           \
                {                                                              \
                        v->_copy(&v->_data[i], &arr[i]);                       \
                }                                                              \
        }                                                                      \
                                                                               \
        static void vector_resize_##T(struct vector_##T *v)                    \
        {                                                                      \
                if(v->_size == v->_max)                                        \
                {                                                              \
                        if(v->_max == 0)                                       \
                        {                                                      \
                                v->_max = 1;                                   \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                v->_max *= 2;                                  \
                        }                                                      \
                        v->_data =                                             \
                            (T *)realloc(v->_data, sizeof(T) * v->_max);       \
                }                                                              \
        }                                                                      \
                                                                               \
        void vector_set_##T(struct vector_##T *v, const size_t at, T el)       \
        {                                                                      \
                if(at < v->_size)                                              \
                {                                                              \
                        v->_copy(&v->_data[at], &el);                          \
                }                                                              \
        }                                                                      \
                                                                               \
        void vector_operate_##T(struct vector_##T *v, void (*operate)(T *))    \
        {                                                                      \
                for(size_t i = 0; i < v->_size; ++i)                           \
                {                                                              \
                        operate(&v->_data[i]);                                 \
                }                                                              \
        }                                                                      \
        void vector_operate_to_##T(struct vector_##T *v,                       \
                                   void (*operate)(T *, void *), void *argout) \
        {                                                                      \
                for(size_t i = 0; i < v->_size; ++i)                           \
                {                                                              \
                        operate(&v->_data[i], argout);                         \
                }                                                              \
        }                                                                      \
                                                                               \
        void vector_operate_inverted_##T(struct vector_##T *v,                 \
                                         void (*operate)(T *))                 \
        {                                                                      \
                for(size_t i = v->_size; i > 0; --i)                           \
                {                                                              \
                        operate(&v->_data[i - 1]);                             \
                }                                                              \
        }                                                                      \
                                                                               \
        void vector_assign_##T(struct vector_##T *v, size_t begin, size_t end, \
                               T el)                                           \
        {                                                                      \
                if(v->_size > end && end > begin)                              \
                {                                                              \
                        for(size_t i = begin; i < end; ++i)                    \
                        {                                                      \
                                v->_copy(&v->_data[i], &el);                   \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void vector_push_back_##T(struct vector_##T *v, T el)                  \
        {                                                                      \
                vector_resize_##T(v);                                          \
                v->_copy(&v->_data[v->_size], &el);                            \
                ++v->_size;                                                    \
        }                                                                      \
                                                                               \
        T *vector_pop_back_##T(struct vector_##T *v)                           \
        {                                                                      \
                T *ret = NULL;                                                 \
                if(v->_size)                                                   \
                {                                                              \
                        --v->_size;                                            \
                        ret = &v->_data[v->_size];                             \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        void vector_insert_##T(struct vector_##T *v, const size_t at, T el)    \
        {                                                                      \
                if(at < v->_size)                                              \
                {                                                              \
                        vector_resize_##T(v);                                  \
                        for(size_t i = v->_size; i > at; --i)                  \
                        {                                                      \
                                v->_copy(&v->_data[i], &v->_data[i - 1]);      \
                        }                                                      \
                        v->_copy(&v->_data[at], &el);                          \
                        ++v->_size;                                            \
                }                                                              \
                else                                                           \
                {                                                              \
                        vector_push_back_##T(v, el);                           \
                }                                                              \
        }                                                                      \
                                                                               \
        void vector_push_front_##T(struct vector_##T *v, T el)                 \
        {                                                                      \
                vector_insert_##T(v, 0, el);                                   \
        }                                                                      \
                                                                               \
        T *vector_at_##T(struct vector_##T *v, const size_t at)                \
        {                                                                      \
                T *ret = NULL;                                                 \
                if(at < v->_size)                                              \
                {                                                              \
                        ret = &v->_data[at];                                   \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        T *vector_back_##T(struct vector_##T *v)                               \
        {                                                                      \
                return vector_at_##T(v, v->_size - 1);                         \
        }                                                                      \
                                                                               \
        T *vector_front_##T(struct vector_##T *v)                              \
        {                                                                      \
                return vector_at_##T(v, 0);                                    \
        }                                                                      \
                                                                               \
        ssize_t vector_locate_##T(const struct vector_##T *v, const T el)      \
        {                                                                      \
                ssize_t position = -1;                                         \
                for(size_t i = 0; i < v->_size; ++i)                           \
                {                                                              \
                        if(v->_equ(&v->_data[i], &el))                         \
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
                for(size_t i = 0; i < v->_size; ++i)                           \
                {                                                              \
                        if(v->_equ(&v->_data[i], &el))                         \
                        {                                                      \
                                count++;                                       \
                        }                                                      \
                }                                                              \
                return count;                                                  \
        }                                                                      \
                                                                               \
        void vector_erase_at_##T(struct vector_##T *v, const size_t at)        \
        {                                                                      \
                if(at < v->_size)                                              \
                {                                                              \
                        for(size_t i = at; i < v->_size - 1; ++i)              \
                        {                                                      \
                                v->_copy(&v->_data[i], &v->_data[i + 1]);      \
                        }                                                      \
                        --v->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        int vector_erase_##T(struct vector_##T *v, const T el)                 \
        {                                                                      \
                ssize_t position = vector_locate_##T(v, el);                   \
                if(position != -1)                                             \
                {                                                              \
                        vector_erase_at_##T(v, position);                      \
                }                                                              \
                return position != -1;                                         \
        }                                                                      \
                                                                               \
        int vector_erase_all_##T(struct vector_##T *v, const T el)             \
        {                                                                      \
                int erase = 0;                                                 \
                while(vector_erase_##T(v, el) != 0)                            \
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
                for(size_t i = 0; i < v->_size - 1; ++i)                       \
                {                                                              \
                        if(comp(&v->_data[i], &v->_data[i + 1]))               \
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
                        comp = v->_comp;                                       \
                }                                                              \
                vector_qsort_##T(v->_data, v->_size, comp);                    \
        }                                                                      \
                                                                               \
        struct vector_##T vector_new_##T()                                     \
        {                                                                      \
                struct vector_##T v = {._size = 0,                             \
                                       ._max = 0,                              \
                                       ._data = NULL,                          \
                                       ._copy = vector_flat_copy_##T,          \
                                       ._free = NULL,                          \
                                       ._comp = vector_flat_comp_##T,          \
                                       ._equ = vector_flat_equ_##T};           \
                vector_set_methods_##T(&v);                                    \
                return v;                                                      \
        }                                                                      \
                                                                               \
        void vector_init_##T(struct vector_##T *v)                             \
        {                                                                      \
                v->_size = 0;                                                  \
                v->_max = 0;                                                   \
                v->_data = NULL;                                               \
                v->_copy = vector_flat_copy_##T;                               \
                v->_free = NULL;                                               \
                v->_comp = vector_flat_comp_##T;                               \
                v->_equ = vector_flat_equ_##T;                                 \
                vector_set_methods_##T(v);                                     \
        }                                                                      \
                                                                               \
        static void vector_set_methods_##T(struct vector_##T *v)               \
        {                                                                      \
                v->size = vector_size_##T;                                     \
                v->set_copy = vector_set_copy_##T;                             \
                v->set_free = vector_set_free_##T;                             \
                v->set_comp = vector_set_comp_##T;                             \
                v->set_equ = vector_set_equ_##T;                               \
                v->free = vector_free_##T;                                     \
                v->equ = vector_equ_##T;                                       \
                v->copy = vector_copy_##T;                                     \
                v->from_array = vector_from_array_##T;                         \
                v->set = vector_set_##T;                                       \
                v->operate = vector_operate_##T;                               \
                v->operate_to = vector_operate_to_##T;                         \
                v->operate_inverted = vector_operate_inverted_##T;             \
                v->assign = vector_assign_##T;                                 \
                v->push_back = vector_push_back_##T;                           \
                v->push_front = vector_push_front_##T;                         \
                v->pop_back = vector_pop_back_##T;                             \
                v->insert = vector_insert_##T;                                 \
                v->at = vector_at_##T;                                         \
                v->back = vector_back_##T;                                     \
                v->front = vector_front_##T;                                   \
                v->locate = vector_locate_##T;                                 \
                v->find = vector_find_##T;                                     \
                v->count = vector_count_##T;                                   \
                v->erase_at = vector_erase_at_##T;                             \
                v->erase = vector_erase_##T;                                   \
                v->erase_all = vector_erase_all_##T;                           \
                v->is_sorted = vector_is_sorted_##T;                           \
                v->sort = vector_sort_##T;                                     \
                v->new = vector_new_##T;                                       \
                v->init = vector_init_##T;                                     \
        }\
