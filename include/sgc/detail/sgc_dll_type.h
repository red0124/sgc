#pragma once
#include <stdlib.h>

#define SGC_INIT_DLL_TYPE_FUNCTIONS(T, S, N)                                   \
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
                tmp_dst->prev_ = curr_dst;                                     \
                curr_dst->next_ = tmp_dst;                                     \
                curr_dst = tmp_dst;                                            \
                curr_src = tmp_src;                                            \
            }                                                                  \
            dst->tail_ = curr_dst;                                             \
            dst->tail_->next_ = dst->head_->prev_ = NULL;                      \
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
        if (!l->shared_) {                                                     \
            T##_copy(&new_el->data_, &el);                                     \
        } else {                                                               \
            new_el->data_ = el;                                                \
        }                                                                      \
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
    void N##_pop_back(struct N* l) {                                           \
        if (l->size_) {                                                        \
            struct N##_node* tmp = l->tail_;                                   \
            l->tail_ = l->tail_->prev_;                                        \
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
    void N##_pop_front(struct N* l) {                                          \
        if (l->size_) {                                                        \
            struct N##_node* tmp = l->head_;                                   \
            l->head_ = l->head_->next_;                                        \
            if (!l->shared_) {                                                 \
                T##_free(&tmp->data_);                                         \
            }                                                                  \
            N##_node_free(l, tmp);                                             \
            if (l->head_) {                                                    \
                l->head_->prev_ = NULL;                                        \
            }                                                                  \
            --l->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_at(struct N* l, const size_t at) {                                  \
        T* ret = NULL;                                                         \
        if (!(at >= l->size_ || l->size_ == 0)) {                              \
            if (at <= l->size_ / 2) {                                          \
                struct N##_node* curr = l->head_;                              \
                for (size_t i = 0; i < at; ++i) {                              \
                    curr = curr->next_;                                        \
                }                                                              \
                ret = &curr->data_;                                            \
            } else {                                                           \
                struct N##_node* curr = l->tail_;                              \
                for (size_t i = 1; i < l->size_ - at; ++i) {                   \
                    curr = curr->prev_;                                        \
                }                                                              \
                ret = &curr->data_;                                            \
            }                                                                  \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    static void N##_node_erase(struct N* l, struct N##_node* n) {              \
        if (n->next_) {                                                        \
            n->next_->prev_ = n->prev_;                                        \
        }                                                                      \
        if (n->prev_) {                                                        \
            n->prev_->next_ = n->next_;                                        \
        }                                                                      \
        if (l->shared_) {                                                      \
            T##_free(&n->data_);                                               \
        }                                                                      \
        N##_node_free(l, n);                                                   \
        n = NULL;                                                              \
    }                                                                          \
                                                                               \
    static struct N##_node* N##_find_node(const struct N* const l,             \
                                          const T el) {                        \
        struct N##_node* location = NULL;                                      \
        for (struct N##_node* curr = l->head_; curr; curr = curr->next_) {     \
            if (T##_equal(&curr->data_, &el)) {                                \
                location = curr;                                               \
                break;                                                         \
            }                                                                  \
        }                                                                      \
        return location;                                                       \
    }                                                                          \
                                                                               \
    int N##_erase(struct N* l, const T el) {                                   \
        struct N##_node* n = N##_find_node(l, el);                             \
        int erase = (n != NULL);                                               \
        if (erase) {                                                           \
            if (l->head_ == n) {                                               \
                N##_pop_front(l);                                              \
            } else if (l->tail_ == n) {                                        \
                N##_pop_back(l);                                               \
            } else {                                                           \
                N##_node_erase(l, n);                                          \
                l->size_--;                                                    \
            }                                                                  \
        }                                                                      \
        return erase;                                                          \
    }                                                                          \
                                                                               \
    /* TODO make this return void */                                           \
    int N##_erase_at(struct N* l, size_t at) {                                 \
        int erase = (at - 1 < l->size_ || at == 0);                            \
        if (at == 0) {                                                         \
            N##_pop_front(l);                                                  \
        } else if (erase) {                                                    \
            struct N##_node* curr = l->head_;                                  \
            if (at <= l->size_ / 2) {                                          \
                curr = l->head_;                                               \
                for (size_t i = 0; i < at; ++i) {                              \
                    curr = curr->next_;                                        \
                }                                                              \
            } else {                                                           \
                curr = l->tail_;                                               \
                for (size_t i = 1; i < l->size_ - at; ++i) {                   \
                    curr = curr->prev_;                                        \
                }                                                              \
            }                                                                  \
            if (curr == l->head_) {                                            \
                l->head_ = l->head_->next_;                                    \
            }                                                                  \
            if (curr == l->tail_) {                                            \
                l->tail_ = l->tail_->prev_;                                    \
            }                                                                  \
            if (!l->shared_) {                                                 \
                T##_free(&curr->data_);                                        \
            }                                                                  \
            N##_node_erase(l, curr);                                           \
            l->size_--;                                                        \
        }                                                                      \
        return erase;                                                          \
    }                                                                          \
                                                                               \
    static void                                                                \
        N##_insert_node(struct N##_node* __restrict__ curr,                    \
                        struct N##_node* __restrict__ const node_new) {        \
        struct N##_node* tmp = curr->next_;                                    \
        node_new->prev_ = curr;                                                \
        node_new->next_ = tmp;                                                 \
        tmp->prev_ = node_new;                                                 \
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
            if (!l->shared_) {                                                 \
                T##_copy(&new_node->data_, &el);                               \
            } else {                                                           \
                new_node->data_ = el;                                          \
            }                                                                  \
            struct N##_node* curr = l->head_;                                  \
            while (compare(&curr->data_, &el) <= 0) {                          \
                curr = curr->next_;                                            \
            }                                                                  \
            N##_insert_node(curr->prev_, new_node);                            \
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
        l->head_->prev_ = NULL;                                                \
                                                                               \
        l->tail_ = nodes_ptr[l->size_ - 1];                                    \
        l->tail_->next_ = NULL;                                                \
                                                                               \
        if (l->size_ > 1) {                                                    \
            l->head_->next_ = nodes_ptr[1];                                    \
            l->tail_->prev_ = nodes_ptr[l->size_ - 2];                         \
        }                                                                      \
                                                                               \
        for (size_t i = 1; i < l->size_ - 1; i++) {                            \
            nodes_ptr[i]->prev_ = nodes_ptr[i - 1];                            \
            nodes_ptr[i]->next_ = nodes_ptr[i + 1];                            \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_iterator_prev(struct N##_iterator* i) {                           \
        i->curr_ = i->curr_->prev_;                                            \
    }                                                                          \
                                                                               \
    void N##_iterator_begin(struct N* l, struct N##_iterator* i) {             \
        i->curr_ = l->head_;                                                   \
    }                                                                          \
                                                                               \
    void N##_iterator_cbegin(const struct N* const l,                          \
                             struct N##_iterator* i) {                         \
        i->curr_ = l->head_;                                                   \
    }                                                                          \
                                                                               \
    void N##_iterator_end(struct N* l, struct N##_iterator* i) {               \
        i->curr_ = l->tail_;                                                   \
    }                                                                          \
                                                                               \
    void N##_iterator_cend(const struct N* const l, struct N##_iterator* i) {  \
        i->curr_ = l->tail_;                                                   \
    }
