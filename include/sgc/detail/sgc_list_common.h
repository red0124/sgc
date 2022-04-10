#pragma once
#include <stdlib.h>

#define _SGC_INIT_COMMON_LIST(T, N)                                            \
    static struct _p_##N##_node* _p_##N##_node_alloc() {                       \
        return (struct _p_##N##_node*)sgc_malloc(                              \
            sizeof(struct _p_##N##_node));                                     \
    }                                                                          \
                                                                               \
    void N##_init(N* l) {                                                      \
        l->size_ = 0;                                                          \
        l->head_ = l->tail_ = NULL;                                            \
        l->sharing_ = 0;                                                       \
    }                                                                          \
                                                                               \
    void N##_free(N* l) {                                                      \
        struct _p_##N##_node* curr = l->head_;                                 \
        struct _p_##N##_node* tmp;                                             \
        for (size_t i = 0; i < l->size_; ++i) {                                \
            tmp = curr;                                                        \
            curr = curr->next_;                                                \
            SGC_FREE(T##_free, tmp->data_, l->sharing_)                        \
            sgc_free(tmp);                                                     \
        }                                                                      \
        l->head_ = l->tail_ = NULL;                                            \
        l->size_ = 0;                                                          \
    }                                                                          \
                                                                               \
    const T* N##_back(const N* const l) {                                      \
        if (l->size_) {                                                        \
            return &l->tail_->data_;                                           \
        }                                                                      \
        return NULL;                                                           \
    }                                                                          \
                                                                               \
    void N##_set_back(N* l, T new_el) {                                        \
        if (l->size_) {                                                        \
            SGC_REPLACE(T##_copy, T##_free, l->tail_->data_, new_el,           \
                        l->sharing_);                                          \
        }                                                                      \
    }                                                                          \
                                                                               \
    const T* N##_front(const N* const l) {                                     \
        if (l->size_) {                                                        \
            return &l->head_->data_;                                           \
        }                                                                      \
        return NULL;                                                           \
    }                                                                          \
                                                                               \
    void N##_set_front(N* l, T new_el) {                                       \
        if (l->size_) {                                                        \
            SGC_REPLACE(T##_copy, T##_free, l->head_->data_, new_el,           \
                        l->sharing_);                                          \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_it_data(N##_it i) {                                                 \
        return &i.curr_->data_;                                                \
    }                                                                          \
                                                                               \
    void N##_it_go_next(N##_it* i) {                                           \
        i->curr_ = i->curr_->next_;                                            \
    }                                                                          \
                                                                               \
    bool N##_it_eq(const N##_it first, const N##_it second) {                  \
        return first.curr_ == second.curr_;                                    \
    }                                                                          \
                                                                               \
    bool N##_it_valid(const N##_it i) {                                        \
        return i.curr_ != NULL;                                                \
    }                                                                          \
                                                                               \
    N##_it N##_end(N* l) {                                                     \
        N##_it i;                                                              \
        N##_it_end(l, &i);                                                     \
        return i;                                                              \
    }                                                                          \
                                                                               \
    N##_it N##_cend(const N* const l) {                                        \
        N##_it i;                                                              \
        N##_it_cend(l, &i);                                                    \
        return i;                                                              \
    }                                                                          \
                                                                               \
    N##_it N##_begin(N* l) {                                                   \
        N##_it i;                                                              \
        N##_it_begin(l, &i);                                                   \
        return i;                                                              \
    }                                                                          \
                                                                               \
    N##_it N##_cbegin(const N* const l) {                                      \
        N##_it i;                                                              \
        N##_it_cbegin(l, &i);                                                  \
        return i;                                                              \
    }
