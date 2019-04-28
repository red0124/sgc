#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SGC_CUSTOM_ALLOCATOR

#include <SGC/list.h>
#include <SGC/string.h>
#include <SGC/static_unordered_set.h>

// this custom allocator uses an unordered_set to store
// the addresses of the allocated memory blocks
// can't think of a simpler one, just a malloc wraper, 
// a bit pointless but perevents leaks and double freeing

SGC_INIT_STATIC(UNORDERED_SET, long, 100, set);
set used_addrs;

void *my_malloc(size_t n)
{
        void *addr = malloc(n);
        set_insert(&used_addrs, (long)addr);
        return addr;
}

void *my_realloc(void *addr, size_t n)
{
        void *old_addr = addr;
        addr = realloc(addr, n);
        set_insert(&used_addrs, (long)addr);
        if(addr != old_addr)
        {
                set_erase(&used_addrs, (long)old_addr);
        }
        return addr;
}

void my_free(void *addr)
{
        struct set_iterator it = set_find(&used_addrs, (long)addr);
        if(set_iterator_valid(it))
        {
                set_iterator_erase(&used_addrs, &it);
                free(addr);
        }
        else
        {
                printf("double free prevented\n");
        }
}

void my_allocator_init(void)
{
        set_init(&used_addrs);
}

void my_allocator_clean(void)
{
        for_each(i in used_addrs as set)
        {
                my_free((void *)*i);
        }
	set_free(&used_addrs);
}

SGC_INIT_ALLOCATOR(my_malloc, my_realloc, my_free);
SGC_INIT(STRING, string);
SGC_INIT(LIST, string, list);

int main(void)
{
        my_allocator_init();

        list l;
        list_init(&l);
        list_set_share(&l, 1);

        string s;
        string_from_cstring(&s, "hello");

        list_push_back(&l, s);
        list_push_back(&l, s);
        list_push_back(&l, s);
        list_push_back(&l, s);

	// this will free all memory
        my_allocator_clean();

	// tries double free
        my_free(s);
        return 0;
}

