#pragma once
#include <stdlib.h>

#define SGC_INIT_COMMON_LIST_TYPE_FUNCTIONS(T, S, N)                           \
                                                                               \
    void N##_free(struct N* l) {                                               \
        struct N##_node* curr = l->_head;                                      \
        struct N##_node* tmp;                                                  \
        for (size_t i = 0; i < l->_size; ++i) {                                \
            tmp = curr;                                                        \
            curr = curr->_next;                                                \
            if (!l->_shared) {                                                 \
                T##_free(&tmp->_data);                                         \
            }                                                                  \
            N##_node_free(l, tmp);                                             \
        }                                                                      \
        l->_head = l->_tail = NULL;                                            \
        l->_size = 0;                                                          \
    }                                                                          \
                                                                               \
    int N##_equal(const struct N* const first, const struct N* const second) { \
        int equal = (first == second);                                         \
        if (equal == 0 && first->_size == second->_size) {                     \
            struct N##_node* curr_first = first->_head;                        \
            struct N##_node* curr_second = second->_head;                      \
            equal = 1;                                                         \
            while (curr_first) {                                               \
                if (!T##_equal(&curr_first->_data, &curr_second->_data)) {     \
                    equal = 0;                                                 \
                    break;                                                     \
                }                                                              \
                curr_first = curr_first->_next;                                \
                curr_second = curr_second->_next;                              \
            }                                                                  \
        }                                                                      \
        return equal;                                                          \
    }                                                                          \
                                                                               \
    T* N##_back(struct N* l) {                                                 \
        T* ret = NULL;                                                         \
        if (l->_size) {                                                        \
            ret = &l->_tail->_data;                                            \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_set_back(struct N* l, T new_el) {                                 \
        if (l->_size) {                                                        \
            SGC_REPLACE(T##_copy, T##_free, l->_tail->_data, new_el,           \
                        l->_shared);                                           \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_front(struct N* l) {                                                \
        T* ret = NULL;                                                         \
        if (l->_size) {                                                        \
            ret = &l->_head->_data;                                            \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    T* N##_set_front(struct N* l, T new_el) {                                  \
        T* ret = NULL;                                                         \
        if (l->_size) {                                                        \
            SGC_REPLACE(T##_copy, T##_free, l->_head->_data, new_el,           \
                        l->_shared);                                           \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_set_at(struct N* l, const size_t at, T new_el) {                  \
        T* el = N##_at(l, at);                                                 \
        if (el) {                                                              \
            SGC_REPLACE(T##_copy, T##_free, *el, new_el, l->_shared);          \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_insert(struct N* l, const size_t at, const T el) {                \
        if (S > 0 && l->_size == S) {                                          \
            return;                                                            \
        }                                                                      \
        if (at == 0) {                                                         \
            N##_push_front(l, el);                                             \
        } else if (at >= l->_size) {                                           \
            N##_push_back(l, el);                                              \
        } else {                                                               \
            struct N##_node* new_node = N##_node_alloc(l);                     \
            if (!l->_shared) {                                                 \
                T##_copy(&new_node->_data, &el);                               \
            } else {                                                           \
                new_node->_data = el;                                          \
            }                                                                  \
            struct N##_node* curr = l->_head;                                  \
            for (size_t i = 0; i < at - 1; ++i) {                              \
                curr = curr->_next;                                            \
            }                                                                  \
            N##_insert_node(curr, new_node);                                   \
            l->_size++;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void N##_memswp(char* i, char* j) {                                 \
        char tmp[sizeof(struct N##_node*)];                                    \
                                                                               \
        memcpy(tmp, i, sizeof(struct N##_node*));                              \
        memcpy(i, j, sizeof(struct N##_node*));                                \
        memcpy(j, tmp, sizeof(struct N##_node*));                              \
    }                                                                          \
                                                                               \
    static inline int N##_compare_node(const void* first, const void* second,  \
                                       int comp(const void*, const void*)) {   \
        struct N##_node* first_ = *(struct N##_node**)first;                   \
        struct N##_node* second_ = *(struct N##_node**)second;                 \
        return comp(&first_->_data, &second_->_data);                          \
    }                                                                          \
                                                                               \
    static void N##_qsort(void* array, size_t array_size,                      \
                          int (*comp)(const void*, const void*)) {             \
        char *i, *j;                                                           \
        size_t thresh = SGC_STACK_THRESH * sizeof(struct N##_node*);           \
        char* array_ = (char*)array;                                           \
        char* limit = array_ + array_size * sizeof(struct N##_node*);          \
        SGC_PREPARE_STACK;                                                     \
                                                                               \
        while (1) {                                                            \
            if ((size_t)(limit - array_) > thresh) {                           \
                i = array_ + sizeof(struct N##_node*);                         \
                j = limit - sizeof(struct N##_node*);                          \
                N##_memswp(((((size_t)(limit - array_)) /                      \
                             sizeof(struct N##_node*)) /                       \
                            2) * sizeof(struct N##_node*) +                    \
                               array_,                                         \
                           array_);                                            \
                if (N##_compare_node(i, j, comp) > 0) {                        \
                    N##_memswp(i, j);                                          \
                }                                                              \
                if (N##_compare_node(array_, j, comp) > 0) {                   \
                    N##_memswp(array_, j);                                     \
                }                                                              \
                if (N##_compare_node(i, array_, comp) > 0) {                   \
                    N##_memswp(i, array_);                                     \
                }                                                              \
                while (1) {                                                    \
                    do {                                                       \
                        i += sizeof(struct N##_node*);                         \
                    } while (N##_compare_node(array_, i, comp) > 0);           \
                    do {                                                       \
                        j -= sizeof(struct N##_node*);                         \
                    } while (N##_compare_node(j, array_, comp) > 0);           \
                    if (i > j) {                                               \
                        break;                                                 \
                    }                                                          \
                    N##_memswp(i, j);                                          \
                }                                                              \
                N##_memswp(array_, j);                                         \
                if (j - array_ > limit - i) {                                  \
                    SGC_STACK_PUSH(array_, j);                                 \
                    array_ = i;                                                \
                } else {                                                       \
                    SGC_STACK_PUSH(i, limit);                                  \
                    limit = j;                                                 \
                }                                                              \
            } else {                                                           \
                for (j = array_, i = j + sizeof(struct N##_node*); i < limit;  \
                     j = i, i += sizeof(struct N##_node*)) {                   \
                    for (; N##_compare_node(j, j + sizeof(struct N##_node*),   \
                                            comp) > 0;                         \
                         j -= sizeof(struct N##_node*)) {                      \
                        N##_memswp(j, j + sizeof(struct N##_node*));           \
                        if (j == array_) {                                     \
                            break;                                             \
                        }                                                      \
                    }                                                          \
                }                                                              \
                if (stackptr != stack) {                                       \
                    SGC_STACK_POP(array_, limit);                              \
                } else {                                                       \
                    break;                                                     \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_sort(struct N* l, int (*comp)(const void*, const void*)) {        \
        struct N##_node** nodes_ptr = (struct N##_node**)sgc_malloc(           \
            sizeof(struct N##_node*) * l->_size);                              \
        struct N##_node* curr = l->_head;                                      \
                                                                               \
        for (size_t i = 0; i < l->_size; i++) {                                \
            nodes_ptr[i] = curr;                                               \
            curr = curr->_next;                                                \
        }                                                                      \
                                                                               \
        N##_qsort(nodes_ptr, l->_size, comp);                                  \
        N##_ptr_array_to_list(nodes_ptr, l);                                   \
        sgc_free(nodes_ptr);                                                   \
    }                                                                          \
                                                                               \
    /* =============== */                                                      \
    /*  LIST ITERATOR  */                                                      \
    /* =============== */                                                      \
                                                                               \
    T* N##_iterator_data(struct N##_iterator i) {                              \
        return &i._curr->_data;                                                \
    }                                                                          \
                                                                               \
    const T* N##_iterator_cdata(const struct N##_iterator i) {                 \
        return &i._curr->_data;                                                \
    }                                                                          \
                                                                               \
    void N##_iterator_next(struct N##_iterator* i) {                           \
        i->_curr = i->_curr->_next;                                            \
    }                                                                          \
                                                                               \
    int N##_iterator_equal(const struct N##_iterator first,                    \
                           const struct N##_iterator second) {                 \
        return first._curr == second._curr;                                    \
    }                                                                          \
                                                                               \
    int N##_iterator_valid(const struct N##_iterator i) {                      \
        return i._curr != NULL;                                                \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_end(struct N* l) {                                 \
        struct N##_iterator i;                                                 \
        N##_iterator_end(l, &i);                                               \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_cend(const struct N* const l) {                    \
        struct N##_iterator i;                                                 \
        N##_iterator_cend(l, &i);                                              \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_begin(struct N* l) {                               \
        struct N##_iterator i;                                                 \
        N##_iterator_begin(l, &i);                                             \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_cbegin(const struct N* const l) {                  \
        struct N##_iterator i;                                                 \
        N##_iterator_cbegin(l, &i);                                            \
        return i;                                                              \
    }

#define SGC_INIT_LIST_TYPE_FUNCTIONS(T, S, N)                                  \
    SGC_INIT_COMMON_LIST_TYPE_FUNCTIONS(T, S, N)                               \
                                                                               \
    void N##_init(struct N* l) {                                               \
        l->_size = 0;                                                          \
        l->_head = l->_tail = NULL;                                            \
        l->_shared = 0;                                                        \
    }                                                                          \
                                                                               \
    static struct N##_node* N##_node_alloc(struct N* l) {                      \
        (void)l;                                                               \
        struct N##_node* ret =                                                 \
            (struct N##_node*)sgc_malloc(sizeof(struct N##_node));             \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    static void N##_node_free(struct N* l, struct N##_node* n) {               \
        (void)l;                                                               \
        free(n);                                                               \
    }

#define SGC_INIT_STATIC_LIST_TYPE_FUNCTIONS(T, S, N)                           \
    SGC_INIT_COMMON_LIST_TYPE_FUNCTIONS(T, S, N)                               \
    void N##_init(struct N* l) {                                               \
        l->_size = 0;                                                          \
        l->_head = l->_tail = NULL;                                            \
        l->_shared = 0;                                                        \
        l->_node_free_list = l->_pool;                                         \
        l->_node_free_list->_next = NULL;                                      \
        for (size_t i = 1; i < S; ++i) {                                       \
            struct N##_node* curr = &l->_pool[i];                              \
            curr->_next = l->_node_free_list;                                  \
            l->_node_free_list = curr;                                         \
        }                                                                      \
    }                                                                          \
                                                                               \
    static struct N##_node* N##_node_alloc(struct N* l) {                      \
        struct N##_node* ret = l->_node_free_list;                             \
        if (ret) {                                                             \
            l->_node_free_list = l->_node_free_list->_next;                    \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    static void N##_node_free(struct N* l, struct N##_node* n) {               \
        n->_next = l->_node_free_list;                                         \
        l->_node_free_list = n;                                                \
    }
