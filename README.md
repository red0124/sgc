Work In Progress

# Semi-Generic C
Algorithms and data structures written in **`C`** using macros. The data structures used are similar to the ones present in the **`C++ STL`**. 

# Simple Example 'vector.c'
```c
#include <sgc/vector.h>
#include <stdio.h>

SGC_INIT(VECTOR, int, vec)

int main(void) {
    vec v;
    vec_init(&v);

    for (size_t i = 0; i < 5; ++i) {
        vec_push_back(&v, i);
    }

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
size: 5
0 1 2 3 4
```
TODO content

To initialize the vector we simply used the **`SGC_INIT`** macro. The first parameter 
of the macro is the data structure, **`VECTOR`** in our case, the second, **`int`**, is the element 
type of the vector and the third, **`vec`** is how our vector will be named. All the funcions
generated will start with **`vec`**. The macro accepts a few additional arguments which may
be used to initialize algorithms(TODO link) for our data structure.

*Note: there macro will generate some functions with the \_p\_ prefix. Those funcions are
ment as private and should not be called.*

# Map Example 'map.c'
```c
#include <sgc/map.h>
#include <stdio.h>

SGC_INIT_DICT(MAP, char, double, map)

int main(void) {
    map m;
    map_init(&m);

    map_set(&m, 'a', 10.0);
    *map_at(&m, 'b') = 11.1;

    map_it it = map_find(&m, 'c');
    if (map_it_valid(it)) {
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
To initialize key-value type containers the **`SGC_INIT_DICT`** macro should be used. Similar to 
**`SGC_INIT`** the first parameter is the name of the data structure, the second is the type of the key,
the thrid is the type of the value, the fourth is the name of the generated data structure and all
additional arguments are algorithm initializers.

# Fixed Size Data Structures 'fixed_size.c'

The library supports a few fixed size containers. Most have identical implementations to their dynamic
counterparts, only fixed size unordered map and set are different since they are implemented using 
closed hashing.

All fixed size containers are named with the **`fs_`** prefix. To use a fixed size vector identical to the one above the
**`SGC_INIT_FS`** macro can be called:
```c
#include <sgc/fs_vector.h>
SGC_INIT_FS(FS_VECTOR, int, 100, vec)
```
This will initialize a fixed size vector of ints named vec with the capacity of 100.

Similar to the fixed size vector, a fixed size unordered map can be initialized usin the
**`SGC_INIT_FS_DICT`** macro:
```c
#include <sgc/fs_unordered_map.h>
SGC_INIT_FS_DICT(FS_UNORDERED_MAP, char, double, 100, umap)
```
Fixed size containers ignore insertions if they are already full.
This behavior can be modified, see *allocators.c* within the examples directory.

# Supported functionalities

Every data structure defines the following functions:
**`init`** **`copy`** **`free`** **`size`** **`empty`** **`set_sharing`** and **`set_owning`**

Dictionary data structures also have:
**`set_sharing_key`** and **`set_owning_key`**

Fixed size data structurs also have:
**`max`**

Now follows a table showing which data stuctures have which additional functionalities defined:

|              | vector | deque | list | forward<br>list | queue | stack | priority<br>queue | map | unordered<br>map | set | unordered<br>set |
| ------------ | :----: | :---: | :--: | :-------------: | :---: | :---: | :---------------: | :-: | :--------------: | :-: | :--------------: |
| push_back    | **x**      | **x**     | **x**    | **x**               |       |       |                   |     |                  |     |                  |
| push_forward |        | **x**     | **x**    | **x**               |       |       |                   |     |                  |     |                  |
| insert [1]   | **x**      | **x**     |      |                 |       |       |                   |     |                  | **x**   | **x**                |
|              |        |       |      |                 |       |       |                   |     |                  |     |                  |
| pop_back     | **x**      | **x**     | **x**    |                 |       |       |                   |     |                  |     |                  |
| pop_front    |        | **x**     | **x**    | **x**               |       |       |                   |     |                  |     |                  |
| erase [2]    | **x**      | **x**     |      |                 |       |       |                   | **x**   | **x**                | **x**   | **x**                |
|              |        |       |      |                 |       |       |                   |     |                  |     |                  |
| back         | **x**      | **x**     | **x**    | **x**               | **x**     |       |                   |     |                  |     |                  |
| front        | **x**      | **x**     | **x**    | **x**               | **x**     |       |                   |     |                  |     |                  |
| at [3]       | **x**      | **x**     |      |                 |       |       |                   | **x**   | **x**                |     |                  |
|              |        |       |      |                 |       |       |                   |     |                  |     |                  |
| set_back     | **x**      | **x**     | **x**    | **x**               | **x**     |       |                   |     |                  |     |                  |
| set_front    | **x**      | **x**     | **x**    | **x**               | **x**     |       |                   |     |                  |     |                  |
| set [4]      | **x**      | **x**     |      |                 |       |       |                   | **x**   | **x**                |     |                  |
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

The functions are mostly identical to methods within the c++ STL with a few exceptions. The **`at`** functions correspond to **`operator[]`**.
- insert [1] For **`vector`** and **`deque`** used to insert element at specified position.
- erase [2] For **`vector`** **and `deque`** used to erase element at specified position.
- at [3] For **`vector`** **and `deque`** used to fetch element at specified position.
- set [4] For **`vector`** **and `deque`** used to set element at specified position.

# Iterators

Some data structures have iterators binded to them, there is three types of iterators, 
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

This table shows which data stucture has access to which iterator:

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

The sort algorithm does not require an iterator but an array function instead.
