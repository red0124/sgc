#include "test_common.h"
#include <sgc/unordered_set.h>

SGC_INIT_UNORDERED_SET(int, set)

void test_unordered_set_insert_erase_combinations(void) {
    TEST_INSERT_ERASE_COMBINATIONS_SET(set);
}

SGC_INIT_UNORDERED_SET(oint, oset)

void test_unordered_set_insert_erase_combinations_observed(void) {
    TEST_INSERT_ERASE_COMBINATIONS_SET(oset);
    ASSERT_ALLOCATION_COUNT
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_unordered_set_insert_erase_combinations);
    RUN_TEST(test_unordered_set_insert_erase_combinations_observed);

    disable_allocation();
    RUN_TEST(test_unordered_set_insert_erase_combinations);
    RUN_TEST(test_unordered_set_insert_erase_combinations_observed);

    enable_allocation();
    enable_moveing();
    RUN_TEST(test_unordered_set_insert_erase_combinations);
    RUN_TEST(test_unordered_set_insert_erase_combinations_observed);

    disable_moveing();
    enable_sharing();
    RUN_TEST(test_unordered_set_insert_erase_combinations);
    RUN_TEST(test_unordered_set_insert_erase_combinations_observed);
    return UNITY_END();
}
