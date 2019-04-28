#pragma once

#include "sgc_basic_types.h"
#include "sgc_utils.h"

#define SGC_INIT_STATIC_FUNCTIONS_STATIC_QUEUE(T, S, N)                        \
        static void N##_move(size_t *flag);

#define SGC_INIT_HEADERS_STATIC_QUEUE(T, S, N)                                 \
                                                                               \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                size_t _back;                                                  \
                size_t _front;                                                 \
                size_t _shared;                                                \
                T _data[S];                                                    \
        };                                                                     \
                                                                               \
        typedef struct N N;                                                    \
        typedef T N##_type;                                                    \
                                                                               \
        size_t N##_max(void);                                                  \
        void N##_set_share(N *q, int is_shared);                               \
        size_t N##_size(const struct N *const q);                              \
        void N##_init(struct N *q);                                            \
        void N##_free(struct N *q);                                            \
        int N##_equal(const struct N *const first,                             \
                      const struct N *const second);                           \
        void N##_copy(struct N *__restrict__ dst,                              \
                      const struct N *__restrict__ const src);                 \
        void N##_push(struct N *q, T el);                                      \
        T *N##_front(struct N *q);                                             \
        void N##_set_front(struct N *q, T new_el);                             \
        T *N##_back(struct N *q);                                              \
        void N##_set_back(struct N *q, T new_el);                              \
        void N##_pop(struct N *q);                                             \
        int N##_empty(const struct N *const q);

#define SGC_INIT_STATIC_QUEUE(T, S, N)                                         \
        SGC_INIT_HEADERS_STATIC_QUEUE(T, S, N);                                \
        SGC_INIT_STATIC_FUNCTIONS_STATIC_QUEUE(T, S, N);                       \
                                                                               \
        size_t N##_max(void)                                                   \
        {                                                                      \
                return S;                                                      \
        }                                                                      \
                                                                               \
        /* ================= */                                                \
        /*  QUEUE FUNCTIONS  */                                                \
        /* ================= */                                                \
                                                                               \
        void N##_set_share(N *q, int is_shared)                                \
        {                                                                      \
                q->_shared = is_shared;                                        \
        }                                                                      \
                                                                               \
        size_t N##_size(const struct N *const q)                               \
        {                                                                      \
                return q->_size;                                               \
        }                                                                      \
                                                                               \
        void N##_init(struct N *q)                                             \
        {                                                                      \
                q->_size = q->_front = q->_back = 0;                           \
                q->_shared = 0;                                                \
        }                                                                      \
                                                                               \
        static void N##_move(size_t *flag)                                     \
        {                                                                      \
                if(*flag + 1 == S)                                             \
                {                                                              \
                        *flag = 0;                                             \
                }                                                              \
                else                                                           \
                {                                                              \
                        ++*flag;                                               \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_free(struct N *q)                                             \
        {                                                                      \
                if(q->_data)                                                   \
                {                                                              \
                        if(!q->_shared)                                        \
                        {                                                      \
                                size_t i;                                      \
                                for(i = q->_front; i != q->_back;)             \
                                {                                              \
                                        T##_free(&q->_data[i]);                \
                                        N##_move(&i);                          \
                                }                                              \
                                T##_free(&q->_data[i]);                        \
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
                        size_t i = first->_front;                              \
                        size_t j = second->_front;                             \
                        for(size_t k = 0; k < first->_size; ++k)               \
                        {                                                      \
                                if(!T##_equal(&first->_data[i],                \
                                              &second->_data[j]))              \
                                {                                              \
                                        equal = 0;                             \
                                        break;                                 \
                                }                                              \
                                N##_move(&i);                                  \
                                N##_move(&j);                                  \
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
                        dst->_shared = src->_shared;                           \
                        if(dst->_shared)                                       \
                        {                                                      \
                                if(src->_front < src->_back)                   \
                                {                                              \
                                        memcpy(dst->_data,                     \
                                               src->_data + src->_front,       \
                                               src->_size * sizeof(T));        \
                                }                                              \
                                else                                           \
                                {                                              \
                                        size_t first_part = src->_back;        \
                                        size_t second_part = S - src->_front;  \
                                        memcpy(dst->_data,                     \
                                               src->_data + src->_front,       \
                                               second_part * sizeof(T));       \
                                        memcpy(dst->_data + second_part,       \
                                               src->_data,                     \
                                               (1 + first_part) * sizeof(T));  \
                                }                                              \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                size_t i = src->_front;                        \
                                for(size_t j = 0; j < src->_size; ++j)         \
                                {                                              \
                                        /* memcpy would be better */           \
                                        SGC_COPY(T##_copy, dst->_data[j],      \
                                                 src->_data[i], dst->_shared); \
                                        N##_move(&i);                          \
                                }                                              \
                        }                                                      \
                }                                                              \
                                                                               \
                dst->_size = src->_size;                                       \
                dst->_back = src->_size - 1;                                   \
                dst->_front = 0;                                               \
        }                                                                      \
                                                                               \
        void N##_push(struct N *q, T el)                                       \
        {                                                                      \
                if(q->_size < S)                                               \
                {                                                              \
                        N##_move(&q->_back);                                   \
                        if(q->_size == 0)                                      \
                        {                                                      \
                                --q->_back;                                    \
                        }                                                      \
                        SGC_COPY(T##_copy, q->_data[q->_back], el,             \
                                 q->_shared);                                  \
                        ++q->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        T *N##_front(struct N *q)                                              \
        {                                                                      \
                T *ret = NULL;                                                 \
                if(q->_size)                                                   \
                {                                                              \
                        ret = &q->_data[q->_front];                            \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        void N##_set_front(struct N *q, T new_el)                              \
        {                                                                      \
                if(q->_size)                                                   \
                {                                                              \
                        SGC_REPLACE(T##_copy, T##_free, q->_data[q->_front],   \
                                    new_el, q->_shared);                       \
                }                                                              \
        }                                                                      \
                                                                               \
        T *N##_back(struct N *q)                                               \
        {                                                                      \
                T *ret = NULL;                                                 \
                if(q->_size)                                                   \
                {                                                              \
                        ret = &q->_data[q->_back];                             \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        void N##_set_back(struct N *q, T new_el)                               \
        {                                                                      \
                if(q->_size)                                                   \
                {                                                              \
                        SGC_REPLACE(T##_copy, T##_free, q->_data[q->_back],    \
                                    new_el, q->_shared);                       \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_pop(struct N *q)                                              \
        {                                                                      \
                if(q->_size)                                                   \
                {                                                              \
                        T *el = &q->_data[q->_front];                          \
                        if(!q->_shared)                                        \
                        {                                                      \
                                T##_free(el);                                  \
                        }                                                      \
                        N##_move(&q->_front);                                  \
                        --q->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        int N##_empty(const struct N *const q)                                 \
        {                                                                      \
                return q->_size == 0;                                          \
        }
