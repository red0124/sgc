#include "test_common.h"
#include <sgc/static_vector.h>

#define VECTOR_MAX 512

SGC_INIT_STATIC_VECTOR(int, VECTOR_MAX, vector)

void vector_pop_front(vector* v) {
    vector_erase_at(v, 0);
}

void test_static_vector_push_pop_front_back(void) {
    // TEST_PUSH_BACK_POP_BACK_AT_FRONT_BACK_EMPTY(vector);
    TEST_TA(vector);
}

void test_static_vector_copy(void) {
    TEST_PUSH_BACK_COPY_EQUAL(vector);
}

void test_static_vector_insert(void) {
    TEST_AT_INSERT(vector);
}

void test_static_vector_erase_at(void) {
    TEST_PUSH_BACK_AT_ERASE_AT(vector);
}

void test_static_vector_insert_set(void) {
    TEST_PUSH_BACK_AT_SET_SET_AT_SET_FRONT_SET_BACK(vector);
}

SGC_INIT_STATIC_VECTOR(al, VECTOR_MAX, avector)

void test_astatic_vector(void) {
    TEST_PUSH_BACK_ERASE_AT_ALLOCATIONS(avector);
}

SGC_INIT_STATIC_VECTOR(vector, VECTOR_MAX, vvector)

void test_static_vector_static_vector(void) {
    TEST_ARRAY_OF_ARRAYS_PUSH_BACK_AT_SHARE(vvector, vector);
}

void test_static_vector_iterator(void) {
    TEST_PUSH_BACK_ITERATOR(vector);
}

void test_static_vector_iterator_from(void) {
    TEST_PUSH_BACK_ITERATOR_FROM(vector);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_static_vector_push_pop_front_back);
    RUN_TEST(test_static_vector_copy);
    RUN_TEST(test_static_vector_insert);
    RUN_TEST(test_static_vector_insert_set);
    RUN_TEST(test_static_vector_erase_at);
    RUN_TEST(test_astatic_vector);
    RUN_TEST(test_static_vector_static_vector);
    RUN_TEST(test_static_vector_iterator);
    RUN_TEST(test_static_vector_iterator_from);

    return UNITY_END();
}
