#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define _SGC_INIT_COMMON_SHASH_MAP(T, S, N)                                    \
    void N##_it_erase(struct N* ds, struct N##_it* it) {                       \
        if (N##_it_valid(*it)) {                                               \
            _p_##N##_node_free(ds, it->curr_);                                 \
            it->curr_->state_ = SGC_NODE_STATE_ERASED;                         \
            N##_it_go_next(it);                                                \
            --ds->size_;                                                       \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_erase(struct N* ds, const T key) {                                \
        struct N##_it it = N##_find(ds, key);                                  \
        if (it.valid_) {                                                       \
            N##_it_erase(ds, &it);                                             \
        }                                                                      \
    }                                                                          \
                                                                               \
    struct N##_it N##_find(struct N* ds, const T key) {                        \
        size_t hash = T##_hash(&key);                                          \
        return _p_##N##_find_by_hash(ds, &key, hash);                          \
    }                                                                          \
                                                                               \
    static struct N##_it _p_##N##_find_by_hash(struct N* ds,                   \
                                               const T* const key,             \
                                               size_t hash) {                  \
        if (ds->size_) {                                                       \
            size_t position = hash % S;                                        \
            struct N##_node* data = ds->data_;                                 \
            while (data[position].state_ != SGC_NODE_STATE_OPEN) {             \
                if (data[position].state_ == SGC_NODE_STATE_USED &&            \
                    _p_##N##_node_equal_key(&data[position], key)) {           \
                    return N##_it_at(ds, position);                            \
                }                                                              \
                if (position == S - 1) {                                       \
                    position = 0;                                              \
                } else {                                                       \
                    ++position;                                                \
                }                                                              \
            }                                                                  \
        }                                                                      \
        struct N##_it it = {NULL, NULL, NULL, 0};                              \
        return it;                                                             \
    }                                                                          \
                                                                               \
    void N##_free(struct N* u) {                                               \
        if (u->size_) {                                                        \
            for (size_t i = 0; i < S; ++i) {                                   \
                if (u->data_[i].state_ == SGC_NODE_STATE_USED) {               \
                    _p_##N##_node_free(u, &u->data_[i]);                       \
                }                                                              \
            }                                                                  \
            u->size_ = 0;                                                      \
        }                                                                      \
    }                                                                          \
                                                                               \
    static struct N##_it N##_it_at(const struct N* const m, size_t at) {       \
        N##_it i;                                                              \
        i.begin_ = (struct N##_node*)(m->data_);                               \
        i.curr_ = i.begin_ + at;                                               \
        i.end_ = i.begin_ + S;                                                 \
        i.valid_ = (i.curr_->state_ == SGC_NODE_STATE_USED) ? 1 : 0;           \
        return i;                                                              \
    }                                                                          \
                                                                               \
    void N##_it_go_next(struct N##_it* i) {                                    \
        i->valid_ = 0;                                                         \
        if (i->curr_ >= i->end_) {                                             \
            return;                                                            \
        }                                                                      \
                                                                               \
        while (i->curr_ < i->end_) {                                           \
            ++i->curr_;                                                        \
            if (i->curr_->state_ == SGC_NODE_STATE_USED) {                     \
                i->valid_ = 1;                                                 \
                break;                                                         \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_it_cbegin(const struct N* const m, struct N##_it* i) {            \
        i->begin_ = (struct N##_node*)(m->data_);                              \
        i->curr_ = i->begin_;                                                  \
        i->end_ = i->begin_ + S - 1;                                           \
        i->valid_ = 1;                                                         \
        if (i->curr_->state_ != SGC_NODE_STATE_USED) {                         \
            N##_it_go_next(i);                                                 \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_it_begin(struct N* m, struct N##_it* i) {                         \
        N##_it_cbegin(m, i);                                                   \
    }                                                                          \
                                                                               \
    void N##_it_go_prev(struct N##_it* i) {                                    \
        i->valid_ = 0;                                                         \
        if (i->curr_ <= i->begin_) {                                           \
            return;                                                            \
        }                                                                      \
                                                                               \
        while (i->curr_ > i->begin_) {                                         \
            --i->curr_;                                                        \
            if (i->curr_->state_ == SGC_NODE_STATE_USED) {                     \
                i->valid_ = 1;                                                 \
                break;                                                         \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_it_cend(const struct N* const m, struct N##_it* i) {              \
        i->begin_ = (struct N##_node*)(m->data_);                              \
        i->end_ = (struct N##_node*)(m->data_) + S - 1;                        \
        i->curr_ = i->end_;                                                    \
        i->valid_ = 1;                                                         \
        if (i->curr_->state_ != SGC_NODE_STATE_USED) {                         \
            N##_it_go_prev(i);                                                 \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_it_end(struct N* m, struct N##_it* i) {                           \
        N##_it_cend(m, i);                                                     \
    }                                                                          \
                                                                               \
    struct N##_it N##_begin(struct N* m) {                                     \
        struct N##_it i;                                                       \
        N##_it_begin(m, &i);                                                   \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_it N##_cbegin(const struct N* const m) {                        \
        struct N##_it i;                                                       \
        N##_it_cbegin(m, &i);                                                  \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_it N##_end(struct N* m) {                                       \
        struct N##_it i;                                                       \
        N##_it_end(m, &i);                                                     \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_it N##_cend(const struct N* const m) {                          \
        struct N##_it i;                                                       \
        N##_it_cend(m, &i);                                                    \
        return i;                                                              \
    }                                                                          \
                                                                               \
    bool N##_it_equal(const struct N##_it first, const struct N##_it second) { \
        return first.curr_ == second.curr_;                                    \
    }                                                                          \
                                                                               \
    bool N##_it_valid(const struct N##_it i) {                                 \
        return i.valid_;                                                       \
    }
