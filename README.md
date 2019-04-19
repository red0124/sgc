
# Semi-Generic C
Algorithms and data structures written in **C** using macros. The data structures used are similar to the ones used in the **C++ STL** with little difference.

# Content
 - [Purpose](#purpose)
 - [Install](#install)
 - [Usage](#how-to-use-it)
 - [Benchmarks](#benchmarks)
 - [Examples](#examples)

# Purpose
  - Can be used used anywhere without any dependencies, just the standard library.
  - It is as simple as possible to use.
  - Can be used on any type of data.
  - Fast since it does not use **void*** as elements.
  - Memory can be shared.
  - Separate compiling is possible.
  - It has static containers which do not need memory allocation making them usable for **microcontrollers**.

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
#include <string.h>

#include <SGC/string.h>
#include <SGC/forward_list.h>
#include <SGC/algorithm.h>

SGC_INIT(STRING, string);
SGC_INIT(FORWARD_LIST, string, list);

int main(int)
{
	list l;
	list_init(&l);

	string s = (string)malloc(sizeof(char) * 10);
	strcpy(s, "hello");

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
To use primitive types we have to include :

```c
#include <SGC/static_types.h>
```

Where some types have their functions defined by default, and more can be added using the **SGC_INIT_STATIC_TYPE** macro, or when creating a primitive structure (structure of primitive types and primitive structures)  **SGC_INIT_STATIC_STRUCT** :

```c
#include <stdlib.h>
#include <string.h>

#include <SGC/static_types.h>
#include <SGC/algorithm.h>
#include <SGC/stack.h>

struct point
{
	double x;
	double y;
};

typedef struct point pt;

SGC_INIT_STATIC_STRUCT(pt, pt);
SGC_INIT(STACK, int, stack);

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

[> Back to content](#content)

# Benchmarks
Compared to **C++ STL** libraries.

![alt text]("https://gitlab.com/ado0/sgc/blob/master/img/vector_push_back.png")


[> Back to content](#content)
# Examples
\>\> Count the number of each word in a file then print every non unique element:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SGC/algorithm.h>
#include <SGC/static_types.h>
#include <SGC/string.h>
#include <SGC/unordered_map.h>

#define BUFF_SIZE 256
#define FILE_NAME "words.txt"

SGC_INIT(STRING, BUFF_SIZE, string);
SGC_INIT_PAIR(UNORDERED_MAP, string, int, map, ITERATE_PAIR);

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
	        if(*i.value > 1)
	        {
		        printf("%s -> %d", *i.key, *i.value);
		}
	}
        map_free(&m);
        return 0;
}
```

[> Back to content](#content)

