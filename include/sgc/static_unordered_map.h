#pragma once

#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_hash_node_state.h"
#include "detail/sgc_static_hash_map_common.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define SGC_INIT_STATIC_FUNCTIONS_STATIC_UNORDERED_MAP(K, V, S, N)             \
    static struct N##_iterator N##_find_by_hash(struct N* u, const K* const k, \
                                                size_t hash);

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
        size_t curr_;                                                          \
        struct N##_node* data_;                                                \
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
    const struct N##_pair* N##_iterator_cdata(struct N##_iterator i) {         \
        return &i.data_[i.curr_].data_;                                        \
    }                                                                          \
                                                                               \
    struct N##_pair* N##_iterator_data(struct N##_iterator i) {                \
        return &i.data_[i.curr_].data_;                                        \
    }                                                                          \
                                                                               \
    void N##_iterator_next(struct N##_iterator* i) {                           \
        size_t curr = i->curr_;                                                \
        while (i->curr_ < S - 1 &&                                             \
               i->data_[i->curr_ + 1]._state != SGC_NODE_STATE_USED) {         \
            ++i->curr_;                                                        \
        }                                                                      \
        ++i->curr_;                                                            \
        if (i->curr_ == S) {                                                   \
            i->curr_ = curr;                                                   \
            i->is_valid_ = 0;                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_iterator_begin(struct N* m, struct N##_iterator* i) {             \
        i->curr_ = 0;                                                          \
        i->data_ = (struct N##_node*)(m->data_);                               \
        if (i->data_[i->curr_]._state != SGC_NODE_STATE_USED) {                \
            N##_iterator_next(i);                                              \
        }                                                                      \
        i->is_valid_ =                                                         \
            (i->data_[i->curr_]._state != SGC_NODE_STATE_USED) ? 0 : 1;        \
    }                                                                          \
                                                                               \
    void N##_iterator_cbegin(const struct N* const m,                          \
                             struct N##_iterator* i) {                         \
        i->curr_ = 0;                                                          \
        i->data_ = (struct N##_node*)(m->data_);                               \
        if (i->data_[i->curr_]._state != SGC_NODE_STATE_USED) {                \
            N##_iterator_next(i);                                              \
        }                                                                      \
        i->is_valid_ =                                                         \
            (i->data_[i->curr_]._state != SGC_NODE_STATE_USED) ? 0 : 1;        \
    }                                                                          \
                                                                               \
    void N##_iterator_prev(struct N##_iterator* i) {                           \
        size_t curr = i->curr_;                                                \
        while (i->curr_ > 1 &&                                                 \
               i->data_[i->curr_ - 1]._state != SGC_NODE_STATE_USED) {         \
            --i->curr_;                                                        \
        }                                                                      \
        --i->curr_;                                                            \
        if (i->curr_ == 0 &&                                                   \
            i->data_[i->curr_]._state != SGC_NODE_STATE_USED) {                \
            i->curr_ = curr;                                                   \
            i->is_valid_ = 0;                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_iterator_end(struct N* m, struct N##_iterator* i) {               \
        i->curr_ = S - 1;                                                      \
        i->data_ = (struct N##_node*)(m->data_);                               \
        if (i->data_[i->curr_]._state != SGC_NODE_STATE_USED) {                \
            N##_iterator_prev(i);                                              \
        }                                                                      \
        i->is_valid_ =                                                         \
            (i->data_[i->curr_]._state != SGC_NODE_STATE_USED) ? 0 : 1;        \
    }                                                                          \
                                                                               \
    void N##_iterator_cend(const struct N* const m, struct N##_iterator* i) {  \
        i->curr_ = S - 1;                                                      \
        i->data_ = (struct N##_node*)(m->data_);                               \
        if (i->data_[i->curr_]._state != SGC_NODE_STATE_USED) {                \
            N##_iterator_prev(i);                                              \
        }                                                                      \
        i->is_valid_ =                                                         \
            (i->data_[i->curr_]._state != SGC_NODE_STATE_USED) ? 0 : 1;        \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_begin(struct N* m) {                               \
        struct N##_iterator i;                                                 \
        N##_iterator_begin(m, &i);                                             \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_cbegin(const struct N* const m) {                  \
        struct N##_iterator i;                                                 \
        N##_iterator_cbegin(m, &i);                                            \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_end(struct N* m) {                                 \
        struct N##_iterator i;                                                 \
        N##_iterator_end(m, &i);                                               \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_cend(const struct N* const m) {                    \
        struct N##_iterator i;                                                 \
        N##_iterator_cend(m, &i);                                              \
        return i;                                                              \
    }                                                                          \
                                                                               \
    bool N##_iterator_equal(const struct N##_iterator first,                   \
                            const struct N##_iterator second) {                \
        return first.curr_ == second.curr_;                                    \
    }                                                                          \
                                                                               \
    bool N##_iterator_valid(const struct N##_iterator i) {                     \
        return i.is_valid_;                                                    \
    }                                                                          \
                                                                               \
    void N##_set_share_key(N* u, int is_shared) {                              \
        u->shared_key_ = is_shared;                                            \
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
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src) {      \
        dst->size_ = src->size_;                                               \
        dst->shared_ = src->shared_;                                           \
        dst->shared_key_ = src->shared_key_;                                   \
        for (size_t i = 0; i < S; ++i) {                                       \
            if (src->data_[i]._state == SGC_NODE_STATE_USED) {                 \
                SGC_COPY(K##_copy, dst->data_[i].data_.key,                    \
                         src->data_[i].data_.key, src->shared_key_);           \
                SGC_COPY(V##_copy, dst->data_[i].data_.value,                  \
                         src->data_[i].data_.value, src->shared_);             \
            }                                                                  \
            dst->data_[i]._state = src->data_[i]._state;                       \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_free(struct N* u) {                                               \
        if (u->size_) {                                                        \
            for (size_t i = 0; i < S; ++i) {                                   \
                if (u->data_[i]._state == SGC_NODE_STATE_USED) {               \
                    if (!u->shared_key_) {                                     \
                        K##_free(&u->data_[i].data_.key);                      \
                    }                                                          \
                    if (!u->shared_) {                                         \
                        V##_free(&u->data_[i].data_.value);                    \
                    }                                                          \
                }                                                              \
            }                                                                  \
            u->size_ = 0;                                                      \
        }                                                                      \
    }                                                                          \
                                                                               \
    static struct N##_iterator N##_find_by_hash(struct N* u, const K* const k, \
                                                size_t hash) {                 \
        struct N##_iterator ret = {0, NULL, 0};                                \
        if (u->size_) {                                                        \
            size_t position = hash % S;                                        \
            while (u->data_[position]._state != SGC_NODE_STATE_OPEN) {         \
                if (u->data_[position]._state == SGC_NODE_STATE_USED &&        \
                    K##_equal(&u->data_[position].data_.key, k)) {             \
                    ret =                                                      \
                        (struct N##_iterator){position,                        \
                                              (struct N##_node*)u->data_, 1};  \
                    break;                                                     \
                }                                                              \
                if (position == S - 1) {                                       \
                    position = 0;                                              \
                } else {                                                       \
                    ++position;                                                \
                }                                                              \
            }                                                                  \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_find(struct N* u, const K k) {                     \
        size_t hash = K##_hash(&k);                                            \
        return N##_find_by_hash(u, &k, hash);                                  \
    }                                                                          \
                                                                               \
    void N##_set_at(struct N* u, const K k, const V v) {                       \
        size_t hash = K##_hash(&k);                                            \
        struct N##_iterator i = N##_find_by_hash(u, &k, hash);                 \
        if (i.is_valid_) {                                                     \
            SGC_REPLACE(V##_copy, V##_free, i.data_[i.curr_].data_.value, v,   \
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
        struct N##_iterator i = N##_find_by_hash(u, &k, hash);                 \
        V* ret = NULL;                                                         \
        if (i.is_valid_) {                                                     \
            ret = &i.data_[i.curr_].data_.value;                               \
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
    void N##_iterator_erase(struct N* u, struct N##_iterator* i) {             \
        if (N##_iterator_valid(*i)) {                                          \
            K* key = &N##_iterator_data(*i)->key;                              \
            V* value = &N##_iterator_data(*i)->value;                          \
            i->data_[i->curr_]._state = SGC_NODE_STATE_ERASED;                 \
            N##_iterator_next(i);                                              \
            if (!u->shared_key_) {                                             \
                K##_free(key);                                                 \
            }                                                                  \
            if (!u->shared_) {                                                 \
                V##_free(value);                                               \
            }                                                                  \
            --u->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_erase(struct N* u, const K k) {                                   \
        struct N##_iterator i = N##_find(u, k);                                \
        if (i.is_valid_) {                                                     \
            N##_iterator_erase(u, &i);                                         \
        }                                                                      \
    }

#define SGC_INIT_STATIC_UNORDERED_MAP(K, V, S, N)                              \
    SGC_INIT_HEADERS_STATIC_UNORDERED_MAP(K, V, S, N)                          \
    SGC_INIT_STATIC_FUNCTIONS_STATIC_UNORDERED_MAP(K, V, S, N)                 \
    _SGC_INIT_UNIQUE_STATIC_UNORDERED_MAP_FUNCTIONS(K, V, S, N)                \
    _SGC_INIT_STATIC_HASH_MAP_TYPE_FUNCTIONS(K, S, N)                          \
    _SGC_INIT_COMMON_FUNCTIONS(N)
