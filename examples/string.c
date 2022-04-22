#include <sgc/map.h>
#include <sgc/string.h>
#include <sgc/vector.h>
#include <stdio.h>

// str <=> char* with init, copy, free and other mandatory sgc functions
SGC_INIT_STRING(str)

// vec <=> vector<string>
SGC_INIT(VECTOR, str, vec)

// map <=> map<string, int>
SGC_INIT_DICT(MAP, str, int, map)

void string_vec_example(void) {
    vec v;
    vec_init(&v);

    vec_push_back(&v, "just");
    vec_push_back(&v, "some");
    vec_push_back(&v, "strings");

    printf("vec:\n");
    for_each(i IN v AS vec) {
        printf("- %s\n", *i);
    }

    printf("\nreplace 'some' with 'random'\n");
    vec_set(&v, 1, "random");

    printf("vec:\n");
    for_each(i IN v AS vec) {
        printf("- %s\n", *i);
    }

    vec_free(&v);
}

void string_map_example(void) {
    map m;
    map_init(&m);

    map_set(&m, "key1", 1);
    map_set(&m, "key2", 2);

    printf("map:\n");
    for_each(i IN m AS map) {
        printf("- %s: %d\n", i->key, i->value);
    }

    printf("\nerase 'key1'\n");
    map_erase(&m, "key1");

    printf("map:\n");
    for_each(i IN m AS map) {
        printf("- %s: %d\n", i->key, i->value);
    }

    map_free(&m);
}

int main(void) {
    printf("vector of strings example: \n");
    string_vec_example();

    printf("\nmap string to int example: \n");
    string_map_example();
    return 0;
}
