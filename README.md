Work In Progress

# Semi-Generic C
Algorithms and data structures written in **C** using macros. The data structures used are similar to the ones used in the **C++ STL** with little difference.

# Simple Example 'intro.c'

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

        for_each(i in v as vec)
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

Now follows a table showing which data stuctures have which functionalities defined:

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
insert [1] For **`vector`** and **`deque`** used to insert element at specified position.
erase [2] For **`vector`** **and `deque`** used to erase element at specified position.
at [3] For **`vector`** **and `deque`** used to fetch element at specified position.
set [4] For **`vector`** **and `deque`** used to set element at specified position.

Some data structures have iterators binded to them, there is three types of iterators, 
random access iterator, bidirectional iterator and forward iterator. The iterator
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
|               | random<br>access<br>iterator | bidirectional<br>iterator | forward<br>iterator |
| ------------- | :--------------------------: | :-----------------------: | :-----------------: |
| vector        | **x**                            |                           |                     |
| deque         | **x**                            |                           |                     |
| list          |                              | **x**                         |                     |
| forward_list  |                              |                           | **x**                   |
| map           |                              | **x**                         |                     |
| unordered_map |                              | **x**                         |                     |
| set           |                              | **x**                         |                     |
| unordered_set |                              | **x**                         |                     |
