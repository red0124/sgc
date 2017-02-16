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
        int vec_set_##type_name(vector_##type_name *vec, const int num,        \
                                const type_name el)                            \
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
        void vec_push_back_##type_name(vector_##type_name *vec,                \
                                       const type_name el)                     \
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
        type_name vec_get_##type_name(const vector_##type_name *vec,           \
                                      const int num)                           \
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
        int vec_insert_##type_name(vector_##type_name *vec, const int num,     \
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
        int vec_size_##type_name(vector_##type_name *vec)                      \
        {                                                                      \
                return vec->_vector_size;                                      \
        }                                                                      \
                                                                               \
        int vec_copy_interval_##type_name(vector_##type_name *to,              \
                                          const vector_##type_name *from,      \
                                          const int x, const int y)            \
        {                                                                      \
                int begin = (x > y) ? y : x;                                   \
                begin = (begin > 0) ? begin : 0;                               \
                int end = (x > y) ? x : y;                                     \
                end = (end < from->_vector_size) ? end : from->_vector_size;   \
                for(int i = begin; i < end && i < from->_vector_size; i++)     \
                {                                                              \
                        vec_push_back_##type_name(                             \
                            to, (from->_vector_elements)[i]);                  \
                }                                                              \
                return (x > from->_vector_size || x < 0 ||                     \
                        y > from->_vector_size || y < 0)                       \
                           ? 1                                                 \
                           : 0;                                                \
        }                                                                      \
                                                                               \
        int vec_copy_##type_name(vector_##type_name *to,                       \
                                 const vector_##type_name *from)               \
        {                                                                      \
                return vec_copy_interval_##type_name(to, from, 0,              \
                                                     from->_vector_size);      \
        }                                                                      \
                                                                               \
        int vec_erase_interval_##type_name(vector_##type_name *vec,            \
                                           const int x, const int y)           \
        {                                                                      \
                int begin = (x > y) ? y : x;                                   \
                begin = (begin > 0) ? begin : 0;                               \
                int end = (x > y) ? x : y;                                     \
                end = (end < vec->_vector_size) ? end : vec->_vector_size;     \
                                                                               \
                for(int i = begin; i < vec->_vector_size - (end - begin); i++) \
                {                                                              \
                        (vec->_vector_elements)[i] =                           \
                            (vec->_vector_elements)[i + (end - begin)];        \
                }                                                              \
                vec->_vector_size -= end - begin;                              \
                                                                               \
                return (x > vec->_vector_size || x < 0 ||                      \
                        y > vec->_vector_size || y < 0)                        \
                           ? 1                                                 \
                           : 0;                                                \
        }                                                                      \
                                                                               \
        int vec_erase_##type_name(vector_##type_name *vec, const int num)      \
        {                                                                      \
                return vec_erase_interval_##type_name(vec, num, num + 1);      \
        }                                                                      \
                                                                               \
        void swap_##type_name(type_name *a, type_name *b)                      \
        {                                                                      \
                type_name tmp = *a;                                            \
                *a = *b;                                                       \
                *b = tmp;                                                      \
        }                                                                      \
                                                                               \
        void vec_print_##type_name(vector_##type_name *vec,                    \
                                   void (*print)(const type_name))             \
        {                                                                      \
                for(int i = 0; i < vec->_vector_size; i++)                     \
                {                                                              \
                        print(vec->_vector_elements[i]);                       \
                }                                                              \
        }                                                                      \
                                                                               \
        int vec_count_##type_name(vector_##type_name *vec,                     \
                                  int (*condition)(type_name))                 \
        {                                                                      \
                int ret = 0;                                                   \
                for(int i = 0; i < vec->_vector_size; i++)                     \
                {                                                              \
                        ret = (condition(vec->_vector_elements[i])) ? ret + 1  \
                                                                    : ret;     \
                }                                                              \
                                                                               \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        type_name *vec_next_##type_name(                                       \
            vector_##type_name *vec, int (*condition)(type_name), int begin)   \
        {                                                                      \
                type_name *ret = NULL;                                         \
                for(int i = begin; i < vec->_vector_size && ret == NULL; i++)  \
                {                                                              \
                        if(condition(vec->_vector_elements[i]))                \
                        {                                                      \
                                ret = &vec->_vector_elements[i];               \
                        }                                                      \
                }                                                              \
                                                                               \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        int vec_group_##type_name(vector_##type_name *vec,                     \
                                  int (*condition)(type_name))                 \
        {                                                                      \
                int i;                                                         \
                for(i = 0; vec_next_##type_name(vec, condition, i) != NULL;    \
                    i++)                                                       \
                {                                                              \
                        swap_##type_name(                                      \
                            &vec->_vector_elements[i],                         \
                            vec_next_##type_name(vec, condition, i));          \
                }                                                              \
                                                                               \
                return i;                                                      \
        }                                                                      \
                                                                               \
        void vec_sort_interval_##type_name(                                    \
            vector_##type_name *vec, int (*condition)(type_name, type_name),   \
            const int x, const int y)                                          \
        {                                                                      \
                int begin = (x > y) ? y : x;                                   \
                begin = (begin > 0) ? begin : 0;                               \
                int end = (x > y) ? x : y;                                     \
                end = (end < vec->_vector_size) ? end : vec->_vector_size;     \
                                                                               \
                int finished = 0;                                              \
                while(!finished)                                               \
                {                                                              \
                        finished = 1;                                          \
                        for(int i = begin; i < end - 1; i++)                   \
                        {                                                      \
                                if(condition((vec->_vector_elements[i]),       \
                                             (vec->_vector_elements[i + 1])))  \
                                {                                              \
                                        swap_##type_name(                      \
                                            &(vec->_vector_elements)[i],       \
                                            &(vec->_vector_elements)[i + 1]);  \
                                        finished = 0;                          \
                                }                                              \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void vec_sort_##type_name(vector_##type_name *vec,                     \
                                  int (*condition)(type_name, type_name))      \
        {                                                                      \
                vec_sort_interval_##type_name(vec, condition, 0,               \
                                              vec->_vector_size);              \
        }
