#pragma once

#include "inc/sgc_basic_types.h"
#include "inc/sgc_utils.h"

#define SGC_INIT_HEADERS_STATIC_STACK(T, S, N)                                 \
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
        void N##_set_share(N *s, int is_shared);                               \
        void N##_init(struct N *s);                                            \
        size_t N##_size(const struct N *s);                                    \
        void N##_free(struct N *s);                                            \
        int N##_equal(const struct N *first, const struct N *second);          \
        void N##_copy(struct N *__restrict__ dst,                              \
                      const struct N *__restrict__ const src);                 \
        void N##_push(struct N *s, T el);                                      \
        void N##_pop(struct N *s);                                             \
        T *N##_top(struct N *s);                                               \
        void N##_set_top(struct N *s, T new_el);                               \
        int N##_empty(struct N *s);

#define SGC_INIT_STATIC_STACK(T, S, N)                                         \
        SGC_INIT_HEADERS_STATIC_STACK(T, S, N);                                \
                                                                               \
        size_t N##_max(void)                                                   \
        {                                                                      \
                return S;                                                      \
        }                                                                      \
                                                                               \
        /* ======================== */                                         \
        /*  STATIC STACK FUNCTIONS  */                                         \
        /* ======================== */                                         \
                                                                               \
        void N##_set_share(N *s, int is_shared)                                \
        {                                                                      \
                s->_shared = is_shared;                                        \
        }                                                                      \
                                                                               \
        void N##_init(struct N *s)                                             \
        {                                                                      \
                s->_size = 0;                                                  \
                s->_shared = 0;                                                \
        }                                                                      \
                                                                               \
        size_t N##_size(const struct N *s)                                     \
        {                                                                      \
                return s->_size;                                               \
        }                                                                      \
                                                                               \
        void N##_free(struct N *s)                                             \
        {                                                                      \
                if(s->_size)                                                   \
                {                                                              \
                        if(!s->_shared)                                        \
                        {                                                      \
                                for(size_t i = 0; i < s->_size; ++i)           \
                                {                                              \
                                        T##_free(&s->_data[i]);                \
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
                        if(dst->_shared)                                       \
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
        void N##_push(struct N *s, T el)                                       \
        {                                                                      \
                if(s->_size < S)                                               \
                {                                                              \
                        SGC_COPY(T##_copy, s->_data[s->_size], el,             \
                                 s->_shared);                                  \
                        ++s->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_pop(struct N *s)                                              \
        {                                                                      \
                if(s->_size)                                                   \
                {                                                              \
                        T *el = &s->_data[s->_size - 1];                       \
                        if(!s->_shared)                                        \
                        {                                                      \
                                T##_free(el);                                  \
                        }                                                      \
                        --s->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        T *N##_top(struct N *s)                                                \
        {                                                                      \
                T *ret = NULL;                                                 \
                if(s->_size)                                                   \
                {                                                              \
                        ret = &s->_data[s->_size - 1];                         \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        void N##_set_top(struct N *s, T new_el)                                \
        {                                                                      \
                if(s->_size)                                                   \
                {                                                              \
                        SGC_REPLACE(T##_copy, T##_free,                        \
                                    s->_data[s->_size - 1], new_el,            \
                                    s->_shared);                               \
                }                                                              \
        }                                                                      \
                                                                               \
        int N##_empty(struct N *s)                                             \
        {                                                                      \
                return s->_size == 0;                                          \
        }
