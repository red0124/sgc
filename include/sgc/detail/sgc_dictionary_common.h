#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define _SGC_INIT_COMMON_DICT_PAIR(K, V, N)                                    \
    static inline void                                                         \
        _p_##N##_node_copy_values(const N* const ds,                           \
                                  struct _p_##N##_node* dst,                   \
                                  const struct _p_##N##_node* const src) {     \
        SGC_COPY(K##_copy, dst->data_.key, src->data_.key, ds->sharing_key_);  \
        SGC_COPY(V##_copy, dst->data_.value, src->data_.value, ds->sharing_);  \
    }                                                                          \
                                                                               \
    static inline void _p_##N##_node_free(const N* const ds,                   \
                                          struct _p_##N##_node* n) {           \
        SGC_FREE(V##_free, n->data_.value, ds->sharing_);                      \
        SGC_FREE(K##_free, n->data_.key, ds->sharing_key_);                    \
    }                                                                          \
                                                                               \
    N##_pair* N##_it_data(N##_it i) {                                          \
        return &i.curr_->data_;                                                \
    }                                                                          \
                                                                               \
    void N##_set_shareing_key(N* m) {                                          \
        m->sharing_key_ = true;                                                \
    }                                                                          \
                                                                               \
    void N##_set_owning_key(N* m) {                                            \
        m->sharing_key_ = false;                                               \
    }

#define _SGC_INIT_COMMON_DICT_PAIR_HASH(K, V, N)                               \
    _SGC_INIT_COMMON_DICT_PAIR(K, V, N)                                       \
    static inline size_t _p_##N##_node_hash_value(                             \
        const struct _p_##N##_node* const n) {                                 \
        return K##_hash(&n->data_.key);                                        \
    }                                                                          \
                                                                               \
    static inline bool                                                         \
        _p_##N##_node_eq_key(const struct _p_##N##_node* const n,              \
                             const K* const key) {                             \
        return K##_eq(&n->data_.key, key);                                     \
    }

#define _SGC_INIT_COMMON_DICT_PAIR_BST(K, V, N)                                \
    _SGC_INIT_COMMON_DICT_PAIR(K, V, N)                                       \
    static inline int                                                          \
        _p_##N##_node_compare(const struct _p_##N##_node* const n,             \
                              const K* const key) {                            \
        return K##_compare(&n->data_.key, key);                                \
    }

#define _SGC_INIT_COMMON_DICT_NONE_PAIR(KV, N)                                 \
    static inline void                                                         \
        _p_##N##_node_copy_values(const N* const ds,                           \
                                  struct _p_##N##_node* dst,                   \
                                  const struct _p_##N##_node* const src) {     \
        SGC_COPY(KV##_copy, dst->value_, src->value_, ds->sharing_);           \
    }                                                                          \
                                                                               \
    static inline void _p_##N##_node_free(const N* const ds,                   \
                                          struct _p_##N##_node* n) {           \
        SGC_FREE(KV##_free, n->value_, ds->sharing_);                          \
    }                                                                          \
                                                                               \
    KV* N##_it_data(N##_it i) {                                                \
        return &i.curr_->value_;                                               \
    }

#define _SGC_INIT_COMMON_DICT_NONE_PAIR_HASH(KV, N)                            \
    _SGC_INIT_COMMON_DICT_NONE_PAIR(KV, N)                                     \
    static inline bool                                                         \
        _p_##N##_node_eq_key(const struct _p_##N##_node* const n,              \
                             const KV* const key) {                            \
        return KV##_eq(&n->value_, key);                                       \
    }                                                                          \
                                                                               \
    static inline size_t _p_##N##_node_hash_value(                             \
        const struct _p_##N##_node* const n) {                                 \
        return KV##_hash(&n->value_);                                          \
    }

#define _SGC_INIT_COMMON_DICT_NONE_PAIR_BST(KV, N)                             \
    _SGC_INIT_COMMON_DICT_NONE_PAIR(KV, N)                                     \
    static inline int                                                          \
        _p_##N##_node_compare(const struct _p_##N##_node* const n,             \
                              const KV* const key) {                           \
        return KV##_compare(&n->value_, key);                                  \
    }