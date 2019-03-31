#pragma once

#define INIT_QUEUE(T, N)                                                       \
                                                                               \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                size_t _max;                                                   \
                size_t _back;                                                  \
                size_t _front;                                                 \
                T *_data;                                                      \
        };                                                                     \
                                                                               \
        typedef struct N N;                                                    \
        typedef T N##_type;                                                    \
        typedef T N##_value;                                                   \
        typedef T N##_key;                                                     \
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
        static void (*N##_default_insert_function)(struct N *, T) =            \
            N##_push;                                                          \
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
        /* ================= */                                                \
        /*  QUEUE FUNCTIONS  */                                                \
        /* ================= */                                                \
                                                                               \
        size_t N##_size(const struct N *const q)                               \
        {                                                                      \
                return q->_size;                                               \
        }                                                                      \
                                                                               \
        void N##_init(struct N *q)                                             \
        {                                                                      \
                q->_size = q->_max = q->_front = q->_back = 0;                 \
                q->_data = NULL;                                               \
        }                                                                      \
                                                                               \
        static void N##_move(size_t *flag, size_t max)                         \
        {                                                                      \
                if(*flag + 1 == max)                                           \
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
                        if(N##_element_copy != N##_flat_copy)                  \
                        {                                                      \
				size_t i;                                      \
                                for(i = q->_front; i != q->_back;)             \
                                {                                              \
                                        N##_element_free(&q->_data[i]);        \
                                        N##_move(&i, q->_max);                 \
                                }                                              \
				N##_element_free(&q->_data[i]);                \
                        }                                                      \
                        free(q->_data);                                        \
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
                                if(!N##_element_equal(&first->_data[i],        \
                                                     &second->_data[j]))       \
                                {                                              \
                                        equal = 0;                             \
                                        break;                                 \
                                }                                              \
                                N##_move(&i, first->_max);                     \
                                N##_move(&j, second->_max);                    \
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
                        dst->_data = (T *)malloc(src->_size * sizeof(T));      \
                        if(N##_element_copy == N##_flat_copy)                  \
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
                                        size_t second_part =                   \
                                            src->_max - src->_front;           \
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
                                        N##_element_copy(&dst->_data[j],       \
                                                         &src->_data[i]);      \
                                        N##_move(&i, src->_max);               \
                                }                                              \
                        }                                                      \
                }                                                              \
                                                                               \
                dst->_size = dst->_max = src->_size;                           \
                dst->_back = src->_size - 1;                                   \
                dst->_front = 0;                                               \
        }                                                                      \
                                                                               \
        static void N##_resize(struct N *q)                                    \
        {                                                                      \
                if(q->_size == q->_max)                                        \
                {                                                              \
                        size_t max = q->_max;                                  \
                        q->_max = (q->_max == 0) ? N##_init_size               \
                                                 : q->_max * N##_growth_scale; \
                                                                               \
                        q->_data =                                             \
                            (T *)realloc(q->_data, sizeof(T) * q->_max);       \
                                                                               \
                        if(q->_front > q->_back)                               \
                        {                                                      \
                                size_t first_part = q->_back;                  \
                                size_t second_part = max - q->_front;          \
                                if(first_part > second_part)                   \
                                {                                              \
                                        memcpy(q->_data +                      \
                                                   (q->_max - second_part),    \
                                               q->_data + q->_front,           \
                                               second_part * sizeof(T));       \
                                        q->_front = q->_front + max;           \
                                }                                              \
                                else                                           \
                                {                                              \
                                        memcpy(q->_data + max, q->_data,       \
                                               (1 + first_part) * sizeof(T));  \
                                        q->_back = q->_back + max;             \
                                }                                              \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_push(struct N *q, T el)                                       \
        {                                                                      \
                N##_resize(q);                                                 \
                N##_move(&q->_back, q->_max);                                  \
                N##_element_copy(&q->_data[q->_back], &el);                    \
                ++q->_size;                                                    \
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
                        T *el = &q->_data[q->_front];                          \
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
                        T *el = &q->_data[q->_back];                           \
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
        void N##_pop(struct N *q)                                              \
        {                                                                      \
                if(q->_size)                                                   \
                {                                                              \
                        T *el = &q->_data[q->_front];                          \
                        if(N##_element_copy != N##_flat_copy)                  \
                        {                                                      \
                                N##_element_free(el);                          \
                        }                                                      \
                        N##_move(&q->_front, q->_max);                         \
                        --q->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        int N##_empty(const struct N *const q)                                 \
        {                                                                      \
                return q->_size == 0;                                          \
        }
