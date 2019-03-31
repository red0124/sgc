#pragma once

#define SGC_INIT_HEADER_ITERATE(T, N)                                              \
        void N##_fold(struct N##_iterator begin, struct N##_iterator end,      \
                      void (*fun)(const T *const, void *), void *argout);      \
                                                                               \
        void N##_execute(struct N##_iterator begin, struct N##_iterator end,   \
                         void (*fun)(const T *const));                         \
                                                                               \
        void N##_write(struct N##_iterator begin, struct N##_iterator end,     \
                       const char *const format, FILE *file);                  \
                                                                               \
        void N##_stdout(const struct N *const c, const char *const format);    \
                                                                               \
        void N##_fold_reverse(                                                 \
            struct N##_iterator begin, struct N##_iterator end,                \
            void (*fun)(const T *const, void *), void *argout);                \
                                                                               \
        void N##_execute_reverse(struct N##_iterator begin,                    \
                                 struct N##_iterator end,                      \
                                 void (*fun)(const T *const));                 \
                                                                               \
        void N##_write_reverse(struct N##_iterator begin,                      \
                               struct N##_iterator end,                        \
                               const char *const format, FILE *file);          \
                                                                               \
        void N##_stdout_reverse(const struct N *const c,                       \
                                const char *const format);

#define SGC_INIT_HEADER_ITERATE_PAIR(K, V, N)                                      \
        void N##_fold_pair(                                                    \
            struct N##_iterator begin, struct N##_iterator end,                \
            void (*fun)(const K *const, const V *const, void *),               \
            void *argout);                                                     \
                                                                               \
        void N##_execute_pair(struct N##_iterator begin,                       \
                              struct N##_iterator end,                         \
                              void (*fun)(const K *const, const V *const));    \
                                                                               \
        void N##_write_pair(struct N##_iterator begin,                         \
                            struct N##_iterator end, const char *const format, \
                            FILE *file);                                       \
                                                                               \
        void N##_stdout_pair(const struct N *const c,                          \
                             const char *const format);                        \
                                                                               \
        void N##_fold_reverse_pair(                                            \
            struct N##_iterator begin, struct N##_iterator end,                \
            void (*fun)(const K *const, const V *const, void *),               \
            void *argout);                                                     \
                                                                               \
        void N##_execute_reverse_pair(                                         \
            struct N##_iterator begin, struct N##_iterator end,                \
            void (*fun)(const K *const, const V *const));                      \
                                                                               \
        void N##_write_reverse_pair(struct N##_iterator begin,                 \
                                    struct N##_iterator end,                   \
                                    const char *const format, FILE *file);     \
                                                                               \
        void N##_stdout_reverse_pair(const struct N *const c,                  \
                                     const char *const format);

#define SGC_INIT_HEADER_WRITE_SELECT(T, N, ...)                                    \
        void N##_write_select(struct N##_iterator begin,                       \
                              struct N##_iterator end,                         \
                              const char *const format, FILE *file);           \
                                                                               \
        void N##_stdout_select(const struct N *const c,                        \
                               const char *const format);                      \
                                                                               \
        void N##_write_select_reverse(struct N##_iterator begin,               \
                                      struct N##_iterator end,                 \
                                      const char *const format, FILE *file);   \
                                                                               \
        void N##_stdout_select_reverse(const struct N *const c,                \
                                       const char *const format);

#define SGC_INIT_HEADER_WRITE_PAIR_SELECT(K, V, N, ...)                            \
        void N##_write_select_pair(struct N##_iterator begin,                  \
                                   struct N##_iterator end,                    \
                                   const char *const format, FILE *file);      \
                                                                               \
        void N##_stdout_select_pair(const struct N *const c,                   \
                                    const char *const format);                 \
                                                                               \
        void N##_write_select_reverse_pair(                                    \
            struct N##_iterator begin, struct N##_iterator end,                \
            const char *const format, FILE *file);                             \
                                                                               \
        void N##_stdout_select_reverse_pair(const struct N *const c,           \
                                            const char *const format);

#define SGC_INIT_HEADER_FIND(T, N)                                                 \
        T *N##_find(struct N##_iterator begin, struct N##_iterator end,        \
                    const T el);                                               \
                                                                               \
        size_t N##_find_index(const struct N *const c, const T el);

#define SGC_INIT_HEADER_BINARY_FIND(T, N)                                          \
        T *N##_binary_find(struct N *c, const T el);                           \
                                                                               \
        size_t N##_binary_find_index(struct N *c, const T el);

#define SGC_INIT_HEADER_QSORT(T, N)                                                \
        void N##_qsort(void *array, size_t array_size,                         \
                       int (*comp)(const void *, const void *));
