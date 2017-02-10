#define INIT_VECTOR(type_name)                                                 \
                                                                               \
        struct vector_##type_name                                              \
        {                                                                      \
                int _vector_size;                                              \
                int _vector_max;                                               \
                type_name *_vector_elements;                                   \
        };                                                                     \
                                                                               \
        typedef struct vector_##type_name vector_##type_name;                  \
                                                                               \
        void vec_init_##type_name(vector_##type_name *vec)                     \
        {                                                                      \
                vec->_vector_size = 0;                                         \
                vec->_vector_max = 1;                                          \
                vec->_vector_elements = malloc(sizeof(type_name));             \
        }                                                                      \
                                                                               \
        void vec_free_##type_name(vector_##type_name *vec)                     \
        {                                                                      \
                vec->_vector_size = 0;                                         \
                vec->_vector_max = 0;                                          \
                free(vec->_vector_elements);                                   \
        }                                                                      \
                                                                               \
        int vec_set_##type_name(vector_##type_name *vec, int num,              \
                                type_name el)                                  \
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
        void vec_push_back_##type_name(vector_##type_name *vec, type_name el)  \
        {                                                                      \
                if(vec->_vector_max == vec->_vector_size)                      \
                {                                                              \
                        vec->_vector_max = vec->_vector_size * 2;              \
                        vec->_vector_elements =                                \
                            realloc(vec->_vector_elements,                     \
                                    vec->_vector_max * sizeof(type_name));     \
                }                                                              \
                (vec->_vector_elements)[vec->_vector_size] = el;               \
                vec->_vector_size++;                                           \
        }                                                                      \
                                                                               \
        type_name vec_pop_back_##type_name(vector_##type_name *vec)            \
        {                                                                      \
                return (vec->_vector_elements)[--vec->_vector_size];           \
        }                                                                      \
                                                                               \
        type_name vec_get_##type_name(vector_##type_name *vec, int num)        \
        {                                                                      \
                type_name ret;                                                 \
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
        int vec_insert_##type_name(vector_##type_name *vec, int num,           \
                                   type_name el)                               \
        {                                                                      \
                int ret = 0;                                                   \
                vec_push_back_##type_name(vec, el);                            \
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
        int vec_erase_##type_name(vector_##type_name *vec, int num)            \
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
        int vec_find_##type_name(vector_##type_name *vec, type_name el)        \
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
        int vec_size_##type_name(vector_##type_name *vec)                      \
        {                                                                      \
                return vec->_vector_size;                                      \
        }
