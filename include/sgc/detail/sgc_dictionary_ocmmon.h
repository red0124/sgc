#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define _SGC_INIT_COMMON_DICTIONARY_PAIR_FUNCTIONS(K, V, N)                    \
    static void N##_node_copy_values(const struct N* const ds,                 \
                                     struct N##_node* dst,                     \
                                     const struct N##_node* const src) {       \
        SGC_COPY(K##_copy, dst->data_.key, src->data_.key, ds->shared_key_);   \
        SGC_COPY(V##_copy, dst->data_.value, src->data_.value, ds->shared_);   \
    }                                                                          \
                                                                               \
    static void N##_node_free(const struct N* const ds, struct N##_node* n) {  \
        SGC_FREE(V##_free, n->data_.value, ds->shared_);                       \
        SGC_FREE(K##_free, n->data_.key, ds->shared_key_);                     \
    }                                                                          \
                                                                               \
    static bool N##_node_equal_key(const struct N##_node* const n,             \
                                   const K* const key) {                       \
        return K##_equal(&n->data_.key, key);                                  \
    }                                                                          \
                                                                               \
    static int N##_node_compare(const struct N##_node* const n,                \
                                const K* const key) {                          \
        return K##_compare(&n->data_.key, key);                                \
    }                                                                          \
                                                                               \
    static size_t N##_node_hash(const struct N##_node* const n) {              \
        return K##_hash(&n->data_.key);                                        \
    }

#define _SGC_INIT_COMMON_DICTIONARY_NONE_PAIR_FUNCTIONS(KV, N)                 \
    static void N##_node_copy_values(const struct N* const ds,                 \
                                     struct N##_node* dst,                     \
                                     const struct N##_node* const src) {       \
        SGC_COPY(KV##_copy, dst->_value, src->_value, m->shared_);             \
    }                                                                          \
                                                                               \
    static void N##_node_free(const struct N* const ds, struct N##_node* n) {  \
        SGC_FREE(KV##_free, n->_value, u->shared_);                            \
    }                                                                          \
                                                                               \
    static bool N##_node_equal_key(const struct N##_node* const n,             \
                                   const KV* const key) {                      \
        return KV##_equal(&n->_value, key);                                    \
    }                                                                          \
                                                                               \
    static int N##_node_compare(const struct N##_node* const n,                \
                                const KV* const key) {                         \
        return KV##_compare(&n->_value, key);                                  \
    }                                                                          \
                                                                               \
    static size_t N##_node_hash(const struct N##_node* const n) {              \
        return KV##_hash(&n->_value);                                          \
    }
