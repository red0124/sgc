#pragma once

#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_dictionary_ocmmon.h"
#include "detail/sgc_hash_node_state.h"
#include "detail/sgc_iterator.h"
#include "detail/sgc_static_hash_map_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define _SGC_INIT_PP_SUNORDERED_SET(KV, S, N)                                  \
    static struct N##_it _p_##N##_find_by_hash(N* u, const KV* const k, \
                                               size_t hash);                   \
    static struct N##_it N##_it_at(const N* const u, size_t at);        \
    static void _p_##N##_node_free(const N* const m,                    \
                                   struct N##_node* n);                        \
    static void _p_##N##_node_copy_values(const N* const m,             \
                                          struct N##_node* dst,                \
                                          const struct N##_node* const src);   \
    static size_t _p_##N##_node_hash_value(const struct N##_node* n);          \
    static bool _p_##N##_node_equal_key(const struct N##_node* const n,        \
                                        const KV* const key);

#define SGC_INIT_HEADERS_SUNORDERED_SET(V, S, N)                               \
    struct N##_node {                                                          \
        V value_;                                                              \
        enum sgc_node_state state_;                                            \
    };                                                                         \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        bool shared_;                                                          \
        struct N##_node data_[S];                                              \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef V N##_type;                                                        \
                                                                               \
    size_t N##_max(void);                                                      \
                                                                               \
    struct N##_it {                                                            \
        struct N##_node* begin_;                                               \
        struct N##_node* curr_;                                                \
        struct N##_node* end_;                                                 \
        bool valid_;                                                           \
    };                                                                         \
                                                                               \
    typedef struct N##_it N##_it;                                              \
    _SGC_INIT_BD_IT_PROTOTIPES(N)                                              \
                                                                               \
    void N##_set_share(N* u, bool shared);                                     \
    size_t N##_size(const N* const u);                                  \
    void N##_init(N* u);                                                \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src);       \
    void N##_free(N* u);                                                \
    struct N##_it N##_find(N* u, const V v);                            \
    void N##_insert(N* u, const V v);                                   \
    void N##_insert_multiple(N* u, const V v);                          \
    void N##_it_erase(N* u, struct N##_it* i);                          \
    void N##_erase(N* u, const V v);                                    \
    bool N##_empty(const N* const u);

#define _SGC_INIT_UNIQUE_SUNORDERED_SET(V, S, N)                               \
    size_t N##_max(void) {                                                     \
        return S;                                                              \
    }                                                                          \
                                                                               \
    void N##_init(N* u) {                                               \
        u->size_ = 0;                                                          \
        u->shared_ = false;                                                    \
        for (size_t i = 0; i < S; ++i) {                                       \
            u->data_[i].state_ = SGC_NODE_STATE_OPEN;                          \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_insert(N* u, const V v) {                                  \
        size_t hash = V##_hash(&v);                                            \
        struct N##_it i = _p_##N##_find_by_hash(u, &v, hash);                  \
        if (!i.valid_ && u->size_ < S - 1) {                                   \
            size_t position = hash % S;                                        \
            while (u->data_[position].state_ == SGC_NODE_STATE_USED) {         \
                if (position == S - 1) {                                       \
                    position = 0;                                              \
                } else {                                                       \
                    ++position;                                                \
                }                                                              \
            }                                                                  \
            SGC_COPY(V##_copy, u->data_[position].value_, v, u->shared_);      \
            u->data_[position].state_ = SGC_NODE_STATE_USED;                   \
            ++u->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_insert_multiple(N* u, const V v) {                         \
        if (u->size_ < S - 1) {                                                \
            size_t position = V##_hash(&v) % S;                                \
            while (u->data_[position].state_ == SGC_NODE_STATE_USED) {         \
                if (position == S - 1) {                                       \
                    position = 0;                                              \
                } else {                                                       \
                    ++position;                                                \
                }                                                              \
            }                                                                  \
            SGC_COPY(V##_copy, u->data_[position].value_, v, u->shared_);      \
            u->data_[position].state_ = SGC_NODE_STATE_USED;                   \
            ++u->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src) {      \
        if (src->size_ != 0) {                                                 \
            dst->size_ = src->size_;                                           \
            dst->shared_ = src->shared_;                                       \
            for (size_t i = 0; i < S; ++i) {                                   \
                if (src->data_[i].state_ == SGC_NODE_STATE_USED) {             \
                    _p_##N##_node_copy_values(src, &dst->data_[i],             \
                                              &src->data_[i]);                 \
                }                                                              \
                dst->data_[i].state_ = src->data_[i].state_;                   \
            }                                                                  \
        } else {                                                               \
            N##_init(dst);                                                     \
        }                                                                      \
    }

#define SGC_INIT_SUNORDERED_SET(V, S, N)                                       \
    SGC_INIT_HEADERS_SUNORDERED_SET(V, S, N)                                   \
    _SGC_INIT_PP_SUNORDERED_SET(V, S, N)                                       \
    _SGC_INIT_UNIQUE_SUNORDERED_SET(V, S, N)                                   \
    _SGC_INIT_COMMON_DICT_NONE_PAIR(V, N)                                      \
    _SGC_INIT_COMMON_SHASH_MAP(V, S, N)                                        \
    _SGC_INIT_COMMON(N)
