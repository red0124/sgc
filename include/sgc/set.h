#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_dictionary_ocmmon.h"
#include "detail/sgc_iterator.h"
#include "detail/sgc_log.h"
#include "detail/sgc_rbtree_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define _SGC_INIT_PP_SET(KV, N)                                                \
    static int _p_##N##_node_compare(const struct N##_node* const n,           \
                                     const KV* const key);                     \
    static struct N##_node* _p_##N##_node_begin(struct N##_node* n);           \
    static struct N##_node* _p_##N##_node_end(struct N##_node* n);             \
    static struct N##_node* _p_##N##_node_new(const KV* const v, bool shared); \
    static size_t _p_##N##_stack_size(size_t size);                            \
    static bool _p_##N##_is_left_child(const struct N##_node* const n,         \
                                       const struct N##_node* const parent);   \
    static struct N##_node*                                                    \
        _p_##N##_sibling(const struct N##_node* const n,                       \
                         const struct N##_node* const parent);                 \
    static void _p_##N##_rotate_left(struct N* s, struct N##_node* parent,     \
                                     struct N##_node* gparent);                \
    static void _p_##N##_rotate_right(struct N* s, struct N##_node* parent,    \
                                      struct N##_node* gparent);               \
    static void _p_##N##_rotate_left_right(struct N* s, struct N##_node* n,    \
                                           struct N##_node* parent,            \
                                           struct N##_node* gparent);          \
    static void _p_##N##_rotate_right_left(struct N* s, struct N##_node* n,    \
                                           struct N##_node* parent,            \
                                           struct N##_node* gparent);          \
    static void _p_##N##_rotate(struct N* s, struct N##_node* n,               \
                                struct N##_node* parent,                       \
                                struct N##_node* gparent);                     \
    static void _p_##N##_correct_tree(struct N* s, struct N##_node* n,         \
                                      struct N##_node* p,                      \
                                      struct N##_node* gp);                    \
    static void _p_##N##_check_color(struct N* s, struct N##_node* n);         \
    static void _p_##N##_node_insert(struct N* s, KV* v);                      \
    static void _p_##N##_node_insert_multiple(struct N* s, KV* v);             \
    static struct N##_node* _p_##N##_node_find(struct N* s, KV v);             \
    static void _p_##N##_erase_rebalanse(struct N* m, struct N##_node* n,      \
                                         struct N##_node* p);                  \
    static struct N##_node* _p_##N##_node_erase(struct N* m,                   \
                                                struct N##_node* n);           \
    static void _p_##N##_node_copy_values(const struct N* const m,             \
                                          struct N##_node* dst,                \
                                          const struct N##_node* const src);   \
    static struct N##_node*                                                    \
        _p_##N##_node_duplicate(const struct N* const m,                       \
                                const struct N##_node* const n);               \
    static void                                                                \
        _p_##N##_copy_base_data(struct N* __restrict__ dst,                    \
                                const struct N* __restrict__ const src);       \
    static void _p_##N##_copy_nodes(struct N* __restrict__ dst,                \
                                    const struct N* __restrict__ const src);   \
    static void _p_##N##_node_free(const struct N* const m, struct N##_node* n);

#define SGC_INIT_HEADERS_SET(KV, N)                                            \
    struct N##_node {                                                          \
        struct N##_node* parent_;                                              \
        struct N##_node* left_;                                                \
        struct N##_node* right_;                                               \
        KV value_;                                                             \
        enum sgc_map_color color_;                                             \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef KV N##_type;                                                       \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        bool shared_;                                                          \
        struct N##_node* root_;                                                \
    };                                                                         \
                                                                               \
    void N##_set_share(N* s, bool shared);                                     \
                                                                               \
    struct N##_it {                                                            \
        struct N##_node* curr_;                                                \
        struct N##_node* next_;                                                \
        bool valid_;                                                           \
    };                                                                         \
                                                                               \
    typedef struct N##_it N##_it;                                              \
    _SGC_INIT_BD_IT_PROTOTIPES(N)                                              \
                                                                               \
    struct N##_it N##_find(struct N* s, const KV v);                           \
    size_t N##_size(const struct N* const s);                                  \
    void N##_init(struct N* s);                                                \
    void N##_free(struct N* s);                                                \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_insert(struct N* s, KV v);                                        \
    void N##_insert_multiple(struct N* s, KV v);                               \
    bool N##_erase(struct N* m, const KV value);                               \
    bool N##_it_erase(struct N* m, struct N##_it* i);                          \
    bool N##_empty(const struct N* const m);

#define _SGC_INIT_UNIQUE_SET(KV, N)                                            \
    static struct N##_node* _p_##N##_node_new(const KV* const v,               \
                                              bool shared) {                   \
        struct N##_node* n =                                                   \
            (struct N##_node*)sgc_malloc(sizeof(struct N##_node));             \
        SGC_COPY(KV##_copy, n->value_, *v, shared);                            \
        n->left_ = n->right_ = SGC_MAP_LEAF;                                   \
        n->color_ = SGC_MAP_RED;                                               \
        return n;                                                              \
    }                                                                          \
                                                                               \
    static void _p_##N##_node_insert(struct N* s, KV* v) {                     \
        struct N##_node* parent = s->root_;                                    \
        struct N##_node* new_node = NULL;                                      \
        while (true) {                                                         \
            int compare = (KV##_compare(&parent->value_, v));                  \
                                                                               \
            if (compare > 0) {                                                 \
                if (parent->left_ == SGC_MAP_LEAF) {                           \
                    new_node = _p_##N##_node_new(v, s->shared_);               \
                    parent->left_ = new_node;                                  \
                    s->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->left_;                                        \
            } else if (compare < 0) {                                          \
                if (parent->right_ == SGC_MAP_LEAF) {                          \
                    new_node = _p_##N##_node_new(v, s->shared_);               \
                    parent->right_ = new_node;                                 \
                    s->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->right_;                                       \
            } else if (!KV##_equal(&parent->value_, v)) {                      \
                SGC_REPLACE(KV##_copy, KV##_free, parent->value_, *v,          \
                            s->shared_);                                       \
                return;                                                        \
            } else {                                                           \
                return;                                                        \
            }                                                                  \
        }                                                                      \
        new_node->parent_ = parent;                                            \
        _p_##N##_check_color(s, new_node);                                     \
    }                                                                          \
                                                                               \
    void N##_insert(struct N* s, KV v) {                                       \
        if (s->root_ == SGC_MAP_LEAF) {                                        \
            struct N##_node* new_node = _p_##N##_node_new(&v, s->shared_);     \
            new_node->color_ = SGC_MAP_BLACK;                                  \
            new_node->parent_ = SGC_MAP_LEAF;                                  \
            s->root_ = new_node;                                               \
            s->size_ = 1;                                                      \
        } else {                                                               \
            _p_##N##_node_insert(s, &v);                                       \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void _p_##N##_node_insert_multiple(struct N* s, KV* v) {            \
        struct N##_node* parent = s->root_;                                    \
        struct N##_node* new_node = NULL;                                      \
        while (true) {                                                         \
            int compare = (KV##_compare(&parent->value_, v));                  \
                                                                               \
            if (compare > 0) {                                                 \
                if (parent->left_ == SGC_MAP_LEAF) {                           \
                    new_node = _p_##N##_node_new(v, s->shared_);               \
                    parent->left_ = new_node;                                  \
                    s->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->left_;                                        \
            } else {                                                           \
                if (parent->right_ == SGC_MAP_LEAF) {                          \
                    new_node = _p_##N##_node_new(v, s->shared_);               \
                    parent->right_ = new_node;                                 \
                    s->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->right_;                                       \
            }                                                                  \
        }                                                                      \
        new_node->parent_ = parent;                                            \
        _p_##N##_check_color(s, new_node);                                     \
    }                                                                          \
                                                                               \
    void N##_insert_multiple(struct N* s, KV v) {                              \
        if (s->root_ == SGC_MAP_LEAF) {                                        \
            struct N##_node* new_node = _p_##N##_node_new(&v, s->shared_);     \
            new_node->color_ = SGC_MAP_BLACK;                                  \
            new_node->parent_ = SGC_MAP_LEAF;                                  \
            s->root_ = new_node;                                               \
            s->size_ = 1;                                                      \
        } else {                                                               \
            _p_##N##_node_insert_multiple(s, &v);                              \
        }                                                                      \
    }                                                                          \
                                                                               \
    static struct N##_node* _p_##N##_node_erase(struct N* m,                   \
                                                struct N##_node* n) {          \
        struct N##_node* succ;                                                 \
        struct N##_node* succ_p;                                               \
        struct N##_node* succ_c = SGC_MAP_LEAF;                                \
        if (!n->left_ || !n->right_) {                                         \
            succ = n;                                                          \
        } else {                                                               \
            succ = n->right_;                                                  \
            if (succ) {                                                        \
                while (succ->left_) {                                          \
                    succ = succ->left_;                                        \
                }                                                              \
            } else {                                                           \
                succ = n->left_;                                               \
            }                                                                  \
        }                                                                      \
        if (succ != n) {                                                       \
            KV##_copy(&n->value_, &succ->value_);                              \
            if (!m->shared_) {                                                 \
                KV##_free(&succ->value_);                                      \
            }                                                                  \
            /* relinking nodes would be better */                              \
        }                                                                      \
                                                                               \
        succ_p = succ->parent_;                                                \
        if (succ->left_) {                                                     \
            succ_c = succ->left_;                                              \
            succ_c->parent_ = succ_p;                                          \
        } else if (succ->right_) {                                             \
            succ_c = succ->right_;                                             \
            succ_c->parent_ = succ_p;                                          \
        }                                                                      \
        if (succ_p) {                                                          \
            if (succ_p->left_ == succ) {                                       \
                succ_p->left_ = succ_c;                                        \
            } else {                                                           \
                succ_p->right_ = succ_c;                                       \
            }                                                                  \
        } else {                                                               \
            m->root_ = (m->root_->left_) ? m->root_->left_ : m->root_->right_; \
        }                                                                      \
                                                                               \
        if ((succ_c && succ_c->color_ == SGC_MAP_RED) ||                       \
            succ->color_ == SGC_MAP_RED) {                                     \
            if (succ_c) {                                                      \
                succ_c->color_ = SGC_MAP_BLACK;                                \
            }                                                                  \
        } else {                                                               \
            _p_##N##_erase_rebalanse(m, succ_c, succ_p);                       \
        }                                                                      \
        if (m->root_) {                                                        \
            m->root_->color_ = SGC_MAP_BLACK;                                  \
        }                                                                      \
        --m->size_;                                                            \
        return succ;                                                           \
    }                                                                          \
                                                                               \
    void N##_init(struct N* s) {                                               \
        s->root_ = SGC_MAP_LEAF;                                               \
        s->size_ = 0;                                                          \
        s->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    static void                                                                \
        _p_##N##_copy_base_data(struct N* __restrict__ dst,                    \
                                const struct N* __restrict__ const src) {      \
        dst->size_ = src->size_;                                               \
        dst->root_ = SGC_MAP_LEAF;                                             \
        dst->shared_ = src->shared_;                                           \
    }

#define SGC_INIT_SET(KV, N)                                                    \
    SGC_INIT_HEADERS_SET(KV, N)                                                \
    _SGC_INIT_PP_SET(KV, N)                                                    \
    _SGC_INIT_UNIQUE_SET(KV, N)                                                \
    _SGC_INIT_COMMON_DICT_NONE_PAIR(KV, N)                                     \
    _SGC_INIT_COMMON_RBTREE(KV, N)                                             \
    _SGC_INIT_COMMON(N)
