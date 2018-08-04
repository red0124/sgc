#pragma once

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef MAP_LEAF
#define MAP_LEAF NULL
#endif

#ifndef RB_COLOR
#define RB_COLOR
enum
{
        MAP_RED,
        MAP_BLACK
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

#ifndef MAP_KILL_COMPARE_WARNING
#warning "MAP: using 'memcmp' as default map element compare"
#warning "MAP: define 'MAP_KILL_COMPARE_WARNING' to remove warning"
#endif

#ifndef MAP_KILL_EQUAL_WARNING
#warning "MAP: using 'memcmp' as default map element equal"
#warning "MAP: define 'MAP_KILL_EQUAL_WARNING' to remove warning"
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
                char color;                                                    \
        };                                                                     \
                                                                               \
        struct map_##K##_##V                                                   \
        {                                                                      \
                size_t size;                                                   \
                struct node_##K##_##V *root;                                   \
        };                                                                     \
                                                                               \
        static void map_element_default_init_##K##_##V(V *el)                  \
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
        static void map_element_default_copy_##K##_##V(V *dst, const V *src)   \
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
        static void map_element_default_copy_key_##K##_##V(K *dst,             \
                                                           const K *src)       \
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
        static int map_element_default_equal_##K##_##V(const V *first,         \
                                                       const V *second)        \
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
        static int map_element_default_equal_key_##K##_##V(const K *first,     \
                                                           const K *second)    \
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
        static int map_element_default_compare_##K##_##V(const void *first,    \
                                                         const void *second)   \
        {                                                                      \
                return memcmp(first, second, sizeof(K)) > 0;                   \
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
        static void map_element_default_free_##K##_##V(K *k, V *v)             \
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
                map_element_compare_##K##_##V = comp;                          \
        }                                                                      \
                                                                               \
        static size_t map_stack_size_##K##_##V(size_t size)                    \
        {                                                                      \
                return sizeof(struct node_##K##_##V *) * (size + 1);           \
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
                                stack[stack_size] = curr;                      \
                                ++stack_size;                                  \
                                curr = curr->left;                             \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                if(stack_size == 0)                            \
                                {                                              \
                                        break;                                 \
                                }                                              \
                                --stack_size;                                  \
                                curr = stack[stack_size];                      \
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
        /* change it */                                                        \
        int map_equal_##K##_##V(const struct map_##K##_##V *first,             \
                                const struct map_##K##_##V *second)            \
        {                                                                      \
                int equal = (first == second);                                 \
                if(equal == 0 && first->size == second->size)                  \
                {                                                              \
                        equal = 1;                                             \
                                                                               \
                        struct node_##K##_##V **stack_first =                  \
                            (struct node_##K##_##V **)malloc(                  \
                                map_stack_size_##K##_##V(first->size));        \
                                                                               \
                        struct node_##K##_##V *curr_first = first->root;       \
                        struct node_##K##_##V *tmp_first = first->root;        \
                                                                               \
                        struct node_##K##_##V **stack_second =                 \
                            (struct node_##K##_##V **)malloc(                  \
                                map_stack_size_##K##_##V(second->size));       \
                                                                               \
                        struct node_##K##_##V *curr_second = second->root;     \
                        struct node_##K##_##V *tmp_second = second->root;      \
                                                                               \
                        size_t stack_size_first = 0;                           \
                        size_t stack_size_second = 0;                          \
                        while(1)                                               \
                        {                                                      \
                                if(curr_first != MAP_LEAF)                     \
                                {                                              \
                                        stack_first[stack_size_first] =        \
                                            curr_first;                        \
                                        ++stack_size_first;                    \
                                        curr_first = curr_first->left;         \
                                }                                              \
                                else                                           \
                                {                                              \
                                        if(stack_size_first == 0)              \
                                        {                                      \
                                                break;                         \
                                        }                                      \
                                        --stack_size_first;                    \
                                        curr_first =                           \
                                            stack_first[stack_size_first];     \
                                                                               \
                                        tmp_first = curr_first;                \
                                        curr_first = curr_first->right;        \
                                }                                              \
                                if(curr_second != MAP_LEAF)                    \
                                {                                              \
                                        stack_second[stack_size_second] =      \
                                            curr_second;                       \
                                        ++stack_size_second;                   \
                                        curr_second = curr_second->left;       \
                                }                                              \
                                else                                           \
                                {                                              \
                                        if(stack_size_second == 0)             \
                                        {                                      \
                                                break;                         \
                                        }                                      \
                                        --stack_size_second;                   \
                                        curr_second =                          \
                                            stack_second[stack_size_second];   \
                                                                               \
                                        tmp_second = curr_second;              \
                                        curr_second = curr_second->right;      \
                                }                                              \
                                if((tmp_first != MAP_LEAF &&                   \
                                    tmp_second != MAP_LEAF) &&                 \
                                   (!map_element_equal_key_##K##_##V(          \
                                        &tmp_first->key, &tmp_second->key) ||  \
                                    !map_element_equal_##K##_##V(              \
                                        &tmp_first->value,                     \
                                        &tmp_second->value)))                  \
                                {                                              \
                                        equal = 0;                             \
                                        break;                                 \
                                }                                              \
                        }                                                      \
                        free(stack_first);                                     \
                        free(stack_second);                                    \
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
                                else if(curr_src->left != MAP_LEAF &&          \
                                        curr_dst->left == MAP_LEAF)            \
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
                                   void (*operate)(K *, V *))                  \
        {                                                                      \
                struct node_##K##_##V **stack =                                \
                    (struct node_##K##_##V **)malloc(                          \
                        map_stack_size_##K##_##V(m->size));                    \
                                                                               \
                struct node_##K##_##V *curr = m->root;                         \
                                                                               \
                size_t stack_size = 0;                                         \
                while(1)                                                       \
                {                                                              \
                        if(curr != MAP_LEAF)                                   \
                        {                                                      \
                                stack[stack_size] = curr;                      \
                                ++stack_size;                                  \
                                curr = curr->left;                             \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                if(stack_size == 0)                            \
                                {                                              \
                                        break;                                 \
                                }                                              \
                                --stack_size;                                  \
                                curr = stack[stack_size];                      \
                                operate(&curr->key, &curr->value);             \
                                curr = curr->right;                            \
                        }                                                      \
                }                                                              \
                free(stack);                                                   \
        }                                                                      \
                                                                               \
        void map_operate_inverted_##K##_##V(struct map_##K##_##V *m,           \
                                            void (*operate)(K *, V *))         \
        {                                                                      \
                struct node_##K##_##V **stack =                                \
                    (struct node_##K##_##V **)malloc(                          \
                        map_stack_size_##K##_##V(m->size));                    \
                                                                               \
                struct node_##K##_##V *curr = m->root;                         \
                                                                               \
                size_t stack_size = 0;                                         \
                while(1)                                                       \
                {                                                              \
                        if(curr != MAP_LEAF)                                   \
                        {                                                      \
                                stack[stack_size] = curr;                      \
                                ++stack_size;                                  \
                                curr = curr->right;                            \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                if(stack_size == 0)                            \
                                {                                              \
                                        break;                                 \
                                }                                              \
                                --stack_size;                                  \
                                curr = stack[stack_size];                      \
                                operate(&curr->key, &curr->value);             \
                                curr = curr->left;                             \
                        }                                                      \
                }                                                              \
                free(stack);                                                   \
        }                                                                      \
                                                                               \
        void map_operate_to_##K##_##V(struct map_##K##_##V *m,                 \
                                      void (*operate)(K *, V *, void *),       \
                                      void *argout)                            \
        {                                                                      \
                struct node_##K##_##V **stack =                                \
                    (struct node_##K##_##V **)malloc(                          \
                        map_stack_size_##K##_##V(m->size));                    \
                                                                               \
                struct node_##K##_##V *curr = m->root;                         \
                                                                               \
                size_t stack_size = 0;                                         \
                while(1)                                                       \
                {                                                              \
                        if(curr != MAP_LEAF)                                   \
                        {                                                      \
                                stack[stack_size] = curr;                      \
                                ++stack_size;                                  \
                                curr = curr->left;                             \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                if(stack_size == 0)                            \
                                {                                              \
                                        break;                                 \
                                }                                              \
                                --stack_size;                                  \
                                curr = stack[stack_size];                      \
                                operate(&curr->key, &curr->value, argout);     \
                                curr = curr->right;                            \
                        }                                                      \
                }                                                              \
                free(stack);                                                   \
        }                                                                      \
                                                                               \
        void map_operate_inverted_to_##K##_##V(                                \
            struct map_##K##_##V *m, void (*operate)(K *, V *, void *),        \
            void *argout)                                                      \
        {                                                                      \
                struct node_##K##_##V **stack =                                \
                    (struct node_##K##_##V **)malloc(                          \
                        map_stack_size_##K##_##V(m->size));                    \
                                                                               \
                struct node_##K##_##V *curr = m->root;                         \
                                                                               \
                size_t stack_size = 0;                                         \
                while(1)                                                       \
                {                                                              \
                        if(curr != MAP_LEAF)                                   \
                        {                                                      \
                                stack[stack_size] = curr;                      \
                                ++stack_size;                                  \
                                curr = curr->right;                            \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                if(stack_size == 0)                            \
                                {                                              \
                                        break;                                 \
                                }                                              \
                                --stack_size;                                  \
                                curr = stack[stack_size];                      \
                                operate(&curr->key, &curr->value, argout);     \
                                curr = curr->left;                             \
                        }                                                      \
                }                                                              \
                free(stack);                                                   \
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
        static void map_insert_node_##K##_##V(struct map_##K##_##V *m,         \
                                              struct node_##K##_##V *new_node) \
        {                                                                      \
                struct node_##K##_##V *parent = m->root;                       \
                for(;;)                                                        \
                {                                                              \
                        if(map_element_compare_##K##_##V(&parent->key,         \
                                                         &new_node->key) > 0)  \
                        {                                                      \
                                if(parent->left == MAP_LEAF)                   \
                                {                                              \
                                        parent->left = new_node;               \
                                        break;                                 \
                                }                                              \
                                parent = parent->left;                         \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                if(parent->right == MAP_LEAF)                  \
                                {                                              \
                                        parent->right = new_node;              \
                                        break;                                 \
                                }                                              \
                                parent = parent->right;                        \
                        }                                                      \
                }                                                              \
                new_node->parent = parent;                                     \
                map_check_color_##K##_##V(m, new_node);                        \
        }                                                                      \
                                                                               \
        void map_set_##K##_##V(struct map_##K##_##V *m, const K key, V value)  \
        {                                                                      \
                /* need to check if a memeber with that key is already added   \
                 */                                                            \
                                                                               \
                struct node_##K##_##V *new_node =                              \
                    (struct node_##K##_##V *)malloc(                           \
                        sizeof(struct node_##K##_##V));                        \
                map_element_copy_key_##K##_##V(&new_node->key, &key);          \
                map_element_copy_##K##_##V(&new_node->value, &value);          \
                new_node->left = new_node->right = MAP_LEAF;                   \
                if(m->root == MAP_LEAF)                                        \
                {                                                              \
                        new_node->color = MAP_BLACK;                           \
                        new_node->parent = MAP_LEAF;                           \
                        m->root = new_node;                                    \
                }                                                              \
                else                                                           \
                {                                                              \
                        new_node->color = MAP_RED;                             \
                        map_insert_node_##K##_##V(m, new_node);                \
                        m->root->color = MAP_BLACK;                            \
                }                                                              \
                m->size++;                                                     \
        }
\
\
\
