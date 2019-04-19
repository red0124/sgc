#pragma once

#ifndef SGC_STRING_BUFF_SIZE
#define SGC_STRING_BUFF_SIZE 128
#endif

#define SGC_INIT_STRING_N(_1, _2, NAME, ...) NAME
#define SGC_INIT_STRING(...)                                                   \
        SGC_INIT_STRING_N(__VA_ARGS__, SGC_INIT_STRING2, SGC_INIT_STRING1)     \
        (__VA_ARGS__);

#define SGC_INIT_STRING2(S, N) SGC_INIT_STRING_WITH_BUFFER(N, S);
#define SGC_INIT_STRING1(N)                                                    \
        SGC_INIT_STRING_WITH_BUFFER(N, SGC_STRING_BUFF_SIZE);

#define SGC_INIT_HEADERS_STRING_N(_1, _2, NAME, ...) NAME
#define SGC_INIT_HEADERS_STRING(...)                                           \
        SGC_INIT_HEADERS_STRING_N(__VA_ARGS__, SGC_INIT_HEADERS_STRING2,       \
                                  SGC_INIT_HEADERS_STRING1)                    \
        (__VA_ARGS__);

#define SGC_INIT_HEADERS_STRING2(S, N)                                         \
        SGC_INIT_HEADERS_STRING_WITH_BUFFER(N, S);

#define SGC_INIT_HEADERS_STRING1(N)                                            \
        SGC_INIT_HEADERS_STRING_WITH_BUFFER(N, SGC_STRING_BUFF_SIZE);

#define SGC_INIT_HEADERS_STRING_WITH_BUFFER(N, S)                              \
        static int N##_char_find(const char *const del, char c);

#define SGC_INIT_STATIC_FUNCTIONS_STRING_WITH_BUFFER(N, S)                     \
                                                                               \
        typedef char *N;                                                       \
        typedef char N##_value;                                                \
        typedef char static_##N[S];                                            \
                                                                               \
        void N##_copy(N *first, const N *const second);                        \
        void N##_init(N *s);                                                   \
        void N##_free(N *s);                                                   \
        int N##_equal(const N *const first, const N *const second);            \
        int N##_compare(const N *const first, const N *const second);          \
        int N##_void_compare(const void *const first,                          \
                             const void *const second);                        \
        size_t N##_hash(const N *const s);                                     \
        void N##_push_back(N *s, const char c);                                \
        void N##_pop_back(N *s);                                               \
        void N##_from_cstring(N *first, const char *const second);             \
        N N##_create(const char *const second);                                \
        N N##_read(FILE *f);                                                   \
        N N##_buffer_read_untill(N s, FILE *f, const char *const del);         \
        N N##_read_untill(FILE *f, const char *const del);                     \
        N N##_read_file(const char *const file_name);                          \
                                                                               \
        struct N##_iterator                                                    \
        {                                                                      \
                char *_curr;                                                   \
        };                                                                     \
                                                                               \
        char *N##_iterator_data(struct N##_iterator i);                        \
        const char *N##_iterator_cdata(const struct N##_iterator i);           \
        void N##_iterator_next(struct N##_iterator *i);                        \
        void N##_iterator_prev(struct N##_iterator *i);                        \
        void N##_iterator_begin(N *s, struct N##_iterator *i);                 \
        void N##_iterator_cbegin(const N *const s, struct N##_iterator *i);    \
        struct N##_iterator N##_begin(N *s);                                   \
        struct N##_iterator N##_cbegin(const N *const s);                      \
        void N##_iterator_end(N *s, struct N##_iterator *i);                   \
        void N##_iterator_cend(const N *const s, struct N##_iterator *i);      \
        struct N##_iterator N##_end(N *s);                                     \
        struct N##_iterator N##_cend(const N *const s);                        \
        void N##_iterator_from(N *s, struct N##_iterator *i, size_t at);       \
        void N##_iterator_cfrom(const N *const s, struct N##_iterator *i,      \
                                size_t at);                                    \
        struct N##_iterator N##_from(N *s, size_t at);                         \
        struct N##_iterator N##_cfrom(const N *const s, size_t at);            \
        void N##_iterator_jump(struct N##_iterator *i, ssize_t range);         \
        int N##_iterator_equal(const struct N##_iterator first,                \
                               const struct N##_iterator second);              \
        ssize_t N##_iterator_range(const struct N##_iterator first,            \
                                   const struct N##_iterator second);          \
        int N##_iterator_valid(const struct N##_iterator i);

#define SGC_INIT_STRING_WITH_BUFFER(N, S)                                      \
        SGC_INIT_HEADERS_STRING_WITH_BUFFER(N, S);                             \
        SGC_INIT_STATIC_FUNCTIONS_STRING_WITH_BUFFER(N, S);                    \
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
        size_t N##_hash(const N *const s)                                      \
        {                                                                      \
                size_t hash = 5381;                                            \
                N str = *s;                                                    \
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
        void N##_push_back(N *s, const char c)                                 \
        {                                                                      \
                size_t len = (*s) ? strlen(*s) : 0;                            \
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
        void N##_from_cstring(N *first, const char *const second)              \
        {                                                                      \
                if(*second)                                                    \
                {                                                              \
                        char *const second_p = (char *)second;                 \
                        N##_copy(first, &second_p);                            \
                }                                                              \
        }                                                                      \
                                                                               \
        N N##_create(const char *const second)                                 \
        {                                                                      \
                N ret = NULL;                                                  \
                N##_from_cstring(&ret, second);                                \
                return ret;                                                    \
        }                                                                      \
                                                                               \
        N N##_read(FILE *f)                                                    \
        {                                                                      \
                N s = NULL;                                                    \
                char buff[S] = "\0";                                           \
                if(fgets(buff, S - 1, f))                                      \
                {                                                              \
                        size_t size = strlen(buff);                            \
                        s = (N)malloc(sizeof(char) * (size + 1));              \
                        memcpy(s, buff, sizeof(char) * (size + 1));            \
                }                                                              \
                return s;                                                      \
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
        N N##_buffer_read_untill(N s, FILE *f, const char *const del)          \
        {                                                                      \
                char c;                                                        \
                size_t size = 0;                                               \
                while(1)                                                       \
                {                                                              \
                        c = fgetc(f);                                          \
                        if(c == EOF || N##_char_find(del, c))                  \
                        {                                                      \
                                break;                                         \
                        }                                                      \
                        s[size++] = c;                                         \
                }                                                              \
                s[size] = '\0';                                                \
                return (size == 0) ? NULL : s;                                 \
        }                                                                      \
                                                                               \
        N N##_read_untill(FILE *f, const char *const del)                      \
        {                                                                      \
                N s = NULL;                                                    \
                char c;                                                        \
                size_t size = 0;                                               \
                char buff[S] = "\0";                                           \
                while(1)                                                       \
                {                                                              \
                        c = fgetc(f);                                          \
                        if(c == EOF || N##_char_find(del, c))                  \
                        {                                                      \
                                break;                                         \
                        }                                                      \
                        buff[size++] = c;                                      \
                }                                                              \
                if(size)                                                       \
                {                                                              \
                        buff[size] = '\0';                                     \
                        size_t size = strlen(buff);                            \
                        s = (N)malloc(sizeof(char) * (size + 1));              \
                        memcpy(s, buff, sizeof(char) * (size + 1));            \
                }                                                              \
                return s;                                                      \
        }                                                                      \
                                                                               \
        N N##_read_file(const char *const file_name)                           \
        {                                                                      \
                N s;                                                           \
                FILE *f = fopen(file_name, "r");                               \
                s = N##_read_untill(f, "");                                    \
                fclose(f);                                                     \
                return s;                                                      \
        }                                                                      \
                                                                               \
        char *N##_iterator_data(struct N##_iterator i)                         \
        {                                                                      \
                return i._curr;                                                \
        }                                                                      \
                                                                               \
        const char *N##_iterator_cdata(const struct N##_iterator i)            \
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
                (void)i;                                                       \
                return 1;                                                      \
        }
