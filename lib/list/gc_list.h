#pragma once

#ifndef GC_STACK
#define GC_STACK
#define GC_STACK_SIZE 64

#define GC_PREPARE_STACK                                                       \
        char *stack[GC_STACK_SIZE];                                            \
        char **stackptr = stack

#define GC_STACK_PUSH(array, limit)                                            \
        stackptr[0] = array;                                                   \
        stackptr[1] = limit;                                                   \
        stackptr += 2

#define GC_STACK_POP(array, limit)                                             \
        stackptr -= 2;                                                         \
        array = stackptr[0];                                                   \
        limit = stackptr[1]

#define THRESH 7
#endif

#define INIT_LIST(T, N)                                                        \
                                                                               \
        struct N##_node                                                        \
        {                                                                      \
                T _data;                                                       \
                struct N##_node *_next;                                        \
                struct N##_node *_prev;                                        \
        };                                                                     \
                                                                               \
        struct N                                                               \
        {                                                                      \
                size_t _size;                                                  \
                struct N##_node *_head;                                        \
                struct N##_node *_tail;                                        \
        };                                                                     \
                                                                               \
        typedef struct N N;                                                    \
                                                                               \
        int N##_is_static()                                                    \
        {                                                                      \
                return 0;                                                      \
        }                                                                      \
                                                                               \
        /* =================== */                                              \
        /*  ELEMENT FUNCTIONS  */                                              \
        /* =================== */                                              \
                                                                               \
        static void (*N##_element_copy)(T *, const T *const) = T##_copy;       \
                                                                               \
        void N##_set_copy(void (*copy)(T *, const T *const))                   \
        {                                                                      \
                N##_element_copy = copy;                                       \
        }                                                                      \
                                                                               \
        static void N##_flat_copy(T *dst, const T *const src)                  \
        {                                                                      \
                *dst = *src;                                                   \
        }                                                                      \
                                                                               \
        void N##_set_share(int is_shared)                                      \
        {                                                                      \
                if(is_shared)                                                  \
                {                                                              \
                        N##_set_copy(N##_flat_copy);                           \
                }                                                              \
                else                                                           \
                {                                                              \
                        N##_set_copy(T##_copy);                                \
                }                                                              \
        }                                                                      \
                                                                               \
        static int (*N##_element_equal)(const T *const, const T *const) =      \
            T##_equal;                                                         \
                                                                               \
        void N##_set_equal(int (*equal)(const T *const, const T *const))       \
        {                                                                      \
                N##_element_equal = equal;                                     \
        }                                                                      \
                                                                               \
        static void (*N##_element_free)(T *) = T##_free;                       \
                                                                               \
        void N##_set_free(void (*free)(T *))                                   \
        {                                                                      \
                N##_element_free = free;                                       \
        }                                                                      \
                                                                               \
        /* ================ */                                                 \
        /*  LIST FUNCTIONS  */                                                 \
        /* ================ */                                                 \
                                                                               \
        size_t N##_size(const struct N *const l)                               \
        {                                                                      \
                return l->_size;                                               \
        }                                                                      \
                                                                               \
        void N##_init(struct N *l)                                             \
        {                                                                      \
                l->_size = 0;                                                  \
                l->_head = l->_tail = NULL;                                    \
        }                                                                      \
                                                                               \
        void N##_free(struct N *l)                                             \
        {                                                                      \
                struct N##_node *curr = l->_head;                              \
                struct N##_node *tmp;                                          \
                for(size_t i = 0; i < l->_size; ++i)                           \
                {                                                              \
                        tmp = curr;                                            \
                        curr = curr->_next;                                    \
                        if(!T##_is_static() &&                                 \
                           N##_element_copy != N##_flat_copy)                  \
                        {                                                      \
                                N##_element_free(&tmp->_data);                 \
                        }                                                      \
                        free(tmp);                                             \
                }                                                              \
                l->_head = l->_tail = NULL;                                    \
                l->_size = 0;                                                  \
        }                                                                      \
                                                                               \
        int N##_equal(const struct N *const first,                             \
                      const struct N *const second)                            \
        {                                                                      \
                int equal = (first == second);                                 \
                if(equal == 0 && first->_size == second->_size)                \
                {                                                              \
                        struct N##_node *curr_first = first->_head;            \
                        struct N##_node *curr_second = second->_head;          \
                        equal = 1;                                             \
                        while(curr_first)                                      \
                        {                                                      \
                                if(!N##_element_equal(&curr_first->_data,      \
                                                      &curr_second->_data))    \
                                {                                              \
                                        equal = 0;                             \
                                        break;                                 \
                                }                                              \
                                curr_first = curr_first->_next;                \
                                curr_second = curr_second->_next;              \
                        }                                                      \
                }                                                              \
                return equal;                                                  \
        }                                                                      \
                                                                               \
        void N##_copy(struct N *__restrict__ dst,                              \
                      const struct N *__restrict__ const src)                  \
        {                                                                      \
                if(src->_size != 0)                                            \
                {                                                              \
                        dst->_head = (struct N##_node *)malloc(                \
                            sizeof(struct N##_node));                          \
                        N##_element_copy(&dst->_head->_data,                   \
                                         &src->_head->_data);                  \
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
                                tmp_dst = (struct N##_node *)malloc(           \
                                    sizeof(struct N##_node));                  \
                                N##_element_copy(&tmp_dst->_data,              \
                                                 &tmp_src->_data);             \
                                tmp_dst->_prev = curr_dst;                     \
                                curr_dst->_next = tmp_dst;                     \
                                curr_dst = tmp_dst;                            \
                                curr_src = tmp_src;                            \
                        }                                                      \
                        dst->_tail = curr_dst;                                 \
                        dst->_tail->_next = dst->_head->_prev = NULL;          \
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
                struct N##_node *new_el =                                      \
                    (struct N##_node *)malloc(sizeof(struct N##_node));        \
                N##_element_copy(&new_el->_data, &el);                         \
                new_el->_next = NULL;                                          \
                switch(l->_size)                                               \
                {                                                              \
                case 0:                                                        \
                        new_el->_prev = NULL;                                  \
                        l->_head = l->_tail = new_el;                          \
                        break;                                                 \
                case 1:                                                        \
                        l->_tail = new_el;                                     \
                        l->_head->_next = l->_tail;                            \
                        l->_tail->_prev = l->_head;                            \
                        break;                                                 \
                default:                                                       \
                        new_el->_prev = l->_tail;                              \
                        l->_tail->_next = new_el;                              \
                        l->_tail = l->_tail->_next;                            \
                        break;                                                 \
                }                                                              \
                l->_size++;                                                    \
        }                                                                      \
                                                                               \
        T *N##_back(struct N *l)                                               \
        {                                                                      \
                T *ret = NULL;                                                 \
                if(l->_size)                                                   \
                {                                                              \
                        ret = &l->_tail->_data;                                \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        void N##_set_back(struct N *l, T new_el)                               \
        {                                                                      \
                if(l->_size)                                                   \
                {                                                              \
                        T *el = &l->_tail->_data;                              \
                        if(!T##_is_static() &&                                 \
                           N##_element_copy != N##_flat_copy)                  \
                        {                                                      \
                                N##_element_free(el);                          \
                                N##_element_copy(el, &new_el);                 \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                *el = new_el;                                  \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_pop_back(struct N *l)                                         \
        {                                                                      \
                if(l->_size)                                                   \
                {                                                              \
                        struct N##_node *tmp = l->_tail;                       \
                        l->_tail = l->_tail->_prev;                            \
                        if(!T##_is_static() &&                                 \
                           N##_element_copy != N##_flat_copy)                  \
                        {                                                      \
                                N##_element_free(&tmp->_data);                 \
                        }                                                      \
                        free(tmp);                                             \
                        l->_tail->_next = NULL;                                \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_push_front(struct N *l, const T el)                           \
        {                                                                      \
                struct N##_node *new_el =                                      \
                    (struct N##_node *)malloc(sizeof(struct N##_node));        \
                N##_element_copy(&new_el->_data, &el);                         \
                new_el->_prev = NULL;                                          \
                switch(l->_size)                                               \
                {                                                              \
                case 0:                                                        \
                        new_el->_next = NULL;                                  \
                        l->_head = l->_tail = new_el;                          \
                        break;                                                 \
                case 1:                                                        \
                        l->_head = new_el;                                     \
                        l->_head->_next = l->_tail;                            \
                        l->_tail->_prev = l->_head;                            \
                        break;                                                 \
                default:                                                       \
                        l->_head->_prev = new_el;                              \
                        new_el->_next = l->_head;                              \
                        l->_head = l->_head->_prev;                            \
                        break;                                                 \
                }                                                              \
                l->_size++;                                                    \
        }                                                                      \
                                                                               \
        T *N##_front(struct N *l)                                              \
        {                                                                      \
                T *ret = NULL;                                                 \
                if(l->_size)                                                   \
                {                                                              \
                        ret = &l->_head->_data;                                \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        T *N##_set_front(struct N *l, T new_el)                                \
        {                                                                      \
                T *ret = NULL;                                                 \
                if(l->_size)                                                   \
                {                                                              \
                        T *el = &l->_head->_data;                              \
                        if(!T##_is_static() &&                                 \
                           N##_element_copy != N##_flat_copy)                  \
                        {                                                      \
                                N##_element_free(el);                          \
                                N##_element_copy(el, &new_el);                 \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                *el = new_el;                                  \
                        }                                                      \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        void N##_pop_front(struct N *l)                                        \
        {                                                                      \
                if(l->_size)                                                   \
                {                                                              \
                        struct N##_node *tmp = l->_head;                       \
                        l->_head = l->_head->_next;                            \
                        if(!T##_is_static() &&                                 \
                           N##_element_copy != N##_flat_copy)                  \
                        {                                                      \
                                N##_element_free(&tmp->_data);                 \
                        }                                                      \
                        free(tmp);                                             \
                        l->_head->_prev = NULL;                                \
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
        void N##_set_at(struct N *l, const size_t at, T new_el)                \
        {                                                                      \
                T *el = N##_at(l, at);                                         \
                if(el)                                                         \
                {                                                              \
                        if(!T##_is_static() &&                                 \
                           N##_element_copy != N##_flat_copy)                  \
                        {                                                      \
                                N##_element_free(el);                          \
                                N##_element_copy(el, &new_el);                 \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                *el = new_el;                                  \
                        }                                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        static struct N##_node *N##_find_node(const struct N *const l,         \
                                              const T el)                      \
        {                                                                      \
                struct N##_node *location = NULL;                              \
                for(struct N##_node *curr = l->_head; curr;                    \
                    curr = curr->_next)                                        \
                {                                                              \
                        if(N##_element_equal(&curr->_data, &el))               \
                        {                                                      \
                                location = curr;                               \
                                break;                                         \
                        }                                                      \
                }                                                              \
                return location;                                               \
        }                                                                      \
                                                                               \
        static void N##_node_erase(struct N##_node *n)                         \
        {                                                                      \
                if(n->_next)                                                   \
                {                                                              \
                        n->_next->_prev = n->_prev;                            \
                }                                                              \
                if(n->_prev)                                                   \
                {                                                              \
                        n->_prev->_next = n->_next;                            \
                }                                                              \
                if(!T##_is_static() && N##_element_copy != N##_flat_copy)      \
                {                                                              \
                        N##_element_free(&n->_data);                           \
                }                                                              \
                free(n);                                                       \
                n = NULL;                                                      \
        }                                                                      \
                                                                               \
        int N##_erase(struct N *l, const T el)                                 \
        {                                                                      \
                struct N##_node *n = N##_find_node(l, el);                     \
                int erase = (n != NULL);                                       \
                if(erase)                                                      \
                {                                                              \
                        N##_node_erase(n);                                     \
                        l->_size--;                                            \
                }                                                              \
                return erase;                                                  \
        }                                                                      \
                                                                               \
        int N##_erase_at(struct N *l, size_t at)                               \
        {                                                                      \
                int erase = (at - 1 < l->_size && at != 0);                    \
                if(erase)                                                      \
                {                                                              \
                        struct N##_node *curr = l->_head;                      \
                        for(size_t i = 0; i < at - 1; ++i)                     \
                        {                                                      \
                                curr = curr->_next;                            \
                        }                                                      \
                        if(curr == l->_head)                                   \
                        {                                                      \
                                l->_head = l->_head->_next;                    \
                        }                                                      \
                        if(curr == l->_tail)                                   \
                        {                                                      \
                                l->_tail = l->_tail->_prev;                    \
                        }                                                      \
                        N##_node_erase(curr);                                  \
                        l->_size--;                                            \
                }                                                              \
                return erase;                                                  \
        }                                                                      \
                                                                               \
        int N##_empty(const struct N *l)                                       \
        {                                                                      \
                return (l->_size == 0);                                        \
        }                                                                      \
                                                                               \
        static void N##_insert_node(                                           \
            struct N##_node *__restrict__ curr,                                \
            struct N##_node *__restrict__ const node_new)                      \
        {                                                                      \
                struct N##_node *tmp = curr->_next;                            \
                node_new->_prev = curr;                                        \
                node_new->_next = tmp;                                         \
                tmp->_prev = node_new;                                         \
                curr->_next = node_new;                                        \
        }                                                                      \
                                                                               \
        void N##_insert(struct N *l, const size_t at, const T el)              \
        {                                                                      \
                if(at == 0)                                                    \
                {                                                              \
                        N##_push_front(l, el);                                 \
                }                                                              \
                else if(at >= l->_size)                                        \
                {                                                              \
                        N##_push_back(l, el);                                  \
                }                                                              \
                else                                                           \
                {                                                              \
                        struct N##_node *new_node = (struct N##_node *)malloc( \
                            sizeof(struct N##_node));                          \
                        N##_element_copy(&new_node->_data, &el);               \
                        struct N##_node *curr = l->_head;                      \
                        for(size_t i = 0; i < at - 1; ++i)                     \
                        {                                                      \
                                curr = curr->_next;                            \
                        }                                                      \
                        N##_insert_node(curr, new_node);                       \
                        l->_size++;                                            \
                }                                                              \
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
                        !compare(&l->_tail->_data, &l->_head->_data))          \
                {                                                              \
                        sorted = 0;                                            \
                }                                                              \
                else if((compare)(&l->_head->_data, &el))                      \
                {                                                              \
                        N##_push_front(l, el);                                 \
                }                                                              \
                else if(!(compare)(&l->_tail->_data, &el))                     \
                {                                                              \
                        N##_push_back(l, el);                                  \
                }                                                              \
                else                                                           \
                {                                                              \
                        struct N##_node *new_node = (struct N##_node *)malloc( \
                            sizeof(struct N##_node));                          \
                        N##_element_copy(&new_node->_data, &el);               \
                        struct N##_node *curr = l->_head;                      \
                        while(!compare(&curr->_data, &el))                     \
                        {                                                      \
                                curr = curr->_next;                            \
                        }                                                      \
                        N##_insert_node(curr->_prev, new_node);                \
                        l->_size++;                                            \
                }                                                              \
                return sorted;                                                 \
        }                                                                      \
                                                                               \
        static void N##_memswp(char *i, char *j)                               \
        {                                                                      \
                char tmp[sizeof(struct N##_node *)];                           \
                                                                               \
                memcpy(tmp, i, sizeof(struct N##_node *));                     \
                memcpy(i, j, sizeof(struct N##_node *));                       \
                memcpy(j, tmp, sizeof(struct N##_node *));                     \
        }                                                                      \
                                                                               \
        static inline int N##_compare_node(                                    \
            const void *first, const void *second,                             \
            int comp(const void *, const void *))                              \
        {                                                                      \
                struct N##_node *first_ = *(struct N##_node **)first;          \
                struct N##_node *second_ = *(struct N##_node **)second;        \
                return comp(&first_->_data, &second_->_data);                  \
        }                                                                      \
                                                                               \
        static void N##_qsort(void *array, size_t array_size,                  \
                              int (*comp)(const void *, const void *))         \
        {                                                                      \
                char *i, *j;                                                   \
                size_t thresh = THRESH * sizeof(struct N##_node *);            \
                char *array_ = (char *)array;                                  \
                char *limit = array_ + array_size * sizeof(struct N##_node *); \
                GC_PREPARE_STACK;                                              \
                                                                               \
                while(1)                                                       \
                {                                                              \
                        if((size_t)(limit - array_) > thresh)                  \
                        {                                                      \
                                i = array_ + sizeof(struct N##_node *);        \
                                j = limit - sizeof(struct N##_node *);         \
                                N##_memswp(((((size_t)(limit - array_)) /      \
                                             sizeof(struct N##_node *)) /      \
                                            2) * sizeof(struct N##_node *) +   \
                                               array_,                         \
                                           array_);                            \
                                if(N##_compare_node(i, j, comp) > 0)           \
                                {                                              \
                                        N##_memswp(i, j);                      \
                                }                                              \
                                if(N##_compare_node(array_, j, comp) > 0)      \
                                {                                              \
                                        N##_memswp(array_, j);                 \
                                }                                              \
                                if(N##_compare_node(i, array_, comp) > 0)      \
                                {                                              \
                                        N##_memswp(i, array_);                 \
                                }                                              \
                                while(1)                                       \
                                {                                              \
                                        do                                     \
                                        {                                      \
                                                i +=                           \
                                                    sizeof(struct N##_node *); \
                                        } while(N##_compare_node(array_, i,    \
                                                                 comp) > 0);   \
                                        do                                     \
                                        {                                      \
                                                j -=                           \
                                                    sizeof(struct N##_node *); \
                                        } while(N##_compare_node(j, array_,    \
                                                                 comp) > 0);   \
                                        if(i > j)                              \
                                        {                                      \
                                                break;                         \
                                        }                                      \
                                        N##_memswp(i, j);                      \
                                }                                              \
                                N##_memswp(array_, j);                         \
                                if(j - array_ > limit - i)                     \
                                {                                              \
                                        GC_STACK_PUSH(array_, j);              \
                                        array_ = i;                            \
                                }                                              \
                                else                                           \
                                {                                              \
                                        GC_STACK_PUSH(i, limit);               \
                                        limit = j;                             \
                                }                                              \
                        }                                                      \
                        else                                                   \
                        {                                                      \
                                for(j = array_,                                \
                                i = j + sizeof(struct N##_node *);             \
                                    i < limit;                                 \
                                    j = i, i += sizeof(struct N##_node *))     \
                                {                                              \
                                        for(;                                  \
                                            N##_compare_node(                  \
                                                j,                             \
                                                j + sizeof(struct N##_node *), \
                                                comp) > 0;                     \
                                            j -= sizeof(struct N##_node *))    \
                                        {                                      \
                                                N##_memswp(                    \
                                                    j,                         \
                                                    j + sizeof(struct N##_node \
                                                                   *));        \
                                                if(j == array_)                \
                                                {                              \
                                                        break;                 \
                                                }                              \
                                        }                                      \
                                }                                              \
                                if(stackptr != stack)                          \
                                {                                              \
                                        GC_STACK_POP(array_, limit);           \
                                }                                              \
                                else                                           \
                                {                                              \
                                        break;                                 \
                                }                                              \
                        }                                                      \
                }                                                              \
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
                l->_head->_prev = NULL;                                        \
                                                                               \
                l->_tail = nodes_ptr[l->_size - 1];                            \
                l->_tail->_next = NULL;                                        \
                                                                               \
                if(l->_size > 1)                                               \
                {                                                              \
                        l->_head->_next = nodes_ptr[1];                        \
                        l->_tail->_prev = nodes_ptr[l->_size - 2];             \
                }                                                              \
                                                                               \
                for(size_t i = 1; i < l->_size - 1; i++)                       \
                {                                                              \
                        nodes_ptr[i]->_prev = nodes_ptr[i - 1];                \
                        nodes_ptr[i]->_next = nodes_ptr[i + 1];                \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_sort(struct N *l, int (*comp)(const void *, const void *))    \
        {                                                                      \
                struct N##_node **nodes_ptr = (struct N##_node **)malloc(      \
                    sizeof(struct N##_node *) * l->_size);                     \
                struct N##_node *curr = l->_head;                              \
                                                                               \
                for(size_t i = 0; i < l->_size; i++)                           \
                {                                                              \
                        nodes_ptr[i] = curr;                                   \
                        curr = curr->_next;                                    \
                }                                                              \
                                                                               \
                N##_qsort(nodes_ptr, l->_size, comp);                          \
                N##_ptr_array_to_list(nodes_ptr, l);                           \
                free(nodes_ptr);                                               \
        }                                                                      \
                                                                               \
        /* =============== */                                                  \
        /*  LIST ITERATOR  */                                                  \
        /* =============== */                                                  \
                                                                               \
        struct N##_iterator                                                    \
        {                                                                      \
                struct N##_node *_curr;                                        \
        };                                                                     \
                                                                               \
        T *N##_iterator_value(struct N##_iterator i)                           \
        {                                                                      \
                return &i._curr->_data;                                        \
        }                                                                      \
                                                                               \
        const T *N##_iterator_cvalue(const struct N##_iterator i)              \
        {                                                                      \
                return &i._curr->_data;                                        \
        }                                                                      \
                                                                               \
        void N##_iterator_next(struct N##_iterator *i)                         \
        {                                                                      \
                i->_curr = i->_curr->_next;                                    \
        }                                                                      \
                                                                               \
        void N##_iterator_prev(struct N##_iterator *i)                         \
        {                                                                      \
                i->_curr = i->_curr->_prev;                                    \
        }                                                                      \
                                                                               \
        void N##_iterator_begin(struct N *l, struct N##_iterator *i)           \
        {                                                                      \
                i->_curr = l->_head;                                           \
        }                                                                      \
                                                                               \
        void N##_iterator_cbegin(const struct N *const l,                      \
                                 struct N##_iterator *i)                       \
        {                                                                      \
                i->_curr = l->_head;                                           \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_begin(struct N *l)                             \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_begin(l, &i);                                     \
                return i;                                                      \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_cbegin(const struct N *const l)                \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_cbegin(l, &i);                                    \
                return i;                                                      \
        }                                                                      \
                                                                               \
        void N##_iterator_end(struct N *l, struct N##_iterator *i)             \
        {                                                                      \
                i->_curr = l->_tail;                                           \
        }                                                                      \
                                                                               \
        void N##_iterator_cend(const struct N *const l,                        \
                               struct N##_iterator *i)                         \
        {                                                                      \
                i->_curr = l->_tail;                                           \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_end(struct N *l)                               \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_end(l, &i);                                       \
                return i;                                                      \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_cend(const struct N *const l)                  \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_cend(l, &i);                                      \
                return i;                                                      \
        }                                                                      \
                                                                               \
        int N##_iterator_equal(const struct N##_iterator first,                \
                               const struct N##_iterator second)               \
        {                                                                      \
                return first._curr == second._curr;                            \
        }                                                                      \
                                                                               \
        int N##_iterator_valid(const struct N##_iterator i)                    \
        {                                                                      \
                return i._curr != NULL;                                        \
        }

