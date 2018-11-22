#pragma once

#define INIT_STRING(N)                                                         \
                                                                               \
        typedef char *N;                                                       \
                                                                               \
        void N##_copy(N *first, const N *const second)                         \
        {                                                                      \
                if(*second)                                                    \
                {                                                              \
                        size_t size = strlen(*second) + 1;                     \
                        *first = (N)malloc(sizeof(char) * size);               \
                        memcpy(*first, *second, size);                         \
                }                                                              \
                else                                                           \
                {                                                              \
                        *first = NULL;                                         \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_init(N *s)                                                    \
        {                                                                      \
                *s = NULL;                                                     \
        }                                                                      \
                                                                               \
        void N##_free(N *s)                                                    \
        {                                                                      \
                free(*s);                                                      \
        }                                                                      \
                                                                               \
        int N##_equal(const N *const first, const N *const second)             \
        {                                                                      \
                int ret = 0;                                                   \
                if(*first && *second)                                          \
                {                                                              \
                        ret = strcmp(*first, *second) == 0;                    \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        int N##_compare(const N *const first, const N *const second)           \
        {                                                                      \
                return strcmp(*first, *second);                                \
        }                                                                      \
                                                                               \
        int N##_void_compare(const void *const first,                          \
                             const void *const second)                         \
        {                                                                      \
                return strcmp(*(N *)first, *(N *)second);                      \
        }                                                                      \
                                                                               \
        size_t N##_hash(const string *const s)                                 \
        {                                                                      \
                size_t hash = 5381;                                            \
                string str = *s;                                               \
                int c;                                                         \
                                                                               \
                while((c = *str++))                                            \
                {                                                              \
                        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */   \
                }                                                              \
                                                                               \
                return hash;                                                   \
        }                                                                      \
                                                                               \
        void N##_push_back(N *, char);                                         \
                                                                               \
        static void (*N##_default_insert_function)(N *, char) = N##_push_back; \
                                                                               \
        void N##_set_default_insert(void (*insert)(N *, char))                 \
        {                                                                      \
                N##_default_insert_function = insert;                          \
        }                                                                      \
                                                                               \
        void N##_default_insert(N *d, char el)                                 \
        {                                                                      \
                N##_default_insert_function(d, el);                            \
        }                                                                      \
                                                                               \
        void N##_push_back(N *s, const char c)                                 \
        {                                                                      \
		size_t len = (*s) ? strlen(*s) : 0;\
                *s = (N)realloc(*s, sizeof(char) * (len + 2));                 \
                (*s)[len] = c;                                                 \
                (*s)[len + 1] = '\0';                                          \
        }                                                                      \
                                                                               \
        void N##_pop_back(N *s)                                                \
        {                                                                      \
                size_t len = strlen(*s);                                       \
                if(len)                                                        \
                {                                                              \
                        (*s)[len - 1] = '\0';                                  \
                }                                                              \
        }                                                                      \
                                                                               \
        int N##_read_buffer(N *s, FILE *f, char *buff, size_t buff_size)       \
        {                                                                      \
                char *tmp = fgets(buff, buff_size, f);                         \
                if(tmp)                                                        \
                {                                                              \
                        size_t size = strlen(buff);                            \
                        buff[size - 1] = '\0';                                 \
                        *s = (N)malloc(sizeof(char) * (size));                 \
                        memcpy(*s, buff, sizeof(char) * (size));               \
                }                                                              \
                return (int)(*tmp);                                            \
        }                                                                      \
                                                                               \
        static int N##_char_find(const char *const del, char c)                \
        {                                                                      \
                int ret = 0;                                                   \
                size_t size = strlen(del);                                     \
                for(size_t i = 0; i < size; ++i)                               \
                {                                                              \
                        if(del[i] == c)                                        \
                        {                                                      \
                                ret = 1;                                       \
                                break;                                         \
                        }                                                      \
                }                                                              \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        int N##_read_untill(N *s, FILE *f, char *del)                          \
        {                                                                      \
                *s = NULL;                                                     \
                char c;                                                        \
                size_t size = 0;                                               \
                size_t max = 0;                                                \
                while(1)                                                       \
                {                                                              \
                        if(fscanf(f, "%c", &c) == EOF)                         \
                        {                                                      \
                                break;                                         \
                        }                                                      \
                        int finish = N##_char_find(del, c);                    \
                        if(finish == 1)                                        \
                        {                                                      \
                                break;                                         \
                        }                                                      \
                        if(size == max)                                        \
                        {                                                      \
                                max = (max == 0) ? 1 : 2 * max;                \
                                *s = (N)realloc(*s, sizeof(char) * (max + 1)); \
                        }                                                      \
                        (*s)[size++] = c;                                      \
                }                                                              \
                if(size)                                                       \
                {                                                              \
                        (*s)[size] = '\0';                                     \
                }                                                              \
                return size;                                                   \
        }                                                                      \
                                                                               \
        int N##_read(N *s, FILE *f)                                            \
        {                                                                      \
                return N##_read_untill(s, f, " \n");                           \
        }                                                                      \
                                                                               \
        int N##_read_file(N *s, const char *const file_name)                   \
        {                                                                      \
                FILE *f = fopen(file_name, "r");                               \
                int ret = N##_read_untill(s, f, "");                           \
                fclose(f);                                                     \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        struct N##_array                                                       \
        {                                                                      \
                N *data;                                                       \
                size_t size;                                                   \
                size_t max;                                                    \
        };                                                                     \
                                                                               \
        typedef struct N##_array N##_array;                                    \
                                                                               \
        static void N##_array_push_back(N##_array *a, N el)                    \
        {                                                                      \
                if(a->size == a->max)                                          \
                {                                                              \
                        a->max = (a->max) ? 2 * (a->max) : 1;                  \
                        a->data = (N *)realloc(a->data, sizeof(N) * a->max);   \
                }                                                              \
                a->data[a->size++] = el;                                       \
        }                                                                      \
                                                                               \
        N##_array N##_split(N s, const char *const del)                        \
        {                                                                      \
                N##_array a = {NULL, 0, 0};                                    \
                N tmp = strtok(s, del);                                        \
                while(tmp)                                                     \
                {                                                              \
                        N##_array_push_back(&a, tmp);                          \
                        tmp = strtok(NULL, del);                               \
                }                                                              \
                return a;                                                      \
        }                                                                      \
                                                                               \
        struct N##_iterator                                                    \
        {                                                                      \
                char *_curr;                                                   \
        };                                                                     \
                                                                               \
        char *N##_iterator_value(struct N##_iterator i)                        \
        {                                                                      \
                return i._curr;                                                \
        }                                                                      \
                                                                               \
        const char *N##_iterator_cvalue(const struct N##_iterator i)           \
        {                                                                      \
                return i._curr;                                                \
        }                                                                      \
                                                                               \
        void N##_iterator_next(struct N##_iterator *i)                         \
        {                                                                      \
                ++i->_curr;                                                    \
        }                                                                      \
                                                                               \
        void N##_iterator_prev(struct N##_iterator *i)                         \
        {                                                                      \
                --i->_curr;                                                    \
        }                                                                      \
                                                                               \
        void N##_iterator_begin(N *s, struct N##_iterator *i)                  \
        {                                                                      \
                i->_curr = *s;                                                 \
        }                                                                      \
                                                                               \
        void N##_iterator_cbegin(const N *const s, struct N##_iterator *i)     \
        {                                                                      \
                i->_curr = *s;                                                 \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_begin(N *s)                                    \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_begin(s, &i);                                     \
                return i;                                                      \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_cbegin(const N *const s)                       \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_cbegin(s, &i);                                    \
                return i;                                                      \
        }                                                                      \
                                                                               \
        void N##_iterator_end(N *s, struct N##_iterator *i)                    \
        {                                                                      \
                i->_curr = *s + strlen(*s) - 1;                                \
        }                                                                      \
                                                                               \
        void N##_iterator_cend(const N *const s, struct N##_iterator *i)       \
        {                                                                      \
                i->_curr = *s + strlen(*s) - 1;                                \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_end(N *s)                                      \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_end(s, &i);                                       \
                return i;                                                      \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_cend(const N *const s)                         \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_cend(s, &i);                                      \
                return i;                                                      \
        }                                                                      \
                                                                               \
        void N##_iterator_from(N *s, struct N##_iterator *i, size_t at)        \
        {                                                                      \
                i->_curr = *s + at;                                            \
        }                                                                      \
                                                                               \
        void N##_iterator_cfrom(const N *const s, struct N##_iterator *i,      \
                                size_t at)                                     \
        {                                                                      \
                i->_curr = *s + at;                                            \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_from(N *s, size_t at)                          \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_from(s, &i, at);                                  \
                return i;                                                      \
        }                                                                      \
                                                                               \
        struct N##_iterator N##_cfrom(const N *const s, size_t at)             \
        {                                                                      \
                struct N##_iterator i;                                         \
                N##_iterator_cfrom(s, &i, at);                                 \
                return i;                                                      \
        }                                                                      \
                                                                               \
        void N##_iterator_jump(struct N##_iterator *i, ssize_t range)          \
        {                                                                      \
                i->_curr = i->_curr + range;                                   \
        }                                                                      \
                                                                               \
        int N##_iterator_equal(const struct N##_iterator first,                \
                               const struct N##_iterator second)               \
        {                                                                      \
                return first._curr == second._curr;                            \
        }                                                                      \
                                                                               \
        ssize_t N##_iterator_range(const struct N##_iterator first,            \
                                   const struct N##_iterator second)           \
        {                                                                      \
                return second._curr - first._curr;                             \
        }                                                                      \
                                                                               \
        int N##_iterator_valid(const struct N##_iterator i)                    \
        {                                                                      \
                return 1;                                                      \
        }
