#include <sgc/list.h>
#include <sgc/vector.h>
#include <stdio.h>

SGC_INIT(VECTOR, float, vec)

// list <=> list<vector<float>>
SGC_INIT(LIST, vec, list)

void print_list(const list* const l) {
    printf("===================\n");
    for_each(i IN * l AS list) {

        // reverse for loop
        for_each_reverse(j IN * i AS vec) {
            printf("%.2f ", *j);
        }
        printf("\n");
    }
}

int main() {
    list l;
    list_init(&l);

    vec v;
    vec_init(&v);

    for (size_t i = 0; i < 5; ++i) {
        vec_push_back(&v, i);
        // this will make a copy of vector v to list l
        list_push_back(&l, v);
        print_list(&l);
    }

    vec_pop_back(list_back(&l));
    vec_pop_back(list_back(&l));
    print_list(&l);

    // this will move vector v to list l
    SGC_MOVE(list, l, list_push_front(&l, v));
    print_list(&l);

    // list l owns vector v and will free it
    list_free(&l);
    return 0;
}
