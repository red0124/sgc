#pragma once

#define INIT_STRING(N)                                                         \
                                                                               \
        typedef char *N;                                                       \
                                                                               \
        int N##_is_static()                                                    \
        {                                                                      \
                return 0;                                                      \
        }                                                                      \
                                                                               \
        void N##_copy(N *first, const N *const second)                         \
        {                                                                      \
                *first = (N)malloc(sizeof(char) * (1 + strlen(*second)));      \
                strcpy(*first, *second);                                       \
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
                return strcmp(*first, *second) == 0;                           \
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
                return *(int *)tmp;                                            \
        }                                                                      \
        /*                                                                     \
static int N##_char_compare(const void *const first,                           \
const void *const second)                                                      \
{                                                                              \
return *(char *)first - *(char *)second;                                       \
}                                                                              \
                         \                                                     \
static int N##_char_binary_find(char *del, char c)                             \
{                                                                              \
int ret = 0;                                                                   \
size_t size = strlen(del);                                                     \
qsort(del, size, sizeof(char), N##_char_compare);                              \
printf("%s\n", del);                                                           \
if(c >= del[0] && c <= del[size - 1])                                          \
{                                                                              \
size_t l = 0;                                                                  \
size_t r = size - 1;                                                           \
size_t m;                                                                      \
while(l <= r)                                                                  \
{                                                                              \
m = l + (r - l) / 2;                                                           \
if(del[m] < c)                                                                 \
{                                                                              \
l = m + 1;                                                                     \
}                                                                              \
else if(del[m] > c)                                                            \
{                                                                              \
r = m - 1;                                                                     \
}                                                                              \
else                                                                           \
{                                                                              \
ret = 1;                                                                       \
break;                                                                         \
}                                                                              \
}                                                                              \
}                                                                              \
return ret;                                                                    \
} */                                                                           \
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
        }\
