#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define _SGC_INIT_STATIC_HASH_MAP_TYPE_FUNCTIONS(T, S, N)                      \
    void N##_iterator_erase(struct N* ds, struct N##_iterator* it) {           \
        if (N##_iterator_valid(*it)) {                                         \
            _m_##N##_node_free(ds, it->curr_);                                 \
            it->curr_->_state = SGC_NODE_STATE_ERASED;                         \
            N##_iterator_next(it);                                             \
            --ds->size_;                                                       \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_erase(struct N* ds, const T key) {                                \
        struct N##_iterator it = N##_find(ds, key);                            \
        if (it.is_valid_) {                                                    \
            N##_iterator_erase(ds, &it);                                       \
        }                                                                      \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_find(struct N* ds, const T key) {                  \
        size_t hash = T##_hash(&key);                                          \
        return _m_##N##_find_by_hash(ds, &key, hash);                          \
    }                                                                          \
                                                                               \
    static struct N##_iterator _m_##N##_find_by_hash(struct N* ds,             \
                                                     const T* const key,       \
                                                     size_t hash) {            \
        if (ds->size_) {                                                       \
            size_t position = hash % S;                                        \
            struct N##_node* data = ds->data_;                                 \
            while (data[position]._state != SGC_NODE_STATE_OPEN) {             \
                if (data[position]._state == SGC_NODE_STATE_USED &&            \
                    _m_##N##_node_equal_key(&data[position], key)) {           \
                    return N##_iterator_at(ds, position);                      \
                }                                                              \
                if (position == S - 1) {                                       \
                    position = 0;                                              \
                } else {                                                       \
                    ++position;                                                \
                }                                                              \
            }                                                                  \
        }                                                                      \
        struct N##_iterator it = {NULL, NULL, NULL, 0};                        \
        return it;                                                             \
    }                                                                          \
                                                                               \
    void N##_free(struct N* u) {                                               \
        if (u->size_) {                                                        \
            for (size_t i = 0; i < S; ++i) {                                   \
                if (u->data_[i]._state == SGC_NODE_STATE_USED) {               \
                    _m_##N##_node_free(u, &u->data_[i]);                       \
                }                                                              \
            }                                                                  \
            u->size_ = 0;                                                      \
        }                                                                      \
    }                                                                          \
                                                                               \
    static struct N##_iterator N##_iterator_at(const struct N* const m,        \
                                               size_t at) {                    \
        N##_iterator i;                                                        \
        i.begin_ = (struct N##_node*)(m->data_);                               \
        i.curr_ = i.begin_ + at;                                               \
        i.end_ = i.begin_ + S;                                                 \
        i.is_valid_ = (i.curr_->_state == SGC_NODE_STATE_USED) ? 1 : 0;        \
        return i;                                                              \
    }                                                                          \
                                                                               \
    void N##_iterator_next(struct N##_iterator* i) {                           \
        i->is_valid_ = 0;                                                      \
        if (i->curr_ >= i->end_) {                                             \
            return;                                                            \
        }                                                                      \
                                                                               \
        while (i->curr_ < i->end_) {                                           \
            ++i->curr_;                                                        \
            if (i->curr_->_state == SGC_NODE_STATE_USED) {                     \
                i->is_valid_ = 1;                                              \
                break;                                                         \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_iterator_cbegin(const struct N* const m,                          \
                             struct N##_iterator* i) {                         \
        i->begin_ = (struct N##_node*)(m->data_);                              \
        i->curr_ = i->begin_;                                                  \
        i->end_ = i->begin_ + S - 1;                                           \
        i->is_valid_ = 1;                                                      \
        if (i->curr_->_state != SGC_NODE_STATE_USED) {                         \
            N##_iterator_next(i);                                              \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_iterator_begin(struct N* m, struct N##_iterator* i) {             \
        N##_iterator_cbegin(m, i);                                             \
    }                                                                          \
                                                                               \
    void N##_iterator_prev(struct N##_iterator* i) {                           \
        i->is_valid_ = 0;                                                      \
        if (i->curr_ <= i->begin_) {                                           \
            return;                                                            \
        }                                                                      \
                                                                               \
        while (i->curr_ > i->begin_) {                                         \
            --i->curr_;                                                        \
            if (i->curr_->_state == SGC_NODE_STATE_USED) {                     \
                i->is_valid_ = 1;                                              \
                break;                                                         \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_iterator_cend(const struct N* const m, struct N##_iterator* i) {  \
        i->begin_ = (struct N##_node*)(m->data_);                              \
        i->end_ = (struct N##_node*)(m->data_) + S - 1;                        \
        i->curr_ = i->end_;                                                    \
        i->is_valid_ = 1;                                                      \
        if (i->curr_->_state != SGC_NODE_STATE_USED) {                         \
            N##_iterator_prev(i);                                              \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_iterator_end(struct N* m, struct N##_iterator* i) {               \
        N##_iterator_cend(m, i);                                               \
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
    }
