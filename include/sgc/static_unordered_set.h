#pragma once

#include "detail/sgc_basic_types.h"
#include "detail/sgc_hash_node_state.h"
#include "detail/sgc_utils.h"

#define SGC_INIT_STATIC_FUNCTIONS_STATIC_UNORDERED_SET(V, S, N)                \
    static struct N##_iterator N##_find_by_hash(struct N* u, const V* const v, \
                                                size_t hash);

#define SGC_INIT_HEADERS_STATIC_UNORDERED_SET(V, S, N)                         \
    struct N##_node {                                                          \
        V _value;                                                              \
        char _state;                                                           \
    };                                                                         \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t shared_;                                                        \
        struct N##_node data_[S];                                              \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef V N##_type;                                                        \
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
    int N##_iterator_equal(const struct N##_iterator first,                    \
                           const struct N##_iterator second);                  \
    int N##_iterator_valid(const struct N##_iterator i);                       \
                                                                               \
    void N##_set_share(N* u, int is_shared);                                   \
    size_t N##_size(const struct N* const u);                                  \
    void N##_init(struct N* u);                                                \
    int N##_equal(const N* const first, const N* const second);                \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src);       \
    void N##_free(struct N* u);                                                \
    struct N##_iterator N##_find(struct N* u, const V v);                      \
    void N##_insert(struct N* u, const V v);                                   \
    void N##_insert_multiple(struct N* u, const V v);                          \
    void N##_iterator_erase(struct N* u, struct N##_iterator* i);              \
    void N##_erase(struct N* u, const V v);                                    \
    int N##_empty(const struct N* const u);

#define SGC_INIT_STATIC_UNORDERED_SET(V, S, N)                                 \
    SGC_INIT_HEADERS_STATIC_UNORDERED_SET(V, S, N)                             \
    SGC_INIT_STATIC_FUNCTIONS_STATIC_UNORDERED_SET(V, S, N)                    \
                                                                               \
    size_t N##_max(void) {                                                     \
        return S;                                                              \
    }                                                                          \
                                                                               \
    /* ========== */                                                           \
    /*  ITERATOR  */                                                           \
    /* ========== */                                                           \
                                                                               \
    const V* N##_iterator_cdata(struct N##_iterator i) {                       \
        return &i.data_[i.curr_]._value;                                       \
    }                                                                          \
                                                                               \
    V* N##_iterator_data(struct N##_iterator i) {                              \
        return &i.data_[i.curr_]._value;                                       \
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
    int N##_iterator_equal(const struct N##_iterator first,                    \
                           const struct N##_iterator second) {                 \
        return first.curr_ == second.curr_;                                    \
    }                                                                          \
                                                                               \
    int N##_iterator_valid(const struct N##_iterator i) {                      \
        return i.is_valid_;                                                    \
    }                                                                          \
                                                                               \
    /* =============== */                                                      \
    /*  SET FUNCTIONS  */                                                      \
    /* =============== */                                                      \
                                                                               \
    void N##_set_share(N* u, int is_shared) {                                  \
        u->shared_ = is_shared;                                                \
    }                                                                          \
                                                                               \
    size_t N##_size(const struct N* const u) {                                 \
        return u->size_;                                                       \
    }                                                                          \
                                                                               \
    void N##_init(struct N* u) {                                               \
        u->size_ = 0;                                                          \
        u->shared_ = 0;                                                        \
        for (size_t i = 0; i < S; ++i) {                                       \
            u->data_[i]._state = SGC_NODE_STATE_OPEN;                          \
        }                                                                      \
    }                                                                          \
                                                                               \
    int N##_equal(const N* const first, const N* const second) {               \
        int equal = (first == second);                                         \
        if (equal == 0 && first->size_ == second->size_) {                     \
            struct N##_iterator it_first = N##_cbegin(first);                  \
            struct N##_iterator it_second = N##_cbegin(second);                \
            while (N##_iterator_valid(it_first)) {                             \
                if (!V##_equal(N##_iterator_cdata(it_first),                   \
                               N##_iterator_cdata(it_second))) {               \
                    equal = 0;                                                 \
                    break;                                                     \
                }                                                              \
                N##_iterator_next(&it_first);                                  \
                N##_iterator_next(&it_second);                                 \
            }                                                                  \
            equal = 1;                                                         \
        }                                                                      \
        return equal;                                                          \
    }                                                                          \
                                                                               \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src) {      \
        dst->size_ = src->size_;                                               \
        dst->shared_ = src->shared_;                                           \
        for (size_t i = 0; i < S; ++i) {                                       \
            if (src->data_[i]._state == SGC_NODE_STATE_USED) {                 \
                SGC_COPY(V##_copy, dst->data_[i]._value, src->data_[i]._value, \
                         src->shared_);                                        \
            }                                                                  \
            dst->data_[i]._state = src->data_[i]._state;                       \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_free(struct N* u) {                                               \
        if (u->size_) {                                                        \
            for (size_t i = 0; i < S; ++i) {                                   \
                if (u->data_[i]._state == SGC_NODE_STATE_USED) {               \
                    if (!u->shared_) {                                         \
                        V##_free(&u->data_[i]._value);                         \
                    }                                                          \
                }                                                              \
            }                                                                  \
            u->size_ = 0;                                                      \
        }                                                                      \
    }                                                                          \
                                                                               \
    static struct N##_iterator N##_find_by_hash(struct N* u, const V* const v, \
                                                size_t hash) {                 \
        struct N##_iterator ret = {0, NULL, 0};                                \
        if (u->size_) {                                                        \
            size_t position = hash % S;                                        \
            while (u->data_[position]._state != SGC_NODE_STATE_OPEN) {         \
                if (u->data_[position]._state == SGC_NODE_STATE_USED &&        \
                    V##_equal(&u->data_[position]._value, v)) {                \
                    ret =                                                      \
                        (struct N##_iterator){position,                        \
                                              (struct N##_node*)u->data_, 1};  \
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
    struct N##_iterator N##_find(struct N* u, const V v) {                     \
        size_t hash = V##_hash(&v);                                            \
        return N##_find_by_hash(u, &v, hash);                                  \
    }                                                                          \
                                                                               \
    void N##_insert(struct N* u, const V v) {                                  \
        size_t hash = V##_hash(&v);                                            \
        struct N##_iterator i = N##_find_by_hash(u, &v, hash);                 \
        if (!i.is_valid_ && u->size_ < S - 1) {                                \
            size_t position = hash % S;                                        \
            while (u->data_[position]._state == SGC_NODE_STATE_USED) {         \
                if (position == S - 1) {                                       \
                    position = 0;                                              \
                } else {                                                       \
                    ++position;                                                \
                }                                                              \
            }                                                                  \
            SGC_COPY(V##_copy, u->data_[position]._value, v, u->shared_);      \
            u->data_[position]._state = SGC_NODE_STATE_USED;                   \
            ++u->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_insert_multiple(struct N* u, const V v) {                         \
        if (u->size_ < S - 1) {                                                \
            size_t position = V##_hash(&v) % S;                                \
            while (u->data_[position]._state == SGC_NODE_STATE_USED) {         \
                if (position == S - 1) {                                       \
                    position = 0;                                              \
                } else {                                                       \
                    ++position;                                                \
                }                                                              \
            }                                                                  \
            SGC_COPY(V##_copy, u->data_[position]._value, v, u->shared_);      \
            u->data_[position]._state = SGC_NODE_STATE_USED;                   \
            ++u->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_iterator_erase(struct N* u, struct N##_iterator* i) {             \
        (void)(u);                                                             \
        if (N##_iterator_valid(*i)) {                                          \
            V* value = N##_iterator_data(*i);                                  \
            i->data_[i->curr_]._state = SGC_NODE_STATE_ERASED;                 \
            N##_iterator_next(i);                                              \
            if (!u->shared_) {                                                 \
                V##_free(value);                                               \
            }                                                                  \
            --u->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_erase(struct N* u, const V v) {                                   \
        struct N##_iterator i = N##_find(u, v);                                \
        if (i.is_valid_) {                                                     \
            N##_iterator_erase(u, &i);                                         \
        }                                                                      \
    }                                                                          \
                                                                               \
    int N##_empty(const struct N* const u) {                                   \
        return u->size_ == 0;                                                  \
    }
