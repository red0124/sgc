#pragma once

#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_dictionary_ocmmon.h"
#include "detail/sgc_hash_node_state.h"
#include "detail/sgc_static_hash_map_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define SGC_INIT_STATIC_FUNCTIONS_STATIC_UNORDERED_MAP(K, V, S, N)             \
    static struct N##_iterator _m_##N##_find_by_hash(struct N* u,              \
                                                     const K* const k,         \
                                                     size_t hash);             \
    static struct N##_iterator N##_iterator_at(const struct N* const u,        \
                                               size_t at);                     \
    static void _m_##N##_node_free(const struct N* const m,                    \
                                   struct N##_node* n);                        \
    static void _m_##N##_node_copy_values(const struct N* const m,             \
                                          struct N##_node* dst,                \
                                          const struct N##_node* const src);   \
    static size_t _m_##N##_node_hash_value(const struct N##_node* n);          \
    static bool _m_##N##_node_equal_key(const struct N##_node* const n,        \
                                        const K* const key);

#define SGC_INIT_HEADERS_STATIC_UNORDERED_MAP(K, V, S, N)                      \
    struct N##_pair {                                                          \
        K key;                                                                 \
        V value;                                                               \
    };                                                                         \
                                                                               \
    struct N##_node {                                                          \
        struct N##_pair data_;                                                 \
        char _state;                                                           \
    };                                                                         \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t shared_;                                                        \
        size_t shared_key_;                                                    \
        struct N##_node data_[S];                                              \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef struct N##_pair N##_type;                                          \
    typedef V N##_value;                                                       \
    typedef K N##_key;                                                         \
                                                                               \
    size_t N##_max(void);                                                      \
                                                                               \
    struct N##_iterator {                                                      \
        struct N##_node* begin_;                                               \
        struct N##_node* curr_;                                                \
        struct N##_node* end_;                                                 \
        int is_valid_;                                                         \
    };                                                                         \
                                                                               \
    typedef struct N##_iterator N##_iterator;                                  \
                                                                               \
    const struct N##_pair* N##_iterator_cdata(struct N##_iterator i);          \
    struct N##_pair* N##_iterator_data(struct N##_iterator i);                 \
    void N##_iterator_next(struct N##_iterator* i);                            \
    void N##_iterator_begin(struct N* m, struct N##_iterator* i);              \
    void N##_iterator_cbegin(const struct N* const m, struct N##_iterator* i); \
    void N##_iterator_prev(struct N##_iterator* i);                            \
    void N##_iterator_end(struct N* m, struct N##_iterator* i);                \
    void N##_iterator_cend(const struct N* const m, struct N##_iterator* i);   \
    struct N##_iterator N##_begin(struct N* m);                                \
    struct N##_iterator N##_cbegin(const struct N* const m);                   \
    struct N##_iterator N##_end(struct N* m);                                  \
    struct N##_iterator N##_cend(const struct N* const m);                     \
    bool N##_iterator_equal(const struct N##_iterator first,                   \
                            const struct N##_iterator second);                 \
    bool N##_iterator_valid(const struct N##_iterator i);                      \
                                                                               \
    void N##_set_share(N* u, int is_shared);                                   \
    void N##_set_share_key(N* u, int is_shared);                               \
    size_t N##_size(const struct N* const u);                                  \
    void N##_init(struct N* u);                                                \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src);       \
    void N##_free(struct N* u);                                                \
    struct N##_iterator N##_find(struct N* u, const K k);                      \
    void N##_set_at(struct N* u, const K k, const V v);                        \
    V* N##_at(struct N* u, K k);                                               \
    void N##_iterator_erase(struct N* u, struct N##_iterator* i);              \
    void N##_erase(struct N* u, const K k);                                    \
    bool N##_empty(const struct N* const u);

#define _SGC_INIT_UNIQUE_STATIC_UNORDERED_MAP_FUNCTIONS(K, V, S, N)            \
    size_t N##_max(void) {                                                     \
        return S;                                                              \
    }                                                                          \
                                                                               \
    void N##_init(struct N* u) {                                               \
        u->size_ = 0;                                                          \
        u->shared_ = u->shared_key_ = 0;                                       \
        for (size_t i = 0; i < S; ++i) {                                       \
            u->data_[i]._state = SGC_NODE_STATE_OPEN;                          \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_set_at(struct N* u, const K k, const V v) {                       \
        size_t hash = K##_hash(&k);                                            \
        struct N##_iterator i = _m_##N##_find_by_hash(u, &k, hash);            \
        if (i.is_valid_) {                                                     \
            SGC_REPLACE(V##_copy, V##_free, i.curr_->data_.value, v,           \
                        u->shared_);                                           \
        } else if (u->size_ < S - 1) {                                         \
            size_t position = hash % S;                                        \
            while (u->data_[position]._state == SGC_NODE_STATE_USED) {         \
                if (position == S - 1) {                                       \
                    position = 0;                                              \
                } else {                                                       \
                    ++position;                                                \
                }                                                              \
            }                                                                  \
            SGC_COPY(K##_copy, u->data_[position].data_.key, k,                \
                     u->shared_key_);                                          \
            SGC_COPY(V##_copy, u->data_[position].data_.value, v, u->shared_); \
            u->data_[position]._state = SGC_NODE_STATE_USED;                   \
            ++u->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    V* N##_at(struct N* u, K k) {                                              \
        size_t hash = K##_hash(&k);                                            \
        struct N##_iterator i = _m_##N##_find_by_hash(u, &k, hash);            \
        V* ret = NULL;                                                         \
        if (i.is_valid_) {                                                     \
            ret = &i.curr_->data_.value;                                       \
        } else if (u->size_ < S - 1) {                                         \
            V v;                                                               \
            V##_init(&v);                                                      \
            size_t position = hash % S;                                        \
            while (u->data_[position]._state == SGC_NODE_STATE_USED) {         \
                if (position == S - 1) {                                       \
                    position = 0;                                              \
                } else {                                                       \
                    ++position;                                                \
                }                                                              \
            }                                                                  \
            SGC_COPY(K##_copy, u->data_[position].data_.key, k,                \
                     u->shared_key_);                                          \
            SGC_COPY(V##_copy, u->data_[position].data_.value, v, u->shared_); \
            u->data_[position]._state = SGC_NODE_STATE_USED;                   \
            ++u->size_;                                                        \
            ret = &u->data_[position].data_.value;                             \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src) {      \
        dst->size_ = src->size_;                                               \
        dst->shared_ = src->shared_;                                           \
        dst->shared_key_ = src->shared_key_;                                   \
        for (size_t i = 0; i < S; ++i) {                                       \
            if (src->data_[i]._state == SGC_NODE_STATE_USED) {                 \
                _m_##N##_node_copy_values(src, &dst->data_[i],                 \
                                          &src->data_[i]);                     \
            }                                                                  \
            dst->data_[i]._state = src->data_[i]._state;                       \
        }                                                                      \
    }

#define SGC_INIT_STATIC_UNORDERED_MAP(K, V, S, N)                              \
    SGC_INIT_HEADERS_STATIC_UNORDERED_MAP(K, V, S, N)                          \
    SGC_INIT_STATIC_FUNCTIONS_STATIC_UNORDERED_MAP(K, V, S, N)                 \
    _SGC_INIT_UNIQUE_STATIC_UNORDERED_MAP_FUNCTIONS(K, V, S, N)                \
    _SGC_INIT_COMMON_DICTIONARY_PAIR_FUNCTIONS(K, V, N)                        \
    _SGC_INIT_STATIC_HASH_MAP_TYPE_FUNCTIONS(K, S, N)                          \
    _SGC_INIT_COMMON_FUNCTIONS(N)
