#include "test_common.h"
#include <sgc/set.h>

SGC_INIT_SET(int, set)

void test_set_insert_erase_combinations(void) {
    TEST_INSERT_ERASE_COMBINATIONS_SET(set);
}

SGC_INIT_SET(oint, oset)

void test_set_insert_erase_combinations_observed(void) {
    TEST_INSERT_ERASE_COMBINATIONS_SET(oset);
    TEST_ASSERT_GREATER_THAN(0, oint_allocation_count);
    ASSERT_EQUAL(oint_allocation_count, oint_deallocation_count);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_set_insert_erase_combinations);
    RUN_TEST(test_set_insert_erase_combinations_observed);
    return UNITY_END();
}
