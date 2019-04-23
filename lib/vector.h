#pragma once

#include "allocator.h"
#include "utils.h"
#include "basic_types.h"

#define SGC_INIT_STATIC_FUNCTIONS_VECTOR(T, N)                                 \
        static void N##_resize(struct N *v);

#define SGC_INIT_HEADERS_VECTOR(T, N)                                          \
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
        void N##_set_share(N *v, int is_shared);                               \
        void N##_init(struct N *v);                                            \
        size_t N##_size(const struct N *v);                                    \
        void N##_free(struct N *v);                                            \
        int N##_equal(const struct N *const first,                             \
                      const struct N *const second);                           \
        void N##_copy(struct N *__restrict__ dst,                              \
                      const struct N *__restrict__ const src);                 \
        void N##_from_array(struct N *v, const T *const arr,                   \
                            const size_t size);                                \
        void N##_shrink(struct N *v);                                          \
        void N##_push_back(struct N *v, T el);                                 \
        void N##_pop_back(struct N *v);                                        \
        void N##_insert(struct N *v, const size_t at, T el);                   \
        void N##_push_front(struct N *v, T el);                                \
        T *N##_at(struct N *v, size_t at);                                     \
        void N##_set_at(struct N *v, size_t at, T new_el);                     \
        T *N##_back(struct N *v);                                              \
        void N##_set_back(struct N *v, T new_el);                              \
        T *N##_front(struct N *v);                                             \
        void N##_set_front(struct N *v, T new_el);                             \
        void N##_erase_at(struct N *v, const size_t at);                       \
        int N##_empty(const struct N *const d);                                \
        T *N##_array(struct N *d);                                             \
                                                                               \
        struct N##_iterator                                                    \
        {                                                                      \
                T *_curr;                                                      \
                T *_end;                                                       \
                T *_begin;                                                     \
        };                                                                     \
                                                                               \
        T *N##_iterator_data(struct N##_iterator i);                           \
        const T *N##_iterator_cdata(const struct N##_iterator i);              \
        void N##_iterator_next(struct N##_iterator *i);                        \
        void N##_iterator_prev(struct N##_iterator *i);                        \
        void N##_iterator_begin(struct N *v, struct N##_iterator *i);          \
        void N##_iterator_cbegin(const struct N *const v,                      \
                                 struct N##_iterator *i);                      \
        struct N##_iterator N##_begin(struct N *v);                            \
        struct N##_iterator N##_cbegin(const struct N *const v);               \
        void N##_iterator_end(struct N *v, struct N##_iterator *i);            \
        void N##_iterator_cend(const struct N *const v,                        \
                               struct N##_iterator *i);                        \
        struct N##_iterator N##_end(struct N *v);                              \
        struct N##_iterator N##_cend(const struct N *const v);                 \
        void N##_iterator_from(struct N *v, struct N##_iterator *i,            \
                               size_t at);                                     \
        void N##_iterator_cfrom(const struct N *const v,                       \
                                struct N##_iterator *i, size_t at);            \
        struct N##_iterator N##_from(struct N *v, size_t at);                  \
        struct N##_iterator N##_cfrom(const struct N *const v, size_t at);     \
        void N##_iterator_jump(struct N##_iterator *i, ssize_t range);         \
        int N##_iterator_equal(const struct N##_iterator first,                \
                               const struct N##_iterator second);              \
        ssize_t N##_iterator_range(const struct N##_iterator first,            \
                                   const struct N##_iterator second);          \
        int N##_iterator_valid(const struct N##_iterator i);

#define SGC_INIT_VECTOR(T, N)                                                  \
        SGC_INIT_HEADERS_VECTOR(T, N);                                         \
        SGC_INIT_STATIC_FUNCTIONS_VECTOR(T, N);                                \
                                                                               \
        /* ================== */                                               \
        /*  VECTOR FUNCTIONS  */                                               \
        /* ================== */                                               \
                                                                               \
        void N##_set_share(N *v, int is_shared)                                \
        {                                                                      \
                v->_shared = is_shared;                                        \
        }                                                                      \
                                                                               \
        void N##_init(struct N *v)                                             \
        {                                                                      \
                v->_size = v->_max = 0;                                        \
                v->_data = NULL;                                               \
                v->_shared = 0;                                                \
        }                                                                      \
                                                                               \
        size_t N##_size(const struct N *v)                                     \
        {                                                                      \
                return v->_size;                                               \
        }                                                                      \
                                                                               \
        void N##_free(struct N *v)                                             \
        {                                                                      \
                if(v->_data)                                                   \
                {                                                              \
                        if(!v->_shared)                                        \
                        {                                                      \
                                for(size_t i = 0; i < v->_size; ++i)           \
                                {                                              \
                                        T##_free(&v->_data[i]);                \
                                }                                              \
                        }                                                      \
                        sgc_free(v->_data);                                    \
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
                        if(!dst->_shared)                                      \
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
        void N##_from_array(struct N *v, const T *const arr,                   \
                            const size_t size)                                 \
        {                                                                      \
                if(size)                                                       \
                {                                                              \
                        v->_max = v->_size = size;                             \
                        v->_data = (T *)sgc_malloc(sizeof(T) * size);          \
                        v->_shared = 0;                                        \
                        for(size_t i = 0; i < v->_size; ++i)                   \
                        {                                                      \
                                T##_copy(&v->_data[i], &arr[i]);               \
                        }                                                      \
                }                                                              \
                else                                                           \
                {                                                              \
                        v->_max = v->_size = 0;                                \
                        v->_data = NULL;                                       \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_shrink(struct N *v)                                           \
        {                                                                      \
                if(!v->_shared)                                                \
                {                                                              \
                        for(size_t i = v->_size; i < v->_max; ++i)             \
                        {                                                      \
                                T##_free(&v->_data[i]);                        \
                        }                                                      \
                }                                                              \
                v->_data = (T *)sgc_realloc(v->_data, sizeof(T) * v->_size);   \
        }                                                                      \
                                                                               \
        static void N##_resize(struct N *v)                                    \
        {                                                                      \
                if(v->_size == v->_max)                                        \
                {                                                              \
                        v->_max = (v->_max == 0) ? 1 : v->_max * 2;            \
                        v->_data =                                             \
                            (T *)sgc_realloc(v->_data, sizeof(T) * v->_max);   \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_push_back(struct N *v, T el)                                  \
        {                                                                      \
                N##_resize(v);                                                 \
                if(!v->_shared)                                                \
                {                                                              \
                        T##_copy(&v->_data[v->_size], &el);                    \
                }                                                              \
                else                                                           \
                {                                                              \
                        v->_data[v->_size] = el;                               \
                }                                                              \
                ++v->_size;                                                    \
        }                                                                      \
                                                                               \
        void N##_pop_back(struct N *v)                                         \
        {                                                                      \
                if(v->_size)                                                   \
                {                                                              \
                        T *el = &v->_data[--v->_size];                         \
                        if(!v->_shared)                                        \
                        {                                                      \
                                T##_free(el);                                  \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_insert(struct N *v, const size_t at, T el)                    \
        {                                                                      \
                if(at < v->_size)                                              \
                {                                                              \
                        N##_resize(v);                                         \
                        memmove(v->_data + at + 1, v->_data + at,              \
                                (v->_size - at) * sizeof(T));                  \
                        if(!v->_shared)                                        \
                        {                                                      \
                                T##_copy(&v->_data[at], &el);                  \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                v->_data[at] = el;                             \
                        }                                                      \
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
        T *N##_at(struct N *v, size_t at)                                      \
        {                                                                      \
                return v->_data + at;                                          \
        }                                                                      \
                                                                               \
        void N##_set_at(struct N *v, size_t at, T new_el)                      \
        {                                                                      \
                if(at < v->_size)                                              \
                {                                                              \
                        T *el = &v->_data[at];                                 \
                        if(!v->_shared)                                        \
                        {                                                      \
                                T##_free(el);                                  \
                                T##_copy(el, &new_el);                         \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                *el = new_el;                                  \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        T *N##_back(struct N *v)                                               \
        {                                                                      \
                return N##_at(v, v->_size - 1);                                \
        }                                                                      \
                                                                               \
        void N##_set_back(struct N *v, T new_el)                               \
        {                                                                      \
                N##_set_at(v, v->_size - 1, new_el);                           \
        }                                                                      \
                                                                               \
        T *N##_front(struct N *v)                                              \
        {                                                                      \
                return N##_at(v, 0);                                           \
        }                                                                      \
                                                                               \
        void N##_set_front(struct N *v, T new_el)                              \
        {                                                                      \
                N##_set_at(v, 0, new_el);                                      \
        }                                                                      \
                                                                               \
        void N##_erase_at(struct N *v, const size_t at)                        \
        {                                                                      \
                if(at < v->_size)                                              \
                {                                                              \
                        if(!v->_shared)                                        \
                        {                                                      \
                                T##_free(&v->_data[at]);                       \
                        }                                                      \
                        memmove(v->_data + at, v->_data + at + 1,              \
                                (v->_size - at) * sizeof(T));                  \
                        --v->_size;                                            \
                }                                                              \
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
        /* ================= */                                                \
        /*  VECTOR ITERATOR  */                                                \
        /* ================= */                                                \
                                                                               \
        T *N##_iterator_data(struct N##_iterator i)                            \
        {                                                                      \
                return i._curr;                                                \
        }                                                                      \
                                                                               \
        const T *N##_iterator_cdata(const struct N##_iterator i)               \
        {                                                                      \
                return i._curr;                                                \
        }                                                                      \
                                                                               \
        void N##_iterator_next(struct N##_iterator *i)                         \
        {                                                                      \
                ++i->_curr;                                                    \
        }                                                                      \
                                                                               \
        void N##_iterator_prev(struct N##_iterator *i)                         \
        {                                                                      \
                --i->_curr;                                                    \
        }                                                                      \
                                                                               \
        void N##_iterator_begin(struct N *v, struct N##_iterator *i)           \
        {                                                                      \
                i->_curr = v->_data;                                           \
                i->_begin = v->_data;                                          \
                i->_end = v->_data + v->_size - 1;                             \
        }                                                                      \
                                                                               \
        void N##_iterator_cbegin(const struct N *const v,                      \
                                 struct N##_iterator *i)                       \
        {                                                                      \
                i->_curr = v->_data;                                           \
                i->_begin = v->_data;                                          \
                i->_end = v->_data + v->_size - 1;                             \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_begin(struct N *v)                             \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_begin(v, &i);                                     \
                return i;                                                      \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_cbegin(const struct N *const v)                \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_cbegin(v, &i);                                    \
                return i;                                                      \
        }                                                                      \
                                                                               \
        void N##_iterator_end(struct N *v, struct N##_iterator *i)             \
        {                                                                      \
                i->_curr = v->_data + v->_size - 1;                            \
                i->_begin = v->_data;                                          \
                i->_end = v->_data + v->_size - 1;                             \
        }                                                                      \
                                                                               \
        void N##_iterator_cend(const struct N *const v,                        \
                               struct N##_iterator *i)                         \
        {                                                                      \
                i->_curr = v->_data + v->_size - 1;                            \
                i->_begin = v->_data;                                          \
                i->_end = v->_data + v->_size - 1;                             \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_end(struct N *v)                               \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_end(v, &i);                                       \
                return i;                                                      \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_cend(const struct N *const v)                  \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_cend(v, &i);                                      \
                return i;                                                      \
        }                                                                      \
                                                                               \
        void N##_iterator_from(struct N *v, struct N##_iterator *i, size_t at) \
        {                                                                      \
                i->_curr = v->_data + at;                                      \
                i->_begin = v->_data;                                          \
                i->_end = v->_data + v->_size - 1;                             \
        }                                                                      \
                                                                               \
        void N##_iterator_cfrom(const struct N *const v,                       \
                                struct N##_iterator *i, size_t at)             \
        {                                                                      \
                i->_curr = v->_data + at;                                      \
                i->_begin = v->_data;                                          \
                i->_end = v->_data + v->_size - 1;                             \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_from(struct N *v, size_t at)                   \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_from(v, &i, at);                                  \
                return i;                                                      \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_cfrom(const struct N *const v, size_t at)      \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_cfrom(v, &i, at);                                 \
                return i;                                                      \
        }                                                                      \
                                                                               \
        void N##_iterator_jump(struct N##_iterator *i, ssize_t range)          \
        {                                                                      \
                i->_curr = i->_curr + range;                                   \
        }                                                                      \
                                                                               \
        int N##_iterator_equal(const struct N##_iterator first,                \
                               const struct N##_iterator second)               \
        {                                                                      \
                return first._curr == second._curr;                            \
        }                                                                      \
                                                                               \
        ssize_t N##_iterator_range(const struct N##_iterator first,            \
                                   const struct N##_iterator second)           \
        {                                                                      \
                return second._curr - first._curr;                             \
        }                                                                      \
                                                                               \
        int N##_iterator_valid(const struct N##_iterator i)                    \
        {                                                                      \
                return i._begin != NULL && i._curr <= i._end &&                \
                       i._curr >= i._begin;                                    \
        }
