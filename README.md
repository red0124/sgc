﻿
```
   ____  ___________
  / ___// ____/ ____/
  \__ \/ / __/ /     
 ___/ / /_/ / /___   
/____/\____/\____/   
```

A header only library for algorithms and data structures written in **`C`** using macros.
The data structures used are similar to the ones present in the **`C++ STL`**.

# Simple Example
```c
#include <sgc/vector.h>
#include <stdio.h>

// vec <=> vector<int>
SGC_INIT(VECTOR, int, vec)

int main(void) {
    vec v;
    vec_init(&v);

    vec_push_back(&v, 1);
    vec_push_back(&v, 5);

    *vec_at(&v, 0) = 2;

    for_each(i IN v AS vec) {
        printf("%d ", *i);
    }

    vec_free(&v);
    return 0;
}
```
Output:
```bash
$ ./vector
size: 2
2 5
```

# Features

 * Easy to use
 * No dependencies
 * Able to work with any type
 * Data structures and algorithms can be separated into headers and source files
 * Gives access to fixed size data structures which invoke no allocations convenient for embedded environments
 * Gives access to memory sharing and 'move semantics'
 * Allows for the usage of custom allocators and error handlers

# Content
 * [Usage](#Usage)
 * [Fixed size data structures](#Fixed-Size-Data-Structures)
 * [Data Structures](#Data-Structures)
 * [Iterators](#Iterators)
 * [Algorithms](#Algorithms)
 * [Benchmarks](#Benchmarks)
 * [Installation](#Installation)

# Usage

To initialize the vector we simply used the **`SGC_INIT`** macro. It will generate
the **`vec`** structure and corresponding functions which all start with **vec_**.

*Note: the macro will also generate some functions with the \_p\_ prefix.
Those functions are meant to be private and should only be invoked internally.*

In order to generate a vector of a type some functions may need to exist
so the library can know how to work with the type. For **`int`** those functions
are **`int_copy`** and **`int_free`** and they are generated by the library along with function for many other primitive types.

*More examples on how to use the library can be found in the examples directory.*

## Map Example
```c
#include <sgc/map.h>
#include <stdio.h>

// map <=> map<int, double>
SGC_INIT_DICT(MAP, char, double, map)

int main(void) {
    map m;
    map_init(&m);

    map_set(&m, 'a', 10.0);
    *map_at(&m, 'b') = 11.1;

    map_it it = map_find(&m, 'c');
    if (map_it_valid(&it)) {
        return 1;
    }

    for_each(i IN m AS map) {
        printf("%c -> %.2f\n", i->key, i->value);
    }

    map_free(&m);
    return 0;
}
```
Output:
```bash
$ ./map
a -> 10.00
b -> 11.10
```
To initialize dictionary type data structures the **`SGC_INIT_DICT`** macro should be used.
It is identical to **`SGC_INIT`** but takes one more type parameter for the key.

# Fixed Size Data Structures

The library supports a few fixed size (fs) data structures. Most have identical implementations to their dynamic
counterparts.

All fixed size containers are named with the **`fs_`** prefix. To use a fixed size vector identical to the one above the
**`SGC_INIT_FS`** macro can be used:
```c
#include <sgc/fs_vector.h>

// vec <=> vector<int> with capacity 100
SGC_INIT_FS(FS_VECTOR, int, 100, vec)
```
Similar to the fixed size vector, a fixed size unordered map can be initialized using the
**`SGC_INIT_FS_DICT`** macro:
```c
#include <sgc/fs_unordered_map.h>

// umap <=> unordered_map<char, double> with capacity 100
SGC_INIT_FS_DICT(FS_UNORDERED_MAP, char, double, 100, umap)
```
Fixed size containers ignore insertions if they are already full.
This behavior can be modified, see **error.c** within the examples directory.

# Data Structures

Every data structure defines the following functions:
**`init`** **`copy`** **`free`** **`size`** **`empty`** **`set_sharing`** and **`set_owning`**

Dictionary data structures also have:
**`set_sharing_key`** and **`set_owning_key`**

Fixed size data structures also have:
**`max`**

Now follows a table showing which data structures have which functionalities defined:

|              | vector | deque | list | forward<br>list | queue | stack | priority<br>queue | map | unordered<br>map | set | unordered<br>set |
| ------------ | :----: | :---: | :--: | :-------------: | :---: | :---: | :---------------: | :-: | :--------------: | :-: | :--------------: |
| push_back    | **x**      | **x**     | **x**    | **x**               |       |       |                   |     |                  |     |                  |
| push_forward |        | **x**     | **x**    | **x**               |       |       |                   |     |                  |     |                  |
| insert       | **x**      | **x**     |      |                 |       |       |                   |     |                  | **x**   | **x**                |
|              |        |       |      |                 |       |       |                   |     |                  |     |                  |
| pop_back     | **x**      | **x**     | **x**    |                 |       |       |                   |     |                  |     |                  |
| pop_front    |        | **x**     | **x**    | **x**               |       |       |                   |     |                  |     |                  |
| erase        | **x**      | **x**     |      |                 |       |       |                   | **x**   | **x**                | **x**   | **x**                |
|              |        |       |      |                 |       |       |                   |     |                  |     |                  |
| back         | **x**      | **x**     | **x**    | **x**               | **x**     |       |                   |     |                  |     |                  |
| front        | **x**      | **x**     | **x**    | **x**               | **x**     |       |                   |     |                  |     |                  |
| at           | **x**      | **x**     |      |                 |       |       |                   | **x**   | **x**                |     |                  |
|              |        |       |      |                 |       |       |                   |     |                  |     |                  |
| set_back     | **x**      | **x**     | **x**    | **x**               | **x**     |       |                   |     |                  |     |                  |
| set_front    | **x**      | **x**     | **x**    | **x**               | **x**     |       |                   |     |                  |     |                  |
| set          | **x**      | **x**     |      |                 |       |       |                   | **x**   | **x**                |     |                  |
|              |        |       |      |                 |       |       |                   |     |                  |     |                  |
| push         |        |       |      |                 | **x**     | **x**     | **x**                 |     |                  |     |                  |
| pop          |        |       |      |                 | **x**     | **x**     | **x**                 |     |                  |     |                  |
| top          |        |       |      |                 |       | **x**     | **x**                 |     |                  |     |                  |
|              |        |       |      |                 |       |       |                   |     |                  |     |                  |
| find         |        |       |      |                 |       |       |                   | **x**   | **x**                | **x**   | **x**                |
| erase_it     |        |       |      |                 |       |       |                   | **x**   | **x**                | **x**   | **x**                |
|              |        |       |      |                 |       |       |                   |     |                  |     |                  |
| array        | **x**      | **x**     |      |                 |       |       |                   |     |                  |     |                  |
| from_array   | **x**      |       |      |                 |       |       | **x**                 |     |                  |     |                  |

The functions are mostly identical to methods within the c++ STL with a few exceptions.
The **`at`** functions correspond to **`operator[]`**.
**`insert`**, **`erase`**, **`at`** and **`set`** for **`vector`** and **`deque`** are used to insert
element at specified position as opposed to **`map`** and **`unordered_map`** functions
which work with keys.

# Iterators

Some data structures have iterators bound to them, there is three types of iterators, 
**random access iterator**, **bidirectional iterator** and **forward iterator**. The iterator
structure for the associated data structure had the same name as the data structure
with **_it** attacked to the end of it, eg for **vec** it would be **vec_it**.

Functions starting with **`it`** take the iterator as input parameter instead of the data structure
- **Forward iterator** is associated with the following functions:
**`begin`** **`cbegin`** **`end`** **`cend`** **`it_data`** **`it_go_next`** **`it_eq`** and **`it_valid`**
- **Bidirectional iterator** is associated with all the function from forward iterator and also the following:
**`it_go_prev`**
- **Random access iterator** is associated with all the function from bidirectional iterator and also the following:
**`from`** **`cfrom`** **`it_move`** and **`it_diff`**

This table shows which data structure has access to which iterator:

|               | random access iterator | bidirectional iterator | forward iterator |
| ------------- | :--------------------: | :--------------------: | :--------------: |
| vector        | **x**                      |                        |                  |
| deque         | **x**                      |                        |                  |
| list          |                        | **x**                      |                  |
| forward_list  |                        |                        | **x**                |
| map           |                        | **x**                      |                  |
| unordered_map |                        | **x**                      |                  |
| set           |                        | **x**                      |                  |
| unordered_set |                        | **x**                      |                  |

# Algorithms

The library gives access some algorithms most of which require an iterator to be able to work.
If we for example wanted to initialize the vector to have access to **`qsort`** and **`eq`** functions they could be initialized like this:
```c
#include <sgc/vector.h>
#include <sgc/algorithm.h>
SGC_INIT(VECTOR, int, vec, QSORT, EQ)
```
The **`SGC_INIT`** function may take additional argument which represent algorithms we want to use.
This will generate functions such as **`vec_qsort`** and **`vec_eq`** among others.
This table shows which algorithms are generated with which initializer group:


| Algorighm                                                                   | Group              | Minimal Requirements                    |
| --------------------------------------------------------------------------- | :----------------: | --------------------------------------- |
| eq<br>count                                                                 | EQ                 | forward iterator                        |
| compare                                                                     | COMPARE            | forward iterator, element compare       |
| qsort<br>qsort_default<br>                                                  | QSORT              | container array function                |
| foreach<br>accumulate                                                       | ITERATE            | forward iterator                        |
| find_el<br>find_it                                                          | FIND               | forward iterator                        |
| binary_find_el<br>binary_find_it                                            | BINARY_FIND        | random access iterator, element compare |

The qsort algorithm does not require an iterator but an array function instead.

# Benchmarks 

A few simple benchmarks are made to compare the performance of the library with 
the C++ stl implementations of **clang** and **gcc**.

The benchmarks were ran on (TODO insert OS and CPU)
![](https://github.com/red0124/sgc/blob/master/benchmark/img/gcc.png)
*gcc 11.2 TODO check*

![](https://github.com/red0124/sgc/blob/master/benchmark/img/clang.png)
*clang 14.1 TODO check*

The code for the benchmarks can be found in the benchmarks directory.

# Installation 
```shell
$ git clone https://github.com/red0124/sgc
$ cd sgc
$ cmake -B build
$ cd build
$ sudo make install
```
The library also supports CMake and meson build systems
