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

#define _SGC_INIT_PP_MAP(K, V, N)                                              \
    static int _p_##N##_node_compare(const struct _p_##N##_node* const n,      \
                                     const K* const key);                      \
    static struct _p_##N##_node* _p_##N##_node_begin(struct _p_##N##_node* n); \
    static struct _p_##N##_node* _p_##N##_node_end(struct _p_##N##_node* n);   \
    static struct _p_##N##_node* _p_##N##_node_new(const K* const k,           \
                                                   const V* const v,           \
                                                   bool sharing_key,           \
                                                   bool shared);               \
    static size_t _p_##N##_stack_size(size_t size);                            \
    static bool                                                                \
        _p_##N##_is_left_child(const struct _p_##N##_node* const n,            \
                               const struct _p_##N##_node* const parent);      \
    static struct _p_##N##_node*                                               \
        _p_##N##_sibling(const struct _p_##N##_node* const n,                  \
                         const struct _p_##N##_node* const parent);            \
    static void _p_##N##_rotate_left(N* m, struct _p_##N##_node* parent,       \
                                     struct _p_##N##_node* gparent);           \
    static void _p_##N##_rotate_right(N* m, struct _p_##N##_node* parent,      \
                                      struct _p_##N##_node* gparent);          \
    static void _p_##N##_rotate_left_right(N* m, struct _p_##N##_node* n,      \
                                           struct _p_##N##_node* parent,       \
                                           struct _p_##N##_node* gparent);     \
    static void _p_##N##_rotate_right_left(N* m, struct _p_##N##_node* n,      \
                                           struct _p_##N##_node* parent,       \
                                           struct _p_##N##_node* gparent);     \
    static void _p_##N##_rotate(N* m, struct _p_##N##_node* n,                 \
                                struct _p_##N##_node* parent,                  \
                                struct _p_##N##_node* gparent);                \
    static void _p_##N##_correct_tree(N* m, struct _p_##N##_node* n,           \
                                      struct _p_##N##_node* p,                 \
                                      struct _p_##N##_node* gp);               \
    static void _p_##N##_check_color(N* m, struct _p_##N##_node* n);           \
    static void _p_##N##_node_insert(N* m, K* k, V* v);                        \
    static V* _p_##N##_node_insert_or_get(N* m, K* k);                         \
    static struct _p_##N##_node* _p_##N##_node_find(N* m, K k);                \
    static void _p_##N##_erase_rebalanse(N* m, struct _p_##N##_node* n,        \
                                         struct _p_##N##_node* p);             \
    static struct _p_##N##_node* _p_##N##_node_erase(N* m,                     \
                                                     struct _p_##N##_node* n); \
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
    static void _p_##N##_node_free(const N* const m, struct _p_##N##_node* n);

#define SGC_INIT_HEADERS_MAP(K, V, N)                                          \
    struct N##_pair {                                                          \
        K key;                                                                 \
        V value;                                                               \
    };                                                                         \
                                                                               \
    struct _p_##N##_node {                                                     \
        struct _p_##N##_node* parent_;                                         \
        struct _p_##N##_node* left_;                                           \
        struct _p_##N##_node* right_;                                          \
        struct N##_pair data_;                                                 \
        enum _sgc_map_color color_;                                            \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef struct N##_pair N##_pair;                                          \
    typedef struct N##_pair N##_type;                                          \
    typedef V N##_value;                                                       \
    typedef K N##_key;                                                         \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        bool sharing_;                                                         \
        bool sharing_key_;                                                     \
        struct _p_##N##_node* root_;                                           \
    };                                                                         \
                                                                               \
    struct N##_it {                                                            \
        struct _p_##N##_node* curr_;                                           \
        struct _p_##N##_node* next_;                                           \
        int valid_;                                                            \
    };                                                                         \
                                                                               \
    typedef struct N##_it N##_it;                                              \
    _SGC_INIT_BD_IT_PROTOTIPES(N)                                              \
                                                                               \
    void N##_set_share(N* m, bool shared);                                     \
    void N##_set_share_key(N* m, bool shared);                                 \
    size_t N##_size(const N* const m);                                         \
    void N##_init(N* m);                                                       \
    void N##_free(N* m);                                                       \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src);       \
    void N##_set(N* m, K k, V v);                                              \
    V* N##_at(N* m, K k);                                                      \
    N##_it N##_find(N* m, const K k);                                          \
    bool N##_erase(N* m, const K key);                                         \
    bool N##_it_erase(N* m, N##_it* i);                                        \
    bool N##_empty(const N* const m);

#define _SGC_INIT_UNIQUE_MAP(K, V, N)                                          \
    static struct _p_##N##_node* _p_##N##_node_new(const K* const k,           \
                                                   const V* const v,           \
                                                   bool sharing_key,           \
                                                   bool sharing_value) {       \
        struct _p_##N##_node* n = sgc_malloc(sizeof(struct _p_##N##_node));    \
                                                                               \
        _SGC_COPY(K, n->data_.key, *k, sharing_key);                           \
        _SGC_COPY(V, n->data_.value, *v, sharing_value);                       \
                                                                               \
        n->left_ = n->right_ = _SGC_MAP_LEAF;                                  \
        n->color_ = _SGC_MAP_COLOR_RED;                                        \
        return n;                                                              \
    }                                                                          \
                                                                               \
    static void _p_##N##_node_insert(N* m, K* k, V* v) {                       \
        struct _p_##N##_node* parent = m->root_;                               \
        struct _p_##N##_node* new_node = NULL;                                 \
        while (true) {                                                         \
            int compare = (K##_compare(&parent->data_.key, k));                \
                                                                               \
            if (compare > 0) {                                                 \
                if (parent->left_ == _SGC_MAP_LEAF) {                          \
                    new_node =                                                 \
                        _p_##N##_node_new(k, v, m->sharing_key_, m->sharing_); \
                    parent->left_ = new_node;                                  \
                    m->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->left_;                                        \
            } else if (compare < 0) {                                          \
                if (parent->right_ == _SGC_MAP_LEAF) {                         \
                    new_node =                                                 \
                        _p_##N##_node_new(k, v, m->sharing_key_, m->sharing_); \
                    parent->right_ = new_node;                                 \
                    m->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->right_;                                       \
            } else if (!V##_eq(&parent->data_.value, v)) {                     \
                _SGC_REPLACE(V, parent->data_.value, *v, m->sharing_);         \
                return;                                                        \
            } else {                                                           \
                return;                                                        \
            }                                                                  \
        }                                                                      \
        new_node->parent_ = parent;                                            \
        _p_##N##_check_color(m, new_node);                                     \
    }                                                                          \
                                                                               \
    void N##_set(N* m, K k, V v) {                                             \
        if (m->root_ == _SGC_MAP_LEAF) {                                       \
            struct _p_##N##_node* new_node =                                   \
                _p_##N##_node_new(&k, &v, m->sharing_key_, m->sharing_);       \
            new_node->color_ = _SGC_MAP_COLOR_BLACK;                           \
            new_node->parent_ = _SGC_MAP_LEAF;                                 \
            m->root_ = new_node;                                               \
            m->size_ = 1;                                                      \
        } else {                                                               \
            _p_##N##_node_insert(m, &k, &v);                                   \
            m->root_->color_ = _SGC_MAP_COLOR_BLACK;                           \
        }                                                                      \
    }                                                                          \
                                                                               \
    static V* _p_##N##_node_insert_or_get(N* m, K* k) {                        \
        V new_el;                                                              \
        V* v = &new_el;                                                        \
        struct _p_##N##_node* parent = m->root_;                               \
        struct _p_##N##_node* new_node = NULL;                                 \
        while (true) {                                                         \
            int compare = (K##_compare(&parent->data_.key, k));                \
                                                                               \
            if (compare > 0) {                                                 \
                if (parent->left_ == _SGC_MAP_LEAF) {                          \
                    V##_init(v);                                               \
                    new_node =                                                 \
                        _p_##N##_node_new(k, v, m->sharing_key_, m->sharing_); \
                    v = &new_node->data_.value;                                \
                    parent->left_ = new_node;                                  \
                    m->size_++;                                                \
                    new_node->parent_ = parent;                                \
                    _p_##N##_check_color(m, new_node);                         \
                    break;                                                     \
                }                                                              \
                parent = parent->left_;                                        \
            } else if (compare < 0) {                                          \
                if (parent->right_ == _SGC_MAP_LEAF) {                         \
                    V##_init(v);                                               \
                    new_node =                                                 \
                        _p_##N##_node_new(k, v, m->sharing_key_, m->sharing_); \
                    v = &new_node->data_.value;                                \
                    parent->right_ = new_node;                                 \
                    m->size_++;                                                \
                    new_node->parent_ = parent;                                \
                    _p_##N##_check_color(m, new_node);                         \
                    break;                                                     \
                }                                                              \
                parent = parent->right_;                                       \
            } else {                                                           \
                v = &parent->data_.value;                                      \
                break;                                                         \
            }                                                                  \
        }                                                                      \
        return v;                                                              \
    }                                                                          \
                                                                               \
    V* N##_at(N* m, K k) {                                                     \
        V* ret = NULL;                                                         \
        if (m->root_ == _SGC_MAP_LEAF) {                                       \
            V v;                                                               \
            V##_init(&v);                                                      \
            struct _p_##N##_node* new_node =                                   \
                _p_##N##_node_new(&k, &v, m->sharing_key_, m->sharing_);       \
            new_node->color_ = _SGC_MAP_COLOR_BLACK;                           \
            new_node->parent_ = _SGC_MAP_LEAF;                                 \
            m->root_ = new_node;                                               \
            m->size_ = 1;                                                      \
            ret = &m->root_->data_.value;                                      \
        } else {                                                               \
            ret = _p_##N##_node_insert_or_get(m, &k);                          \
            m->root_->color_ = _SGC_MAP_COLOR_BLACK;                           \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    static struct _p_##N##_node*                                               \
        _p_##N##_node_erase(N* m, struct _p_##N##_node* n) {                   \
        struct _p_##N##_node* succ;                                            \
        struct _p_##N##_node* succ_p;                                          \
        struct _p_##N##_node* succ_c = _SGC_MAP_LEAF;                          \
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
                                                                               \
        if (succ != n) {                                                       \
            /* TODO relinking nodes would be better */                         \
            _SGC_REPLACE(K, n->data_.key, succ->data_.key, m->sharing_key_)    \
            _SGC_REPLACE(V, n->data_.value, succ->data_.value, m->sharing_)    \
            _p_##N##_node_free(m, succ);                                       \
        } else {                                                               \
            _p_##N##_node_free(m, succ);                                       \
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
        if ((succ_c && succ_c->color_ == _SGC_MAP_COLOR_RED) ||                \
            succ->color_ == _SGC_MAP_COLOR_RED) {                              \
            if (succ_c) {                                                      \
                succ_c->color_ = _SGC_MAP_COLOR_BLACK;                         \
            }                                                                  \
        } else {                                                               \
            _p_##N##_erase_rebalanse(m, succ_c, succ_p);                       \
        }                                                                      \
        if (m->root_) {                                                        \
            m->root_->color_ = _SGC_MAP_COLOR_BLACK;                           \
        }                                                                      \
        --m->size_;                                                            \
        return succ;                                                           \
    }                                                                          \
                                                                               \
    void N##_init(N* s) {                                                      \
        s->size_ = 0;                                                          \
        s->root_ = _SGC_MAP_LEAF;                                              \
        s->sharing_ = 0;                                                       \
        s->sharing_key_ = 0;                                                   \
    }                                                                          \
                                                                               \
    static void _p_##N##_copy_base_data(N* __restrict__ dst,                   \
                                        const N* __restrict__ const src) {     \
        dst->size_ = src->size_;                                               \
        dst->root_ = _SGC_MAP_LEAF;                                            \
        dst->sharing_key_ = src->sharing_key_;                                 \
        dst->sharing_ = src->sharing_;                                         \
    }

#define SGC_INIT_MAP(K, V, N)                                                  \
    SGC_INIT_HEADERS_MAP(K, V, N)                                              \
    _SGC_INIT_PP_MAP(K, V, N)                                                  \
    _SGC_INIT_UNIQUE_MAP(K, V, N)                                              \
    _SGC_INIT_COMMON_DICT_PAIR_BST(K, V, N)                                    \
    _SGC_INIT_COMMON_RBTREE(K, N)                                              \
    _SGC_INIT_COMMON(N)
