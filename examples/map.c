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
