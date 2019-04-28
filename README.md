# Semi-Generic C 1.0.0
Algorithms and data structures written in **C** using macros. The data structures used are similar to the ones used in the **C++ STL** with little difference.

# Simple Example

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SGC/vector.h>

struct person
{
        char first_name[32];
        char last_name[32];
        int age;
};

SGC_INIT(STATIC_STRUCT, struct person, person);
SGC_INIT(VECTOR, person, vec);

int main(void)
{
        vec v;
        vec_init(&v);

        vec_push_back(&v, (person){"a", "a", 10});
        vec_push_back(&v, (person){"b", "b", 20});
        vec_push_back(&v, (person){"c", "c", 30});

        sgc_for_each(i, v, vec)
        {
                printf("%s %s %d\n", i->first_name, i->last_name, i->age);
        }

        vec_free(&v);
        return 0;
}
```

Output:
```bash
$ ./program
a a 10
b b 20
c c 30
$ 
```

# Content
 - [Purpose](#purpose)
 - [Install](#install)
 - [Usage](#how-to-use-it)
 - [Benchmarks](#benchmarks)
 - [Examples](#examples)

# Purpose
  - Can be used used anywhere without any dependencies, just the standard library.
  - It is as simple as possible to use.
  - Can be used on any data type.
  - Fast since it does not use **void*** as elements.
  - Memory can be shared.
  - Separate compiling is possible.
  - It has static containers which do not need memory allocation making them usable for **microcontrollers**.
  - It has support for custom allocators

[> Back to content](#content)
# Install
Just run the following commands in your shell:
```bash
$ git clone https://gitlab.com/ado0/sgc
$ cd sgc
$ sudo make install
```
The source files will be installed to your include file and are ready for usage. 

[> Back to content](#content)
## How to use it:
The headers are located int the **SGC** directory in your include file, simply include them like this:
```c
// examples
#include <SGC/vector.h>
#include <SGC/algorithm.h>
#include <SGC/static_unordered_map.h>
// ...
```

The algorithms and data structures are initialized using the **SGC_INIT** macro defined in **SGC/algorithm.h**:

```c
SGC_INIT(CONTAINER, type, name[, ALGORITHMS]);
```
**CONTAINER  ::**  type of the container we initialize
**type ::**  type of the elements we are storing
**name ::** name given to your newly created functions and structures
** ALGORITHMS :: (optional)** algorithms to be initialized with the container

The **name** has to be a single word (use typedef if needed).

The macro will generate algorithms and data structures required for the container with the optional algorithms if defined.

Map-like containers require a key and a value instead of the type alone, so we have to use a different macro:

```c
SGC_INIT_PAIR(CONTAINER, key, value, name[, ALGORITHMS]);
```
**key ::**  type of the key we are storing
**value ::**  type of the value we are storing

And finally static containers who also require the size of the container to be predefined:

```c
SGC_INIT_STATIC(CONTAINER, type, size, name[, ALGORITHMS]);
SGC_INIT_STATIC_PAIR(CONTAINER, key, value, size, name[, ALGORITHMS]);
```
**size ::**  the capacity of the container

More on those later.
```c
// examples

// vector of ints named my_vector 
// includes ITERATE and FIND algorithms
SGC_INIT(VECTOR, int, my_vector, ITERATE, FIND);

// map with chars as keys and doubles as values named map
SGC_INIT_PAIR(MAP, char, double, map);

// statid deque of floats with the capacity of 100 elements named dq
SGC_INIT_STATIC(DEQUE, float, 100, dq);

// ...
```

The containers may use **malloc**, **free**, **fprintf**, **memcpy**, and other **C** functions so we require those functions to be defined before creating the containers.

Simple example, **"test.c"**:

```c
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <SGC/list.h>
#include <SGC/string.h>
#include <SGC/algorithm.h>

SGC_INIT(STRING, string);
SGC_INIT(LIST, string, list, ITERATE);

int main(void)
{
	list l;
	list_init(&l);
	
	list_push_back(&l, "just");
	list_push_back(&l, "some");
	list_push_back(&l, "random");	
	list_push_back(&l, "strings");
	
	list_fprintf(&l, "%s\n", stdout);
	
	list_free(&l);
	return 0;
}
```

```bash
$ gcc test.c
$ ./a.out
just
some
random
strings
```

First we called **list_init** to set the default values of our structure so we can use it, **push_back** is used to insert some elements into the container, the elements in the container will be a copy of the elements passed into the function, and using **list_free** we free all the memory allocated.

The **ITERATE** algorithm is required to use the **list_fprintf** function.

To use a type as an element of a given container, some functions have to be defined so the container may know how to allocate, copy, free and compare the elements:

```c
// initialize the element
void el_init(el_type* el);

// copy src to dst element
void el_copy(el_type* __restrict__ dst, 
	const el_type* __restrict__ const src);

// destroy the element
void el_free(el_type* el);

// test for equality, returns 1 if equal, 0 othervise
int el_equal(const el_type* const first, 
	const el_type* const second);

// compare two element, requred for MAP, SET, PRIORITY_QUEUE and
// STATIC_PRIORITY_QUEUE
int el_compare(const el_type* const first, 
	const el_type* const second);

// hash, requred for hashed containers, UNORDERED_MAP, 
// UNORDERED_SET, STATIC_UNORDERED_MAP, STATIC_UNORDERED_SET
size_t el_hash(const el_type* const el);
```

If you want to disable copying and destroying elements when using a container simply use the **container_set_share** function:

```c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <SGC/string.h>
#include <SGC/forward_list.h>
#include <SGC/algorithm.h>

SGC_INIT(STRING, string);
SGC_INIT(FORWARD_LIST, string, list);

int main(void)
{
	list l;
	list_init(&l);

	string s;
	string_from_cstring(&s, "hello");

	// allocate memory and copy the string
	list_push_back(&l, s);

	// use the string itself as shared
	list_set_share(&l, 1);
	list_push_back(&l, s);
	list_set_share(&l, 0);

	// this will also free the string since it is shared 
	// so no memory will be left allocated
	list_free(&l);
	return 0;
}
```
Some types have their functions defined by default, and more can be added using the **SGC_INIT_BASIC_TYPE** macro, or when creating a primitive structure (structure of primitive types and primitive structures)  **SGC_INIT_STATIC_STRUCT** :

```c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <SGC/stack.h>

struct point
{
	double x;
	double y;
};

SGC_INIT(STATIC_STRUCT, struct point, pt);
SGC_INIT(STACK, pt, stack);

int main(void)
{
	stack s;
	stack_init(&s);
	stack_push(&s, (pt){1, 2});
	stack_free(&s);
	return 0;
}
```

Containers can also be used as elements for other containers

```c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <SGC/string.h>
#include <SGC/algorithm.h>
#include <SGC/vector.h>
#include <SGC/list.h>

SGC_INIT(STRING, string);
SGC_INIT(VECTOR, string, vector);
SGC_INIT(LIST, vector, list);

int main(void)
{
	list l;
	list_init(&l);

	vector v;
	vector_init(&v);
	vector_push_back(&v, "hello");
	
	list_set_share(&l, 1);
	list_push_back(&l, v);
	list_set_share(&l, 0);

	// no leaks
	list_free(&l);
	return 0;
}
```

An easy way to traverse through the container is by using the **sgc_for_each** macro

```c
sgc_for_each(element, container_instance, container_name);
{
	// actions on element
}
```
**container_name ::** name of the container we iterate through
**container_instance ::** the container we iterate through
**element ::** the name of the pointer we access the elements with

Custom allocators can be set by defining SGC_CUSTOM_ALLOCATOR before including
the header then later calling: 
```c
SGC_INIT_ALLOCATOR(custom_malloc, custom_realloc, custom_free);
```

And your containers will use those instead of the default ones.

[> Back to content](#content)

# Benchmarks
Compared to **C++ STL** libraries.

**Vector push_back**

![alt text](https://gitlab.com/ado0/sgc/raw/master/img/vector_push_back.png)

[> Back to content](#content)

**Vector fetch element**

![alt text](https://gitlab.com/ado0/sgc/raw/master/img/vector_fetch.png)

[> Back to content](#content)

**List push_back**

![alt text](https://gitlab.com/ado0/sgc/raw/master/img/list_push_back.png)

[> Back to content](#content)

**List iterate**

![alt text](https://gitlab.com/ado0/sgc/raw/master/img/list_iterate.png)

[> Back to content](#content)

**Priority Queue push**

![alt text](https://gitlab.com/ado0/sgc/raw/master/img/priority_queue_push.png)

[> Back to content](#content)

**Priority Queue push and pop**

![alt text](https://gitlab.com/ado0/sgc/raw/master/img/priority_queue_pop.png)

[> Back to content](#content)

**Map insert**

![alt text](https://gitlab.com/ado0/sgc/raw/master/img/map_insert.png)

[> Back to content](#content)

**Map fetch**

![alt text](https://gitlab.com/ado0/sgc/raw/master/img/map_fetch.png)

[> Back to content](#content)

**Map iterate**

![alt text](https://gitlab.com/ado0/sgc/raw/master/img/map_iterate.png)

[> Back to content](#content)

**Unordered Map insert**

![alt text](https://gitlab.com/ado0/sgc/raw/master/img/unordered_map_insert.png)

[> Back to content](#content)

**Unordered Map fetch**

![alt text](https://gitlab.com/ado0/sgc/raw/master/img/unordered_map_fetch.png)

[> Back to content](#content)

**Unordered Map iterate**

![alt text](https://gitlab.com/ado0/sgc/raw/master/img/unordered_map_iterate.png)

[> Back to content](#content)

**Static containers have similar performance to their non static counterparts
except the unordered containers since they use closhed hashing compared
to the non static ones which use open hashing.**

**Static Unordered Map insert, C++ map is reserved**

![alt text](https://gitlab.com/ado0/sgc/raw/master/img/static_unordered_map_insert.png)

[> Back to content](#content)

**Static Unordered Map fetch, C++ map is reserved**

![alt text](https://gitlab.com/ado0/sgc/raw/master/img/static_unordered_map_fetch.png)

[> Back to content](#content)

**Static Unordered Map iterate, C++ map is reserved**

![alt text](https://gitlab.com/ado0/sgc/raw/master/img/static_unordered_map_iterate.png)

[> Back to content](#content)
# Examples
## The examples are not ment to be solved the best possible way, they are here just to show the usage of the library !
\>\> Count the number of each word in a file then print every non unique element:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "words.txt"

#include <SGC/string.h>
#include <SGC/unordered_map.h>

SGC_INIT(STRING, string);
SGC_INIT_PAIR(UNORDERED_MAP, string, int, map);

int main(void)
{
        map m;
        map_init(&m);

        static_string buff;
        
        FILE *in = fopen(FILE_NAME, "r");
	while(string_buffer_read_until(buff, in, "\n"))
	{
		++*map_at(&m, buff);
	}
	fclose(in);
	
        sgc_for_each(i, m, map)
        {
	        if(i->value > 1)
	        {
		        printf("%s -> %d", i->key, i->value);
		}
	}
        map_free(&m);
        return 0;
}
```

[> Back to content](#content)

\>\> Simple custom allocator

```c
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
        sgc_for_each(i, used_addrs, set)
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
        s = string_create("hello");

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
```
Output:
```bash
$ ./program
double free prevented
```

[> Back to content](#content)

\>\> Read strings from stdin, save those which are palindromes and store them in a sorted manner into a txt file

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SGC/vector.h>
#include <SGC/string.h>
#include <SGC/algorithm.h>

SGC_INIT(STRING, string);
SGC_INIT(VECTOR, string, vector, QSORT, ITERATE);

int main(void)
{

	char buff[32];
	string s = buff;

	vector v;
	vector_init(&v);

	while(string_buffer_read_until(buff, stdin, "\n "))
	{
		int palindrome = 1;
		sgc_for_each_intersect(i, s, s, string)
		{
			if(*i.first != *i.second)
			{
				palindrome = 0;
				break;
			}
		}
		if(palindrome)
		{
			printf("Perfectly balanced. As all things shoud be.\n");
			vector_push_back(&v, s);
		}
	}

	vector_sort(&v, NULL);

	FILE* f = fopen("out.txt", "w");
	vector_fprintf(&v, "%s\n", f);
	fclose(f);

	vector_free(&v);
        return 0;
}
```

[> Back to content](#content)

\>\> Non preemptive priority scheduler

```c
#include <stdio.h>
#include <string.h>

#include <SGC/static_vector.h>
#include <SGC/static_priority_queue.h>

struct task
{
	void (*fun)(void);
	int priority;
	int initital_priority;
};

int task_compare(const struct task* first,
		 const struct task* second)
{
	return first->priority - second->priority;
}

#define MAX_TASKS 32

SGC_INIT_STATIC(STRUCT, struct task, task);
SGC_INIT_STATIC(PRIORITY_QUEUE, task, MAX_TASKS, pqueue);
SGC_INIT_STATIC(VECTOR, task, MAX_TASKS, vector);

pqueue sched_pqueue;
vector sched_vector;

void sched_init(void)
{
	pqueue_init(&sched_pqueue);
	vector_init(&sched_vector);
}

void sched_add(void (*fun)(void), int priority)
{
	pqueue_push(&sched_pqueue, (task){fun, priority, priority});
}

void sched_run(void)
{
	if(pqueue_empty(&sched_pqueue))
	{
		return;
	}
	while(1)
	{
		task curr = *pqueue_top(&sched_pqueue);
		pqueue_pop(&sched_pqueue);

		curr.fun();
		--curr.priority;

		if(curr.priority <= 0)
		{
			curr.priority = curr.initital_priority;
			vector_push_back(&sched_vector, curr);
		}
		else
		{
			pqueue_push(&sched_pqueue, curr);
		}

		if(pqueue_empty(&sched_pqueue))
		{
			sgc_for_each(i, sched_vector, vector)
			{
				pqueue_push(&sched_pqueue, *i);
			}
			// should write a function to clean the containers
			vector_init(&sched_vector);
		}
	}
}

void foo(void)
{
	printf("foo\n");
}

void bar(void)
{
	printf("bar\n");
}

void tar(void)
{
	printf("tar\n");
}

int main(void)
{
	sched_init();

	sched_add(foo, 10);
	sched_add(bar, 5);
	sched_add(tar, 1);

	sched_run();
	return 0;
}
```

[> Back to content](#content)
