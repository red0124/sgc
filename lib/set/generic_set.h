#pragma once

#ifndef MAP_LEAF
#define MAP_LEAF NULL
#endif

#ifndef MAP_RB_COLOR
#define MAP_RB_COLOR
enum map_color
{
        MAP_RED,
        MAP_BLACK,
};
#endif

#define INIT_SET(V, N)                                                         \
                                                                               \
        struct N##_node                                                        \
        {                                                                      \
                struct N##_node *_parent;                                      \
                struct N##_node *_left;                                        \
                struct N##_node *_right;                                       \
                V _value;                                                      \
                enum map_color _color;                                         \
        };                                                                     \
                                                                               \
        typedef struct N N;                                                    \
                                                                               \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                struct N##_node *_root;                                        \
        };                                                                     \
                                                                               \
        /* ================ */                                                 \
        /*  NODE FUNCTIONS  */                                                 \
        /* ================ */                                                 \
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
        int N##_is_static()                                                    \
        {                                                                      \
                return 0;                                                      \
        }                                                                      \
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
        int (*N##_element_equal)(const V *const, const V *const) = V##_equal;  \
                                                                               \
        void N##_set_equal(int (*equal)(const V *const, const V *const))       \
        {                                                                      \
                N##_element_equal = equal;                                     \
        }                                                                      \
                                                                               \
        int (*N##_element_compare)(const V *const, const V *const) =           \
            V##_compare;                                                       \
                                                                               \
        void N##_set_compare(int (*compare)(const V *const, const V *const))   \
        {                                                                      \
                N##_element_compare = compare;                                 \
        }                                                                      \
                                                                               \
        void (*N##_element_free)(V *) = V##_free;                              \
                                                                               \
        void N##_set_free(void (*free)(V *))                                   \
        {                                                                      \
                N##_element_free = free;                                       \
        }                                                                      \
                                                                               \
        static struct N##_node *N##_node_new(const V *const v)                 \
        {                                                                      \
                struct N##_node *n =                                           \
                    (struct N##_node *)malloc(sizeof(struct N##_node));        \
                N##_element_copy(&n->_value, v);                               \
                n->_left = n->_right = MAP_LEAF;                               \
                n->_color = MAP_RED;                                           \
                return n;                                                      \
        }                                                                      \
                                                                               \
        /* ========== */                                                       \
        /*  ITERATOR  */                                                       \
        /* ========== */                                                       \
                                                                               \
        struct N##_iterator                                                    \
        {                                                                      \
                struct N##_node *curr;                                         \
                struct N##_node *next;                                         \
        };                                                                     \
                                                                               \
        V *N##_iterator_value(struct N##_iterator i)                           \
        {                                                                      \
                return &i.curr->_value;                                        \
        }                                                                      \
                                                                               \
        void N##_iterator_next(struct N##_iterator *i)                         \
        {                                                                      \
                if(!i->next)                                                   \
                {                                                              \
                        return;                                                \
                }                                                              \
                i->curr = i->next;                                             \
                if(i->next->_right)                                            \
                {                                                              \
                        i->next = N##_node_begin(i->next->_right);             \
                }                                                              \
                else                                                           \
                {                                                              \
                        struct N##_node *parent = i->next->_parent;            \
                        while(parent && parent->_right == i->next)             \
                        {                                                      \
                                i->next = parent;                              \
                                parent = parent->_parent;                      \
                        }                                                      \
                        if(i->next->_right != parent)                          \
                        {                                                      \
                                i->next = parent;                              \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_iterator_begin(struct N *m, struct N##_iterator *i)           \
        {                                                                      \
                i->curr = MAP_LEAF;                                            \
                i->next = (m->_root) ? N##_node_begin(m->_root) : MAP_LEAF;    \
                N##_iterator_next(i);                                          \
        }                                                                      \
                                                                               \
        void N##_iterator_cbegin(const struct N *const m,                      \
                                 struct N##_iterator *i)                       \
        {                                                                      \
                i->curr = MAP_LEAF;                                            \
                i->next = (m->_root) ? N##_node_begin(m->_root) : MAP_LEAF;    \
                N##_iterator_next(i);                                          \
        }                                                                      \
                                                                               \
        void N##_iterator_prev(struct N##_iterator *i)                         \
        {                                                                      \
                if(!i->curr)                                                   \
                {                                                              \
                        return;                                                \
                }                                                              \
                i->next = i->curr;                                             \
                if(i->curr->_left)                                             \
                {                                                              \
                        i->curr = N##_node_end(i->curr->_left);                \
                }                                                              \
                else                                                           \
                {                                                              \
                        struct N##_node *parent = i->curr->_parent;            \
                        while(parent && parent->_left == i->curr)              \
                        {                                                      \
                                i->curr = parent;                              \
                                parent = parent->_parent;                      \
                        }                                                      \
                        if(i->curr->_right != parent)                          \
                        {                                                      \
                                i->curr = parent;                              \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_iterator_end(struct N *m, struct N##_iterator *i)             \
        {                                                                      \
                i->curr = (m->_root) ? N##_node_end(m->_root) : MAP_LEAF;      \
                i->next = MAP_LEAF;                                            \
        }                                                                      \
                                                                               \
        void N##_iterator_cend(const struct N *const m,                        \
                               struct N##_iterator *i)                         \
        {                                                                      \
                i->curr = (m->_root) ? N##_node_end(m->_root) : MAP_LEAF;      \
                i->next = MAP_LEAF;                                            \
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
                return first.curr == second.curr;                              \
        }                                                                      \
                                                                               \
        /* =============== */                                                  \
        /*  FAST ITERATOR  */                                                  \
        /* =============== */                                                  \
                                                                               \
        struct N##_fast_iterator                                               \
        {                                                                      \
                struct N##_node *curr;                                         \
                struct N##_node *next;                                         \
                struct N##_node **stack;                                       \
                size_t stack_size;                                             \
        };                                                                     \
                                                                               \
        static size_t N##_exp_two(size_t curr)                                 \
        {                                                                      \
                size_t power = 1;                                              \
                for(size_t i = 0; i < curr; ++i)                               \
                {                                                              \
                        power *= 2;                                            \
                }                                                              \
                return power;                                                  \
        }                                                                      \
                                                                               \
        static size_t N##_log_two(size_t size)                                 \
        {                                                                      \
                size_t curr = 1;                                               \
                while(size >= N##_exp_two(curr))                               \
                {                                                              \
                        ++curr;                                                \
                }                                                              \
                return curr + 1;                                               \
        }                                                                      \
                                                                               \
        static size_t N##_stack_size(size_t size)                              \
        {                                                                      \
                size = N##_log_two(size) + 1;                                  \
                return sizeof(struct N##_node *) * (size * 2);                 \
        }                                                                      \
                                                                               \
        static void N##_fast_iterator_init(const struct N *const m,            \
                                           struct N##_fast_iterator *i)        \
        {                                                                      \
                i->stack_size = 0;                                             \
                i->stack =                                                     \
                    (struct N##_node **)malloc(N##_stack_size(m->_size));      \
        }                                                                      \
                                                                               \
        void N##_fast_iterator_free(struct N##_fast_iterator *i)               \
        {                                                                      \
                if(i->stack)                                                   \
                {                                                              \
                        free(i->stack);                                        \
                        i->stack = NULL;                                       \
                        i->curr = MAP_LEAF;                                    \
                        i->next = MAP_LEAF;                                    \
                        i->stack_size = 0;                                     \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_fast_iterator_next(struct N##_fast_iterator *i)               \
        {                                                                      \
                if(!i->stack_size)                                             \
                {                                                              \
                        return;                                                \
                }                                                              \
                i->curr = i->next;                                             \
                if(i->next->_right)                                            \
                {                                                              \
                        i->stack[i->stack_size++] = i->next;                   \
                        i->next = i->next->_right;                             \
                        while(i->next->_left)                                  \
                        {                                                      \
                                i->stack[i->stack_size++] = i->next;           \
                                i->next = i->next->_left;                      \
                        }                                                      \
                }                                                              \
                else                                                           \
                {                                                              \
                        struct N##_node *parent = i->stack[--i->stack_size];   \
                        while(parent && parent->_right == i->next)             \
                        {                                                      \
                                i->next = parent;                              \
                                parent = i->stack[--i->stack_size];            \
                        }                                                      \
                        if(i->next->_right != parent)                          \
                        {                                                      \
                                i->next = parent;                              \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_fast_iterator_begin(struct N *m, struct N##_fast_iterator *i) \
        {                                                                      \
                N##_fast_iterator_init(m, i);                                  \
                struct N##_node *curr = m->_root;                              \
                if(!curr)                                                      \
                {                                                              \
                        i->curr = MAP_LEAF;                                    \
                        i->next = MAP_LEAF;                                    \
                        return;                                                \
                }                                                              \
                                                                               \
                i->stack[i->stack_size++] = MAP_LEAF;                          \
                while(curr->_left)                                             \
                {                                                              \
                        i->stack[i->stack_size++] = curr;                      \
                        curr = curr->_left;                                    \
                }                                                              \
                i->curr = MAP_LEAF;                                            \
                i->next = curr;                                                \
                N##_fast_iterator_next(i);                                     \
        }                                                                      \
                                                                               \
        void N##_fast_iterator_cbegin(const struct N *const m,                 \
                                      struct N##_fast_iterator *i)             \
        {                                                                      \
                N##_fast_iterator_init(m, i);                                  \
                struct N##_node *curr = m->_root;                              \
                if(!curr)                                                      \
                {                                                              \
                        i->curr = MAP_LEAF;                                    \
                        i->next = MAP_LEAF;                                    \
                        return;                                                \
                }                                                              \
                                                                               \
                i->stack[i->stack_size++] = MAP_LEAF;                          \
                while(curr->_left)                                             \
                {                                                              \
                        i->stack[i->stack_size++] = curr;                      \
                        curr = curr->_left;                                    \
                }                                                              \
                i->curr = MAP_LEAF;                                            \
                i->next = curr;                                                \
                N##_fast_iterator_next(i);                                     \
        }                                                                      \
                                                                               \
        void N##_fast_iterator_prev(struct N##_fast_iterator *i)               \
        {                                                                      \
                if(!i->curr)                                                   \
                {                                                              \
                        return;                                                \
                }                                                              \
                i->next = i->curr;                                             \
                if(i->curr->_left)                                             \
                {                                                              \
                        i->stack[i->stack_size++] = i->curr;                   \
                        i->curr = i->curr->_left;                              \
                        while(i->curr->_right)                                 \
                        {                                                      \
                                i->stack[i->stack_size++] = i->curr;           \
                                i->curr = i->curr->_right;                     \
                        }                                                      \
                }                                                              \
                else                                                           \
                {                                                              \
                        struct N##_node *parent = i->stack[--i->stack_size];   \
                        while(parent && parent->_left == i->curr)              \
                        {                                                      \
                                parent = i->stack[--i->stack_size];            \
                                i->curr = parent;                              \
                        }                                                      \
                        if(i->curr->_right != parent)                          \
                        {                                                      \
                                i->curr = parent;                              \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_fast_iterator_end(struct N *m, struct N##_fast_iterator *i)   \
        {                                                                      \
                N##_fast_iterator_init(m, i);                                  \
                struct N##_node *curr = m->_root;                              \
                if(!curr)                                                      \
                {                                                              \
                        i->curr = MAP_LEAF;                                    \
                        i->next = MAP_LEAF;                                    \
                        return;                                                \
                }                                                              \
                                                                               \
                i->stack[i->stack_size++] = MAP_LEAF;                          \
                while(curr->_right)                                            \
                {                                                              \
                        i->stack[i->stack_size++] = curr;                      \
                        curr = curr->_right;                                   \
                }                                                              \
                i->curr = curr;                                                \
                i->next = MAP_LEAF;                                            \
        }                                                                      \
                                                                               \
        void N##_fast_iterator_cend(const struct N *const m,                   \
                                    struct N##_fast_iterator *i)               \
        {                                                                      \
                N##_fast_iterator_init(m, i);                                  \
                struct N##_node *curr = m->_root;                              \
                if(!curr)                                                      \
                {                                                              \
                        i->curr = MAP_LEAF;                                    \
                        i->next = MAP_LEAF;                                    \
                        return;                                                \
                }                                                              \
                                                                               \
                i->stack[i->stack_size++] = MAP_LEAF;                          \
                while(curr->_right)                                            \
                {                                                              \
                        i->stack[i->stack_size++] = curr;                      \
                        curr = curr->_right;                                   \
                }                                                              \
                i->curr = curr;                                                \
                i->next = MAP_LEAF;                                            \
        }                                                                      \
                                                                               \
        int N##_fast_iterator_equal(const struct N##_fast_iterator first,      \
                                    const struct N##_fast_iterator second)     \
        {                                                                      \
                return first.curr == second.curr;                              \
        }                                                                      \
                                                                               \
        /* =============== */                                                  \
        /*  MAP FUNCTIONS  */                                                  \
        /* =============== */                                                  \
                                                                               \
        size_t N##_size(const struct N *const m)                               \
        {                                                                      \
                return m->_size;                                               \
        }                                                                      \
                                                                               \
        void N##_init(struct N *m)                                             \
        {                                                                      \
                m->_size = 0;                                                  \
                m->_root = MAP_LEAF;                                           \
        }                                                                      \
                                                                               \
        void N##_free(struct N *m)                                             \
        {                                                                      \
                if(!m->_size)                                                  \
                {                                                              \
                        return;                                                \
                }                                                              \
                struct N##_node **stack =                                      \
                    (struct N##_node **)malloc(N##_stack_size(m->_size));      \
                                                                               \
                struct N##_node *curr = m->_root;                              \
                struct N##_node *tmp = NULL;                                   \
                                                                               \
                size_t stack_size = 0;                                         \
                while(1)                                                       \
                {                                                              \
                        if(curr != MAP_LEAF)                                   \
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
                                if(N##_element_copy != N##_flat_copy)          \
                                {                                              \
                                        N##_element_free(&tmp->_value);        \
                                }                                              \
                                free(tmp);                                     \
                        }                                                      \
                }                                                              \
                free(stack);                                                   \
                m->_root = MAP_LEAF;                                           \
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
                        struct N##_fast_iterator it_first;                     \
                        N##_fast_iterator_cbegin(first, &it_first);            \
                                                                               \
                        struct N##_fast_iterator it_second;                    \
                        N##_fast_iterator_cbegin(second, &it_second);          \
                                                                               \
                        for(size_t i = 0; i < first->_size; ++i)               \
                        {                                                      \
                                if(!N##_element_equal(                         \
                                       &it_first.curr->_value,                 \
                                       &it_second.curr->_value))               \
                                {                                              \
                                        equal = 0;                             \
                                        break;                                 \
                                }                                              \
                                N##_fast_iterator_next(&it_first);             \
                                N##_fast_iterator_next(&it_second);            \
                        }                                                      \
                                                                               \
                        N##_fast_iterator_free(&it_first);                     \
                        N##_fast_iterator_free(&it_second);                    \
                }                                                              \
                return equal;                                                  \
        }                                                                      \
                                                                               \
        void N##_copy(struct N *__restrict__ dst,                              \
                      const struct N *__restrict__ const src)                  \
        {                                                                      \
                dst->_size = src->_size;                                       \
                dst->_root = MAP_LEAF;                                         \
                                                                               \
                if(src->_size != 0)                                            \
                {                                                              \
                        dst->_root = (struct N##_node *)malloc(                \
                            sizeof(struct N##_node));                          \
                                                                               \
                        N##_element_copy(&dst->_root->_value,                  \
                                         &src->_root->_value);                 \
                        dst->_root->_color = src->_root->_color;               \
                        dst->_root->_left = dst->_root->_right =               \
                            dst->_root->_parent = MAP_LEAF;                    \
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
                                                                               \
                        struct N##_node *tmp = MAP_LEAF;                       \
                                                                               \
                        stack_src[0] = MAP_LEAF;                               \
                        stack_dst[0] = MAP_LEAF;                               \
                                                                               \
                        stack_src[1] = src->_root;                             \
                        stack_dst[1] = dst->_root;                             \
                        size_t stack_size = 2;                                 \
                                                                               \
                        while(stack_size > 0)                                  \
                        {                                                      \
                                if(!((curr_src->_left != MAP_LEAF &&           \
                                      curr_dst->_left == MAP_LEAF) ||          \
                                     (curr_src->_right != MAP_LEAF &&          \
                                      curr_dst->_right == MAP_LEAF)))          \
                                {                                              \
                                        --stack_size;                          \
                                        curr_src = stack_src[stack_size];      \
                                        curr_dst = stack_dst[stack_size];      \
                                        continue;                              \
                                }                                              \
                                                                               \
                                if(curr_src->_left != MAP_LEAF &&              \
                                   curr_dst->_left == MAP_LEAF)                \
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
                                tmp->_left = tmp->_right = MAP_LEAF;           \
                                curr_dst = tmp;                                \
                                N##_element_copy(&curr_dst->_value,            \
                                                 &curr_src->_value);           \
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
                return (n == parent->_left);                                   \
        }                                                                      \
                                                                               \
        static struct N##_node *N##_brother(                                   \
            const struct N##_node *const n,                                    \
            const struct N##_node *const parent)                               \
        {                                                                      \
                struct N##_node *brother = NULL;                               \
                if(parent != MAP_LEAF)                                         \
                {                                                              \
                        brother = (n == parent->_left) ? parent->_right        \
                                                       : parent->_left;        \
                }                                                              \
                return brother;                                                \
        }                                                                      \
        static void N##_rotate_left(struct N *m, struct N##_node *parent,      \
                                    struct N##_node *gparent)                  \
        {                                                                      \
                struct N##_node *_left = parent->_left;                        \
                gparent->_right = _left;                                       \
                if(_left != MAP_LEAF)                                          \
                {                                                              \
                        _left->_parent = gparent;                              \
                }                                                              \
                if(gparent == m->_root)                                        \
                {                                                              \
                        m->_root = parent;                                     \
                        parent->_parent = MAP_LEAF;                            \
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
        }                                                                      \
                                                                               \
        static void N##_rotate_right(struct N *m, struct N##_node *parent,     \
                                     struct N##_node *gparent)                 \
        {                                                                      \
                struct N##_node *right = parent->_right;                       \
                gparent->_left = right;                                        \
                if(right != MAP_LEAF)                                          \
                {                                                              \
                        right->_parent = gparent;                              \
                }                                                              \
                if(gparent == m->_root)                                        \
                {                                                              \
                        m->_root = parent;                                     \
                        parent->_parent = MAP_LEAF;                            \
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
                                n->_color = MAP_RED;                           \
                                parent->_color = MAP_BLACK;                    \
                                struct N##_node *brother = parent->_right;     \
                                if(brother != MAP_LEAF)                        \
                                {                                              \
                                        brother->_color = MAP_RED;             \
                                }                                              \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                N##_rotate_right_left(m, n, parent, gparent);  \
                                n->_color = MAP_BLACK;                         \
                                n->_right->_color = MAP_RED;                   \
                                n->_left->_color = MAP_RED;                    \
                        }                                                      \
                }                                                              \
                else                                                           \
                {                                                              \
                        if(!N##_is_left_child(parent, gparent))                \
                        {                                                      \
                                N##_rotate_left(m, parent, gparent);           \
                                n->_color = MAP_RED;                           \
                                parent->_color = MAP_BLACK;                    \
                                struct N##_node *brother = parent->_right;     \
                                if(brother != MAP_LEAF)                        \
                                {                                              \
                                        brother->_color = MAP_RED;             \
                                }                                              \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                N##_rotate_left_right(m, n, parent, gparent);  \
                                n->_color = MAP_BLACK;                         \
                                n->_right->_color = MAP_RED;                   \
                                n->_left->_color = MAP_RED;                    \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        static void N##_corect_tree(struct N *m, struct N##_node *n,           \
                                    struct N##_node *parent)                   \
        {                                                                      \
                struct N##_node *gparent = parent->_parent;                    \
                struct N##_node *aunt = N##_brother(parent, gparent);          \
                if(aunt == MAP_LEAF || aunt->_color == MAP_BLACK)              \
                {                                                              \
                        N##_rotate(m, n, parent, gparent);                     \
                }                                                              \
                else if(aunt != NULL)                                          \
                {                                                              \
                        aunt->_color = MAP_BLACK;                              \
                }                                                              \
                gparent->_color = MAP_RED;                                     \
                parent->_color = MAP_BLACK;                                    \
        }                                                                      \
                                                                               \
        static void N##_check_color(struct N *m, struct N##_node *n)           \
        {                                                                      \
                if(n == m->_root)                                              \
                {                                                              \
                        return;                                                \
                }                                                              \
                struct N##_node *parent = n->_parent;                          \
                if(n->_color == MAP_RED && parent->_color == MAP_RED)          \
                {                                                              \
                        N##_corect_tree(m, n, parent);                         \
                }                                                              \
                N##_check_color(m, parent);                                    \
        }                                                                      \
                                                                               \
        static void N##_insert_node(struct N *m, V *v)                         \
        {                                                                      \
                struct N##_node *parent = m->_root;                            \
                struct N##_node *new_node = NULL;                              \
                for(;;)                                                        \
                {                                                              \
                        int compare =                                          \
                            (N##_element_compare(&parent->_value, v));         \
                                                                               \
                        if(compare > 0)                                        \
                        {                                                      \
                                if(parent->_left == MAP_LEAF)                  \
                                {                                              \
                                        new_node = N##_node_new(v);            \
                                        parent->_left = new_node;              \
                                        m->_size++;                            \
                                        break;                                 \
                                }                                              \
                                parent = parent->_left;                        \
                        }                                                      \
                        else if(compare < 0)                                   \
                        {                                                      \
                                if(parent->_right == MAP_LEAF)                 \
                                {                                              \
                                        new_node = N##_node_new(v);            \
                                        parent->_right = new_node;             \
                                        m->_size++;                            \
                                        break;                                 \
                                }                                              \
                                parent = parent->_right;                       \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                if(N##_element_copy != N##_flat_copy)          \
                                {                                              \
                                        N##_element_free(&parent->_value);     \
                                        N##_element_copy(&parent->_value, v);  \
                                }                                              \
                                else                                           \
                                {                                              \
                                        parent->_value = *v;                   \
                                }                                              \
                                return;                                        \
                        }                                                      \
                }                                                              \
                new_node->_parent = parent;                                    \
                N##_check_color(m, new_node);                                  \
        }                                                                      \
                                                                               \
        void N##_insert(struct N *m, V v)                                      \
        {                                                                      \
                if(m->_root == MAP_LEAF)                                       \
                {                                                              \
                        struct N##_node *new_node = N##_node_new(&v);          \
                        new_node->_color = MAP_BLACK;                          \
                        new_node->_parent = MAP_LEAF;                          \
                        m->_root = new_node;                                   \
                        m->_size = 1;                                          \
                }                                                              \
                else                                                           \
                {                                                              \
                        N##_insert_node(m, &v);                                \
                        m->_root->_color = MAP_BLACK;                          \
                }                                                              \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_find(struct N *m, V v)                         \
        {                                                                      \
                struct N##_iterator ret = {MAP_LEAF, MAP_LEAF};                \
                struct N##_node *prev;                                         \
                if(m->_root)                                                   \
                {                                                              \
                        struct N##_node *curr = m->_root;                      \
                        while(curr)                                            \
                        {                                                      \
                                prev = curr;                                   \
                                int compare =                                  \
                                    (N##_element_compare(&curr->_value, &v));  \
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
                                        ret.next = curr;                       \
                                        ret.curr = prev;                       \
                                        N##_iterator_next(&ret);               \
                                        break;                                 \
                                }                                              \
                        }                                                      \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        static struct N##_node *N##_find_node(struct N *m, V v)                \
        {                                                                      \
                struct N##_iterator i = N##_find(m, v);                        \
                return i.curr;                                                 \
        }                                                                      \
                                                                               \
        static void N##_erase_rebalanse(struct N *m, struct N##_node *n,       \
                                        struct N##_node *p)                    \
        {                                                                      \
                if(p)                                                          \
                {                                                              \
                        struct N##_node *s;                                    \
                        struct N##_node *r;                                    \
                        if(p->_left == n)                                      \
                        {                                                      \
                                s = p->_right;                                 \
                                if(!s)                                         \
                                {                                              \
                                        return;                                \
                                }                                              \
                                if(s->_color == MAP_RED)                       \
                                {                                              \
                                        s->_color = MAP_BLACK;                 \
                                        p->_color = MAP_RED;                   \
                                }                                              \
                                if((!s->_right ||                              \
                                    s->_right->_color == MAP_BLACK) &&         \
                                   (!s->_left ||                               \
                                    s->_left->_color == MAP_BLACK))            \
                                {                                              \
                                        s->_color = MAP_RED;                   \
                                }                                              \
                                else if(s->_right &&                           \
                                        s->_right->_color == MAP_RED)          \
                                {                                              \
                                        r = s->_right;                         \
                                        if(r)                                  \
                                        {                                      \
                                                r->_color = MAP_BLACK;         \
                                        }                                      \
                                        N##_rotate_left(m, s, p);              \
                                }                                              \
                                else if(s->_left &&                            \
                                        s->_left->_color == MAP_RED)           \
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
                                if(s->_color == MAP_RED)                       \
                                {                                              \
                                        s->_color = MAP_BLACK;                 \
                                        p->_color = MAP_RED;                   \
                                }                                              \
                                if((!s->_right ||                              \
                                    s->_right->_color == MAP_BLACK) &&         \
                                   (!s->_left ||                               \
                                    s->_left->_color == MAP_BLACK))            \
                                {                                              \
                                        s->_color = MAP_RED;                   \
                                }                                              \
                                else if(s->_left &&                            \
                                        s->_left->_color == MAP_RED)           \
                                {                                              \
                                        r = s->_left;                          \
                                        if(r)                                  \
                                        {                                      \
                                                r->_color = MAP_BLACK;         \
                                        }                                      \
                                        N##_rotate_right(m, s, p);             \
                                }                                              \
                                else if(s->_right &&                           \
                                        s->_right->_color == MAP_RED)          \
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
                struct N##_node *succ_c;                                       \
                struct N##_node *succ;                                         \
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
                succ_c = (succ->_left) ? succ->_left : succ->_right;           \
                struct N##_node *succ_p = succ->_parent;                       \
                if(succ_c)                                                     \
                {                                                              \
                        succ_c->_parent = succ_p;                              \
                }                                                              \
                if(!succ->_parent)                                             \
                {                                                              \
                        m->_root = succ_c;                                     \
                }                                                              \
                else                                                           \
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
                if(succ != n)                                                  \
                {                                                              \
			N##_element_copy(&n->_value, &succ->_value);           \
                        if(N##_element_copy != N##_flat_copy)                  \
                        {                                                      \
                                N##_element_free(&succ->_value);               \
                        }                                                      \
                }                                                              \
                if(succ->_color == MAP_BLACK)                                  \
                {                                                              \
                        N##_erase_rebalanse(m, succ_c, succ_p);                \
                }                                                              \
                if(m->_root)                                                   \
                {                                                              \
                        m->_root->_color = MAP_BLACK;                          \
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
                        if(N##_element_copy != N##_flat_copy)                  \
                        {                                                      \
                                N##_element_free(&n->_value);                  \
                        }                                                      \
                        free(N##_erase_node(m, n));                            \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        int N##_iterator_erase(struct N *m, struct N##_iterator *i)            \
        {                                                                      \
                struct N##_iterator tmp = {i->curr, i->next};                  \
                N##_iterator_next(&tmp);                                       \
                int ret = (i->curr) ? 1 : 0;                                   \
                if(ret)                                                        \
                {                                                              \
                        if(N##_element_copy != N##_flat_copy)                  \
                        {                                                      \
                                N##_element_free(&i->curr->_value);            \
                        }                                                      \
                        free(N##_erase_node(m, i->curr));                      \
                }                                                              \
                i->curr = tmp.curr;                                            \
                i->next = tmp.next;                                            \
                return ret;                                                    \
        }\
\
