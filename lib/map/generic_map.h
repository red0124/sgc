#pragma once

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef LEAF
#define LEAF NULL
#endif

#ifndef RB_COLOR
#define RB_COLOR
enum
{
        RED,
        BLACK
};
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
                void (*copy)(V *, const V *);                                  \
                void (*copy_key)(K *, const K *);                              \
                void (*free)(K *, V *);                                        \
                int (*comp)(const void *, const void *);                       \
                int (*equ)(const V *, const V *);                              \
                int (*equ_key)(const K *, const K *);                          \
        };                                                                     \
                                                                               \
        static void map_flat_copy_##K##_##V(V *dst, const V *src)              \
        {                                                                      \
                *dst = *src;                                                   \
        }                                                                      \
                                                                               \
        static void map_flat_copy_key_##K##_##V(K *dst, const K *src)          \
        {                                                                      \
                *dst = *src;                                                   \
        }                                                                      \
                                                                               \
        static int map_flat_equ_##K##_##V(const V *first, const V *second)     \
        {                                                                      \
                return memcmp(first, second, sizeof(V)) == 0;                  \
        }                                                                      \
                                                                               \
        static int map_flat_equ_key_##K##_##V(const K *first, const K *second) \
        {                                                                      \
                return memcmp(first, second, sizeof(K)) == 0;                  \
        }                                                                      \
                                                                               \
        static int map_flat_comp_##K##_##V(const void *first,                  \
                                           const void *second)                 \
        {                                                                      \
                return memcmp(first, second, sizeof(K));                       \
        }                                                                      \
                                                                               \
        size_t map_size_##K##_##V(const struct map_##K##_##V *m)               \
        {                                                                      \
                return m->size;                                                \
        }                                                                      \
                                                                               \
        struct map_##K##_##V map_new_##K##_##V(                                \
            int (*comp)(const void *, const void *))                           \
        {                                                                      \
                struct map_##K##_##V m = {                                     \
                    0,                                                         \
                    LEAF,                                                      \
                    map_flat_copy_##K##_##V,                                   \
                    map_flat_copy_key_##K##_##V,                               \
                    NULL,                                                      \
                    (comp == NULL) ? map_flat_comp_##K##_##V : comp,           \
                    map_flat_equ_##K##_##V,                                    \
                    map_flat_equ_key_##K##_##V};                               \
                return m;                                                      \
        }                                                                      \
                                                                               \
        void map_set_copy_##K##_##V(struct map_##K##_##V *m,                   \
                                    void (*copy)(V *, const V *))              \
        {                                                                      \
                m->copy = copy;                                                \
        }                                                                      \
                                                                               \
        void map_set_copy_key_##K##_##V(struct map_##K##_##V *m,               \
                                        void (*copy_key)(K *, const K *))      \
        {                                                                      \
                m->copy_key = copy_key;                                        \
        }                                                                      \
                                                                               \
        void map_set_free_##K##_##V(struct map_##K##_##V *m,                   \
                                    void (*free_)(K *, V *))                   \
        {                                                                      \
                m->free = free_;                                               \
        }                                                                      \
                                                                               \
        void map_set_comp_##K##_##V(struct map_##K##_##V *l,                   \
                                    int (*comp)(const void *, const void *))   \
        {                                                                      \
                l->comp = comp;                                                \
        }                                                                      \
                                                                               \
        void map_set_equ_##K##_##V(struct map_##K##_##V *m,                    \
                                   int (*equ)(const K *, const K *))           \
        {                                                                      \
                m->equ = equ;                                                  \
        }                                                                      \
                                                                               \
        void map_init_##K##_##V(struct map_##K##_##V *m,                       \
                                int (*comp)(const void *, const void *))       \
        {                                                                      \
                m->size = 0;                                                   \
                m->root = LEAF;                                                \
                m->copy = map_flat_copy_##K##_##V;                             \
                m->copy_key = map_flat_copy_key_##K##_##V;                     \
                m->free = NULL;                                                \
                m->comp = (comp == NULL) ? map_flat_comp_##K##_##V : comp;     \
                m->equ = map_flat_equ_##K##_##V;                               \
                m->equ_key = map_flat_equ_key_##K##_##V;                       \
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
                        if(curr != LEAF)                                       \
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
                                if(m->free)                                    \
                                {                                              \
                                        m->free(&tmp->key, &tmp->value);       \
                                }                                              \
                                free(tmp);                                     \
                        }                                                      \
                }                                                              \
                free(stack);                                                   \
                m->root = LEAF;                                                \
                m->size = 0;                                                   \
        }                                                                      \
                                                                               \
        /* change it */                                                        \
        int map_equ_##K##_##V(const struct map_##K##_##V *first,               \
                              const struct map_##K##_##V *second)              \
        {                                                                      \
                if(first->equ == NULL)                                         \
                {                                                              \
                        fprintf(                                               \
                            stderr,                                            \
                            "MAP ERROR :: UNDEFINED EQUALITY CONDITION\n");    \
                        return 0;                                              \
                }                                                              \
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
                                if(curr_first != LEAF)                         \
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
                                if(curr_second != LEAF)                        \
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
                                if((tmp_first != LEAF &&                       \
                                    tmp_second != LEAF) &&                     \
                                   (!first->equ_key(&tmp_first->key,           \
                                                    &tmp_second->key) ||       \
                                    !first->equ(&tmp_first->value,             \
                                                &tmp_second->value)))          \
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
        void map_copy_##K##_##V(struct map_##K##_##V *restrict dst,            \
                                const struct map_##K##_##V *restrict src)      \
        {                                                                      \
                dst->size = src->size;                                         \
                dst->equ = src->equ;                                           \
                dst->equ_key = src->equ_key;                                   \
                dst->copy = src->copy;                                         \
                dst->copy_key = src->copy_key;                                 \
                dst->free = src->free;                                         \
                dst->root = LEAF;                                              \
                                                                               \
                if(src->size != 0)                                             \
                {                                                              \
                        dst->root = (struct node_##K##_##V *)malloc(           \
                            sizeof(struct node_##K##_##V));                    \
                                                                               \
                        src->copy(&dst->root->value, &src->root->value);       \
                        src->copy_key(&dst->root->key, &src->root->key);       \
                        dst->root->color = src->root->color;                   \
                        dst->root->left = dst->root->right =                   \
                            dst->root->parent = LEAF;                          \
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
                        struct node_##K##_##V *tmp = LEAF;                     \
                                                                               \
                        stack_src[0] = LEAF;                                   \
                        stack_dst[0] = LEAF;                                   \
                                                                               \
                        stack_src[1] = src->root;                              \
                        stack_dst[1] = dst->root;                              \
                        size_t stack_size = 2;                                 \
                                                                               \
                        while(stack_size > 0)                                  \
                        {                                                      \
                                if(!((curr_src->left != LEAF &&                \
                                      curr_dst->left == LEAF) ||               \
                                     (curr_src->right != LEAF &&               \
                                      curr_dst->right == LEAF)))               \
                                {                                              \
                                        --stack_size;                          \
                                        curr_src = stack_src[stack_size];      \
                                        curr_dst = stack_dst[stack_size];      \
                                        continue;                              \
                                }                                              \
                                else if(curr_src->left != LEAF &&              \
                                        curr_dst->left == LEAF)                \
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
                                tmp->left = tmp->right = LEAF;                 \
                                curr_dst = tmp;                                \
                                src->copy(&curr_dst->value, &curr_src->value); \
                                src->copy_key(&curr_dst->key, &curr_src->key); \
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
                        if(curr != LEAF)                                       \
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
                        if(curr != LEAF)                                       \
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
                if(parent != LEAF)                                             \
                {                                                              \
                        brother = (n == parent->left) ? parent->right          \
                                                      : parent->left;          \
                }                                                              \
                return brother;                                                \
        }                                                                      \
        static void map_rotate_left_##K##_##V(                                 \
            struct map_##K##_##V *m,        \
            struct node_##K##_##V *parent, struct node_##K##_##V *gparent)     \
        {                                                                      \
                struct node_##K##_##V *left = parent->left;                    \
                gparent->right = left;                                         \
                if(left != LEAF)                                               \
                {                                                              \
                        left->parent = gparent;                                \
                }                                                              \
                if(gparent == m->root)                                         \
                {                                                              \
                        m->root = parent;                                      \
                        parent->parent = LEAF;                                 \
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
        static void map_rotate_right_##K##_##V(                                \
            struct map_##K##_##V *m,           \
            struct node_##K##_##V *parent, struct node_##K##_##V *gparent)     \
        {                                                                      \
                struct node_##K##_##V *right = parent->right;                  \
                gparent->left = right;                                         \
                if(right != LEAF)                                              \
                {                                                              \
                        right->parent = gparent;                               \
                }                                                              \
                if(gparent == m->root)                                         \
                {                                                              \
                        m->root = parent;                                      \
                        parent->parent = LEAF;                                 \
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
		map_rotate_right_##K##_##V(m, parent, gparent);                \
        }                                                                      \
                                                                               \
        static void map_rotate_right_left_##K##_##V(                           \
            struct map_##K##_##V *m, struct node_##K##_##V *n,                 \
            struct node_##K##_##V *parent, struct node_##K##_##V *gparent)     \
        {                                                                      \
		map_rotate_right_##K##_##V(m, n, parent);                      \
		map_rotate_left_##K##_##V(m, parent, gparent);                 \
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
                                n->color = RED;                                \
                                parent->color = BLACK;                         \
                                struct node_##K##_##V *brother =               \
                                    parent->right;                             \
                                if(brother != LEAF)                            \
                                {                                              \
                                        brother->color = RED;                  \
                                }                                              \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                map_rotate_right_left_##K##_##V(m, n, parent,  \
                                                                gparent);      \
                                n->color = BLACK;                              \
                                n->right->color = RED;                         \
                                n->left->color = RED;                          \
                        }                                                      \
                }                                                              \
                else                                                           \
                {                                                              \
                        if(!map_is_left_child_##K##_##V(parent, gparent))      \
                        {                                                      \
                                map_rotate_left_##K##_##V(m, parent,        \
                                                          gparent);            \
                                n->color = RED;                                \
                                parent->color = BLACK;                         \
                                struct node_##K##_##V *brother =               \
                                    parent->right;                             \
                                if(brother != LEAF)                            \
                                {                                              \
                                        brother->color = RED;                  \
                                }                                              \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                map_rotate_left_right_##K##_##V(m, n, parent,  \
                                                                gparent);      \
                                n->color = BLACK;                              \
                                n->right->color = RED;                         \
                                n->left->color = RED;                          \
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
                if(aunt == LEAF || aunt->color == BLACK)                       \
                {                                                              \
                        map_rotate_##K##_##V(m, n, parent, gparent);           \
                }                                                              \
                else if(aunt != NULL)                                          \
                {                                                              \
                        aunt->color = BLACK;                                   \
                }                                                              \
                gparent->color = RED;                                          \
                parent->color = BLACK;                                         \
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
                if(n->color == RED && parent->color == RED)                    \
                {                                                              \
                        map_corect_tree_##K##_##V(m, n, parent);               \
                }                                                              \
                map_check_color_##K##_##V(m, parent);                          \
        }                                                                      \
                                                                               \
        static void map_insert_node_##K##_##V(struct map_##K##_##V *m,         \
                                              struct node_##K##_##V *new_node) \
        {                                                                      \
		struct node_##K##_##V* parent = m->root;                       \
                for(;;)                                                        \
                {                                                              \
                        if(m->comp(&parent->key, &new_node->key) > 0)          \
                        {                                                      \
                                if(parent->left == LEAF)                       \
                                {                                              \
                                        parent->left = new_node;               \
                                        break;                                 \
                                }                                              \
                                parent = parent->left;                         \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                if(parent->right == LEAF)                      \
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
        void map_at_##K##_##V(struct map_##K##_##V *m, const K key, V value)   \
        {                                                                      \
                /* need to check if a memeber with that key is already added   \
                 */                                                            \
                                                                               \
                struct node_##K##_##V *new_node =                              \
                    (struct node_##K##_##V *)malloc(                           \
                        sizeof(struct node_##K##_##V));                        \
                m->copy_key(&new_node->key, &key);                             \
                m->copy(&new_node->value, &value);                             \
                new_node->left = new_node->right = LEAF;                       \
                if(m->root == LEAF)                                            \
                {                                                              \
                        new_node->color = BLACK;                               \
                        new_node->parent = LEAF;                               \
                        m->root = new_node;                                    \
                }                                                              \
                else                                                           \
                {                                                              \
                        new_node->color = RED;                                 \
                        map_insert_node_##K##_##V(m, new_node);                \
                }                                                              \
                m->size++;                                                     \
        }\
\
\
