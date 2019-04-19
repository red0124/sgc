#pragma once

#ifndef SGC_NODE_STATE
#define SGC_NODE_STATE

enum sgc_node_state
{
        SGC_NODE_STATE_OPEN,
        SGC_NODE_STATE_USED,
        SGC_NODE_STATE_ERASED,
};

#endif

#define SGC_INIT_STATIC_FUNCTIONS_STATIC_UNORDERED_MAP(K, V, S, N)             \
        static struct N##_iterator N##_find_by_hash(                           \
            struct N *u, const K *const k, size_t hash);

#define SGC_INIT_HEADERS_STATIC_UNORDERED_MAP(K, V, S, N)                      \
                                                                               \
        struct N##_pair                                                        \
        {                                                                      \
                K key;                                                         \
                V value;                                                       \
        };                                                                     \
                                                                               \
        struct N##_node                                                        \
        {                                                                      \
                struct N##_pair _data;                                         \
                char _state;                                                   \
        };                                                                     \
                                                                               \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                size_t _shared;                                                \
                size_t _shared_key;                                            \
                struct N##_node _data[S];                                      \
        };                                                                     \
                                                                               \
        typedef struct N N;                                                    \
        typedef struct N##_pair N##_type;                                      \
        typedef V N##_value;                                                   \
        typedef K N##_key;                                                     \
                                                                               \
        size_t N##_max(void);                                                  \
                                                                               \
        struct N##_iterator                                                    \
        {                                                                      \
                size_t _curr;                                                  \
                struct N##_node *_data;                                        \
                int _is_valid;                                                 \
        };                                                                     \
                                                                               \
        const struct N##_pair *N##_iterator_cdata(struct N##_iterator i);      \
        struct N##_pair *N##_iterator_data(struct N##_iterator i);             \
        void N##_iterator_next(struct N##_iterator *i);                        \
        void N##_iterator_begin(struct N *m, struct N##_iterator *i);          \
        void N##_iterator_cbegin(const struct N *const m,                      \
                                 struct N##_iterator *i);                      \
        void N##_iterator_prev(struct N##_iterator *i);                        \
        void N##_iterator_end(struct N *m, struct N##_iterator *i);            \
        void N##_iterator_cend(const struct N *const m,                        \
                               struct N##_iterator *i);                        \
        struct N##_iterator N##_begin(struct N *m);                            \
        struct N##_iterator N##_cbegin(const struct N *const m);               \
        struct N##_iterator N##_end(struct N *m);                              \
        struct N##_iterator N##_cend(const struct N *const m);                 \
        int N##_iterator_equal(const struct N##_iterator first,                \
                               const struct N##_iterator second);              \
        int N##_iterator_valid(const struct N##_iterator i);                   \
                                                                               \
        void N##_set_share(N *u, int is_shared);                               \
        void N##_set_share_key(N *u, int is_shared);                           \
        size_t N##_size(const struct N *const u);                              \
        void N##_init(struct N *u);                                            \
        int N##_equal(const N *const first, const N *const second);            \
        void N##_copy(N *__restrict__ dst, const N *__restrict__ const src);   \
        void N##_free(struct N *u);                                            \
        struct N##_iterator N##_find(struct N *u, const K k);                  \
        void N##_set_at(struct N *u, const K k, const V v);                    \
        V *N##_at(struct N *u, K k);                                           \
        void N##_iterator_erase(struct N *u, struct N##_iterator *i);          \
        void N##_erase(struct N *u, const K k);                                \
        int N##_empty(const struct N *const u);

#define SGC_INIT_STATIC_UNORDERED_MAP(K, V, S, N)                              \
        SGC_INIT_HEADERS_STATIC_UNORDERED_MAP(K, V, S, N);                     \
        SGC_INIT_STATIC_FUNCTIONS_STATIC_UNORDERED_MAP(K, V, S, N);            \
                                                                               \
        size_t N##_max(void)                                                   \
        {                                                                      \
                return S;                                                      \
        }                                                                      \
                                                                               \
        /* ========== */                                                       \
        /*  ITERATOR  */                                                       \
        /* ========== */                                                       \
                                                                               \
        const struct N##_pair *N##_iterator_cdata(struct N##_iterator i)       \
        {                                                                      \
                return &i._data[i._curr]._data;                                \
        }                                                                      \
                                                                               \
        struct N##_pair *N##_iterator_data(struct N##_iterator i)              \
        {                                                                      \
                return &i._data[i._curr]._data;                                \
        }                                                                      \
                                                                               \
        void N##_iterator_next(struct N##_iterator *i)                         \
        {                                                                      \
                size_t curr = i->_curr;                                        \
                while(i->_curr < S - 1 &&                                      \
                      i->_data[i->_curr + 1]._state != SGC_NODE_STATE_USED)    \
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
                if(i->_data[i->_curr]._state != SGC_NODE_STATE_USED)           \
                {                                                              \
                        N##_iterator_next(i);                                  \
                }                                                              \
                i->_is_valid =                                                 \
                    (i->_data[i->_curr]._state != SGC_NODE_STATE_USED) ? 0     \
                                                                       : 1;    \
        }                                                                      \
                                                                               \
        void N##_iterator_cbegin(const struct N *const m,                      \
                                 struct N##_iterator *i)                       \
        {                                                                      \
                i->_curr = 0;                                                  \
                i->_data = (struct N##_node *)(m->_data);                      \
                if(i->_data[i->_curr]._state != SGC_NODE_STATE_USED)           \
                {                                                              \
                        N##_iterator_next(i);                                  \
                }                                                              \
                i->_is_valid =                                                 \
                    (i->_data[i->_curr]._state != SGC_NODE_STATE_USED) ? 0     \
                                                                       : 1;    \
        }                                                                      \
                                                                               \
        void N##_iterator_prev(struct N##_iterator *i)                         \
        {                                                                      \
                size_t curr = i->_curr;                                        \
                while(i->_curr > 1 &&                                          \
                      i->_data[i->_curr - 1]._state != SGC_NODE_STATE_USED)    \
                {                                                              \
                        --i->_curr;                                            \
                }                                                              \
                --i->_curr;                                                    \
                if(i->_curr == 0 &&                                            \
                   i->_data[i->_curr]._state != SGC_NODE_STATE_USED)           \
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
                if(i->_data[i->_curr]._state != SGC_NODE_STATE_USED)           \
                {                                                              \
                        N##_iterator_prev(i);                                  \
                }                                                              \
                i->_is_valid =                                                 \
                    (i->_data[i->_curr]._state != SGC_NODE_STATE_USED) ? 0     \
                                                                       : 1;    \
        }                                                                      \
                                                                               \
        void N##_iterator_cend(const struct N *const m,                        \
                               struct N##_iterator *i)                         \
        {                                                                      \
                i->_curr = S - 1;                                              \
                i->_data = (struct N##_node *)(m->_data);                      \
                if(i->_data[i->_curr]._state != SGC_NODE_STATE_USED)           \
                {                                                              \
                        N##_iterator_prev(i);                                  \
                }                                                              \
                i->_is_valid =                                                 \
                    (i->_data[i->_curr]._state != SGC_NODE_STATE_USED) ? 0     \
                                                                       : 1;    \
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
        /*  MAP FUNCTIONS  */                                                  \
        /* =============== */                                                  \
                                                                               \
        void N##_set_share(N *u, int is_shared)                                \
        {                                                                      \
                u->_shared = is_shared;                                        \
        }                                                                      \
                                                                               \
        void N##_set_share_key(N *u, int is_shared)                            \
        {                                                                      \
                u->_shared_key = is_shared;                                    \
        }                                                                      \
                                                                               \
        size_t N##_size(const struct N *const u)                               \
        {                                                                      \
                return u->_size;                                               \
        }                                                                      \
                                                                               \
        void N##_init(struct N *u)                                             \
        {                                                                      \
                u->_size = 0;                                                  \
                u->_shared = u->_shared_key = 0;                               \
                for(size_t i = 0; i < S; ++i)                                  \
                {                                                              \
                        u->_data[i]._state = SGC_NODE_STATE_OPEN;              \
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
                                if(!K##_equal(                                 \
                                       &N##_iterator_cdata(it_first)->key,     \
                                       &N##_iterator_cdata(it_second)->key) || \
                                   !V##_equal(                                 \
                                       &N##_iterator_cdata(it_first)->value,   \
                                       &N##_iterator_cdata(it_second)->value)) \
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
                dst->_shared = src->_shared;                                   \
                dst->_shared_key = src->_shared_key;                           \
                for(size_t i = 0; i < S; ++i)                                  \
                {                                                              \
                        if(src->_data[i]._state == SGC_NODE_STATE_USED)        \
                        {                                                      \
                                if(!src->_shared_key)                          \
                                {                                              \
                                        K##_copy(&dst->_data[i]._data.key,     \
                                                 &src->_data[i]._data.key);    \
                                }                                              \
                                else                                           \
                                {                                              \
                                        dst->_data[i]._data.key =              \
                                            src->_data[i]._data.key;           \
                                }                                              \
                                                                               \
                                if(!src->_shared)                              \
                                {                                              \
                                        V##_copy(&dst->_data[i]._data.value,   \
                                                 &src->_data[i]._data.value);  \
                                }                                              \
                                else                                           \
                                {                                              \
                                        dst->_data[i]._data.value =            \
                                            src->_data[i]._data.value;         \
                                }                                              \
                        }                                                      \
                        dst->_data[i]._state = src->_data[i]._state;           \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_free(struct N *u)                                             \
        {                                                                      \
                if(u->_size)                                                   \
                {                                                              \
                        for(size_t i = 0; i < S; ++i)                          \
                        {                                                      \
                                if(u->_data[i]._state == SGC_NODE_STATE_USED)  \
                                {                                              \
                                        if(!u->_shared_key)                    \
                                        {                                      \
                                                K##_free(                      \
                                                    &u->_data[i]._data.key);   \
                                        }                                      \
                                        if(!u->_shared)                        \
                                        {                                      \
                                                V##_free(                      \
                                                    &u->_data[i]._data.value); \
                                        }                                      \
                                }                                              \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        static struct N##_iterator N##_find_by_hash(                           \
            struct N *u, const K *const k, size_t hash)                        \
        {                                                                      \
                struct N##_iterator ret = {0, NULL, 0};                        \
                if(u->_size)                                                   \
                {                                                              \
                        size_t position = hash % S;                            \
                        while(u->_data[position]._state !=                     \
                              SGC_NODE_STATE_OPEN)                             \
                        {                                                      \
                                if(u->_data[position]._state ==                \
                                       SGC_NODE_STATE_USED &&                  \
                                   K##_equal(&u->_data[position]._data.key,    \
                                             k))                               \
                                {                                              \
                                        ret = (struct N##_iterator){           \
                                            position,                          \
                                            (struct N##_node *)u->_data, 1};   \
                                        break;                                 \
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
        struct N##_iterator N##_find(struct N *u, const K k)                   \
        {                                                                      \
                size_t hash = K##_hash(&k);                                    \
                return N##_find_by_hash(u, &k, hash);                          \
        }                                                                      \
                                                                               \
        void N##_set_at(struct N *u, const K k, const V v)                     \
        {                                                                      \
                size_t hash = K##_hash(&k);                                    \
                struct N##_iterator i = N##_find_by_hash(u, &k, hash);         \
                if(i._is_valid)                                                \
                {                                                              \
                        if(!u->_shared)                                        \
                        {                                                      \
                                V##_free(&i._data[i._curr]._data.value);       \
                                V##_copy(&i._data[i._curr]._data.value, &v);   \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                i._data[i._curr]._data.value = v;              \
                        }                                                      \
                }                                                              \
                else if(u->_size < S - 1)                                      \
                {                                                              \
                        size_t position = hash % S;                            \
                        while(u->_data[position]._state ==                     \
                              SGC_NODE_STATE_USED)                             \
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
                        if(!u->_shared)                                        \
                        {                                                      \
                                V##_copy(&u->_data[position]._data.value, &v); \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                u->_data[position]._data.value = v;            \
                        }                                                      \
                        if(!u->_shared_key)                                    \
                        {                                                      \
                                K##_copy(&u->_data[position]._data.key, &k);   \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                u->_data[position]._data.key = k;              \
                        }                                                      \
                        u->_data[position]._state = SGC_NODE_STATE_USED;       \
                        ++u->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        V *N##_at(struct N *u, K k)                                            \
        {                                                                      \
                size_t hash = K##_hash(&k);                                    \
                struct N##_iterator i = N##_find_by_hash(u, &k, hash);         \
                V *ret = NULL;                                                 \
                if(i._is_valid)                                                \
                {                                                              \
                        if(u->_shared_key)                                     \
                        {                                                      \
                                K##_free(&k);                                  \
                        }                                                      \
                        ret = &i._data[i._curr]._data.value;                   \
                }                                                              \
                else if(u->_size < S - 1)                                      \
                {                                                              \
                        V v;                                                   \
                        V##_init(&v);                                          \
                        size_t position = hash % S;                            \
                        while(u->_data[position]._state ==                     \
                              SGC_NODE_STATE_USED)                             \
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
                        if(!u->_shared)                                        \
                        {                                                      \
                                V##_copy(&u->_data[position]._data.value, &v); \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                u->_data[position]._data.value = v;            \
                        }                                                      \
                        if(!u->_shared_key)                                    \
                        {                                                      \
                                K##_copy(&u->_data[position]._data.key, &k);   \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                u->_data[position]._data.key = k;              \
                        }                                                      \
                        u->_data[position]._state = SGC_NODE_STATE_USED;       \
                        ++u->_size;                                            \
                        ret = &u->_data[position]._data.value;                 \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        void N##_iterator_erase(struct N *u, struct N##_iterator *i)           \
        {                                                                      \
                if(N##_iterator_valid(*i))                                     \
                {                                                              \
                        K *key = &N##_iterator_data(*i)->key;                  \
                        V *value = &N##_iterator_data(*i)->value;              \
                        i->_data[i->_curr]._state = SGC_NODE_STATE_ERASED;     \
                        N##_iterator_next(i);                                  \
                        if(!u->_shared_key)                                    \
                        {                                                      \
                                K##_free(key);                                 \
                        }                                                      \
                        if(!u->_shared)                                        \
                        {                                                      \
                                V##_free(value);                               \
                        }                                                      \
                        --u->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_erase(struct N *u, const K k)                                 \
        {                                                                      \
                struct N##_iterator i = N##_find(u, k);                        \
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
