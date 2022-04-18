#include "test_common.h"
#include <sgc/map.h>

SGC_INIT_MAP(int, int, map)

void test_map_insert_erase_combinations(void) {
    TEST_INSERT_ERASE_COMBINATIONS_MAP(map);
}

SGC_INIT_MAP(oint, oint, omap)

void test_map_insert_erase_combinations_observed(void) {
    TEST_INSERT_ERASE_COMBINATIONS_MAP(omap);
    TEST_ASSERT_GREATER_THAN(0, oint_allocation_count);
    ASSERT_EQUAL(oint_allocation_count, oint_deallocation_count);
}

SGC_INIT_MAP(oint, int, oint_int_map)

void test_map_insert_erase_combinations_observed_key(void) {
    TEST_INSERT_ERASE_COMBINATIONS_MAP(oint_int_map);
    TEST_ASSERT_GREATER_THAN(0, oint_allocation_count);
    ASSERT_EQUAL(oint_allocation_count, oint_deallocation_count);
}

SGC_INIT_MAP(int, oint, int_oint_map)

void test_map_insert_erase_combinations_observed_value(void) {
    TEST_INSERT_ERASE_COMBINATIONS_MAP(int_oint_map);
    TEST_ASSERT_GREATER_THAN(0, oint_allocation_count);
    ASSERT_EQUAL(oint_allocation_count, oint_deallocation_count);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_map_insert_erase_combinations);
    RUN_TEST(test_map_insert_erase_combinations_observed);
    RUN_TEST(test_map_insert_erase_combinations_observed_key);
    RUN_TEST(test_map_insert_erase_combinations_observed_value);
    return UNITY_END();
}
