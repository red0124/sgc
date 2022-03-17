#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_dictionary_ocmmon.h"
#include "detail/sgc_log.h"
#include "detail/sgc_rbtree_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define _SGC_INIT_PRIKVATE_SET_FUNCTION_DECLARATIONS(KV, N)                    \
    static int N##_node_compare(const struct N##_node* const n,                \
                                const KV* const key);                          \
    static struct N##_node* N##_node_begin(struct N##_node* n);                \
    static struct N##_node* N##_node_end(struct N##_node* n);                  \
    static struct N##_node* N##_node_new(const KV* const v, size_t is_shared); \
    static size_t N##_stack_size(size_t size);                                 \
    static bool N##_is_left_child(const struct N##_node* const n,              \
                                  const struct N##_node* const parent);        \
    static struct N##_node* N##_sibling(const struct N##_node* const n,        \
                                        const struct N##_node* const parent);  \
    static void N##_rotate_left(struct N* s, struct N##_node* parent,          \
                                struct N##_node* gparent);                     \
    static void N##_rotate_right(struct N* s, struct N##_node* parent,         \
                                 struct N##_node* gparent);                    \
    static void N##_rotate_left_right(struct N* s, struct N##_node* n,         \
                                      struct N##_node* parent,                 \
                                      struct N##_node* gparent);               \
    static void N##_rotate_right_left(struct N* s, struct N##_node* n,         \
                                      struct N##_node* parent,                 \
                                      struct N##_node* gparent);               \
    static void N##_rotate(struct N* s, struct N##_node* n,                    \
                           struct N##_node* parent, struct N##_node* gparent); \
    static void N##_correct_tree(struct N* s, struct N##_node* n,              \
                                 struct N##_node* p, struct N##_node* gp);     \
    static void N##_check_color(struct N* s, struct N##_node* n);              \
    static void N##_node_insert(struct N* s, KV* v);                           \
    static void N##_insert_multiple_node(struct N* s, KV* v);                  \
    struct N##_iterator N##_find(struct N* s, KV v);                           \
    static struct N##_node* N##_node_find(struct N* s, KV v);                  \
    static void N##_erase_rebalanse(struct N* m, struct N##_node* n,           \
                                    struct N##_node* p);                       \
    static struct N##_node* N##_node_erase(struct N* m, struct N##_node* n);   \
    static void N##_node_copy_values(const struct N* const m,                  \
                                     struct N##_node* dst,                     \
                                     const struct N##_node* const src);        \
    static struct N##_node*                                                    \
        N##_node_duplicate(const struct N* const m,                            \
                           const struct N##_node* const n);                    \
    static void N##_copy_base_data(struct N* __restrict__ dst,                 \
                                   const struct N* __restrict__ const src);    \
    static void N##_copy_nodes(struct N* __restrict__ dst,                     \
                               const struct N* __restrict__ const src);        \
    static void N##_node_free(const struct N* const m, struct N##_node* n);

#define SGC_INIT_HEADERS_SET(KV, N)                                            \
    struct N##_node {                                                          \
        struct N##_node* parent_;                                              \
        struct N##_node* left_;                                                \
        struct N##_node* right_;                                               \
        KV _value;                                                             \
        enum sgc_map_color color_;                                             \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef KV N##_type;                                                       \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t shared_;                                                        \
        struct N##_node* root_;                                                \
    };                                                                         \
                                                                               \
    void N##_set_share(N* s, int is_shared);                                   \
                                                                               \
    struct N##_iterator {                                                      \
        struct N##_node* curr_;                                                \
        struct N##_node* next_;                                                \
        int is_valid_;                                                         \
    };                                                                         \
                                                                               \
    typedef struct N##_iterator N##_iterator;                                  \
                                                                               \
    KV* N##_iterator_data(struct N##_iterator i);                              \
    const KV* N##_iterator_cdata(struct N##_iterator i);                       \
    void N##_iterator_next(struct N##_iterator* i);                            \
    void N##_iterator_begin(struct N* s, struct N##_iterator* i);              \
    void N##_iterator_cbegin(const struct N* const s, struct N##_iterator* i); \
    void N##_iterator_prev(struct N##_iterator* i);                            \
    void N##_iterator_end(struct N* s, struct N##_iterator* i);                \
    void N##_iterator_cend(const struct N* const s, struct N##_iterator* i);   \
    struct N##_iterator N##_begin(struct N* m);                                \
    struct N##_iterator N##_cbegin(const struct N* const m);                   \
    struct N##_iterator N##_end(struct N* m);                                  \
    struct N##_iterator N##_cend(const struct N* const m);                     \
    bool N##_iterator_equal(const struct N##_iterator first,                   \
                            const struct N##_iterator second);                 \
    bool N##_iterator_valid(const struct N##_iterator i);                      \
    size_t N##_size(const struct N* const s);                                  \
    void N##_init(struct N* s);                                                \
    void N##_free(struct N* s);                                                \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_insert(struct N* s, KV v);                                        \
    void N##_insert_multiple(struct N* s, KV v);                               \
    bool N##_erase(struct N* m, const KV value);                               \
    bool N##_iterator_erase(struct N* m, struct N##_iterator* i);              \
    bool N##_empty(const struct N* const m);

#define _SGC_INIT_UNIQUE_SET_FUNCTIONS(KV, N)                                  \
    static struct N##_node* N##_node_new(const KV* const v,                    \
                                         size_t is_shared) {                   \
        struct N##_node* n =                                                   \
            (struct N##_node*)sgc_malloc(sizeof(struct N##_node));             \
        SGC_COPY(KV##_copy, n->_value, *v, is_shared);                         \
        n->left_ = n->right_ = SGC_MAP_LEAF;                                   \
        n->color_ = SGC_MAP_RED;                                               \
        return n;                                                              \
    }                                                                          \
                                                                               \
    static void N##_node_insert(struct N* s, KV* v) {                          \
        struct N##_node* parent = s->root_;                                    \
        struct N##_node* new_node = NULL;                                      \
        while (true) {                                                         \
            int compare = (KV##_compare(&parent->_value, v));                  \
                                                                               \
            if (compare > 0) {                                                 \
                if (parent->left_ == SGC_MAP_LEAF) {                           \
                    new_node = N##_node_new(v, s->shared_);                    \
                    parent->left_ = new_node;                                  \
                    s->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->left_;                                        \
            } else if (compare < 0) {                                          \
                if (parent->right_ == SGC_MAP_LEAF) {                          \
                    new_node = N##_node_new(v, s->shared_);                    \
                    parent->right_ = new_node;                                 \
                    s->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->right_;                                       \
            } else if (!KV##_equal(&parent->_value, v)) {                      \
                SGC_REPLACE(KV##_copy, KV##_free, parent->_value, *v,          \
                            s->shared_);                                       \
                return;                                                        \
            } else {                                                           \
                return;                                                        \
            }                                                                  \
        }                                                                      \
        new_node->parent_ = parent;                                            \
        N##_check_color(s, new_node);                                          \
    }                                                                          \
                                                                               \
    void N##_insert(struct N* s, KV v) {                                       \
        if (s->root_ == SGC_MAP_LEAF) {                                        \
            struct N##_node* new_node = N##_node_new(&v, s->shared_);          \
            new_node->color_ = SGC_MAP_BLACK;                                  \
            new_node->parent_ = SGC_MAP_LEAF;                                  \
            s->root_ = new_node;                                               \
            s->size_ = 1;                                                      \
        } else {                                                               \
            N##_node_insert(s, &v);                                            \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void N##_insert_multiple_node(struct N* s, KV* v) {                 \
        struct N##_node* parent = s->root_;                                    \
        struct N##_node* new_node = NULL;                                      \
        while (true) {                                                         \
            int compare = (KV##_compare(&parent->_value, v));                  \
                                                                               \
            if (compare > 0) {                                                 \
                if (parent->left_ == SGC_MAP_LEAF) {                           \
                    new_node = N##_node_new(v, s->shared_);                    \
                    parent->left_ = new_node;                                  \
                    s->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->left_;                                        \
            } else {                                                           \
                if (parent->right_ == SGC_MAP_LEAF) {                          \
                    new_node = N##_node_new(v, s->shared_);                    \
                    parent->right_ = new_node;                                 \
                    s->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->right_;                                       \
            }                                                                  \
        }                                                                      \
        new_node->parent_ = parent;                                            \
        N##_check_color(s, new_node);                                          \
    }                                                                          \
                                                                               \
    void N##_insert_multiple(struct N* s, KV v) {                              \
        if (s->root_ == SGC_MAP_LEAF) {                                        \
            struct N##_node* new_node = N##_node_new(&v, s->shared_);          \
            new_node->color_ = SGC_MAP_BLACK;                                  \
            new_node->parent_ = SGC_MAP_LEAF;                                  \
            s->root_ = new_node;                                               \
            s->size_ = 1;                                                      \
        } else {                                                               \
            N##_insert_multiple_node(s, &v);                                   \
        }                                                                      \
    }                                                                          \
                                                                               \
    static struct N##_node* N##_node_erase(struct N* m, struct N##_node* n) {  \
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
            KV##_copy(&n->_value, &succ->_value);                              \
            if (!m->shared_) {                                                 \
                KV##_free(&succ->_value);                                      \
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
            N##_erase_rebalanse(m, succ_c, succ_p);                            \
        }                                                                      \
        if (m->root_) {                                                        \
            m->root_->color_ = SGC_MAP_BLACK;                                  \
        }                                                                      \
        --m->size_;                                                            \
        return succ;                                                           \
    }                                                                          \
                                                                               \
    void N##_init(struct N* s) {                                               \
        s->size_ = 0;                                                          \
        s->root_ = SGC_MAP_LEAF;                                               \
        s->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    static void N##_copy_base_data(struct N* __restrict__ dst,                 \
                                   const struct N* __restrict__ const src) {   \
        dst->size_ = src->size_;                                               \
        dst->root_ = SGC_MAP_LEAF;                                             \
        dst->shared_ = src->shared_;                                           \
    }

#define SGC_INIT_SET(KV, N)                                                    \
    SGC_INIT_HEADERS_SET(KV, N)                                                \
    _SGC_INIT_PRIKVATE_SET_FUNCTION_DECLARATIONS(KV, N)                        \
    _SGC_INIT_COMMON_DICTIONARY_NONE_PAIR_FUNCTIONS(KV, N)                     \
    _SGC_INIT_UNIQUE_SET_FUNCTIONS(KV, N)                                      \
    _SGC_INIT_RBTREE_TYPE_FUNCTIONS(KV, N)                                     \
    _SGC_INIT_COMMON_FUNCTIONS(N)
