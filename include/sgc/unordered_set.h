#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_dictionary_ocmmon.h"
#include "detail/sgc_hash_map_common.h"
#include "detail/sgc_iterator.h"
#include "detail/sgc_prime.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define _SGC_INIT_PP_UNORDERED_SET(KV, N)                                      \
    static void _p_##N##_bucket_sgc_free(const struct N* const u,              \
                                         struct N##_node* bucket);             \
    static void _p_##N##_bucket_insert(struct N##_node* bucket,                \
                                       struct N##_node* new_node);             \
    static size_t _p_##N##_bucket_node_size(struct N##_node* bucket);          \
    static struct N##_node* _p_##N##_bucket_remove(struct N* u,                \
                                                   struct N##_node* bucket,    \
                                                   const KV* const key);       \
    static struct N##_node* _p_##N##_bucket_end(struct N##_node* bucket);      \
    static struct N##_it _p_##N##_find_by_hash(struct N* u, const KV* const v, \
                                               size_t hash);                   \
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
    static size_t _p_##N##_node_hash_value(const struct N##_node* const n);    \
    static bool _p_##N##_node_equal_key(const struct N##_node* const n,        \
                                        const KV* const key);

#define SGC_INIT_HEADERS_UNORDERED_SET(KV, N)                                  \
    struct N##_node {                                                          \
        KV value_;                                                             \
        struct N##_node* next_;                                                \
    };                                                                         \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t max_;                                                           \
        bool shared_;                                                          \
        struct N##_node** data_;                                               \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef KV N##_type;                                                       \
                                                                               \
    struct N##_node* _p_##N##_node_new(const KV* const value, bool shared);    \
    size_t N##_bucket_count(const struct N* const u);                          \
    size_t N##_bucket_size(const struct N* const u, size_t n);                 \
    size_t N##_buckets_used(const struct N* const u);                          \
                                                                               \
    struct N##_it {                                                            \
        struct N##_node** data_;                                               \
        struct N##_node* curr_;                                                \
        size_t curr_bucket_;                                                   \
        size_t max_;                                                           \
        bool valid_;                                                           \
    };                                                                         \
                                                                               \
    typedef struct N##_it N##_it;                                              \
    _SGC_INIT_BD_IT_PROTOTIPES(N)                                              \
    void N##_set_share(N* u, bool shared);                                     \
    size_t N##_size(const struct N* const u);                                  \
    void N##_init(struct N* u);                                                \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src);       \
    void N##_free(struct N* u);                                                \
    struct N##_it N##_find(struct N* u, const KV v);                           \
    void N##_rehash(struct N* u, size_t new_max);                              \
    void N##_insert(struct N* u, const KV v);                                  \
    void N##_insert_multiple(struct N* u, const KV v);                         \
    void N##_erase(struct N* u, const KV v);                                   \
    void N##_it_erase(struct N* u, struct N##_it* i);                          \
    bool N##_empty(const struct N* const u);

#define _SGC_INIT_UNIQUE_UNORDERED_SET(KV, N)                                  \
    struct N##_node* _p_##N##_node_new(const KV* const value, bool shared) {   \
        struct N##_node* new_node =                                            \
            (struct N##_node*)sgc_malloc(sizeof(struct N##_node));             \
        SGC_COPY(KV##_copy, new_node->value_, *value, shared);                 \
        new_node->next_ = NULL;                                                \
        return new_node;                                                       \
    }                                                                          \
                                                                               \
    void N##_init(struct N* u) {                                               \
        u->size_ = u->max_ = 0;                                                \
        u->data_ = NULL;                                                       \
        u->shared_ = 0;                                                        \
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
    static struct N##_it _p_##N##_find_by_hash(struct N* u, const KV* const v, \
                                               size_t hash) {                  \
        struct N##_it ret = {NULL, NULL, 0, 0, 0};                             \
        if (u->max_) {                                                         \
            size_t position = hash % u->max_;                                  \
            struct N##_node* tmp = u->data_[position];                         \
            while (tmp) {                                                      \
                if (KV##_equal(&tmp->value_, v)) {                             \
                    ret =                                                      \
                        (struct N##_it){u->data_, tmp, position, u->max_, 1};  \
                }                                                              \
                tmp = tmp->next_;                                              \
            }                                                                  \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    struct N##_it N##_find(struct N* u, const KV v) {                          \
        size_t hash = KV##_hash(&v);                                           \
        return _p_##N##_find_by_hash(u, &v, hash);                             \
    }                                                                          \
                                                                               \
    void N##_insert(struct N* u, const KV v) {                                 \
        size_t hash = KV##_hash(&v);                                           \
        struct N##_it i = _p_##N##_find_by_hash(u, &v, hash);                  \
        if (!i.curr_) {                                                        \
            _p_##N##_resize(u);                                                \
            struct N##_node* new_node = _p_##N##_node_new(&v, u->shared_);     \
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
    void N##_insert_multiple(struct N* u, const KV v) {                        \
        _p_##N##_resize(u);                                                    \
        struct N##_node* new_node = _p_##N##_node_new(&v, u->shared_);         \
        size_t hash = KV##_hash(&v);                                           \
        size_t position = hash % u->max_;                                      \
        if (u->data_[position]) {                                              \
            _p_##N##_bucket_insert(u->data_[position], new_node);              \
        } else {                                                               \
            u->data_[position] = new_node;                                     \
        }                                                                      \
        ++u->size_;                                                            \
    }                                                                          \
                                                                               \
    void N##_it_erase(struct N* u, struct N##_it* i) {                         \
        if (N##_it_valid(*i)) {                                                \
            KV value = i->curr_->value_;                                       \
            N##_it_go_next(i);                                                 \
            N##_erase(u, value);                                               \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void                                                                \
        _p_##N##_copy_base_data(struct N* __restrict__ dst,                    \
                                const struct N* __restrict__ const src) {      \
        dst->size_ = src->size_;                                               \
        dst->max_ = src->max_;                                                 \
        dst->shared_ = src->shared_;                                           \
    }

#define SGC_INIT_UNORDERED_SET(KV, N)                                          \
    SGC_INIT_HEADERS_UNORDERED_SET(KV, N)                                      \
    _SGC_INIT_PP_UNORDERED_SET(KV, N)                                          \
    _SGC_INIT_UNIQUE_UNORDERED_SET(KV, N)                                      \
    _SGC_INIT_COMMON_DICT_NONE_PAIR(KV, N)                                     \
    _SGC_INIT_COMMON_HASH_MAP(KV, N)                                           \
    _SGC_INIT_COMMON(N)
