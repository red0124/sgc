#pragma once

#ifndef SGC_FAIL
#define SGC_FAIL exit(EXIT_FAILURE);
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

#define sgc_malloc(n) sgc_safe_malloc(n)
#define sgc_realloc(a, n) sgc_safe_realloc(a, n)
#define sgc_free(a) sgc_safe_free(a)

#else
#define sgc_malloc(n) malloc(n);
#define sgc_realloc(a, n) realloc(a, n)
#define sgc_free(a) free(a)

#endif

