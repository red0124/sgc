#pragma once

#include "inc/sgc_allocator.h"
#include "inc/sgc_basic_types.h"
#include "inc/sgc_log.h"
#include "inc/sgc_tree_node.h"
#include "inc/sgc_utils.h"

#define SGC_INIT_STATIC_FUNCTIONS_STATIC_MAP(K, V, S, N)                       \
        static struct N##_node *N##_node_begin(struct N##_node *n);            \
        static struct N##_node *N##_node_end(struct N##_node *n);              \
        static struct N##_node *N##_node_new(struct N *m, const K *const k,    \
                                             const V *const v);                \
        static size_t N##_stack_size(size_t size);                             \
        static int N##_is_left_child(const struct N##_node *const n,           \
                                     const struct N##_node *const parent);     \
        static struct N##_node *N##_sibling(                                   \
            const struct N##_node *const n,                                    \
            const struct N##_node *const parent);                              \
        static void N##_rotate_left(struct N *m, struct N##_node *parent,      \
                                    struct N##_node *gparent);                 \
        static void N##_rotate_right(struct N *m, struct N##_node *parent,     \
                                     struct N##_node *gparent);                \
        static void N##_rotate_left_right(struct N *m, struct N##_node *n,     \
                                          struct N##_node *parent,             \
                                          struct N##_node *gparent);           \
        static void N##_rotate_right_left(struct N *m, struct N##_node *n,     \
                                          struct N##_node *parent,             \
                                          struct N##_node *gparent);           \
        static void N##_rotate(struct N *m, struct N##_node *n,                \
                               struct N##_node *parent,                        \
                               struct N##_node *gparent);                      \
        static void N##_corect_tree(struct N *m, struct N##_node *n,           \
                                    struct N##_node *p, struct N##_node *gp);  \
        static void N##_check_color(struct N *m, struct N##_node *n);          \
        static void N##_insert_node(struct N *m, K *k, V *v);                  \
        static V *N##_insert_or_get_node(struct N *m, K *k);                   \
        static struct N##_node *N##_find_node(struct N *m, K k);               \
        static void N##_erase_rebalanse(struct N *m, struct N##_node *n,       \
                                        struct N##_node *p);                   \
        static struct N##_node *N##_erase_node(struct N *m,                    \
                                               struct N##_node *n);            \
        static struct N##_node *N##_node_alloc(struct N *l);                   \
        static void N##_node_free(struct N *l, struct N##_node *n);

#define SGC_INIT_HEADERS_STATIC_MAP(K, V, S, N)                                \
                                                                               \
        struct N##_pair                                                        \
        {                                                                      \
                K key;                                                         \
                V value;                                                       \
        };                                                                     \
                                                                               \
        struct N##_node                                                        \
        {                                                                      \
                struct N##_node *_parent;                                      \
                struct N##_node *_left;                                        \
                struct N##_node *_right;                                       \
                struct N##_pair _data;                                         \
                enum sgc_map_color _color;                                     \
        };                                                                     \
                                                                               \
        typedef struct N N;                                                    \
        typedef struct N##_pair N##_type;                                      \
        typedef V N##_value;                                                   \
        typedef K N##_key;                                                     \
                                                                               \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                size_t _shared;                                                \
                size_t _shared_key;                                            \
                struct N##_node *_root;                                        \
                struct N##_node _pool[S];                                      \
                struct N##_node *_node_free_list;                              \
        };                                                                     \
                                                                               \
        struct N##_iterator                                                    \
        {                                                                      \
                struct N##_node *_curr;                                        \
                struct N##_node *_next;                                        \
                int _is_valid;                                                 \
        };                                                                     \
        typedef struct N##_iterator N##_iterator;                              \
                                                                               \
        struct N##_pair *N##_iterator_data(struct N##_iterator i);             \
        const struct N##_pair *N##_iterator_cdata(struct N##_iterator i);      \
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
        void N##_set_share(N *m, int is_shared);                               \
        void N##_set_share_key(N *m, int is_shared);                           \
        size_t N##_size(const struct N *const m);                              \
        size_t N##_max();                                                      \
        void N##_init(struct N *m);                                            \
        void N##_free(struct N *m);                                            \
        int N##_equal(const struct N *const first,                             \
                      const struct N *const second);                           \
        void N##_copy(struct N *__restrict__ dst,                              \
                      const struct N *__restrict__ const src);                 \
        void N##_set_at(struct N *m, K k, V v);                                \
        V *N##_at(struct N *m, K k);                                           \
        struct N##_iterator N##_find(struct N *m, K k);                        \
        int N##_erase(struct N *m, const K key);                               \
        int N##_iterator_erase(struct N *m, struct N##_iterator *i);           \
        int N##_empty(const struct N *const m);

#define SGC_INIT_STATIC_MAP(K, V, S, N)                                        \
        SGC_INIT_HEADERS_STATIC_MAP(K, V, S, N);                               \
        SGC_INIT_STATIC_FUNCTIONS_STATIC_MAP(K, V, S, N);                      \
                                                                               \
        /* ================ */                                                 \
        /*  NODE FUNCTIONS  */                                                 \
        /* ================ */                                                 \
                                                                               \
        static struct N##_node *N##_node_alloc(struct N *m)                    \
        {                                                                      \
                struct N##_node *ret = m->_node_free_list;                     \
                if(ret)                                                        \
                {                                                              \
                        m->_node_free_list = m->_node_free_list->_right;       \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        static void N##_node_free(struct N *m, struct N##_node *n)             \
        {                                                                      \
                n->_right = m->_node_free_list;                                \
                m->_node_free_list = n;                                        \
        }                                                                      \
                                                                               \
        static struct N##_node *N##_node_begin(struct N##_node *n)             \
        {                                                                      \
                while(n->_left)                                                \
                {                                                              \
                        n = n->_left;                                          \
                }                                                              \
                return n;                                                      \
        }                                                                      \
                                                                               \
        static struct N##_node *N##_node_end(struct N##_node *n)               \
        {                                                                      \
                while(n->_right)                                               \
                {                                                              \
                        n = n->_right;                                         \
                }                                                              \
                return n;                                                      \
        }                                                                      \
                                                                               \
        static struct N##_node *N##_node_new(struct N *m, const K *const k,    \
                                             const V *const v)                 \
        {                                                                      \
                struct N##_node *n = N##_node_alloc(m);                        \
                                                                               \
                SGC_COPY(K##_copy, n->_data.key, *k, m->_shared_key);          \
                SGC_COPY(V##_copy, n->_data.value, *v, m->_shared);            \
                                                                               \
                n->_left = n->_right = SGC_MAP_LEAF;                           \
                n->_color = SGC_MAP_RED;                                       \
                return n;                                                      \
        }                                                                      \
                                                                               \
        /* ========== */                                                       \
        /*  ITERATOR  */                                                       \
        /* ========== */                                                       \
                                                                               \
        struct N##_pair *N##_iterator_data(struct N##_iterator i)              \
        {                                                                      \
                return &i._curr->_data;                                        \
        }                                                                      \
                                                                               \
        const struct N##_pair *N##_iterator_cdata(struct N##_iterator i)       \
        {                                                                      \
                return &i._curr->_data;                                        \
        }                                                                      \
                                                                               \
        void N##_iterator_next(struct N##_iterator *i)                         \
        {                                                                      \
                if(!i->_next)                                                  \
                {                                                              \
                        i->_is_valid = 0;                                      \
                        return;                                                \
                }                                                              \
                i->_curr = i->_next;                                           \
                if(i->_next->_right)                                           \
                {                                                              \
                        i->_next = N##_node_begin(i->_next->_right);           \
                }                                                              \
                else                                                           \
                {                                                              \
                        struct N##_node *parent = i->_next->_parent;           \
                        while(parent && parent->_right == i->_next)            \
                        {                                                      \
                                i->_next = parent;                             \
                                parent = parent->_parent;                      \
                        }                                                      \
                        if(i->_next->_right != parent)                         \
                        {                                                      \
                                i->_next = parent;                             \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_iterator_begin(struct N *m, struct N##_iterator *i)           \
        {                                                                      \
                i->_curr = SGC_MAP_LEAF;                                       \
                i->_next =                                                     \
                    (m->_root) ? N##_node_begin(m->_root) : SGC_MAP_LEAF;      \
                i->_is_valid = 1;                                              \
                N##_iterator_next(i);                                          \
        }                                                                      \
                                                                               \
        void N##_iterator_cbegin(const struct N *const m,                      \
                                 struct N##_iterator *i)                       \
        {                                                                      \
                i->_curr = SGC_MAP_LEAF;                                       \
                i->_next =                                                     \
                    (m->_root) ? N##_node_begin(m->_root) : SGC_MAP_LEAF;      \
                i->_is_valid = 1;                                              \
                N##_iterator_next(i);                                          \
        }                                                                      \
                                                                               \
        void N##_iterator_prev(struct N##_iterator *i)                         \
        {                                                                      \
                if(!i->_curr)                                                  \
                {                                                              \
                        i->_is_valid = 0;                                      \
                        return;                                                \
                }                                                              \
                i->_next = i->_curr;                                           \
                if(i->_curr->_left)                                            \
                {                                                              \
                        i->_curr = N##_node_end(i->_curr->_left);              \
                }                                                              \
                else                                                           \
                {                                                              \
                        struct N##_node *parent = i->_curr->_parent;           \
                        while(parent && parent->_left == i->_curr)             \
                        {                                                      \
                                i->_curr = parent;                             \
                                parent = parent->_parent;                      \
                        }                                                      \
                        if(i->_curr->_right != parent)                         \
                        {                                                      \
                                i->_curr = parent;                             \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_iterator_end(struct N *m, struct N##_iterator *i)             \
        {                                                                      \
                i->_curr = (m->_root) ? N##_node_end(m->_root) : SGC_MAP_LEAF; \
                i->_next = SGC_MAP_LEAF;                                       \
                i->_is_valid = (i->_curr) ? 1 : 0;                             \
        }                                                                      \
                                                                               \
        void N##_iterator_cend(const struct N *const m,                        \
                               struct N##_iterator *i)                         \
        {                                                                      \
                i->_curr = (m->_root) ? N##_node_end(m->_root) : SGC_MAP_LEAF; \
                i->_next = SGC_MAP_LEAF;                                       \
                i->_is_valid = (i->_curr) ? 1 : 0;                             \
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
        size_t N##_max()                                                       \
        {                                                                      \
                return S;                                                      \
        }                                                                      \
                                                                               \
        void N##_set_share(N *m, int is_shared)                                \
        {                                                                      \
                m->_shared = is_shared;                                        \
        }                                                                      \
                                                                               \
        void N##_set_share_key(N *m, int is_shared)                            \
        {                                                                      \
                m->_shared_key = is_shared;                                    \
        }                                                                      \
                                                                               \
        static size_t N##_stack_size(size_t size)                              \
        {                                                                      \
                size = sgc_log_two(size) + 1;                                  \
                return sizeof(struct N##_node *) * (size * 2);                 \
        }                                                                      \
                                                                               \
        size_t N##_size(const struct N *const m)                               \
        {                                                                      \
                return m->_size;                                               \
        }                                                                      \
                                                                               \
        void N##_init(struct N *m)                                             \
        {                                                                      \
                m->_size = 0;                                                  \
                m->_root = SGC_MAP_LEAF;                                       \
                m->_shared = m->_shared_key = 0;                               \
                m->_node_free_list = m->_pool;                                 \
                m->_node_free_list->_right = NULL;                             \
                for(size_t i = 1; i < S; ++i)                                  \
                {                                                              \
                        struct N##_node *curr = &m->_pool[i];                  \
                        curr->_right = m->_node_free_list;                     \
                        m->_node_free_list = curr;                             \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_free(struct N *m)                                             \
        {                                                                      \
                if(!m->_size)                                                  \
                {                                                              \
                        return;                                                \
                }                                                              \
                struct N##_node **stack =                                      \
                    (struct N##_node **)sgc_malloc(N##_stack_size(m->_size));  \
                                                                               \
                struct N##_node *curr = m->_root;                              \
                struct N##_node *tmp = NULL;                                   \
                                                                               \
                size_t stack_size = 0;                                         \
                while(1)                                                       \
                {                                                              \
                        if(curr != SGC_MAP_LEAF)                               \
                        {                                                      \
                                stack[stack_size++] = curr;                    \
                                curr = curr->_left;                            \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                if(stack_size == 0)                            \
                                {                                              \
                                        break;                                 \
                                }                                              \
                                curr = stack[--stack_size];                    \
                                tmp = curr;                                    \
                                curr = curr->_right;                           \
                                if(!m->_shared)                                \
                                {                                              \
                                        V##_free(&tmp->_data.value);           \
                                }                                              \
                                if(!m->_shared_key)                            \
                                {                                              \
                                        K##_free(&tmp->_data.key);             \
                                }                                              \
                                N##_node_free(m, tmp);                         \
                        }                                                      \
                }                                                              \
                sgc_free(stack);                                               \
                m->_root = SGC_MAP_LEAF;                                       \
                m->_size = 0;                                                  \
        }                                                                      \
                                                                               \
        int N##_equal(const struct N *const first,                             \
                      const struct N *const second)                            \
        {                                                                      \
                int equal = (first == second);                                 \
                if(equal == 0 && first->_size == second->_size)                \
                {                                                              \
                        equal = 1;                                             \
                        struct N##_iterator it_first;                          \
                        N##_iterator_cbegin(first, &it_first);                 \
                                                                               \
                        struct N##_iterator it_second;                         \
                        N##_iterator_cbegin(second, &it_second);               \
                                                                               \
                        for(size_t i = 0; i < first->_size; ++i)               \
                        {                                                      \
                                if((!K##_equal(&it_first._curr->_data.key,     \
                                               &it_second._curr->_data.key) || \
                                    !V##_equal(                                \
                                        &it_first._curr->_data.value,          \
                                        &it_second._curr->_data.value)))       \
                                {                                              \
                                        equal = 0;                             \
                                        break;                                 \
                                }                                              \
                                N##_iterator_next(&it_first);                  \
                                N##_iterator_next(&it_second);                 \
                        }                                                      \
                }                                                              \
                return equal;                                                  \
        }                                                                      \
                                                                               \
        void N##_copy(struct N *__restrict__ dst,                              \
                      const struct N *__restrict__ const src)                  \
        {                                                                      \
                N##_init(dst);                                                 \
                dst->_size = src->_size;                                       \
                dst->_root = SGC_MAP_LEAF;                                     \
                dst->_shared_key = src->_shared_key;                           \
                dst->_shared = src->_shared;                                   \
                                                                               \
                if(src->_size != 0)                                            \
                {                                                              \
                        dst->_root = N##_node_alloc(dst);                      \
                                                                               \
                        SGC_COPY(K##_copy, dst->_root->_data.key,              \
                                 src->_root->_data.key, src->_shared_key);     \
                        SGC_COPY(V##_copy, dst->_root->_data.value,            \
                                 src->_root->_data.value, src->_shared);       \
                                                                               \
                        dst->_root->_color = src->_root->_color;               \
                        dst->_root->_left = dst->_root->_right =               \
                            dst->_root->_parent = SGC_MAP_LEAF;                \
                                                                               \
                        struct N##_node **stack_src =                          \
                            (struct N##_node **)sgc_malloc(                    \
                                N##_stack_size(src->_size));                   \
                                                                               \
                        struct N##_node *curr_src = src->_root;                \
                                                                               \
                        struct N##_node **stack_dst =                          \
                            (struct N##_node **)sgc_malloc(                    \
                                N##_stack_size(dst->_size));                   \
                                                                               \
                        struct N##_node *curr_dst = dst->_root;                \
                                                                               \
                        struct N##_node *tmp = SGC_MAP_LEAF;                   \
                                                                               \
                        stack_src[0] = SGC_MAP_LEAF;                           \
                        stack_dst[0] = SGC_MAP_LEAF;                           \
                                                                               \
                        stack_src[1] = src->_root;                             \
                        stack_dst[1] = dst->_root;                             \
                        size_t stack_size = 2;                                 \
                                                                               \
                        while(stack_size > 0)                                  \
                        {                                                      \
                                if(!((curr_src->_left != SGC_MAP_LEAF &&       \
                                      curr_dst->_left == SGC_MAP_LEAF) ||      \
                                     (curr_src->_right != SGC_MAP_LEAF &&      \
                                      curr_dst->_right == SGC_MAP_LEAF)))      \
                                {                                              \
                                        --stack_size;                          \
                                        curr_src = stack_src[stack_size];      \
                                        curr_dst = stack_dst[stack_size];      \
                                        continue;                              \
                                }                                              \
                                                                               \
                                if(curr_src->_left != SGC_MAP_LEAF &&          \
                                   curr_dst->_left == SGC_MAP_LEAF)            \
                                {                                              \
                                        curr_dst->_left = N##_node_alloc(dst); \
                                        tmp = curr_dst->_left;                 \
                                        tmp->_parent = curr_dst;               \
                                        curr_src = curr_src->_left;            \
                                }                                              \
                                else                                           \
                                {                                              \
                                        curr_dst->_right =                     \
                                            N##_node_alloc(dst);               \
                                        tmp = curr_dst->_right;                \
                                        tmp->_parent = curr_dst;               \
                                        curr_src = curr_src->_right;           \
                                }                                              \
                                tmp->_left = tmp->_right = SGC_MAP_LEAF;       \
                                curr_dst = tmp;                                \
                                SGC_COPY(K##_copy, curr_dst->_data.key,        \
                                         curr_src->_data.key,                  \
                                         src->_shared_key);                    \
                                SGC_COPY(V##_copy, curr_dst->_data.value,      \
                                         curr_src->_data.value, src->_shared); \
                                curr_dst->_color = curr_src->_color;           \
                                stack_src[stack_size] = curr_src;              \
                                stack_dst[stack_size] = curr_dst;              \
                                ++stack_size;                                  \
                        }                                                      \
                                                                               \
                        sgc_free(stack_src);                                   \
                        sgc_free(stack_dst);                                   \
                }                                                              \
        }                                                                      \
                                                                               \
        static int N##_is_left_child(const struct N##_node *const n,           \
                                     const struct N##_node *const parent)      \
        {                                                                      \
                int ret = 0;                                                   \
                if(parent)                                                     \
                {                                                              \
                        ret = (n == parent->_left);                            \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        static struct N##_node *N##_sibling(                                   \
            const struct N##_node *const n,                                    \
            const struct N##_node *const parent)                               \
        {                                                                      \
                struct N##_node *sibling = NULL;                               \
                if(parent != SGC_MAP_LEAF)                                     \
                {                                                              \
                        sibling = (n == parent->_left) ? parent->_right        \
                                                       : parent->_left;        \
                }                                                              \
                return sibling;                                                \
        }                                                                      \
                                                                               \
        static void N##_rotate_left(struct N *m, struct N##_node *parent,      \
                                    struct N##_node *gparent)                  \
        {                                                                      \
                struct N##_node *_left = parent->_left;                        \
                if(gparent)                                                    \
                {                                                              \
                        gparent->_right = _left;                               \
                }                                                              \
                if(_left != SGC_MAP_LEAF)                                      \
                {                                                              \
                        _left->_parent = gparent;                              \
                }                                                              \
                if(gparent == m->_root)                                        \
                {                                                              \
                        m->_root = parent;                                     \
                        parent->_parent = SGC_MAP_LEAF;                        \
                }                                                              \
                else                                                           \
                {                                                              \
                        struct N##_node *ggparent = gparent->_parent;          \
                        parent->_parent = ggparent;                            \
                        if(N##_is_left_child(gparent, ggparent))               \
                        {                                                      \
                                ggparent->_left = parent;                      \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                ggparent->_right = parent;                     \
                        }                                                      \
                }                                                              \
                parent->_left = gparent;                                       \
                gparent->_parent = parent;                                     \
                parent->_color = SGC_MAP_BLACK;                                \
                gparent->_color = SGC_MAP_RED;                                 \
        }                                                                      \
                                                                               \
        static void N##_rotate_right(struct N *m, struct N##_node *parent,     \
                                     struct N##_node *gparent)                 \
        {                                                                      \
                struct N##_node *right = parent->_right;                       \
                gparent->_left = right;                                        \
                if(right != SGC_MAP_LEAF)                                      \
                {                                                              \
                        right->_parent = gparent;                              \
                }                                                              \
                if(gparent == m->_root)                                        \
                {                                                              \
                        m->_root = parent;                                     \
                        parent->_parent = SGC_MAP_LEAF;                        \
                }                                                              \
                else                                                           \
                {                                                              \
                        struct N##_node *ggparent = gparent->_parent;          \
                        parent->_parent = ggparent;                            \
                        if(N##_is_left_child(gparent, ggparent))               \
                        {                                                      \
                                ggparent->_left = parent;                      \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                ggparent->_right = parent;                     \
                        }                                                      \
                }                                                              \
                parent->_right = gparent;                                      \
                gparent->_parent = parent;                                     \
                parent->_color = SGC_MAP_BLACK;                                \
                gparent->_color = SGC_MAP_RED;                                 \
        }                                                                      \
                                                                               \
        static void N##_rotate_left_right(struct N *m, struct N##_node *n,     \
                                          struct N##_node *parent,             \
                                          struct N##_node *gparent)            \
        {                                                                      \
                N##_rotate_left(m, n, parent);                                 \
                N##_rotate_right(m, n, gparent);                               \
        }                                                                      \
                                                                               \
        static void N##_rotate_right_left(struct N *m, struct N##_node *n,     \
                                          struct N##_node *parent,             \
                                          struct N##_node *gparent)            \
        {                                                                      \
                N##_rotate_right(m, n, parent);                                \
                N##_rotate_left(m, n, gparent);                                \
        }                                                                      \
                                                                               \
        static void N##_rotate(struct N *m, struct N##_node *n,                \
                               struct N##_node *parent,                        \
                               struct N##_node *gparent)                       \
        {                                                                      \
                if(N##_is_left_child(n, parent))                               \
                {                                                              \
                        if(N##_is_left_child(parent, gparent))                 \
                        {                                                      \
                                N##_rotate_right(m, parent, gparent);          \
                                n->_color = SGC_MAP_RED;                       \
                                parent->_color = SGC_MAP_BLACK;                \
                                struct N##_node *sibling = parent->_right;     \
                                if(sibling != SGC_MAP_LEAF)                    \
                                {                                              \
                                        sibling->_color = SGC_MAP_RED;         \
                                }                                              \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                N##_rotate_right_left(m, n, parent, gparent);  \
                                n->_color = SGC_MAP_BLACK;                     \
                                n->_right->_color = SGC_MAP_RED;               \
                                n->_left->_color = SGC_MAP_RED;                \
                        }                                                      \
                }                                                              \
                else                                                           \
                {                                                              \
                        if(!N##_is_left_child(parent, gparent))                \
                        {                                                      \
                                N##_rotate_left(m, parent, gparent);           \
                                n->_color = SGC_MAP_RED;                       \
                                parent->_color = SGC_MAP_BLACK;                \
                                struct N##_node *sibling = parent->_right;     \
                                if(sibling != SGC_MAP_LEAF)                    \
                                {                                              \
                                        sibling->_color = SGC_MAP_RED;         \
                                }                                              \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                N##_rotate_left_right(m, n, parent, gparent);  \
                                n->_color = SGC_MAP_BLACK;                     \
                                n->_right->_color = SGC_MAP_RED;               \
                                n->_left->_color = SGC_MAP_RED;                \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        static void N##_corect_tree(struct N *m, struct N##_node *n,           \
                                    struct N##_node *p, struct N##_node *gp)   \
        {                                                                      \
                struct N##_node *u = N##_sibling(p, gp);                       \
                if(u == SGC_MAP_LEAF || u->_color == SGC_MAP_BLACK)            \
                {                                                              \
                        N##_rotate(m, n, p, gp);                               \
                }                                                              \
                else                                                           \
                {                                                              \
                        u->_color = SGC_MAP_BLACK;                             \
                        p->_color = SGC_MAP_BLACK;                             \
                        gp->_color = SGC_MAP_RED;                              \
                }                                                              \
        }                                                                      \
                                                                               \
        static void N##_check_color(struct N *m, struct N##_node *n)           \
        {                                                                      \
                if(n == m->_root)                                              \
                {                                                              \
                        m->_root->_color = SGC_MAP_BLACK;                      \
                        return;                                                \
                }                                                              \
                struct N##_node *p = n->_parent;                               \
                struct N##_node *gp = p->_parent;                              \
                if(p->_color == SGC_MAP_RED && n->_color == SGC_MAP_RED)       \
                {                                                              \
                        N##_corect_tree(m, n, p, gp);                          \
                }                                                              \
                if(gp)                                                         \
                {                                                              \
                        N##_check_color(m, gp);                                \
                }                                                              \
        }                                                                      \
                                                                               \
        static void N##_insert_node(struct N *m, K *k, V *v)                   \
        {                                                                      \
                if(m->_size == S)                                              \
                {                                                              \
                        return;                                                \
                }                                                              \
                struct N##_node *parent = m->_root;                            \
                struct N##_node *new_node = NULL;                              \
                for(;;)                                                        \
                {                                                              \
                        int compare = (K##_compare(&parent->_data.key, k));    \
                                                                               \
                        if(compare > 0)                                        \
                        {                                                      \
                                if(parent->_left == SGC_MAP_LEAF)              \
                                {                                              \
                                        new_node = N##_node_new(m, k, v);      \
                                        parent->_left = new_node;              \
                                        m->_size++;                            \
                                        break;                                 \
                                }                                              \
                                parent = parent->_left;                        \
                        }                                                      \
                        else if(compare < 0)                                   \
                        {                                                      \
                                if(parent->_right == SGC_MAP_LEAF)             \
                                {                                              \
                                        new_node = N##_node_new(m, k, v);      \
                                        parent->_right = new_node;             \
                                        m->_size++;                            \
                                        break;                                 \
                                }                                              \
                                parent = parent->_right;                       \
                        }                                                      \
                        else if(!V##_equal(&parent->_data.value, v))           \
                        {                                                      \
                                SGC_REPLACE(V##_copy, V##_free,                \
                                            parent->_data.value, *v,           \
                                            m->_shared);                       \
                                return;                                        \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                return;                                        \
                        }                                                      \
                }                                                              \
                new_node->_parent = parent;                                    \
                N##_check_color(m, new_node);                                  \
        }                                                                      \
                                                                               \
        void N##_set_at(struct N *m, K k, V v)                                 \
        {                                                                      \
                if(m->_root == SGC_MAP_LEAF)                                   \
                {                                                              \
                        struct N##_node *new_node = N##_node_new(m, &k, &v);   \
                        new_node->_color = SGC_MAP_BLACK;                      \
                        new_node->_parent = SGC_MAP_LEAF;                      \
                        m->_root = new_node;                                   \
                        m->_size = 1;                                          \
                }                                                              \
                else                                                           \
                {                                                              \
                        N##_insert_node(m, &k, &v);                            \
                        m->_root->_color = SGC_MAP_BLACK;                      \
                }                                                              \
        }                                                                      \
                                                                               \
        static V *N##_insert_or_get_node(struct N *m, K *k)                    \
        {                                                                      \
                V new_el;                                                      \
                V *v = &new_el;                                                \
                struct N##_node *parent = m->_root;                            \
                struct N##_node *new_node = NULL;                              \
                for(;;)                                                        \
                {                                                              \
                        int compare = (K##_compare(&parent->_data.key, k));    \
                                                                               \
                        if(compare > 0)                                        \
                        {                                                      \
                                if(parent->_left == SGC_MAP_LEAF)              \
                                {                                              \
                                        V##_init(v);                           \
                                        new_node = N##_node_new(m, k, v);      \
                                        v = &new_node->_data.value;            \
                                        parent->_left = new_node;              \
                                        m->_size++;                            \
                                        new_node->_parent = parent;            \
                                        N##_check_color(m, new_node);          \
                                        break;                                 \
                                }                                              \
                                parent = parent->_left;                        \
                        }                                                      \
                        else if(compare < 0)                                   \
                        {                                                      \
                                if(parent->_right == SGC_MAP_LEAF)             \
                                {                                              \
                                        V##_init(v);                           \
                                        new_node = N##_node_new(m, k, v);      \
                                        v = &new_node->_data.value;            \
                                        parent->_right = new_node;             \
                                        m->_size++;                            \
                                        new_node->_parent = parent;            \
                                        N##_check_color(m, new_node);          \
                                        break;                                 \
                                }                                              \
                                parent = parent->_right;                       \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                v = &parent->_data.value;                      \
                                break;                                         \
                        }                                                      \
                }                                                              \
                return v;                                                      \
        }                                                                      \
                                                                               \
        V *N##_at(struct N *m, K k)                                            \
        {                                                                      \
                V *ret = NULL;                                                 \
                if(m->_root == SGC_MAP_LEAF)                                   \
                {                                                              \
                        V v;                                                   \
                        V##_init(&v);                                          \
                        struct N##_node *new_node = N##_node_new(m, &k, &v);   \
                        new_node->_color = SGC_MAP_BLACK;                      \
                        new_node->_parent = SGC_MAP_LEAF;                      \
                        m->_root = new_node;                                   \
                        m->_size = 1;                                          \
                        ret = &m->_root->_data.value;                          \
                }                                                              \
                else                                                           \
                {                                                              \
                        ret = N##_insert_or_get_node(m, &k);                   \
                        m->_root->_color = SGC_MAP_BLACK;                      \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_find(struct N *m, K k)                         \
        {                                                                      \
                struct N##_iterator ret = {SGC_MAP_LEAF, SGC_MAP_LEAF, 0};     \
                struct N##_node *prev;                                         \
                if(m->_root)                                                   \
                {                                                              \
                        struct N##_node *curr = m->_root;                      \
                        while(curr)                                            \
                        {                                                      \
                                prev = curr;                                   \
                                int compare =                                  \
                                    (K##_compare(&curr->_data.key, &k));       \
                                                                               \
                                if(compare > 0)                                \
                                {                                              \
                                        curr = curr->_left;                    \
                                }                                              \
                                else if(compare < 0)                           \
                                {                                              \
                                        curr = curr->_right;                   \
                                }                                              \
                                else                                           \
                                {                                              \
                                        ret._next = curr;                      \
                                        ret._curr = prev;                      \
                                        ret._is_valid = 1;                     \
                                        N##_iterator_next(&ret);               \
                                        break;                                 \
                                }                                              \
                        }                                                      \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        static struct N##_node *N##_find_node(struct N *m, K k)                \
        {                                                                      \
                struct N##_iterator i = N##_find(m, k);                        \
                return i._curr;                                                \
        }                                                                      \
                                                                               \
        static void N##_erase_rebalanse(struct N *m, struct N##_node *n,       \
                                        struct N##_node *p)                    \
        {                                                                      \
                if(p)                                                          \
                {                                                              \
                        struct N##_node *s;                                    \
                        struct N##_node *r;                                    \
                        if(p->_left == n && p->_right)                         \
                        {                                                      \
                                s = p->_right;                                 \
                                if(s->_color == SGC_MAP_RED)                   \
                                {                                              \
                                        N##_rotate_left(m, s, p);              \
                                        s->_color = SGC_MAP_BLACK;             \
                                        p->_color = SGC_MAP_BLACK;             \
                                        if(p->_right)                          \
                                        {                                      \
                                                p->_right->_color =            \
                                                    SGC_MAP_RED;               \
                                        }                                      \
                                }                                              \
                                else if((!s->_right || s->_right->_color ==    \
                                                           SGC_MAP_BLACK) &&   \
                                        (!s->_left ||                          \
                                         s->_left->_color == SGC_MAP_BLACK))   \
                                {                                              \
                                        s->_color = SGC_MAP_RED;               \
                                        if(p->_color == SGC_MAP_RED)           \
                                        {                                      \
                                                p->_color = SGC_MAP_BLACK;     \
                                        }                                      \
                                        else                                   \
                                        {                                      \
                                                N##_erase_rebalanse(           \
                                                    m, p, p->_parent);         \
                                        }                                      \
                                }                                              \
                                else if(s->_right &&                           \
                                        s->_right->_color == SGC_MAP_RED)      \
                                {                                              \
                                        r = s->_right;                         \
                                        r->_color = SGC_MAP_BLACK;             \
                                        N##_rotate_left(m, s, p);              \
                                }                                              \
                                else if(s->_left &&                            \
                                        s->_left->_color == SGC_MAP_RED)       \
                                {                                              \
                                        r = s->_left;                          \
                                        N##_rotate_right_left(m, r, s, p);     \
                                }                                              \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                s = p->_left;                                  \
                                if(!s)                                         \
                                {                                              \
                                        return;                                \
                                }                                              \
                                if(s->_color == SGC_MAP_RED)                   \
                                {                                              \
                                        N##_rotate_right(m, s, p);             \
                                        s->_color = SGC_MAP_BLACK;             \
                                        p->_color = SGC_MAP_BLACK;             \
                                        if(p->_left)                           \
                                        {                                      \
                                                p->_left->_color =             \
                                                    SGC_MAP_RED;               \
                                        }                                      \
                                }                                              \
                                else if((!s->_right || s->_right->_color ==    \
                                                           SGC_MAP_BLACK) &&   \
                                        (!s->_left ||                          \
                                         s->_left->_color == SGC_MAP_BLACK))   \
                                {                                              \
                                        s->_color = SGC_MAP_RED;               \
                                        N##_erase_rebalanse(m, p, p->_parent); \
                                }                                              \
                                else if(s->_left &&                            \
                                        s->_left->_color == SGC_MAP_RED)       \
                                {                                              \
                                        r = s->_left;                          \
                                        if(r)                                  \
                                        {                                      \
                                                r->_color = SGC_MAP_BLACK;     \
                                        }                                      \
                                        if(p->_color == SGC_MAP_RED)           \
                                        {                                      \
                                                p->_color = SGC_MAP_BLACK;     \
                                        }                                      \
                                        else                                   \
                                        {                                      \
                                                N##_rotate_right(m, s, p);     \
                                        }                                      \
                                }                                              \
                                else if(s->_right &&                           \
                                        s->_right->_color == SGC_MAP_RED)      \
                                {                                              \
                                        r = s->_right;                         \
                                        N##_rotate_left_right(m, r, s, p);     \
                                }                                              \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        static struct N##_node *N##_erase_node(struct N *m,                    \
                                               struct N##_node *n)             \
        {                                                                      \
                struct N##_node *succ;                                         \
                struct N##_node *succ_p;                                       \
                struct N##_node *succ_c = SGC_MAP_LEAF;                        \
                if(!n->_left || !n->_right)                                    \
                {                                                              \
                        succ = n;                                              \
                }                                                              \
                else                                                           \
                {                                                              \
                        succ = n->_right;                                      \
                        if(succ)                                               \
                        {                                                      \
                                while(succ->_left)                             \
                                {                                              \
                                        succ = succ->_left;                    \
                                }                                              \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                succ = n->_left;                               \
                        }                                                      \
                }                                                              \
                if(succ != n)                                                  \
                {                                                              \
                        if(!m->_shared)                                        \
                        {                                                      \
                                V##_free(&n->_data.value);                     \
                                V##_copy(&n->_data.value, &succ->_data.value); \
                                V##_free(&succ->_data.value);                  \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                n->_data.value = succ->_data.value;            \
                        }                                                      \
                        if(!m->_shared_key)                                    \
                        {                                                      \
                                K##_free(&n->_data.key);                       \
                                K##_copy(&n->_data.key, &succ->_data.key);     \
                                K##_free(&succ->_data.key);                    \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                n->_data.key = succ->_data.key;                \
                        }                                                      \
                        /* relinking nodes would be better */                  \
                }                                                              \
                                                                               \
                succ_p = succ->_parent;                                        \
                if(succ->_left)                                                \
                {                                                              \
                        succ_c = succ->_left;                                  \
                        succ_c->_parent = succ_p;                              \
                }                                                              \
                else if(succ->_right)                                          \
                {                                                              \
                        succ_c = succ->_right;                                 \
                        succ_c->_parent = succ_p;                              \
                }                                                              \
                if(succ_p)                                                     \
                {                                                              \
                        if(succ_p->_left == succ)                              \
                        {                                                      \
                                succ_p->_left = succ_c;                        \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                succ_p->_right = succ_c;                       \
                        }                                                      \
                }                                                              \
                else                                                           \
                {                                                              \
                        m->_root = (m->_root->_left) ? m->_root->_left         \
                                                     : m->_root->_right;       \
                }                                                              \
                                                                               \
                if((succ_c && succ_c->_color == SGC_MAP_RED) ||                \
                   succ->_color == SGC_MAP_RED)                                \
                {                                                              \
                        if(succ_c)                                             \
                        {                                                      \
                                succ_c->_color = SGC_MAP_BLACK;                \
                        }                                                      \
                }                                                              \
                else                                                           \
                {                                                              \
                        N##_erase_rebalanse(m, succ_c, succ_p);                \
                }                                                              \
                if(m->_root)                                                   \
                {                                                              \
                        m->_root->_color = SGC_MAP_BLACK;                      \
                }                                                              \
                --m->_size;                                                    \
                return succ;                                                   \
        }                                                                      \
                                                                               \
        int N##_erase(struct N *m, const K key)                                \
        {                                                                      \
                struct N##_node *n = N##_find_node(m, key);                    \
                int ret = (n) ? 1 : 0;                                         \
                if(ret)                                                        \
                {                                                              \
                        N##_node_free(m, N##_erase_node(m, n));                \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        int N##_iterator_erase(struct N *m, struct N##_iterator *i)            \
        {                                                                      \
                struct N##_iterator tmp = {i->_curr, i->_next, i->_is_valid};  \
                N##_iterator_next(&tmp);                                       \
                int ret = i->_is_valid;                                        \
                if(ret)                                                        \
                {                                                              \
                        N##_node_free(m, N##_erase_node(m, i->_curr));         \
                }                                                              \
                i->_curr = tmp._curr;                                          \
                i->_next = tmp._next;                                          \
                i->_is_valid = tmp._is_valid;                                  \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        int N##_empty(const struct N *const m)                                 \
        {                                                                      \
                return m->_size == 0;                                          \
        }