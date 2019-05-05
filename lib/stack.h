#pragma once

#include "inc/sgc_allocator.h"
#include "inc/sgc_basic_types.h"
#include "inc/sgc_utils.h"

#define SGC_INIT_STATIC_FUNCTIONS_STACK(T, N)                                  \
        static void N##_resize(struct N *s);

#define SGC_INIT_HEADERS_STACK(T, N)                                           \
                                                                               \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                size_t _max;                                                   \
                size_t _shared;                                                \
                T *_data;                                                      \
        };                                                                     \
                                                                               \
        typedef struct N N;                                                    \
        typedef T N##_type;                                                    \
                                                                               \
        void N##_set_share(N *s, int is_shared);                               \
        size_t N##_size(const struct N *const s);                              \
        void N##_init(struct N *const s);                                      \
        void N##_free(struct N *s);                                            \
        int N##_equal(const struct N *const first,                             \
                      const struct N *const second);                           \
        void N##_copy(struct N *__restrict__ dst,                              \
                      const struct N *__restrict__ const src);                 \
        void N##_push(struct N *s, T el);                                      \
        void N##_pop(struct N *s);                                             \
        T *N##_top(struct N *s);                                               \
        void N##_set_top(struct N *s, T new_el);                               \
        int N##_empty(struct N *s);

#define SGC_INIT_STACK(T, N)                                                   \
        SGC_INIT_HEADERS_STACK(T, N);                                          \
                                                                               \
        /* ================= */                                                \
        /*  STACK FUNCTIONS  */                                                \
        /* ================= */                                                \
                                                                               \
        void N##_set_share(N *s, int is_shared)                                \
        {                                                                      \
                s->_shared = is_shared;                                        \
        }                                                                      \
                                                                               \
        size_t N##_size(const struct N *const s)                               \
        {                                                                      \
                return s->_size;                                               \
        }                                                                      \
                                                                               \
        void N##_init(struct N *const s)                                       \
        {                                                                      \
                s->_size = s->_max = 0;                                        \
                s->_data = NULL;                                               \
                s->_shared = 0;                                                \
        }                                                                      \
                                                                               \
        void N##_free(struct N *s)                                             \
        {                                                                      \
                if(s->_data)                                                   \
                {                                                              \
                        if(!s->_shared)                                        \
                        {                                                      \
                                for(size_t i = 0; i < s->_size; ++i)           \
                                {                                              \
                                        T##_free(&s->_data[i]);                \
                                }                                              \
                        }                                                      \
                        sgc_free(s->_data);                                    \
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
                        dst->_max = src->_size;                                \
                        dst->_data = (T *)sgc_malloc(dst->_max * sizeof(T));   \
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
        static void N##_resize(struct N *s)                                    \
        {                                                                      \
                if(s->_size == s->_max)                                        \
                {                                                              \
                        s->_max = (s->_max == 0) ? 1 : s->_max * 2;            \
                                                                               \
                        s->_data =                                             \
                            (T *)sgc_realloc(s->_data, sizeof(T) * s->_max);   \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_push(struct N *s, T el)                                       \
        {                                                                      \
                N##_resize(s);                                                 \
                SGC_COPY(T##_copy, s->_data[s->_size], el, s->_shared);        \
                ++s->_size;                                                    \
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
