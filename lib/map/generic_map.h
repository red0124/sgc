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
        MAP_DBLACK
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
                struct node_##K##_##V *parent;                                 \
                struct node_##K##_##V *left;                                   \
                struct node_##K##_##V *right;                                  \
                K key;                                                         \
                V value;                                                       \
                enum map_color color;                                          \
        };                                                                     \
                                                                               \
        struct map_##K##_##V                                                   \
        {                                                                      \
                size_t size;                                                   \
                struct node_##K##_##V *root;                                   \
        };                                                                     \
                                                                               \
        void map_element_default_init_##K##_##V(V *el)                         \
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
        void map_element_default_copy_##K##_##V(V *dst, const V *src)          \
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
        void map_element_default_copy_key_##K##_##V(K *dst, const K *src)      \
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
        int map_element_default_equal_##K##_##V(const V *first,                \
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
        int map_element_default_equal_key_##K##_##V(const K *first,            \
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
        int map_element_default_compare_##K##_##V(const void *first,           \
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
        void map_element_default_free_##K##_##V(K *k, V *v)                    \
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
        static struct node_##K##_##V *node_begin_##K##_##V(                    \
            struct node_##K##_##V *n)                                          \
        {                                                                      \
                while(n->left)                                                 \
                {                                                              \
                        n = n->left;                                           \
                }                                                              \
                return n;                                                      \
        }                                                                      \
                                                                               \
        static struct node_##K##_##V *node_end_##K##_##V(                      \
            struct node_##K##_##V *n)                                          \
        {                                                                      \
                while(n->right)                                                \
                {                                                              \
                        n = n->right;                                          \
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
                if(i->next->right)                                             \
                {                                                              \
                        i->next = node_begin_##K##_##V(i->next->right);        \
                }                                                              \
                else                                                           \
                {                                                              \
                        struct node_##K##_##V *parent = i->next->parent;       \
                        while(parent && parent->right == i->next)              \
                        {                                                      \
                                i->next = parent;                              \
                                parent = parent->parent;                       \
                        }                                                      \
                        if(i->next->right != parent)                           \
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
                    (m->root) ? node_begin_##K##_##V(m->root) : MAP_LEAF;      \
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
                if(i->curr->left)                                              \
                {                                                              \
                        i->curr = node_end_##K##_##V(i->curr->left);           \
                }                                                              \
                else                                                           \
                {                                                              \
                        struct node_##K##_##V *parent = i->curr->parent;       \
                        while(parent && parent->left == i->curr)               \
                        {                                                      \
                                i->curr = parent;                              \
                                parent = parent->parent;                       \
                        }                                                      \
                        if(i->curr->right != parent)                           \
                        {                                                      \
                                i->curr = parent;                              \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void map_iterator_end_##K##_##V(struct map_##K##_##V *m,               \
                                        struct map_iterator_##K##_##V *i)      \
        {                                                                      \
                i->curr = (m->root) ? node_end_##K##_##V(m->root) : MAP_LEAF;  \
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
                    map_stack_size_##K##_##V(m->size));                        \
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
                if(i->next->right)                                             \
                {                                                              \
                        i->stack[i->stack_size++] = i->next;                   \
                        i->next = i->next->right;                              \
                        while(i->next->left)                                   \
                        {                                                      \
                                i->stack[i->stack_size++] = i->next;           \
                                i->next = i->next->left;                       \
                        }                                                      \
                }                                                              \
                else                                                           \
                {                                                              \
                        struct node_##K##_##V *parent =                        \
                            i->stack[--i->stack_size];                         \
                        while(parent && parent->right == i->next)              \
                        {                                                      \
                                i->next = parent;                              \
                                parent = i->stack[--i->stack_size];            \
                        }                                                      \
                        if(i->next->right != parent)                           \
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
                struct node_##K##_##V *curr = m->root;                         \
                if(!curr)                                                      \
                {                                                              \
                        i->curr = MAP_LEAF;                                    \
                        i->next = MAP_LEAF;                                    \
                        return;                                                \
                }                                                              \
                                                                               \
                i->stack[i->stack_size++] = MAP_LEAF;                          \
                while(curr->left)                                              \
                {                                                              \
                        i->stack[i->stack_size++] = curr;                      \
                        curr = curr->left;                                     \
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
                if(i->curr->left)                                              \
                {                                                              \
                        i->stack[i->stack_size++] = i->curr;                   \
                        i->curr = i->curr->left;                               \
                        while(i->curr->right)                                  \
                        {                                                      \
                                i->stack[i->stack_size++] = i->curr;           \
                                i->curr = i->curr->right;                      \
                        }                                                      \
                }                                                              \
                else                                                           \
                {                                                              \
                        struct node_##K##_##V *parent =                        \
                            i->stack[--i->stack_size];                         \
                        while(parent && parent->left == i->curr)               \
                        {                                                      \
                                parent = i->stack[--i->stack_size];            \
                                i->curr = parent;                              \
                        }                                                      \
                        if(i->curr->right != parent)                           \
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
                struct node_##K##_##V *curr = m->root;                         \
                if(!curr)                                                      \
                {                                                              \
                        i->curr = MAP_LEAF;                                    \
                        i->next = MAP_LEAF;                                    \
                        return;                                                \
                }                                                              \
                                                                               \
                i->stack[i->stack_size++] = MAP_LEAF;                          \
                while(curr->right)                                             \
                {                                                              \
                        i->stack[i->stack_size++] = curr;                      \
                        curr = curr->right;                                    \
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
        static void node_init_##K##_##V(struct node_##K##_##V **n, const K *k, \
                                        const V *v)                            \
        {                                                                      \
                *n = (struct node_##K##_##V *)malloc(                          \
                    sizeof(struct node_##K##_##V));                            \
                map_element_copy_key_##K##_##V(&(*n)->key, k);                 \
                map_element_copy_##K##_##V(&(*n)->value, v);                   \
                (*n)->left = (*n)->right = MAP_LEAF;                           \
                (*n)->color = MAP_RED;                                         \
        }                                                                      \
                                                                               \
        size_t map_size_##K##_##V(const struct map_##K##_##V *m)               \
        {                                                                      \
                return m->size;                                                \
        }                                                                      \
                                                                               \
        void map_init_##K##_##V(struct map_##K##_##V *m,                       \
                                int (*comp)(const void *, const void *))       \
        {                                                                      \
                m->size = 0;                                                   \
                m->root = MAP_LEAF;                                            \
                if(comp)                                                       \
                {                                                              \
                        map_element_compare_##K##_##V = comp;                  \
                }                                                              \
        }                                                                      \
                                                                               \
        void map_free_##K##_##V(struct map_##K##_##V *m)                       \
        {                                                                      \
                struct node_##K##_##V **stack =                                \
                    (struct node_##K##_##V **)malloc(                          \
                        map_stack_size_##K##_##V(m->size));                    \
                                                                               \
                struct node_##K##_##V *curr = m->root;                         \
                struct node_##K##_##V *tmp = NULL;                             \
                                                                               \
                size_t stack_size = 0;                                         \
                while(1)                                                       \
                {                                                              \
                        if(curr != MAP_LEAF)                                   \
                        {                                                      \
                                stack[stack_size++] = curr;                    \
                                curr = curr->left;                             \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                if(stack_size == 0)                            \
                                {                                              \
                                        break;                                 \
                                }                                              \
                                curr = stack[--stack_size];                    \
                                tmp = curr;                                    \
                                curr = curr->right;                            \
                                if(map_element_free_##K##_##V !=               \
                                   map_element_default_free_##K##_##V)         \
                                {                                              \
                                        map_element_free_##K##_##V(            \
                                            &tmp->key, &tmp->value);           \
                                }                                              \
                                free(tmp);                                     \
                        }                                                      \
                }                                                              \
                free(stack);                                                   \
                m->root = MAP_LEAF;                                            \
                m->size = 0;                                                   \
        }                                                                      \
                                                                               \
        int map_equal_##K##_##V(struct map_##K##_##V *first,                   \
                                struct map_##K##_##V *second)                  \
        {                                                                      \
                int equal = (first == second);                                 \
                if(equal == 0 && first->size == second->size)                  \
                {                                                              \
                        equal = 1;                                             \
                        struct map_fast_iterator_##K##_##V it_first;           \
                        map_fast_iterator_begin_##K##_##V(first, &it_first);   \
                                                                               \
                        struct map_fast_iterator_##K##_##V it_second;          \
                        map_fast_iterator_begin_##K##_##V(second, &it_second); \
                                                                               \
                        for(size_t i = 0; i < first->size; ++i)                \
                        {                                                      \
                                if((!map_element_equal_key_##K##_##V(          \
                                        &it_first.curr->key,                   \
                                        &it_second.curr->key) ||               \
                                    !map_element_equal_##K##_##V(              \
                                        &it_first.curr->value,                 \
                                        &it_second.curr->value)))              \
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
                dst->size = src->size;                                         \
                dst->root = MAP_LEAF;                                          \
                                                                               \
                if(src->size != 0)                                             \
                {                                                              \
                        dst->root = (struct node_##K##_##V *)malloc(           \
                            sizeof(struct node_##K##_##V));                    \
                                                                               \
                        map_element_copy_##K##_##V(&dst->root->value,          \
                                                   &src->root->value);         \
                        map_element_copy_key_##K##_##V(&dst->root->key,        \
                                                       &src->root->key);       \
                        dst->root->color = src->root->color;                   \
                        dst->root->left = dst->root->right =                   \
                            dst->root->parent = MAP_LEAF;                      \
                                                                               \
                        struct node_##K##_##V **stack_src =                    \
                            (struct node_##K##_##V **)malloc(                  \
                                map_stack_size_##K##_##V(src->size));          \
                                                                               \
                        struct node_##K##_##V *curr_src = src->root;           \
                                                                               \
                        struct node_##K##_##V **stack_dst =                    \
                            (struct node_##K##_##V **)malloc(                  \
                                map_stack_size_##K##_##V(dst->size));          \
                                                                               \
                        struct node_##K##_##V *curr_dst = dst->root;           \
                                                                               \
                        struct node_##K##_##V *tmp = MAP_LEAF;                 \
                                                                               \
                        stack_src[0] = MAP_LEAF;                               \
                        stack_dst[0] = MAP_LEAF;                               \
                                                                               \
                        stack_src[1] = src->root;                              \
                        stack_dst[1] = dst->root;                              \
                        size_t stack_size = 2;                                 \
                                                                               \
                        while(stack_size > 0)                                  \
                        {                                                      \
                                if(!((curr_src->left != MAP_LEAF &&            \
                                      curr_dst->left == MAP_LEAF) ||           \
                                     (curr_src->right != MAP_LEAF &&           \
                                      curr_dst->right == MAP_LEAF)))           \
                                {                                              \
                                        --stack_size;                          \
                                        curr_src = stack_src[stack_size];      \
                                        curr_dst = stack_dst[stack_size];      \
                                        continue;                              \
                                }                                              \
                                                                               \
                                if(curr_src->left != MAP_LEAF &&               \
                                   curr_dst->left == MAP_LEAF)                 \
                                {                                              \
                                        curr_dst->left =                       \
                                            (struct node_##K##_##V *)malloc(   \
                                                sizeof(                        \
                                                    struct node_##K##_##V));   \
                                        tmp = curr_dst->left;                  \
                                        tmp->parent = curr_dst;                \
                                        curr_src = curr_src->left;             \
                                }                                              \
                                else                                           \
                                {                                              \
                                        curr_dst->right =                      \
                                            (struct node_##K##_##V *)malloc(   \
                                                sizeof(                        \
                                                    struct node_##K##_##V));   \
                                        tmp = curr_dst->right;                 \
                                        tmp->parent = curr_dst;                \
                                        curr_src = curr_src->right;            \
                                }                                              \
                                tmp->left = tmp->right = MAP_LEAF;             \
                                curr_dst = tmp;                                \
                                map_element_copy_##K##_##V(&curr_dst->value,   \
                                                           &curr_src->value);  \
                                map_element_copy_key_##K##_##V(                \
                                    &curr_dst->key, &curr_src->key);           \
                                curr_dst->color = curr_src->color;             \
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
                for(size_t i = 0; i < m->size; ++i)                            \
                {                                                              \
                        operate(&it.curr->key, &it.curr->value);               \
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
                for(size_t i = 0; i < m->size; ++i)                            \
                {                                                              \
                        operate(&it.curr->key, &it.curr->value);               \
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
                for(size_t i = 0; i < m->size; ++i)                            \
                {                                                              \
                        operate(&it.curr->key, &it.curr->value, argout);       \
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
                for(size_t i = 0; i < m->size; ++i)                            \
                {                                                              \
                        operate(&it.curr->key, &it.curr->value, argout);       \
                        map_fast_iterator_prev_##K##_##V(&it);                 \
                }                                                              \
                                                                               \
                map_fast_iterator_free_##K##_##V(&it);                         \
        }                                                                      \
                                                                               \
        static int map_is_left_child_##K##_##V(struct node_##K##_##V *n,       \
                                               struct node_##K##_##V *parent)  \
        {                                                                      \
                return (n == parent->left);                                    \
        }                                                                      \
                                                                               \
        static struct node_##K##_##V *map_brother_##K##_##V(                   \
            struct node_##K##_##V *n, struct node_##K##_##V *parent)           \
        {                                                                      \
                struct node_##K##_##V *brother = NULL;                         \
                if(parent != MAP_LEAF)                                         \
                {                                                              \
                        brother = (n == parent->left) ? parent->right          \
                                                      : parent->left;          \
                }                                                              \
                return brother;                                                \
        }                                                                      \
        static void map_rotate_left_##K##_##V(struct map_##K##_##V *m,         \
                                              struct node_##K##_##V *parent,   \
                                              struct node_##K##_##V *gparent)  \
        {                                                                      \
                struct node_##K##_##V *left = parent->left;                    \
                gparent->right = left;                                         \
                if(left != MAP_LEAF)                                           \
                {                                                              \
                        left->parent = gparent;                                \
                }                                                              \
                if(gparent == m->root)                                         \
                {                                                              \
                        m->root = parent;                                      \
                        parent->parent = MAP_LEAF;                             \
                }                                                              \
                else                                                           \
                {                                                              \
                        struct node_##K##_##V *ggparent = gparent->parent;     \
                        parent->parent = ggparent;                             \
                        if(map_is_left_child_##K##_##V(gparent, ggparent))     \
                        {                                                      \
                                ggparent->left = parent;                       \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                ggparent->right = parent;                      \
                        }                                                      \
                }                                                              \
                parent->left = gparent;                                        \
                gparent->parent = parent;                                      \
        }                                                                      \
                                                                               \
        static void map_rotate_right_##K##_##V(struct map_##K##_##V *m,        \
                                               struct node_##K##_##V *parent,  \
                                               struct node_##K##_##V *gparent) \
        {                                                                      \
                struct node_##K##_##V *right = parent->right;                  \
                gparent->left = right;                                         \
                if(right != MAP_LEAF)                                          \
                {                                                              \
                        right->parent = gparent;                               \
                }                                                              \
                if(gparent == m->root)                                         \
                {                                                              \
                        m->root = parent;                                      \
                        parent->parent = MAP_LEAF;                             \
                }                                                              \
                else                                                           \
                {                                                              \
                        struct node_##K##_##V *ggparent = gparent->parent;     \
                        parent->parent = ggparent;                             \
                        if(map_is_left_child_##K##_##V(gparent, ggparent))     \
                        {                                                      \
                                ggparent->left = parent;                       \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                ggparent->right = parent;                      \
                        }                                                      \
                }                                                              \
                parent->right = gparent;                                       \
                gparent->parent = parent;                                      \
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
                                n->color = MAP_RED;                            \
                                parent->color = MAP_BLACK;                     \
                                struct node_##K##_##V *brother =               \
                                    parent->right;                             \
                                if(brother != MAP_LEAF)                        \
                                {                                              \
                                        brother->color = MAP_RED;              \
                                }                                              \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                map_rotate_right_left_##K##_##V(m, n, parent,  \
                                                                gparent);      \
                                n->color = MAP_BLACK;                          \
                                n->right->color = MAP_RED;                     \
                                n->left->color = MAP_RED;                      \
                        }                                                      \
                }                                                              \
                else                                                           \
                {                                                              \
                        if(!map_is_left_child_##K##_##V(parent, gparent))      \
                        {                                                      \
                                map_rotate_left_##K##_##V(m, parent, gparent); \
                                n->color = MAP_RED;                            \
                                parent->color = MAP_BLACK;                     \
                                struct node_##K##_##V *brother =               \
                                    parent->right;                             \
                                if(brother != MAP_LEAF)                        \
                                {                                              \
                                        brother->color = MAP_RED;              \
                                }                                              \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                map_rotate_left_right_##K##_##V(m, n, parent,  \
                                                                gparent);      \
                                n->color = MAP_BLACK;                          \
                                n->right->color = MAP_RED;                     \
                                n->left->color = MAP_RED;                      \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        static void map_corect_tree_##K##_##V(struct map_##K##_##V *m,         \
                                              struct node_##K##_##V *n,        \
                                              struct node_##K##_##V *parent)   \
        {                                                                      \
                struct node_##K##_##V *gparent = parent->parent;               \
                struct node_##K##_##V *aunt =                                  \
                    map_brother_##K##_##V(parent, gparent);                    \
                if(aunt == MAP_LEAF || aunt->color == MAP_BLACK)               \
                {                                                              \
                        map_rotate_##K##_##V(m, n, parent, gparent);           \
                }                                                              \
                else if(aunt != NULL)                                          \
                {                                                              \
                        aunt->color = MAP_BLACK;                               \
                }                                                              \
                gparent->color = MAP_RED;                                      \
                parent->color = MAP_BLACK;                                     \
        }                                                                      \
                                                                               \
        static void map_check_color_##K##_##V(struct map_##K##_##V *m,         \
                                              struct node_##K##_##V *n)        \
        {                                                                      \
                if(n == m->root)                                               \
                {                                                              \
                        return;                                                \
                }                                                              \
                struct node_##K##_##V *parent = n->parent;                     \
                if(n->color == MAP_RED && parent->color == MAP_RED)            \
                {                                                              \
                        map_corect_tree_##K##_##V(m, n, parent);               \
                }                                                              \
                map_check_color_##K##_##V(m, parent);                          \
        }                                                                      \
                                                                               \
        static void map_insert_node_##K##_##V(struct map_##K##_##V *m, K *k,   \
                                              V *v)                            \
        {                                                                      \
                struct node_##K##_##V *parent = m->root;                       \
                struct node_##K##_##V *new_node;                               \
                for(;;)                                                        \
                {                                                              \
                        int compare =                                          \
                            (map_element_compare_##K##_##V(&parent->key, k));  \
                        if(!compare)                                           \
                        {                                                      \
                                map_element_copy_##K##_##V(&parent->value, v); \
                                return;                                        \
                        }                                                      \
                                                                               \
                        if(compare > 0)                                        \
                        {                                                      \
                                if(parent->left == MAP_LEAF)                   \
                                {                                              \
                                        node_init_##K##_##V(&new_node, k, v);  \
                                        parent->left = new_node;               \
                                        break;                                 \
                                }                                              \
                                parent = parent->left;                         \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                if(parent->right == MAP_LEAF)                  \
                                {                                              \
                                        node_init_##K##_##V(&new_node, k, v);  \
                                        parent->right = new_node;              \
                                        break;                                 \
                                }                                              \
                                parent = parent->right;                        \
                        }                                                      \
                }                                                              \
                new_node->parent = parent;                                     \
                map_check_color_##K##_##V(m, new_node);                        \
                m->size++;                                                     \
        }                                                                      \
                                                                               \
        void map_set_##K##_##V(struct map_##K##_##V *m, K k, V v)              \
        {                                                                      \
                if(m->root == MAP_LEAF)                                        \
                {                                                              \
                        struct node_##K##_##V *new_node;                       \
                        node_init_##K##_##V(&new_node, &k, &v);                \
                        new_node->color = MAP_BLACK;                           \
                        new_node->parent = MAP_LEAF;                           \
                        m->root = new_node;                                    \
                        m->size = 1;                                           \
                }                                                              \
                else                                                           \
                {                                                              \
                        map_insert_node_##K##_##V(m, &k, &v);                  \
                        m->root->color = MAP_BLACK;                            \
                }                                                              \
        }                                                                      \
                                                                               \
        V *map_at_##K##_##V(struct map_##K##_##V *m, K k)                      \
        {                                                                      \
                V *ret = NULL;                                                 \
                if(m->root)                                                    \
                {                                                              \
                        struct node_##K##_##V *curr = m->root;                 \
                        while(curr)                                            \
                        {                                                      \
                                int compare = (map_element_compare_##K##_##V(  \
                                    &curr->key, &k));                          \
                                if(!compare)                                   \
                                {                                              \
                                        ret = &curr->value;                    \
                                        break;                                 \
                                }                                              \
                                                                               \
                                if(compare > 0)                                \
                                {                                              \
                                        curr = curr->left;                     \
                                }                                              \
                                else                                           \
                                {                                              \
                                        curr = curr->right;                    \
                                }                                              \
                        }                                                      \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        static void map_erase_fixup_##K##_##V(struct map_##K##_##V *m,         \
                                              struct node_##K##_##V *n)        \
        {                                                                      \
        }                                                                      \
                                                                               \
        struct node_##K##_##V *map_erase_##K##_##V(struct map_##K##_##V *m,    \
                                                   struct node_##K##_##V *n)   \
        {                                                                      \
                struct node_##K##_##V *curr;                                   \
                struct node_##K##_##V *tmp;                                    \
                if(!n->left || !n->right)                                      \
                {                                                              \
                        tmp = n;                                               \
                }                                                              \
                else                                                           \
                {                                                              \
                        tmp = n;                                               \
                        while(tmp->right)                                      \
                        {                                                      \
                                tmp = tmp->right;                              \
                        }                                                      \
                }                                                              \
                                                                               \
                curr = (tmp->left) ? tmp->left : tmp->right;                   \
                struct node_##K##_##V *parent = tmp->parent;                   \
		if(curr)                                                       \
		{                                                              \
			curr->parent = parent;                                 \
		}                                                              \
                                                                               \
                if(!tmp->parent)                                               \
                {                                                              \
                        m->root = curr;                                        \
                }                                                              \
                else                                                           \
                {                                                              \
                        if(tmp == parent->left)                                \
                        {                                                      \
                                parent->left = curr;                           \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                parent->right = curr;                          \
                        }                                                      \
                }                                                              \
                                                                               \
                if(tmp != n)                                                   \
                {                                                              \
                        map_element_copy_##K##_##V(&n->value, &tmp->value);    \
                        map_element_copy_key_##K##_##V(&n->key, &tmp->key);    \
                }                                                              \
		                                                               \
                if(tmp->color == MAP_BLACK)                                    \
                {                                                              \
                        map_erase_fixup_##K##_##V(m, curr);                    \
                }                                                              \
		--m->size;                                                     \
                return tmp;                                                    \
        }
