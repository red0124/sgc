#include "test_common.h"
#include <sgc/list.h>

#define TEST_ELEMENTS_NUM 50

SGC_INIT_LIST(int, list)

const int* list_at(list* l, size_t at) {
    list_it curr = list_begin(l);

    while (list_it_valid(curr)) {
        if (at == 0) {
            return list_it_data(curr);
        }
        list_it_go_next(&curr);
        --at;
    }

    if (at == 0) {
        return list_it_data(curr);
    }

    return NULL;
}

void list_set(list* l, size_t at, int el) {
    int* curr_el = (int*)list_at(l, at);
    if (curr_el != NULL) {
        *curr_el = el;
    }
}

void list_insert(list* l, int at, int el) {
    if (at > (int)list_size(l)) {
        return;
    }

    list new_list;
    list_init(&new_list);

    for (list_it curr = list_begin(l); list_it_valid(curr);
         list_it_go_next(&curr)) {
        if (at == 0) {
            list_push_back(&new_list, el);
        }
        list_push_back(&new_list, *list_it_data(curr));
        --at;
    }

    if (at == 0) {
        list_push_back(&new_list, el);
    }

    list_free(l);
    *l = new_list;
}

void list_erase(list* l, int at) {
    if (at >= (int)list_size(l)) {
        return;
    }

    list new_list;
    list_init(&new_list);

    for (list_it curr = list_begin(l); list_it_valid(curr);
         list_it_go_next(&curr)) {
        if (at != 0) {
            list_push_back(&new_list, *list_it_data(curr));
        }
        --at;
    }

    list_free(l);
    *l = new_list;
}

void test_list_xxx(void) {
    TEST_TA(list);
}

void test_list_push_pop_front_back(void) {
}

void test_list_copy(void) {
}

void test_list_insert_set_at(void) {
}

void test_list_erase(void) {
}

void test_list_sort(void) {
}

SGC_INIT_LIST(al, alist)

void test_alist(void) {
}

SGC_INIT_LIST(list, llist)

void test_list_list(void) {
}

void test_list_it(void) {
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_list_xxx);
    RUN_TEST(test_list_push_pop_front_back);
    RUN_TEST(test_list_copy);
    RUN_TEST(test_list_insert_set_at);
    RUN_TEST(test_list_erase);
    RUN_TEST(test_list_sort);
    RUN_TEST(test_alist);
    RUN_TEST(test_list_list);
    RUN_TEST(test_list_it);

    return UNITY_END();
}
