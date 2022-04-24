#pragma once
#include <stdbool.h>
#include <stdlib.h>

enum _sgc_node_state {
    _SGC_NODE_STATE_OPEN,
    _SGC_NODE_STATE_USED,
    _SGC_NODE_STATE_ERASED,
};

#define _SGC_INIT_COMMON_FS_HASH_MAP(T, S, N)                                  \
    void N##_erase_it(N* ds, struct N##_it* it) {                              \
        if (N##_it_valid(it)) {                                                \
            _p_##N##_node_free(ds, it->curr_);                                 \
            it->curr_->state_ = _SGC_NODE_STATE_ERASED;                        \
            N##_it_go_next(it);                                                \
            --ds->size_;                                                       \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_erase(N* ds, const T key) {                                       \
        struct N##_it it = N##_find(ds, key);                                  \
        if (it.valid_) {                                                       \
            N##_erase_it(ds, &it);                                             \
        }                                                                      \
    }                                                                          \
                                                                               \
    struct N##_it N##_find(N* ds, const T key) {                               \
        size_t hash = T##_hash(&key);                                          \
        return _p_##N##_find_by_hash(ds, &key, hash);                          \
    }                                                                          \
                                                                               \
    static struct N##_it _p_##N##_find_by_hash(N* ds, const T* const key,      \
                                               size_t hash) {                  \
        if (ds->size_ > 0) {                                                   \
            size_t position = hash % S;                                        \
            size_t starting_position = S;                                      \
            struct _p_##N##_node* data = ds->data_;                            \
            while (data[position].state_ != _SGC_NODE_STATE_OPEN) {            \
                if (data[position].state_ == _SGC_NODE_STATE_USED &&           \
                    _p_##N##_node_eq_key(&data[position], key)) {              \
                    return _p_##N##_it_at(ds, position);                       \
                }                                                              \
                if (S != 1 && position == S - 1) {                             \
                    position = 0;                                              \
                    starting_position = hash % S;                              \
                } else {                                                       \
                    ++position;                                                \
                    if (position >= starting_position) {                       \
                        break;                                                 \
                    }                                                          \
                }                                                              \
            }                                                                  \
        }                                                                      \
        struct N##_it it;                                                      \
        it.valid_ = false;                                                     \
        return it;                                                             \
    }                                                                          \
                                                                               \
    void N##_free(N* u) {                                                      \
        if (u->size_) {                                                        \
            for (size_t i = 0; i < S; ++i) {                                   \
                if (u->data_[i].state_ == _SGC_NODE_STATE_USED) {              \
                    _p_##N##_node_free(u, &u->data_[i]);                       \
                }                                                              \
            }                                                                  \
            u->size_ = 0;                                                      \
        }                                                                      \
    }                                                                          \
                                                                               \
    static struct N##_it _p_##N##_it_at(const N* const m, size_t at) {         \
        N##_it i;                                                              \
        i.begin_ = (struct _p_##N##_node*)(m->data_);                          \
        i.curr_ = i.begin_ + at;                                               \
        i.end_ = i.begin_ + S - 1;                                             \
        i.valid_ = (i.curr_->state_ == _SGC_NODE_STATE_USED);                  \
        return i;                                                              \
    }                                                                          \
                                                                               \
    void N##_it_go_next(struct N##_it* i) {                                    \
        i->valid_ = false;                                                     \
        if (i->curr_ >= i->end_) {                                             \
            return;                                                            \
        }                                                                      \
                                                                               \
        while (i->curr_ < i->end_) {                                           \
            ++i->curr_;                                                        \
            if (i->curr_->state_ == _SGC_NODE_STATE_USED) {                    \
                i->valid_ = 1;                                                 \
                break;                                                         \
            }                                                                  \
        }                                                                      \
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
            if (i->curr_->state_ == _SGC_NODE_STATE_USED) {                    \
                i->valid_ = 1;                                                 \
                break;                                                         \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    struct N##_it N##_begin(N* m) {                                            \
        struct N##_it i;                                                       \
        i.begin_ = (struct _p_##N##_node*)(m->data_);                          \
        i.curr_ = i.begin_;                                                    \
        i.end_ = i.begin_ + S - 1;                                             \
        i.valid_ = true;                                                       \
        if (i.curr_->state_ != _SGC_NODE_STATE_USED) {                         \
            N##_it_go_next(&i);                                                \
        }                                                                      \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_it N##_end(N* m) {                                              \
        struct N##_it i;                                                       \
        i.begin_ = (struct _p_##N##_node*)(m->data_);                          \
        i.end_ = (struct _p_##N##_node*)(m->data_) + S - 1;                    \
        i.curr_ = i.end_;                                                      \
        i.valid_ = 1;                                                          \
        if (i.curr_->state_ != _SGC_NODE_STATE_USED) {                         \
            N##_it_go_prev(&i);                                                \
        }                                                                      \
        return i;                                                              \
    }                                                                          \
                                                                               \
    bool N##_it_eq(const N##_it* const first, const N##_it* const second) {    \
        return first->curr_ == second->curr_;                                  \
    }                                                                          \
                                                                               \
    bool N##_it_valid(const N##_it* const i) {                                 \
        return i->valid_;                                                      \
    }
