#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_log.h"
#include "detail/sgc_tree_node.h"
#include "detail/sgc_utils.h"

#define SGC_INIT_STATIC_FUNCTIONS_STATIC_MAP(K, V, S, N)                       \
    static struct N##_node* N##_node_begin(struct N##_node* n);                \
    static struct N##_node* N##_node_end(struct N##_node* n);                  \
    static struct N##_node* N##_node_new(struct N* m, const K* const k,        \
                                         const V* const v);                    \
    static size_t N##_stack_size(size_t size);                                 \
    static int N##_is_left_child(const struct N##_node* const n,               \
                                 const struct N##_node* const parent);         \
    static struct N##_node* N##_sibling(const struct N##_node* const n,        \
                                        const struct N##_node* const parent);  \
    static void N##_rotate_left(struct N* m, struct N##_node* parent,          \
                                struct N##_node* gparent);                     \
    static void N##_rotate_right(struct N* m, struct N##_node* parent,         \
                                 struct N##_node* gparent);                    \
    static void N##_rotate_left_right(struct N* m, struct N##_node* n,         \
                                      struct N##_node* parent,                 \
                                      struct N##_node* gparent);               \
    static void N##_rotate_right_left(struct N* m, struct N##_node* n,         \
                                      struct N##_node* parent,                 \
                                      struct N##_node* gparent);               \
    static void N##_rotate(struct N* m, struct N##_node* n,                    \
                           struct N##_node* parent, struct N##_node* gparent); \
    static void N##_corect_tree(struct N* m, struct N##_node* n,               \
                                struct N##_node* p, struct N##_node* gp);      \
    static void N##_check_color(struct N* m, struct N##_node* n);              \
    static void N##_insert_node(struct N* m, K* k, V* v);                      \
    static V* N##_insert_or_get_node(struct N* m, K* k);                       \
    static struct N##_node* N##_find_node(struct N* m, K k);                   \
    static void N##_erase_rebalanse(struct N* m, struct N##_node* n,           \
                                    struct N##_node* p);                       \
    static struct N##_node* N##_erase_node(struct N* m, struct N##_node* n);   \
    static struct N##_node* N##_node_alloc(struct N* l);                       \
    static void N##_node_free(struct N* l, struct N##_node* n);

#define SGC_INIT_HEADERS_STATIC_MAP(K, V, S, N)                                \
                                                                               \
    struct N##_pair {                                                          \
        K key;                                                                 \
        V value;                                                               \
    };                                                                         \
                                                                               \
    struct N##_node {                                                          \
        struct N##_node* parent_;                                              \
        struct N##_node* left_;                                                \
        struct N##_node* right_;                                               \
        struct N##_pair data_;                                                 \
        enum sgc_map_color color_;                                             \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef struct N##_pair N##_type;                                          \
    typedef V N##_value;                                                       \
    typedef K N##_key;                                                         \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t shared_;                                                        \
        size_t shared_key_;                                                    \
        struct N##_node* root_;                                                \
        struct N##_node _pool[S];                                              \
        struct N##_node* _node_free_list;                                      \
    };                                                                         \
                                                                               \
    struct N##_iterator {                                                      \
        struct N##_node* curr_;                                                \
        struct N##_node* next_;                                                \
        int is_valid_;                                                         \
    };                                                                         \
    typedef struct N##_iterator N##_iterator;                                  \
                                                                               \
    struct N##_pair* N##_iterator_data(struct N##_iterator i);                 \
    const struct N##_pair* N##_iterator_cdata(struct N##_iterator i);          \
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
                                                                               \
    void N##_set_share(N* m, int is_shared);                                   \
    void N##_set_share_key(N* m, int is_shared);                               \
    size_t N##_size(const struct N* const m);                                  \
    size_t N##_max();                                                          \
    void N##_init(struct N* m);                                                \
    void N##_free(struct N* m);                                                \
    int N##_equal(const struct N* const first, const struct N* const second);  \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_set_at(struct N* m, K k, V v);                                    \
    V* N##_at(struct N* m, K k);                                               \
    struct N##_iterator N##_find(struct N* m, K k);                            \
    int N##_erase(struct N* m, const K key);                                   \
    int N##_iterator_erase(struct N* m, struct N##_iterator* i);               \
    int N##_empty(const struct N* const m);

#define SGC_INIT_STATIC_MAP(K, V, S, N)                                        \
    SGC_INIT_HEADERS_STATIC_MAP(K, V, S, N)                                    \
    SGC_INIT_STATIC_FUNCTIONS_STATIC_MAP(K, V, S, N)                           \
                                                                               \
    /* ================ */                                                     \
    /*  NODE FUNCTIONS  */                                                     \
    /* ================ */                                                     \
                                                                               \
    static struct N##_node* N##_node_alloc(struct N* m) {                      \
        struct N##_node* ret = m->_node_free_list;                             \
        if (ret) {                                                             \
            m->_node_free_list = m->_node_free_list->right_;                   \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    static void N##_node_free(struct N* m, struct N##_node* n) {               \
        n->right_ = m->_node_free_list;                                        \
        m->_node_free_list = n;                                                \
    }                                                                          \
                                                                               \
    static struct N##_node* N##_node_begin(struct N##_node* n) {               \
        while (n->left_) {                                                     \
            n = n->left_;                                                      \
        }                                                                      \
        return n;                                                              \
    }                                                                          \
                                                                               \
    static struct N##_node* N##_node_end(struct N##_node* n) {                 \
        while (n->right_) {                                                    \
            n = n->right_;                                                     \
        }                                                                      \
        return n;                                                              \
    }                                                                          \
                                                                               \
    static struct N##_node* N##_node_new(struct N* m, const K* const k,        \
                                         const V* const v) {                   \
        struct N##_node* n = N##_node_alloc(m);                                \
                                                                               \
        SGC_COPY(K##_copy, n->data_.key, *k, m->shared_key_);                  \
        SGC_COPY(V##_copy, n->data_.value, *v, m->shared_);                    \
                                                                               \
        n->left_ = n->right_ = SGC_MAP_LEAF;                                   \
        n->color_ = SGC_MAP_RED;                                               \
        return n;                                                              \
    }                                                                          \
                                                                               \
    /* ========== */                                                           \
    /*  ITERATOR  */                                                           \
    /* ========== */                                                           \
                                                                               \
    struct N##_pair* N##_iterator_data(struct N##_iterator i) {                \
        return &i.curr_->data_;                                                \
    }                                                                          \
                                                                               \
    const struct N##_pair* N##_iterator_cdata(struct N##_iterator i) {         \
        return &i.curr_->data_;                                                \
    }                                                                          \
                                                                               \
    void N##_iterator_next(struct N##_iterator* i) {                           \
        if (!i->next_) {                                                       \
            i->is_valid_ = 0;                                                  \
            return;                                                            \
        }                                                                      \
        i->curr_ = i->next_;                                                   \
        if (i->next_->right_) {                                                \
            i->next_ = N##_node_begin(i->next_->right_);                       \
        } else {                                                               \
            struct N##_node* parent = i->next_->parent_;                       \
            while (parent && parent->right_ == i->next_) {                     \
                i->next_ = parent;                                             \
                parent = parent->parent_;                                      \
            }                                                                  \
            if (i->next_->right_ != parent) {                                  \
                i->next_ = parent;                                             \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_iterator_begin(struct N* m, struct N##_iterator* i) {             \
        i->curr_ = SGC_MAP_LEAF;                                               \
        i->next_ = (m->root_) ? N##_node_begin(m->root_) : SGC_MAP_LEAF;       \
        i->is_valid_ = 1;                                                      \
        N##_iterator_next(i);                                                  \
    }                                                                          \
                                                                               \
    void N##_iterator_cbegin(const struct N* const m,                          \
                             struct N##_iterator* i) {                         \
        i->curr_ = SGC_MAP_LEAF;                                               \
        i->next_ = (m->root_) ? N##_node_begin(m->root_) : SGC_MAP_LEAF;       \
        i->is_valid_ = 1;                                                      \
        N##_iterator_next(i);                                                  \
    }                                                                          \
                                                                               \
    void N##_iterator_prev(struct N##_iterator* i) {                           \
        if (!i->curr_) {                                                       \
            i->is_valid_ = 0;                                                  \
            return;                                                            \
        }                                                                      \
        i->next_ = i->curr_;                                                   \
        if (i->curr_->left_) {                                                 \
            i->curr_ = N##_node_end(i->curr_->left_);                          \
        } else {                                                               \
            struct N##_node* parent = i->curr_->parent_;                       \
            while (parent && parent->left_ == i->curr_) {                      \
                i->curr_ = parent;                                             \
                parent = parent->parent_;                                      \
            }                                                                  \
            if (i->curr_->right_ != parent) {                                  \
                i->curr_ = parent;                                             \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_iterator_end(struct N* m, struct N##_iterator* i) {               \
        i->curr_ = (m->root_) ? N##_node_end(m->root_) : SGC_MAP_LEAF;         \
        i->next_ = SGC_MAP_LEAF;                                               \
        i->is_valid_ = (i->curr_) ? 1 : 0;                                     \
    }                                                                          \
                                                                               \
    void N##_iterator_cend(const struct N* const m, struct N##_iterator* i) {  \
        i->curr_ = (m->root_) ? N##_node_end(m->root_) : SGC_MAP_LEAF;         \
        i->next_ = SGC_MAP_LEAF;                                               \
        i->is_valid_ = (i->curr_) ? 1 : 0;                                     \
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
    /*  MAP FUNCTIONS  */                                                      \
    /* =============== */                                                      \
                                                                               \
    size_t N##_max() {                                                         \
        return S;                                                              \
    }                                                                          \
                                                                               \
    void N##_set_share(N* m, int is_shared) {                                  \
        m->shared_ = is_shared;                                                \
    }                                                                          \
                                                                               \
    void N##_set_share_key(N* m, int is_shared) {                              \
        m->shared_key_ = is_shared;                                            \
    }                                                                          \
                                                                               \
    static size_t N##_stack_size(size_t size) {                                \
        size = sgc_log_two(size) + 1;                                          \
        return sizeof(struct N##_node*) * (size * 2);                          \
    }                                                                          \
                                                                               \
    size_t N##_size(const struct N* const m) {                                 \
        return m->size_;                                                       \
    }                                                                          \
                                                                               \
    void N##_init(struct N* m) {                                               \
        m->size_ = 0;                                                          \
        m->root_ = SGC_MAP_LEAF;                                               \
        m->shared_ = m->shared_key_ = 0;                                       \
        m->_node_free_list = m->_pool;                                         \
        m->_node_free_list->right_ = NULL;                                     \
        for (size_t i = 1; i < S; ++i) {                                       \
            struct N##_node* curr = &m->_pool[i];                              \
            curr->right_ = m->_node_free_list;                                 \
            m->_node_free_list = curr;                                         \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_free(struct N* m) {                                               \
        if (!m->size_) {                                                       \
            return;                                                            \
        }                                                                      \
        struct N##_node** stack =                                              \
            (struct N##_node**)sgc_malloc(N##_stack_size(m->size_));           \
                                                                               \
        struct N##_node* curr = m->root_;                                      \
        struct N##_node* tmp = NULL;                                           \
                                                                               \
        size_t stack_size = 0;                                                 \
        while (1) {                                                            \
            if (curr != SGC_MAP_LEAF) {                                        \
                stack[stack_size++] = curr;                                    \
                curr = curr->left_;                                            \
            } else {                                                           \
                if (stack_size == 0) {                                         \
                    break;                                                     \
                }                                                              \
                curr = stack[--stack_size];                                    \
                tmp = curr;                                                    \
                curr = curr->right_;                                           \
                if (!m->shared_) {                                             \
                    V##_free(&tmp->data_.value);                               \
                }                                                              \
                if (!m->shared_key_) {                                         \
                    K##_free(&tmp->data_.key);                                 \
                }                                                              \
                N##_node_free(m, tmp);                                         \
            }                                                                  \
        }                                                                      \
        sgc_free(stack);                                                       \
        m->root_ = SGC_MAP_LEAF;                                               \
        m->size_ = 0;                                                          \
    }                                                                          \
                                                                               \
    int N##_equal(const struct N* const first, const struct N* const second) { \
        int equal = (first == second);                                         \
        if (equal == 0 && first->size_ == second->size_) {                     \
            equal = 1;                                                         \
            struct N##_iterator it_first;                                      \
            N##_iterator_cbegin(first, &it_first);                             \
                                                                               \
            struct N##_iterator it_second;                                     \
            N##_iterator_cbegin(second, &it_second);                           \
                                                                               \
            for (size_t i = 0; i < first->size_; ++i) {                        \
                if ((!K##_equal(&it_first.curr_->data_.key,                    \
                                &it_second.curr_->data_.key) ||                \
                     !V##_equal(&it_first.curr_->data_.value,                  \
                                &it_second.curr_->data_.value))) {             \
                    equal = 0;                                                 \
                    break;                                                     \
                }                                                              \
                N##_iterator_next(&it_first);                                  \
                N##_iterator_next(&it_second);                                 \
            }                                                                  \
        }                                                                      \
        return equal;                                                          \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        N##_init(dst);                                                         \
        dst->size_ = src->size_;                                               \
        dst->root_ = SGC_MAP_LEAF;                                             \
        dst->shared_key_ = src->shared_key_;                                   \
        dst->shared_ = src->shared_;                                           \
                                                                               \
        if (src->size_ != 0) {                                                 \
            dst->root_ = N##_node_alloc(dst);                                  \
                                                                               \
            SGC_COPY(K##_copy, dst->root_->data_.key, src->root_->data_.key,   \
                     src->shared_key_);                                        \
            SGC_COPY(V##_copy, dst->root_->data_.value,                        \
                     src->root_->data_.value, src->shared_);                   \
                                                                               \
            dst->root_->color_ = src->root_->color_;                           \
            dst->root_->left_ = dst->root_->right_ = dst->root_->parent_ =     \
                SGC_MAP_LEAF;                                                  \
                                                                               \
            struct N##_node** stack_src =                                      \
                (struct N##_node**)sgc_malloc(N##_stack_size(src->size_));     \
                                                                               \
            struct N##_node* curr_src = src->root_;                            \
                                                                               \
            struct N##_node** stack_dst =                                      \
                (struct N##_node**)sgc_malloc(N##_stack_size(dst->size_));     \
                                                                               \
            struct N##_node* curr_dst = dst->root_;                            \
                                                                               \
            struct N##_node* tmp = SGC_MAP_LEAF;                               \
                                                                               \
            stack_src[0] = SGC_MAP_LEAF;                                       \
            stack_dst[0] = SGC_MAP_LEAF;                                       \
                                                                               \
            stack_src[1] = src->root_;                                         \
            stack_dst[1] = dst->root_;                                         \
            size_t stack_size = 2;                                             \
                                                                               \
            while (stack_size > 0) {                                           \
                if (!((curr_src->left_ != SGC_MAP_LEAF &&                      \
                       curr_dst->left_ == SGC_MAP_LEAF) ||                     \
                      (curr_src->right_ != SGC_MAP_LEAF &&                     \
                       curr_dst->right_ == SGC_MAP_LEAF))) {                   \
                    --stack_size;                                              \
                    curr_src = stack_src[stack_size];                          \
                    curr_dst = stack_dst[stack_size];                          \
                    continue;                                                  \
                }                                                              \
                                                                               \
                if (curr_src->left_ != SGC_MAP_LEAF &&                         \
                    curr_dst->left_ == SGC_MAP_LEAF) {                         \
                    curr_dst->left_ = N##_node_alloc(dst);                     \
                    tmp = curr_dst->left_;                                     \
                    tmp->parent_ = curr_dst;                                   \
                    curr_src = curr_src->left_;                                \
                } else {                                                       \
                    curr_dst->right_ = N##_node_alloc(dst);                    \
                    tmp = curr_dst->right_;                                    \
                    tmp->parent_ = curr_dst;                                   \
                    curr_src = curr_src->right_;                               \
                }                                                              \
                tmp->left_ = tmp->right_ = SGC_MAP_LEAF;                       \
                curr_dst = tmp;                                                \
                SGC_COPY(K##_copy, curr_dst->data_.key, curr_src->data_.key,   \
                         src->shared_key_);                                    \
                SGC_COPY(V##_copy, curr_dst->data_.value,                      \
                         curr_src->data_.value, src->shared_);                 \
                curr_dst->color_ = curr_src->color_;                           \
                stack_src[stack_size] = curr_src;                              \
                stack_dst[stack_size] = curr_dst;                              \
                ++stack_size;                                                  \
            }                                                                  \
                                                                               \
            sgc_free(stack_src);                                               \
            sgc_free(stack_dst);                                               \
        }                                                                      \
    }                                                                          \
                                                                               \
    static int N##_is_left_child(const struct N##_node* const n,               \
                                 const struct N##_node* const parent) {        \
        int ret = 0;                                                           \
        if (parent) {                                                          \
            ret = (n == parent->left_);                                        \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    static struct N##_node* N##_sibling(const struct N##_node* const n,        \
                                        const struct N##_node* const parent) { \
        struct N##_node* sibling = NULL;                                       \
        if (parent != SGC_MAP_LEAF) {                                          \
            sibling = (n == parent->left_) ? parent->right_ : parent->left_;   \
        }                                                                      \
        return sibling;                                                        \
    }                                                                          \
                                                                               \
    static void N##_rotate_left(struct N* m, struct N##_node* parent,          \
                                struct N##_node* gparent) {                    \
        struct N##_node* left = parent->left_;                                 \
        if (gparent) {                                                         \
            gparent->right_ = left;                                            \
        }                                                                      \
        if (left != SGC_MAP_LEAF) {                                            \
            left->parent_ = gparent;                                           \
        }                                                                      \
        if (gparent == m->root_) {                                             \
            m->root_ = parent;                                                 \
            parent->parent_ = SGC_MAP_LEAF;                                    \
        } else {                                                               \
            struct N##_node* ggparent = gparent->parent_;                      \
            parent->parent_ = ggparent;                                        \
            if (N##_is_left_child(gparent, ggparent)) {                        \
                ggparent->left_ = parent;                                      \
            } else {                                                           \
                ggparent->right_ = parent;                                     \
            }                                                                  \
        }                                                                      \
        parent->left_ = gparent;                                               \
        gparent->parent_ = parent;                                             \
        parent->color_ = SGC_MAP_BLACK;                                        \
        gparent->color_ = SGC_MAP_RED;                                         \
    }                                                                          \
                                                                               \
    static void N##_rotate_right(struct N* m, struct N##_node* parent,         \
                                 struct N##_node* gparent) {                   \
        struct N##_node* right = parent->right_;                               \
        gparent->left_ = right;                                                \
        if (right != SGC_MAP_LEAF) {                                           \
            right->parent_ = gparent;                                          \
        }                                                                      \
        if (gparent == m->root_) {                                             \
            m->root_ = parent;                                                 \
            parent->parent_ = SGC_MAP_LEAF;                                    \
        } else {                                                               \
            struct N##_node* ggparent = gparent->parent_;                      \
            parent->parent_ = ggparent;                                        \
            if (N##_is_left_child(gparent, ggparent)) {                        \
                ggparent->left_ = parent;                                      \
            } else {                                                           \
                ggparent->right_ = parent;                                     \
            }                                                                  \
        }                                                                      \
        parent->right_ = gparent;                                              \
        gparent->parent_ = parent;                                             \
        parent->color_ = SGC_MAP_BLACK;                                        \
        gparent->color_ = SGC_MAP_RED;                                         \
    }                                                                          \
                                                                               \
    static void N##_rotate_left_right(struct N* m, struct N##_node* n,         \
                                      struct N##_node* parent,                 \
                                      struct N##_node* gparent) {              \
        N##_rotate_left(m, n, parent);                                         \
        N##_rotate_right(m, n, gparent);                                       \
    }                                                                          \
                                                                               \
    static void N##_rotate_right_left(struct N* m, struct N##_node* n,         \
                                      struct N##_node* parent,                 \
                                      struct N##_node* gparent) {              \
        N##_rotate_right(m, n, parent);                                        \
        N##_rotate_left(m, n, gparent);                                        \
    }                                                                          \
                                                                               \
    static void N##_rotate(struct N* m, struct N##_node* n,                    \
                           struct N##_node* parent,                            \
                           struct N##_node* gparent) {                         \
        if (N##_is_left_child(n, parent)) {                                    \
            if (N##_is_left_child(parent, gparent)) {                          \
                N##_rotate_right(m, parent, gparent);                          \
                n->color_ = SGC_MAP_RED;                                       \
                parent->color_ = SGC_MAP_BLACK;                                \
                struct N##_node* sibling = parent->right_;                     \
                if (sibling != SGC_MAP_LEAF) {                                 \
                    sibling->color_ = SGC_MAP_RED;                             \
                }                                                              \
            } else {                                                           \
                N##_rotate_right_left(m, n, parent, gparent);                  \
                n->color_ = SGC_MAP_BLACK;                                     \
                n->right_->color_ = SGC_MAP_RED;                               \
                n->left_->color_ = SGC_MAP_RED;                                \
            }                                                                  \
        } else {                                                               \
            if (!N##_is_left_child(parent, gparent)) {                         \
                N##_rotate_left(m, parent, gparent);                           \
                n->color_ = SGC_MAP_RED;                                       \
                parent->color_ = SGC_MAP_BLACK;                                \
                struct N##_node* sibling = parent->right_;                     \
                if (sibling != SGC_MAP_LEAF) {                                 \
                    sibling->color_ = SGC_MAP_RED;                             \
                }                                                              \
            } else {                                                           \
                N##_rotate_left_right(m, n, parent, gparent);                  \
                n->color_ = SGC_MAP_BLACK;                                     \
                n->right_->color_ = SGC_MAP_RED;                               \
                n->left_->color_ = SGC_MAP_RED;                                \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void N##_corect_tree(struct N* m, struct N##_node* n,               \
                                struct N##_node* p, struct N##_node* gp) {     \
        struct N##_node* u = N##_sibling(p, gp);                               \
        if (u == SGC_MAP_LEAF || u->color_ == SGC_MAP_BLACK) {                 \
            N##_rotate(m, n, p, gp);                                           \
        } else {                                                               \
            u->color_ = SGC_MAP_BLACK;                                         \
            p->color_ = SGC_MAP_BLACK;                                         \
            gp->color_ = SGC_MAP_RED;                                          \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void N##_check_color(struct N* m, struct N##_node* n) {             \
        if (n == m->root_) {                                                   \
            m->root_->color_ = SGC_MAP_BLACK;                                  \
            return;                                                            \
        }                                                                      \
        struct N##_node* p = n->parent_;                                       \
        struct N##_node* gp = p->parent_;                                      \
        if (p->color_ == SGC_MAP_RED && n->color_ == SGC_MAP_RED) {            \
            N##_corect_tree(m, n, p, gp);                                      \
        }                                                                      \
        if (gp) {                                                              \
            N##_check_color(m, gp);                                            \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void N##_insert_node(struct N* m, K* k, V* v) {                     \
        if (m->size_ == S) {                                                   \
            return;                                                            \
        }                                                                      \
        struct N##_node* parent = m->root_;                                    \
        struct N##_node* new_node = NULL;                                      \
        for (;;) {                                                             \
            int compare = (K##_compare(&parent->data_.key, k));                \
                                                                               \
            if (compare > 0) {                                                 \
                if (parent->left_ == SGC_MAP_LEAF) {                           \
                    new_node = N##_node_new(m, k, v);                          \
                    parent->left_ = new_node;                                  \
                    m->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->left_;                                        \
            } else if (compare < 0) {                                          \
                if (parent->right_ == SGC_MAP_LEAF) {                          \
                    new_node = N##_node_new(m, k, v);                          \
                    parent->right_ = new_node;                                 \
                    m->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->right_;                                       \
            } else if (!V##_equal(&parent->data_.value, v)) {                  \
                SGC_REPLACE(V##_copy, V##_free, parent->data_.value, *v,       \
                            m->shared_);                                       \
                return;                                                        \
            } else {                                                           \
                return;                                                        \
            }                                                                  \
        }                                                                      \
        new_node->parent_ = parent;                                            \
        N##_check_color(m, new_node);                                          \
    }                                                                          \
                                                                               \
    void N##_set_at(struct N* m, K k, V v) {                                   \
        if (m->root_ == SGC_MAP_LEAF) {                                        \
            struct N##_node* new_node = N##_node_new(m, &k, &v);               \
            new_node->color_ = SGC_MAP_BLACK;                                  \
            new_node->parent_ = SGC_MAP_LEAF;                                  \
            m->root_ = new_node;                                               \
            m->size_ = 1;                                                      \
        } else {                                                               \
            N##_insert_node(m, &k, &v);                                        \
            m->root_->color_ = SGC_MAP_BLACK;                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    static V* N##_insert_or_get_node(struct N* m, K* k) {                      \
        V new_el;                                                              \
        V* v = &new_el;                                                        \
        struct N##_node* parent = m->root_;                                    \
        struct N##_node* new_node = NULL;                                      \
        for (;;) {                                                             \
            int compare = (K##_compare(&parent->data_.key, k));                \
                                                                               \
            if (compare > 0) {                                                 \
                if (parent->left_ == SGC_MAP_LEAF) {                           \
                    V##_init(v);                                               \
                    new_node = N##_node_new(m, k, v);                          \
                    v = &new_node->data_.value;                                \
                    parent->left_ = new_node;                                  \
                    m->size_++;                                                \
                    new_node->parent_ = parent;                                \
                    N##_check_color(m, new_node);                              \
                    break;                                                     \
                }                                                              \
                parent = parent->left_;                                        \
            } else if (compare < 0) {                                          \
                if (parent->right_ == SGC_MAP_LEAF) {                          \
                    V##_init(v);                                               \
                    new_node = N##_node_new(m, k, v);                          \
                    v = &new_node->data_.value;                                \
                    parent->right_ = new_node;                                 \
                    m->size_++;                                                \
                    new_node->parent_ = parent;                                \
                    N##_check_color(m, new_node);                              \
                    break;                                                     \
                }                                                              \
                parent = parent->right_;                                       \
            } else {                                                           \
                v = &parent->data_.value;                                      \
                break;                                                         \
            }                                                                  \
        }                                                                      \
        return v;                                                              \
    }                                                                          \
                                                                               \
    V* N##_at(struct N* m, K k) {                                              \
        V* ret = NULL;                                                         \
        if (m->root_ == SGC_MAP_LEAF) {                                        \
            V v;                                                               \
            V##_init(&v);                                                      \
            struct N##_node* new_node = N##_node_new(m, &k, &v);               \
            new_node->color_ = SGC_MAP_BLACK;                                  \
            new_node->parent_ = SGC_MAP_LEAF;                                  \
            m->root_ = new_node;                                               \
            m->size_ = 1;                                                      \
            ret = &m->root_->data_.value;                                      \
        } else {                                                               \
            ret = N##_insert_or_get_node(m, &k);                               \
            m->root_->color_ = SGC_MAP_BLACK;                                  \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_find(struct N* m, K k) {                           \
        struct N##_iterator ret = {SGC_MAP_LEAF, SGC_MAP_LEAF, 0};             \
        struct N##_node* prev;                                                 \
        if (m->root_) {                                                        \
            struct N##_node* curr = m->root_;                                  \
            while (curr) {                                                     \
                prev = curr;                                                   \
                int compare = (K##_compare(&curr->data_.key, &k));             \
                                                                               \
                if (compare > 0) {                                             \
                    curr = curr->left_;                                        \
                } else if (compare < 0) {                                      \
                    curr = curr->right_;                                       \
                } else {                                                       \
                    ret.next_ = curr;                                          \
                    ret.curr_ = prev;                                          \
                    ret.is_valid_ = 1;                                         \
                    N##_iterator_next(&ret);                                   \
                    break;                                                     \
                }                                                              \
            }                                                                  \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    static struct N##_node* N##_find_node(struct N* m, K k) {                  \
        struct N##_iterator i = N##_find(m, k);                                \
        return i.curr_;                                                        \
    }                                                                          \
                                                                               \
    static void N##_erase_rebalanse(struct N* m, struct N##_node* n,           \
                                    struct N##_node* p) {                      \
        if (p) {                                                               \
            struct N##_node* s;                                                \
            struct N##_node* r;                                                \
            if (p->left_ == n && p->right_) {                                  \
                s = p->right_;                                                 \
                if (s->color_ == SGC_MAP_RED) {                                \
                    N##_rotate_left(m, s, p);                                  \
                    s->color_ = SGC_MAP_BLACK;                                 \
                    p->color_ = SGC_MAP_BLACK;                                 \
                    if (p->right_) {                                           \
                        p->right_->color_ = SGC_MAP_RED;                       \
                    }                                                          \
                } else if ((!s->right_ ||                                      \
                            s->right_->color_ == SGC_MAP_BLACK) &&             \
                           (!s->left_ || s->left_->color_ == SGC_MAP_BLACK)) { \
                    s->color_ = SGC_MAP_RED;                                   \
                    if (p->color_ == SGC_MAP_RED) {                            \
                        p->color_ = SGC_MAP_BLACK;                             \
                    } else {                                                   \
                        N##_erase_rebalanse(m, p, p->parent_);                 \
                    }                                                          \
                } else if (s->right_ && s->right_->color_ == SGC_MAP_RED) {    \
                    r = s->right_;                                             \
                    r->color_ = SGC_MAP_BLACK;                                 \
                    N##_rotate_left(m, s, p);                                  \
                } else if (s->left_ && s->left_->color_ == SGC_MAP_RED) {      \
                    r = s->left_;                                              \
                    N##_rotate_right_left(m, r, s, p);                         \
                }                                                              \
            } else {                                                           \
                s = p->left_;                                                  \
                if (!s) {                                                      \
                    return;                                                    \
                }                                                              \
                if (s->color_ == SGC_MAP_RED) {                                \
                    N##_rotate_right(m, s, p);                                 \
                    s->color_ = SGC_MAP_BLACK;                                 \
                    p->color_ = SGC_MAP_BLACK;                                 \
                    if (p->left_) {                                            \
                        p->left_->color_ = SGC_MAP_RED;                        \
                    }                                                          \
                } else if ((!s->right_ ||                                      \
                            s->right_->color_ == SGC_MAP_BLACK) &&             \
                           (!s->left_ || s->left_->color_ == SGC_MAP_BLACK)) { \
                    s->color_ = SGC_MAP_RED;                                   \
                    N##_erase_rebalanse(m, p, p->parent_);                     \
                } else if (s->left_ && s->left_->color_ == SGC_MAP_RED) {      \
                    r = s->left_;                                              \
                    if (r) {                                                   \
                        r->color_ = SGC_MAP_BLACK;                             \
                    }                                                          \
                    if (p->color_ == SGC_MAP_RED) {                            \
                        p->color_ = SGC_MAP_BLACK;                             \
                    } else {                                                   \
                        N##_rotate_right(m, s, p);                             \
                    }                                                          \
                } else if (s->right_ && s->right_->color_ == SGC_MAP_RED) {    \
                    r = s->right_;                                             \
                    N##_rotate_left_right(m, r, s, p);                         \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    static struct N##_node* N##_erase_node(struct N* m, struct N##_node* n) {  \
        struct N##_node* succ;                                                 \
        struct N##_node* succ_p;                                               \
        struct N##_node* succ_c = SGC_MAP_LEAF;                                \
        if (!n->left_ || !n->right_) {                                         \
            succ = n;                                                          \
        } else {                                                               \
            succ = n->right_;                                                  \
            if (succ) {                                                        \
                while (succ->left_) {                                          \
                    succ = succ->left_;                                        \
                }                                                              \
            } else {                                                           \
                succ = n->left_;                                               \
            }                                                                  \
        }                                                                      \
        if (succ != n) {                                                       \
            if (!m->shared_) {                                                 \
                V##_free(&n->data_.value);                                     \
                V##_copy(&n->data_.value, &succ->data_.value);                 \
                V##_free(&succ->data_.value);                                  \
            } else {                                                           \
                n->data_.value = succ->data_.value;                            \
            }                                                                  \
            if (!m->shared_key_) {                                             \
                K##_free(&n->data_.key);                                       \
                K##_copy(&n->data_.key, &succ->data_.key);                     \
                K##_free(&succ->data_.key);                                    \
            } else {                                                           \
                n->data_.key = succ->data_.key;                                \
            }                                                                  \
            /* relinking nodes would be better */                              \
        }                                                                      \
                                                                               \
        succ_p = succ->parent_;                                                \
        if (succ->left_) {                                                     \
            succ_c = succ->left_;                                              \
            succ_c->parent_ = succ_p;                                          \
        } else if (succ->right_) {                                             \
            succ_c = succ->right_;                                             \
            succ_c->parent_ = succ_p;                                          \
        }                                                                      \
        if (succ_p) {                                                          \
            if (succ_p->left_ == succ) {                                       \
                succ_p->left_ = succ_c;                                        \
            } else {                                                           \
                succ_p->right_ = succ_c;                                       \
            }                                                                  \
        } else {                                                               \
            m->root_ = (m->root_->left_) ? m->root_->left_ : m->root_->right_; \
        }                                                                      \
                                                                               \
        if ((succ_c && succ_c->color_ == SGC_MAP_RED) ||                       \
            succ->color_ == SGC_MAP_RED) {                                     \
            if (succ_c) {                                                      \
                succ_c->color_ = SGC_MAP_BLACK;                                \
            }                                                                  \
        } else {                                                               \
            N##_erase_rebalanse(m, succ_c, succ_p);                            \
        }                                                                      \
        if (m->root_) {                                                        \
            m->root_->color_ = SGC_MAP_BLACK;                                  \
        }                                                                      \
        --m->size_;                                                            \
        return succ;                                                           \
    }                                                                          \
                                                                               \
    int N##_erase(struct N* m, const K key) {                                  \
        struct N##_node* n = N##_find_node(m, key);                            \
        int ret = (n) ? 1 : 0;                                                 \
        if (ret) {                                                             \
            N##_node_free(m, N##_erase_node(m, n));                            \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    int N##_iterator_erase(struct N* m, struct N##_iterator* i) {              \
        struct N##_iterator tmp = {i->curr_, i->next_, i->is_valid_};          \
        N##_iterator_next(&tmp);                                               \
        int ret = i->is_valid_;                                                \
        if (ret) {                                                             \
            N##_node_free(m, N##_erase_node(m, i->curr_));                     \
        }                                                                      \
        i->curr_ = tmp.curr_;                                                  \
        i->next_ = tmp.next_;                                                  \
        i->is_valid_ = tmp.is_valid_;                                          \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    int N##_empty(const struct N* const m) {                                   \
        return m->size_ == 0;                                                  \
    }
