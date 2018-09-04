#pragma once

#define INIT_STACK(T, N)                                                       \
                                                                               \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                size_t _max;                                                   \
                T *_data;                                                      \
        };                                                                     \
                                                                               \
        static size_t N##_init_size = 1;                                       \
        static double N##_growth_scale = 2;                                    \
                                                                               \
        void N##_set_init_size(size_t init_size)                               \
        {                                                                      \
                init_size = (init_size == 0) ? 1 : init_size;                  \
                N##_init_size = init_size;                                     \
        }                                                                      \
                                                                               \
        void N##_set_growth_scale(double growth_scale)                         \
        {                                                                      \
                growth_scale = (growth_scale == 0) ? 1 : growth_scale;         \
                N##_growth_scale = growth_scale;                               \
        }                                                                      \
                                                                               \
        int N##_is_static()                                                    \
        {                                                                      \
                return 0;                                                      \
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
        /* ================= */                                                \
        /*  STACK FUNCTIONS  */                                                \
        /* ================= */                                                \
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
        }                                                                      \
                                                                               \
        void N##_free(struct N *s)                                             \
        {                                                                      \
                if(s->_data)                                                   \
                {                                                              \
                        if(!T##_is_static() &&                                 \
                           N##_element_copy != N##_flat_copy)                  \
                        {                                                      \
                                for(size_t i = 0; i < s->_size; ++i)           \
                                {                                              \
                                        N##_element_free(&s->_data[i]);        \
                                }                                              \
                        }                                                      \
                        free(s->_data);                                        \
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
                                if(N##_element_equal(&first->_data[i],         \
                                                     &second->_data[i]))       \
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
                        dst->_data = (T *)malloc(dst->_max * sizeof(T));       \
                        if(T##_is_static() ||                                  \
                           N##_element_copy == N##_flat_copy)                  \
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
        static void N##_resize(struct N *s)                                    \
        {                                                                      \
                if(s->_size == s->_max)                                        \
                {                                                              \
			s->_max = (s->_max == 0) ? N##_init_size               \
						 : s->_max * N##_growth_scale; \
                                                                               \
                        s->_data =                                             \
                            (T *)realloc(s->_data, sizeof(T) * s->_max);       \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_push(struct N *s, T el)                                       \
        {                                                                      \
                N##_resize(s);                                                 \
                N##_element_copy(&s->_data[s->_size], &el);                    \
                ++s->_size;                                                    \
        }                                                                      \
                                                                               \
        void N##_pop(struct N *s)                                              \
        {                                                                      \
                if(s->_size)                                                   \
                {                                                              \
			T *el = &s->_data[s->_size - 1];                       \
                        if(!T##_is_static() &&                                 \
                           N##_element_copy != N##_flat_copy)                  \
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
                        if(!T##_is_static() &&                                 \
                           N##_element_copy != N##_flat_copy)                  \
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

