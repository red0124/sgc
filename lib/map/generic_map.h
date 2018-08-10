#pragma once

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef MAP_LEAF
#define MAP_LEAF NULL
#endif

#ifndef RB_COLOR
#define RB_COLOR
enum map_color
{
        MAP_RED,
        MAP_BLACK,
};
#endif

#ifndef MAP_KILL_WARNINGS
#warning "MAP: define 'MAP_KILL_WARNINGS' to remove all warnings"

#ifndef MAP_KILL_INIT_WARNING
#warning "MAP: using 'void' as default map element init"
#warning "MAP: define 'MAP_KILL_INIT_WARNING' to remove warning"
#endif

#ifndef MAP_KILL_COPY_WARNING
#warning "MAP: using '=' as default map element copy"
#warning "MAP: define 'MAP_KILL_COPY_WARNING' to remove warning"
#endif

#ifndef MAP_KILL_COPY_KEY_WARNING
#warning "MAP: using '=' as default map key copy"
#warning "MAP: define 'MAP_KILL_COPY_KEY_WARNING' to remove warning"
#endif

#ifndef MAP_KILL_COMPARE_WARNING
#warning "MAP: using 'memcmp' as default map element compare"
#warning "MAP: define 'MAP_KILL_COMPARE_WARNING' to remove warning"
#endif

#ifndef MAP_KILL_EQUAL_KEY_WARNING
#warning "MAP: using 'memcmp' as default map key equal"
#warning "MAP: define 'MAP_KILL_EQUAL_KEY_WARNING' to remove warning"
#endif

#ifndef MAP_KILL_FREE_WARNING
#warning "MAP: using 'void' as default map element free"
#warning "MAP: define 'MAP_KILL_FREE_WARNING' to remove warning"
#endif

#endif

#define INIT_MAP(K, V)                                                         \
                                                                               \
        struct node_##K##_##V                                                  \
        {                                                                      \
                struct node_##K##_##V *_parent;                                \
                struct node_##K##_##V *_left;                                  \
                struct node_##K##_##V *_right;                                 \
                K _key;                                                        \
                V _value;                                                      \
                enum map_color _color;                                         \
        };                                                                     \
                                                                               \
        struct map_##K##_##V                                                   \
        {                                                                      \
                size_t _size;                                                  \
                struct node_##K##_##V *_root;                                  \
        };                                                                     \
                                                                               \
        static void map_element_default_init_##K##_##V(V *el)                   \
        {                                                                      \
                (void)el;                                                      \
        }                                                                      \
                                                                               \
        void (*map_element_init_##K##_##V)(V *) =                              \
            map_element_default_init_##K##_##V;                                \
                                                                               \
        void map_set_init_##K##_##V(void (*init)(V *))                         \
        {                                                                      \
                map_element_init_##K##_##V = init;                             \
        }                                                                      \
                                                                               \
        static void map_element_default_copy_##K##_##V(V *dst, const V *src)          \
        {                                                                      \
                *dst = *src;                                                   \
        }                                                                      \
                                                                               \
        void (*map_element_copy_##K##_##V)(V *, const V *) =                   \
            map_element_default_copy_##K##_##V;                                \
                                                                               \
        void map_set_copy_##K##_##V(void (*copy)(V *, const V *))              \
        {                                                                      \
                map_element_copy_##K##_##V = copy;                             \
        }                                                                      \
                                                                               \
        static void map_element_default_copy_key_##K##_##V(K *dst, const K *src)      \
        {                                                                      \
                *dst = *src;                                                   \
        }                                                                      \
                                                                               \
        void (*map_element_copy_key_##K##_##V)(K *, const K *) =               \
            map_element_default_copy_key_##K##_##V;                            \
                                                                               \
        void map_set_copy_key_##K##_##V(void (*copy)(K *, const K *))          \
        {                                                                      \
                map_element_copy_key_##K##_##V = copy;                         \
        }                                                                      \
                                                                               \
        static int map_element_default_equal_##K##_##V(const V *first,                \
                                                const V *second)               \
        {                                                                      \
                return memcmp(first, second, sizeof(V)) == 0;                  \
        }                                                                      \
                                                                               \
        int (*map_element_equal_##K##_##V)(const V *, const V *) =             \
            map_element_default_equal_##K##_##V;                               \
                                                                               \
        void map_set_equal_##K##_##V(int (*equal)(const V *, const V *))       \
        {                                                                      \
                map_element_equal_##K##_##V = equal;                           \
        }                                                                      \
                                                                               \
        static int map_element_default_equal_key_##K##_##V(const K *first,            \
                                                    const K *second)           \
        {                                                                      \
                return memcmp(first, second, sizeof(K)) == 0;                  \
        }                                                                      \
                                                                               \
        int (*map_element_equal_key_##K##_##V)(const K *, const K *) =         \
            map_element_default_equal_key_##K##_##V;                           \
                                                                               \
        void map_set_equal_key_##K##_##V(int (*equal)(const K *, const K *))   \
        {                                                                      \
                map_element_equal_key_##K##_##V = equal;                       \
        }                                                                      \
                                                                               \
        static int map_element_default_compare_##K##_##V(const void *first,           \
                                                  const void *second)          \
        {                                                                      \
                return memcmp(first, second, sizeof(K));                       \
        }                                                                      \
                                                                               \
        int (*map_element_compare_##K##_##V)(const void *, const void *) =     \
            map_element_default_compare_##K##_##V;                             \
                                                                               \
        void map_set_compare_##K##_##V(                                        \
            int (*compare)(const void *, const void *))                        \
        {                                                                      \
                map_element_compare_##K##_##V = compare;                       \
        }                                                                      \
                                                                               \
        static void map_element_default_free_##K##_##V(K *k, V *v)                    \
        {                                                                      \
                (void)k;                                                       \
                (void)v;                                                       \
        }                                                                      \
                                                                               \
        void (*map_element_free_##K##_##V)(K *, V *) =                         \
            map_element_default_free_##K##_##V;                                \
                                                                               \
        void map_set_free_##K##_##V(void (*free)(K *, V *))                    \
        {                                                                      \
                map_element_free_##K##_##V = free;                             \
        }                                                                      \
                                                                               \
        struct map_iterator_##K##_##V                                          \
        {                                                                      \
                struct node_##K##_##V *curr;                                   \
                struct node_##K##_##V *next;                                   \
        };                                                                     \
                                                                               \
        K *map_iterator_key_##K##_##V(struct map_iterator_##K##_##V i)         \
        {                                                                      \
                return &i.curr->_key;                                          \
        }                                                                      \
                                                                               \
        V *map_iterator_value_##K##_##V(struct map_iterator_##K##_##V i)       \
        {                                                                      \
                return &i.curr->_value;                                        \
        }                                                                      \
                                                                               \
        static struct node_##K##_##V *node_begin_##K##_##V(                    \
            struct node_##K##_##V *n)                                          \
        {                                                                      \
                while(n->_left)                                                \
                {                                                              \
                        n = n->_left;                                          \
                }                                                              \
                return n;                                                      \
        }                                                                      \
                                                                               \
        static struct node_##K##_##V *node_end_##K##_##V(                      \
            struct node_##K##_##V *n)                                          \
        {                                                                      \
                while(n->_right)                                               \
                {                                                              \
                        n = n->_right;                                         \
                }                                                              \
                return n;                                                      \
        }                                                                      \
                                                                               \
        void map_iterator_next_##K##_##V(struct map_iterator_##K##_##V *i)     \
        {                                                                      \
                if(!i->next)                                                   \
                {                                                              \
                        return;                                                \
                }                                                              \
                i->curr = i->next;                                             \
                if(i->next->_right)                                            \
                {                                                              \
                        i->next = node_begin_##K##_##V(i->next->_right);       \
                }                                                              \
                else                                                           \
                {                                                              \
                        struct node_##K##_##V *parent = i->next->_parent;      \
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
        void map_iterator_begin_##K##_##V(struct map_##K##_##V *m,             \
                                          struct map_iterator_##K##_##V *i)    \
        {                                                                      \
                i->curr = MAP_LEAF;                                            \
                i->next =                                                      \
                    (m->_root) ? node_begin_##K##_##V(m->_root) : MAP_LEAF;    \
                map_iterator_next_##K##_##V(i);                                \
        }                                                                      \
                                                                               \
        void map_iterator_prev_##K##_##V(struct map_iterator_##K##_##V *i)     \
        {                                                                      \
                if(!i->curr)                                                   \
                {                                                              \
                        return;                                                \
                }                                                              \
                i->next = i->curr;                                             \
                if(i->curr->_left)                                             \
                {                                                              \
                        i->curr = node_end_##K##_##V(i->curr->_left);          \
                }                                                              \
                else                                                           \
                {                                                              \
                        struct node_##K##_##V *parent = i->curr->_parent;      \
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
        void map_iterator_end_##K##_##V(struct map_##K##_##V *m,               \
                                        struct map_iterator_##K##_##V *i)      \
        {                                                                      \
                i->curr =                                                      \
                    (m->_root) ? node_end_##K##_##V(m->_root) : MAP_LEAF;      \
                i->next = MAP_LEAF;                                            \
        }                                                                      \
                                                                               \
        struct map_iterator_##K##_##V map_begin_##K##_##V(                     \
            struct map_##K##_##V *m)                                           \
        {                                                                      \
                struct map_iterator_##K##_##V i;                               \
                map_iterator_begin_##K##_##V(m, &i);                           \
                return i;                                                      \
        }                                                                      \
                                                                               \
        struct map_iterator_##K##_##V map_end_##K##_##V(                       \
            struct map_##K##_##V *m)                                           \
        {                                                                      \
                struct map_iterator_##K##_##V i;                               \
                map_iterator_end_##K##_##V(m, &i);                             \
                return i;                                                      \
        }                                                                      \
                                                                               \
        int map_iterator_equal_##K##_##V(struct map_iterator_##K##_##V first,  \
                                         struct map_iterator_##K##_##V second) \
        {                                                                      \
                return first.curr == second.curr;                              \
        }                                                                      \
                                                                               \
        struct map_fast_iterator_##K##_##V                                     \
        {                                                                      \
                struct node_##K##_##V *curr;                                   \
                struct node_##K##_##V *next;                                   \
                struct node_##K##_##V **stack;                                 \
                size_t stack_size;                                             \
        };                                                                     \
                                                                               \
        static size_t map_exp_two_##K##_##V(size_t curr)                       \
        {                                                                      \
                size_t power = 1;                                              \
                for(size_t i = 0; i < curr; ++i)                               \
                {                                                              \
                        power *= 2;                                            \
                }                                                              \
                return power;                                                  \
        }                                                                      \
                                                                               \
        static size_t map_log_two_##K##_##V(size_t size)                       \
        {                                                                      \
                size_t curr = 1;                                               \
                while(size >= map_exp_two_##K##_##V(curr))                     \
                {                                                              \
                        ++curr;                                                \
                }                                                              \
                return curr + 1;                                               \
        }                                                                      \
                                                                               \
        static size_t map_stack_size_##K##_##V(size_t size)                    \
        {                                                                      \
                size = map_log_two_##K##_##V(size) + 1;                        \
                return sizeof(struct node_##K##_##V *) * (size * 2);           \
        }                                                                      \
                                                                               \
        static void map_fast_iterator_init_##K##_##V(                          \
            struct map_##K##_##V *m, struct map_fast_iterator_##K##_##V *i)    \
        {                                                                      \
                i->stack_size = 0;                                             \
                i->stack = (struct node_##K##_##V **)malloc(                   \
                    map_stack_size_##K##_##V(m->_size));                       \
        }                                                                      \
                                                                               \
        void map_fast_iterator_free_##K##_##V(                                 \
            struct map_fast_iterator_##K##_##V *i)                             \
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
        void map_fast_iterator_next_##K##_##V(                                 \
            struct map_fast_iterator_##K##_##V *i)                             \
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
                        struct node_##K##_##V *parent =                        \
                            i->stack[--i->stack_size];                         \
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
        void map_fast_iterator_begin_##K##_##V(                                \
            struct map_##K##_##V *m, struct map_fast_iterator_##K##_##V *i)    \
        {                                                                      \
                map_fast_iterator_init_##K##_##V(m, i);                        \
                struct node_##K##_##V *curr = m->_root;                        \
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
                map_fast_iterator_next_##K##_##V(i);                           \
        }                                                                      \
                                                                               \
        void map_fast_iterator_prev_##K##_##V(                                 \
            struct map_fast_iterator_##K##_##V *i)                             \
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
                        struct node_##K##_##V *parent =                        \
                            i->stack[--i->stack_size];                         \
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
        void map_fast_iterator_end_##K##_##V(                                  \
            struct map_##K##_##V *m, struct map_fast_iterator_##K##_##V *i)    \
        {                                                                      \
                map_fast_iterator_init_##K##_##V(m, i);                        \
                struct node_##K##_##V *curr = m->_root;                        \
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
        int map_fast_iterator_equal_##K##_##V(                                 \
            struct map_fast_iterator_##K##_##V first,                          \
            struct map_fast_iterator_##K##_##V second)                         \
        {                                                                      \
                return first.curr == second.curr;                              \
        }                                                                      \
                                                                               \
        static struct node_##K##_##V *node_new_##K##_##V(const K *k,           \
                                                         const V *v)           \
        {                                                                      \
                struct node_##K##_##V *n = (struct node_##K##_##V *)malloc(    \
                    sizeof(struct node_##K##_##V));                            \
                map_element_copy_key_##K##_##V(&n->_key, k);                   \
                map_element_copy_##K##_##V(&n->_value, v);                     \
                n->_left = n->_right = MAP_LEAF;                               \
                n->_color = MAP_RED;                                           \
                return n;                                                      \
        }                                                                      \
                                                                               \
        size_t map_size_##K##_##V(const struct map_##K##_##V *m)               \
        {                                                                      \
                return m->_size;                                               \
        }                                                                      \
                                                                               \
        void map_init_##K##_##V(struct map_##K##_##V *m,                       \
                                int (*comp)(const void *, const void *))       \
        {                                                                      \
                m->_size = 0;                                                  \
                m->_root = MAP_LEAF;                                           \
                if(comp)                                                       \
                {                                                              \
                        map_element_compare_##K##_##V = comp;                  \
                }                                                              \
        }                                                                      \
                                                                               \
        void map_default_init_##K##_##V(struct map_##K##_##V *m)               \
        {                                                                      \
                map_init_##K##_##V(m, NULL);                                   \
        }                                                                      \
                                                                               \
        void map_free_##K##_##V(struct map_##K##_##V *m)                       \
        {                                                                      \
                if(!m->_size)                                                  \
                {                                                              \
                        return;                                                \
                }                                                              \
                struct node_##K##_##V **stack =                                \
                    (struct node_##K##_##V **)malloc(                          \
                        map_stack_size_##K##_##V(m->_size));                   \
                                                                               \
                struct node_##K##_##V *curr = m->_root;                        \
                struct node_##K##_##V *tmp = NULL;                             \
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
                                if(map_element_free_##K##_##V !=               \
                                   map_element_default_free_##K##_##V)         \
                                {                                              \
                                        map_element_free_##K##_##V(            \
                                            &tmp->_key, &tmp->_value);         \
                                }                                              \
                                free(tmp);                                     \
                        }                                                      \
                }                                                              \
                free(stack);                                                   \
                m->_root = MAP_LEAF;                                           \
                m->_size = 0;                                                  \
        }                                                                      \
                                                                               \
        int map_equal_##K##_##V(struct map_##K##_##V *first,                   \
                                struct map_##K##_##V *second)                  \
        {                                                                      \
                int equal = (first == second);                                 \
                if(equal == 0 && first->_size == second->_size)                \
                {                                                              \
                        equal = 1;                                             \
                        struct map_fast_iterator_##K##_##V it_first;           \
                        map_fast_iterator_begin_##K##_##V(first, &it_first);   \
                                                                               \
                        struct map_fast_iterator_##K##_##V it_second;          \
                        map_fast_iterator_begin_##K##_##V(second, &it_second); \
                                                                               \
                        for(size_t i = 0; i < first->_size; ++i)               \
                        {                                                      \
                                if((!map_element_equal_key_##K##_##V(          \
                                        &it_first.curr->_key,                  \
                                        &it_second.curr->_key) ||              \
                                    !map_element_equal_##K##_##V(              \
                                        &it_first.curr->_value,                \
                                        &it_second.curr->_value)))             \
                                {                                              \
                                        equal = 0;                             \
                                        break;                                 \
                                }                                              \
                                map_fast_iterator_next_##K##_##V(&it_first);   \
                                map_fast_iterator_next_##K##_##V(&it_second);  \
                        }                                                      \
                                                                               \
                        map_fast_iterator_free_##K##_##V(&it_first);           \
                        map_fast_iterator_free_##K##_##V(&it_second);          \
                }                                                              \
                return equal;                                                  \
        }                                                                      \
                                                                               \
        void map_copy_##K##_##V(struct map_##K##_##V *__restrict__ dst,        \
                                const struct map_##K##_##V *__restrict__ src)  \
        {                                                                      \
                dst->_size = src->_size;                                       \
                dst->_root = MAP_LEAF;                                         \
                                                                               \
                if(src->_size != 0)                                            \
                {                                                              \
                        dst->_root = (struct node_##K##_##V *)malloc(          \
                            sizeof(struct node_##K##_##V));                    \
                                                                               \
                        map_element_copy_##K##_##V(&dst->_root->_value,        \
                                                   &src->_root->_value);       \
                        map_element_copy_key_##K##_##V(&dst->_root->_key,      \
                                                       &src->_root->_key);     \
                        dst->_root->_color = src->_root->_color;               \
                        dst->_root->_left = dst->_root->_right =               \
                            dst->_root->_parent = MAP_LEAF;                    \
                                                                               \
                        struct node_##K##_##V **stack_src =                    \
                            (struct node_##K##_##V **)malloc(                  \
                                map_stack_size_##K##_##V(src->_size));         \
                                                                               \
                        struct node_##K##_##V *curr_src = src->_root;          \
                                                                               \
                        struct node_##K##_##V **stack_dst =                    \
                            (struct node_##K##_##V **)malloc(                  \
                                map_stack_size_##K##_##V(dst->_size));         \
                                                                               \
                        struct node_##K##_##V *curr_dst = dst->_root;          \
                                                                               \
                        struct node_##K##_##V *tmp = MAP_LEAF;                 \
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
                                            (struct node_##K##_##V *)malloc(   \
                                                sizeof(                        \
                                                    struct node_##K##_##V));   \
                                        tmp = curr_dst->_left;                 \
                                        tmp->_parent = curr_dst;               \
                                        curr_src = curr_src->_left;            \
                                }                                              \
                                else                                           \
                                {                                              \
                                        curr_dst->_right =                     \
                                            (struct node_##K##_##V *)malloc(   \
                                                sizeof(                        \
                                                    struct node_##K##_##V));   \
                                        tmp = curr_dst->_right;                \
                                        tmp->_parent = curr_dst;               \
                                        curr_src = curr_src->_right;           \
                                }                                              \
                                tmp->_left = tmp->_right = MAP_LEAF;           \
                                curr_dst = tmp;                                \
                                map_element_copy_##K##_##V(&curr_dst->_value,  \
                                                           &curr_src->_value); \
                                map_element_copy_key_##K##_##V(                \
                                    &curr_dst->_key, &curr_src->_key);         \
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
        void map_operate_##K##_##V(struct map_##K##_##V *m,                    \
                                   void (*operate)(const K *, V *))            \
        {                                                                      \
                struct map_fast_iterator_##K##_##V it;                         \
                map_fast_iterator_begin_##K##_##V(m, &it);                     \
                                                                               \
                for(size_t i = 0; i < m->_size; ++i)                           \
                {                                                              \
                        operate(&it.curr->_key, &it.curr->_value);             \
                        map_fast_iterator_next_##K##_##V(&it);                 \
                }                                                              \
                                                                               \
                map_fast_iterator_free_##K##_##V(&it);                         \
        }                                                                      \
                                                                               \
        void map_operate_inverted_##K##_##V(struct map_##K##_##V *m,           \
                                            void (*operate)(const K *, V *))   \
        {                                                                      \
                struct map_fast_iterator_##K##_##V it;                         \
                map_fast_iterator_end_##K##_##V(m, &it);                       \
                                                                               \
                for(size_t i = 0; i < m->_size; ++i)                           \
                {                                                              \
                        operate(&it.curr->_key, &it.curr->_value);             \
                        map_fast_iterator_prev_##K##_##V(&it);                 \
                }                                                              \
                                                                               \
                map_fast_iterator_free_##K##_##V(&it);                         \
        }                                                                      \
                                                                               \
        void map_operate_to_##K##_##V(struct map_##K##_##V *m,                 \
                                      void (*operate)(const K *, V *, void *), \
                                      void *argout)                            \
        {                                                                      \
                struct map_fast_iterator_##K##_##V it;                         \
                map_fast_iterator_begin_##K##_##V(m, &it);                     \
                                                                               \
                for(size_t i = 0; i < m->_size; ++i)                           \
                {                                                              \
                        operate(&it.curr->_key, &it.curr->_value, argout);     \
                        map_fast_iterator_next_##K##_##V(&it);                 \
                }                                                              \
                                                                               \
                map_fast_iterator_free_##K##_##V(&it);                         \
        }                                                                      \
                                                                               \
        void map_operate_inverted_to_##K##_##V(                                \
            struct map_##K##_##V *m, void (*operate)(const K *, V *, void *),  \
            void *argout)                                                      \
        {                                                                      \
                struct map_fast_iterator_##K##_##V it;                         \
                map_fast_iterator_end_##K##_##V(m, &it);                       \
                                                                               \
                for(size_t i = 0; i < m->_size; ++i)                           \
                {                                                              \
                        operate(&it.curr->_key, &it.curr->_value, argout);     \
                        map_fast_iterator_prev_##K##_##V(&it);                 \
                }                                                              \
                                                                               \
                map_fast_iterator_free_##K##_##V(&it);                         \
        }                                                                      \
                                                                               \
        static int map_is_left_child_##K##_##V(struct node_##K##_##V *n,       \
                                               struct node_##K##_##V *parent)  \
        {                                                                      \
                return (n == parent->_left);                                   \
        }                                                                      \
                                                                               \
        static struct node_##K##_##V *map_brother_##K##_##V(                   \
            struct node_##K##_##V *n, struct node_##K##_##V *parent)           \
        {                                                                      \
                struct node_##K##_##V *brother = NULL;                         \
                if(parent != MAP_LEAF)                                         \
                {                                                              \
                        brother = (n == parent->_left) ? parent->_right        \
                                                       : parent->_left;        \
                }                                                              \
                return brother;                                                \
        }                                                                      \
        static void map_rotate_left_##K##_##V(struct map_##K##_##V *m,         \
                                              struct node_##K##_##V *parent,   \
                                              struct node_##K##_##V *gparent)  \
        {                                                                      \
                struct node_##K##_##V *_left = parent->_left;                  \
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
                        struct node_##K##_##V *ggparent = gparent->_parent;    \
                        parent->_parent = ggparent;                            \
                        if(map_is_left_child_##K##_##V(gparent, ggparent))     \
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
        static void map_rotate_right_##K##_##V(struct map_##K##_##V *m,        \
                                               struct node_##K##_##V *parent,  \
                                               struct node_##K##_##V *gparent) \
        {                                                                      \
                struct node_##K##_##V *right = parent->_right;                 \
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
                        struct node_##K##_##V *ggparent = gparent->_parent;    \
                        parent->_parent = ggparent;                            \
                        if(map_is_left_child_##K##_##V(gparent, ggparent))     \
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
        static void map_rotate_left_right_##K##_##V(                           \
            struct map_##K##_##V *m, struct node_##K##_##V *n,                 \
            struct node_##K##_##V *parent, struct node_##K##_##V *gparent)     \
        {                                                                      \
                map_rotate_left_##K##_##V(m, n, parent);                       \
                map_rotate_right_##K##_##V(m, n, gparent);                     \
        }                                                                      \
                                                                               \
        static void map_rotate_right_left_##K##_##V(                           \
            struct map_##K##_##V *m, struct node_##K##_##V *n,                 \
            struct node_##K##_##V *parent, struct node_##K##_##V *gparent)     \
        {                                                                      \
                map_rotate_right_##K##_##V(m, n, parent);                      \
                map_rotate_left_##K##_##V(m, n, gparent);                      \
        }                                                                      \
                                                                               \
        static void map_rotate_##K##_##V(                                      \
            struct map_##K##_##V *m, struct node_##K##_##V *n,                 \
            struct node_##K##_##V *parent, struct node_##K##_##V *gparent)     \
        {                                                                      \
                if(map_is_left_child_##K##_##V(n, parent))                     \
                {                                                              \
                        if(map_is_left_child_##K##_##V(parent, gparent))       \
                        {                                                      \
                                map_rotate_right_##K##_##V(m, parent,          \
                                                           gparent);           \
                                n->_color = MAP_RED;                           \
                                parent->_color = MAP_BLACK;                    \
                                struct node_##K##_##V *brother =               \
                                    parent->_right;                            \
                                if(brother != MAP_LEAF)                        \
                                {                                              \
                                        brother->_color = MAP_RED;             \
                                }                                              \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                map_rotate_right_left_##K##_##V(m, n, parent,  \
                                                                gparent);      \
                                n->_color = MAP_BLACK;                         \
                                n->_right->_color = MAP_RED;                   \
                                n->_left->_color = MAP_RED;                    \
                        }                                                      \
                }                                                              \
                else                                                           \
                {                                                              \
                        if(!map_is_left_child_##K##_##V(parent, gparent))      \
                        {                                                      \
                                map_rotate_left_##K##_##V(m, parent, gparent); \
                                n->_color = MAP_RED;                           \
                                parent->_color = MAP_BLACK;                    \
                                struct node_##K##_##V *brother =               \
                                    parent->_right;                            \
                                if(brother != MAP_LEAF)                        \
                                {                                              \
                                        brother->_color = MAP_RED;             \
                                }                                              \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                map_rotate_left_right_##K##_##V(m, n, parent,  \
                                                                gparent);      \
                                n->_color = MAP_BLACK;                         \
                                n->_right->_color = MAP_RED;                   \
                                n->_left->_color = MAP_RED;                    \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        static void map_corect_tree_##K##_##V(struct map_##K##_##V *m,         \
                                              struct node_##K##_##V *n,        \
                                              struct node_##K##_##V *parent)   \
        {                                                                      \
                struct node_##K##_##V *gparent = parent->_parent;              \
                struct node_##K##_##V *aunt =                                  \
                    map_brother_##K##_##V(parent, gparent);                    \
                if(aunt == MAP_LEAF || aunt->_color == MAP_BLACK)              \
                {                                                              \
                        map_rotate_##K##_##V(m, n, parent, gparent);           \
                }                                                              \
                else if(aunt != NULL)                                          \
                {                                                              \
                        aunt->_color = MAP_BLACK;                              \
                }                                                              \
                gparent->_color = MAP_RED;                                     \
                parent->_color = MAP_BLACK;                                    \
        }                                                                      \
                                                                               \
        static void map_check_color_##K##_##V(struct map_##K##_##V *m,         \
                                              struct node_##K##_##V *n)        \
        {                                                                      \
                if(n == m->_root)                                              \
                {                                                              \
                        return;                                                \
                }                                                              \
                struct node_##K##_##V *parent = n->_parent;                    \
                if(n->_color == MAP_RED && parent->_color == MAP_RED)          \
                {                                                              \
                        map_corect_tree_##K##_##V(m, n, parent);               \
                }                                                              \
                map_check_color_##K##_##V(m, parent);                          \
        }                                                                      \
                                                                               \
        static void map_insert_node_##K##_##V(struct map_##K##_##V *m, K *k,   \
                                              V *v)                            \
        {                                                                      \
                struct node_##K##_##V *parent = m->_root;                      \
                struct node_##K##_##V *new_node = NULL;                        \
                for(;;)                                                        \
                {                                                              \
                        int compare =                                          \
                            (map_element_compare_##K##_##V(&parent->_key, k)); \
                                                                               \
                        if(compare > 0)                                        \
                        {                                                      \
                                if(parent->_left == MAP_LEAF)                  \
                                {                                              \
                                        new_node = node_new_##K##_##V(k, v);   \
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
                                        new_node = node_new_##K##_##V(k, v);   \
                                        parent->_right = new_node;             \
                                        m->_size++;                            \
                                        break;                                 \
                                }                                              \
                                parent = parent->_right;                       \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                map_element_copy_##K##_##V(&parent->_value,    \
                                                           v);                 \
                                return;                                        \
                        }                                                      \
                }                                                              \
                new_node->_parent = parent;                                    \
                map_check_color_##K##_##V(m, new_node);                        \
        }                                                                      \
                                                                               \
        struct map_##K##_##V *map_set_##K##_##V(struct map_##K##_##V *m, K k,  \
                                                V v)                           \
        {                                                                      \
                if(m->_root == MAP_LEAF)                                       \
                {                                                              \
                        struct node_##K##_##V *new_node =                      \
                            node_new_##K##_##V(&k, &v);                        \
                        new_node->_color = MAP_BLACK;                          \
                        new_node->_parent = MAP_LEAF;                          \
                        m->_root = new_node;                                   \
                        m->_size = 1;                                          \
                }                                                              \
                else                                                           \
                {                                                              \
                        map_insert_node_##K##_##V(m, &k, &v);                  \
                        m->_root->_color = MAP_BLACK;                          \
                }                                                              \
                return m;                                                      \
        }                                                                      \
                                                                               \
        struct map_iterator_##K##_##V map_find_##K##_##V(                      \
            struct map_##K##_##V *m, K k)                                      \
        {                                                                      \
                struct map_iterator_##K##_##V ret = {MAP_LEAF, MAP_LEAF};      \
                struct node_##K##_##V *prev;                                   \
                if(m->_root)                                                   \
                {                                                              \
                        struct node_##K##_##V *curr = m->_root;                \
                        while(curr)                                            \
                        {                                                      \
                                prev = curr;                                   \
                                int compare = (map_element_compare_##K##_##V(  \
                                    &curr->_key, &k));                         \
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
                                        map_iterator_next_##K##_##V(&ret);     \
                                        break;                                 \
                                }                                              \
                        }                                                      \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        static struct node_##K##_##V *map_find_node_##K##_##V(                 \
            struct map_##K##_##V *m, K k)                                      \
        {                                                                      \
                struct map_iterator_##K##_##V i = map_find_##K##_##V(m, k);    \
                return i.curr;                                                 \
        }                                                                      \
                                                                               \
        V *map_at_##K##_##V(struct map_##K##_##V *m, K k)                      \
        {                                                                      \
                struct node_##K##_##V *n = map_find_node_##K##_##V(m, k);      \
                V *ret;                                                        \
                if(!n)                                                         \
                {                                                              \
                        V new_value;                                           \
                        map_element_init_##K##_##V(&new_value);                \
                        map_set_##K##_##V(m, k, new_value);                    \
                        ret = map_at_##K##_##V(m, k);                          \
                }                                                              \
                else                                                           \
                {                                                              \
                        ret = &n->_value;                                      \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        static void map_erase_rebalanse_##K##_##V(struct map_##K##_##V *m,     \
                                                  struct node_##K##_##V *n,    \
                                                  struct node_##K##_##V *p)    \
        {                                                                      \
                if(p)                                                          \
                {                                                              \
                        struct node_##K##_##V *s;                              \
                        struct node_##K##_##V *r;                              \
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
                                        map_rotate_left_##K##_##V(m, s, p);    \
                                }                                              \
                                else if(s->_left &&                            \
                                        s->_left->_color == MAP_RED)           \
                                {                                              \
                                        r = s->_left;                          \
                                        map_rotate_right_left_##K##_##V(m, r,  \
                                                                        s, p); \
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
                                        map_rotate_right_##K##_##V(m, s, p);   \
                                }                                              \
                                else if(s->_right &&                           \
                                        s->_right->_color == MAP_RED)          \
                                {                                              \
                                        r = s->_right;                         \
                                        map_rotate_left_right_##K##_##V(m, r,  \
                                                                        s, p); \
                                }                                              \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        static void node_move_##K##_##V(struct node_##K##_##V *first,          \
                                        struct node_##K##_##V *second)         \
        {                                                                      \
                first->_parent, second->_parent;                               \
                first->_left, second->_left;                                   \
                first->_right, second->_right;                                 \
                first->_color = second->_color;                                \
                struct node_##K##_##V *p = first->_parent;                     \
                if(p)                                                          \
                {                                                              \
                        if(p->_right == second)                                \
                        {                                                      \
                                p->_right = first;                             \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                p->_left = first;                              \
                        }                                                      \
                }                                                              \
                if(first->_left)                                               \
                {                                                              \
                        first->_left->_parent = first;                         \
                }                                                              \
                if(first->_right)                                              \
                {                                                              \
                        first->_right->_parent = first;                        \
                }                                                              \
        }                                                                      \
                                                                               \
        static struct node_##K##_##V *map_erase_node_##K##_##V(                \
            struct map_##K##_##V *m, struct node_##K##_##V *n)                 \
        {                                                                      \
                struct node_##K##_##V *succ_c;                                 \
                struct node_##K##_##V *succ;                                   \
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
                struct node_##K##_##V *succ_p = succ->_parent;                 \
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
                        if(map_element_copy_##K##_##V ==                       \
                               map_element_default_copy_##K##_##V &&           \
                           map_element_copy_key_##K##_##V ==                   \
                               map_element_default_copy_key_##K##_##V)         \
                        {                                                      \
                                map_element_copy_key_##K##_##V(&n->_key,       \
                                                               &succ->_key);   \
                                map_element_copy_##K##_##V(&n->_value,         \
                                                           &succ->_value);     \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                node_move_##K##_##V(n, succ);                  \
                        }                                                      \
                }                                                              \
                if(succ->_color == MAP_BLACK)                                  \
                {                                                              \
                        map_erase_rebalanse_##K##_##V(m, succ_c, succ_p);      \
                }                                                              \
                if(m->_root)                                                   \
                {                                                              \
                        m->_root->_color = MAP_BLACK;                          \
                }                                                              \
                --m->_size;                                                    \
                return succ;                                                   \
        }                                                                      \
                                                                               \
        int map_erase_##K##_##V(struct map_##K##_##V *m, const K key)          \
        {                                                                      \
                struct node_##K##_##V *n = map_find_node_##K##_##V(m, key);    \
                int ret = (n) ? 1 : 0;                                         \
                if(ret)                                                        \
                {                                                              \
                        map_element_free_##K##_##V(&n->_key, &n->_value);      \
                        free(map_erase_node_##K##_##V(m, n));                  \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        int map_iterator_erase_##K##_##V(struct map_##K##_##V *m,              \
                                         struct map_iterator_##K##_##V *i)     \
        {                                                                      \
                struct map_iterator_##K##_##V tmp = {i->curr, i->next};        \
                map_iterator_next_##K##_##V(&tmp);                             \
                int ret = (i->curr) ? 1 : 0;                                   \
                if(ret)                                                        \
                {                                                              \
                        map_element_free_##K##_##V(&i->curr->_key,             \
                                                   &i->curr->_value);          \
                        free(map_erase_node_##K##_##V(m, i->curr));            \
                }                                                              \
                i->curr = tmp.curr;                                            \
                i->next = tmp.next;                                            \
                return ret;                                                    \
        }\
\
