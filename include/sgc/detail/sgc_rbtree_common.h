#pragma once
#include <stdlib.h>

// TODO rename
#define SGC_MAP_LEAF NULL

// TODO rename
enum sgc_map_color {
    SGC_MAP_RED,
    SGC_MAP_BLACK,
};

#define _SGC_INIT_RBTREE_TYPE_FUNCTIONS(K, N)                                  \
    bool N##_erase(struct N* m, const K key) {                                 \
        struct N##_node* n = _p_##N##_node_find(m, key);                       \
        if (n) {                                                               \
            sgc_free(_p_##N##_node_erase(m, n));                               \
        }                                                                      \
        return (bool)n;                                                        \
    }                                                                          \
                                                                               \
    bool N##_it_erase(struct N* m, struct N##_it* i) {             \
        struct N##_it tmp = {i->curr_, i->next_, i->valid_};          \
        N##_it_go_next(&tmp);                                               \
        bool valid = i->valid_;                                             \
        if (valid) {                                                           \
            sgc_free(_p_##N##_node_erase(m, i->curr_));                        \
        }                                                                      \
        i->curr_ = tmp.curr_;                                                  \
        i->next_ = tmp.next_;                                                  \
        i->valid_ = tmp.valid_;                                          \
        return valid;                                                          \
    }                                                                          \
                                                                               \
    static void _p_##N##_erase_rebalanse(struct N* m, struct N##_node* n,      \
                                         struct N##_node* p) {                 \
        if (p) {                                                               \
            struct N##_node* s;                                                \
            struct N##_node* r;                                                \
            if (p->left_ == n && p->right_) {                                  \
                s = p->right_;                                                 \
                if (s->color_ == SGC_MAP_RED) {                                \
                    _p_##N##_rotate_left(m, s, p);                             \
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
                        _p_##N##_erase_rebalanse(m, p, p->parent_);            \
                    }                                                          \
                } else if (s->right_ && s->right_->color_ == SGC_MAP_RED) {    \
                    r = s->right_;                                             \
                    r->color_ = SGC_MAP_BLACK;                                 \
                    _p_##N##_rotate_left(m, s, p);                             \
                } else if (s->left_ && s->left_->color_ == SGC_MAP_RED) {      \
                    r = s->left_;                                              \
                    _p_##N##_rotate_right_left(m, r, s, p);                    \
                }                                                              \
            } else {                                                           \
                s = p->left_;                                                  \
                if (!s) {                                                      \
                    return;                                                    \
                }                                                              \
                if (s->color_ == SGC_MAP_RED) {                                \
                    _p_##N##_rotate_right(m, s, p);                            \
                    s->color_ = SGC_MAP_BLACK;                                 \
                    p->color_ = SGC_MAP_BLACK;                                 \
                    if (p->left_) {                                            \
                        p->left_->color_ = SGC_MAP_RED;                        \
                    }                                                          \
                } else if ((!s->right_ ||                                      \
                            s->right_->color_ == SGC_MAP_BLACK) &&             \
                           (!s->left_ || s->left_->color_ == SGC_MAP_BLACK)) { \
                    s->color_ = SGC_MAP_RED;                                   \
                    _p_##N##_erase_rebalanse(m, p, p->parent_);                \
                } else if (s->left_ && s->left_->color_ == SGC_MAP_RED) {      \
                    r = s->left_;                                              \
                    if (r) {                                                   \
                        r->color_ = SGC_MAP_BLACK;                             \
                    }                                                          \
                    if (p->color_ == SGC_MAP_RED) {                            \
                        p->color_ = SGC_MAP_BLACK;                             \
                    } else {                                                   \
                        _p_##N##_rotate_right(m, s, p);                        \
                    }                                                          \
                } else if (s->right_ && s->right_->color_ == SGC_MAP_RED) {    \
                    r = s->right_;                                             \
                    _p_##N##_rotate_left_right(m, r, s, p);                    \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    struct N##_it N##_find(struct N* m, K key) {                         \
        struct N##_it ret = {SGC_MAP_LEAF, SGC_MAP_LEAF, 0};             \
        struct N##_node* prev;                                                 \
        if (m->root_) {                                                        \
            struct N##_node* curr = m->root_;                                  \
            while (curr) {                                                     \
                prev = curr;                                                   \
                int compare = _p_##N##_node_compare(curr, &key);               \
                                                                               \
                if (compare > 0) {                                             \
                    curr = curr->left_;                                        \
                } else if (compare < 0) {                                      \
                    curr = curr->right_;                                       \
                } else {                                                       \
                    ret.next_ = curr;                                          \
                    ret.curr_ = prev;                                          \
                    ret.valid_ = 1;                                         \
                    N##_it_go_next(&ret);                                   \
                    break;                                                     \
                }                                                              \
            }                                                                  \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    static struct N##_node* _p_##N##_node_find(struct N* s, K key) {           \
        struct N##_it i = N##_find(s, key);                              \
        return i.curr_;                                                        \
    }                                                                          \
                                                                               \
    static void _p_##N##_correct_tree(struct N* s, struct N##_node* n,         \
                                      struct N##_node* p,                      \
                                      struct N##_node* gp) {                   \
        struct N##_node* u = _p_##N##_sibling(p, gp);                          \
        if (u == SGC_MAP_LEAF || u->color_ == SGC_MAP_BLACK) {                 \
            _p_##N##_rotate(s, n, p, gp);                                      \
        } else {                                                               \
            u->color_ = SGC_MAP_BLACK;                                         \
            p->color_ = SGC_MAP_BLACK;                                         \
            gp->color_ = SGC_MAP_RED;                                          \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void _p_##N##_check_color(struct N* s, struct N##_node* n) {        \
        if (n == s->root_) {                                                   \
            s->root_->color_ = SGC_MAP_BLACK;                                  \
            return;                                                            \
        }                                                                      \
        struct N##_node* p = n->parent_;                                       \
        struct N##_node* gp = p->parent_;                                      \
        if (p->color_ == SGC_MAP_RED && n->color_ == SGC_MAP_RED) {            \
            _p_##N##_correct_tree(s, n, p, gp);                                \
        }                                                                      \
        if (gp) {                                                              \
            _p_##N##_check_color(s, gp);                                       \
        }                                                                      \
    }                                                                          \
                                                                               \
    static bool _p_##N##_is_left_child(const struct N##_node* const n,         \
                                       const struct N##_node* const parent) {  \
        bool ret = false;                                                      \
        if (parent) {                                                          \
            ret = (n == parent->left_);                                        \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    static struct N##_node*                                                    \
        _p_##N##_sibling(const struct N##_node* const n,                       \
                         const struct N##_node* const parent) {                \
        struct N##_node* sibling = NULL;                                       \
        if (parent != SGC_MAP_LEAF) {                                          \
            sibling = (n == parent->left_) ? parent->right_ : parent->left_;   \
        }                                                                      \
        return sibling;                                                        \
    }                                                                          \
                                                                               \
    static void _p_##N##_rotate_left(struct N* m, struct N##_node* parent,     \
                                     struct N##_node* gparent) {               \
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
            if (_p_##N##_is_left_child(gparent, ggparent)) {                   \
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
    static void _p_##N##_rotate_right(struct N* m, struct N##_node* parent,    \
                                      struct N##_node* gparent) {              \
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
            if (_p_##N##_is_left_child(gparent, ggparent)) {                   \
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
    static void _p_##N##_rotate_left_right(struct N* m, struct N##_node* n,    \
                                           struct N##_node* parent,            \
                                           struct N##_node* gparent) {         \
        _p_##N##_rotate_left(m, n, parent);                                    \
        _p_##N##_rotate_right(m, n, gparent);                                  \
    }                                                                          \
                                                                               \
    static void _p_##N##_rotate_right_left(struct N* m, struct N##_node* n,    \
                                           struct N##_node* parent,            \
                                           struct N##_node* gparent) {         \
        _p_##N##_rotate_right(m, n, parent);                                   \
        _p_##N##_rotate_left(m, n, gparent);                                   \
    }                                                                          \
                                                                               \
    static void _p_##N##_rotate(struct N* m, struct N##_node* n,               \
                                struct N##_node* parent,                       \
                                struct N##_node* gparent) {                    \
        if (_p_##N##_is_left_child(n, parent)) {                               \
            if (_p_##N##_is_left_child(parent, gparent)) {                     \
                _p_##N##_rotate_right(m, parent, gparent);                     \
                n->color_ = SGC_MAP_RED;                                       \
                parent->color_ = SGC_MAP_BLACK;                                \
                struct N##_node* sibling = parent->right_;                     \
                if (sibling != SGC_MAP_LEAF) {                                 \
                    sibling->color_ = SGC_MAP_RED;                             \
                }                                                              \
            } else {                                                           \
                _p_##N##_rotate_right_left(m, n, parent, gparent);             \
                n->color_ = SGC_MAP_BLACK;                                     \
                n->right_->color_ = SGC_MAP_RED;                               \
                n->left_->color_ = SGC_MAP_RED;                                \
            }                                                                  \
        } else {                                                               \
            if (!_p_##N##_is_left_child(parent, gparent)) {                    \
                _p_##N##_rotate_left(m, parent, gparent);                      \
                n->color_ = SGC_MAP_RED;                                       \
                parent->color_ = SGC_MAP_BLACK;                                \
                struct N##_node* sibling = parent->right_;                     \
                if (sibling != SGC_MAP_LEAF) {                                 \
                    sibling->color_ = SGC_MAP_RED;                             \
                }                                                              \
            } else {                                                           \
                _p_##N##_rotate_left_right(m, n, parent, gparent);             \
                n->color_ = SGC_MAP_BLACK;                                     \
                n->right_->color_ = SGC_MAP_RED;                               \
                n->left_->color_ = SGC_MAP_RED;                                \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    static struct N##_node* _p_##N##_node_begin(struct N##_node* n) {          \
        while (n->left_) {                                                     \
            n = n->left_;                                                      \
        }                                                                      \
        return n;                                                              \
    }                                                                          \
                                                                               \
    static struct N##_node* _p_##N##_node_end(struct N##_node* n) {            \
        while (n->right_) {                                                    \
            n = n->right_;                                                     \
        }                                                                      \
        return n;                                                              \
    }                                                                          \
                                                                               \
    void N##_it_go_next(struct N##_it* i) {                           \
        if (!i->next_) {                                                       \
            i->valid_ = 0;                                                  \
            return;                                                            \
        }                                                                      \
        i->curr_ = i->next_;                                                   \
        if (i->next_->right_) {                                                \
            i->next_ = _p_##N##_node_begin(i->next_->right_);                  \
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
    void N##_it_begin(struct N* m, struct N##_it* i) {             \
        i->curr_ = SGC_MAP_LEAF;                                               \
        i->next_ = (m->root_) ? _p_##N##_node_begin(m->root_) : SGC_MAP_LEAF;  \
        i->valid_ = 1;                                                      \
        N##_it_go_next(i);                                                  \
    }                                                                          \
                                                                               \
    void N##_it_cbegin(const struct N* const m,                          \
                             struct N##_it* i) {                         \
        i->curr_ = SGC_MAP_LEAF;                                               \
        i->next_ = (m->root_) ? _p_##N##_node_begin(m->root_) : SGC_MAP_LEAF;  \
        i->valid_ = 1;                                                      \
        N##_it_go_next(i);                                                  \
    }                                                                          \
                                                                               \
    void N##_it_go_prev(struct N##_it* i) {                           \
        if (!i->curr_) {                                                       \
            i->valid_ = 0;                                                  \
            return;                                                            \
        }                                                                      \
        i->next_ = i->curr_;                                                   \
        if (i->curr_->left_) {                                                 \
            i->curr_ = _p_##N##_node_end(i->curr_->left_);                     \
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
    void N##_it_end(struct N* m, struct N##_it* i) {               \
        i->curr_ = (m->root_) ? _p_##N##_node_end(m->root_) : SGC_MAP_LEAF;    \
        i->next_ = SGC_MAP_LEAF;                                               \
        i->valid_ = (i->curr_) ? 1 : 0;                                     \
    }                                                                          \
                                                                               \
    void N##_it_cend(const struct N* const m, struct N##_it* i) {  \
        i->curr_ = (m->root_) ? _p_##N##_node_end(m->root_) : SGC_MAP_LEAF;    \
        i->next_ = SGC_MAP_LEAF;                                               \
        i->valid_ = (i->curr_) ? 1 : 0;                                     \
    }                                                                          \
                                                                               \
    struct N##_it N##_begin(struct N* m) {                               \
        struct N##_it i;                                                 \
        N##_it_begin(m, &i);                                             \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_it N##_cbegin(const struct N* const m) {                  \
        struct N##_it i;                                                 \
        N##_it_cbegin(m, &i);                                            \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_it N##_end(struct N* m) {                                 \
        struct N##_it i;                                                 \
        N##_it_end(m, &i);                                               \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_it N##_cend(const struct N* const m) {                    \
        struct N##_it i;                                                 \
        N##_it_cend(m, &i);                                              \
        return i;                                                              \
    }                                                                          \
                                                                               \
    bool N##_it_equal(const struct N##_it first,                   \
                            const struct N##_it second) {                \
        return first.curr_ == second.curr_;                                    \
    }                                                                          \
                                                                               \
    bool N##_it_valid(const struct N##_it i) {                     \
        return i.valid_;                                                    \
    }                                                                          \
                                                                               \
    static size_t _p_##N##_stack_size(size_t size) {                           \
        size = sgc_log_two(size) + 1;                                          \
        return sizeof(struct N##_node*) * (size * 2);                          \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        _p_##N##_copy_base_data(dst, src);                                     \
        _p_##N##_copy_nodes(dst, src);                                         \
    }                                                                          \
                                                                               \
    static void _p_##N##_copy_nodes(struct N* __restrict__ dst,                \
                                    const struct N* __restrict__ const src) {  \
        if (src->size_ != 0) {                                                 \
            dst->root_ = _p_##N##_node_duplicate(src, src->root_);             \
                                                                               \
            struct N##_node** stack_src = (struct N##_node**)sgc_malloc(       \
                _p_##N##_stack_size(src->size_));                              \
                                                                               \
            struct N##_node* curr_src = src->root_;                            \
                                                                               \
            struct N##_node** stack_dst = (struct N##_node**)sgc_malloc(       \
                _p_##N##_stack_size(dst->size_));                              \
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
                _p_##N##_node_copy_values(src, curr_dst, curr_src);            \
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
    static struct N##_node*                                                    \
        _p_##N##_node_duplicate(const struct N* const m,                       \
                                const struct N##_node* const n) {              \
        struct N##_node* new_node =                                            \
            (struct N##_node*)sgc_malloc(sizeof(struct N##_node));             \
                                                                               \
        new_node->left_ = new_node->right_ = new_node->parent_ = SGC_MAP_LEAF; \
                                                                               \
        _p_##N##_node_copy_values(m, new_node, n);                             \
        new_node->color_ = n->color_;                                          \
        return new_node;                                                       \
    }                                                                          \
                                                                               \
    void N##_free(struct N* m) {                                               \
        if (!m->size_) {                                                       \
            return;                                                            \
        }                                                                      \
        struct N##_node** stack =                                              \
            (struct N##_node**)sgc_malloc(_p_##N##_stack_size(m->size_));      \
                                                                               \
        struct N##_node* curr = m->root_;                                      \
        struct N##_node* tmp = NULL;                                           \
                                                                               \
        size_t stack_size = 0;                                                 \
        while (true) {                                                         \
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
                _p_##N##_node_free(m, tmp);                                    \
                sgc_free(tmp);                                                 \
            }                                                                  \
        }                                                                      \
        sgc_free(stack);                                                       \
        m->root_ = SGC_MAP_LEAF;                                               \
        m->size_ = 0;                                                          \
    }
