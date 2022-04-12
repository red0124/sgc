Hello



--------------------------------------------------





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

|              | vector | deque | list | fw<br>list | queue | stack | priority<br>queue | set | uo<br>set | map | uo<br>map |
| ------------ | :----: | :---: | :--: | :-------------: | :---: | :---: | :---------------: | :-: | :--------------: | :-: | :--------------: |
| push_back    | **x**      | **x**     | **x**    | **x**               |       |       |                   |     |                  |     |                  |
| push_forward |        | **x**     | **x**    | **x**               |       |       |                   |     |                  |     |                  |
| insert [1]   | **x**      | **x**     |      |                 |       |       |                   | **x**   | **x**                |     |                  |
|              |        |       |      |                 |       |       |                   |     |                  |     |                  |
| pop_back     | **x**      | **x**     | **x**    |                 |       |       |                   |     |                  |     |                  |
| pop_front    |        | **x**     | **x**    | **x**               |       |       |                   |     |                  |     |                  |
| erase [2]    | **x**      | **x**     |      |                 |       |       |                   | **x**   | **x**                | **x**   | **x**                |
|              |        |       |      |                 |       |       |                   |     |                  |     |                  |
| back         | **x**      | **x**     | **x**    | **x**               | **x**     |       |                   |     |                  |     |                  |
| front        | **x**      | **x**     | **x**    | **x**               | **x**     |       |                   |     |                  |     |                  |
| at [3]       | **x**      | **x**     |      |                 |       |       |                   |     |                  | **x**   | **x**                |
|              |        |       |      |                 |       |       |                   |     |                  |     |                  |
| set_back     | **x**      | **x**     | **x**    | **x**               | **x**     |       |                   |     |                  |     |                  |
| set_front    | **x**      | **x**     | **x**    | **x**               | **x**     |       |                   |     |                  |     |                  |
| set [4]      | **x**      | **x**     |      |                 |       |       |                   |     |                  | **x**   | **x**                |
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
