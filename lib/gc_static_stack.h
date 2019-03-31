#pragma once

#define SGC_INIT_STATIC_STACK(T, S, N)                                             \
                                                                               \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                T _data[S];                                                    \
        };                                                                     \
                                                                               \
        typedef struct N N;                                                    \
        typedef T N##_type;                                                    \
        typedef T N##_value;                                                   \
        typedef T N##_key;                                                     \
                                                                               \
        size_t N##_max()                                                       \
        {                                                                      \
                return S;                                                      \
        }                                                                      \
                                                                               \
        /* =================== */                                              \
        /*  ELEMENT FUNCTIONS  */                                              \
        /* =================== */                                              \
                                                                               \
        static void (*N##_element_copy)(T *, const T *const) = T##_copy;       \
                                                                               \
        void N##_set_copy(void (*copy)(T *, const T *const))                   \
        {                                                                      \
                N##_element_copy = copy;                                       \
        }                                                                      \
                                                                               \
        static void N##_flat_copy(T *dst, const T *const src)                  \
        {                                                                      \
                *dst = *src;                                                   \
        }                                                                      \
                                                                               \
        void N##_set_share(int is_shared)                                      \
        {                                                                      \
                if(is_shared)                                                  \
                {                                                              \
                        N##_set_copy(N##_flat_copy);                           \
                }                                                              \
                else                                                           \
                {                                                              \
                        N##_set_copy(T##_copy);                                \
                }                                                              \
        }                                                                      \
                                                                               \
        static int (*N##_element_equal)(const T *const, const T *const) =      \
            T##_equal;                                                         \
                                                                               \
        void N##_set_equal(int (*equal)(const T *const, const T *const))       \
        {                                                                      \
                N##_element_equal = equal;                                     \
        }                                                                      \
                                                                               \
        static void (*N##_element_free)(T *) = T##_free;                       \
                                                                               \
        void N##_set_free(void (*free)(T *))                                   \
        {                                                                      \
                N##_element_free = free;                                       \
        }                                                                      \
                                                                               \
        void N##_push(struct N *, T);                                          \
                                                                               \
        static void (*N##_default_insert_function)(struct N *, T) = N##_push;  \
                                                                               \
        void N##_set_default_insert(void (*insert)(N *, T))                    \
        {                                                                      \
                N##_default_insert_function = insert;                          \
        }                                                                      \
                                                                               \
        void N##_default_insert(struct N *d, T el)                             \
        {                                                                      \
                N##_default_insert_function(d, el);                            \
        }                                                                      \
                                                                               \
        /* ======================== */                                         \
        /*  STATIC STACK FUNCTIONS  */                                         \
        /* ======================== */                                         \
                                                                               \
        void N##_init(struct N *s)                                             \
        {                                                                      \
                s->_size = 0;                                                  \
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
                        if(N##_element_copy != N##_flat_copy)                  \
                        {                                                      \
                                for(size_t i = 0; i < s->_size; ++i)           \
                                {                                              \
                                        N##_element_free(&s->_data[i]);        \
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
                      const struct N *__restrict__ const src)                  \
        {                                                                      \
                if(src->_size != 0)                                            \
                {                                                              \
                        dst->_size = src->_size;                               \
                        if(N##_element_copy == N##_flat_copy)                  \
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
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_push(struct N *s, T el)                                       \
        {                                                                      \
                if(s->_size < S)                                               \
                {                                                              \
                        N##_element_copy(&s->_data[s->_size], &el);            \
                        ++s->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_pop(struct N *s)                                              \
        {                                                                      \
                if(s->_size)                                                   \
                {                                                              \
                        T *el = &s->_data[s->_size - 1];                       \
                        if(N##_element_copy != N##_flat_copy)                  \
                        {                                                      \
                                N##_element_free(el);                          \
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
                        T *el = &s->_data[s->_size - 1];                       \
                        if(N##_element_copy != N##_flat_copy)                  \
                        {                                                      \
                                N##_element_free(el);                          \
                                N##_element_copy(el, &new_el);                 \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                *el = new_el;                                  \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        int N##_empty(struct N *s)                                             \
        {                                                                      \
                return s->_size == 0;                                          \
        }
