#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_prime.h"
#include "detail/sgc_utils.h"

#define SGC_INIT_STATIC_FUNCTIONS_UNORDERED_SET(V, N)                          \
    static void N##_bucket_sgc_free(struct N##_node* bucket,                   \
                                    size_t is_shared);                         \
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
    static void N##_resize(struct N* u);

#define SGC_INIT_HEADERS_UNORDERED_SET(V, N)                                   \
                                                                               \
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
    int N##_iterator_equal(const struct N##_iterator first,                    \
                           const struct N##_iterator second);                  \
    int N##_iterator_valid(const struct N##_iterator i);                       \
    void N##_set_share(N* u, int is_shared);                                   \
    size_t N##_size(const struct N* const u);                                  \
    void N##_init(struct N* u);                                                \
    int N##_equal(const N* const first, const N* const second);                \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src);       \
    void N##_free(struct N* u);                                                \
    struct N##_iterator N##_find(struct N* u, const V v);                      \
    void N##_rehash(struct N* u, size_t new_max);                              \
    void N##_insert(struct N* u, const V v);                                   \
    void N##_insert_multiple(struct N* u, const V v);                          \
    void N##_erase(struct N* u, const V v);                                    \
    void N##_iterator_erase(struct N* u, struct N##_iterator* i);              \
    int N##_empty(const struct N* const u);

#define SGC_INIT_UNORDERED_SET(V, N)                                           \
    SGC_INIT_HEADERS_UNORDERED_SET(V, N)                                       \
    SGC_INIT_STATIC_FUNCTIONS_UNORDERED_SET(V, N)                              \
                                                                               \
    /* ================== */                                                   \
    /*  BUCKET FUNCTIONS  */                                                   \
    /* ================== */                                                   \
                                                                               \
    struct N##_node* N##_node_new(const V* const value, size_t is_shared) {    \
        struct N##_node* new_node =                                            \
            (struct N##_node*)sgc_malloc(sizeof(struct N##_node));             \
        SGC_COPY(V##_copy, new_node->_value, *value, is_shared);               \
        new_node->next_ = NULL;                                                \
        return new_node;                                                       \
    }                                                                          \
                                                                               \
    static void N##_bucket_sgc_free(struct N##_node* bucket,                   \
                                    size_t is_shared) {                        \
        if (bucket) {                                                          \
            struct N##_node* curr = bucket;                                    \
            struct N##_node* next = bucket;                                    \
            while (next) {                                                     \
                curr = next;                                                   \
                next = curr->next_;                                            \
                if (!is_shared) {                                              \
                    V##_free(&curr->_value);                                   \
                }                                                              \
                sgc_free(curr);                                                \
                curr = NULL;                                                   \
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
    /* ========== */                                                           \
    /*  ITERATOR  */                                                           \
    /* ========== */                                                           \
                                                                               \
    const V* N##_iterator_cdata(struct N##_iterator i) {                       \
        return &i.curr_->_value;                                               \
    }                                                                          \
                                                                               \
    V* N##_iterator_data(struct N##_iterator i) {                              \
        return &i.curr_->_value;                                               \
    }                                                                          \
                                                                               \
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
        u->size_ = u->max_ = 0;                                                \
        u->data_ = NULL;                                                       \
        u->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    int N##_equal(const N* const first, const N* const second) {               \
        int equal = (first == second);                                         \
        if (equal == 0 && first->size_ == second->size_) {                     \
            struct N##_iterator it_first = N##_cbegin(first);                  \
            struct N##_iterator it_second = N##_cbegin(second);                \
            while (N##_iterator_valid(it_first)) {                             \
                if (!V##_equal(&it_first.curr_->_value,                        \
                               &it_second.curr_->_value)) {                    \
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
        if (!src->data_) {                                                     \
            dst->data_ = NULL;                                                 \
            dst->size_ = dst->max_ = 0;                                        \
            return;                                                            \
        }                                                                      \
        dst->size_ = src->size_;                                               \
        dst->max_ = src->max_;                                                 \
        dst->data_ = (struct N##_node**)sgc_malloc(sizeof(struct N##_node*) *  \
                                                   dst->max_);                 \
        dst->shared_ = src->shared_;                                           \
        for (size_t i = 0; i < src->max_; ++i) {                               \
            if (src->data_[i]) {                                               \
                dst->data_[i] =                                                \
                    (struct N##_node*)sgc_malloc(sizeof(struct N##_node));     \
                SGC_COPY(V##_copy, dst->data_[i]->_value,                      \
                         src->data_[i]->_value, src->shared_);                 \
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
                    SGC_COPY(V##_copy, tmp_dst->_value, tmp_src->_value,       \
                             src->shared_);                                    \
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
    void N##_free(struct N* u) {                                               \
        if (u->size_) {                                                        \
            for (size_t i = 0; i < u->max_; ++i) {                             \
                N##_bucket_sgc_free(u->data_[i], u->shared_);                  \
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
    int N##_empty(const struct N* const u) {                                   \
        return u->size_ == 0;                                                  \
    }
