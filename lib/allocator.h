#pragma once

#define SGC_INIT_ALLOCATOR(MALLOC, REALLOC, FREE)                              \
        void *sgc_malloc(size_t n)                                             \
        {                                                                      \
                return MALLOC(n);                                              \
        }                                                                      \
                                                                               \
        void *sgc_realloc(void *addr, size_t n)                                \
        {                                                                      \
                return REALLOC(addr, n);                                       \
        }                                                                      \
                                                                               \
        void sgc_free(void *addr)                                              \
        {                                                                      \
                FREE(addr);                                                    \
        }

#ifndef SGC_CUSTOM_ALLOCATOR
#define SGC_CUSTOM_ALLOCATOR
SGC_INIT_ALLOCATOR(malloc, realloc, free);

#endif
