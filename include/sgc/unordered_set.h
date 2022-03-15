#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_hash_map_common.h"
#include "detail/sgc_prime.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define SGC_INIT_STATIC_FUNCTIONS_UNORDERED_SET(V, N)                          \
    static void N##_bucket_sgc_free(const struct N* const u,                   \
                                    struct N##_node* bucket);                  \
    static void N##_bucket_insert(struct N##_node* bucket,                     \
                                  struct N##_node* new_node);                  \
    static size_t N##_bucket_node_size(struct N##_node* bucket);               \
    static struct N##_node* N##_bucket_remove(struct N##_node* bucket,         \
                                              const V* const value,            \
                                              size_t* size, size_t is_shared); \
    static struct N##_node* N##_bucket_end(struct N##_node* bucket);           \
    static struct N##_iterator N##_find_by_hash(struct N* u, const V* const v, \
                                                size_t hash);                  \
    static void N##_rehash_size(const struct N* const u, size_t* max,          \
                                size_t* new_max);                              \
    static void N##_resize(struct N* u);                                       \
    static void N##_copy_base_data(struct N* __restrict__ dst,                 \
                                   const struct N* __restrict__ const src);    \
    static void N##_copy_nodes(struct N* __restrict__ dst,                     \
                               const struct N* __restrict__ const src);        \
    static void N##_node_free(const struct N* const m, struct N##_node* n);    \
    static void N##_node_copy_values(const struct N* const m,                  \
                                     struct N##_node* dst,                     \
                                     const struct N##_node* const src);

#define SGC_INIT_HEADERS_UNORDERED_SET(V, N)                                   \
    struct N##_node {                                                          \
        V _value;                                                              \
        struct N##_node* next_;                                                \
    };                                                                         \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t max_;                                                           \
        size_t shared_;                                                        \
        struct N##_node** data_;                                               \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef V N##_type;                                                        \
                                                                               \
    struct N##_node* N##_node_new(const V* const value, size_t is_shared);     \
    size_t N##_bucket_count(const struct N* const u);                          \
    size_t N##_bucket_size(const struct N* const u, size_t n);                 \
    size_t N##_buckets_used(const struct N* const u);                          \
                                                                               \
    struct N##_iterator {                                                      \
        struct N##_node** data_;                                               \
        struct N##_node* curr_;                                                \
        size_t curr_bucket_;                                                   \
        size_t max_;                                                           \
        int is_valid_;                                                         \
    };                                                                         \
                                                                               \
    typedef struct N##_iterator N##_iterator;                                  \
                                                                               \
    const V* N##_iterator_cdata(struct N##_iterator i);                        \
    V* N##_iterator_data(struct N##_iterator i);                               \
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
    void N##_set_share(N* u, int is_shared);                                   \
    size_t N##_size(const struct N* const u);                                  \
    void N##_init(struct N* u);                                                \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src);       \
    void N##_free(struct N* u);                                                \
    struct N##_iterator N##_find(struct N* u, const V v);                      \
    void N##_rehash(struct N* u, size_t new_max);                              \
    void N##_insert(struct N* u, const V v);                                   \
    void N##_insert_multiple(struct N* u, const V v);                          \
    void N##_erase(struct N* u, const V v);                                    \
    void N##_iterator_erase(struct N* u, struct N##_iterator* i);              \
    bool N##_empty(const struct N* const u);

#define _SGC_INIT_UNIQUE_UNORDERED_SET_FUNCTIONS(V, N)                         \
    V* N##_iterator_data(struct N##_iterator i) {                              \
        return &i.curr_->_value;                                               \
    }                                                                          \
                                                                               \
    const V* N##_iterator_cdata(struct N##_iterator i) {                       \
        return &i.curr_->_value;                                               \
    }                                                                          \
    struct N##_node* N##_node_new(const V* const value, size_t is_shared) {    \
        struct N##_node* new_node =                                            \
            (struct N##_node*)sgc_malloc(sizeof(struct N##_node));             \
        SGC_COPY(V##_copy, new_node->_value, *value, is_shared);               \
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
                N##_bucket_sgc_free(u, u->data_[i]);                           \
            }                                                                  \
        }                                                                      \
        if (u->data_) {                                                        \
            sgc_free(u->data_);                                                \
        }                                                                      \
    }                                                                          \
                                                                               \
    static struct N##_iterator N##_find_by_hash(struct N* u, const V* const v, \
                                                size_t hash) {                 \
        struct N##_iterator ret = {NULL, NULL, 0, 0, 0};                       \
        if (u->max_) {                                                         \
            size_t position = hash % u->max_;                                  \
            struct N##_node* tmp = u->data_[position];                         \
            while (tmp) {                                                      \
                if (V##_equal(&tmp->_value, v)) {                              \
                    ret = (struct N##_iterator){u->data_, tmp, position,       \
                                                u->max_, 1};                   \
                }                                                              \
                tmp = tmp->next_;                                              \
            }                                                                  \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_find(struct N* u, const V v) {                     \
        size_t hash = V##_hash(&v);                                            \
        return N##_find_by_hash(u, &v, hash);                                  \
    }                                                                          \
                                                                               \
    static void N##_rehash_size(const struct N* const u, size_t* max,          \
                                size_t* new_max) {                             \
        *max = u->max_;                                                        \
        if (u->size_ == *max) {                                                \
            *new_max = sgc_next_prime(2 * u->max_ + 1);                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_rehash(struct N* u, size_t new_max) {                             \
        struct N##_node** new_data =                                           \
            (struct N##_node**)sgc_malloc(sizeof(struct N##_node*) * new_max); \
        for (size_t i = 0; i < new_max; ++i) {                                 \
            new_data[i] = NULL;                                                \
        }                                                                      \
                                                                               \
        V* value;                                                              \
        size_t position;                                                       \
        struct N##_iterator tmp = N##_begin(u);                                \
        struct N##_node* next;                                                 \
        for (size_t i = 0; i < u->size_; ++i) {                                \
            value = &tmp.curr_->_value;                                        \
            position = V##_hash(value) % new_max;                              \
            next = tmp.curr_->next_;                                           \
            tmp.curr_->next_ = NULL;                                           \
            if (new_data[position]) {                                          \
                N##_bucket_insert(new_data[position], tmp.curr_);              \
            } else {                                                           \
                new_data[position] = tmp.curr_;                                \
            }                                                                  \
            if (next) {                                                        \
                tmp.curr_ = next;                                              \
            } else {                                                           \
                N##_iterator_next(&tmp);                                       \
            }                                                                  \
        }                                                                      \
        sgc_free(u->data_);                                                    \
        u->data_ = new_data;                                                   \
        u->max_ = new_max;                                                     \
    }                                                                          \
                                                                               \
    static void N##_resize(struct N* u) {                                      \
        size_t max, new_max;                                                   \
        N##_rehash_size(u, &max, &new_max);                                    \
        if (u->size_ == max) {                                                 \
            struct N##_node** new_data = (struct N##_node**)sgc_malloc(        \
                sizeof(struct N##_node*) * new_max);                           \
            for (size_t i = 0; i < new_max; ++i) {                             \
                new_data[i] = NULL;                                            \
            }                                                                  \
                                                                               \
            V* value;                                                          \
            size_t position;                                                   \
            struct N##_iterator tmp = N##_begin(u);                            \
            struct N##_node* next;                                             \
            for (size_t i = 0; i < u->size_; ++i) {                            \
                value = &tmp.curr_->_value;                                    \
                position = V##_hash(value) % new_max;                          \
                next = tmp.curr_->next_;                                       \
                tmp.curr_->next_ = NULL;                                       \
                if (new_data[position]) {                                      \
                    N##_bucket_insert(new_data[position], tmp.curr_);          \
                } else {                                                       \
                    new_data[position] = tmp.curr_;                            \
                }                                                              \
                if (next) {                                                    \
                    tmp.curr_ = next;                                          \
                } else {                                                       \
                    N##_iterator_next(&tmp);                                   \
                }                                                              \
            }                                                                  \
            sgc_free(u->data_);                                                \
            u->data_ = new_data;                                               \
            u->max_ = new_max;                                                 \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_insert(struct N* u, const V v) {                                  \
        size_t hash = V##_hash(&v);                                            \
        struct N##_iterator i = N##_find_by_hash(u, &v, hash);                 \
        if (!i.curr_) {                                                        \
            N##_resize(u);                                                     \
            struct N##_node* new_node = N##_node_new(&v, u->shared_);          \
            size_t position = hash % u->max_;                                  \
            if (u->data_[position]) {                                          \
                N##_bucket_insert(u->data_[position], new_node);               \
            } else {                                                           \
                u->data_[position] = new_node;                                 \
            }                                                                  \
            ++u->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_insert_multiple(struct N* u, const V v) {                         \
        N##_resize(u);                                                         \
        struct N##_node* new_node = N##_node_new(&v, u->shared_);              \
        size_t hash = V##_hash(&v);                                            \
        size_t position = hash % u->max_;                                      \
        if (u->data_[position]) {                                              \
            N##_bucket_insert(u->data_[position], new_node);                   \
        } else {                                                               \
            u->data_[position] = new_node;                                     \
        }                                                                      \
        ++u->size_;                                                            \
    }                                                                          \
                                                                               \
    void N##_erase(struct N* u, const V v) {                                   \
        if (u->data_) {                                                        \
            size_t hash = V##_hash(&v);                                        \
            size_t position = hash % u->max_;                                  \
            u->data_[position] = N##_bucket_remove(u->data_[position], &v,     \
                                                   &u->size_, u->shared_);     \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_iterator_erase(struct N* u, struct N##_iterator* i) {             \
        if (N##_iterator_valid(*i)) {                                          \
            V value = i->curr_->_value;                                        \
            N##_iterator_next(i);                                              \
            N##_erase(u, value);                                               \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void N##_node_copy_values(const struct N* const m,                  \
                                     struct N##_node* dst,                     \
                                     const struct N##_node* const src) {       \
        SGC_COPY(V##_copy, dst->_value, src->_value, m->shared_);              \
    }                                                                          \
                                                                               \
    static void N##_copy_base_data(struct N* __restrict__ dst,                 \
                                   const struct N* __restrict__ const src) {   \
        dst->size_ = src->size_;                                               \
        dst->max_ = src->max_;                                                 \
        dst->shared_ = src->shared_;                                           \
    }                                                                          \
                                                                               \
    static void N##_node_free(const struct N* const m, struct N##_node* n) {   \
        SGC_FREE(V##_free, n->_value, m->shared_);                             \
    }                                                                          \
                                                                               \
    static struct N##_node* N##_bucket_remove(struct N##_node* bucket,         \
                                              const V* const value,            \
                                              size_t* size,                    \
                                              size_t is_shared) {              \
        struct N##_node* ret = bucket;                                         \
        struct N##_node* tmp = bucket;                                         \
        struct N##_node* prev = bucket;                                        \
        while (tmp) {                                                          \
            if (V##_equal(&tmp->_value, value)) {                              \
                if (tmp == bucket) {                                           \
                    ret = tmp->next_;                                          \
                }                                                              \
                prev->next_ = tmp->next_;                                      \
                if (!is_shared) {                                              \
                    V##_free(&tmp->_value);                                    \
                }                                                              \
                sgc_free(tmp);                                                 \
                --*size;                                                       \
                break;                                                         \
            }                                                                  \
            prev = tmp;                                                        \
            tmp = tmp->next_;                                                  \
        }                                                                      \
        return ret;                                                            \
    }

#define SGC_INIT_UNORDERED_SET(V, N)                                           \
    SGC_INIT_HEADERS_UNORDERED_SET(V, N)                                       \
    SGC_INIT_STATIC_FUNCTIONS_UNORDERED_SET(V, N)                              \
    _SGC_INIT_COMMON_FUNCTIONS(V, N)                                           \
    _SGC_INIT_UNIQUE_UNORDERED_SET_FUNCTIONS(V, N)                             \
    _SGC_INIT_HASH_MAP_TYPE_FUNCTIONS(V, N)
