#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_common.h"
#include "detail/sgc_iterator.h"
#include "detail/sgc_list_common.h"
#include "detail/sgc_primitive_types.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define _SGC_INIT_PP_LIST(T, N)                                                \
    static struct _p_##N##_node* _p_##N##_node_alloc();

// TODO add iterator insert/erase, add sort
#define SGC_INIT_HEADERS_LIST(T, N)                                            \
                                                                               \
    struct _p_##N##_node {                                                     \
        T data_;                                                               \
        struct _p_##N##_node* next_;                                           \
        struct _p_##N##_node* prev_;                                           \
    };                                                                         \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        bool sharing_;                                                         \
        struct _p_##N##_node* head_;                                           \
        struct _p_##N##_node* tail_;                                           \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
                                                                               \
    void N##_set_share(N* l, bool shared);                                     \
    size_t N##_size(const N* const l);                                         \
    void N##_init(N* l);                                                       \
    void N##_free(N* l);                                                       \
    bool N##_eq(const N* const first, const N* const second);                  \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src);       \
    void N##_push_back(N* l, T el);                                            \
    const T* N##_back(const N* const l);                                       \
    void N##_set_back(N* l, T new_el);                                         \
    void N##_pop_back(N* l);                                                   \
    void N##_push_front(N* l, const T el);                                     \
    const T* N##_front(const N* const l);                                      \
    void N##_set_front(N* l, T new_el);                                        \
    void N##_pop_front(N* l);                                                  \
    bool N##_empty(const N* l);                                                \
                                                                               \
    struct N##_it {                                                            \
        struct _p_##N##_node* curr_;                                           \
    };                                                                         \
                                                                               \
    typedef struct N##_it N##_it;                                              \
    _SGC_INIT_BD_IT_PROTOTIPES(N)

#define _SGC_INIT_UNIQUE_LIST(T, N)                                            \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src) {      \
        if (src->size_ != 0) {                                                 \
            dst->sharing_ = src->sharing_;                                     \
            dst->head_ = _p_##N##_node_alloc(dst);                             \
            dst->size_ = src->size_;                                           \
            SGC_COPY(T, dst->head_->data_, src->head_->data_, src->sharing_);  \
            struct _p_##N##_node* curr_src = src->head_;                       \
            struct _p_##N##_node* curr_dst = dst->head_;                       \
            struct _p_##N##_node* tmp_src = NULL;                              \
            struct _p_##N##_node* tmp_dst = NULL;                              \
            while (curr_src) {                                                 \
                tmp_src = curr_src->next_;                                     \
                if (!tmp_src) {                                                \
                    break;                                                     \
                }                                                              \
                tmp_dst = _p_##N##_node_alloc(dst);                            \
                SGC_COPY(T, tmp_dst->data_, tmp_src->data_, src->sharing_)     \
                tmp_dst->prev_ = curr_dst;                                     \
                curr_dst->next_ = tmp_dst;                                     \
                curr_dst = tmp_dst;                                            \
                curr_src = tmp_src;                                            \
            }                                                                  \
            dst->tail_ = curr_dst;                                             \
            dst->tail_->next_ = dst->head_->prev_ = NULL;                      \
        } else {                                                               \
            N##_init(dst);                                                     \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_push_back(N* l, T el) {                                           \
        struct _p_##N##_node* new_el = _p_##N##_node_alloc(l);                 \
        SGC_COPY(T, new_el->data_, el, l->sharing_)                            \
        new_el->next_ = NULL;                                                  \
        switch (l->size_) {                                                    \
        case 0:                                                                \
            new_el->prev_ = NULL;                                              \
            l->head_ = l->tail_ = new_el;                                      \
            break;                                                             \
        case 1:                                                                \
            l->tail_ = new_el;                                                 \
            l->head_->next_ = l->tail_;                                        \
            l->tail_->prev_ = l->head_;                                        \
            break;                                                             \
        default:                                                               \
            new_el->prev_ = l->tail_;                                          \
            l->tail_->next_ = new_el;                                          \
            l->tail_ = l->tail_->next_;                                        \
            break;                                                             \
        }                                                                      \
        l->size_++;                                                            \
    }                                                                          \
                                                                               \
    void N##_pop_back(N* l) {                                                  \
        if (l->size_) {                                                        \
            struct _p_##N##_node* tmp = l->tail_;                              \
            l->tail_ = l->tail_->prev_;                                        \
            SGC_FREE(T, tmp->data_, l->sharing_)                        \
            sgc_free(tmp);                                                     \
            if (l->tail_) {                                                    \
                l->tail_->next_ = NULL;                                        \
            }                                                                  \
            --l->size_;                                                        \
            if (l->size_ == 0) {                                               \
                l->head_ = l->tail_ = NULL;                                    \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_push_front(N* l, const T el) {                                    \
        struct _p_##N##_node* new_el = _p_##N##_node_alloc(l);                 \
        SGC_COPY(T, new_el->data_, el, l->sharing_)                            \
        new_el->prev_ = NULL;                                                  \
        switch (l->size_) {                                                    \
        case 0:                                                                \
            new_el->next_ = NULL;                                              \
            l->head_ = l->tail_ = new_el;                                      \
            break;                                                             \
        case 1:                                                                \
            l->head_ = new_el;                                                 \
            l->head_->next_ = l->tail_;                                        \
            l->tail_->prev_ = l->head_;                                        \
            break;                                                             \
        default:                                                               \
            l->head_->prev_ = new_el;                                          \
            new_el->next_ = l->head_;                                          \
            l->head_ = l->head_->prev_;                                        \
            break;                                                             \
        }                                                                      \
        l->size_++;                                                            \
    }                                                                          \
                                                                               \
    void N##_pop_front(N* l) {                                                 \
        if (l->size_) {                                                        \
            struct _p_##N##_node* tmp = l->head_;                              \
            l->head_ = l->head_->next_;                                        \
            SGC_FREE(T, tmp->data_, l->sharing_)                        \
            sgc_free(tmp);                                                     \
            if (l->head_) {                                                    \
                l->head_->prev_ = NULL;                                        \
            }                                                                  \
            --l->size_;                                                        \
            if (l->size_ == 0) {                                               \
                l->head_ = l->tail_ = NULL;                                    \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_it_go_prev(N##_it* i) {                                           \
        i->curr_ = i->curr_->prev_;                                            \
    }                                                                          \
                                                                               \
    void N##_it_begin(N* l, N##_it* i) {                                       \
        i->curr_ = l->head_;                                                   \
    }                                                                          \
                                                                               \
    void N##_it_cbegin(const N* const l, N##_it* i) {                          \
        i->curr_ = l->head_;                                                   \
    }                                                                          \
                                                                               \
    void N##_it_end(N* l, N##_it* i) {                                         \
        i->curr_ = l->tail_;                                                   \
    }                                                                          \
                                                                               \
    void N##_it_cend(const N* const l, N##_it* i) {                            \
        i->curr_ = l->tail_;                                                   \
    }

#define SGC_INIT_LIST(T, N)                                                    \
    SGC_INIT_HEADERS_LIST(T, N)                                                \
    _SGC_INIT_PP_LIST(T, N)                                                    \
    _SGC_INIT_UNIQUE_LIST(T, N)                                                \
    _SGC_INIT_COMMON_LIST(T, N)                                                \
    _SGC_INIT_COMMON(N)
