#pragma once

#define SGC_INIT_SLL_TYPE_FUNCTIONS(T, S, N)                                   \
        void N##_copy(struct N *__restrict__ dst,                              \
                      const struct N *__restrict__ const src)                  \
        {                                                                      \
                dst->_shared = src->_shared;                                   \
                N##_init(dst);                                                 \
                if(src->_size != 0)                                            \
                {                                                              \
                        dst->_head = N##_node_alloc(dst);                      \
                        SGC_COPY(T##_copy, dst->_head->_data,                  \
                                 src->_head->_data, src->_shared);             \
                        struct N##_node *curr_src = src->_head;                \
                        struct N##_node *curr_dst = dst->_head;                \
                        struct N##_node *tmp_src = NULL;                       \
                        struct N##_node *tmp_dst = NULL;                       \
                        while(curr_src)                                        \
                        {                                                      \
                                tmp_src = curr_src->_next;                     \
                                if(!tmp_src)                                   \
                                {                                              \
                                        break;                                 \
                                }                                              \
                                tmp_dst = N##_node_alloc(dst);                 \
                                SGC_COPY(T##_copy, tmp_dst->_data,             \
                                         tmp_src->_data, src->_shared);        \
                                curr_dst->_next = tmp_dst;                     \
                                curr_dst = tmp_dst;                            \
                                curr_src = tmp_src;                            \
                        }                                                      \
                        dst->_tail = curr_dst;                                 \
                        dst->_tail->_next = NULL;                              \
                }                                                              \
                else                                                           \
                {                                                              \
                        dst->_head = dst->_tail = NULL;                        \
                }                                                              \
                dst->_size = src->_size;                                       \
        }                                                                      \
                                                                               \
        void N##_push_back(struct N *l, T el)                                  \
        {                                                                      \
                if(S > 0 && l->_size == S)                                     \
                {                                                              \
                        return;                                                \
                }                                                              \
                struct N##_node *new_el = N##_node_alloc(l);                   \
                SGC_COPY(T##_copy, new_el->_data, el, l->_shared);             \
                new_el->_next = NULL;                                          \
                switch(l->_size)                                               \
                {                                                              \
                case 0:                                                        \
                        l->_head = l->_tail = new_el;                          \
                        break;                                                 \
                case 1:                                                        \
                        l->_tail = new_el;                                     \
                        l->_head->_next = l->_tail;                            \
                        break;                                                 \
                default:                                                       \
                        l->_tail->_next = new_el;                              \
                        l->_tail = l->_tail->_next;                            \
                        break;                                                 \
                }                                                              \
                l->_size++;                                                    \
        }                                                                      \
                                                                               \
        static struct N##_node *N##_prev(struct N##_node *head,                \
                                         struct N##_node *n)                   \
        {                                                                      \
                struct N##_node *curr = (head == n) ? NULL : head;             \
                struct N##_node *next = curr;                                  \
                while(next && next != n)                                       \
                {                                                              \
                        curr = next;                                           \
                        next = next->_next;                                    \
                }                                                              \
                return curr;                                                   \
        }                                                                      \
                                                                               \
        void N##_pop_back(struct N *l)                                         \
        {                                                                      \
                if(l->_size)                                                   \
                {                                                              \
                        struct N##_node *tmp = l->_tail;                       \
                        l->_tail = N##_prev(l->_head, l->_tail);               \
                        if(!l->_shared)                                        \
                        {                                                      \
                                T##_free(&tmp->_data);                         \
                        }                                                      \
                        N##_node_free(l, tmp);                                 \
                        if(l->_tail)                                           \
                        {                                                      \
                                l->_tail->_next = NULL;                        \
                        }                                                      \
                        --l->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_push_front(struct N *l, const T el)                           \
        {                                                                      \
                if(S > 0 && l->_size == S)                                     \
                {                                                              \
                        return;                                                \
                }                                                              \
                struct N##_node *new_el = N##_node_alloc(l);                   \
                SGC_COPY(T##_copy, new_el->_data, el, l->_shared);             \
                switch(l->_size)                                               \
                {                                                              \
                case 0:                                                        \
                        new_el->_next = NULL;                                  \
                        l->_head = l->_tail = new_el;                          \
                        break;                                                 \
                case 1:                                                        \
                        l->_head = new_el;                                     \
                        l->_head->_next = l->_tail;                            \
                        break;                                                 \
                default:                                                       \
                        new_el->_next = l->_head;                              \
                        l->_head = new_el;                                     \
                        break;                                                 \
                }                                                              \
                l->_size++;                                                    \
        }                                                                      \
                                                                               \
        void N##_pop_front(struct N *l)                                        \
        {                                                                      \
                if(l->_size)                                                   \
                {                                                              \
                        struct N##_node *tmp = l->_head;                       \
                        l->_head = l->_head->_next;                            \
                        if(!l->_shared)                                        \
                        {                                                      \
                                T##_free(&tmp->_data);                         \
                        }                                                      \
                        N##_node_free(l, tmp);                                 \
                        --l->_size;                                            \
                }                                                              \
        }                                                                      \
                                                                               \
        T *N##_at(struct N *l, const size_t at)                                \
        {                                                                      \
                T *ret = NULL;                                                 \
                if(!(at >= l->_size || l->_size == 0))                         \
                {                                                              \
                        struct N##_node *curr = l->_head;                      \
                        for(size_t i = 0; i < at; ++i)                         \
                        {                                                      \
                                curr = curr->_next;                            \
                        }                                                      \
                        ret = &curr->_data;                                    \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        static void N##_node_erase(struct N *l, struct N##_node *n,            \
                                   struct N##_node *prev)                      \
        {                                                                      \
                if(prev)                                                       \
                {                                                              \
                        prev->_next = n->_next;                                \
                }                                                              \
                if(!l->_shared)                                                \
                {                                                              \
                        T##_free(&n->_data);                                   \
                }                                                              \
                N##_node_free(l, n);                                           \
                n = NULL;                                                      \
        }                                                                      \
                                                                               \
        int N##_erase(struct N *l, const T el)                                 \
        {                                                                      \
                int found = 0;                                                 \
                struct N##_node *curr = l->_head;                              \
                struct N##_node *prev = curr;                                  \
                if(!curr)                                                      \
                {                                                              \
                        return found;                                          \
                }                                                              \
                while(curr)                                                    \
                {                                                              \
                        if(T##_equal(&curr->_data, &el))                       \
                        {                                                      \
                                found = 1;                                     \
                                break;                                         \
                        }                                                      \
                        prev = curr;                                           \
                        curr = curr->_next;                                    \
                }                                                              \
                if(found)                                                      \
                {                                                              \
                        if(curr == l->_head)                                   \
                        {                                                      \
                                N##_pop_front(l);                              \
                        }                                                      \
                        else if(curr == l->_tail)                              \
                        {                                                      \
                                N##_pop_back(l);                               \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                N##_node_erase(l, curr, prev);                 \
                l->_size--;                                                    \
                        }                                                      \
                }                                                              \
                return found;                                                  \
        }                                                                      \
                                                                               \
        int N##_erase_at(struct N *l, size_t at)                               \
        {                                                                      \
                int erase = (at - 1 < l->_size || at == 0);                    \
                if(at == 0)                                                    \
                {                                                              \
                        N##_pop_front(l);                                      \
                }                                                              \
                else if(erase)                                                 \
                {                                                              \
                        struct N##_node *curr = l->_head;                      \
                        struct N##_node *prev = curr;                          \
                        for(size_t i = 0; i < at - 1; ++i)                     \
                        {                                                      \
                                prev = curr;                                   \
                                curr = curr->_next;                            \
                        }                                                      \
                        if(curr == l->_head)                                   \
                        {                                                      \
                                l->_head = l->_head->_next;                    \
                        }                                                      \
                        if(curr == l->_tail)                                   \
                        {                                                      \
                                l->_tail = prev;                               \
                        }                                                      \
                        N##_node_erase(l, curr, prev);                         \
                        l->_size--;                                            \
                }                                                              \
                return erase;                                                  \
        }                                                                      \
                                                                               \
        static void N##_insert_node(                                           \
            struct N##_node *__restrict__ curr,                                \
            struct N##_node *__restrict__ const node_new)                      \
        {                                                                      \
                struct N##_node *tmp = curr->_next;                            \
                node_new->_next = tmp;                                         \
                curr->_next = node_new;                                        \
        }                                                                      \
                                                                               \
        int N##_insert_sorted(struct N *l, const T el,                         \
                              int (*compare)(const T *const, const T *const))  \
        {                                                                      \
                int sorted = 1;                                                \
                if(l->_head == NULL)                                           \
                {                                                              \
                        N##_push_front(l, el);                                 \
                }                                                              \
                else if(l->_tail && l->_head != l->_tail &&                    \
                        compare(&l->_tail->_data, &l->_head->_data) <= 0)      \
                {                                                              \
                        sorted = 0;                                            \
                }                                                              \
                else if((compare)(&l->_head->_data, &el) > 0)                  \
                {                                                              \
                        N##_push_front(l, el);                                 \
                }                                                              \
                else if((compare)(&l->_tail->_data, &el) <= 0)                 \
                {                                                              \
                        N##_push_back(l, el);                                  \
                }                                                              \
                else                                                           \
                {                                                              \
                        struct N##_node *new_node = N##_node_alloc(l);         \
                        SGC_COPY(T##_copy, new_node->_data, el, l->_shared);   \
                        struct N##_node *curr = l->_head;                      \
                        struct N##_node *prev = curr;                          \
                        while(compare(&curr->_data, &el) <= 0)                 \
                        {                                                      \
                                prev = curr;                                   \
                                curr = curr->_next;                            \
                        }                                                      \
                        N##_insert_node(prev, new_node);                       \
                        l->_size++;                                            \
                }                                                              \
                return sorted;                                                 \
        }                                                                      \
                                                                               \
        static void N##_ptr_array_to_list(struct N##_node **nodes_ptr,         \
                                          struct N *l)                         \
        {                                                                      \
                if(!l->_size)                                                  \
                {                                                              \
                        return;                                                \
                }                                                              \
                                                                               \
                l->_head = nodes_ptr[0];                                       \
                                                                               \
                l->_tail = nodes_ptr[l->_size - 1];                            \
                l->_tail->_next = NULL;                                        \
                                                                               \
                if(l->_size > 1)                                               \
                {                                                              \
                        l->_head->_next = nodes_ptr[1];                        \
                }                                                              \
                                                                               \
                for(size_t i = 1; i < l->_size - 1; i++)                       \
                {                                                              \
                        nodes_ptr[i]->_next = nodes_ptr[i + 1];                \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_iterator_begin(struct N *l, struct N##_iterator *i)           \
        {                                                                      \
                i->_curr = l->_head;                                           \
                i->_head = l->_head;                                           \
        }                                                                      \
                                                                               \
        void N##_iterator_cbegin(const struct N *const l,                      \
                                 struct N##_iterator *i)                       \
        {                                                                      \
                i->_curr = l->_head;                                           \
                i->_head = l->_head;                                           \
        }                                                                      \
                                                                               \
        void N##_iterator_end(struct N *l, struct N##_iterator *i)             \
        {                                                                      \
                i->_curr = l->_tail;                                           \
                i->_head = l->_head;                                           \
        }                                                                      \
                                                                               \
        void N##_iterator_cend(const struct N *const l,                        \
                               struct N##_iterator *i)                         \
        {                                                                      \
                i->_curr = l->_tail;                                           \
                i->_head = l->_head;                                           \
        }                                                                      \
                                                                               \
        void N##_iterator_prev(struct N##_iterator *i)                         \
        {                                                                      \
                i->_curr = N##_prev(i->_head, i->_curr);                       \
        }
