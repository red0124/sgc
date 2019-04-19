#pragma once

#ifndef SGC_MAP
#define SGC_MAP
#define SGC_MAP_LEAF NULL
#endif

#ifndef SGC_MAP_COLOR
#define SGC_MAP_COLOR
enum sgc_map_color
{
        SGC_MAP_RED,
        SGC_MAP_BLACK,
};
#endif

#ifndef SGC_MAP_LOG
#define SGC_MAP_LOG
static size_t sgc_exp_two(size_t curr)
{
        size_t power = 1;
        for(size_t i = 0; i < curr; ++i)
        {
                power *= 2;
        }
        return power;
}

static size_t sgc_log_two(size_t size)
{
        size_t curr = 1;
        while(size >= sgc_exp_two(curr))
        {
                ++curr;
        }
        return curr + 1;
}
#endif

#define SGC_INIT_STATIC_FUNCTIONS_SET(V, N)                                    \
        static struct N##_node *N##_node_begin(struct N##_node *n);            \
        static struct N##_node *N##_node_end(struct N##_node *n);              \
        static struct N##_node *N##_node_new(const V *const v,                 \
                                             size_t is_shared);                \
        static size_t N##_stack_size(size_t size);                             \
        static int N##_is_left_child(const struct N##_node *const n,           \
                                     const struct N##_node *const parent);     \
        static struct N##_node *N##_sibling(                                   \
            const struct N##_node *const n,                                    \
            const struct N##_node *const parent);                              \
        static void N##_rotate_left(struct N *s, struct N##_node *parent,      \
                                    struct N##_node *gparent);                 \
        static void N##_rotate_right(struct N *s, struct N##_node *parent,     \
                                     struct N##_node *gparent);                \
        static void N##_rotate_left_right(struct N *s, struct N##_node *n,     \
                                          struct N##_node *parent,             \
                                          struct N##_node *gparent);           \
        static void N##_rotate_right_left(struct N *s, struct N##_node *n,     \
                                          struct N##_node *parent,             \
                                          struct N##_node *gparent);           \
        static void N##_rotate(struct N *s, struct N##_node *n,                \
                               struct N##_node *parent,                        \
                               struct N##_node *gparent);                      \
        static void N##_corect_tree(struct N *s, struct N##_node *n,           \
                                    struct N##_node *p, struct N##_node *gp);  \
        static void N##_check_color(struct N *s, struct N##_node *n);          \
        static void N##_insert_node(struct N *s, V *v);                        \
        static void N##_insert_multiple_node(struct N *s, V *v);               \
        struct N##_iterator N##_find(struct N *s, V v);                        \
        static struct N##_node *N##_find_node(struct N *s, V v);               \
        static void N##_erase_rebalanse(struct N *m, struct N##_node *n,       \
                                        struct N##_node *p);                   \
        static struct N##_node *N##_erase_node(struct N *m, struct N##_node *n);

#define SGC_INIT_HEADERS_SET(V, N)                                             \
                                                                               \
        struct N##_node                                                        \
        {                                                                      \
                struct N##_node *_parent;                                      \
                struct N##_node *_left;                                        \
                struct N##_node *_right;                                       \
                V _value;                                                      \
                enum sgc_map_color _color;                                     \
        };                                                                     \
                                                                               \
        typedef struct N N;                                                    \
        typedef V N##_type;                                                    \
                                                                               \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                size_t _shared;                                                \
                struct N##_node *_root;                                        \
        };                                                                     \
                                                                               \
        void N##_set_share(N *s, int is_shared);                               \
                                                                               \
        struct N##_iterator                                                    \
        {                                                                      \
                struct N##_node *_curr;                                        \
                struct N##_node *_next;                                        \
                int _is_valid;                                                 \
        };                                                                     \
                                                                               \
        V *N##_iterator_data(struct N##_iterator i);                           \
        const V *N##_iterator_cdata(struct N##_iterator i);                    \
        void N##_iterator_next(struct N##_iterator *i);                        \
        void N##_iterator_begin(struct N *s, struct N##_iterator *i);          \
        void N##_iterator_cbegin(const struct N *const s,                      \
                                 struct N##_iterator *i);                      \
        void N##_iterator_prev(struct N##_iterator *i);                        \
        void N##_iterator_end(struct N *s, struct N##_iterator *i);            \
        void N##_iterator_cend(const struct N *const s,                        \
                               struct N##_iterator *i);                        \
        struct N##_iterator N##_begin(struct N *m);                            \
        struct N##_iterator N##_cbegin(const struct N *const m);               \
        struct N##_iterator N##_end(struct N *m);                              \
        struct N##_iterator N##_cend(const struct N *const m);                 \
        int N##_iterator_equal(const struct N##_iterator first,                \
                               const struct N##_iterator second);              \
        int N##_iterator_valid(const struct N##_iterator i);                   \
        size_t N##_size(const struct N *const s);                              \
        void N##_init(struct N *s);                                            \
        void N##_free(struct N *s);                                            \
        int N##_equal(const struct N *const first,                             \
                      const struct N *const second);                           \
        void N##_copy(struct N *__restrict__ dst,                              \
                      const struct N *__restrict__ const src);                 \
        void N##_insert(struct N *s, V v);                                     \
        void N##_insert_multiple(struct N *s, V v);                            \
        int N##_erase(struct N *m, const V value);                             \
        int N##_iterator_erase(struct N *m, struct N##_iterator *i);           \
        int N##_empty(const struct N *const m);

#define SGC_INIT_SET(V, N)                                                     \
        SGC_INIT_HEADERS_SET(V, N);                                            \
        SGC_INIT_STATIC_FUNCTIONS_SET(V, N);                                   \
                                                                               \
        /* ================ */                                                 \
        /*  NODE FUNCTIONS  */                                                 \
        /* ================ */                                                 \
                                                                               \
        void N##_set_share(N *s, int is_shared)                                \
        {                                                                      \
                s->_shared = is_shared;                                        \
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
        static struct N##_node *N##_node_new(const V *const v,                 \
                                             size_t is_shared)                 \
        {                                                                      \
                struct N##_node *n =                                           \
                    (struct N##_node *)malloc(sizeof(struct N##_node));        \
                if(!is_shared)                                                 \
                {                                                              \
                        V##_copy(&n->_value, v);                               \
                }                                                              \
                else                                                           \
                {                                                              \
                        n->_value = *v;                                        \
                }                                                              \
                n->_left = n->_right = SGC_MAP_LEAF;                           \
                n->_color = SGC_MAP_RED;                                       \
                return n;                                                      \
        }                                                                      \
                                                                               \
        /* ========== */                                                       \
        /*  ITERATOR  */                                                       \
        /* ========== */                                                       \
                                                                               \
        V *N##_iterator_data(struct N##_iterator i)                            \
        {                                                                      \
                return &i._curr->_value;                                       \
        }                                                                      \
                                                                               \
        const V *N##_iterator_cdata(struct N##_iterator i)                     \
        {                                                                      \
                return &i._curr->_value;                                       \
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
        void N##_iterator_begin(struct N *s, struct N##_iterator *i)           \
        {                                                                      \
                i->_curr = SGC_MAP_LEAF;                                       \
                i->_next =                                                     \
                    (s->_root) ? N##_node_begin(s->_root) : SGC_MAP_LEAF;      \
                i->_is_valid = 1;                                              \
                N##_iterator_next(i);                                          \
        }                                                                      \
                                                                               \
        void N##_iterator_cbegin(const struct N *const s,                      \
                                 struct N##_iterator *i)                       \
        {                                                                      \
                i->_curr = SGC_MAP_LEAF;                                       \
                i->_next =                                                     \
                    (s->_root) ? N##_node_begin(s->_root) : SGC_MAP_LEAF;      \
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
        void N##_iterator_end(struct N *s, struct N##_iterator *i)             \
        {                                                                      \
                i->_curr = (s->_root) ? N##_node_end(s->_root) : SGC_MAP_LEAF; \
                i->_next = SGC_MAP_LEAF;                                       \
                i->_is_valid = (i->_curr) ? 1 : 0;                             \
        }                                                                      \
                                                                               \
        void N##_iterator_cend(const struct N *const s,                        \
                               struct N##_iterator *i)                         \
        {                                                                      \
                i->_curr = (s->_root) ? N##_node_end(s->_root) : SGC_MAP_LEAF; \
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
        /*  SET FUNCTIONS  */                                                  \
        /* =============== */                                                  \
                                                                               \
        static size_t N##_stack_size(size_t size)                              \
        {                                                                      \
                size = sgc_log_two(size) + 1;                                  \
                return sizeof(struct N##_node *) * (size * 2);                 \
        }                                                                      \
                                                                               \
        size_t N##_size(const struct N *const s)                               \
        {                                                                      \
                return s->_size;                                               \
        }                                                                      \
                                                                               \
        void N##_init(struct N *s)                                             \
        {                                                                      \
                s->_size = 0;                                                  \
                s->_root = SGC_MAP_LEAF;                                       \
                s->_shared = 0;                                                \
        }                                                                      \
                                                                               \
        void N##_free(struct N *s)                                             \
        {                                                                      \
                if(!s->_size)                                                  \
                {                                                              \
                        return;                                                \
                }                                                              \
                struct N##_node **stack =                                      \
                    (struct N##_node **)malloc(N##_stack_size(s->_size));      \
                                                                               \
                struct N##_node *curr = s->_root;                              \
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
                                if(!s->_shared)                                \
                                {                                              \
                                        V##_free(&tmp->_value);                \
                                }                                              \
                                free(tmp);                                     \
                        }                                                      \
                }                                                              \
                free(stack);                                                   \
                s->_root = SGC_MAP_LEAF;                                       \
                s->_size = 0;                                                  \
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
                                if(!V##_equal(&it_first._curr->_value,         \
                                              &it_second._curr->_value))       \
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
                dst->_size = src->_size;                                       \
                dst->_root = SGC_MAP_LEAF;                                     \
                dst->_shared = src->_shared;                                   \
                                                                               \
                if(src->_size != 0)                                            \
                {                                                              \
                        dst->_root = (struct N##_node *)malloc(                \
                            sizeof(struct N##_node));                          \
                                                                               \
                        if(!dst->_shared)                                      \
                        {                                                      \
                                V##_copy(&dst->_root->_value,                  \
                                         &src->_root->_value);                 \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                dst->_root->_value = src->_root->_value;       \
                        }                                                      \
                        dst->_root->_color = src->_root->_color;               \
                        dst->_root->_left = dst->_root->_right =               \
                            dst->_root->_parent = SGC_MAP_LEAF;                \
                                                                               \
                        struct N##_node **stack_src =                          \
                            (struct N##_node **)malloc(                        \
                                N##_stack_size(src->_size));                   \
                                                                               \
                        struct N##_node *curr_src = src->_root;                \
                                                                               \
                        struct N##_node **stack_dst =                          \
                            (struct N##_node **)malloc(                        \
                                N##_stack_size(dst->_size));                   \
                                                                               \
                        struct N##_node *curr_dst = dst->_root;                \
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
                                        curr_dst->_left =                      \
                                            (struct N##_node *)malloc(         \
                                                sizeof(struct N##_node));      \
                                        tmp = curr_dst->_left;                 \
                                        tmp->_parent = curr_dst;               \
                                        curr_src = curr_src->_left;            \
                                }                                              \
                                else                                           \
                                {                                              \
                                        curr_dst->_right =                     \
                                            (struct N##_node *)malloc(         \
                                                sizeof(struct N##_node));      \
                                        tmp = curr_dst->_right;                \
                                        tmp->_parent = curr_dst;               \
                                        curr_src = curr_src->_right;           \
                                }                                              \
                                tmp->_left = tmp->_right = SGC_MAP_LEAF;       \
                                curr_dst = tmp;                                \
                                if(!dst->_shared)                              \
                                {                                              \
                                        V##_copy(&curr_dst->_value,            \
                                                 &curr_src->_value);           \
                                }                                              \
                                else                                           \
                                {                                              \
                                        curr_dst->_value = curr_src->_value;   \
                                }                                              \
                                curr_dst->_color = curr_src->_color;           \
                                stack_src[stack_size] = curr_src;              \
                                stack_dst[stack_size] = curr_dst;              \
                                ++stack_size;                                  \
                        }                                                      \
                                                                               \
                        free(stack_src);                                       \
                        free(stack_dst);                                       \
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
        static void N##_rotate_left(struct N *s, struct N##_node *parent,      \
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
                if(gparent == s->_root)                                        \
                {                                                              \
                        s->_root = parent;                                     \
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
        static void N##_rotate_right(struct N *s, struct N##_node *parent,     \
                                     struct N##_node *gparent)                 \
        {                                                                      \
                struct N##_node *right = parent->_right;                       \
                gparent->_left = right;                                        \
                if(right != SGC_MAP_LEAF)                                      \
                {                                                              \
                        right->_parent = gparent;                              \
                }                                                              \
                if(gparent == s->_root)                                        \
                {                                                              \
                        s->_root = parent;                                     \
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
        static void N##_rotate_left_right(struct N *s, struct N##_node *n,     \
                                          struct N##_node *parent,             \
                                          struct N##_node *gparent)            \
        {                                                                      \
                N##_rotate_left(s, n, parent);                                 \
                N##_rotate_right(s, n, gparent);                               \
        }                                                                      \
                                                                               \
        static void N##_rotate_right_left(struct N *s, struct N##_node *n,     \
                                          struct N##_node *parent,             \
                                          struct N##_node *gparent)            \
        {                                                                      \
                N##_rotate_right(s, n, parent);                                \
                N##_rotate_left(s, n, gparent);                                \
        }                                                                      \
                                                                               \
        static void N##_rotate(struct N *s, struct N##_node *n,                \
                               struct N##_node *parent,                        \
                               struct N##_node *gparent)                       \
        {                                                                      \
                if(N##_is_left_child(n, parent))                               \
                {                                                              \
                        if(N##_is_left_child(parent, gparent))                 \
                        {                                                      \
                                N##_rotate_right(s, parent, gparent);          \
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
                                N##_rotate_right_left(s, n, parent, gparent);  \
                                n->_color = SGC_MAP_BLACK;                     \
                                n->_right->_color = SGC_MAP_RED;               \
                                n->_left->_color = SGC_MAP_RED;                \
                        }                                                      \
                }                                                              \
                else                                                           \
                {                                                              \
                        if(!N##_is_left_child(parent, gparent))                \
                        {                                                      \
                                N##_rotate_left(s, parent, gparent);           \
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
                                N##_rotate_left_right(s, n, parent, gparent);  \
                                n->_color = SGC_MAP_BLACK;                     \
                                n->_right->_color = SGC_MAP_RED;               \
                                n->_left->_color = SGC_MAP_RED;                \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        static void N##_corect_tree(struct N *s, struct N##_node *n,           \
                                    struct N##_node *p, struct N##_node *gp)   \
        {                                                                      \
                struct N##_node *u = N##_sibling(p, gp);                       \
                if(u == SGC_MAP_LEAF || u->_color == SGC_MAP_BLACK)            \
                {                                                              \
                        N##_rotate(s, n, p, gp);                               \
                }                                                              \
                else                                                           \
                {                                                              \
                        u->_color = SGC_MAP_BLACK;                             \
                        p->_color = SGC_MAP_BLACK;                             \
                        gp->_color = SGC_MAP_RED;                              \
                }                                                              \
        }                                                                      \
                                                                               \
        static void N##_check_color(struct N *s, struct N##_node *n)           \
        {                                                                      \
                if(n == s->_root)                                              \
                {                                                              \
                        s->_root->_color = SGC_MAP_BLACK;                      \
                        return;                                                \
                }                                                              \
                struct N##_node *p = n->_parent;                               \
                struct N##_node *gp = p->_parent;                              \
                if(p->_color == SGC_MAP_RED && n->_color == SGC_MAP_RED)       \
                {                                                              \
                        N##_corect_tree(s, n, p, gp);                          \
                }                                                              \
                if(gp)                                                         \
                {                                                              \
                        N##_check_color(s, gp);                                \
                }                                                              \
        }                                                                      \
                                                                               \
        static void N##_insert_node(struct N *s, V *v)                         \
        {                                                                      \
                struct N##_node *parent = s->_root;                            \
                struct N##_node *new_node = NULL;                              \
                for(;;)                                                        \
                {                                                              \
                        int compare = (V##_compare(&parent->_value, v));       \
                                                                               \
                        if(compare > 0)                                        \
                        {                                                      \
                                if(parent->_left == SGC_MAP_LEAF)              \
                                {                                              \
                                        new_node =                             \
                                            N##_node_new(v, s->_shared);       \
                                        parent->_left = new_node;              \
                                        s->_size++;                            \
                                        break;                                 \
                                }                                              \
                                parent = parent->_left;                        \
                        }                                                      \
                        else if(compare < 0)                                   \
                        {                                                      \
                                if(parent->_right == SGC_MAP_LEAF)             \
                                {                                              \
                                        new_node =                             \
                                            N##_node_new(v, s->_shared);       \
                                        parent->_right = new_node;             \
                                        s->_size++;                            \
                                        break;                                 \
                                }                                              \
                                parent = parent->_right;                       \
                        }                                                      \
                        else if(!V##_equal(&parent->_value, v))                \
                        {                                                      \
                                if(!s->_shared)                                \
                                {                                              \
                                        V##_free(&parent->_value);             \
                                        V##_copy(&parent->_value, v);          \
                                }                                              \
                                else                                           \
                                {                                              \
                                        parent->_value = *v;                   \
                                }                                              \
                                return;                                        \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                return;                                        \
                        }                                                      \
                }                                                              \
                new_node->_parent = parent;                                    \
                N##_check_color(s, new_node);                                  \
        }                                                                      \
                                                                               \
        void N##_insert(struct N *s, V v)                                      \
        {                                                                      \
                if(s->_root == SGC_MAP_LEAF)                                   \
                {                                                              \
                        struct N##_node *new_node =                            \
                            N##_node_new(&v, s->_shared);                      \
                        new_node->_color = SGC_MAP_BLACK;                      \
                        new_node->_parent = SGC_MAP_LEAF;                      \
                        s->_root = new_node;                                   \
                        s->_size = 1;                                          \
                }                                                              \
                else                                                           \
                {                                                              \
                        N##_insert_node(s, &v);                                \
                }                                                              \
        }                                                                      \
                                                                               \
        static void N##_insert_multiple_node(struct N *s, V *v)                \
        {                                                                      \
                struct N##_node *parent = s->_root;                            \
                struct N##_node *new_node = NULL;                              \
                for(;;)                                                        \
                {                                                              \
                        int compare = (V##_compare(&parent->_value, v));       \
                                                                               \
                        if(compare > 0)                                        \
                        {                                                      \
                                if(parent->_left == SGC_MAP_LEAF)              \
                                {                                              \
                                        new_node =                             \
                                            N##_node_new(v, s->_shared);       \
                                        parent->_left = new_node;              \
                                        s->_size++;                            \
                                        break;                                 \
                                }                                              \
                                parent = parent->_left;                        \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                if(parent->_right == SGC_MAP_LEAF)             \
                                {                                              \
                                        new_node =                             \
                                            N##_node_new(v, s->_shared);       \
                                        parent->_right = new_node;             \
                                        s->_size++;                            \
                                        break;                                 \
                                }                                              \
                                parent = parent->_right;                       \
                        }                                                      \
                }                                                              \
                new_node->_parent = parent;                                    \
                N##_check_color(s, new_node);                                  \
        }                                                                      \
                                                                               \
        void N##_insert_multiple(struct N *s, V v)                             \
        {                                                                      \
                if(s->_root == SGC_MAP_LEAF)                                   \
                {                                                              \
                        struct N##_node *new_node =                            \
                            N##_node_new(&v, s->_shared);                      \
                        new_node->_color = SGC_MAP_BLACK;                      \
                        new_node->_parent = SGC_MAP_LEAF;                      \
                        s->_root = new_node;                                   \
                        s->_size = 1;                                          \
                }                                                              \
                else                                                           \
                {                                                              \
                        N##_insert_multiple_node(s, &v);                       \
                }                                                              \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_find(struct N *s, V v)                         \
        {                                                                      \
                struct N##_iterator ret = {SGC_MAP_LEAF, SGC_MAP_LEAF, 0};     \
                struct N##_node *prev;                                         \
                if(s->_root)                                                   \
                {                                                              \
                        struct N##_node *curr = s->_root;                      \
                        while(curr)                                            \
                        {                                                      \
                                prev = curr;                                   \
                                int compare =                                  \
                                    (V##_compare(&curr->_value, &v));          \
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
        static struct N##_node *N##_find_node(struct N *s, V v)                \
        {                                                                      \
                struct N##_iterator i = N##_find(s, v);                        \
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
                                else if(s->_left &&                            \
                                        s->_left->_color == SGC_MAP_RED)       \
                                {                                              \
                                        r = s->_left;                          \
                                        if(r)                                  \
                                        {                                      \
                                                r->_color = SGC_MAP_BLACK;     \
                                        }                                      \
                                        N##_rotate_right(m, s, p);             \
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
                        V##_copy(&n->_value, &succ->_value);                   \
                        if(!m->_shared)                                        \
                        {                                                      \
                                V##_free(&succ->_value);                       \
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
        int N##_erase(struct N *m, const V value)                              \
        {                                                                      \
                struct N##_node *n = N##_find_node(m, value);                  \
                int ret = (n) ? 1 : 0;                                         \
                if(ret)                                                        \
                {                                                              \
                        if(!m->_shared)                                        \
                        {                                                      \
                                V##_free(&n->_value);                          \
                        }                                                      \
                        free(N##_erase_node(m, n));                            \
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
                        if(!m->_shared)                                        \
                        {                                                      \
                                V##_free(&i->_curr->_value);                   \
                        }                                                      \
                        free(N##_erase_node(m, i->_curr));                     \
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
