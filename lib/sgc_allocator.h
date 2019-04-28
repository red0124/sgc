#pragma once

#define SGC_INIT_HEADERS_ALLOCATOR_N(_1, _2, _3, _4, NAME, ...) NAME
#define SGC_INIT_HEADERS_ALLOCATOR(...)                                        \
        SGC_INIT_HEADERS_ALLOCATOR_N(__VA_ARGS__, SGC_INIT_HEADERS_ALLOCATOR4, \
                                     SGC_HEADERS_INIT_ALLOCATOR3)              \
        (__VA_ARGS__)

#define SGC_INIT_HEADERS_ALLOCATOR3(MALLOC, REALLOC, FREE)                     \
        SGC_INIT_HEADERS_ALLOCATOR4(MALLOC, REALLOC, FREE, extern);

#define SGC_INIT_HEADERS_ALLOCATOR4(MALLOC, REALLOC, FREE, F)                  \
        F void *sgc_malloc(size_t n);                                          \
        F void *sgc_realloc(void *addr, size_t n);                             \
        F void sgc_free(void *addr);

#define SGC_INIT_ALLOCATOR_N(_1, _2, _3, _4, NAME, ...) NAME
#define SGC_INIT_ALLOCATOR(...)                                                \
        SGC_INIT_ALLOCATOR_N(__VA_ARGS__, SGC_INIT_ALLOCATOR4,                 \
                             SGC_INIT_ALLOCATOR3)                              \
        (__VA_ARGS__)

#define SGC_INIT_ALLOCATOR3(MALLOC, REALLOC, FREE)                             \
        SGC_INIT_ALLOCATOR4(MALLOC, REALLOC, FREE, static inline);

#define SGC_INIT_ALLOCATOR4(MALLOC, REALLOC, FREE, F)                          \
        SGC_INIT_HEADERS_ALLOCATOR4(MALLOC, REALLOC, FREE, F)                  \
        F void *sgc_malloc(size_t n)                                           \
        {                                                                      \
                return MALLOC(n);                                              \
        }                                                                      \
                                                                               \
        F void *sgc_realloc(void *addr, size_t n)                              \
        {                                                                      \
                return REALLOC(addr, n);                                       \
        }                                                                      \
                                                                               \
        F void sgc_free(void *addr)                                            \
        {                                                                      \
                FREE(addr);                                                    \
        }

#ifndef SGC_FAIL
#define SGC_FAIL exit(1);
#endif

#ifdef SGC_SAFE_ALLOCATOR
static void *sgc_safe_malloc(size_t n)
{
        void *ret = malloc(n);
        if(!ret)
        {
                SGC_FAIL;
        }
        return ret;
}

static void *sgc_safe_realloc(void *addr, size_t n)
{
        void *ret = realloc(addr, n);
        if(!ret)
        {
                SGC_FAIL;
        }
        return ret;
}

static void sgc_safe_free(void *addr)
{
        free(addr);
}

SGC_INIT_ALLOCATOR(sgc_safe_malloc, sgc_safe_realloc, sgc_safe_free,
                   static inline);

#else
#ifndef SGC_CUSTOM_ALLOCATOR
SGC_INIT_ALLOCATOR(malloc, realloc, free, static inline);
#endif
#endif
