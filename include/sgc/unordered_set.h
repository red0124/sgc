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

#define _SGC_INIT_PP_UNORDERED_SET(KV, N)                                      \
    static void _p_##N##_bucket_free_nodes(const N* const u,                   \
                                           struct _p_##N##_node* bucket);      \
    static void _p_##N##_bucket_insert(struct _p_##N##_node* bucket,           \
                                       struct _p_##N##_node* new_node);        \
    static size_t _p_##N##_bucket_node_size(struct _p_##N##_node* bucket);     \
    static struct _p_##N##_node*                                               \
        _p_##N##_bucket_remove(N* u, struct _p_##N##_node* bucket,             \
                               const KV* const key);                           \
    static struct _p_##N##_node* _p_##N##_bucket_end(                          \
        struct _p_##N##_node* bucket);                                         \
    static struct N##_it _p_##N##_find_by_hash(N* u, const KV* const v,        \
                                               size_t hash);                   \
    static void _p_##N##_rehash_size(const N* const u, size_t* max,            \
                                     size_t* new_max);                         \
    static bool _p_##N##_resize(N* u);                                         \
    static void _p_##N##_copy_base_data(N* __restrict__ dst,                   \
                                        const N* __restrict__ const src);      \
    static void _p_##N##_copy_nodes(N* __restrict__ dst,                       \
                                    const N* __restrict__ const src);          \
    static void _p_##N##_node_free(const N* const m, struct _p_##N##_node* n); \
    static void                                                                \
        _p_##N##_node_copy_values(const N* const m, struct _p_##N##_node* dst, \
                                  const struct _p_##N##_node* const src);      \
    static size_t _p_##N##_node_hash_value(                                    \
        const struct _p_##N##_node* const n);                                  \
    static bool _p_##N##_node_eq_key(const struct _p_##N##_node* const n,      \
                                     const KV* const key);                     \
    struct _p_##N##_node* _p_##N##_node_new(const KV* const value, bool shared);

#define SGC_INIT_HEADERS_UNORDERED_SET(KV, N)                                  \
    struct _p_##N##_node {                                                     \
        KV value_;                                                             \
        struct _p_##N##_node* next_;                                           \
    };                                                                         \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t max_;                                                           \
        bool sharing_;                                                         \
        struct _p_##N##_node** data_;                                          \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef KV N##_type;                                                       \
    typedef KV N##_value;                                                      \
                                                                               \
    size_t N##_bucket_count(const N* const u);                                 \
    size_t N##_bucket_size(const N* const u, size_t n);                        \
    size_t N##_buckets_used(const N* const u);                                 \
                                                                               \
    struct N##_it {                                                            \
        size_t curr_bucket_;                                                   \
        size_t max_;                                                           \
        bool valid_;                                                           \
        struct _p_##N##_node** data_;                                          \
        struct _p_##N##_node* curr_;                                           \
    };                                                                         \
                                                                               \
    typedef struct N##_it N##_it;                                              \
    _SGC_INIT_BD_IT_PROTOTIPES(N)                                              \
    void N##_set_sharing(N* u);                                                \
    void N##_set_owning(N* u);                                                 \
    size_t N##_size(const N* const u);                                         \
    void N##_init(N* u);                                                       \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src);       \
    void N##_free(N* u);                                                       \
    struct N##_it N##_find(N* u, const KV v);                                  \
    void N##_rehash(N* u, size_t new_max);                                     \
    void N##_insert(N* u, const KV v);                                         \
    void N##_erase(N* u, const KV v);                                          \
    void N##_erase_it(N* u, struct N##_it* i);                                 \
    bool N##_empty(const N* const u);

#define _SGC_INIT_UNIQUE_UNORDERED_SET(KV, N)                                  \
    struct _p_##N##_node* _p_##N##_node_new(const KV* const value,             \
                                            bool shared) {                     \
        struct _p_##N##_node* new_node =                                       \
            (struct _p_##N##_node*)sgc_malloc(sizeof(struct _p_##N##_node));   \
        if (!new_node) {                                                       \
            return NULL;                                                       \
        }                                                                      \
        _SGC_COPY(KV, new_node->value_, *value, shared);                       \
        new_node->next_ = NULL;                                                \
        return new_node;                                                       \
    }                                                                          \
                                                                               \
    void N##_init(N* u) {                                                      \
        u->size_ = u->max_ = 0;                                                \
        u->data_ = NULL;                                                       \
        u->sharing_ = 0;                                                       \
    }                                                                          \
                                                                               \
    void N##_free(N* u) {                                                      \
        if (u->size_) {                                                        \
            for (size_t i = 0; i < u->max_; ++i) {                             \
                _p_##N##_bucket_free_nodes(u, u->data_[i]);                    \
            }                                                                  \
        }                                                                      \
        if (u->data_) {                                                        \
            sgc_free(u->data_);                                                \
        }                                                                      \
    }                                                                          \
                                                                               \
    static N##_it _p_##N##_find_by_hash(N* u, const KV* const v,               \
                                        size_t hash) {                         \
        N##_it it;                                                             \
        it.valid_ = false;                                                     \
        if (u->max_) {                                                         \
            size_t position = hash % u->max_;                                  \
            struct _p_##N##_node* tmp = u->data_[position];                    \
            while (tmp) {                                                      \
                if (KV##_eq(&tmp->value_, v)) {                                \
                    it.valid_ = true;                                          \
                    it.data_ = u->data_;                                       \
                    it.curr_ = tmp;                                            \
                    it.curr_bucket_ = position;                                \
                    it.max_ = u->max_;                                         \
                    break;                                                     \
                }                                                              \
                tmp = tmp->next_;                                              \
            }                                                                  \
        }                                                                      \
        return it;                                                             \
    }                                                                          \
                                                                               \
    N##_it N##_find(N* u, const KV v) {                                        \
        size_t hash = KV##_hash(&v);                                           \
        return _p_##N##_find_by_hash(u, &v, hash);                             \
    }                                                                          \
                                                                               \
    void N##_insert(N* u, const KV v) {                                        \
        size_t hash = KV##_hash(&v);                                           \
        N##_it i = _p_##N##_find_by_hash(u, &v, hash);                         \
        if (!i.valid_) {                                                       \
            if (!_p_##N##_resize(u)) {                                         \
                return;                                                        \
            }                                                                  \
            struct _p_##N##_node* new_node =                                   \
                _p_##N##_node_new(&v, u->sharing_);                            \
            if (!new_node) {                                                   \
                return;                                                        \
            }                                                                  \
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
    void N##_erase_it(N* u, N##_it* i) {                                       \
        if (N##_it_valid(i)) {                                                 \
            KV value = i->curr_->value_;                                       \
            N##_it_go_next(i);                                                 \
            N##_erase(u, value);                                               \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void _p_##N##_copy_base_data(N* __restrict__ dst,                   \
                                        const N* __restrict__ const src) {     \
        dst->size_ = src->size_;                                               \
        dst->max_ = src->max_;                                                 \
        dst->sharing_ = src->sharing_;                                         \
    }

#define SGC_INIT_DEFINITIONS_UNORDERED_SET(KV, N)                              \
    _SGC_INIT_PP_UNORDERED_SET(KV, N)                                          \
    _SGC_INIT_UNIQUE_UNORDERED_SET(KV, N)                                      \
    _SGC_INIT_COMMON_DICT_NONE_PAIR_HASH(KV, N)                                \
    _SGC_INIT_COMMON_HASH_MAP(KV, N)                                           \
    _SGC_INIT_IT_CBEGIN_CEND(N)                                                \
    _SGC_INIT_COMMON(N)

#define SGC_INIT_UNORDERED_SET(KV, N)                                          \
    SGC_INIT_HEADERS_UNORDERED_SET(KV, N)                                      \
    SGC_INIT_DEFINITIONS_UNORDERED_SET(KV, N)
