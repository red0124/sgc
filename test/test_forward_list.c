#include "test_common.h"
#include <sgc/forward_list.h>

#define TEST_ELEMENTS_NUM 50

SGC_INIT_FORWARD_LIST(int, list)

void test_list_push_pop_front_back(void) {
}

void test_list_copy(void) {
}

void test_list_insert_set_at(void) {
}

void test_list_erase(void) {
}

void test_list_insert_sorted(void) {
}

void test_list_sort(void) {
}

SGC_INIT_FORWARD_LIST(al, alist)

void test_alist(void) {
}

SGC_INIT_FORWARD_LIST(list, llist)

void test_list_list(void) {
}

void test_list_iterator(void) {
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_list_push_pop_front_back);
    RUN_TEST(test_list_copy);
    RUN_TEST(test_list_insert_set_at);
    RUN_TEST(test_list_erase);
    RUN_TEST(test_list_insert_sorted);
    RUN_TEST(test_list_sort);
    RUN_TEST(test_alist);
    RUN_TEST(test_list_list);
    RUN_TEST(test_list_iterator);

    return UNITY_END();
}
