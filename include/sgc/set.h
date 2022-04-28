#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_common.h"
#include "detail/sgc_dictionary_common.h"
#include "detail/sgc_iterator.h"
#include "detail/sgc_log.h"
#include "detail/sgc_primitive_types.h"
#include "detail/sgc_rbtree_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define _SGC_INIT_PP_SET(KV, N)                                                \
    static int _p_##N##_node_compare(const struct _p_##N##_node* const n,      \
                                     const KV* const key);                     \
    static struct _p_##N##_node* _p_##N##_node_begin(struct _p_##N##_node* n); \
    static struct _p_##N##_node* _p_##N##_node_end(struct _p_##N##_node* n);   \
    static struct _p_##N##_node* _p_##N##_node_new(const KV* const v,          \
                                                   bool shared);               \
    static size_t _p_##N##_stack_size(size_t size);                            \
    static bool                                                                \
        _p_##N##_is_left_child(const struct _p_##N##_node* const n,            \
                               const struct _p_##N##_node* const parent);      \
    static struct _p_##N##_node*                                               \
        _p_##N##_sibling(const struct _p_##N##_node* const n,                  \
                         const struct _p_##N##_node* const parent);            \
    static void _p_##N##_rotate_left(N* s, struct _p_##N##_node* parent,       \
                                     struct _p_##N##_node* gparent);           \
    static void _p_##N##_rotate_right(N* s, struct _p_##N##_node* parent,      \
                                      struct _p_##N##_node* gparent);          \
    static void _p_##N##_rotate_left_right(N* s, struct _p_##N##_node* n,      \
                                           struct _p_##N##_node* parent,       \
                                           struct _p_##N##_node* gparent);     \
    static void _p_##N##_rotate_right_left(N* s, struct _p_##N##_node* n,      \
                                           struct _p_##N##_node* parent,       \
                                           struct _p_##N##_node* gparent);     \
    static void _p_##N##_rotate(N* s, struct _p_##N##_node* n,                 \
                                struct _p_##N##_node* parent,                  \
                                struct _p_##N##_node* gparent);                \
    static void _p_##N##_correct_tree(N* s, struct _p_##N##_node* n,           \
                                      struct _p_##N##_node* p,                 \
                                      struct _p_##N##_node* gp);               \
    static void _p_##N##_check_color(N* s, struct _p_##N##_node* n);           \
    static void _p_##N##_node_insert(N* s, KV* v);                             \
    static struct _p_##N##_node* _p_##N##_node_find(N* s, KV v);               \
    static void _p_##N##_erase_rebalanse(N* m, struct _p_##N##_node* n,        \
                                         struct _p_##N##_node* p);             \
    static void _p_##N##_node_erase(N* m, struct _p_##N##_node* n);            \
    static void                                                                \
        _p_##N##_node_copy_values(const N* const m, struct _p_##N##_node* dst, \
                                  const struct _p_##N##_node* const src);      \
    static struct _p_##N##_node*                                               \
        _p_##N##_node_duplicate(const N* const m,                              \
                                const struct _p_##N##_node* const n);          \
    static void _p_##N##_copy_base_data(N* __restrict__ dst,                   \
                                        const N* __restrict__ const src);      \
    static void _p_##N##_copy_nodes(N* __restrict__ dst,                       \
                                    const N* __restrict__ const src);          \
    static void _p_##N##_node_free(const N* const m, struct _p_##N##_node* n); \
    static void _p_##N##_node_replace_data(const N* const m,                   \
                                           struct _p_##N##_node* dst,          \
                                           struct _p_##N##_node* src);

#define SGC_INIT_HEADERS_SET(KV, N)                                            \
    struct _p_##N##_node {                                                     \
        struct _p_##N##_node* parent_;                                         \
        struct _p_##N##_node* left_;                                           \
        struct _p_##N##_node* right_;                                          \
        KV value_;                                                             \
        enum _sgc_map_color color_;                                            \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef KV N##_type;                                                       \
    typedef KV N##_value;                                                      \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        bool sharing_;                                                         \
        struct _p_##N##_node* root_;                                           \
    };                                                                         \
                                                                               \
    struct N##_it {                                                            \
        bool valid_;                                                           \
        struct _p_##N##_node* curr_;                                           \
        struct _p_##N##_node* next_;                                           \
    };                                                                         \
                                                                               \
    typedef struct N##_it N##_it;                                              \
    _SGC_INIT_BD_IT_PROTOTIPES(N)                                              \
                                                                               \
    void N##_set_sharing(N* s);                                                \
    void N##_set_owning(N* s);                                                 \
    struct N##_it N##_find(N* s, const KV v);                                  \
    size_t N##_size(const N* const s);                                         \
    void N##_init(N* s);                                                       \
    void N##_free(N* s);                                                       \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src);       \
    void N##_insert(N* s, KV v);                                               \
    bool N##_erase(N* m, const KV value);                                      \
    bool N##_erase_it(N* m, N##_it* i);                                        \
    bool N##_empty(const N* const m);

#define _SGC_INIT_UNIQUE_SET(KV, N)                                            \
    static struct _p_##N##_node* _p_##N##_node_new(const KV* const v,          \
                                                   bool shared) {              \
        struct _p_##N##_node* n =                                              \
            (struct _p_##N##_node*)sgc_malloc(sizeof(struct _p_##N##_node));   \
        if (!n) {                                                              \
            return NULL;                                                       \
        }                                                                      \
        _SGC_COPY(KV, n->value_, *v, shared);                                  \
        n->left_ = n->right_ = _SGC_MAP_LEAF;                                  \
        n->color_ = _SGC_MAP_COLOR_RED;                                        \
        return n;                                                              \
    }                                                                          \
                                                                               \
    static void _p_##N##_node_insert(N* s, KV* v) {                            \
        struct _p_##N##_node* parent = s->root_;                               \
        struct _p_##N##_node* new_node = NULL;                                 \
        while (true) {                                                         \
            int compare = (KV##_compare(&parent->value_, v));                  \
                                                                               \
            if (compare > 0) {                                                 \
                if (parent->left_ == _SGC_MAP_LEAF) {                          \
                    new_node = _p_##N##_node_new(v, s->sharing_);              \
                    if (!new_node) {                                           \
                        return;                                                \
                    }                                                          \
                    parent->left_ = new_node;                                  \
                    s->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->left_;                                        \
            } else if (compare < 0) {                                          \
                if (parent->right_ == _SGC_MAP_LEAF) {                         \
                    new_node = _p_##N##_node_new(v, s->sharing_);              \
                    if (!new_node) {                                           \
                        return;                                                \
                    }                                                          \
                    parent->right_ = new_node;                                 \
                    s->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->right_;                                       \
            } else if (!KV##_eq(&parent->value_, v)) {                         \
                _SGC_REPLACE(KV, parent->value_, *v, s->sharing_);             \
                return;                                                        \
            } else {                                                           \
                return;                                                        \
            }                                                                  \
        }                                                                      \
        new_node->parent_ = parent;                                            \
        _p_##N##_check_color(s, new_node);                                     \
    }                                                                          \
                                                                               \
    void N##_insert(N* s, KV v) {                                              \
        if (s->root_ == _SGC_MAP_LEAF) {                                       \
            struct _p_##N##_node* new_node =                                   \
                _p_##N##_node_new(&v, s->sharing_);                            \
            if (!new_node) {                                                   \
                return;                                                        \
            }                                                                  \
            new_node->color_ = _SGC_MAP_COLOR_BLACK;                           \
            new_node->parent_ = _SGC_MAP_LEAF;                                 \
            s->root_ = new_node;                                               \
            s->size_ = 1;                                                      \
        } else {                                                               \
            _p_##N##_node_insert(s, &v);                                       \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void _p_##N##_node_replace_data(const N* const m,                   \
                                           struct _p_##N##_node* dst,          \
                                           struct _p_##N##_node* src) {        \
        _SGC_REPLACE(KV, dst->value_, src->value_, m->sharing_);               \
    }                                                                          \
                                                                               \
    void N##_init(N* s) {                                                      \
        s->root_ = _SGC_MAP_LEAF;                                              \
        s->size_ = 0;                                                          \
        s->sharing_ = 0;                                                       \
    }                                                                          \
                                                                               \
    static void _p_##N##_copy_base_data(N* __restrict__ dst,                   \
                                        const N* __restrict__ const src) {     \
        dst->size_ = src->size_;                                               \
        dst->root_ = _SGC_MAP_LEAF;                                            \
        dst->sharing_ = src->sharing_;                                         \
    }

#define SGC_INIT_DEFINITIONS_SET(KV, N)                                        \
    _SGC_INIT_PP_SET(KV, N)                                                    \
    _SGC_INIT_UNIQUE_SET(KV, N)                                                \
    _SGC_INIT_COMMON_DICT_NONE_PAIR_BST(KV, N)                                 \
    _SGC_INIT_COMMON_RBTREE(KV, N)                                             \
    _SGC_INIT_IT_CBEGIN_CEND(N)                                                \
    _SGC_INIT_COMMON(N)

#define SGC_INIT_SET(KV, N)                                                    \
    SGC_INIT_HEADERS_SET(KV, N)                                                \
    SGC_INIT_DEFINITIONS_SET(KV, N)
