Work In Progress

# Semi-Generic C
Algorithms and data structures written in **`C`** using macros. The data structures used are similar to the ones present in the **`C++ STL`**. 

# Simple Example 'vector.c'

```c
{r engine='bash', comment=''}
cat examples/vector.c
```

Output:
```bash
$ ./vector
size: 5
0 1 2 3 4
```

TODO content

TODO how does SGC_INIT work

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

    it = map_find(&m, 'a');
    if (map_it_valid(it)) {
        printf("value for 'a': %.2f\n", map_it_data(it)->value);
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
value for 'a': 10.00
a -> 10.00
b -> 11.10
```

# Supported functionalities

Every data structure defines the following functions:
- init
- copy
- free
- size
- empty
- set_shareing
- set_owning

Dictionary data structures also have:
- set_shareing_key
- set_owning_key

Fixed size (fs) data structurs also have:
- max

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
| it_erase     |        |       |      |                 |       |       |                   | **x**   | **x**                | **x**   | **x**                |
|              |        |       |      |                 |       |       |                   |     |                  |     |                  |
| array        | **x**      | **x**     |      |                 |       |       |                   |     |                  |     |                  |
| from_array   | **x**      |       |      |                 |       |       | **x**                 |     |                  |     |                  |

The functions are mostly identical to methods within the c++ STL with a few exceptions. The **`at`** functions correspond to **`operator[]`**.
- insert [1] For **`vector`** and **`deque`** used to insert element at specified position.
- erase [2] For **`vector`** **and `deque`** used to erase element at specified position.
- at [3] For **`vector`** **and `deque`** used to fetch element at specified position.
- set [4] For **`vector`** **and `deque`** used to set element at specified position.

Some data structures have iterators binded to them, there is three types of iterators, 
random access iterator (RA), bidirectional (BD) iterator and forward (FWD) iterator. The iterator
structure for the associated data structure had the same name as the data structure
with **`_it`** attacked to the end of it.

(TODO update it_erase)
Functions starting with **`it`** take the iterator as input parameter instead of the data structure

Forward iterator is associated with the following functions:
- begin
- cbegin
- end
- cend
- it_data
- it_go_next
- it_begin
- it_cbegin
- it_end
- it_cend
- it_eq
- it_valid

Bidirectional iterator is associated with all the function from forward iterator and also the following:
- it_go_prev

Random access iterator is associated with all the function from bidirectional iterator and also the following:
- from
- cfrom
- it_from
- it_cfrom
- it_jump
- it_diff

Now follows a table showing which data stuctures support which iterators:

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

The library supports the some algorithms most of which require an iterator to be able to work:

| Algorighm                                                                   | Group              | Minimal Requirements                    |
| --------------------------------------------------------------------------- | :----------------: | --------------------------------------- |
| eq<br>count                                                                 | EQ                 | forward iterator                        |
| compare                                                                     | COMPARE            | forward iterator, element compare       |
| qsort<br>qsort_default<br>                                                  | QSORT              | container array function                |
| foreach<br>accumulate                                                       | ITERATE            | forward iterator                        |
| find_el<br>find_it                                                          | FIND               | forward iterator                        |
| binary_find_el<br>binary_find_it                                            | BINARY_FIND        | random access iterator, element compare |

The sort algorithm does not require an iterator but an array function instead.
