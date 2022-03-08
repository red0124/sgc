#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_log.h"
#include "detail/sgc_tree_node.h"
#include "detail/sgc_utils.h"

#define SGC_INIT_STATIC_FUNCTIONS_SET(V, N)                                    \
    static struct N##_node* N##_node_begin(struct N##_node* n);                \
    static struct N##_node* N##_node_end(struct N##_node* n);                  \
    static struct N##_node* N##_node_new(const V* const v, size_t is_shared);  \
    static size_t N##_stack_size(size_t size);                                 \
    static int N##_is_left_child(const struct N##_node* const n,               \
                                 const struct N##_node* const parent);         \
    static struct N##_node* N##_sibling(const struct N##_node* const n,        \
                                        const struct N##_node* const parent);  \
    static void N##_rotate_left(struct N* s, struct N##_node* parent,          \
                                struct N##_node* gparent);                     \
    static void N##_rotate_right(struct N* s, struct N##_node* parent,         \
                                 struct N##_node* gparent);                    \
    static void N##_rotate_left_right(struct N* s, struct N##_node* n,         \
                                      struct N##_node* parent,                 \
                                      struct N##_node* gparent);               \
    static void N##_rotate_right_left(struct N* s, struct N##_node* n,         \
                                      struct N##_node* parent,                 \
                                      struct N##_node* gparent);               \
    static void N##_rotate(struct N* s, struct N##_node* n,                    \
                           struct N##_node* parent, struct N##_node* gparent); \
    static void N##_corect_tree(struct N* s, struct N##_node* n,               \
                                struct N##_node* p, struct N##_node* gp);      \
    static void N##_check_color(struct N* s, struct N##_node* n);              \
    static void N##_insert_node(struct N* s, V* v);                            \
    static void N##_insert_multiple_node(struct N* s, V* v);                   \
    struct N##_iterator N##_find(struct N* s, V v);                            \
    static struct N##_node* N##_find_node(struct N* s, V v);                   \
    static void N##_erase_rebalanse(struct N* m, struct N##_node* n,           \
                                    struct N##_node* p);                       \
    static struct N##_node* N##_erase_node(struct N* m, struct N##_node* n);

#define SGC_INIT_HEADERS_SET(V, N)                                             \
                                                                               \
    struct N##_node {                                                          \
        struct N##_node* parent_;                                              \
        struct N##_node* left_;                                                \
        struct N##_node* right_;                                               \
        V _value;                                                              \
        enum sgc_map_color color_;                                             \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef V N##_type;                                                        \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t shared_;                                                        \
        struct N##_node* root_;                                                \
    };                                                                         \
                                                                               \
    void N##_set_share(N* s, int is_shared);                                   \
                                                                               \
    struct N##_iterator {                                                      \
        struct N##_node* curr_;                                                \
        struct N##_node* next_;                                                \
        int is_valid_;                                                         \
    };                                                                         \
                                                                               \
    typedef struct N##_iterator N##_iterator;                                  \
                                                                               \
    V* N##_iterator_data(struct N##_iterator i);                               \
    const V* N##_iterator_cdata(struct N##_iterator i);                        \
    void N##_iterator_next(struct N##_iterator* i);                            \
    void N##_iterator_begin(struct N* s, struct N##_iterator* i);              \
    void N##_iterator_cbegin(const struct N* const s, struct N##_iterator* i); \
    void N##_iterator_prev(struct N##_iterator* i);                            \
    void N##_iterator_end(struct N* s, struct N##_iterator* i);                \
    void N##_iterator_cend(const struct N* const s, struct N##_iterator* i);   \
    struct N##_iterator N##_begin(struct N* m);                                \
    struct N##_iterator N##_cbegin(const struct N* const m);                   \
    struct N##_iterator N##_end(struct N* m);                                  \
    struct N##_iterator N##_cend(const struct N* const m);                     \
    int N##_iterator_equal(const struct N##_iterator first,                    \
                           const struct N##_iterator second);                  \
    int N##_iterator_valid(const struct N##_iterator i);                       \
    size_t N##_size(const struct N* const s);                                  \
    void N##_init(struct N* s);                                                \
    void N##_free(struct N* s);                                                \
    int N##_equal(const struct N* const first, const struct N* const second);  \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_insert(struct N* s, V v);                                         \
    void N##_insert_multiple(struct N* s, V v);                                \
    int N##_erase(struct N* m, const V value);                                 \
    int N##_iterator_erase(struct N* m, struct N##_iterator* i);               \
    int N##_empty(const struct N* const m);

#define SGC_INIT_SET(V, N)                                                     \
    SGC_INIT_HEADERS_SET(V, N)                                                 \
    SGC_INIT_STATIC_FUNCTIONS_SET(V, N)                                        \
                                                                               \
    /* ================ */                                                     \
    /*  NODE FUNCTIONS  */                                                     \
    /* ================ */                                                     \
                                                                               \
    void N##_set_share(N* s, int is_shared) {                                  \
        s->shared_ = is_shared;                                                \
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
    static struct N##_node* N##_node_new(const V* const v, size_t is_shared) { \
        struct N##_node* n =                                                   \
            (struct N##_node*)sgc_malloc(sizeof(struct N##_node));             \
        SGC_COPY(V##_copy, n->_value, *v, is_shared);                          \
        n->left_ = n->right_ = SGC_MAP_LEAF;                                   \
        n->color_ = SGC_MAP_RED;                                               \
        return n;                                                              \
    }                                                                          \
                                                                               \
    /* ========== */                                                           \
    /*  ITERATOR  */                                                           \
    /* ========== */                                                           \
                                                                               \
    V* N##_iterator_data(struct N##_iterator i) {                              \
        return &i.curr_->_value;                                               \
    }                                                                          \
                                                                               \
    const V* N##_iterator_cdata(struct N##_iterator i) {                       \
        return &i.curr_->_value;                                               \
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
    void N##_iterator_begin(struct N* s, struct N##_iterator* i) {             \
        i->curr_ = SGC_MAP_LEAF;                                               \
        i->next_ = (s->root_) ? N##_node_begin(s->root_) : SGC_MAP_LEAF;       \
        i->is_valid_ = 1;                                                      \
        N##_iterator_next(i);                                                  \
    }                                                                          \
                                                                               \
    void N##_iterator_cbegin(const struct N* const s,                          \
                             struct N##_iterator* i) {                         \
        i->curr_ = SGC_MAP_LEAF;                                               \
        i->next_ = (s->root_) ? N##_node_begin(s->root_) : SGC_MAP_LEAF;       \
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
    void N##_iterator_end(struct N* s, struct N##_iterator* i) {               \
        i->curr_ = (s->root_) ? N##_node_end(s->root_) : SGC_MAP_LEAF;         \
        i->next_ = SGC_MAP_LEAF;                                               \
        i->is_valid_ = (i->curr_) ? 1 : 0;                                     \
    }                                                                          \
                                                                               \
    void N##_iterator_cend(const struct N* const s, struct N##_iterator* i) {  \
        i->curr_ = (s->root_) ? N##_node_end(s->root_) : SGC_MAP_LEAF;         \
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
    /*  SET FUNCTIONS  */                                                      \
    /* =============== */                                                      \
                                                                               \
    static size_t N##_stack_size(size_t size) {                                \
        size = sgc_log_two(size) + 1;                                          \
        return sizeof(struct N##_node*) * (size * 2);                          \
    }                                                                          \
                                                                               \
    size_t N##_size(const struct N* const s) {                                 \
        return s->size_;                                                       \
    }                                                                          \
                                                                               \
    void N##_init(struct N* s) {                                               \
        s->size_ = 0;                                                          \
        s->root_ = SGC_MAP_LEAF;                                               \
        s->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    void N##_free(struct N* s) {                                               \
        if (!s->size_) {                                                       \
            return;                                                            \
        }                                                                      \
        struct N##_node** stack =                                              \
            (struct N##_node**)sgc_malloc(N##_stack_size(s->size_));           \
                                                                               \
        struct N##_node* curr = s->root_;                                      \
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
                if (!s->shared_) {                                             \
                    V##_free(&tmp->_value);                                    \
                }                                                              \
                sgc_free(tmp);                                                 \
            }                                                                  \
        }                                                                      \
        sgc_free(stack);                                                       \
        s->root_ = SGC_MAP_LEAF;                                               \
        s->size_ = 0;                                                          \
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
                if (!V##_equal(&it_first.curr_->_value,                        \
                               &it_second.curr_->_value)) {                    \
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
        dst->size_ = src->size_;                                               \
        dst->root_ = SGC_MAP_LEAF;                                             \
        dst->shared_ = src->shared_;                                           \
                                                                               \
        if (src->size_ != 0) {                                                 \
            dst->root_ =                                                       \
                (struct N##_node*)sgc_malloc(sizeof(struct N##_node));         \
                                                                               \
            SGC_COPY(V##_copy, dst->root_->_value, src->root_->_value,         \
                     dst->shared_);                                            \
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
                    curr_dst->left_ =                                          \
                        (struct N##_node*)sgc_malloc(sizeof(struct N##_node)); \
                    tmp = curr_dst->left_;                                     \
                    tmp->parent_ = curr_dst;                                   \
                    curr_src = curr_src->left_;                                \
                } else {                                                       \
                    curr_dst->right_ =                                         \
                        (struct N##_node*)sgc_malloc(sizeof(struct N##_node)); \
                    tmp = curr_dst->right_;                                    \
                    tmp->parent_ = curr_dst;                                   \
                    curr_src = curr_src->right_;                               \
                }                                                              \
                tmp->left_ = tmp->right_ = SGC_MAP_LEAF;                       \
                curr_dst = tmp;                                                \
                SGC_COPY(V##_copy, curr_dst->_value, curr_src->_value,         \
                         dst->shared_);                                        \
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
    static void N##_rotate_left(struct N* s, struct N##_node* parent,          \
                                struct N##_node* gparent) {                    \
        struct N##_node* left = parent->left_;                                 \
        if (gparent) {                                                         \
            gparent->right_ = left;                                            \
        }                                                                      \
        if (left != SGC_MAP_LEAF) {                                            \
            left->parent_ = gparent;                                           \
        }                                                                      \
        if (gparent == s->root_) {                                             \
            s->root_ = parent;                                                 \
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
    static void N##_rotate_right(struct N* s, struct N##_node* parent,         \
                                 struct N##_node* gparent) {                   \
        struct N##_node* right = parent->right_;                               \
        gparent->left_ = right;                                                \
        if (right != SGC_MAP_LEAF) {                                           \
            right->parent_ = gparent;                                          \
        }                                                                      \
        if (gparent == s->root_) {                                             \
            s->root_ = parent;                                                 \
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
    static void N##_rotate_left_right(struct N* s, struct N##_node* n,         \
                                      struct N##_node* parent,                 \
                                      struct N##_node* gparent) {              \
        N##_rotate_left(s, n, parent);                                         \
        N##_rotate_right(s, n, gparent);                                       \
    }                                                                          \
                                                                               \
    static void N##_rotate_right_left(struct N* s, struct N##_node* n,         \
                                      struct N##_node* parent,                 \
                                      struct N##_node* gparent) {              \
        N##_rotate_right(s, n, parent);                                        \
        N##_rotate_left(s, n, gparent);                                        \
    }                                                                          \
                                                                               \
    static void N##_rotate(struct N* s, struct N##_node* n,                    \
                           struct N##_node* parent,                            \
                           struct N##_node* gparent) {                         \
        if (N##_is_left_child(n, parent)) {                                    \
            if (N##_is_left_child(parent, gparent)) {                          \
                N##_rotate_right(s, parent, gparent);                          \
                n->color_ = SGC_MAP_RED;                                       \
                parent->color_ = SGC_MAP_BLACK;                                \
                struct N##_node* sibling = parent->right_;                     \
                if (sibling != SGC_MAP_LEAF) {                                 \
                    sibling->color_ = SGC_MAP_RED;                             \
                }                                                              \
            } else {                                                           \
                N##_rotate_right_left(s, n, parent, gparent);                  \
                n->color_ = SGC_MAP_BLACK;                                     \
                n->right_->color_ = SGC_MAP_RED;                               \
                n->left_->color_ = SGC_MAP_RED;                                \
            }                                                                  \
        } else {                                                               \
            if (!N##_is_left_child(parent, gparent)) {                         \
                N##_rotate_left(s, parent, gparent);                           \
                n->color_ = SGC_MAP_RED;                                       \
                parent->color_ = SGC_MAP_BLACK;                                \
                struct N##_node* sibling = parent->right_;                     \
                if (sibling != SGC_MAP_LEAF) {                                 \
                    sibling->color_ = SGC_MAP_RED;                             \
                }                                                              \
            } else {                                                           \
                N##_rotate_left_right(s, n, parent, gparent);                  \
                n->color_ = SGC_MAP_BLACK;                                     \
                n->right_->color_ = SGC_MAP_RED;                               \
                n->left_->color_ = SGC_MAP_RED;                                \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void N##_corect_tree(struct N* s, struct N##_node* n,               \
                                struct N##_node* p, struct N##_node* gp) {     \
        struct N##_node* u = N##_sibling(p, gp);                               \
        if (u == SGC_MAP_LEAF || u->color_ == SGC_MAP_BLACK) {                 \
            N##_rotate(s, n, p, gp);                                           \
        } else {                                                               \
            u->color_ = SGC_MAP_BLACK;                                         \
            p->color_ = SGC_MAP_BLACK;                                         \
            gp->color_ = SGC_MAP_RED;                                          \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void N##_check_color(struct N* s, struct N##_node* n) {             \
        if (n == s->root_) {                                                   \
            s->root_->color_ = SGC_MAP_BLACK;                                  \
            return;                                                            \
        }                                                                      \
        struct N##_node* p = n->parent_;                                       \
        struct N##_node* gp = p->parent_;                                      \
        if (p->color_ == SGC_MAP_RED && n->color_ == SGC_MAP_RED) {            \
            N##_corect_tree(s, n, p, gp);                                      \
        }                                                                      \
        if (gp) {                                                              \
            N##_check_color(s, gp);                                            \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void N##_insert_node(struct N* s, V* v) {                           \
        struct N##_node* parent = s->root_;                                    \
        struct N##_node* new_node = NULL;                                      \
        for (;;) {                                                             \
            int compare = (V##_compare(&parent->_value, v));                   \
                                                                               \
            if (compare > 0) {                                                 \
                if (parent->left_ == SGC_MAP_LEAF) {                           \
                    new_node = N##_node_new(v, s->shared_);                    \
                    parent->left_ = new_node;                                  \
                    s->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->left_;                                        \
            } else if (compare < 0) {                                          \
                if (parent->right_ == SGC_MAP_LEAF) {                          \
                    new_node = N##_node_new(v, s->shared_);                    \
                    parent->right_ = new_node;                                 \
                    s->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->right_;                                       \
            } else if (!V##_equal(&parent->_value, v)) {                       \
                SGC_REPLACE(V##_copy, V##_free, parent->_value, *v,            \
                            s->shared_);                                       \
                return;                                                        \
            } else {                                                           \
                return;                                                        \
            }                                                                  \
        }                                                                      \
        new_node->parent_ = parent;                                            \
        N##_check_color(s, new_node);                                          \
    }                                                                          \
                                                                               \
    void N##_insert(struct N* s, V v) {                                        \
        if (s->root_ == SGC_MAP_LEAF) {                                        \
            struct N##_node* new_node = N##_node_new(&v, s->shared_);          \
            new_node->color_ = SGC_MAP_BLACK;                                  \
            new_node->parent_ = SGC_MAP_LEAF;                                  \
            s->root_ = new_node;                                               \
            s->size_ = 1;                                                      \
        } else {                                                               \
            N##_insert_node(s, &v);                                            \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void N##_insert_multiple_node(struct N* s, V* v) {                  \
        struct N##_node* parent = s->root_;                                    \
        struct N##_node* new_node = NULL;                                      \
        for (;;) {                                                             \
            int compare = (V##_compare(&parent->_value, v));                   \
                                                                               \
            if (compare > 0) {                                                 \
                if (parent->left_ == SGC_MAP_LEAF) {                           \
                    new_node = N##_node_new(v, s->shared_);                    \
                    parent->left_ = new_node;                                  \
                    s->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->left_;                                        \
            } else {                                                           \
                if (parent->right_ == SGC_MAP_LEAF) {                          \
                    new_node = N##_node_new(v, s->shared_);                    \
                    parent->right_ = new_node;                                 \
                    s->size_++;                                                \
                    break;                                                     \
                }                                                              \
                parent = parent->right_;                                       \
            }                                                                  \
        }                                                                      \
        new_node->parent_ = parent;                                            \
        N##_check_color(s, new_node);                                          \
    }                                                                          \
                                                                               \
    void N##_insert_multiple(struct N* s, V v) {                               \
        if (s->root_ == SGC_MAP_LEAF) {                                        \
            struct N##_node* new_node = N##_node_new(&v, s->shared_);          \
            new_node->color_ = SGC_MAP_BLACK;                                  \
            new_node->parent_ = SGC_MAP_LEAF;                                  \
            s->root_ = new_node;                                               \
            s->size_ = 1;                                                      \
        } else {                                                               \
            N##_insert_multiple_node(s, &v);                                   \
        }                                                                      \
    }                                                                          \
                                                                               \
    struct N##_iterator N##_find(struct N* s, V v) {                           \
        struct N##_iterator ret = {SGC_MAP_LEAF, SGC_MAP_LEAF, 0};             \
        struct N##_node* prev;                                                 \
        if (s->root_) {                                                        \
            struct N##_node* curr = s->root_;                                  \
            while (curr) {                                                     \
                prev = curr;                                                   \
                int compare = (V##_compare(&curr->_value, &v));                \
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
    static struct N##_node* N##_find_node(struct N* s, V v) {                  \
        struct N##_iterator i = N##_find(s, v);                                \
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
                    if (p->color_ == SGC_MAP_RED) {                            \
                        p->color_ = SGC_MAP_BLACK;                             \
                    } else {                                                   \
                        N##_erase_rebalanse(m, p, p->parent_);                 \
                    }                                                          \
                } else if (s->left_ && s->left_->color_ == SGC_MAP_RED) {      \
                    r = s->left_;                                              \
                    if (r) {                                                   \
                        r->color_ = SGC_MAP_BLACK;                             \
                    }                                                          \
                    N##_rotate_right(m, s, p);                                 \
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
            V##_copy(&n->_value, &succ->_value);                               \
            if (!m->shared_) {                                                 \
                V##_free(&succ->_value);                                       \
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
    int N##_erase(struct N* m, const V value) {                                \
        struct N##_node* n = N##_find_node(m, value);                          \
        int ret = (n) ? 1 : 0;                                                 \
        if (ret) {                                                             \
            if (!m->shared_) {                                                 \
                V##_free(&n->_value);                                          \
            }                                                                  \
            sgc_free(N##_erase_node(m, n));                                    \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    int N##_iterator_erase(struct N* m, struct N##_iterator* i) {              \
        struct N##_iterator tmp = {i->curr_, i->next_, i->is_valid_};          \
        N##_iterator_next(&tmp);                                               \
        int ret = i->is_valid_;                                                \
        if (ret) {                                                             \
            if (!m->shared_) {                                                 \
                V##_free(&i->curr_->_value);                                   \
            }                                                                  \
            sgc_free(N##_erase_node(m, i->curr_));                             \
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
