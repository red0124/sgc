#pragma once

#define INIT_PRIORITY_QUEUE(T, N)                                              \
                                                                               \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                size_t _max;                                                   \
                T *_data;                                                      \
        };                                                                     \
                                                                               \
        typedef struct N N;                                                    \
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
        int (*N##_element_compare)(const T *const, const T *const) =           \
            T##_compare;                                                       \
                                                                               \
        void N##_set_compare(int (*compare)(const T *const, const T *const))   \
        {                                                                      \
                N##_element_compare = compare;                                 \
        }                                                                      \
                                                                               \
        /* ==========================*/                                        \
        /*  PRIOITY QUEUE FUNCTIONS  */                                        \
        /* ==========================*/                                        \
                                                                               \
        void N##_init(struct N *p)                                             \
        {                                                                      \
                p->_size = p->_max = 0;                                        \
                p->_data = NULL;                                               \
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
                        if(!T##_is_static() &&                                 \
                           N##_element_copy != N##_flat_copy)                  \
                        {                                                      \
                                for(size_t i = 0; i < p->_size; ++i)           \
                                {                                              \
                                        N##_element_free(&p->_data[i]);        \
                                }                                              \
                        }                                                      \
                        free(p->_data);                                        \
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
        void N##_shrink(struct N *p)                                           \
        {                                                                      \
                if(!T##_is_static() || N##_element_copy != N##_flat_copy)      \
                {                                                              \
                        for(size_t i = p->_size; i < p->_max; ++i)             \
                        {                                                      \
                                N##_element_free(&p->_data[i]);                \
                        }                                                      \
                }                                                              \
                p->_data = (T *)realloc(p->_data, sizeof(T) * p->_size);       \
        }                                                                      \
                                                                               \
        static void N##_resize(struct N *p)                                    \
        {                                                                      \
                if(p->_size == p->_max)                                        \
                {                                                              \
                        p->_max = (p->_max == 0) ? N##_init_size               \
                                                 : p->_max * N##_growth_scale; \
                        p->_data =                                             \
                            (T *)realloc(p->_data, sizeof(T) * p->_max);       \
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
                        if(N##_element_compare(&p->_data[parent],              \
                                               &p->_data[curr]) < 0)           \
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
                N##_resize(p);                                                 \
                N##_element_copy(&p->_data[p->_size], &el);                    \
                N##_fix_insert(p);                                             \
                ++p->_size;                                                    \
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
                           N##_element_compare(&p->_data[left],                \
                                               &p->_data[right]) > 0)          \
                        {                                                      \
                                tmp = left;                                    \
                        }                                                      \
                        if(N##_element_compare(&p->_data[tmp],                 \
                                               &p->_data[curr]) > 0)           \
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
                        if(N##_element_copy != N##_flat_copy)                  \
                        {                                                      \
                                N##_element_free(&p->_data[p->_size]);         \
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
                        p->_max = size;                                        \
                        p->_data = (T *)malloc(sizeof(T) * p->_max);           \
                        p->_size = 0;                                          \
                        for(size_t i = 0; i < size; ++i)                       \
                        {                                                      \
                                N##_push(p, arr[i]);                           \
                        }                                                      \
                }                                                              \
                else                                                           \
                {                                                              \
                        p->_max = p->_size = 0;                                \
                        p->_data = NULL;                                       \
                }                                                              \
        }