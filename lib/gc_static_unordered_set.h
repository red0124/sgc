#pragma once

#ifndef GC_NODE_STATE
#define GC_NODE_STATE

enum node_state
{
        STATE_OPEN,
        STATE_USED,
        STATE_ERASED,
};

#endif

#define INIT_STATIC_UNORDERED_SET(V, S, N)                                     \
                                                                               \
        struct N##_node                                                        \
        {                                                                      \
                V _value;                                                      \
                char _state;                                                   \
        };                                                                     \
                                                                               \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                struct N##_node _data[S];                                      \
        };                                                                     \
                                                                               \
        typedef struct N N;                                                    \
                                                                               \
        int N##_is_static()                                                    \
        {                                                                      \
                return 1;                                                      \
        }                                                                      \
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
        static void (*N##_element_init)(V *) = V##_init;                       \
                                                                               \
        void N##_set_init(void (*init)(V *))                                   \
        {                                                                      \
                N##_element_init = init;                                       \
        }                                                                      \
                                                                               \
        static void (*N##_element_copy)(V *, const V *const) = V##_copy;       \
                                                                               \
        void N##_set_copy(void (*copy)(V *, const V *const))                   \
        {                                                                      \
                N##_element_copy = copy;                                       \
        }                                                                      \
                                                                               \
        static void N##_flat_copy(V *dst, const V *const src)                  \
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
                        N##_set_copy(V##_copy);                                \
                }                                                              \
        }                                                                      \
                                                                               \
        static int (*N##_element_equal)(const V *const, const V *const) =      \
            V##_equal;                                                         \
                                                                               \
        void N##_set_equal(int (*equal)(const V *const, const V *const))       \
        {                                                                      \
                N##_element_equal = equal;                                     \
        }                                                                      \
                                                                               \
        static size_t (*N##_element_hash)(const V *const) = V##_hash;          \
                                                                               \
        void N##_set_hash(size_t (*hash)(const V *const))                      \
        {                                                                      \
                N##_element_hash = hash;                                       \
        }                                                                      \
                                                                               \
        static void (*N##_element_free)(V *) = V##_free;                       \
                                                                               \
        void N##_set_free(void (*free)(V *))                                   \
        {                                                                      \
                N##_element_free = free;                                       \
        }                                                                      \
                                                                               \
        /* ========== */                                                       \
        /*  ITERATOR  */                                                       \
        /* ========== */                                                       \
                                                                               \
        struct N##_iterator                                                    \
        {                                                                      \
                size_t _curr;                                                  \
                struct N##_node *_data;                                        \
                int _is_valid;                                                 \
        };                                                                     \
                                                                               \
        const V *N##_iterator_cvalue(struct N##_iterator i)                    \
        {                                                                      \
                return &i._data[i._curr]._value;                               \
        }                                                                      \
                                                                               \
        V *N##_iterator_value(struct N##_iterator i)                           \
        {                                                                      \
                return &i._data[i._curr]._value;                               \
        }                                                                      \
                                                                               \
        void N##_iterator_next(struct N##_iterator *i)                         \
        {                                                                      \
                size_t curr = i->_curr;                                        \
                while(i->_curr < S - 1 &&                                      \
                      i->_data[i->_curr + 1]._state != STATE_USED)             \
                {                                                              \
                        ++i->_curr;                                            \
                }                                                              \
                ++i->_curr;                                                    \
                if(i->_curr == S)                                              \
                {                                                              \
                        i->_curr = curr;                                       \
                        i->_is_valid = 0;                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_iterator_begin(struct N *m, struct N##_iterator *i)           \
        {                                                                      \
                i->_curr = 0;                                                  \
                i->_data = (struct N##_node *)(m->_data);                      \
                if(i->_data[i->_curr]._state != STATE_USED)                    \
                {                                                              \
                        N##_iterator_next(i);                                  \
                }                                                              \
                i->_is_valid =                                                 \
                    (i->_data[i->_curr]._state != STATE_USED) ? 0 : 1;         \
        }                                                                      \
                                                                               \
        void N##_iterator_cbegin(const struct N *const m,                      \
                                 struct N##_iterator *i)                       \
        {                                                                      \
                i->_curr = 0;                                                  \
                i->_data = (struct N##_node *)(m->_data);                      \
                if(i->_data[i->_curr]._state != STATE_USED)                    \
                {                                                              \
                        N##_iterator_next(i);                                  \
                }                                                              \
                i->_is_valid =                                                 \
                    (i->_data[i->_curr]._state != STATE_USED) ? 0 : 1;         \
        }                                                                      \
                                                                               \
        void N##_iterator_prev(struct N##_iterator *i)                         \
        {                                                                      \
                size_t curr = i->_curr;                                        \
                while(i->_curr > 1 &&                                          \
                      i->_data[i->_curr - 1]._state != STATE_USED)             \
                {                                                              \
                        --i->_curr;                                            \
                }                                                              \
                --i->_curr;                                                    \
                if(i->_curr == 0 && i->_data[i->_curr]._state != STATE_USED)   \
                {                                                              \
                        i->_curr = curr;                                       \
                        i->_is_valid = 0;                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_iterator_end(struct N *m, struct N##_iterator *i)             \
        {                                                                      \
                i->_curr = S - 1;                                              \
                i->_data = (struct N##_node *)(m->_data);                      \
                if(i->_data[i->_curr]._state != STATE_USED)                    \
                {                                                              \
                        N##_iterator_prev(i);                                  \
                }                                                              \
                i->_is_valid =                                                 \
                    (i->_data[i->_curr]._state != STATE_USED) ? 0 : 1;         \
        }                                                                      \
                                                                               \
        void N##_iterator_cend(const struct N *const m,                        \
                               struct N##_iterator *i)                         \
        {                                                                      \
                i->_curr = S - 1;                                              \
                i->_data = (struct N##_node *)(m->_data);                      \
                if(i->_data[i->_curr]._state != STATE_USED)                    \
                {                                                              \
                        N##_iterator_prev(i);                                  \
                }                                                              \
                i->_is_valid =                                                 \
                    (i->_data[i->_curr]._state != STATE_USED) ? 0 : 1;         \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_begin(struct N *m)                             \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_begin(m, &i);                                     \
                return i;                                                      \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_cbegin(const struct N *const m)                \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_cbegin(m, &i);                                    \
                return i;                                                      \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_end(struct N *m)                               \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_end(m, &i);                                       \
                return i;                                                      \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_cend(const struct N *const m)                  \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_cend(m, &i);                                      \
                return i;                                                      \
        }                                                                      \
                                                                               \
        int N##_iterator_equal(const struct N##_iterator first,                \
                               const struct N##_iterator second)               \
        {                                                                      \
                return first._curr == second._curr;                            \
        }                                                                      \
                                                                               \
        int N##_iterator_valid(const struct N##_iterator i)                    \
        {                                                                      \
                return i._is_valid;                                            \
        }                                                                      \
                                                                               \
        /* =============== */                                                  \
        /*  SET FUNCTIONS  */                                                  \
        /* =============== */                                                  \
                                                                               \
        size_t N##_size(const struct N *const u)                               \
        {                                                                      \
                return u->_size;                                               \
        }                                                                      \
                                                                               \
        void N##_init(struct N *u)                                             \
        {                                                                      \
                u->_size = 0;                                                  \
                for(size_t i = 0; i < S; ++i)                                  \
                {                                                              \
                        u->_data[i]._state = STATE_OPEN;                       \
                }                                                              \
        }                                                                      \
                                                                               \
        int N##_equal(const N *const first, const N *const second)             \
        {                                                                      \
                int equal = (first == second);                                 \
                if(equal == 0 && first->_size == second->_size)                \
                {                                                              \
                        struct N##_iterator it_first = N##_cbegin(first);      \
                        struct N##_iterator it_second = N##_cbegin(second);    \
                        while(N##_iterator_valid(it_first))                    \
                        {                                                      \
                                if(!N##_element_equal(                         \
                                       N##_iterator_cvalue(it_first),          \
                                       N##_iterator_cvalue(it_second)))        \
                                {                                              \
                                        equal = 0;                             \
                                        break;                                 \
                                }                                              \
                                N##_iterator_next(&it_first);                  \
                                N##_iterator_next(&it_second);                 \
                        }                                                      \
                        equal = 1;                                             \
                }                                                              \
                return equal;                                                  \
        }                                                                      \
                                                                               \
        void N##_copy(N *__restrict__ dst, const N *__restrict__ const src)    \
        {                                                                      \
                dst->_size = src->_size;                                       \
                for(size_t i = 0; i < S; ++i)                                  \
                {                                                              \
                        if(src->_data[i]._state == STATE_USED)                 \
                        {                                                      \
                                N##_element_copy(&dst->_data[i]._value,        \
                                                 &src->_data[i]._value);       \
                        }                                                      \
                        dst->_data[i]._state = src->_data[i]._state;           \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_free(struct N *u)                                             \
        {                                                                      \
                if(u->_size && !V##_is_static())                               \
                {                                                              \
                        for(size_t i = 0; i < S; ++i)                          \
                        {                                                      \
                                if(u->_data[i]._state == STATE_USED)           \
                                {                                              \
                                        if(N##_element_copy != N##_flat_copy)  \
                                        {                                      \
                                                N##_element_free(              \
                                                    &u->_data[i]._value);      \
                                        }                                      \
                                }                                              \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        static struct N##_iterator N##_find_by_hash(                           \
            struct N *u, const V *const v, size_t hash)                        \
        {                                                                      \
                struct N##_iterator ret = {0, NULL, 0};                        \
                if(u->_size)                                                   \
                {                                                              \
                        size_t position = hash % S;                            \
                        while(u->_data[position]._state != STATE_OPEN)         \
                        {                                                      \
                                if(u->_data[position]._state == STATE_USED &&  \
                                   N##_element_equal(                          \
                                       &u->_data[position]._value, v))         \
                                {                                              \
                                        ret = (struct N##_iterator){           \
                                            position,                          \
                                            (struct N##_node *)u->_data, 1};   \
                                }                                              \
                                if(position == S - 1)                          \
                                {                                              \
                                        position = 0;                          \
                                }                                              \
                                else                                           \
                                {                                              \
                                        ++position;                            \
                                }                                              \
                        }                                                      \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_find(struct N *u, const V v)                   \
        {                                                                      \
                size_t hash = N##_element_hash(&v);                            \
                return N##_find_by_hash(u, &v, hash);                          \
        }                                                                      \
                                                                               \
        void N##_insert(struct N *u, const V v)                                \
        {                                                                      \
                size_t hash = N##_element_hash(&v);                            \
                struct N##_iterator i = N##_find_by_hash(u, &v, hash);         \
                if(!i._is_valid && u->_size < S - 1)                           \
                {                                                              \
                        size_t position = hash % S;                            \
                        while(u->_data[position]._state == STATE_USED)         \
                        {                                                      \
                                if(position == S - 1)                          \
                                {                                              \
                                        position = 0;                          \
                                }                                              \
                                else                                           \
                                {                                              \
                                        ++position;                            \
                                }                                              \
                        }                                                      \
                        N##_element_copy(&u->_data[position]._value, &v);      \
                        u->_data[position]._state = STATE_USED;                \
                        ++u->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_insert_multiple(struct N *u, const V v)                       \
        {                                                                      \
                if(u->_size < S - 1)                                           \
                {                                                              \
                        size_t position = N##_element_hash(&v) % S;            \
                        while(u->_data[position]._state == STATE_USED)         \
                        {                                                      \
                                if(position == S - 1)                          \
                                {                                              \
                                        position = 0;                          \
                                }                                              \
                                else                                           \
                                {                                              \
                                        ++position;                            \
                                }                                              \
                        }                                                      \
                        N##_element_copy(&u->_data[position]._value, &v);      \
                        u->_data[position]._state = STATE_USED;                \
                        ++u->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_iterator_erase(struct N *u, struct N##_iterator *i)           \
        {                                                                      \
                (void *)(u);                                                   \
                if(N##_iterator_valid(*i))                                     \
                {                                                              \
                        V *value = N##_iterator_value(*i);                     \
                        i->_data[i->_curr]._state = STATE_ERASED;              \
                        N##_iterator_next(i);                                  \
                        if(N##_element_copy != N##_flat_copy)                  \
                        {                                                      \
                                N##_element_free(value);                       \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_erase(struct N *u, const V v)                                 \
        {                                                                      \
                struct N##_iterator i = N##_find(u, v);                        \
                if(i._is_valid)                                                \
                {                                                              \
                        N##_iterator_erase(u, &i);                             \
                }                                                              \
        }                                                                      \
                                                                               \
        int N##_empty(const struct N *const u)                                 \
        {                                                                      \
                return u->_size == 0;                                          \
        }
