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

#define INIT_STATIC_VECTOR(T, S, N)                                            \
                                                                               \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                T _data[S];                                                    \
        };                                                                     \
                                                                               \
        static void N##_element_default_init(T *el)                            \
        {                                                                      \
                (void)el;                                                      \
        }                                                                      \
                                                                               \
        void (*N##_element_init)(T *) = N##_element_default_init;              \
                                                                               \
        void N##_set_init(void (*init)(T *))                                   \
        {                                                                      \
                N##_element_init = init;                                       \
        }                                                                      \
                                                                               \
        void N##_init(struct N *v)                                             \
        {                                                                      \
                v->_size = 0;                                                  \
                if(N##_element_init != N##_element_default_init)               \
                {                                                              \
                        for(size_t i = 0; i < S; ++i)                          \
                        {                                                      \
                                N##_element_init(&v->_data[i]);                \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        static void N##_element_default_copy(T *dst, const T *src)             \
        {                                                                      \
                *dst = *src;                                                   \
        }                                                                      \
                                                                               \
        void (*N##_element_copy)(T *, const T *) = N##_element_default_copy;   \
                                                                               \
        void N##_set_copy(void (*copy)(T *, const T *))                        \
        {                                                                      \
                N##_element_copy = copy;                                       \
        }                                                                      \
                                                                               \
        static int N##_element_default_equal(const T *first, const T *second)  \
        {                                                                      \
                return memcmp(first, second, sizeof(T)) == 0;                  \
        }                                                                      \
                                                                               \
        int (*N##_element_equal)(const T *, const T *) =                       \
            N##_element_default_equal;                                         \
                                                                               \
        void N##_set_equal(int (*equal)(const T *, const T *))                 \
        {                                                                      \
                N##_element_equal = equal;                                     \
        }                                                                      \
                                                                               \
        static int N##_element_default_compare(const void *first,              \
                                               const void *second)             \
        {                                                                      \
                return memcmp(first, second, sizeof(T)) > 0;                   \
        }                                                                      \
                                                                               \
        int (*N##_element_compare)(const void *, const void *) =               \
            N##_element_default_compare;                                       \
                                                                               \
        void N##_set_compare(int (*compare)(const void *, const void *))       \
        {                                                                      \
                N##_element_compare = compare;                                 \
        }                                                                      \
                                                                               \
        static void N##_element_default_free(T *el)                            \
        {                                                                      \
                (void)el;                                                      \
        }                                                                      \
                                                                               \
        void (*N##_element_free)(T *) = N##_element_default_free;              \
                                                                               \
        void N##_set_free(void (*free)(T *))                                   \
        {                                                                      \
                N##_element_free = free;                                       \
        }                                                                      \
                                                                               \
        size_t N##_size(const struct vector *v)                                \
        {                                                                      \
                return v->_size;                                               \
        }                                                                      \
                                                                               \
        void N##_free(struct vector *v)                                        \
        {                                                                      \
                if(v->_size)                                                   \
                {                                                              \
                        if(N##_element_free != N##_element_default_free)       \
                        {                                                      \
                                for(size_t i = 0; i < v->_size; ++i)           \
                                {                                              \
                                        N##_element_free(&v->_data[i]);        \
                                }                                              \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        int N##_equal(const struct N *first, const struct N *second)           \
        {                                                                      \
                int equal = (first == second);                                 \
                if(equal == 0 && first->_size == second->_size)                \
                {                                                              \
                        equal = 1;                                             \
                        for(size_t i = 0; i < first->_size; ++i)               \
                        {                                                      \
                                if(!N##_element_equal(&first->_data[i],        \
                                                      &second->_data[i]))      \
                                {                                              \
                                        equal = 0;                             \
                                        break;                                 \
                                }                                              \
                        }                                                      \
                }                                                              \
                return equal;                                                  \
        }                                                                      \
                                                                               \
        void N##_copy(struct N *__restrict__ dst,                              \
                      const struct N *__restrict__ src)                        \
        {                                                                      \
                if(src->_size != 0)                                            \
                {                                                              \
                        dst->_size = src->_size;                               \
                        if(N##_element_copy == N##_element_default_copy)       \
                        {                                                      \
                                memcpy(dst->_data, src->_data,                 \
                                       src->_size * sizeof(T));                \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                for(size_t i = 0; i < dst->_size; ++i)         \
                                {                                              \
                                        N##_element_copy(&dst->_data[i],       \
                                                         &src->_data[i]);      \
                                }                                              \
                        }                                                      \
                        if(N##_element_init != N##_element_default_init)       \
                        {                                                      \
                                for(size_t i = dst->_size; i < S; ++i)         \
                                {                                              \
                                        N##_element_init(&dst->_data[i]);      \
                                }                                              \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_set(struct N *v, const size_t at, T el)                       \
        {                                                                      \
                if(at < v->_size)                                              \
                {                                                              \
                        N##_element_copy(&v->_data[at], &el);                  \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_operate(struct N *v, void (*operate)(T *))                    \
        {                                                                      \
                for(size_t i = 0; i < v->_size; ++i)                           \
                {                                                              \
                        operate(&v->_data[i]);                                 \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_operate_to(struct N *v, void (*operate)(T *, void *),         \
                            void *argout)                                      \
        {                                                                      \
                for(size_t i = 0; i < v->_size; ++i)                           \
                {                                                              \
                        operate(&v->_data[i], argout);                         \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_operate_inverted(struct N *v, void (*operate)(T *))           \
        {                                                                      \
                for(size_t i = v->_size; i > 0; --i)                           \
                {                                                              \
                        operate(&v->_data[i - 1]);                             \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_operate_inverted_to(                                          \
            struct N *v, void (*operate)(T *, void *), void *argout)           \
        {                                                                      \
                for(size_t i = v->_size; i > 0; --i)                           \
                {                                                              \
                        operate(&v->_data[i - 1], argout);                     \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_assign(struct N *v, size_t begin, size_t end, T el)           \
        {                                                                      \
                if(v->_size > end)                                             \
                {                                                              \
                        for(size_t i = begin; i < end; ++i)                    \
                        {                                                      \
                                N##_element_copy(&v->_data[i], &el);           \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_push_back(struct N *v, T el)                                  \
        {                                                                      \
                if(v->_size < S)                                               \
                {                                                              \
                        N##_element_copy(&v->_data[v->_size], &el);            \
                        ++v->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        T *N##_pop_back(struct N *v)                                           \
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
        void N##_insert(struct N *v, const size_t at, T el)                    \
        {                                                                      \
                if(at < v->_size)                                              \
                {                                                              \
                        for(size_t i = v->_size; i > at; --i)                  \
                        {                                                      \
                                N##_element_copy(&v->_data[i],                 \
                                                 &v->_data[i - 1]);            \
                        }                                                      \
                        N##_element_copy(&v->_data[at], &el);                  \
                        ++v->_size;                                            \
                }                                                              \
                else                                                           \
                {                                                              \
                        N##_push_back(v, el);                                  \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_push_front(struct N *v, T el)                                 \
        {                                                                      \
                N##_insert(v, 0, el);                                          \
        }                                                                      \
                                                                               \
        T *N##_at(struct N *v, const size_t at)                                \
        {                                                                      \
                T *ret = NULL;                                                 \
                if(at < v->_size)                                              \
                {                                                              \
                        ret = &v->_data[at];                                   \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        T *N##_back(struct N *v)                                               \
        {                                                                      \
                return N##_at(v, v->_size - 1);                                \
        }                                                                      \
                                                                               \
        T *N##_front(struct N *v)                                              \
        {                                                                      \
                return N##_at(v, 0);                                           \
        }                                                                      \
                                                                               \
        ssize_t N##_locate(const struct N *v, const T el)                      \
        {                                                                      \
                ssize_t position = -1;                                         \
                for(size_t i = 0; i < v->_size; ++i)                           \
                {                                                              \
                        if(N##_element_equal(&v->_data[i], &el))               \
                        {                                                      \
                                position = i;                                  \
                                break;                                         \
                        }                                                      \
                }                                                              \
                return position;                                               \
        }                                                                      \
                                                                               \
        int N##_find(const struct N *v, const T el)                            \
        {                                                                      \
                return N##_locate(v, el) >= 0;                                 \
        }                                                                      \
                                                                               \
        size_t N##_count(const struct N *v, const T el)                        \
        {                                                                      \
                size_t count = 0;                                              \
                for(size_t i = 0; i < v->_size; ++i)                           \
                {                                                              \
                        if(N##_element_equal(&v->_data[i], &el))               \
                        {                                                      \
                                count++;                                       \
                        }                                                      \
                }                                                              \
                return count;                                                  \
        }                                                                      \
                                                                               \
        void N##_erase_at(struct N *v, const size_t at)                        \
        {                                                                      \
                if(at < v->_size)                                              \
                {                                                              \
                        if(N##_element_free != N##_element_default_free)       \
                        {                                                      \
                                N##_element_free(&v->_data[at]);               \
                        }                                                      \
                                                                               \
                        for(size_t i = at; i < v->_size - 1; ++i)              \
                        {                                                      \
                                N##_element_copy(&v->_data[i],                 \
                                                 &v->_data[i + 1]);            \
                        }                                                      \
                        --v->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        int N##_erase(struct N *v, const T el)                                 \
        {                                                                      \
                ssize_t position = N##_locate(v, el);                          \
                if(position != -1)                                             \
                {                                                              \
                        N##_erase_at(v, position);                             \
                }                                                              \
                return position != -1;                                         \
        }                                                                      \
                                                                               \
        int N##_erase_all(struct N *v, const T el)                             \
        {                                                                      \
                int erase = 0;                                                 \
                while(N##_erase(v, el) != 0)                                   \
                {                                                              \
                        erase = 1;                                             \
                }                                                              \
                return erase;                                                  \
        }                                                                      \
                                                                               \
        int N##_is_sorted(const struct N *v,                                   \
                          int (*comp)(const void *, const void *))             \
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
        static inline void N##_memswp(char *i, char *j)                        \
        {                                                                      \
                T tmp;                                                         \
                                                                               \
                memcpy(&tmp, i, sizeof(T));                                    \
                memcpy(i, j, sizeof(T));                                       \
                memcpy(j, &tmp, sizeof(T));                                    \
        }                                                                      \
                                                                               \
        static void N##_qsort(void *array, size_t array_size,                  \
                              int (*comp)(const void *, const void *))         \
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
                                N##_memswp(((((size_t)(limit - array_)) /      \
                                             sizeof(T)) /                      \
                                            2) * sizeof(T) +                   \
                                               array_,                         \
                                           array_);                            \
                                if(comp(i, j) > 0)                             \
                                {                                              \
                                        N##_memswp(i, j);                      \
                                }                                              \
                                if(comp(array_, j) > 0)                        \
                                {                                              \
                                        N##_memswp(array_, j);                 \
                                }                                              \
                                if(comp(i, array_) > 0)                        \
                                {                                              \
                                        N##_memswp(i, array_);                 \
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
                                        N##_memswp(i, j);                      \
                                }                                              \
                                N##_memswp(array_, j);                         \
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
                                                N##_memswp(j, j + sizeof(T));  \
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
        void N##_sort(struct N *v, int (*comp)(const void *, const void *))    \
        {                                                                      \
                if(comp == NULL)                                               \
                {                                                              \
                        comp = N##_element_compare;                            \
                }                                                              \
                N##_qsort(v->_data, v->_size, comp);                           \
        }
