#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_dictionary_ocmmon.h"
#include "detail/sgc_hash_map_common.h"
#include "detail/sgc_prime.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define _SGC_INIT_PP_UNORDERED_MAP(K, V, N)                       \
    static void _p_##N##_bucket_sgc_free(const struct N* const u,              \
                                         struct N##_node* bucket);             \
    static void _p_##N##_bucket_insert(struct N##_node* bucket,                \
                                       struct N##_node* new_node);             \
    static size_t _p_##N##_bucket_node_size(struct N##_node* bucket);          \
    static struct N##_node* _p_##N##_bucket_remove(struct N* u,                \
                                                   struct N##_node* bucket,    \
                                                   const K* const key);        \
    static struct N##_node* _p_##N##_bucket_end(struct N##_node* bucket);      \
    static struct N##_it _p_##N##_find_by_hash(struct N* u,              \
                                                     const K* const k,         \
                                                     size_t hash);             \
    static void _p_##N##_rehash_size(const struct N* const u, size_t* max,     \
                                     size_t* new_max);                         \
    static void _p_##N##_resize(struct N* u);                                  \
    static void                                                                \
        _p_##N##_copy_base_data(struct N* __restrict__ dst,                    \
                                const struct N* __restrict__ const src);       \
    static void _p_##N##_copy_nodes(struct N* __restrict__ dst,                \
                                    const struct N* __restrict__ const src);   \
    static void _p_##N##_node_free(const struct N* const m,                    \
                                   struct N##_node* n);                        \
    static void _p_##N##_node_copy_values(const struct N* const m,             \
                                          struct N##_node* dst,                \
                                          const struct N##_node* const src);   \
    static size_t _p_##N##_node_hash_value(const struct N##_node* n);          \
    static bool _p_##N##_node_equal_key(const struct N##_node* const n,        \
                                        const K* const key);

#define SGC_INIT_HEADERS_UNORDERED_MAP(K, V, N)                                \
                                                                               \
    struct N##_pair {                                                          \
        K key;                                                                 \
        V value;                                                               \
    };                                                                         \
                                                                               \
    struct N##_node {                                                          \
        struct N##_pair data_;                                                 \
        struct N##_node* next_;                                                \
    };                                                                         \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t max_;                                                           \
        size_t shared_;                                                        \
        size_t shared_key_;                                                    \
        struct N##_node** data_;                                               \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef struct N##_pair N##_type;                                          \
    typedef V N##_value;                                                       \
    typedef K N##_key;                                                         \
                                                                               \
    struct N##_node* _p_##N##_node_new(const K* key, const V* const value,     \
                                       size_t shared_key,                   \
                                       size_t shared);                      \
    size_t N##_bucket_count(const struct N* const u);                          \
    size_t N##_bucket_size(const struct N* const u, size_t n);                 \
    size_t N##_buckets_used(const struct N* const u);                          \
                                                                               \
    struct N##_it {                                                      \
        struct N##_node** data_;                                               \
        struct N##_node* curr_;                                                \
        size_t curr_bucket_;                                                   \
        size_t max_;                                                           \
        int valid_;                                                         \
    };                                                                         \
                                                                               \
    typedef struct N##_it N##_it;                                  \
                                                                               \
    struct N##_pair* N##_it_data(struct N##_it i);                 \
    const struct N##_pair* N##_it_cdata(struct N##_it i);          \
    void N##_it_go_next(struct N##_it* i);                            \
    void N##_it_begin(struct N* m, struct N##_it* i);              \
    void N##_it_cbegin(const struct N* const m, struct N##_it* i); \
    void N##_it_go_prev(struct N##_it* i);                            \
    void N##_it_end(struct N* m, struct N##_it* i);                \
    void N##_it_cend(const struct N* const m, struct N##_it* i);   \
    struct N##_it N##_begin(struct N* m);                                \
    struct N##_it N##_cbegin(const struct N* const m);                   \
    struct N##_it N##_end(struct N* m);                                  \
    struct N##_it N##_cend(const struct N* const m);                     \
    bool N##_it_equal(const struct N##_it first,                   \
                            const struct N##_it second);                 \
    bool N##_it_valid(const struct N##_it i);                      \
                                                                               \
    void N##_set_share(N* u, int shared);                                   \
    void N##_set_share_key(N* u, int shared_key);                           \
    size_t N##_size(const struct N* const u);                                  \
    void N##_init(struct N* u);                                                \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src);       \
    void N##_free(struct N* u);                                                \
    struct N##_it N##_find(struct N* u, const K k);                      \
    void N##_rehash(struct N* u, size_t new_max);                              \
    void N##_set(struct N* u, const K k, const V v);                        \
    V* N##_at(struct N* u, K k);                                               \
    void N##_erase(struct N* u, const K k);                                    \
    void N##_it_erase(struct N* u, struct N##_it* i);              \
    bool N##_empty(const struct N* const u);

#define _SGC_INIT_UNIQUE_UNORDERED_MAP_FUNCTIONS(K, V, N)                      \
    struct N##_node* _p_##N##_node_new(const K* key, const V* const value,     \
                                       size_t shared_key,                   \
                                       size_t shared) {                     \
        struct N##_node* new_node =                                            \
            (struct N##_node*)sgc_malloc(sizeof(struct N##_node));             \
        SGC_COPY(K##_copy, new_node->data_.key, *key, shared_key);          \
        SGC_COPY(V##_copy, new_node->data_.value, *value, shared);          \
        new_node->next_ = NULL;                                                \
        return new_node;                                                       \
    }                                                                          \
                                                                               \
    void N##_init(struct N* u) {                                               \
        u->size_ = u->max_ = 0;                                                \
        u->data_ = NULL;                                                       \
        u->shared_ = u->shared_key_ = 0;                                       \
    }                                                                          \
                                                                               \
    void N##_free(struct N* u) {                                               \
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
    static struct N##_it _p_##N##_find_by_hash(struct N* u,              \
                                                     const K* const k,         \
                                                     size_t hash) {            \
        struct N##_it ret = {NULL, NULL, 0, 0, 0};                       \
        if (u->max_) {                                                         \
            size_t position = hash % u->max_;                                  \
            struct N##_node* tmp = u->data_[position];                         \
            while (tmp) {                                                      \
                if (K##_equal(&tmp->data_.key, k)) {                           \
                    ret = (struct N##_it){u->data_, tmp, position,       \
                                                u->max_, 1};                   \
                    break;                                                     \
                }                                                              \
                tmp = tmp->next_;                                              \
            }                                                                  \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    struct N##_it N##_find(struct N* u, const K k) {                     \
        size_t hash = K##_hash(&k);                                            \
        return _p_##N##_find_by_hash(u, &k, hash);                             \
    }                                                                          \
                                                                               \
    void N##_set(struct N* u, const K k, const V v) {                       \
        size_t hash = K##_hash(&k);                                            \
        struct N##_it i = _p_##N##_find_by_hash(u, &k, hash);            \
        if (i.curr_) {                                                         \
            SGC_REPLACE(V##_copy, V##_free, i.curr_->data_.value, v, i.curr_); \
        } else {                                                               \
            _p_##N##_resize(u);                                                \
            struct N##_node* new_node =                                        \
                _p_##N##_node_new(&k, &v, u->shared_key_, u->shared_);         \
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
    V* N##_at(struct N* u, K k) {                                              \
        size_t hash = K##_hash(&k);                                            \
        struct N##_it i = _p_##N##_find_by_hash(u, &k, hash);            \
        V* ret;                                                                \
        if (i.curr_) {                                                         \
            ret = &i.curr_->data_.value;                                       \
        } else {                                                               \
            V v;                                                               \
            _p_##N##_resize(u);                                                \
            V##_init(&v);                                                      \
            struct N##_node* new_node =                                        \
                _p_##N##_node_new(&k, &v, u->shared_key_, u->shared_);         \
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
    void N##_it_erase(struct N* u, struct N##_it* i) {             \
        if (N##_it_valid(*i)) {                                          \
            K key = i->curr_->data_.key;                                       \
            N##_it_go_next(i);                                              \
            N##_erase(u, key);                                                 \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void                                                                \
        _p_##N##_copy_base_data(struct N* __restrict__ dst,                    \
                                const struct N* __restrict__ const src) {      \
        dst->size_ = src->size_;                                               \
        dst->max_ = src->max_;                                                 \
        dst->shared_key_ = src->shared_key_;                                   \
        dst->shared_ = src->shared_;                                           \
    }

#define SGC_INIT_UNORDERED_MAP(K, V, N)                                        \
    SGC_INIT_HEADERS_UNORDERED_MAP(K, V, N)                                    \
    _SGC_INIT_PP_UNORDERED_MAP(K, V, N)                           \
    _SGC_INIT_UNIQUE_UNORDERED_MAP_FUNCTIONS(K, V, N)                          \
    _SGC_INIT_COMMON_DICTIONARY_PAIR_FUNCTIONS(K, V, N)                        \
    _SGC_INIT_HASH_MAP_TYPE_FUNCTIONS(K, N)                                    \
    _SGC_INIT_COMMON(N)
