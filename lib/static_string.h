#pragma once

#define SGC_INIT_STATIC_STRING(S, N)                                           \
                                                                               \
        typedef char N[S];                                                     \
        typedef char N##_value;                                                \
        typedef char N##_type;                                                 \
        typedef char N##_key;                                                  \
                                                                               \
        void N##_copy(N *first, const N *const second)                         \
        {                                                                      \
                if(*second)                                                    \
                {                                                              \
                        size_t size = strlen(*second) + 1;                     \
                        memcpy(*first, *second, size);                         \
                }                                                              \
                else                                                           \
                {                                                              \
                        *first[0] = '\0';                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        void N##_init(N *s)                                                    \
        {                                                                      \
                **s = '\0';                                                  \
        }                                                                      \
                                                                               \
        void N##_free(N *s)                                                    \
        {                                                                      \
		(void)s;\
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
                const char* str = (const char*)*s;                             \
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
                size_t len = strlen(*s);                            \
		if(len + 1 < S)\
		{\
			(*s)[len] = c;                                                 \
			(*s)[len + 1] = '\0';                                          \
		}\
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
                        N##_copy(first, (const N* const)&second_p);            \
                }                                                              \
        }                                                                      \
                                                                               \
        int N##_read(N* s, FILE *f)                                            \
        {                                                                      \
                return fgets(*s, S - 1, f) != NULL;                            \
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
        int N##_read_untill(N* s, FILE *f, const char *const del)              \
        {                                                                      \
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
                        memcpy(s, buff, sizeof(char) * (size + 1));            \
                }                                                              \
		return size != 0;\
        }                                                                      \
                                                                               \
        int N##_read_file(N* s, const char *const file_name)                   \
        {                                                                      \
                FILE *f = fopen(file_name, "r");                               \
                int ret = N##_read_untill(s, f, "");                           \
                fclose(f);                                                     \
		return ret;\
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
                i->_curr = (char*)*s;                                        \
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
                i->_curr = (char*)*s + strlen(*s) - 1;                         \
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
                i->_curr = (char*)*s + at;                                     \
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
