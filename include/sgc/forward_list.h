#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_common.h"
#include "detail/sgc_iterator.h"
#include "detail/sgc_list_common.h"
#include "detail/sgc_primitive_types.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define _SGC_INIT_PP_FORWARD_LIST(T, N)                                        \
    static struct _p_##N##_node* _p_##N##_node_alloc();

#define SGC_INIT_HEADERS_FORWARD_LIST(T, N)                                    \
    struct _p_##N##_node {                                                     \
        T data_;                                                               \
        struct _p_##N##_node* next_;                                           \
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
    void N##_push_front(N* l, const T el);                                     \
    const T* N##_front(const N* const l);                                      \
    void N##_set_front(N* l, T new_el);                                        \
    void N##_pop_front(N* l);                                                  \
    bool N##_empty(const N* l);                                                \
                                                                               \
    struct N##_it {                                                            \
        struct _p_##N##_node* curr_;                                           \
        struct _p_##N##_node* head_;                                           \
    };                                                                         \
                                                                               \
    typedef struct N##_it N##_it;                                              \
    _SGC_INIT_FWD_IT_PROTOTIPES(N)

#define _SGC_INIT_UNIQUE_FORWARD_LIST(T, N)                                    \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src) {      \
        if (src->size_ != 0) {                                                 \
            dst->size_ = src->size_;                                           \
            dst->sharing_ = src->sharing_;                                     \
            dst->head_ = _p_##N##_node_alloc(dst);                             \
            SGC_COPY(T##_copy, dst->head_->data_, src->head_->data_,           \
                     src->sharing_);                                           \
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
                SGC_COPY(T##_copy, tmp_dst->data_, tmp_src->data_,             \
                         src->sharing_);                                       \
                curr_dst->next_ = tmp_dst;                                     \
                curr_dst = tmp_dst;                                            \
                curr_src = tmp_src;                                            \
            }                                                                  \
            dst->tail_ = curr_dst;                                             \
            dst->tail_->next_ = NULL;                                          \
        } else {                                                               \
            N##_init(dst);                                                     \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_push_back(N* l, T el) {                                           \
        struct _p_##N##_node* new_el = _p_##N##_node_alloc(l);                 \
        SGC_COPY(T##_copy, new_el->data_, el, l->sharing_);                    \
        new_el->next_ = NULL;                                                  \
        switch (l->size_) {                                                    \
        case 0:                                                                \
            l->head_ = l->tail_ = new_el;                                      \
            break;                                                             \
        case 1:                                                                \
            l->tail_ = new_el;                                                 \
            l->head_->next_ = l->tail_;                                        \
            break;                                                             \
        default:                                                               \
            l->tail_->next_ = new_el;                                          \
            l->tail_ = l->tail_->next_;                                        \
            break;                                                             \
        }                                                                      \
        l->size_++;                                                            \
    }                                                                          \
                                                                               \
    void N##_push_front(N* l, const T el) {                                    \
        struct _p_##N##_node* new_el = _p_##N##_node_alloc(l);                 \
        SGC_COPY(T##_copy, new_el->data_, el, l->sharing_);                    \
        switch (l->size_) {                                                    \
        case 0:                                                                \
            new_el->next_ = NULL;                                              \
            l->head_ = l->tail_ = new_el;                                      \
            break;                                                             \
        case 1:                                                                \
            l->head_ = new_el;                                                 \
            l->head_->next_ = l->tail_;                                        \
            break;                                                             \
        default:                                                               \
            new_el->next_ = l->head_;                                          \
            l->head_ = new_el;                                                 \
            break;                                                             \
        }                                                                      \
        l->size_++;                                                            \
    }                                                                          \
                                                                               \
    void N##_pop_front(N* l) {                                                 \
        if (l->size_) {                                                        \
            struct _p_##N##_node* tmp = l->head_;                              \
            l->head_ = l->head_->next_;                                        \
            SGC_FREE(T##_free, tmp->data_, l->sharing_)                        \
            sgc_free(tmp);                                                     \
            --l->size_;                                                        \
            if (l->size_ == 0) {                                               \
                l->tail_ = NULL;                                               \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    /* TODO use when creating it erase */                                      \
    __attribute__((                                                            \
        unused)) static void _p_##N##_node_erase(N* l,                         \
                                                 struct _p_##N##_node* n,      \
                                                 struct _p_##N##_node* prev) { \
        if (prev) {                                                            \
            prev->next_ = n->next_;                                            \
        }                                                                      \
        SGC_FREE(T##_free, n->data_, l->sharing_)                              \
        sgc_free(n);                                                           \
        n = NULL;                                                              \
    }                                                                          \
                                                                               \
    /* TODO use when creating it insert */                                     \
    __attribute__((unused)) static void                                        \
        N##_insert_node(struct _p_##N##_node* __restrict__ curr,               \
                        struct _p_##N##_node* __restrict__ const node_new) {   \
        struct _p_##N##_node* tmp = curr->next_;                               \
        node_new->next_ = tmp;                                                 \
        curr->next_ = node_new;                                                \
    }                                                                          \
                                                                               \
    static void _p_##N##_ptr_array_to_list(struct _p_##N##_node** nodes_ptr,   \
                                           N* l) {                             \
        if (!l->size_) {                                                       \
            return;                                                            \
        }                                                                      \
                                                                               \
        l->head_ = nodes_ptr[0];                                               \
                                                                               \
        l->tail_ = nodes_ptr[l->size_ - 1];                                    \
        l->tail_->next_ = NULL;                                                \
                                                                               \
        if (l->size_ > 1) {                                                    \
            l->head_->next_ = nodes_ptr[1];                                    \
        }                                                                      \
                                                                               \
        for (size_t i = 1; i < l->size_ - 1; i++) {                            \
            nodes_ptr[i]->next_ = nodes_ptr[i + 1];                            \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_it_begin(N* l, N##_it* i) {                                       \
        i->curr_ = l->head_;                                                   \
        i->head_ = l->head_;                                                   \
    }                                                                          \
                                                                               \
    void N##_it_cbegin(const N* const l, N##_it* i) {                          \
        i->curr_ = l->head_;                                                   \
        i->head_ = l->head_;                                                   \
    }                                                                          \
                                                                               \
    void N##_it_end(N* l, N##_it* i) {                                         \
        i->curr_ = l->tail_;                                                   \
        i->head_ = l->head_;                                                   \
    }                                                                          \
                                                                               \
    void N##_it_cend(const N* const l, N##_it* i) {                            \
        i->curr_ = l->tail_;                                                   \
        i->head_ = l->head_;                                                   \
    }

#define SGC_INIT_FORWARD_LIST(T, N)                                            \
    SGC_INIT_HEADERS_FORWARD_LIST(T, N)                                        \
    _SGC_INIT_PP_FORWARD_LIST(T, N)                                            \
    _SGC_INIT_UNIQUE_FORWARD_LIST(T, N)                                        \
    _SGC_INIT_COMMON_LIST(T, N)                                                \
    _SGC_INIT_COMMON(N)
