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

#define _SGC_INIT_PP_MAP(K, V, N)                                              \
    static int _p_##N##_node_compare(const struct N##_node* const n,           \
                                     const K* const key);                      \
    static struct N##_node* _p_##N##_node_begin(struct N##_node* n);           \
    static struct N##_node* _p_##N##_node_end(struct N##_node* n);             \
    static struct N##_node* _p_##N##_node_new(const K* const k,                \
                                              const V* const v,                \
                                              bool shared_key, bool shared);   \
    static size_t _p_##N##_stack_size(size_t size);                            \
    static bool _p_##N##_is_left_child(const struct N##_node* const n,         \
                                       const struct N##_node* const parent);   \
    static struct N##_node*                                                    \
        _p_##N##_sibling(const struct N##_node* const n,                       \
                         const struct N##_node* const parent);                 \
    static void _p_##N##_rotate_left(N* m, struct N##_node* parent,     \
                                     struct N##_node* gparent);                \
    static void _p_##N##_rotate_right(N* m, struct N##_node* parent,    \
                                      struct N##_node* gparent);               \
    static void _p_##N##_rotate_left_right(N* m, struct N##_node* n,    \
                                           struct N##_node* parent,            \
                                           struct N##_node* gparent);          \
    static void _p_##N##_rotate_right_left(N* m, struct N##_node* n,    \
                                           struct N##_node* parent,            \
                                           struct N##_node* gparent);          \
    static void _p_##N##_rotate(N* m, struct N##_node* n,               \
                                struct N##_node* parent,                       \
                                struct N##_node* gparent);                     \
    static void _p_##N##_correct_tree(N* m, struct N##_node* n,         \
                                      struct N##_node* p,                      \
                                      struct N##_node* gp);                    \
    static void _p_##N##_check_color(N* m, struct N##_node* n);         \
    static void _p_##N##_node_insert(N* m, K* k, V* v);                 \
    static V* N##_node_insert_or_get(N* m, K* k);                       \
    static struct N##_node* _p_##N##_node_find(N* m, K k);              \
    static void _p_##N##_erase_rebalanse(N* m, struct N##_node* n,      \
                                         struct N##_node* p);                  \
    static struct N##_node* _p_##N##_node_erase(N* m,                   \
                                                struct N##_node* n);           \
    static void _p_##N##_node_copy_values(const N* const m,             \
                                          struct N##_node* dst,                \
                                          const struct N##_node* const src);   \
    static struct N##_node*                                                    \
        _p_##N##_node_duplicate(const N* const m,                       \
                                const struct N##_node* const n);               \
    static void                                                                \
        _p_##N##_copy_base_data(N* __restrict__ dst,                    \
                                const N* __restrict__ const src);       \
    static void _p_##N##_copy_nodes(N* __restrict__ dst,                \
                                    const N* __restrict__ const src);   \
    static void _p_##N##_node_free(const N* const m, struct N##_node* n);

#define SGC_INIT_HEADERS_MAP(K, V, N)                                          \
    struct N##_pair {                                                          \
        K key;                                                                 \
        V value;                                                               \
    };                                                                         \
                                                                               \
    struct N##_node {                                                          \
        struct N##_node* parent_;                                              \
        struct N##_node* left_;                                                \
        struct N##_node* right_;                                               \
        struct N##_pair data_;                                                 \
        enum sgc_map_color color_;                                             \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef struct N##_pair N##_type;                                          \
    typedef V N##_value;                                                       \
    typedef K N##_key;                                                         \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        bool shared_;                                                          \
        bool shared_key_;                                                      \
        struct N##_node* root_;                                                \
    };                                                                         \
                                                                               \
    struct N##_it {                                                            \
        struct N##_node* curr_;                                                \
        struct N##_node* next_;                                                \
        int valid_;                                                            \
    };                                                                         \
                                                                               \
    typedef struct N##_it N##_it;                                              \
    _SGC_INIT_BD_IT_PROTOTIPES(N)                                              \
                                                                               \
    void N##_set_share(N* m, bool shared);                                     \
    void N##_set_share_key(N* m, bool shared);                                 \
    size_t N##_size(const N* const m);                                  \
    void N##_init(N* m);                                                \
    void N##_free(N* m);                                                \
    void N##_copy(N* __restrict__ dst,                                  \
                  const N* __restrict__ const src);                     \
    void N##_set(N* m, K k, V v);                                       \
    const V* N##_at(N* m, K k);                                         \
    struct N##_it N##_find(N* m, const K k);                            \
    bool N##_erase(N* m, const K key);                                  \
    bool N##_it_erase(N* m, struct N##_it* i);                          \
    bool N##_empty(const N* const m);

#define _SGC_INIT_UNIQUE_MAP(K, V, N)                                          \
    static struct N##_node* _p_##N##_node_new(const K* const k,                \
                                              const V* const v,                \
                                              bool shared_key, bool shared) {  \
        struct N##_node* n = sgc_malloc(sizeof(struct N##_node));              \
                                                                               \
        SGC_COPY(K##_copy, n->data_.key, *k, shared_key);                      \
        SGC_COPY(V##_copy, n->data_.value, *v, shared);                        \
                                                                               \
        n->left_ = n->right_ = SGC_MAP_LEAF;                                   \
        n->color_ = SGC_MAP_RED;                                               \
        return n;                                                              \
    }                                                                          \
                                                                               \
    static void _p_##N##_node_insert(N* m, K* k, V* v) {                \
        struct N##_node* parent = m->root_;                                    \
        struct N##_node* new_node = NULL;                                      \
        while (true) {                                                         \
            int compare = (K##_compare(&parent->data_.key, k));                \
                                                                               \
            if (compare > 0) {                                                 \
                if (parent->left_ == SGC_MAP_LEAF) {                           \
                    new_node =                                                 \
                        _p_##N##_node_new(k, v, m->shared_key_, m->shared_);   \
                    parent->left_ = new_node;                                  \
                    m->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->left_;                                        \
            } else if (compare < 0) {                                          \
                if (parent->right_ == SGC_MAP_LEAF) {                          \
                    new_node =                                                 \
                        _p_##N##_node_new(k, v, m->shared_key_, m->shared_);   \
                    parent->right_ = new_node;                                 \
                    m->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->right_;                                       \
            } else if (!V##_equal(&parent->data_.value, v)) {                  \
                SGC_REPLACE(V##_copy, V##_free, parent->data_.value, *v,       \
                            m->shared_);                                       \
                return;                                                        \
            } else {                                                           \
                return;                                                        \
            }                                                                  \
        }                                                                      \
        new_node->parent_ = parent;                                            \
        _p_##N##_check_color(m, new_node);                                     \
    }                                                                          \
                                                                               \
    void N##_set(N* m, K k, V v) {                                      \
        if (m->root_ == SGC_MAP_LEAF) {                                        \
            struct N##_node* new_node =                                        \
                _p_##N##_node_new(&k, &v, m->shared_key_, m->shared_);         \
            new_node->color_ = SGC_MAP_BLACK;                                  \
            new_node->parent_ = SGC_MAP_LEAF;                                  \
            m->root_ = new_node;                                               \
            m->size_ = 1;                                                      \
        } else {                                                               \
            _p_##N##_node_insert(m, &k, &v);                                   \
            m->root_->color_ = SGC_MAP_BLACK;                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    static V* N##_node_insert_or_get(N* m, K* k) {                      \
        V new_el;                                                              \
        V* v = &new_el;                                                        \
        struct N##_node* parent = m->root_;                                    \
        struct N##_node* new_node = NULL;                                      \
        while (true) {                                                         \
            int compare = (K##_compare(&parent->data_.key, k));                \
                                                                               \
            if (compare > 0) {                                                 \
                if (parent->left_ == SGC_MAP_LEAF) {                           \
                    V##_init(v);                                               \
                    new_node =                                                 \
                        _p_##N##_node_new(k, v, m->shared_key_, m->shared_);   \
                    v = &new_node->data_.value;                                \
                    parent->left_ = new_node;                                  \
                    m->size_++;                                                \
                    new_node->parent_ = parent;                                \
                    _p_##N##_check_color(m, new_node);                         \
                    break;                                                     \
                }                                                              \
                parent = parent->left_;                                        \
            } else if (compare < 0) {                                          \
                if (parent->right_ == SGC_MAP_LEAF) {                          \
                    V##_init(v);                                               \
                    new_node =                                                 \
                        _p_##N##_node_new(k, v, m->shared_key_, m->shared_);   \
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
    const V* N##_at(N* const m, K k) {                                  \
        V* ret = NULL;                                                         \
        if (m->root_ == SGC_MAP_LEAF) {                                        \
            V v;                                                               \
            V##_init(&v);                                                      \
            struct N##_node* new_node =                                        \
                _p_##N##_node_new(&k, &v, m->shared_key_, m->shared_);         \
            new_node->color_ = SGC_MAP_BLACK;                                  \
            new_node->parent_ = SGC_MAP_LEAF;                                  \
            m->root_ = new_node;                                               \
            m->size_ = 1;                                                      \
            ret = &m->root_->data_.value;                                      \
        } else {                                                               \
            ret = N##_node_insert_or_get(m, &k);                               \
            m->root_->color_ = SGC_MAP_BLACK;                                  \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    static struct N##_node* _p_##N##_node_erase(N* m,                   \
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
                                                                               \
        if (succ != n) {                                                       \
            /* TODO relinking nodes would be better */                         \
            SGC_REPLACE(K##_copy, K##_free, n->data_.key, succ->data_.key,     \
                        m->shared_key_)                                        \
            SGC_REPLACE(V##_copy, V##_free, n->data_.value, succ->data_.value, \
                        m->shared_)                                            \
                                                                               \
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
    void N##_init(N* s) {                                               \
        s->size_ = 0;                                                          \
        s->root_ = SGC_MAP_LEAF;                                               \
        s->shared_ = 0;                                                        \
        s->shared_key_ = 0;                                                    \
    }                                                                          \
                                                                               \
    static void                                                                \
        _p_##N##_copy_base_data(N* __restrict__ dst,                    \
                                const N* __restrict__ const src) {      \
        dst->size_ = src->size_;                                               \
        dst->root_ = SGC_MAP_LEAF;                                             \
        dst->shared_key_ = src->shared_key_;                                   \
        dst->shared_ = src->shared_;                                           \
    }

#define SGC_INIT_MAP(K, V, N)                                                  \
    SGC_INIT_HEADERS_MAP(K, V, N)                                              \
    _SGC_INIT_PP_MAP(K, V, N)                                                  \
    _SGC_INIT_UNIQUE_MAP(K, V, N)                                              \
    _SGC_INIT_COMMON_DICT_PAIR(K, V, N)                                        \
    _SGC_INIT_COMMON_RBTREE(K, N)                                              \
    _SGC_INIT_COMMON(N)
