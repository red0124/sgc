#define INIT_VECTOR(name)                                                      \
                                                                               \
        struct vector_##name                                                   \
        {                                                                      \
                int _vector_size;                                              \
                int _vector_max;                                               \
                name *_vector_elements;                                        \
        };                                                                     \
                                                                               \
        typedef struct vector_##name vector_##name;                            \
                                                                               \
        void vec_init_##name(vector_##name *vec)                               \
        {                                                                      \
                vec->_vector_size = 0;                                         \
                vec->_vector_max = 1;                                          \
                vec->_vector_elements = malloc(sizeof(name));                  \
        }                                                                      \
                                                                               \
        void vec_free_##name(vector_##name *vec)                               \
        {                                                                      \
                vec->_vector_size = 0;                                         \
                vec->_vector_max = 0;                                          \
                free(vec->_vector_elements);                                   \
        }                                                                      \
                                                                               \
        int vec_set_##name(vector_##name *vec, int num, name el)               \
        {                                                                      \
                int ret = 0;                                                   \
                if(num < vec->_vector_size)                                    \
                {                                                              \
                        (vec->_vector_elements)[num] = el;                     \
                        ret = 1;                                               \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        void vec_push_back_##name(vector_##name *vec, name el)                 \
        {                                                                      \
                if(vec->_vector_max == vec->_vector_size)                      \
                {                                                              \
                        vec->_vector_max = vec->_vector_size * 2;              \
                        vec->_vector_elements =                                \
                            realloc(vec->_vector_elements,                     \
                                    vec->_vector_max * sizeof(name));          \
                }                                                              \
                (vec->_vector_elements)[vec->_vector_size] = el;               \
                vec->_vector_size++;                                           \
        }                                                                      \
                                                                               \
        name vec_pop_back_##name(vector_##name *vec)                           \
        {                                                                      \
                return (vec->_vector_elements)[--vec->_vector_size];           \
        }                                                                      \
                                                                               \
        name vec_get_##name(vector_##name *vec, int num)                       \
        {                                                                      \
                name ret;                                                      \
                if(num < vec->_vector_size && num >= 0)                        \
                {                                                              \
                        ret = (vec->_vector_elements)[num];                    \
                }                                                              \
                else                                                           \
                {                                                              \
                        ret = (vec->_vector_elements)[vec->_vector_size - 1];  \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
        int vec_insert_##name(vector_##name *vec, int num, name el)            \
        {                                                                      \
                int ret = 0;                                                   \
                vec_push_back_##name(vec, el);                                 \
                if(num < vec->_vector_size && num >= 0)                        \
                {                                                              \
                        ret = 1;                                               \
                        for(int i = vec->_vector_size - 1; i > num; i--)       \
                        {                                                      \
                                (vec->_vector_elements)[i] =                   \
                                    (vec->_vector_elements)[i - 1];            \
                        }                                                      \
                        (vec->_vector_elements)[num] = el;                     \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        int vec_erase_##name(vector_##name *vec, int num)                      \
        {                                                                      \
                int ret = 0;                                                   \
                if(num < vec->_vector_size && num >= 0)                        \
                {                                                              \
                        ret = 1;                                               \
                        for(int i = num; i < vec->_vector_size - 1; i++)       \
                        {                                                      \
                                (vec->_vector_elements)[i] =                   \
                                    (vec->_vector_elements)[i + 1];            \
                        }                                                      \
                        vec->_vector_size--;                                   \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        int vec_find_##name(vector_##name *vec, name el)                       \
        {                                                                      \
                int ret = -1;                                                  \
                for(int i = 0; i < vec->_vector_size; i++)                     \
                {                                                              \
                        if((vec->_vector_elements)[i] == el)                   \
                        {                                                      \
                                ret = i;                                       \
                                break;                                         \
                        }                                                      \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
        int vec_size_##name(vector_##name *vec)                                \
        {                                                                      \
                return vec->_vector_size;                                      \
        }
