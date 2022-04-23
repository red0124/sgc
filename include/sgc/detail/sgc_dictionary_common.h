#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define _SGC_INIT_COMMON_DICT_PAIR(K, V, N)                                    \
    static void                                                                \
        _p_##N##_node_copy_values(const N* const ds,                           \
                                  struct _p_##N##_node* dst,                   \
                                  const struct _p_##N##_node* const src) {     \
        _SGC_COPY(K, dst->data_.key, src->data_.key, ds->sharing_key_);        \
        _SGC_COPY(V, dst->data_.value, src->data_.value, ds->sharing_);        \
    }                                                                          \
                                                                               \
    static void _p_##N##_node_free(const N* const ds,                          \
                                   struct _p_##N##_node* n) {                  \
        _SGC_FREE(V, n->data_.value, ds->sharing_);                            \
        _SGC_FREE(K, n->data_.key, ds->sharing_key_);                          \
    }                                                                          \
                                                                               \
    N##_pair* N##_it_data(N##_it* i) {                                         \
        return &i->curr_->data_;                                               \
    }                                                                          \
                                                                               \
    N##_value* N##_it_value(N##_it* i) {                                       \
        return &i->curr_->data_.value;                                         \
    }                                                                          \
                                                                               \
    void N##_set_sharing_key(N* m) {                                           \
        m->sharing_key_ = true;                                                \
    }                                                                          \
                                                                               \
    void N##_set_owning_key(N* m) {                                            \
        m->sharing_key_ = false;                                               \
    }

#define _SGC_INIT_COMMON_DICT_PAIR_FS_HASH(K, V, N)                            \
    _SGC_INIT_COMMON_DICT_PAIR(K, V, N)                                        \
    static bool _p_##N##_node_eq_key(const struct _p_##N##_node* const n,      \
                                     const K* const key) {                     \
        return K##_eq(&n->data_.key, key);                                     \
    }

#define _SGC_INIT_COMMON_DICT_PAIR_HASH(K, V, N)                               \
    _SGC_INIT_COMMON_DICT_PAIR(K, V, N)                                        \
    static size_t _p_##N##_node_hash_value(                                    \
        const struct _p_##N##_node* const n) {                                 \
        return K##_hash(&n->data_.key);                                        \
    }                                                                          \
                                                                               \
    static bool _p_##N##_node_eq_key(const struct _p_##N##_node* const n,      \
                                     const K* const key) {                     \
        return K##_eq(&n->data_.key, key);                                     \
    }

#define _SGC_INIT_COMMON_DICT_PAIR_BST(K, V, N)                                \
    _SGC_INIT_COMMON_DICT_PAIR(K, V, N)                                        \
    static int _p_##N##_node_compare(const struct _p_##N##_node* const n,      \
                                     const K* const key) {                     \
        return K##_compare(&n->data_.key, key);                                \
    }

#define _SGC_INIT_COMMON_DICT_NONE_PAIR(KV, N)                                 \
    static void                                                                \
        _p_##N##_node_copy_values(const N* const ds,                           \
                                  struct _p_##N##_node* dst,                   \
                                  const struct _p_##N##_node* const src) {     \
        _SGC_COPY(KV, dst->value_, src->value_, ds->sharing_);                 \
    }                                                                          \
                                                                               \
    static void _p_##N##_node_free(const N* const ds,                          \
                                   struct _p_##N##_node* n) {                  \
        _SGC_FREE(KV, n->value_, ds->sharing_);                                \
    }                                                                          \
                                                                               \
    KV* N##_it_data(N##_it* i) {                                                \
        return &i->curr_->value_;                                               \
    }                                                                          \
                                                                               \
    KV* N##_it_value(N##_it* i) {                                               \
        return &i->curr_->value_;                                               \
    }

#define _SGC_INIT_COMMON_DICT_NONE_PAIR_FS_HASH(KV, N)                         \
    _SGC_INIT_COMMON_DICT_NONE_PAIR(KV, N)                                     \
    static bool _p_##N##_node_eq_key(const struct _p_##N##_node* const n,      \
                                     const KV* const key) {                    \
        return KV##_eq(&n->value_, key);                                       \
    }

#define _SGC_INIT_COMMON_DICT_NONE_PAIR_HASH(KV, N)                            \
    _SGC_INIT_COMMON_DICT_NONE_PAIR(KV, N)                                     \
    static bool _p_##N##_node_eq_key(const struct _p_##N##_node* const n,      \
                                     const KV* const key) {                    \
        return KV##_eq(&n->value_, key);                                       \
    }                                                                          \
                                                                               \
    static size_t _p_##N##_node_hash_value(                                    \
        const struct _p_##N##_node* const n) {                                 \
        return KV##_hash(&n->value_);                                          \
    }

#define _SGC_INIT_COMMON_DICT_NONE_PAIR_BST(KV, N)                             \
    _SGC_INIT_COMMON_DICT_NONE_PAIR(KV, N)                                     \
    static int _p_##N##_node_compare(const struct _p_##N##_node* const n,      \
                                     const KV* const key) {                    \
        return KV##_compare(&n->value_, key);                                  \
    }
