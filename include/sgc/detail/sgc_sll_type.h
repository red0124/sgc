#pragma once
#include <stdlib.h>

#define SGC_INIT_SLL_TYPE_FUNCTIONS(T, S, N)                                   \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        dst->shared_ = src->shared_;                                           \
        N##_init(dst);                                                         \
        if (src->size_ != 0) {                                                 \
            dst->head_ = N##_node_alloc(dst);                                  \
            SGC_COPY(T##_copy, dst->head_->data_, src->head_->data_,           \
                     src->shared_);                                            \
            struct N##_node* curr_src = src->head_;                            \
            struct N##_node* curr_dst = dst->head_;                            \
            struct N##_node* tmp_src = NULL;                                   \
            struct N##_node* tmp_dst = NULL;                                   \
            while (curr_src) {                                                 \
                tmp_src = curr_src->next_;                                     \
                if (!tmp_src) {                                                \
                    break;                                                     \
                }                                                              \
                tmp_dst = N##_node_alloc(dst);                                 \
                SGC_COPY(T##_copy, tmp_dst->data_, tmp_src->data_,             \
                         src->shared_);                                        \
                curr_dst->next_ = tmp_dst;                                     \
                curr_dst = tmp_dst;                                            \
                curr_src = tmp_src;                                            \
            }                                                                  \
            dst->tail_ = curr_dst;                                             \
            dst->tail_->next_ = NULL;                                          \
        } else {                                                               \
            dst->head_ = dst->tail_ = NULL;                                    \
        }                                                                      \
        dst->size_ = src->size_;                                               \
    }                                                                          \
                                                                               \
    void N##_push_back(struct N* l, T el) {                                    \
        if (S > 0 && l->size_ == S) {                                          \
            return;                                                            \
        }                                                                      \
        struct N##_node* new_el = N##_node_alloc(l);                           \
        SGC_COPY(T##_copy, new_el->data_, el, l->shared_);                     \
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
    static struct N##_node* N##_prev(struct N##_node* head,                    \
                                     struct N##_node* n) {                     \
        struct N##_node* curr = (head == n) ? NULL : head;                     \
        struct N##_node* next = curr;                                          \
        while (next && next != n) {                                            \
            curr = next;                                                       \
            next = next->next_;                                                \
        }                                                                      \
        return curr;                                                           \
    }                                                                          \
                                                                               \
    void N##_pop_back(struct N* l) {                                           \
        if (l->size_) {                                                        \
            struct N##_node* tmp = l->tail_;                                   \
            l->tail_ = N##_prev(l->head_, l->tail_);                           \
            if (!l->shared_) {                                                 \
                T##_free(&tmp->data_);                                         \
            }                                                                  \
            N##_node_free(l, tmp);                                             \
            if (l->tail_) {                                                    \
                l->tail_->next_ = NULL;                                        \
            }                                                                  \
            --l->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_push_front(struct N* l, const T el) {                             \
        if (S > 0 && l->size_ == S) {                                          \
            return;                                                            \
        }                                                                      \
        struct N##_node* new_el = N##_node_alloc(l);                           \
        SGC_COPY(T##_copy, new_el->data_, el, l->shared_);                     \
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
    void N##_pop_front(struct N* l) {                                          \
        if (l->size_) {                                                        \
            struct N##_node* tmp = l->head_;                                   \
            l->head_ = l->head_->next_;                                        \
            if (!l->shared_) {                                                 \
                T##_free(&tmp->data_);                                         \
            }                                                                  \
            N##_node_free(l, tmp);                                             \
            --l->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_at(struct N* l, const size_t at) {                                  \
        T* ret = NULL;                                                         \
        if (!(at >= l->size_ || l->size_ == 0)) {                              \
            struct N##_node* curr = l->head_;                                  \
            for (size_t i = 0; i < at; ++i) {                                  \
                curr = curr->next_;                                            \
            }                                                                  \
            ret = &curr->data_;                                                \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    static void N##_node_erase(struct N* l, struct N##_node* n,                \
                               struct N##_node* prev) {                        \
        if (prev) {                                                            \
            prev->next_ = n->next_;                                            \
        }                                                                      \
        if (!l->shared_) {                                                     \
            T##_free(&n->data_);                                               \
        }                                                                      \
        N##_node_free(l, n);                                                   \
        n = NULL;                                                              \
    }                                                                          \
                                                                               \
    int N##_erase(struct N* l, const T el) {                                   \
        int found = 0;                                                         \
        struct N##_node* curr = l->head_;                                      \
        struct N##_node* prev = curr;                                          \
        if (!curr) {                                                           \
            return found;                                                      \
        }                                                                      \
        while (curr) {                                                         \
            if (T##_equal(&curr->data_, &el)) {                                \
                found = 1;                                                     \
                break;                                                         \
            }                                                                  \
            prev = curr;                                                       \
            curr = curr->next_;                                                \
        }                                                                      \
        if (found) {                                                           \
            if (curr == l->head_) {                                            \
                N##_pop_front(l);                                              \
            } else if (curr == l->tail_) {                                     \
                N##_pop_back(l);                                               \
            } else {                                                           \
                N##_node_erase(l, curr, prev);                                 \
                l->size_--;                                                    \
            }                                                                  \
        }                                                                      \
        return found;                                                          \
    }                                                                          \
                                                                               \
    int N##_erase_at(struct N* l, size_t at) {                                 \
        int erase = (at - 1 < l->size_ || at == 0);                            \
        if (at == 0) {                                                         \
            N##_pop_front(l);                                                  \
        } else if (erase) {                                                    \
            struct N##_node* curr = l->head_;                                  \
            struct N##_node* prev = curr;                                      \
            for (size_t i = 0; i < at; ++i) {                                  \
                prev = curr;                                                   \
                curr = curr->next_;                                            \
            }                                                                  \
            if (curr == l->head_) {                                            \
                l->head_ = l->head_->next_;                                    \
            }                                                                  \
            if (curr == l->tail_) {                                            \
                l->tail_ = prev;                                               \
            }                                                                  \
            N##_node_erase(l, curr, prev);                                     \
            l->size_--;                                                        \
        }                                                                      \
        return erase;                                                          \
    }                                                                          \
                                                                               \
    static void                                                                \
        N##_insert_node(struct N##_node* __restrict__ curr,                    \
                        struct N##_node* __restrict__ const node_new) {        \
        struct N##_node* tmp = curr->next_;                                    \
        node_new->next_ = tmp;                                                 \
        curr->next_ = node_new;                                                \
    }                                                                          \
                                                                               \
    int N##_insert_sorted(struct N* l, const T el,                             \
                          int (*compare)(const T* const, const T* const)) {    \
        if (S > 0 && l->size_ == S) {                                          \
            return 0;                                                          \
        }                                                                      \
        int sorted = 1;                                                        \
        if (l->head_ == NULL) {                                                \
            N##_push_front(l, el);                                             \
        } else if (l->tail_ && l->head_ != l->tail_ &&                         \
                   compare(&l->tail_->data_, &l->head_->data_) <= 0) {         \
            sorted = 0;                                                        \
        } else if ((compare)(&l->head_->data_, &el) > 0) {                     \
            N##_push_front(l, el);                                             \
        } else if ((compare)(&l->tail_->data_, &el) <= 0) {                    \
            N##_push_back(l, el);                                              \
        } else {                                                               \
            struct N##_node* new_node = N##_node_alloc(l);                     \
            SGC_COPY(T##_copy, new_node->data_, el, l->shared_);               \
            struct N##_node* curr = l->head_;                                  \
            struct N##_node* prev = curr;                                      \
            while (compare(&curr->data_, &el) <= 0) {                          \
                prev = curr;                                                   \
                curr = curr->next_;                                            \
            }                                                                  \
            N##_insert_node(prev, new_node);                                   \
            l->size_++;                                                        \
        }                                                                      \
        return sorted;                                                         \
    }                                                                          \
                                                                               \
    static void N##_ptr_array_to_list(struct N##_node** nodes_ptr,             \
                                      struct N* l) {                           \
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
    void N##_iterator_begin(struct N* l, struct N##_iterator* i) {             \
        i->curr_ = l->head_;                                                   \
        i->head_ = l->head_;                                                   \
    }                                                                          \
                                                                               \
    void N##_iterator_cbegin(const struct N* const l,                          \
                             struct N##_iterator* i) {                         \
        i->curr_ = l->head_;                                                   \
        i->head_ = l->head_;                                                   \
    }                                                                          \
                                                                               \
    void N##_iterator_end(struct N* l, struct N##_iterator* i) {               \
        i->curr_ = l->tail_;                                                   \
        i->head_ = l->head_;                                                   \
    }                                                                          \
                                                                               \
    void N##_iterator_cend(const struct N* const l, struct N##_iterator* i) {  \
        i->curr_ = l->tail_;                                                   \
        i->head_ = l->head_;                                                   \
    }                                                                          \
                                                                               \
    void N##_iterator_prev(struct N##_iterator* i) {                           \
        i->curr_ = N##_prev(i->head_, i->curr_);                               \
    }
