#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_log.h"
#include "detail/sgc_rbtree_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define _SGC_INIT_PRIVATE_SET_FUNCTION_DECLARATIONS(V, N)                      \
    static int _m_##N##_node_compare(const struct _m_##N##_node* const n,      \
                                     const V* const key);                      \
    static struct _m_##N##_node* _m_##N##_node_begin(struct _m_##N##_node* n); \
    static struct _m_##N##_node* _m_##N##_node_end(struct _m_##N##_node* n);   \
    static struct _m_##N##_node* _m_##N##_node_new(const V* const v,           \
                                                   size_t is_shared);          \
    static size_t _m_##N##_stack_size(size_t size);                            \
    static bool                                                                \
        _m_##N##_is_left_child(const struct _m_##N##_node* const n,            \
                               const struct _m_##N##_node* const parent);      \
    static struct _m_##N##_node*                                               \
        N##_sibling(const struct _m_##N##_node* const n,                       \
                    const struct _m_##N##_node* const parent);                 \
    static void _m_##N##_rotate_left(struct N* s,                              \
                                     struct _m_##N##_node* parent,             \
                                     struct _m_##N##_node* gparent);           \
    static void _m_##N##_rotate_right(struct N* s,                             \
                                      struct _m_##N##_node* parent,            \
                                      struct _m_##N##_node* gparent);          \
    static void _m_##N##_rotate_left_right(struct N* s,                        \
                                           struct _m_##N##_node* n,            \
                                           struct _m_##N##_node* parent,       \
                                           struct _m_##N##_node* gparent);     \
    static void _m_##N##_rotate_right_left(struct N* s,                        \
                                           struct _m_##N##_node* n,            \
                                           struct _m_##N##_node* parent,       \
                                           struct _m_##N##_node* gparent);     \
    static void _m_##N##_rotate(struct N* s, struct _m_##N##_node* n,          \
                                struct _m_##N##_node* parent,                  \
                                struct _m_##N##_node* gparent);                \
    static void _m_##N##_correct_tree(struct N* s, struct _m_##N##_node* n,    \
                                      struct _m_##N##_node* p,                 \
                                      struct _m_##N##_node* gp);               \
    static void _m_##N##_check_color(struct N* s, struct _m_##N##_node* n);    \
    static void _m_##N##_node_insert(struct N* s, V* v);                       \
    static void N##_insert_multiple_node(struct N* s, V* v);                   \
    struct N##_iterator N##_find(struct N* s, V v);                            \
    static struct _m_##N##_node* _m_##N##_node_find(struct N* s, V v);         \
    static void _m_##N##_erase_rebalanse(struct N* m, struct _m_##N##_node* n, \
                                         struct _m_##N##_node* p);             \
    static struct _m_##N##_node* _m_##N##_node_erase(struct N* m,              \
                                                     struct _m_##N##_node* n); \
    static void                                                                \
        _m_##N##_node_copy_values(const struct N* const m,                     \
                                  struct _m_##N##_node* dst,                   \
                                  const struct _m_##N##_node* const src);      \
    static struct _m_##N##_node*                                               \
        _m_##N##_node_duplicate(const struct N* const m,                       \
                                const struct _m_##N##_node* const n);          \
    static void                                                                \
        _m_##N##_copy_base_data(struct N* __restrict__ dst,                    \
                                const struct N* __restrict__ const src);       \
    static void _m_##N##_copy_nodes(struct N* __restrict__ dst,                \
                                    const struct N* __restrict__ const src);   \
    static void _m_##N##_node_free(const struct N* const m,                    \
                                   struct _m_##N##_node* n);

#define SGC_INIT_HEADERS_SET(V, N)                                             \
    struct _m_##N##_node {                                                     \
        struct _m_##N##_node* parent_;                                         \
        struct _m_##N##_node* left_;                                           \
        struct _m_##N##_node* right_;                                          \
        V _value;                                                              \
        enum sgc_map_color color_;                                             \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef V N##_type;                                                        \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t shared_;                                                        \
        struct _m_##N##_node* root_;                                           \
    };                                                                         \
                                                                               \
    void N##_set_share(N* s, int is_shared);                                   \
                                                                               \
    struct N##_iterator {                                                      \
        struct _m_##N##_node* curr_;                                           \
        struct _m_##N##_node* next_;                                           \
        int is_valid_;                                                         \
    };                                                                         \
                                                                               \
    typedef struct N##_iterator N##_iterator;                                  \
                                                                               \
    V* N##_iterator_data(struct N##_iterator i);                               \
    const V* N##_iterator_cdata(struct N##_iterator i);                        \
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
    void N##_insert(struct N* s, V v);                                         \
    void N##_insert_multiple(struct N* s, V v);                                \
    bool N##_erase(struct N* m, const V value);                                \
    bool N##_iterator_erase(struct N* m, struct N##_iterator* i);              \
    bool N##_empty(const struct N* const m);

#define _SGC_INIT_UNIQUE_SET_FUNCTIONS(V, N)                                   \
    static struct _m_##N##_node* _m_##N##_node_new(const V* const v,           \
                                                   size_t is_shared) {         \
        struct _m_##N##_node* n =                                              \
            (struct _m_##N##_node*)sgc_malloc(sizeof(struct _m_##N##_node));   \
        SGC_COPY(V##_copy, n->_value, *v, is_shared);                          \
        n->left_ = n->right_ = SGC_MAP_LEAF;                                   \
        n->color_ = SGC_MAP_RED;                                               \
        return n;                                                              \
    }                                                                          \
                                                                               \
    V* N##_iterator_data(struct N##_iterator i) {                              \
        return &i.curr_->_value;                                               \
    }                                                                          \
                                                                               \
    const V* N##_iterator_cdata(struct N##_iterator i) {                       \
        return &i.curr_->_value;                                               \
    }                                                                          \
                                                                               \
    static void _m_##N##_node_insert(struct N* s, V* v) {                      \
        struct _m_##N##_node* parent = s->root_;                               \
        struct _m_##N##_node* new_node = NULL;                                 \
        while (true) {                                                         \
            int compare = (V##_compare(&parent->_value, v));                   \
                                                                               \
            if (compare > 0) {                                                 \
                if (parent->left_ == SGC_MAP_LEAF) {                           \
                    new_node = _m_##N##_node_new(v, s->shared_);               \
                    parent->left_ = new_node;                                  \
                    s->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->left_;                                        \
            } else if (compare < 0) {                                          \
                if (parent->right_ == SGC_MAP_LEAF) {                          \
                    new_node = _m_##N##_node_new(v, s->shared_);               \
                    parent->right_ = new_node;                                 \
                    s->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->right_;                                       \
            } else if (!V##_equal(&parent->_value, v)) {                       \
                SGC_REPLACE(V##_copy, V##_free, parent->_value, *v,            \
                            s->shared_);                                       \
                return;                                                        \
            } else {                                                           \
                return;                                                        \
            }                                                                  \
        }                                                                      \
        new_node->parent_ = parent;                                            \
        _m_##N##_check_color(s, new_node);                                     \
    }                                                                          \
                                                                               \
    void N##_insert(struct N* s, V v) {                                        \
        if (s->root_ == SGC_MAP_LEAF) {                                        \
            struct _m_##N##_node* new_node =                                   \
                _m_##N##_node_new(&v, s->shared_);                             \
            new_node->color_ = SGC_MAP_BLACK;                                  \
            new_node->parent_ = SGC_MAP_LEAF;                                  \
            s->root_ = new_node;                                               \
            s->size_ = 1;                                                      \
        } else {                                                               \
            _m_##N##_node_insert(s, &v);                                       \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void N##_insert_multiple_node(struct N* s, V* v) {                  \
        struct _m_##N##_node* parent = s->root_;                               \
        struct _m_##N##_node* new_node = NULL;                                 \
        while (true) {                                                         \
            int compare = (V##_compare(&parent->_value, v));                   \
                                                                               \
            if (compare > 0) {                                                 \
                if (parent->left_ == SGC_MAP_LEAF) {                           \
                    new_node = _m_##N##_node_new(v, s->shared_);               \
                    parent->left_ = new_node;                                  \
                    s->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->left_;                                        \
            } else {                                                           \
                if (parent->right_ == SGC_MAP_LEAF) {                          \
                    new_node = _m_##N##_node_new(v, s->shared_);               \
                    parent->right_ = new_node;                                 \
                    s->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->right_;                                       \
            }                                                                  \
        }                                                                      \
        new_node->parent_ = parent;                                            \
        _m_##N##_check_color(s, new_node);                                     \
    }                                                                          \
                                                                               \
    void N##_insert_multiple(struct N* s, V v) {                               \
        if (s->root_ == SGC_MAP_LEAF) {                                        \
            struct _m_##N##_node* new_node =                                   \
                _m_##N##_node_new(&v, s->shared_);                             \
            new_node->color_ = SGC_MAP_BLACK;                                  \
            new_node->parent_ = SGC_MAP_LEAF;                                  \
            s->root_ = new_node;                                               \
            s->size_ = 1;                                                      \
        } else {                                                               \
            N##_insert_multiple_node(s, &v);                                   \
        }                                                                      \
    }                                                                          \
                                                                               \
    static struct _m_##N##_node*                                               \
        _m_##N##_node_erase(struct N* m, struct _m_##N##_node* n) {            \
        struct _m_##N##_node* succ;                                            \
        struct _m_##N##_node* succ_p;                                          \
        struct _m_##N##_node* succ_c = SGC_MAP_LEAF;                           \
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
            V##_copy(&n->_value, &succ->_value);                               \
            if (!m->shared_) {                                                 \
                V##_free(&succ->_value);                                       \
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
            _m_##N##_erase_rebalanse(m, succ_c, succ_p);                       \
        }                                                                      \
        if (m->root_) {                                                        \
            m->root_->color_ = SGC_MAP_BLACK;                                  \
        }                                                                      \
        --m->size_;                                                            \
        return succ;                                                           \
    }                                                                          \
                                                                               \
    static int _m_##N##_node_compare(const struct _m_##N##_node* const n,      \
                                     const V* const key) {                     \
        return V##_compare(&n->_value, key);                                   \
    }                                                                          \
                                                                               \
    void N##_init(struct N* s) {                                               \
        s->size_ = 0;                                                          \
        s->root_ = SGC_MAP_LEAF;                                               \
        s->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    static void                                                                \
        _m_##N##_node_copy_values(const struct N* const m,                     \
                                  struct _m_##N##_node* dst,                   \
                                  const struct _m_##N##_node* const src) {     \
        SGC_COPY(V##_copy, dst->_value, src->_value, m->shared_);              \
        dst->color_ = src->color_;                                             \
    }                                                                          \
                                                                               \
    static void                                                                \
        _m_##N##_copy_base_data(struct N* __restrict__ dst,                    \
                                const struct N* __restrict__ const src) {      \
        dst->size_ = src->size_;                                               \
        dst->root_ = SGC_MAP_LEAF;                                             \
        dst->shared_ = src->shared_;                                           \
    }                                                                          \
                                                                               \
    static void _m_##N##_node_free(const struct N* const m,                    \
                                   struct _m_##N##_node* n) {                  \
        SGC_FREE(V##_free, n->_value, m->shared_);                             \
    }

#define SGC_INIT_SET(V, N)                                                     \
    SGC_INIT_HEADERS_SET(V, N)                                                 \
    _SGC_INIT_PRIVATE_SET_FUNCTION_DECLARATIONS(V, N)                          \
    _SGC_INIT_UNIQUE_SET_FUNCTIONS(V, N)                                       \
    _SGC_INIT_RBTREE_TYPE_FUNCTIONS(V, N)                                      \
    _SGC_INIT_COMMON_FUNCTIONS(N)
