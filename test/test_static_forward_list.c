#include "test_common.h"
#include <sgc/static_forward_list.h>

#define TEST_ELEMENTS_NUM 50
#define LIST_MAX 512

SGC_INIT_STATIC_FORWARD_LIST(int, LIST_MAX, list)

void test_list_push_pop_front_back(void) {
    TEST_PUSH_BACK_POP_BACK_AT_FRONT_BACK_EMPTY(list);
}

void test_list_copy(void) {
    TEST_PUSH_BACK_COPY_EQUAL(list);
}

void test_list_insert_set_at(void) {
    TEST_AT_INSERT(list);
}

void test_list_set_at(void) {
    TEST_PUSH_BACK_AT_SET_SET_AT_SET_FRONT_SET_BACK(list);
}

void test_list_erase(void) {
    TEST_PUSH_BACK_AT_ERASE_AT(list);
}

void test_list_insert_sorted(void) {
    TEST_INSERT_SORTED(list);
}

void test_list_sort(void) {
    TEST_LIST_SORT(list);
}

SGC_INIT_STATIC_FORWARD_LIST(al, LIST_MAX, alist)

void test_alist(void) {
    TEST_PUSH_BACK_ERASE_AT_ALLOCATIONS(alist);
}

SGC_INIT_STATIC_FORWARD_LIST(list, LIST_MAX, llist)

void test_list_list(void) {
    TEST_ARRAY_OF_ARRAYS_PUSH_BACK_AT_SHARE(llist, list);
}

void test_list_iterator(void) {
    TEST_PUSH_BACK_ITERATOR(list);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_list_push_pop_front_back);
    RUN_TEST(test_list_copy);
    RUN_TEST(test_list_insert_set_at);
    RUN_TEST(test_list_set_at);
    RUN_TEST(test_list_erase);
    RUN_TEST(test_list_insert_sorted);
    RUN_TEST(test_list_sort);
    RUN_TEST(test_alist);
    RUN_TEST(test_list_list);
    RUN_TEST(test_list_iterator);

    return UNITY_END();
}
