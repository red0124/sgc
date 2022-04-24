#pragma once
#include <stdlib.h>

#define _SGC_MAP_LEAF NULL

enum _sgc_map_color {
    _SGC_MAP_COLOR_RED,
    _SGC_MAP_COLOR_BLACK,
};

#define _SGC_INIT_COMMON_RBTREE(K, N)                                          \
    bool N##_erase(N* m, const K key) {                                        \
        struct _p_##N##_node* n = _p_##N##_node_find(m, key);                  \
        if (n) {                                                               \
            _p_##N##_node_erase(m, n);                                         \
        }                                                                      \
        return (bool)n;                                                        \
    }                                                                          \
                                                                               \
    bool N##_erase_it(N* m, N##_it* i) {                                       \
        N##_it tmp = *i;                                                       \
        N##_it_go_next(&tmp);                                                  \
        bool valid = i->valid_;                                                \
        if (valid) {                                                           \
            _p_##N##_node_erase(m, i->curr_);                                  \
        }                                                                      \
        i->curr_ = tmp.curr_;                                                  \
        i->next_ = tmp.next_;                                                  \
        i->valid_ = tmp.valid_;                                                \
        return valid;                                                          \
    }                                                                          \
                                                                               \
    static void _p_##N##_erase_rebalanse(N* m, struct _p_##N##_node* n,        \
                                         struct _p_##N##_node* p) {            \
        if (p) {                                                               \
            struct _p_##N##_node* s;                                           \
            struct _p_##N##_node* r;                                           \
            if (p->left_ == n && p->right_) {                                  \
                s = p->right_;                                                 \
                if (s->color_ == _SGC_MAP_COLOR_RED) {                         \
                    _p_##N##_rotate_left(m, s, p);                             \
                    s->color_ = _SGC_MAP_COLOR_BLACK;                          \
                    p->color_ = _SGC_MAP_COLOR_BLACK;                          \
                    if (p->right_) {                                           \
                        p->right_->color_ = _SGC_MAP_COLOR_RED;                \
                    }                                                          \
                } else if ((!s->right_ ||                                      \
                            s->right_->color_ == _SGC_MAP_COLOR_BLACK) &&      \
                           (!s->left_ ||                                       \
                            s->left_->color_ == _SGC_MAP_COLOR_BLACK)) {       \
                    s->color_ = _SGC_MAP_COLOR_RED;                            \
                    if (p->color_ == _SGC_MAP_COLOR_RED) {                     \
                        p->color_ = _SGC_MAP_COLOR_BLACK;                      \
                    } else {                                                   \
                        _p_##N##_erase_rebalanse(m, p, p->parent_);            \
                    }                                                          \
                } else if (s->right_ &&                                        \
                           s->right_->color_ == _SGC_MAP_COLOR_RED) {          \
                    r = s->right_;                                             \
                    r->color_ = _SGC_MAP_COLOR_BLACK;                          \
                    _p_##N##_rotate_left(m, s, p);                             \
                } else if (s->left_ &&                                         \
                           s->left_->color_ == _SGC_MAP_COLOR_RED) {           \
                    r = s->left_;                                              \
                    _p_##N##_rotate_right_left(m, r, s, p);                    \
                }                                                              \
            } else {                                                           \
                s = p->left_;                                                  \
                if (!s) {                                                      \
                    return;                                                    \
                }                                                              \
                if (s->color_ == _SGC_MAP_COLOR_RED) {                         \
                    _p_##N##_rotate_right(m, s, p);                            \
                    s->color_ = _SGC_MAP_COLOR_BLACK;                          \
                    p->color_ = _SGC_MAP_COLOR_BLACK;                          \
                    if (p->left_) {                                            \
                        p->left_->color_ = _SGC_MAP_COLOR_RED;                 \
                    }                                                          \
                } else if ((!s->right_ ||                                      \
                            s->right_->color_ == _SGC_MAP_COLOR_BLACK) &&      \
                           (!s->left_ ||                                       \
                            s->left_->color_ == _SGC_MAP_COLOR_BLACK)) {       \
                    s->color_ = _SGC_MAP_COLOR_RED;                            \
                    _p_##N##_erase_rebalanse(m, p, p->parent_);                \
                } else if (s->left_ &&                                         \
                           s->left_->color_ == _SGC_MAP_COLOR_RED) {           \
                    r = s->left_;                                              \
                    if (r) {                                                   \
                        r->color_ = _SGC_MAP_COLOR_BLACK;                      \
                    }                                                          \
                    if (p->color_ == _SGC_MAP_COLOR_RED) {                     \
                        p->color_ = _SGC_MAP_COLOR_BLACK;                      \
                    } else {                                                   \
                        _p_##N##_rotate_right(m, s, p);                        \
                    }                                                          \
                } else if (s->right_ &&                                        \
                           s->right_->color_ == _SGC_MAP_COLOR_RED) {          \
                    r = s->right_;                                             \
                    _p_##N##_rotate_left_right(m, r, s, p);                    \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    N##_it N##_find(N* m, const K key) {                                       \
        N##_it ret = {_SGC_MAP_LEAF, _SGC_MAP_LEAF, 0};                        \
        struct _p_##N##_node* prev;                                            \
        if (m->root_) {                                                        \
            struct _p_##N##_node* curr = m->root_;                             \
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
                    ret.valid_ = 1;                                            \
                    N##_it_go_next(&ret);                                      \
                    break;                                                     \
                }                                                              \
            }                                                                  \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    static struct _p_##N##_node* _p_##N##_node_find(N* s, K key) {             \
        N##_it i = N##_find(s, key);                                           \
        return i.curr_;                                                        \
    }                                                                          \
                                                                               \
    static void _p_##N##_correct_tree(N* s, struct _p_##N##_node* n,           \
                                      struct _p_##N##_node* p,                 \
                                      struct _p_##N##_node* gp) {              \
        struct _p_##N##_node* u = _p_##N##_sibling(p, gp);                     \
        if (u == _SGC_MAP_LEAF || u->color_ == _SGC_MAP_COLOR_BLACK) {         \
            _p_##N##_rotate(s, n, p, gp);                                      \
        } else {                                                               \
            u->color_ = _SGC_MAP_COLOR_BLACK;                                  \
            p->color_ = _SGC_MAP_COLOR_BLACK;                                  \
            gp->color_ = _SGC_MAP_COLOR_RED;                                   \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void _p_##N##_check_color(N* s, struct _p_##N##_node* n) {          \
        if (n == s->root_) {                                                   \
            s->root_->color_ = _SGC_MAP_COLOR_BLACK;                           \
            return;                                                            \
        }                                                                      \
        struct _p_##N##_node* p = n->parent_;                                  \
        struct _p_##N##_node* gp = p->parent_;                                 \
        if (p->color_ == _SGC_MAP_COLOR_RED &&                                 \
            n->color_ == _SGC_MAP_COLOR_RED) {                                 \
            _p_##N##_correct_tree(s, n, p, gp);                                \
        }                                                                      \
        if (gp) {                                                              \
            _p_##N##_check_color(s, gp);                                       \
        }                                                                      \
    }                                                                          \
                                                                               \
    static bool                                                                \
        _p_##N##_is_left_child(const struct _p_##N##_node* const n,            \
                               const struct _p_##N##_node* const parent) {     \
        bool ret = false;                                                      \
        if (parent) {                                                          \
            ret = (n == parent->left_);                                        \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    static struct _p_##N##_node*                                               \
        _p_##N##_sibling(const struct _p_##N##_node* const n,                  \
                         const struct _p_##N##_node* const parent) {           \
        struct _p_##N##_node* sibling = NULL;                                  \
        if (parent != _SGC_MAP_LEAF) {                                         \
            sibling = (n == parent->left_) ? parent->right_ : parent->left_;   \
        }                                                                      \
        return sibling;                                                        \
    }                                                                          \
                                                                               \
    static void _p_##N##_rotate_left(N* m, struct _p_##N##_node* parent,       \
                                     struct _p_##N##_node* gparent) {          \
        struct _p_##N##_node* left = parent->left_;                            \
        if (gparent) {                                                         \
            gparent->right_ = left;                                            \
        }                                                                      \
        if (left != _SGC_MAP_LEAF) {                                           \
            left->parent_ = gparent;                                           \
        }                                                                      \
        if (gparent == m->root_) {                                             \
            m->root_ = parent;                                                 \
            parent->parent_ = _SGC_MAP_LEAF;                                   \
        } else {                                                               \
            struct _p_##N##_node* ggparent = gparent->parent_;                 \
            parent->parent_ = ggparent;                                        \
            if (_p_##N##_is_left_child(gparent, ggparent)) {                   \
                ggparent->left_ = parent;                                      \
            } else {                                                           \
                ggparent->right_ = parent;                                     \
            }                                                                  \
        }                                                                      \
        parent->left_ = gparent;                                               \
        gparent->parent_ = parent;                                             \
        parent->color_ = _SGC_MAP_COLOR_BLACK;                                 \
        gparent->color_ = _SGC_MAP_COLOR_RED;                                  \
    }                                                                          \
                                                                               \
    static void _p_##N##_rotate_right(N* m, struct _p_##N##_node* parent,      \
                                      struct _p_##N##_node* gparent) {         \
        struct _p_##N##_node* right = parent->right_;                          \
        gparent->left_ = right;                                                \
        if (right != _SGC_MAP_LEAF) {                                          \
            right->parent_ = gparent;                                          \
        }                                                                      \
        if (gparent == m->root_) {                                             \
            m->root_ = parent;                                                 \
            parent->parent_ = _SGC_MAP_LEAF;                                   \
        } else {                                                               \
            struct _p_##N##_node* ggparent = gparent->parent_;                 \
            parent->parent_ = ggparent;                                        \
            if (_p_##N##_is_left_child(gparent, ggparent)) {                   \
                ggparent->left_ = parent;                                      \
            } else {                                                           \
                ggparent->right_ = parent;                                     \
            }                                                                  \
        }                                                                      \
        parent->right_ = gparent;                                              \
        gparent->parent_ = parent;                                             \
        parent->color_ = _SGC_MAP_COLOR_BLACK;                                 \
        gparent->color_ = _SGC_MAP_COLOR_RED;                                  \
    }                                                                          \
                                                                               \
    static void _p_##N##_rotate_left_right(N* m, struct _p_##N##_node* n,      \
                                           struct _p_##N##_node* parent,       \
                                           struct _p_##N##_node* gparent) {    \
        _p_##N##_rotate_left(m, n, parent);                                    \
        _p_##N##_rotate_right(m, n, gparent);                                  \
    }                                                                          \
                                                                               \
    static void _p_##N##_rotate_right_left(N* m, struct _p_##N##_node* n,      \
                                           struct _p_##N##_node* parent,       \
                                           struct _p_##N##_node* gparent) {    \
        _p_##N##_rotate_right(m, n, parent);                                   \
        _p_##N##_rotate_left(m, n, gparent);                                   \
    }                                                                          \
                                                                               \
    static void _p_##N##_rotate(N* m, struct _p_##N##_node* n,                 \
                                struct _p_##N##_node* parent,                  \
                                struct _p_##N##_node* gparent) {               \
        if (_p_##N##_is_left_child(n, parent)) {                               \
            if (_p_##N##_is_left_child(parent, gparent)) {                     \
                _p_##N##_rotate_right(m, parent, gparent);                     \
                n->color_ = _SGC_MAP_COLOR_RED;                                \
                parent->color_ = _SGC_MAP_COLOR_BLACK;                         \
                struct _p_##N##_node* sibling = parent->right_;                \
                if (sibling != _SGC_MAP_LEAF) {                                \
                    sibling->color_ = _SGC_MAP_COLOR_RED;                      \
                }                                                              \
            } else {                                                           \
                _p_##N##_rotate_right_left(m, n, parent, gparent);             \
                n->color_ = _SGC_MAP_COLOR_BLACK;                              \
                n->right_->color_ = _SGC_MAP_COLOR_RED;                        \
                n->left_->color_ = _SGC_MAP_COLOR_RED;                         \
            }                                                                  \
        } else {                                                               \
            if (!_p_##N##_is_left_child(parent, gparent)) {                    \
                _p_##N##_rotate_left(m, parent, gparent);                      \
                n->color_ = _SGC_MAP_COLOR_RED;                                \
                parent->color_ = _SGC_MAP_COLOR_BLACK;                         \
                struct _p_##N##_node* sibling = parent->right_;                \
                if (sibling != _SGC_MAP_LEAF) {                                \
                    sibling->color_ = _SGC_MAP_COLOR_RED;                      \
                }                                                              \
            } else {                                                           \
                _p_##N##_rotate_left_right(m, n, parent, gparent);             \
                n->color_ = _SGC_MAP_COLOR_BLACK;                              \
                n->right_->color_ = _SGC_MAP_COLOR_RED;                        \
                n->left_->color_ = _SGC_MAP_COLOR_RED;                         \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    static struct _p_##N##_node* _p_##N##_node_begin(                          \
        struct _p_##N##_node* n) {                                             \
        while (n->left_) {                                                     \
            n = n->left_;                                                      \
        }                                                                      \
        return n;                                                              \
    }                                                                          \
                                                                               \
    static struct _p_##N##_node* _p_##N##_node_end(struct _p_##N##_node* n) {  \
        while (n->right_) {                                                    \
            n = n->right_;                                                     \
        }                                                                      \
        return n;                                                              \
    }                                                                          \
                                                                               \
    void N##_it_go_next(N##_it* i) {                                           \
        if (!i->next_) {                                                       \
            i->valid_ = false;                                                 \
            return;                                                            \
        }                                                                      \
        i->curr_ = i->next_;                                                   \
        if (i->next_->right_) {                                                \
            i->next_ = _p_##N##_node_begin(i->next_->right_);                  \
        } else {                                                               \
            struct _p_##N##_node* parent = i->next_->parent_;                  \
            while (parent && parent->right_ == i->next_) {                     \
                i->next_ = parent;                                             \
                parent = parent->parent_;                                      \
            }                                                                  \
            if (i->next_->right_ != parent) {                                  \
                i->next_ = parent;                                             \
            } else {                                                           \
                i->next_ = _SGC_MAP_LEAF;                                      \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    N##_it N##_begin(N* m) {                                                   \
        N##_it i;                                                              \
        i.curr_ = _SGC_MAP_LEAF;                                               \
        i.next_ = (m->root_) ? _p_##N##_node_begin(m->root_) : _SGC_MAP_LEAF;  \
        i.valid_ = true;                                                       \
        N##_it_go_next(&i);                                                    \
        return i;                                                              \
    }                                                                          \
                                                                               \
    void N##_it_go_prev(N##_it* i) {                                           \
        if (!i->curr_) {                                                       \
            i->valid_ = false;                                                 \
            return;                                                            \
        }                                                                      \
        i->next_ = i->curr_;                                                   \
        if (i->curr_->left_) {                                                 \
            i->curr_ = _p_##N##_node_end(i->curr_->left_);                     \
        } else {                                                               \
            struct _p_##N##_node* parent = i->curr_->parent_;                  \
            while (parent && parent->left_ == i->curr_) {                      \
                i->curr_ = parent;                                             \
                parent = parent->parent_;                                      \
            }                                                                  \
            if (parent == _SGC_MAP_LEAF) {                                     \
                i->valid_ = false;                                             \
                return;                                                        \
            }                                                                  \
            if (i->curr_->left_ != parent) {                                   \
                i->curr_ = parent;                                             \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    N##_it N##_end(N* m) {                                                     \
        N##_it i;                                                              \
        i.curr_ = (m->root_) ? _p_##N##_node_end(m->root_) : _SGC_MAP_LEAF;    \
        i.next_ = _SGC_MAP_LEAF;                                               \
        i.valid_ = (i.curr_) ? 1 : 0;                                          \
        return i;                                                              \
    }                                                                          \
                                                                               \
    bool N##_it_eq(const N##_it* const first, const N##_it* const second) {    \
        return first->curr_ == second->curr_;                                  \
    }                                                                          \
                                                                               \
    bool N##_it_valid(const N##_it* const i) {                                 \
        return i->valid_;                                                      \
    }                                                                          \
                                                                               \
    static size_t _p_##N##_stack_size(size_t size) {                           \
        size = sgc_log_two(size) + 1;                                          \
        return sizeof(struct _p_##N##_node*) * (size * 2);                     \
    }                                                                          \
                                                                               \
    void N##_copy(N* __restrict__ dst, const N* __restrict__ const src) {      \
        if (src->size_ != 0) {                                                 \
            _p_##N##_copy_base_data(dst, src);                                 \
            _p_##N##_copy_nodes(dst, src);                                     \
        } else {                                                               \
            N##_init(dst);                                                     \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void _p_##N##_copy_nodes(N* __restrict__ dst,                       \
                                    const N* __restrict__ const src) {         \
        if (src->size_ != 0) {                                                 \
            dst->root_ = _p_##N##_node_duplicate(src, src->root_);             \
            if (!dst->root_) {                                                 \
                N##_init(dst);                                                 \
                return;                                                        \
            }                                                                  \
                                                                               \
            struct _p_##N##_node** stack_src =                                 \
                (struct _p_##N##_node**)sgc_malloc(                            \
                    _p_##N##_stack_size(src->size_));                          \
            if (!stack_src) {                                                  \
                N##_free(dst);                                                 \
                N##_init(dst);                                                 \
                return;                                                        \
            }                                                                  \
                                                                               \
            struct _p_##N##_node* curr_src = src->root_;                       \
                                                                               \
            struct _p_##N##_node** stack_dst =                                 \
                (struct _p_##N##_node**)sgc_malloc(                            \
                    _p_##N##_stack_size(dst->size_));                          \
            if (!stack_dst) {                                                  \
                sgc_free(stack_src);                                           \
                N##_init(dst);                                                 \
                return;                                                        \
            }                                                                  \
                                                                               \
            struct _p_##N##_node* curr_dst = dst->root_;                       \
                                                                               \
            struct _p_##N##_node* tmp = _SGC_MAP_LEAF;                         \
                                                                               \
            stack_src[0] = _SGC_MAP_LEAF;                                      \
            stack_dst[0] = _SGC_MAP_LEAF;                                      \
                                                                               \
            stack_src[1] = src->root_;                                         \
            stack_dst[1] = dst->root_;                                         \
            size_t stack_size = 2;                                             \
                                                                               \
            while (stack_size > 0) {                                           \
                if (!((curr_src->left_ != _SGC_MAP_LEAF &&                     \
                       curr_dst->left_ == _SGC_MAP_LEAF) ||                    \
                      (curr_src->right_ != _SGC_MAP_LEAF &&                    \
                       curr_dst->right_ == _SGC_MAP_LEAF))) {                  \
                    --stack_size;                                              \
                    curr_src = stack_src[stack_size];                          \
                    curr_dst = stack_dst[stack_size];                          \
                    continue;                                                  \
                }                                                              \
                                                                               \
                struct _p_##N##_node* new_node =                               \
                    (struct _p_##N##_node*)sgc_malloc(                         \
                        sizeof(struct _p_##N##_node));                         \
                                                                               \
                if (!new_node) {                                               \
                    sgc_free(stack_dst);                                       \
                    sgc_free(stack_src);                                       \
                    N##_free(dst);                                             \
                    N##_init(dst);                                             \
                    return;                                                    \
                }                                                              \
                                                                               \
                if (curr_src->left_ != _SGC_MAP_LEAF &&                        \
                    curr_dst->left_ == _SGC_MAP_LEAF) {                        \
                    curr_dst->left_ = new_node;                                \
                    tmp = curr_dst->left_;                                     \
                    tmp->parent_ = curr_dst;                                   \
                    curr_src = curr_src->left_;                                \
                } else {                                                       \
                    curr_dst->right_ = new_node;                               \
                    tmp = curr_dst->right_;                                    \
                    tmp->parent_ = curr_dst;                                   \
                    curr_src = curr_src->right_;                               \
                }                                                              \
                tmp->left_ = tmp->right_ = _SGC_MAP_LEAF;                      \
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
    static struct _p_##N##_node*                                               \
        _p_##N##_node_duplicate(const N* const m,                              \
                                const struct _p_##N##_node* const n) {         \
        struct _p_##N##_node* new_node =                                       \
            (struct _p_##N##_node*)sgc_malloc(sizeof(struct _p_##N##_node));   \
        if (!new_node) {                                                       \
            return NULL;                                                       \
        }                                                                      \
                                                                               \
        new_node->left_ = new_node->right_ = new_node->parent_ =               \
            _SGC_MAP_LEAF;                                                     \
                                                                               \
        _p_##N##_node_copy_values(m, new_node, n);                             \
        new_node->color_ = n->color_;                                          \
        return new_node;                                                       \
    }                                                                          \
                                                                               \
    void N##_free(N* m) {                                                      \
        if (!m->size_) {                                                       \
            return;                                                            \
        }                                                                      \
                                                                               \
        struct _p_##N##_node* curr = m->root_;                                 \
        while (curr != _SGC_MAP_LEAF && curr->left_ != _SGC_MAP_LEAF) {        \
            curr = curr->left_;                                                \
        }                                                                      \
                                                                               \
        while (m->root_ != _SGC_MAP_LEAF) {                                    \
            curr->left_ = m->root_->right_;                                    \
            while (curr != _SGC_MAP_LEAF && curr->left_ != _SGC_MAP_LEAF) {    \
                curr = curr->left_;                                            \
            }                                                                  \
            struct _p_##N##_node* tmp = m->root_;                              \
            m->root_ = m->root_->left_;                                        \
            _p_##N##_node_free(m, tmp);                                        \
            sgc_free(tmp);                                                     \
        }                                                                      \
        m->root_ = _SGC_MAP_LEAF;                                              \
        m->size_ = 0;                                                          \
    }                                                                          \
                                                                               \
    static void _p_##N##_node_erase(N* m, struct _p_##N##_node* n) {           \
        struct _p_##N##_node* succ;                                            \
        struct _p_##N##_node* succ_p;                                          \
        struct _p_##N##_node* succ_c = _SGC_MAP_LEAF;                          \
        if (!n->left_ || !n->right_) {                                         \
            succ = n;                                                          \
        } else {                                                               \
            succ = n->right_;                                                  \
            while (succ->left_) {                                              \
                succ = succ->left_;                                            \
            }                                                                  \
        }                                                                      \
                                                                               \
        if (succ != n) {                                                       \
            /* TODO relinking */                                               \
            _p_##N##_node_replace_data(m, n, succ);                            \
            _p_##N##_node_free(m, succ);                                       \
        } else {                                                               \
            _p_##N##_node_free(m, succ);                                       \
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
        if ((succ_c && succ_c->color_ == _SGC_MAP_COLOR_RED) ||                \
            succ->color_ == _SGC_MAP_COLOR_RED) {                              \
            if (succ_c) {                                                      \
                succ_c->color_ = _SGC_MAP_COLOR_BLACK;                         \
            }                                                                  \
        } else {                                                               \
            _p_##N##_erase_rebalanse(m, succ_c, succ_p);                       \
        }                                                                      \
        if (m->root_) {                                                        \
            m->root_->color_ = _SGC_MAP_COLOR_BLACK;                           \
        }                                                                      \
        --m->size_;                                                            \
        sgc_free(succ);                                                        \
    }
