#pragma once

#include "inc/sgc_basic_types.h"
#include "inc/sgc_utils.h"

#define SGC_INIT_STATIC_FUNCTIONS_STATIC_DEQUE(T, S, N)                        \
        static void N##_move(size_t *flag);                                    \
        static void N##_move_back(size_t *flag);

#define SGC_INIT_HEADERS_STATIC_DEQUE(T, S, N)                                 \
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
        void N##_set_share(N *d, int is_shared);                               \
        size_t N##_size(const struct N *const d);                              \
        void N##_init(struct N *d);                                            \
        void N##_free(struct N *d);                                            \
        int N##_equal(const struct N *const first,                             \
                      const struct N *const second);                           \
        void N##_copy(struct N *__restrict__ dst,                              \
                      const struct N *__restrict__ const src);                 \
        void N##_push_back(struct N *d, T el);                                 \
        void N##_push_front(struct N *d, T el);                                \
        T *N##_front(struct N *d);                                             \
        void N##_set_front(struct N *d, T new_el);                             \
        T *N##_back(struct N *d);                                              \
        void N##_set_back(struct N *d, T new_el);                              \
        void N##_pop_front(struct N *d);                                       \
        void N##_pop_back(struct N *d);                                        \
        void N##_insert(struct N *d, const size_t at, T el);                   \
        void N##_erase_at(struct N *d, const size_t at);                       \
        T *N##_at(struct N *d, size_t at);                                     \
        void N##_set_at(struct N *d, size_t at, T new_el);                     \
        int N##_empty(const struct N *const d);                                \
        T *N##_array(struct N *d);                                             \
                                                                               \
        struct N##_iterator                                                    \
        {                                                                      \
                size_t _curr;                                                  \
                T *_data;                                                      \
                int _is_valid;                                                 \
        };                                                                     \
                                                                               \
        typedef struct N##_iterator N##_iterator;                              \
                                                                               \
        T *N##_iterator_data(struct N##_iterator i);                           \
        const T *N##_iterator_cdata(const struct N##_iterator i);              \
        void N##_iterator_next(struct N##_iterator *i);                        \
        void N##_iterator_prev(struct N##_iterator *i);                        \
        void N##_iterator_begin(struct N *d, struct N##_iterator *i);          \
        void N##_iterator_cbegin(const struct N *const d,                      \
                                 struct N##_iterator *i);                      \
        struct N##_iterator N##_begin(struct N *d);                            \
        struct N##_iterator N##_cbegin(const struct N *const d);               \
        void N##_iterator_end(struct N *d, struct N##_iterator *i);            \
        void N##_iterator_cend(const struct N *const d,                        \
                               struct N##_iterator *i);                        \
        struct N##_iterator N##_end(struct N *d);                              \
        struct N##_iterator N##_cend(const struct N *const d);                 \
        void N##_iterator_from(struct N *d, struct N##_iterator *i,            \
                               size_t at);                                     \
        void N##_iterator_cfrom(const struct N *const d,                       \
                                struct N##_iterator *i, size_t at);            \
        struct N##_iterator N##_from(struct N *d, size_t at);                  \
        struct N##_iterator N##_cfrom(const struct N *const d, size_t at);     \
        void N##_iterator_jump(struct N##_iterator *i, ssize_t range);         \
        int N##_iterator_equal(const struct N##_iterator first,                \
                               const struct N##_iterator second);              \
        ssize_t N##_iterator_range(const struct N##_iterator first,            \
                                   const struct N##_iterator second);          \
        int N##_iterator_valid(const struct N##_iterator it);

#define SGC_INIT_STATIC_DEQUE(T, S, N)                                         \
        SGC_INIT_HEADERS_STATIC_DEQUE(T, S, N);                                \
        SGC_INIT_STATIC_FUNCTIONS_STATIC_DEQUE(T, S, N);                       \
                                                                               \
        size_t N##_max(void)                                                   \
        {                                                                      \
                return S;                                                      \
        }                                                                      \
                                                                               \
        /* =================== */                                              \
        /*  ELEMENT FUNCTIONS  */                                              \
        /* =================== */                                              \
                                                                               \
        void N##_set_share(N *d, int is_shared)                                \
        {                                                                      \
                d->_shared = is_shared;                                        \
        }                                                                      \
                                                                               \
        size_t N##_size(const struct N *const d)                               \
        {                                                                      \
                return d->_size;                                               \
        }                                                                      \
                                                                               \
        void N##_init(struct N *d)                                             \
        {                                                                      \
                d->_size = d->_front = d->_back = 0;                           \
                d->_shared = 0;                                                \
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
        static void N##_move_back(size_t *flag)                                \
        {                                                                      \
                if(*flag == 0)                                                 \
                {                                                              \
                        *flag = S - 1;                                         \
                }                                                              \
                else                                                           \
                {                                                              \
                        --*flag;                                               \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_free(struct N *d)                                             \
        {                                                                      \
                if(d->_data)                                                   \
                {                                                              \
                        if(!d->_shared)                                        \
                        {                                                      \
                                size_t i;                                      \
                                for(i = d->_front; i != d->_back;)             \
                                {                                              \
                                        T##_free(&d->_data[i]);                \
                                        N##_move(&i);                          \
                                }                                              \
                                T##_free(&d->_data[i]);                        \
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
                                        T##_copy(&dst->_data[j],               \
                                                 &src->_data[i]);              \
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
        void N##_push_back(struct N *d, T el)                                  \
        {                                                                      \
                if(d->_size < S)                                               \
                {                                                              \
                        N##_move(&d->_back);                                   \
                        if(d->_size == 0)                                      \
                        {                                                      \
                                --d->_back;                                    \
                        }                                                      \
                        SGC_COPY(T##_copy, d->_data[d->_back], el,             \
                                 d->_shared);                                  \
                        ++d->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_push_front(struct N *d, T el)                                 \
        {                                                                      \
                N##_move_back(&d->_front);                                     \
                if(d->_size == 0)                                              \
                {                                                              \
                        d->_front = 0;                                         \
                }                                                              \
                SGC_COPY(T##_copy, d->_data[d->_front], el, d->_shared);       \
                ++d->_size;                                                    \
        }                                                                      \
                                                                               \
        T *N##_front(struct N *d)                                              \
        {                                                                      \
                T *ret = NULL;                                                 \
                if(d->_size)                                                   \
                {                                                              \
                        ret = &d->_data[d->_front];                            \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        void N##_set_front(struct N *d, T new_el)                              \
        {                                                                      \
                if(d->_size)                                                   \
                {                                                              \
                        SGC_REPLACE(T##_copy, T##_free, d->_data[d->_front],   \
                                    new_el, d->_shared);                       \
                }                                                              \
        }                                                                      \
                                                                               \
        T *N##_back(struct N *d)                                               \
        {                                                                      \
                T *ret = NULL;                                                 \
                if(d->_size)                                                   \
                {                                                              \
                        ret = &d->_data[d->_back];                             \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        void N##_set_back(struct N *d, T new_el)                               \
        {                                                                      \
                if(d->_size)                                                   \
                {                                                              \
                        SGC_REPLACE(T##_copy, T##_free, d->_data[d->_back],    \
                                    new_el, d->_shared);                       \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_pop_front(struct N *d)                                        \
        {                                                                      \
                if(d->_size)                                                   \
                {                                                              \
                        T *el = &d->_data[d->_front];                          \
                        if(!d->_shared)                                        \
                        {                                                      \
                                T##_free(el);                                  \
                        }                                                      \
                        N##_move(&d->_front);                                  \
                        --d->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_pop_back(struct N *d)                                         \
        {                                                                      \
                if(d->_size)                                                   \
                {                                                              \
                        T *el = &d->_data[d->_back];                           \
                        if(!d->_shared)                                        \
                        {                                                      \
                                T##_free(el);                                  \
                        }                                                      \
                        N##_move_back(&d->_back);                              \
                        --d->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_insert(struct N *d, const size_t at, T el)                    \
        {                                                                      \
                if(at == 0 || d->_size == 0)                                   \
                {                                                              \
                        N##_push_front(d, el);                                 \
                }                                                              \
                else if(at >= d->_size)                                        \
                {                                                              \
                        N##_push_back(d, el);                                  \
                }                                                              \
                else                                                           \
                {                                                              \
                        size_t _at = (at + d->_front) % S;                     \
                        size_t shift_front = 0;                                \
                        size_t shift_back = 0;                                 \
                        size_t shift_end = 0;                                  \
                        size_t shift_begin = 0;                                \
                        if(2 * at > d->_size)                                  \
                        {                                                      \
                                if(_at <= d->_back)                            \
                                {                                              \
                                        shift_end = d->_back + 1 - _at;        \
                                        if(d->_back + 1 == S)                  \
                                        {                                      \
                                                --shift_end;                   \
                                                shift_back = 1;                \
                                        }                                      \
                                }                                              \
                                else                                           \
                                {                                              \
                                        shift_end = S - _at - 1;               \
                                        shift_back = 1;                        \
                                        shift_begin = d->_back + 1;            \
                                }                                              \
                                memmove(d->_data + 1, d->_data,                \
                                        shift_begin * sizeof(T));              \
                                memmove(d->_data, d->_data + S - 1,            \
                                        shift_back * sizeof(T));               \
                                memmove(d->_data + _at + 1, d->_data + _at,    \
                                        shift_end * sizeof(T));                \
                                N##_move(&d->_back);                           \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                if(_at >= d->_front)                           \
                                {                                              \
                                        shift_end = _at - d->_front;           \
                                        if(d->_front == 0)                     \
                                        {                                      \
                                                --shift_end;                   \
                                                shift_front = 1;               \
                                        }                                      \
                                }                                              \
                                else                                           \
                                {                                              \
                                        shift_end = S - d->_front;             \
                                        shift_begin = _at;                     \
                                        shift_back = 1;                        \
                                }                                              \
                                memmove(d->_data + S - 1,                      \
                                        d->_data + d->_front,                  \
                                        shift_front * sizeof(T));              \
                                memmove(d->_data + d->_front - 1 +             \
                                            shift_front,                       \
                                        d->_data + d->_front + shift_front,    \
                                        shift_end * sizeof(T));                \
                                memmove(d->_data + S - 1, d->_data,            \
                                        shift_back * sizeof(T));               \
                                memmove(d->_data, d->_data + 1,                \
                                        shift_begin * sizeof(T));              \
                                N##_move_back(&d->_front);                     \
                        }                                                      \
                        ++d->_size;                                            \
                        SGC_COPY(T##_copy, d->_data[(at + d->_front) % S], el, \
                                 d->_shared);                                  \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_erase_at(struct N *d, const size_t at)                        \
        {                                                                      \
                if(at < d->_size && d->_size > 0)                              \
                {                                                              \
                        if(!d->_shared)                                        \
                        {                                                      \
                                T##_free(&d->_data[at]);                       \
                        }                                                      \
                        size_t _at = (at + d->_front) % S;                     \
                        size_t shift_back = 0;                                 \
                        size_t shift_end = 0;                                  \
                        size_t shift_begin = 0;                                \
                        if(d->_size == 1)                                      \
                        {                                                      \
                                d->_front = d->_back = 0;                      \
                        }                                                      \
                        else if(2 * at > d->_size)                             \
                        {                                                      \
                                if(_at <= d->_back)                            \
                                {                                              \
                                        shift_begin = d->_back - _at;          \
                                }                                              \
                                else                                           \
                                {                                              \
                                        shift_begin = S - _at - 1;             \
                                        shift_back = 1;                        \
                                        shift_end = d->_back;                  \
                                }                                              \
                                memmove(d->_data + _at, d->_data + _at + 1,    \
                                        shift_begin * sizeof(T));              \
                                memmove(d->_data + S - 1, d->_data,            \
                                        shift_back * sizeof(T));               \
                                memmove(d->_data, d->_data + 1,                \
                                        shift_end * sizeof(T));                \
                                N##_move_back(&d->_back);                      \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                if(_at >= d->_front)                           \
                                {                                              \
                                        shift_end = _at - d->_front;           \
                                }                                              \
                                else                                           \
                                {                                              \
                                        shift_end = S - d->_front - 1;         \
                                        shift_begin = _at;                     \
                                        shift_back = 1;                        \
                                }                                              \
                                memmove(d->_data + 1, d->_data,                \
                                        shift_begin * sizeof(T));              \
                                memmove(d->_data, d->_data + S - 1,            \
                                        shift_back * sizeof(T));               \
                                memmove(d->_data + d->_front + 1,              \
                                        d->_data + d->_front,                  \
                                        shift_end * sizeof(T));                \
                                N##_move(&d->_front);                          \
                        }                                                      \
                        --d->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        T *N##_at(struct N *d, size_t at)                                      \
        {                                                                      \
                T *ret = NULL;                                                 \
                if(at < d->_size)                                              \
                {                                                              \
                        ret = &d->_data[(d->_front + at) % S];                 \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        void N##_set_at(struct N *d, size_t at, T new_el)                      \
        {                                                                      \
                if(at < d->_size)                                              \
                {                                                              \
                        SGC_REPLACE(T##_copy, T##_free,                        \
                                    d->_data[(d->_front + at) % S], new_el,    \
                                    d->_shared);                               \
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
                        if(d->_back >= d->_front)                              \
                        {                                                      \
                                ret = d->_data + d->_front;                    \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                memcpy(d->_data + d->_back + 1,                \
                                       d->_data + d->_front,                   \
                                       (S - d->_front) * sizeof(T));           \
                                d->_front = 0;                                 \
                                d->_back = d->_size - 1;                       \
                                ret = d->_data;                                \
                        }                                                      \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        /* ================ */                                                 \
        /*  DEQUE ITERATOR  */                                                 \
        /* ================ */                                                 \
                                                                               \
        T *N##_iterator_data(struct N##_iterator i)                            \
        {                                                                      \
                return &i._data[i._curr];                                      \
        }                                                                      \
                                                                               \
        const T *N##_iterator_cdata(const struct N##_iterator i)               \
        {                                                                      \
                return &i._data[i._curr];                                      \
        }                                                                      \
                                                                               \
        void N##_iterator_next(struct N##_iterator *i)                         \
        {                                                                      \
                if(i->_curr + 1 == S)                                          \
                {                                                              \
                        i->_curr = 0;                                          \
                }                                                              \
                else                                                           \
                {                                                              \
                        ++i->_curr;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_iterator_prev(struct N##_iterator *i)                         \
        {                                                                      \
                if(i->_curr == 0)                                              \
                {                                                              \
                        i->_curr = S - 1;                                      \
                }                                                              \
                else                                                           \
                {                                                              \
                        --i->_curr;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_iterator_begin(struct N *d, struct N##_iterator *i)           \
        {                                                                      \
                i->_data = (T *)d->_data;                                      \
                i->_curr = d->_front;                                          \
                i->_is_valid = (d->_size) ? 1 : 0;                             \
        }                                                                      \
                                                                               \
        void N##_iterator_cbegin(const struct N *const d,                      \
                                 struct N##_iterator *i)                       \
        {                                                                      \
                i->_data = (T *)d->_data;                                      \
                i->_curr = d->_front;                                          \
                i->_is_valid = (d->_size) ? 1 : 0;                             \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_begin(struct N *d)                             \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_begin(d, &i);                                     \
                return i;                                                      \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_cbegin(const struct N *const d)                \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_cbegin(d, &i);                                    \
                return i;                                                      \
        }                                                                      \
                                                                               \
        void N##_iterator_end(struct N *d, struct N##_iterator *i)             \
        {                                                                      \
                i->_data = (T *)d->_data;                                      \
                i->_curr = d->_back;                                           \
                i->_is_valid = (d->_size) ? 1 : 0;                             \
        }                                                                      \
                                                                               \
        void N##_iterator_cend(const struct N *const d,                        \
                               struct N##_iterator *i)                         \
        {                                                                      \
                i->_data = (T *)d->_data;                                      \
                i->_curr = d->_back;                                           \
                i->_is_valid = (d->_size) ? 1 : 0;                             \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_end(struct N *d)                               \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_end(d, &i);                                       \
                return i;                                                      \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_cend(const struct N *const d)                  \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_cend(d, &i);                                      \
                return i;                                                      \
        }                                                                      \
                                                                               \
        void N##_iterator_from(struct N *d, struct N##_iterator *i, size_t at) \
        {                                                                      \
                i->_data = (T *)d->_data;                                      \
                i->_curr = (d->_front + at) % S;                               \
                i->_is_valid = (d->_size > at) ? 1 : 0;                        \
        }                                                                      \
                                                                               \
        void N##_iterator_cfrom(const struct N *const d,                       \
                                struct N##_iterator *i, size_t at)             \
        {                                                                      \
                i->_data = (T *)d->_data;                                      \
                i->_curr = (d->_front + at) % S;                               \
                i->_is_valid = (d->_size > at) ? 1 : 0;                        \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_from(struct N *d, size_t at)                   \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_from(d, &i, at);                                  \
                return i;                                                      \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_cfrom(const struct N *const d, size_t at)      \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_cfrom(d, &i, at);                                 \
                return i;                                                      \
        }                                                                      \
                                                                               \
        void N##_iterator_jump(struct N##_iterator *i, ssize_t range)          \
        {                                                                      \
                i->_curr = (S + i->_curr + range) % S;                         \
        }                                                                      \
                                                                               \
        int N##_iterator_equal(const struct N##_iterator first,                \
                               const struct N##_iterator second)               \
        {                                                                      \
                return first._curr == second._curr &&                          \
                       first._data == second._data;                            \
        }                                                                      \
                                                                               \
        ssize_t N##_iterator_range(const struct N##_iterator first,            \
                                   const struct N##_iterator second)           \
        {                                                                      \
                return second._curr - first._curr;                             \
        }                                                                      \
                                                                               \
        int N##_iterator_valid(const struct N##_iterator it)                   \
        {                                                                      \
                return it._is_valid;                                           \
        }
