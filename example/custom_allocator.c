#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SGC_CUSTOM_ALLOCATOR
#define POOL_SIZE 10000

#include <SGC/forward_list.h>
#include <SGC/string.h>

static char *mem_pool;
static size_t mem_size;

void mem_init(char *pool, size_t size)
{
        mem_pool = pool;
        mem_size = size;
}

void *mem_alloc(size_t n)
{
	void* ret = NULL;
	if(mem_size >= n)
	{
		ret = mem_pool;
		mem_pool += n;
		mem_size -= n;
	}

        return ret;
}

void *mem_realloc(void *addr, size_t n)
{
        (void)n;
        return addr;
}

void mem_free(void *addr)
{
        (void)addr;
}

SGC_INIT_ALLOCATOR(mem_alloc, mem_realloc, mem_free);

SGC_INIT(STRING, string);
SGC_INIT(FORWARD_LIST, string, list);

int main(void)
{
        char pool[POOL_SIZE];
	mem_init(pool, POOL_SIZE);

	list l;
	list_init(&l);

	static_string buff;
	while(string_buffer_read_until(buff, stdin, "\n "))
	{
		list_push_back(&l, buff);
	}

	fore(i in l as list)
	{
		printf("%s\n", *i);
	}

	list_free(&l);
        return 0;
}
