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

#ifndef VECTOR_KILL_WARNINGS
#warning "VECTOR: define 'VECTOR_KILL_WARNINGS' to remove all warnings"

#ifndef VECTOR_KILL_INIT_WARNING
#warning "VECTOR: using 'void' as default vector element init"
#warning "VECTOR: define 'VECTOR_KILL_INIT_WARNING' to remove warning"
#endif

#ifndef VECTOR_KILL_COPY_WARNING
#warning "VECTOR: using '=' as default vector element copy"
#warning "VECTOR: define 'VECTOR_KILL_COPY_WARNING' to remove warning"
#endif

#ifndef VECTOR_KILL_COMPARE_WARNING
#warning "VECTOR: using 'memcmp' as default vector element compare"
#warning "VECTOR: define 'VECTOR_KILL_COMPARE_WARNING' to remove warning"
#endif

#ifndef VECTOR_KILL_EQUAL_WARNING
#warning "VECTOR: using 'memcmp' as default vector element equal"
#warning "VECTOR: define 'VECTOR_KILL_EQUAL_WARNING' to remove warning"
#endif

#ifndef VECTOR_KILL_FREE_WARNING
#warning "VECTOR: using 'void' as default vector element free"
#warning "VECTOR: define 'VECTOR_KILL_FREE_WARNING' to remove warning"
#endif

#endif

#define INIT_VECTOR(T)                                                         \
                                                                               \
        struct vector_##T                                                      \
        {                                                                      \
                size_t _size;                                                  \
                size_t _max;                                                   \
                T *_data;                                                      \
        };                                                                     \
                                                                               \
        void vector_init_##T(struct vector_##T *v)                             \
        {                                                                      \
                v->_size = v->_max = 0;                                        \
                v->_data = NULL;                                               \
        }                                                                      \
                                                                               \
        static void vector_element_default_init_##T(T *el)                     \
        {                                                                      \
                (void)el;                                                      \
        }                                                                      \
                                                                               \
        void (*vector_element_init_##T)(T *) =                                 \
            vector_element_default_init_##T;                                   \
                                                                               \
        void vector_set_init_##T(void (*init)(T *))                            \
        {                                                                      \
                vector_element_init_##T = init;                                \
        }                                                                      \
                                                                               \
        static void vector_element_default_copy_##T(T *dst, const T *src)      \
        {                                                                      \
                *dst = *src;                                                   \
        }                                                                      \
                                                                               \
        void (*vector_element_copy_##T)(T *, const T *) =                      \
            vector_element_default_copy_##T;                                   \
                                                                               \
        void vector_set_copy_##T(void (*copy)(T *, const T *))                 \
        {                                                                      \
                vector_element_copy_##T = copy;                                \
        }                                                                      \
                                                                               \
        static int vector_element_default_equal_##T(const T *first,            \
                                                    const T *second)           \
        {                                                                      \
                return memcmp(first, second, sizeof(T)) == 0;                  \
        }                                                                      \
                                                                               \
        int (*vector_element_equal_##T)(const T *, const T *) =                \
            vector_element_default_equal_##T;                                  \
                                                                               \
        void vector_set_equal_##T(int (*equal)(const T *, const T *))          \
        {                                                                      \
                vector_element_equal_##T = equal;                              \
        }                                                                      \
                                                                               \
        static int vector_element_default_compare_##T(const void *first,       \
                                                      const void *second)      \
        {                                                                      \
                return memcmp(first, second, sizeof(T)) > 0;                   \
        }                                                                      \
                                                                               \
        int (*vector_element_compare_##T)(const void *, const void *) =        \
            vector_element_default_compare_##T;                                \
                                                                               \
        void vector_set_compare_##T(                                           \
            int (*compare)(const void *, const void *))                        \
        {                                                                      \
                vector_element_compare_##T = compare;                          \
        }                                                                      \
                                                                               \
        static void vector_element_default_free_##T(T *el)                     \
        {                                                                      \
                (void)el;                                                      \
        }                                                                      \
                                                                               \
        void (*vector_element_free_##T)(T *) =                                 \
            vector_element_default_free_##T;                                   \
                                                                               \
        void vector_set_free_##T(void (*free)(T *))                            \
        {                                                                      \
                vector_element_free_##T = free;                                \
        }                                                                      \
                                                                               \
        size_t vector_size_##T(const struct vector_##T *v)                     \
        {                                                                      \
                return v->_size;                                               \
        }                                                                      \
                                                                               \
        void vector_free_##T(struct vector_##T *v)                             \
        {                                                                      \
                if(v->_data)                                                   \
                {                                                              \
                        if(vector_element_free_##T !=                          \
                           vector_element_default_free_##T)                    \
                        {                                                      \
                                for(size_t i = 0; i < v->_size; ++i)           \
                                {                                              \
                                        vector_element_free_##T(&v->_data[i]); \
                                }                                              \
                        }                                                      \
                        free(v->_data);                                        \
                }                                                              \
        }                                                                      \
                                                                               \
        int vector_equal_##T(const struct vector_##T *first,                   \
                             const struct vector_##T *second)                  \
        {                                                                      \
                int equal = (first == second);                                 \
                if(equal == 0 && first->_size == second->_size)                \
                {                                                              \
                        equal = 1;                                             \
                        for(size_t i = 0; i < first->_size; ++i)               \
                        {                                                      \
                                if(!vector_element_equal_##T(                  \
                                       &first->_data[i], &second->_data[i]))   \
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
                        if(vector_element_copy_##T ==                          \
                           vector_element_default_copy_##T)                    \
                        {                                                      \
                                memcpy(dst->_data, src->_data,                 \
                                       src->_size * sizeof(T));                \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                for(size_t i = 0; i < dst->_size; ++i)         \
                                {                                              \
                                        vector_element_copy_##T(               \
                                            &dst->_data[i], &src->_data[i]);   \
                                }                                              \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void vector_from_array_##T(struct vector_##T *v, const T *arr,         \
                                   const size_t size)                          \
        {                                                                      \
                v->_max = v->_size = size;                                     \
                v->_data = (T *)malloc(sizeof(T) * size);                      \
                if(vector_element_copy_##T == vector_element_default_copy_##T) \
                {                                                              \
                        memcpy(v->_data, arr, size * sizeof(T));               \
                }                                                              \
                else                                                           \
                {                                                              \
                        for(size_t i = 0; i < v->_size; ++i)                   \
                        {                                                      \
                                vector_element_copy_##T(&v->_data[i],          \
                                                        &arr[i]);              \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        static void vector_resize_##T(struct vector_##T *v)                    \
        {                                                                      \
                if(v->_size == v->_max)                                        \
                {                                                              \
                        v->_max = (v->_max == 0) ? 1 : v->_max * 2;            \
                        v->_data =                                             \
                            (T *)realloc(v->_data, sizeof(T) * v->_max);       \
                        if(vector_element_init_##T !=                          \
                           vector_element_default_init_##T)                    \
                        {                                                      \
                                for(size_t i = v->_size; i < v->_max; ++i)     \
                                {                                              \
                                        vector_element_init_##T(&v->_data[i]); \
                                }                                              \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void vector_set_##T(struct vector_##T *v, const size_t at, T el)       \
        {                                                                      \
                if(at < v->_size)                                              \
                {                                                              \
                        vector_element_copy_##T(&v->_data[at], &el);           \
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
	                                                                       \
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
                if(v->_size > end)                                             \
                {                                                              \
                        for(size_t i = begin; i < end; ++i)                    \
                        {                                                      \
                                vector_element_copy_##T(&v->_data[i], &el);    \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void vector_push_back_##T(struct vector_##T *v, T el)                  \
        {                                                                      \
                vector_resize_##T(v);                                          \
                vector_element_copy_##T(&v->_data[v->_size], &el);             \
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
                                vector_element_copy_##T(&v->_data[i],          \
                                                        &v->_data[i - 1]);     \
                        }                                                      \
                        vector_element_copy_##T(&v->_data[at], &el);           \
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
                        if(vector_element_equal_##T(&v->_data[i], &el))        \
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
                        if(vector_element_equal_##T(&v->_data[i], &el))        \
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
                                vector_element_copy_##T(&v->_data[i],          \
                                                        &v->_data[i + 1]);     \
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
                        comp = vector_element_compare_##T;                     \
                }                                                              \
                vector_qsort_##T(v->_data, v->_size, comp);                    \
        }
\
