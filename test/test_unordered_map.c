#include "test_common.h"
#include <sgc/unordered_map.h>

SGC_INIT_UNORDERED_MAP(int, int, map)

void test_unordered_map_insert_erase_combinations(void) {
    TEST_INSERT_ERASE_COMBINATIONS_MAP(map);
}

SGC_INIT_UNORDERED_MAP(oint, oint, omap)

void test_unordered_map_insert_erase_combinations_observed(void) {
    TEST_INSERT_ERASE_COMBINATIONS_MAP(omap);
    ASSERT_ALLOCATION_COUNT
}

SGC_INIT_UNORDERED_MAP(oint, int, oint_int_map)

void test_unordered_map_insert_erase_combinations_observed_key(void) {
    TEST_INSERT_ERASE_COMBINATIONS_MAP(oint_int_map);
    ASSERT_ALLOCATION_COUNT
}

SGC_INIT_UNORDERED_MAP(int, oint, int_oint_map)

void test_unordered_map_insert_erase_combinations_observed_value(void) {
    TEST_INSERT_ERASE_COMBINATIONS_MAP(int_oint_map);
    ASSERT_ALLOCATION_COUNT
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_unordered_map_insert_erase_combinations);
    RUN_TEST(test_unordered_map_insert_erase_combinations_observed);
    RUN_TEST(test_unordered_map_insert_erase_combinations_observed_key);
    RUN_TEST(test_unordered_map_insert_erase_combinations_observed_value);

    disable_allocation();
    RUN_TEST(test_unordered_map_insert_erase_combinations);
    RUN_TEST(test_unordered_map_insert_erase_combinations_observed);
    RUN_TEST(test_unordered_map_insert_erase_combinations_observed_key);
    RUN_TEST(test_unordered_map_insert_erase_combinations_observed_value);

    enable_allocation();
    enable_moveing();
    RUN_TEST(test_unordered_map_insert_erase_combinations);
    RUN_TEST(test_unordered_map_insert_erase_combinations_observed);
    RUN_TEST(test_unordered_map_insert_erase_combinations_observed_key);
    RUN_TEST(test_unordered_map_insert_erase_combinations_observed_value);

    disable_moveing();
    enable_sharing();
    RUN_TEST(test_unordered_map_insert_erase_combinations);
    RUN_TEST(test_unordered_map_insert_erase_combinations_observed);
    RUN_TEST(test_unordered_map_insert_erase_combinations_observed_key);
    RUN_TEST(test_unordered_map_insert_erase_combinations_observed_value);
    return UNITY_END();
}
