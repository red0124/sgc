#pragma once
#include <stdlib.h>

#define _SGC_INIT_COMMON_LIST(T, N)                                            \
    static struct _p_##N##_node* _p_##N##_node_alloc(void) {                   \
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
            _SGC_FREE(T, tmp->data_, l->sharing_)                              \
            sgc_free(tmp);                                                     \
        }                                                                      \
        l->head_ = l->tail_ = NULL;                                            \
        l->size_ = 0;                                                          \
    }                                                                          \
                                                                               \
    T* N##_back(const N* const l) {                                            \
        if (l->size_) {                                                        \
            return &l->tail_->data_;                                           \
        }                                                                      \
        return NULL;                                                           \
    }                                                                          \
                                                                               \
    void N##_set_back(N* l, T new_el) {                                        \
        if (l->size_) {                                                        \
            _SGC_REPLACE(T, l->tail_->data_, new_el, l->sharing_);             \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_front(const N* const l) {                                           \
        if (l->size_) {                                                        \
            return &l->head_->data_;                                           \
        }                                                                      \
        return NULL;                                                           \
    }                                                                          \
                                                                               \
    void N##_set_front(N* l, T new_el) {                                       \
        if (l->size_) {                                                        \
            _SGC_REPLACE(T, l->head_->data_, new_el, l->sharing_);             \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_it_data(N##_it* i) {                                                \
        return &i->curr_->data_;                                               \
    }                                                                          \
                                                                               \
    T* N##_it_value(N##_it* i) {                                               \
        return &i->curr_->data_;                                               \
    }                                                                          \
                                                                               \
    void N##_it_go_next(N##_it* i) {                                           \
        i->curr_ = i->curr_->next_;                                            \
    }                                                                          \
                                                                               \
    bool N##_it_eq(const N##_it* const first, const N##_it* const second) {    \
        return first->curr_ == second->curr_;                                  \
    }                                                                          \
                                                                               \
    bool N##_it_valid(const N##_it* const i) {                                 \
        return i->curr_ != NULL;                                               \
    }                                                                          \
                                                                               \
    N##_it N##_end(N* l) {                                                     \
        N##_it i;                                                              \
        i.curr_ = l->tail_;                                                    \
        return i;                                                              \
    }                                                                          \
                                                                               \
    N##_it N##_begin(N* l) {                                                   \
        N##_it i;                                                              \
        i.curr_ = l->head_;                                                    \
        return i;                                                              \
    }                                                                          \
                                                                               \
    static void _p_##N##_free_nodes(struct _p_##N##_node* n, bool sharing) {   \
        struct _p_##N##_node* curr = n;                                        \
        struct _p_##N##_node* next;                                            \
        while (curr) {                                                         \
            next = curr->next_;                                                \
            _SGC_FREE(T, curr->data_, sharing);                                \
            sgc_free(curr);                                                    \
            curr = next;                                                       \
        }                                                                      \
    }
