#pragma once

#include "detail/sgc_common.h"
#include "detail/sgc_dictionary_common.h"
#include "detail/sgc_error_handlers.h"
#include "detail/sgc_fs_hash_map_common.h"
#include "detail/sgc_iterator.h"
#include "detail/sgc_primitive_types.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define _SGC_INIT_PP_FS_UNORDERED_MAP(K, V, S, N)                              \
    static N##_it _p_##N##_find_by_hash(N* u, const K* const k, size_t hash);  \
    static N##_it _p_##N##_it_at(const N* const u, size_t at);                 \
    static void _p_##N##_node_free(const N* const m, struct _p_##N##_node* n); \
    static void                                                                \
        _p_##N##_node_copy_values(const N* const m, struct _p_##N##_node* dst, \
                                  const struct _p_##N##_node* const src);      \
    static bool _p_##N##_node_eq_key(const struct _p_##N##_node* const n,      \
                                     const K* const key);

#define SGC_INIT_HEADERS_FS_UNORDERED_MAP(K, V, S, N)                          \
    struct N##_pair {                                                          \
        K key;                                                                 \
        V value;                                                               \
    };                                                                         \
                                                                               \
    struct _p_##N##_node {                                                     \
        struct N##_pair data_;                                                 \
        enum _sgc_node_state state_;                                           \
    };                                                                         \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        bool sharing_;                                                         \
        bool sharing_key_;                                                     \
        struct _p_##N##_node data_[S];                                         \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef struct N##_pair N##_pair;                                          \
    typedef struct N##_pair N##_type;                                          \
    typedef V N##_value;                                                       \
    typedef K N##_key;                                                         \
                                                                               \
    size_t N##_max(void);                                                      \
                                                                               \
    struct N##_it {                                                            \
        bool valid_;                                                           \
        struct _p_##N##_node* begin_;                                          \
        struct _p_##N##_node* curr_;                                           \
        struct _p_##N##_node* end_;                                            \
    };                                                                         \
                                                                               \
    typedef struct N##_it N##_it;                                              \
    _SGC_INIT_BD_IT_PROTOTIPES(N)                                              \
    void N##_set_sharing(N* u);                                                \
    void N##_set_owning(N* u);                                                 \
    void N##_set_share_key(N* u, bool shared);                                 \
    size_t N##_size(const N* const u);                                         \
    void N##_init(N* u);                                                       \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src);       \
    void N##_free(N* u);                                                       \
    N##_it N##_find(N* u, const K k);                                          \
    void N##_set(N* u, const K k, const V v);                                  \
    V* N##_at(N* u, K k);                                                      \
    void N##_erase_it(N* u, N##_it* i);                                        \
    void N##_erase(N* u, const K k);                                           \
    bool N##_empty(const N* const u);

#define _SGC_INIT_UNIQUE_FS_UNORDERED_MAP(K, V, S, N)                          \
    size_t N##_max(void) {                                                     \
        return S;                                                              \
    }                                                                          \
                                                                               \
    void N##_init(N* u) {                                                      \
        u->size_ = 0;                                                          \
        u->sharing_ = u->sharing_key_ = 0;                                     \
        for (size_t i = 0; i < S; ++i) {                                       \
            u->data_[i].state_ = _SGC_NODE_STATE_OPEN;                         \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_set(N* u, const K k, const V v) {                                 \
        size_t hash = K##_hash(&k);                                            \
        N##_it i = _p_##N##_find_by_hash(u, &k, hash);                         \
        if (i.valid_) {                                                        \
            _SGC_REPLACE(V, i.curr_->data_.value, v, u->sharing_);             \
        } else if (u->size_ < S) {                                             \
            size_t position = hash % S;                                        \
            while (u->data_[position].state_ == _SGC_NODE_STATE_USED) {        \
                if (position == S - 1) {                                       \
                    position = 0;                                              \
                } else {                                                       \
                    ++position;                                                \
                }                                                              \
            }                                                                  \
            _SGC_COPY(K, u->data_[position].data_.key, k, u->sharing_key_);    \
            _SGC_COPY(V, u->data_[position].data_.value, v, u->sharing_);      \
            u->data_[position].state_ = _SGC_NODE_STATE_USED;                  \
            ++u->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    V* N##_at(N* u, K k) {                                                     \
        size_t hash = K##_hash(&k);                                            \
        N##_it i = _p_##N##_find_by_hash(u, &k, hash);                         \
        if (i.valid_) {                                                        \
            return &i.curr_->data_.value;                                      \
        } else if (u->size_ < S) {                                             \
            size_t position = hash % S;                                        \
            while (u->data_[position].state_ == _SGC_NODE_STATE_USED) {        \
                if (position == S - 1) {                                       \
                    position = 0;                                              \
                } else {                                                       \
                    ++position;                                                \
                }                                                              \
            }                                                                  \
            _SGC_COPY(K, u->data_[position].data_.key, k, u->sharing_key_);    \
            u->data_[position].state_ = _SGC_NODE_STATE_USED;                  \
            ++u->size_;                                                        \
            V* v = &u->data_[position].data_.value;                            \
            V##_init(v);                                                       \
            return v;                                                          \
        } else {                                                               \
            _sgc_no_space_left_handler();                                      \
        }                                                                      \
        return NULL;                                                           \
    }                                                                          \
                                                                               \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src) {      \
        if (src->size_ > 0) {                                                  \
            dst->size_ = src->size_;                                           \
            dst->sharing_ = src->sharing_;                                     \
            dst->sharing_key_ = src->sharing_key_;                             \
            for (size_t i = 0; i < S; ++i) {                                   \
                if (src->data_[i].state_ == _SGC_NODE_STATE_USED) {            \
                    _p_##N##_node_copy_values(src, &dst->data_[i],             \
                                              &src->data_[i]);                 \
                }                                                              \
                dst->data_[i].state_ = src->data_[i].state_;                   \
            }                                                                  \
        } else {                                                               \
            N##_init(dst);                                                     \
        }                                                                      \
    }

#define SGC_INIT_DEFINITIONS_FS_UNORDERED_MAP(K, V, S, N)                      \
    _SGC_INIT_PP_FS_UNORDERED_MAP(K, V, S, N)                                  \
    _SGC_INIT_UNIQUE_FS_UNORDERED_MAP(K, V, S, N)                              \
    _SGC_INIT_COMMON_DICT_PAIR_FS_HASH(K, V, N)                                \
    _SGC_INIT_COMMON_FS_HASH_MAP(K, S, N)                                      \
    _SGC_INIT_IT_CBEGIN_CEND(N)                                                \
    _SGC_INIT_COMMON(N)

#define SGC_INIT_FS_UNORDERED_MAP(K, V, S, N)                                  \
    SGC_INIT_HEADERS_FS_UNORDERED_MAP(K, V, S, N)                              \
    SGC_INIT_DEFINITIONS_FS_UNORDERED_MAP(K, V, S, N)
