#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define _SGC_INIT_HASH_MAP_TYPE_FUNCTIONS(T, N)                                \
    void N##_iterator_next(struct N##_iterator* i) {                           \
        if (i->curr_ && i->curr_->next_) {                                     \
            i->curr_ = i->curr_->next_;                                        \
        } else {                                                               \
            struct N##_node* tmp = i->curr_;                                   \
            ++i->curr_bucket_;                                                 \
            i->is_valid_ = (i->curr_bucket_ != i->max_);                       \
            while (i->curr_bucket_ < i->max_) {                                \
                i->curr_ = i->data_[i->curr_bucket_];                          \
                if (i->curr_) {                                                \
                    break;                                                     \
                }                                                              \
                ++i->curr_bucket_;                                             \
            }                                                                  \
            if (!i->curr_) {                                                   \
                i->is_valid_ = 0;                                              \
                i->curr_ = tmp;                                                \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_iterator_begin(struct N* m, struct N##_iterator* i) {             \
        if (m->data_) {                                                        \
            i->data_ = m->data_;                                               \
            i->curr_ = m->data_[0];                                            \
            i->curr_bucket_ = 0;                                               \
            i->max_ = m->max_;                                                 \
            if (!i->curr_) {                                                   \
                N##_iterator_next(i);                                          \
            }                                                                  \
            i->is_valid_ = 1;                                                  \
        } else {                                                               \
            *i = (struct N##_iterator){NULL, NULL, 0, 0, 0};                   \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_iterator_cbegin(const struct N* const m,                          \
                             struct N##_iterator* i) {                         \
        if (m->data_) {                                                        \
            i->data_ = m->data_;                                               \
            i->curr_ = m->data_[0];                                            \
            i->curr_bucket_ = 0;                                               \
            i->max_ = m->max_;                                                 \
            if (!i->curr_) {                                                   \
                N##_iterator_next(i);                                          \
            }                                                                  \
            i->is_valid_ = 1;                                                  \
        } else {                                                               \
            *i = (struct N##_iterator){NULL, NULL, 0, 0, 0};                   \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_iterator_prev(struct N##_iterator* i) {                           \
        if (i->curr_ && i->data_[i->curr_bucket_] != i->curr_) {               \
            struct N##_node* curr = i->data_[i->curr_bucket_];                 \
            struct N##_node* next = curr->next_;                               \
            while (next != i->curr_) {                                         \
                curr = next;                                                   \
                next = curr->next_;                                            \
            }                                                                  \
            i->curr_ = curr;                                                   \
        } else {                                                               \
            struct N##_node* tmp = i->curr_;                                   \
            --i->curr_bucket_;                                                 \
            while (1) {                                                        \
                i->curr_ = i->data_[i->curr_bucket_];                          \
                if (i->curr_) {                                                \
                    break;                                                     \
                }                                                              \
                --i->curr_bucket_;                                             \
            }                                                                  \
            if (!i->curr_) {                                                   \
                i->is_valid_ = 0;                                              \
                i->curr_ = tmp;                                                \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_iterator_end(struct N* m, struct N##_iterator* i) {               \
        if (m->data_) {                                                        \
            i->data_ = m->data_;                                               \
            i->curr_ = m->data_[m->max_ - 1];                                  \
            i->max_ = m->max_;                                                 \
            i->curr_bucket_ = m->max_ - 1;                                     \
            if (i->curr_) {                                                    \
                i->curr_ = N##_bucket_end(i->curr_);                           \
            } else {                                                           \
                N##_iterator_prev(i);                                          \
            }                                                                  \
            i->is_valid_ = 1;                                                  \
        } else {                                                               \
            *i = (struct N##_iterator){NULL, NULL, 0, 0, 0};                   \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_iterator_cend(const struct N* const m, struct N##_iterator* i) {  \
        if (m->data_) {                                                        \
            i->data_ = m->data_;                                               \
            i->curr_ = m->data_[m->max_ - 1];                                  \
            i->max_ = m->max_;                                                 \
            i->curr_bucket_ = m->max_ - 1;                                     \
            if (i->curr_) {                                                    \
                i->curr_ = N##_bucket_end(i->curr_);                           \
            } else {                                                           \
                N##_iterator_prev(i);                                          \
            }                                                                  \
            i->is_valid_ = 1;                                                  \
        } else {                                                               \
            *i = (struct N##_iterator){NULL, NULL, 0, 0, 0};                   \
        }                                                                      \
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
    static void N##_bucket_sgc_free(const struct N* const u,                   \
                                    struct N##_node* bucket) {                 \
        if (bucket) {                                                          \
            struct N##_node* curr = bucket;                                    \
            struct N##_node* next = bucket;                                    \
            while (next) {                                                     \
                curr = next;                                                   \
                next = curr->next_;                                            \
                N##_node_free(u, curr);                                        \
                sgc_free(curr);                                                \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void N##_bucket_insert(struct N##_node* bucket,                     \
                                  struct N##_node* new_node) {                 \
        struct N##_node* curr = bucket;                                        \
        struct N##_node* next = curr;                                          \
        while (next) {                                                         \
            curr = next;                                                       \
            next = curr->next_;                                                \
        }                                                                      \
        curr->next_ = new_node;                                                \
    }                                                                          \
                                                                               \
    static size_t N##_bucket_node_size(struct N##_node* bucket) {              \
        size_t size = 0;                                                       \
        if (bucket) {                                                          \
            struct N##_node* curr = bucket;                                    \
            while (curr) {                                                     \
                ++size;                                                        \
                curr = curr->next_;                                            \
            }                                                                  \
        }                                                                      \
        return size;                                                           \
    }                                                                          \
                                                                               \
    static struct N##_node* N##_bucket_end(struct N##_node* bucket) {          \
        struct N##_node* curr = bucket;                                        \
        struct N##_node* next = bucket;                                        \
        while (next) {                                                         \
            curr = next;                                                       \
            next = curr->next_;                                                \
        }                                                                      \
        return curr;                                                           \
    }                                                                          \
                                                                               \
    size_t N##_bucket_count(const struct N* const u) {                         \
        return u->max_;                                                        \
    }                                                                          \
                                                                               \
    size_t N##_bucket_size(const struct N* const u, size_t n) {                \
        size_t ret = 0;                                                        \
        if (u->data_) {                                                        \
            ret = N##_bucket_node_size(u->data_[n]);                           \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    size_t N##_buckets_used(const struct N* const u) {                         \
        size_t ret = 0;                                                        \
        for (size_t i = 0; i < u->max_; ++i) {                                 \
            ret += (u->data_[i] == NULL) ? 0 : 1;                              \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src) {      \
        N##_copy_base_data(dst, src);                                          \
        N##_copy_nodes(dst, src);                                              \
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
            size_t position;                                                   \
            struct N##_iterator tmp = N##_begin(u);                            \
            struct N##_node* next;                                             \
            for (size_t i = 0; i < u->size_; ++i) {                            \
                position = N##_node_hash_value(tmp.curr_) % new_max;           \
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
    static void N##_copy_nodes(struct N* __restrict__ dst,                     \
                               const struct N* __restrict__ const src) {       \
        dst->data_ = (struct N##_node**)sgc_malloc(sizeof(struct N##_node*) *  \
                                                   dst->max_);                 \
        for (size_t i = 0; i < src->max_; ++i) {                               \
            if (src->data_[i]) {                                               \
                dst->data_[i] =                                                \
                    (struct N##_node*)sgc_malloc(sizeof(struct N##_node));     \
                N##_node_copy_values(src, dst->data_[i], src->data_[i]);       \
                struct N##_node* curr_src = src->data_[i];                     \
                struct N##_node* curr_dst = dst->data_[i];                     \
                struct N##_node* tmp_src = NULL;                               \
                struct N##_node* tmp_dst = NULL;                               \
                while (curr_src) {                                             \
                    tmp_src = curr_src->next_;                                 \
                    if (!tmp_src) {                                            \
                        break;                                                 \
                    }                                                          \
                    tmp_dst =                                                  \
                        (struct N##_node*)sgc_malloc(sizeof(struct N##_node)); \
                    N##_node_copy_values(src, tmp_dst, tmp_src);               \
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
    static void N##_rehash_size(const struct N* const u, size_t* max,          \
                                size_t* new_max) {                             \
        *max = u->max_;                                                        \
        if (u->size_ == *max) {                                                \
            *new_max = sgc_next_prime(2 * u->max_ + 1);                        \
        }                                                                      \
    }                                                                          \
    /* TODO check why this exists */                                           \
    void N##_rehash(struct N* u, size_t new_max) {                             \
        struct N##_node** new_data =                                           \
            (struct N##_node**)sgc_malloc(sizeof(struct N##_node*) * new_max); \
        for (size_t i = 0; i < new_max; ++i) {                                 \
            new_data[i] = NULL;                                                \
        }                                                                      \
                                                                               \
        size_t position;                                                       \
        struct N##_iterator tmp = N##_begin(u);                                \
        struct N##_node* next;                                                 \
        for (size_t i = 0; i < u->size_; ++i) {                                \
            position = N##_node_hash_value(tmp.curr_) % new_max;               \
            position = 0;                                                      \
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
    static struct N##_node* N##_bucket_remove(struct N* u,                     \
                                              struct N##_node* bucket,         \
                                              const T* const key) {            \
        struct N##_node* ret = bucket;                                         \
        struct N##_node* tmp = bucket;                                         \
        struct N##_node* prev = bucket;                                        \
        while (tmp) {                                                          \
            if (N##_node_equal_key(tmp, key)) {                                \
                if (tmp == bucket) {                                           \
                    ret = tmp->next_;                                          \
                }                                                              \
                prev->next_ = tmp->next_;                                      \
                N##_node_free(u, tmp);                                         \
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
    void N##_erase(struct N* u, const T v) {                                   \
        if (u->data_) {                                                        \
            size_t hash = T##_hash(&v);                                        \
            size_t position = hash % u->max_;                                  \
            u->data_[position] = N##_bucket_remove(u, u->data_[position], &v); \
        }                                                                      \
    }
