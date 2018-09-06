#pragma once

#define INIT_UNORDERED_MAP(K, V, S, N)                                         \
                                                                               \
        struct N##_node                                                        \
        {                                                                      \
		K _key;                                                        \
                V _value;                                                      \
        };                                                                     \
                                                                               \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                struct N##_node *_data[S];                                     \
        };                                                                     \
                                                                               \
        typedef struct N N;                                                    \
                                                                               \
        int N##_is_static()                                                    \
        {                                                                      \
                return 1;                                                      \
        }                                                                      \
	\
	size_t N##_max()\
{\
	return S;\
}\
	\
                                                                               \
        /* =================== */                                              \
        /*  ELEMENT FUNCTIONS  */                                              \
        /* =================== */                                              \
                                                                               \
        void (*N##_element_init)(V *) = V##_init;                              \
                                                                               \
        void N##_set_init(void (*init)(V *))                                   \
        {                                                                      \
                N##_element_init = init;                                       \
        }                                                                      \
                                                                               \
        void (*N##_element_copy)(V *, const V *const) = V##_copy;              \
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
        void (*N##_element_copy_key)(K *, const K *const) = K##_copy;          \
                                                                               \
        void N##_set_copy_key(void (*copy)(K *, const K *const))               \
        {                                                                      \
                N##_element_copy_key = copy;                                   \
        }                                                                      \
                                                                               \
        static void N##_flat_copy_key(K *dst, const K *const src)              \
        {                                                                      \
                *dst = *src;                                                   \
        }                                                                      \
                                                                               \
        void N##_set_share_key(int is_shared)                                  \
        {                                                                      \
                if(is_shared)                                                  \
                {                                                              \
                        N##_set_copy_key(N##_flat_copy_key);                   \
                }                                                              \
                else                                                           \
                {                                                              \
                        N##_set_copy_key(K##_copy);                            \
                }                                                              \
        }                                                                      \
                                                                               \
        int (*N##_element_equal)(const V *const, const V *const) = V##_equal;  \
                                                                               \
        void N##_set_equal(int (*equal)(const V *const, const V *const))       \
        {                                                                      \
                N##_element_equal = equal;                                     \
        }                                                                      \
                                                                               \
        int (*N##_element_equal_key)(const K *const, const K *const) =         \
            K##_equal;                                                         \
                                                                               \
        void N##_set_equal_key(int (*equal)(const K *const, const K *const))   \
        {                                                                      \
                N##_element_equal_key = equal;                                 \
        }                                                                      \
                                                                               \
        size_t (*N##_element_hash)(const K *const) = K##_hash;                 \
                                                                               \
        void N##_set_hash(size_t (*hash)(const K *const))                      \
        {                                                                      \
                N##_element_hash = hash;                                       \
        }                                                                      \
                                                                               \
        void (*N##_element_free_key)(K *) = K##_free;                          \
                                                                               \
        void N##_set_free_key(void (*free)(K *))                               \
        {                                                                      \
                N##_element_free_key = free;                                   \
        }                                                                      \
                                                                               \
        void (*N##_element_free)(V *) = V##_free;                              \
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
		size_t _max;                                                   \
                struct N##_node **_data;                                       \
        };                                                                     \
                                                                               \
        K *N##_iterator_key(struct N##_iterator i)                             \
        {                                                                      \
                return &i._data[i->_curr]->_key;                             \
        }                                                                      \
                                                                               \
        V *N##_iterator_value(struct N##_iterator i)                           \
        {                                                                      \
                return &i._data[i->_curr]->_value;                             \
        }                                                                      \
                                                                               \
        void N##_iterator_next(struct N##_iterator *i)                         \
        {                                                                      \
                if(i->_end < &i->_curr)                                        \
                {                                                              \
			while(i->_curr + 1)
			{
			}
			++i->_curr;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_iterator_begin(struct N *m, struct N##_iterator *i)           \
        {                                                                      \
		i->_curr = i->_data[0];\
		i->_begin = (struct N##_node **)(i->_data);\
		i->_end = (struct N##_node **)(i->_data) + i->_size;\
        }                                                                      \
                                                                               \
        void N##_iterator_cbegin(const struct N *const m,                      \
                                 struct N##_iterator *i)                       \
        {                                                                      \
		i->_curr = i->_data[0];\
		i->_begin = (struct N##_node **)(i->_data);\
		i->_end = (struct N##_node **)(i->_data) + i->_size;\
        }                                                                      \
                                                                               \
        void N##_iterator_prev(struct N##_iterator *i)                         \
        {                                                                      \
                if(i->_curr && i->_data[i->_curr_bucket] != i->_curr)          \
                {                                                              \
                        struct N##_node *curr = i->_data[i->_curr_bucket];     \
                        struct N##_node *next = curr->_next;                   \
                        while(next != i->_curr)                                \
                        {                                                      \
                                curr = next;                                   \
                                next = curr->_next;                            \
                        }                                                      \
                        i->_curr = curr;                                       \
                }                                                              \
                else                                                           \
                {                                                              \
                        struct N##_node *tmp = i->_curr;                       \
                        --i->_curr_bucket;                                     \
                        while(i->_curr_bucket >= 0)                            \
                        {                                                      \
                                i->_curr = i->_data[i->_curr_bucket];          \
                                if(i->_curr)                                   \
                                {                                              \
                                        break;                                 \
                                }                                              \
                                --i->_curr_bucket;                             \
                        }                                                      \
                        if(!i->_curr)                                          \
                        {                                                      \
                                i->_is_valid = 0;                              \
                                i->_curr = tmp;                                \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_iterator_end(struct N *m, struct N##_iterator *i)             \
        {                                                                      \
                if(m->_data)                                                   \
                {                                                              \
                        i->_data = m->_data;                                   \
                        i->_curr = m->_data[m->_max - 1];                      \
                        i->_max = m->_max;                                     \
                        i->_curr_bucket = m->_max - 1;                         \
                        if(i->_curr)                                           \
                        {                                                      \
                                i->_curr = N##_bucket_end(i->_curr);           \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                N##_iterator_prev(i);                          \
                        }                                                      \
                        i->_is_valid = 1;                                      \
                }                                                              \
                else                                                           \
                {                                                              \
                        *i = (struct N##_iterator){NULL, NULL, 0, 0, 0};       \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_iterator_cend(const struct N *const m,                        \
                               struct N##_iterator *i)                         \
        {                                                                      \
                if(m->_data)                                                   \
                {                                                              \
                        i->_data = m->_data;                                   \
                        i->_curr = m->_data[m->_max - 1];                      \
                        i->_max = m->_max;                                     \
                        i->_curr_bucket = m->_max - 1;                         \
                        if(i->_curr)                                           \
                        {                                                      \
                                i->_curr = N##_bucket_end(i->_curr);           \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                N##_iterator_prev(i);                          \
                        }                                                      \
                        i->_is_valid = 1;                                      \
                }                                                              \
                else                                                           \
                {                                                              \
                        *i = (struct N##_iterator){NULL, NULL, 0, 0, 0};       \
                }                                                              \
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
        size_t N##_size(const struct N *const u)                               \
        {                                                                      \
                return u->_size;                                               \
        }                                                                      \
                                                                               \
        void N##_init(struct N *u)                                             \
        {                                                                      \
                u->_size = u->_max = 0;                                        \
                u->_data = NULL;                                               \
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
                                if(!N##_element_equal_key(                     \
                                       &it_first._curr->_key,                  \
                                       &it_second._curr->_key) ||              \
                                   !N##_element_equal(                         \
                                       &it_first._curr->_value,                \
                                       &it_second._curr->_value))              \
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
                if(!src->_data)                                                \
                {                                                              \
                        dst->_data = NULL;                                     \
                        dst->_size = dst->_max = 0;                            \
                        return;                                                \
                }                                                              \
                dst->_size = src->_size;                                       \
                dst->_max = src->_max;                                         \
                dst->_data = (struct N##_node **)malloc(                       \
                    sizeof(struct N##_node *) * dst->_max);                    \
                for(size_t i = 0; i < src->_max; ++i)                          \
                {                                                              \
                        if(src->_data[i])                                      \
                        {                                                      \
                                dst->_data[i] = (struct N##_node *)malloc(     \
                                    sizeof(struct N##_node));                  \
                                N##_element_copy_key(&dst->_data[i]->_key,     \
                                                     &src->_data[i]->_key);    \
                                N##_element_copy(&dst->_data[i]->_value,       \
                                                 &src->_data[i]->_value);      \
                                struct N##_node *curr_src = src->_data[i];     \
                                struct N##_node *curr_dst = dst->_data[i];     \
                                struct N##_node *tmp_src = NULL;               \
                                struct N##_node *tmp_dst = NULL;               \
                                while(curr_src)                                \
                                {                                              \
                                        tmp_src = curr_src->_next;             \
                                        if(!tmp_src)                           \
                                        {                                      \
                                                break;                         \
                                        }                                      \
                                        tmp_dst = (struct N##_node *)malloc(   \
                                            sizeof(struct N##_node));          \
                                        N##_element_copy_key(&tmp_dst->_key,   \
                                                             &tmp_src->_key);  \
                                        N##_element_copy(&tmp_dst->_value,     \
                                                         &tmp_src->_value);    \
                                        curr_dst->_next = tmp_dst;             \
                                        curr_dst = tmp_dst;                    \
                                        curr_src = tmp_src;                    \
                                }                                              \
                                curr_dst->_next = NULL;                        \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                dst->_data[i] = NULL;                          \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_free(struct N *u)                                             \
        {                                                                      \
                if(u->_size)                                                   \
                {                                                              \
                        for(size_t i = 0; i < u->_max; ++i)                    \
                        {                                                      \
                                N##_bucket_free(u->_data[i]);                  \
                        }                                                      \
                }                                                              \
                if(u->_data)                                                   \
                {                                                              \
                        free(u->_data);                                        \
                }                                                              \
        }                                                                      \
                                                                               \
        static struct N##_iterator N##_find_by_hash(                           \
            struct N *u, const K *const k, size_t hash)                        \
        {                                                                      \
                struct N##_iterator ret = {NULL, NULL, 0, 0, 0};               \
                if(u->_max)                                                    \
                {                                                              \
                        size_t position = hash % u->_max;                      \
                        struct N##_node *tmp = u->_data[position];             \
                        if(tmp)                                                \
                        {                                                      \
                                while(tmp)                                     \
                                {                                              \
                                        if(N##_element_equal_key(&tmp->_key,   \
                                                                 k))           \
                                        {                                      \
                                                ret = (struct N##_iterator){   \
                                                    u->_data, tmp, position,   \
                                                    u->_max, 1};               \
                                        }                                      \
                                        tmp = tmp->_next;                      \
                                }                                              \
                        }                                                      \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_find(struct N *u, const K k)                   \
        {                                                                      \
                size_t hash = N##_element_hash(&k);                            \
                return N##_find_by_hash(u, &k, hash);                          \
        }                                                                      \
                                                                               \
        static void N##_rehash_size(const struct N *const u, size_t *max,      \
                                    size_t *new_max)                           \
        {                                                                      \
                *max = u->_max;                                                \
                if(u->_size == *max)                                           \
                {                                                              \
                        *new_max = gc_next_prime(2 * u->_max + 1);             \
                }                                                              \
        }                                                                      \
                                                                               \
	void N##_rehash(struct N *u, size_t new_max)                           \
        {                                                                      \
                struct N##_node **new_data = (struct N##_node **)malloc(       \
                    sizeof(struct N##_node *) * new_max);                      \
                for(size_t i = 0; i < new_max; ++i)                            \
                {                                                              \
                        new_data[i] = NULL;                                    \
                }                                                              \
                                                                               \
                V *value;                                                      \
                size_t position;                                               \
                struct N##_iterator tmp = N##_begin(u);                        \
                struct N##_node *next;                                         \
                for(size_t i = 0; i < u->_size; ++i)                           \
                {                                                              \
                        value = &tmp._curr->_value;                            \
                        position = N##_element_hash(value) % new_max;          \
                        next = tmp._curr->_next;                               \
                        tmp._curr->_next = NULL;                               \
                        if(new_data[position])                                 \
                        {                                                      \
                                N##_bucket_insert(new_data[position],          \
                                                  tmp._curr);                  \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                new_data[position] = tmp._curr;                \
                        }                                                      \
                        if(next)                                               \
                        {                                                      \
                                tmp._curr = next;                              \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                N##_iterator_next(&tmp);                       \
                        }                                                      \
                }                                                              \
                free(u->_data);                                                \
                u->_data = new_data;                                           \
                u->_max = new_max;                                             \
        }                                                                      \
                                                                               \
        static void N##_resize(struct N *u)                                    \
        {                                                                      \
                size_t max, new_max;                                           \
                N##_rehash_size(u, &max, &new_max);                            \
                if(u->_size == max)                                            \
                {                                                              \
                        struct N##_node **new_data =                           \
                            (struct N##_node **)malloc(                        \
                                sizeof(struct N##_node *) * new_max);          \
                        for(size_t i = 0; i < new_max; ++i)                    \
                        {                                                      \
                                new_data[i] = NULL;                            \
                        }                                                      \
                                                                               \
                        K *key;                                                \
                        size_t position;                                       \
                        struct N##_iterator tmp = N##_begin(u);                \
                        struct N##_node *next;                                 \
                        for(size_t i = 0; i < u->_size; ++i)                   \
                        {                                                      \
                                key = &tmp._curr->_key;                        \
                                position = N##_element_hash(key) % new_max;    \
                                next = tmp._curr->_next;                       \
                                tmp._curr->_next = NULL;                       \
                                if(new_data[position])                         \
                                {                                              \
                                        N##_bucket_insert(new_data[position],  \
                                                          tmp._curr);          \
                                }                                              \
                                else                                           \
                                {                                              \
                                        new_data[position] = tmp._curr;        \
                                }                                              \
                                if(next)                                       \
                                {                                              \
                                        tmp._curr = next;                      \
                                }                                              \
                                else                                           \
                                {                                              \
                                        N##_iterator_next(&tmp);               \
                                }                                              \
                        }                                                      \
                        free(u->_data);                                        \
                        u->_data = new_data;                                   \
                        u->_max = new_max;                                     \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_set_at(struct N *u, const K k, const V v)                     \
        {                                                                      \
                size_t hash = N##_element_hash(&k);                            \
                struct N##_iterator i = N##_find_by_hash(u, &k, hash);         \
                if(i._curr)                                                    \
                {                                                              \
                        if(N##_element_copy != N##_flat_copy)                  \
                        {                                                      \
                                N##_element_free(&i._curr->_value);            \
                        }                                                      \
                        N##_element_copy(&i._curr->_value, &v);                \
                }                                                              \
                else                                                           \
                {                                                              \
                        N##_resize(u);                                         \
                        struct N##_node *new_node = N##_node_new(&k, &v);      \
                        size_t position = hash % u->_max;                      \
                        if(u->_data[position])                                 \
                        {                                                      \
                                N##_bucket_insert(u->_data[position],          \
                                                  new_node);                   \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                u->_data[position] = new_node;                 \
                        }                                                      \
                        ++u->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        V *N##_at(struct N *u, const K k)                                      \
        {                                                                      \
                size_t hash = N##_element_hash(&k);                            \
                struct N##_iterator i = N##_find_by_hash(u, &k, hash);         \
                V *ret;                                                        \
                if(i._curr)                                                    \
                {                                                              \
                        ret = &i._curr->_value;                                \
                }                                                              \
                else                                                           \
                {                                                              \
                        N##_resize(u);                                         \
                        V v;                                                   \
                        N##_element_init(&v);                                  \
                        struct N##_node *new_node = N##_node_new(&k, &v);      \
                        size_t position = hash % u->_max;                      \
                        if(u->_data[position])                                 \
                        {                                                      \
                                N##_bucket_insert(u->_data[position],          \
                                                  new_node);                   \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                u->_data[position] = new_node;                 \
                        }                                                      \
                        ++u->_size;                                            \
                        ret = &new_node->_value;                               \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        void N##_erase(struct N *u, const K k)                                 \
        {                                                                      \
                if(u->_data)                                                   \
                {                                                              \
                        size_t hash = N##_element_hash(&k);                    \
                        size_t position = hash % u->_max;                      \
                        u->_data[position] = N##_bucket_remove(                \
                            u->_data[position], &k, &u->_size);                \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_iterator_erase(struct N *u, struct N##_iterator *i)           \
        {                                                                      \
                if(N##_iterator_valid(*i))                                     \
                {                                                              \
                        K key = i->_curr->_key;                                \
                        N##_iterator_next(i);                                  \
                        N##_erase(u, key);                                     \
                }                                                              \
        }                                                                      \
                                                                               \
        int N##_empty(const struct N *const u)                                 \
        {                                                                      \
                return u->_size == 0;                                          \
        }                                                                      \

