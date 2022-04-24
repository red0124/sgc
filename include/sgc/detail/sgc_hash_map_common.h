#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define _SGC_INIT_COMMON_HASH_MAP(T, N)                                        \
    void N##_it_go_next(N##_it* i) {                                           \
        if (i->curr_ && i->curr_->next_) {                                     \
            i->curr_ = i->curr_->next_;                                        \
        } else {                                                               \
            ++i->curr_bucket_;                                                 \
            if (i->curr_bucket_ == i->max_) {                                  \
                i->valid_ = false;                                             \
                return;                                                        \
            }                                                                  \
            while (i->curr_bucket_ < i->max_) {                                \
                i->curr_ = i->data_[i->curr_bucket_];                          \
                if (i->curr_) {                                                \
                    return;                                                    \
                }                                                              \
                ++i->curr_bucket_;                                             \
            }                                                                  \
            i->valid_ = false;                                                 \
        }                                                                      \
    }                                                                          \
                                                                               \
    N##_it N##_begin(N* m) {                                                   \
        N##_it i;                                                              \
        if (m->size_ > 0) {                                                    \
            i.data_ = m->data_;                                                \
            i.curr_ = m->data_[0];                                             \
            i.curr_bucket_ = 0;                                                \
            i.max_ = m->max_;                                                  \
            if (!i.curr_) {                                                    \
                N##_it_go_next(&i);                                            \
            }                                                                  \
            i.valid_ = true;                                                   \
        } else {                                                               \
            i.valid_ = false;                                                  \
        }                                                                      \
        return i;                                                              \
    }                                                                          \
                                                                               \
    void N##_it_go_prev(N##_it* i) {                                           \
        if (i->curr_ && i->data_[i->curr_bucket_] != i->curr_) {               \
            struct _p_##N##_node* curr = i->data_[i->curr_bucket_];            \
            struct _p_##N##_node* next = curr->next_;                          \
            while (next != i->curr_) {                                         \
                curr = next;                                                   \
                next = curr->next_;                                            \
            }                                                                  \
            i->curr_ = curr;                                                   \
        } else {                                                               \
            do {                                                               \
                if (i->curr_bucket_ == 0) {                                    \
                    i->valid_ = false;                                         \
                    return;                                                    \
                }                                                              \
                --i->curr_bucket_;                                             \
                i->curr_ = i->data_[i->curr_bucket_];                          \
                if (i->curr_) {                                                \
                    while (i->curr_->next_) {                                  \
                        i->curr_ = i->curr_->next_;                            \
                    }                                                          \
                    return;                                                    \
                }                                                              \
            } while (true);                                                    \
        }                                                                      \
    }                                                                          \
                                                                               \
    N##_it N##_end(N* m) {                                                     \
        N##_it i;                                                              \
        if (m->size_ > 0) {                                                    \
            i.data_ = m->data_;                                                \
            i.curr_ = m->data_[m->max_ - 1];                                   \
            i.max_ = m->max_;                                                  \
            i.curr_bucket_ = m->max_ - 1;                                      \
            if (i.curr_) {                                                     \
                i.curr_ = _p_##N##_bucket_end(i.curr_);                        \
            } else {                                                           \
                N##_it_go_prev(&i);                                            \
            }                                                                  \
            i.valid_ = true;                                                   \
        } else {                                                               \
            i.valid_ = false;                                                  \
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
    }                                                                          \
                                                                               \
    static void _p_##N##_bucket_free_nodes(const N* const u,                   \
                                           struct _p_##N##_node* bucket) {     \
        if (bucket) {                                                          \
            struct _p_##N##_node* curr = bucket;                               \
            struct _p_##N##_node* next = bucket;                               \
            while (next) {                                                     \
                curr = next;                                                   \
                next = curr->next_;                                            \
                _p_##N##_node_free(u, curr);                                   \
                sgc_free(curr);                                                \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void _p_##N##_bucket_insert(struct _p_##N##_node* bucket,           \
                                       struct _p_##N##_node* new_node) {       \
        struct _p_##N##_node* curr = bucket;                                   \
        struct _p_##N##_node* next = curr;                                     \
        while (next) {                                                         \
            curr = next;                                                       \
            next = curr->next_;                                                \
        }                                                                      \
        curr->next_ = new_node;                                                \
    }                                                                          \
                                                                               \
    static size_t _p_##N##_bucket_node_size(struct _p_##N##_node* bucket) {    \
        size_t size = 0;                                                       \
        if (bucket) {                                                          \
            struct _p_##N##_node* curr = bucket;                               \
            while (curr) {                                                     \
                ++size;                                                        \
                curr = curr->next_;                                            \
            }                                                                  \
        }                                                                      \
        return size;                                                           \
    }                                                                          \
                                                                               \
    static struct _p_##N##_node* _p_##N##_bucket_end(                          \
        struct _p_##N##_node* bucket) {                                        \
        struct _p_##N##_node* curr = bucket;                                   \
        struct _p_##N##_node* next = bucket;                                   \
        while (next) {                                                         \
            curr = next;                                                       \
            next = curr->next_;                                                \
        }                                                                      \
        return curr;                                                           \
    }                                                                          \
                                                                               \
    size_t N##_bucket_count(const N* const u) {                                \
        return u->max_;                                                        \
    }                                                                          \
                                                                               \
    size_t N##_bucket_size(const N* const u, size_t n) {                       \
        size_t ret = 0;                                                        \
        if (u->data_) {                                                        \
            ret = _p_##N##_bucket_node_size(u->data_[n]);                      \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    size_t N##_buckets_used(const N* const u) {                                \
        size_t ret = 0;                                                        \
        for (size_t i = 0; i < u->max_; ++i) {                                 \
            ret += (u->data_[i] == NULL) ? 0 : 1;                              \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src) {      \
        if (src->size_) {                                                      \
            _p_##N##_copy_base_data(dst, src);                                 \
            _p_##N##_copy_nodes(dst, src);                                     \
        } else {                                                               \
            N##_init(dst);                                                     \
        }                                                                      \
    }                                                                          \
                                                                               \
    static bool _p_##N##_resize(N* u) {                                        \
        size_t max, new_max;                                                   \
        _p_##N##_rehash_size(u, &max, &new_max);                               \
        if (u->size_ == max) {                                                 \
            struct _p_##N##_node** new_data =                                  \
                (struct _p_##N##_node**)sgc_malloc(                            \
                    sizeof(struct _p_##N##_node*) * new_max);                  \
            if (!new_data) {                                                   \
                return false;                                                  \
            }                                                                  \
            for (size_t i = 0; i < new_max; ++i) {                             \
                new_data[i] = NULL;                                            \
            }                                                                  \
                                                                               \
            size_t position;                                                   \
            N##_it tmp = N##_begin(u);                                         \
            struct _p_##N##_node* next;                                        \
            for (size_t i = 0; i < u->size_; ++i) {                            \
                position = _p_##N##_node_hash_value(tmp.curr_) % new_max;      \
                next = tmp.curr_->next_;                                       \
                tmp.curr_->next_ = NULL;                                       \
                if (new_data[position]) {                                      \
                    _p_##N##_bucket_insert(new_data[position], tmp.curr_);     \
                } else {                                                       \
                    new_data[position] = tmp.curr_;                            \
                }                                                              \
                if (next) {                                                    \
                    tmp.curr_ = next;                                          \
                } else {                                                       \
                    N##_it_go_next(&tmp);                                      \
                }                                                              \
            }                                                                  \
            sgc_free(u->data_);                                                \
            u->data_ = new_data;                                               \
            u->max_ = new_max;                                                 \
        }                                                                      \
        return true;                                                           \
    }                                                                          \
                                                                               \
    static void _p_##N##_copy_nodes(N* __restrict__ dst,                       \
                                    const N* __restrict__ const src) {         \
        dst->data_ = (struct _p_##N##_node**)sgc_malloc(                       \
            sizeof(struct _p_##N##_node*) * dst->max_);                        \
        if (!dst->data_) {                                                     \
            N##_init(dst);                                                     \
            return;                                                            \
        }                                                                      \
        for (size_t i = 0; i < src->max_; ++i) {                               \
            if (src->data_[i]) {                                               \
                struct _p_##N##_node* new_data =                               \
                    (struct _p_##N##_node*)sgc_malloc(                         \
                        sizeof(struct _p_##N##_node));                         \
                if (!new_data) {                                               \
                    for (size_t j = 0; j < i; ++j) {                           \
                        _p_##N##_bucket_free_nodes(dst, dst->data_[j]);        \
                    }                                                          \
                    sgc_free(dst->data_);                                      \
                    N##_init(dst);                                             \
                    return;                                                    \
                }                                                              \
                dst->data_[i] = new_data;                                      \
                _p_##N##_node_copy_values(src, dst->data_[i], src->data_[i]);  \
                struct _p_##N##_node* curr_src = src->data_[i];                \
                struct _p_##N##_node* curr_dst = dst->data_[i];                \
                struct _p_##N##_node* tmp_src = NULL;                          \
                struct _p_##N##_node* tmp_dst = NULL;                          \
                while (curr_src) {                                             \
                    tmp_src = curr_src->next_;                                 \
                    if (!tmp_src) {                                            \
                        break;                                                 \
                    }                                                          \
                    tmp_dst = (struct _p_##N##_node*)sgc_malloc(               \
                        sizeof(struct _p_##N##_node));                         \
                    if (!tmp_dst) {                                            \
                        for (size_t j = 0; j < i; ++j) {                       \
                            _p_##N##_bucket_free_nodes(dst, dst->data_[j]);    \
                        }                                                      \
                        curr_dst->next_ = NULL;                                \
                        _p_##N##_bucket_free_nodes(dst, dst->data_[i]);        \
                        sgc_free(dst->data_);                                  \
                        N##_init(dst);                                         \
                        return;                                                \
                    }                                                          \
                    _p_##N##_node_copy_values(src, tmp_dst, tmp_src);          \
                    curr_dst->next_ = tmp_dst;                                 \
                    curr_dst = tmp_dst;                                        \
                    curr_src = tmp_src;                                        \
                }                                                              \
                curr_dst->next_ = NULL;                                        \
            } else {                                                           \
                dst->data_[i] = NULL;                                          \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void _p_##N##_rehash_size(const N* const u, size_t* max,            \
                                     size_t* new_max) {                        \
        *max = u->max_;                                                        \
        if (u->size_ == *max) {                                                \
            *new_max = sgc_next_prime(2 * u->max_ + 1);                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_rehash(N* u, size_t new_max) {                                    \
        struct _p_##N##_node** new_data = (struct _p_##N##_node**)sgc_malloc(  \
            sizeof(struct _p_##N##_node*) * new_max);                          \
        if (!new_data) {                                                       \
            return;                                                            \
        }                                                                      \
        for (size_t i = 0; i < new_max; ++i) {                                 \
            new_data[i] = NULL;                                                \
        }                                                                      \
                                                                               \
        size_t position;                                                       \
        N##_it tmp = N##_begin(u);                                             \
        struct _p_##N##_node* next;                                            \
        for (size_t i = 0; i < u->size_; ++i) {                                \
            position = _p_##N##_node_hash_value(tmp.curr_) % new_max;          \
            position = 0;                                                      \
            next = tmp.curr_->next_;                                           \
            tmp.curr_->next_ = NULL;                                           \
            if (new_data[position]) {                                          \
                _p_##N##_bucket_insert(new_data[position], tmp.curr_);         \
            } else {                                                           \
                new_data[position] = tmp.curr_;                                \
            }                                                                  \
            if (next) {                                                        \
                tmp.curr_ = next;                                              \
            } else {                                                           \
                N##_it_go_next(&tmp);                                          \
            }                                                                  \
        }                                                                      \
        sgc_free(u->data_);                                                    \
        u->data_ = new_data;                                                   \
        u->max_ = new_max;                                                     \
    }                                                                          \
                                                                               \
    static struct _p_##N##_node*                                               \
        _p_##N##_bucket_remove(N* u, struct _p_##N##_node* bucket,             \
                               const T* const key) {                           \
        struct _p_##N##_node* ret = bucket;                                    \
        struct _p_##N##_node* tmp = bucket;                                    \
        struct _p_##N##_node* prev = bucket;                                   \
        while (tmp) {                                                          \
            if (_p_##N##_node_eq_key(tmp, key)) {                              \
                if (tmp == bucket) {                                           \
                    ret = tmp->next_;                                          \
                }                                                              \
                prev->next_ = tmp->next_;                                      \
                _p_##N##_node_free(u, tmp);                                    \
                sgc_free(tmp);                                                 \
                --u->size_;                                                    \
                break;                                                         \
            }                                                                  \
            prev = tmp;                                                        \
            tmp = tmp->next_;                                                  \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_erase(N* u, const T v) {                                          \
        if (u->data_) {                                                        \
            size_t hash = T##_hash(&v);                                        \
            size_t position = hash % u->max_;                                  \
            u->data_[position] =                                               \
                _p_##N##_bucket_remove(u, u->data_[position], &v);             \
        }                                                                      \
    }
