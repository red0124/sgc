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
