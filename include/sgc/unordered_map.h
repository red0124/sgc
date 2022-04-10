#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_common.h"
#include "detail/sgc_dictionary_common.h"
#include "detail/sgc_hash_map_common.h"
#include "detail/sgc_iterator.h"
#include "detail/sgc_prime.h"
#include "detail/sgc_primitive_types.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define _SGC_INIT_PP_UNORDERED_MAP(K, V, N)                                    \
    static void _p_##N##_bucket_sgc_free(const N* const u,                     \
                                         struct _p_##N##_node* bucket);        \
    static void _p_##N##_bucket_insert(struct _p_##N##_node* bucket,           \
                                       struct _p_##N##_node* new_node);        \
    static size_t _p_##N##_bucket_node_size(struct _p_##N##_node* bucket);     \
    static struct _p_##N##_node*                                               \
        _p_##N##_bucket_remove(N* u, struct _p_##N##_node* bucket,             \
                               const K* const key);                            \
    static struct _p_##N##_node* _p_##N##_bucket_end(                          \
        struct _p_##N##_node* bucket);                                         \
    static struct N##_it _p_##N##_find_by_hash(N* u, const K* const k,         \
                                               size_t hash);                   \
    static void _p_##N##_rehash_size(const N* const u, size_t* max,            \
                                     size_t* new_max);                         \
    static void _p_##N##_resize(N* u);                                         \
    static void _p_##N##_copy_base_data(N* __restrict__ dst,                   \
                                        const N* __restrict__ const src);      \
    static void _p_##N##_copy_nodes(N* __restrict__ dst,                       \
                                    const N* __restrict__ const src);          \
    static void _p_##N##_node_free(const N* const m, struct _p_##N##_node* n); \
    static void                                                                \
        _p_##N##_node_copy_values(const N* const m, struct _p_##N##_node* dst, \
                                  const struct _p_##N##_node* const src);      \
    static size_t _p_##N##_node_hash_value(const struct _p_##N##_node* n);     \
    static bool _p_##N##_node_eq_key(const struct _p_##N##_node* const n,      \
                                     const K* const key);

#define SGC_INIT_HEADERS_UNORDERED_MAP(K, V, N)                                \
                                                                               \
    struct N##_pair {                                                          \
        K key;                                                                 \
        V value;                                                               \
    };                                                                         \
                                                                               \
    struct _p_##N##_node {                                                     \
        struct N##_pair data_;                                                 \
        struct _p_##N##_node* next_;                                           \
    };                                                                         \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t max_;                                                           \
        bool sharing_;                                                         \
        bool sharing_key_;                                                     \
        struct _p_##N##_node** data_;                                          \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef struct N##_pair N##_pair;                                          \
    typedef struct N##_pair N##_type;                                          \
    typedef V N##_value;                                                       \
    typedef K N##_key;                                                         \
                                                                               \
    struct _p_##N##_node* _p_##N##_node_new(const K* key,                      \
                                            const V* const value,              \
                                            bool sharing_key, bool shared);    \
    size_t N##_bucket_count(const N* const u);                                 \
    size_t N##_bucket_size(const N* const u, size_t n);                        \
    size_t N##_buckets_used(const N* const u);                                 \
                                                                               \
    struct N##_it {                                                            \
        struct _p_##N##_node** data_;                                          \
        struct _p_##N##_node* curr_;                                           \
        size_t curr_bucket_;                                                   \
        size_t max_;                                                           \
        bool valid_;                                                           \
    };                                                                         \
                                                                               \
    typedef struct N##_it N##_it;                                              \
    _SGC_INIT_BD_IT_PROTOTIPES(N)                                              \
                                                                               \
    void N##_set_shareing(N* u);                                               \
    void N##_set_owning(N* u);                                                 \
    void N##_set_shareing_key(N* u);                                           \
    void N##_set_owning_key(N* u);                                             \
    size_t N##_size(const N* const u);                                         \
    void N##_init(N* u);                                                       \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src);       \
    void N##_free(N* u);                                                       \
    struct N##_it N##_find(N* u, const K k);                                   \
    void N##_rehash(N* u, size_t new_max);                                     \
    void N##_set(N* u, const K k, const V v);                                  \
    V* N##_at(N* u, K k);                                                      \
    void N##_erase(N* u, const K k);                                           \
    void N##_it_erase(N* u, struct N##_it* i);                                 \
    bool N##_empty(const N* const u);

#define _SGC_INIT_UNIQUE_UNORDERED_MAP(K, V, N)                                \
    struct _p_##N##_node* _p_##N##_node_new(const K* key,                      \
                                            const V* const value,              \
                                            bool sharing_key, bool shared) {   \
        struct _p_##N##_node* new_node =                                       \
            (struct _p_##N##_node*)sgc_malloc(sizeof(struct _p_##N##_node));   \
        SGC_COPY(K##_copy, new_node->data_.key, *key, sharing_key);            \
        SGC_COPY(V##_copy, new_node->data_.value, *value, shared);             \
        new_node->next_ = NULL;                                                \
        return new_node;                                                       \
    }                                                                          \
                                                                               \
    void N##_init(N* u) {                                                      \
        u->sharing_ = u->sharing_key_ = false;                                 \
        u->size_ = u->max_ = 0;                                                \
        u->data_ = NULL;                                                       \
    }                                                                          \
                                                                               \
    void N##_free(N* u) {                                                      \
        if (u->size_) {                                                        \
            for (size_t i = 0; i < u->max_; ++i) {                             \
                _p_##N##_bucket_sgc_free(u, u->data_[i]);                      \
            }                                                                  \
        }                                                                      \
        if (u->data_) {                                                        \
            sgc_free(u->data_);                                                \
        }                                                                      \
    }                                                                          \
                                                                               \
    static N##_it _p_##N##_find_by_hash(N* u, const K* const k, size_t hash) { \
        N##_it ret = {NULL, NULL, 0, 0, false};                                \
        if (u->max_) {                                                         \
            size_t position = hash % u->max_;                                  \
            struct _p_##N##_node* tmp = u->data_[position];                    \
            while (tmp) {                                                      \
                if (K##_eq(&tmp->data_.key, k)) {                              \
                    ret = (N##_it){u->data_, tmp, position, u->max_, 1};       \
                    break;                                                     \
                }                                                              \
                tmp = tmp->next_;                                              \
            }                                                                  \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    N##_it N##_find(N* u, const K k) {                                         \
        size_t hash = K##_hash(&k);                                            \
        return _p_##N##_find_by_hash(u, &k, hash);                             \
    }                                                                          \
                                                                               \
    void N##_set(N* u, const K k, const V v) {                                 \
        size_t hash = K##_hash(&k);                                            \
        N##_it i = _p_##N##_find_by_hash(u, &k, hash);                         \
        if (i.valid_) {                                                        \
            SGC_REPLACE(V##_copy, V##_free, i.curr_->data_.value, v,           \
                        u->sharing_);                                          \
        } else {                                                               \
            _p_##N##_resize(u);                                                \
            struct _p_##N##_node* new_node =                                   \
                _p_##N##_node_new(&k, &v, u->sharing_key_, u->sharing_);       \
            size_t position = hash % u->max_;                                  \
            if (u->data_[position]) {                                          \
                _p_##N##_bucket_insert(u->data_[position], new_node);          \
            } else {                                                           \
                u->data_[position] = new_node;                                 \
            }                                                                  \
            ++u->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    V* N##_at(N* u, K k) {                                                     \
        size_t hash = K##_hash(&k);                                            \
        N##_it i = _p_##N##_find_by_hash(u, &k, hash);                         \
        V* ret;                                                                \
        if (i.curr_) {                                                         \
            ret = &i.curr_->data_.value;                                       \
        } else {                                                               \
            V v;                                                               \
            _p_##N##_resize(u);                                                \
            V##_init(&v);                                                      \
            struct _p_##N##_node* new_node =                                   \
                _p_##N##_node_new(&k, &v, u->sharing_key_, u->sharing_);       \
            size_t position = hash % u->max_;                                  \
            if (u->data_[position]) {                                          \
                _p_##N##_bucket_insert(u->data_[position], new_node);          \
            } else {                                                           \
                u->data_[position] = new_node;                                 \
            }                                                                  \
            ++u->size_;                                                        \
            ret = &new_node->data_.value;                                      \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_it_erase(N* u, N##_it* i) {                                       \
        if (N##_it_valid(*i)) {                                                \
            K key = i->curr_->data_.key;                                       \
            N##_it_go_next(i);                                                 \
            N##_erase(u, key);                                                 \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void _p_##N##_copy_base_data(N* __restrict__ dst,                   \
                                        const N* __restrict__ const src) {     \
        dst->size_ = src->size_;                                               \
        dst->max_ = src->max_;                                                 \
        dst->sharing_key_ = src->sharing_key_;                                 \
        dst->sharing_ = src->sharing_;                                         \
    }

#define SGC_INIT_UNORDERED_MAP(K, V, N)                                        \
    SGC_INIT_HEADERS_UNORDERED_MAP(K, V, N)                                    \
    _SGC_INIT_PP_UNORDERED_MAP(K, V, N)                                        \
    _SGC_INIT_UNIQUE_UNORDERED_MAP(K, V, N)                                    \
    _SGC_INIT_COMMON_DICT_PAIR_HASH(K, V, N)                                \
    _SGC_INIT_COMMON_HASH_MAP(K, N)                                            \
    _SGC_INIT_COMMON(N)
