#pragma once

#include "sgc_basic_types.h"
#include "sgc_utils.h"

#define SGC_INIT_STATIC_FUNCTIONS_STATIC_PRIORITY_QUEUE(T, S, N)               \
        static void N##_memswp(T *i, T *j);                                    \
        static void N##_fix_insert(struct N *p);                               \
        static void N##_fix_erase(struct N *p);

#define SGC_INIT_HEADERS_STATIC_PRIORITY_QUEUE(T, S, N)                        \
                                                                               \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                size_t _shared;                                                \
                T _data[S];                                                    \
        };                                                                     \
                                                                               \
        typedef struct N N;                                                    \
        typedef T N##_type;                                                    \
                                                                               \
        size_t N##_max(void);                                                  \
        void N##_set_share(N *p, int is_shared);                               \
        void N##_init(struct N *p);                                            \
        size_t N##_size(const struct N *p);                                    \
        void N##_free(struct N *p);                                            \
        int N##_equal(const struct N *const first,                             \
                      const struct N *const second);                           \
        void N##_copy(struct N *__restrict__ dst,                              \
                      const struct N *__restrict__ const src);                 \
        void N##_push(struct N *p, T el);                                      \
        void N##_pop(struct N *p);                                             \
        T *N##_top(struct N *p);                                               \
        int N##_empty(const struct N *const d);                                \
        T *N##_array(struct N *d);                                             \
        void N##_from_array(struct N *p, const T *const arr, const size_t size);

#define SGC_INIT_STATIC_PRIORITY_QUEUE(T, S, N)                                \
        SGC_INIT_HEADERS_STATIC_PRIORITY_QUEUE(T, S, N)                        \
        SGC_INIT_STATIC_FUNCTIONS_STATIC_PRIORITY_QUEUE(T, S, N)               \
                                                                               \
        size_t N##_max(void)                                                   \
        {                                                                      \
                return S;                                                      \
        }                                                                      \
                                                                               \
        /* ==========================*/                                        \
        /*  PRIOITY QUEUE FUNCTIONS  */                                        \
        /* ==========================*/                                        \
                                                                               \
        void N##_set_share(N *p, int is_shared)                                \
        {                                                                      \
                p->_shared = is_shared;                                        \
        }                                                                      \
                                                                               \
        void N##_init(struct N *p)                                             \
        {                                                                      \
                p->_size = 0;                                                  \
                p->_shared = 0;                                                \
        }                                                                      \
                                                                               \
        size_t N##_size(const struct N *p)                                     \
        {                                                                      \
                return p->_size;                                               \
        }                                                                      \
                                                                               \
        void N##_free(struct N *p)                                             \
        {                                                                      \
                if(p->_data)                                                   \
                {                                                              \
                        if(!p->_shared)                                        \
                        {                                                      \
                                for(size_t i = 0; i < p->_size; ++i)           \
                                {                                              \
                                        T##_free(&p->_data[i]);                \
                                }                                              \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        int N##_equal(const struct N *const first,                             \
                      const struct N *const second)                            \
        {                                                                      \
                int equal = (first == second);                                 \
                if(equal == 0 && first->_size == second->_size)                \
                {                                                              \
                        equal = 1;                                             \
                        for(size_t i = 0; i < first->_size; ++i)               \
                        {                                                      \
                                if(!T##_equal(&first->_data[i],                \
                                              &second->_data[i]))              \
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
                      const struct N *__restrict__ const src)                  \
        {                                                                      \
                if(src->_size != 0)                                            \
                {                                                              \
                        dst->_size = src->_size;                               \
                        dst->_shared = src->_shared;                           \
                        if(src->_shared)                                       \
                        {                                                      \
                                memcpy(dst->_data, src->_data,                 \
                                       src->_size * sizeof(T));                \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                for(size_t i = 0; i < dst->_size; ++i)         \
                                {                                              \
                                        T##_copy(&dst->_data[i],               \
                                                 &src->_data[i]);              \
                                }                                              \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        static void N##_memswp(T *i, T *j)                                     \
        {                                                                      \
                char *tmp[sizeof(T)];                                          \
                                                                               \
                memcpy(tmp, i, sizeof(T));                                     \
                memcpy(i, j, sizeof(T));                                       \
                memcpy(j, tmp, sizeof(T));                                     \
        }                                                                      \
                                                                               \
        static void N##_fix_insert(struct N *p)                                \
        {                                                                      \
                size_t curr = p->_size;                                        \
                while(curr)                                                    \
                {                                                              \
                        size_t parent = (curr - 1) / 2;                        \
                        if(T##_compare(&p->_data[parent], &p->_data[curr]) <   \
                           0)                                                  \
                        {                                                      \
                                N##_memswp(&p->_data[parent],                  \
                                           &p->_data[curr]);                   \
                                curr = parent;                                 \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                break;                                         \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_push(struct N *p, T el)                                       \
        {                                                                      \
                if(p->_size != S)                                              \
                {                                                              \
                        if(!p->_shared)                                        \
                        {                                                      \
                                T##_copy(&p->_data[p->_size], &el);            \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                p->_data[p->_size] = el;                       \
                        }                                                      \
                        N##_fix_insert(p);                                     \
                        ++p->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        static void N##_fix_erase(struct N *p)                                 \
        {                                                                      \
                size_t curr = 0;                                               \
                while((curr + 1) * 2 <= p->_size)                              \
                {                                                              \
                        size_t right = (curr + 1) * 2;                         \
                        size_t left = right - 1;                               \
                        size_t tmp = right;                                    \
                        if(right == p->_size ||                                \
                           T##_compare(&p->_data[left], &p->_data[right]) > 0) \
                        {                                                      \
                                tmp = left;                                    \
                        }                                                      \
                        if(T##_compare(&p->_data[tmp], &p->_data[curr]) > 0)   \
                        {                                                      \
                                N##_memswp(&p->_data[curr], &p->_data[tmp]);   \
                                curr = tmp;                                    \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                break;                                         \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_pop(struct N *p)                                              \
        {                                                                      \
                if(p->_size)                                                   \
                {                                                              \
                        N##_memswp(&p->_data[0], &p->_data[--p->_size]);       \
                        if(!p->_shared)                                        \
                        {                                                      \
                                T##_free(&p->_data[p->_size]);                 \
                        }                                                      \
                        N##_fix_erase(p);                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        T *N##_top(struct N *p)                                                \
        {                                                                      \
                T *ret = NULL;                                                 \
                if(p->_size)                                                   \
                {                                                              \
                        ret = &p->_data[0];                                    \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        int N##_empty(const struct N *const d)                                 \
        {                                                                      \
                return d->_size == 0;                                          \
        }                                                                      \
                                                                               \
        T *N##_array(struct N *d)                                              \
        {                                                                      \
                T *ret = NULL;                                                 \
                if(d->_size)                                                   \
                {                                                              \
                        ret = d->_data;                                        \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        void N##_from_array(struct N *p, const T *const arr,                   \
                            const size_t size)                                 \
        {                                                                      \
                if(size)                                                       \
                {                                                              \
                        p->_size = 0;                                          \
                        for(size_t i = 0; i < size; ++i)                       \
                        {                                                      \
                                N##_push(p, arr[i]);                           \
                        }                                                      \
                }                                                              \
                else                                                           \
                {                                                              \
                        p->_size = 0;                                          \
                }                                                              \
        }
