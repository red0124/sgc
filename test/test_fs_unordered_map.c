#include "test_common.h"
#include <sgc/fs_unordered_map.h>

#define MAP_MAX 128

SGC_INIT_FS_UNORDERED_MAP(int, int, MAP_MAX, map)

void test_fs_unordered_map_insert_erase_combinations(void) {
    TEST_TM(map);
}

SGC_INIT_FS_UNORDERED_MAP(oint, oint, MAP_MAX, omap)

void test_fs_unordered_map_insert_erase_combinations_observed(void) {
    TEST_TM(omap);
    TEST_ASSERT_GREATER_THAN(0, oint_allocation_count);
    ASSERT_EQUAL(oint_allocation_count, oint_deallocation_count);
}

SGC_INIT_FS_UNORDERED_MAP(oint, int, MAP_MAX, oint_int_map)

void test_fs_unordered_map_insert_erase_combinations_observed_key(void) {
    TEST_TM(oint_int_map);
    TEST_ASSERT_GREATER_THAN(0, oint_allocation_count);
    ASSERT_EQUAL(oint_allocation_count, oint_deallocation_count);
}

SGC_INIT_FS_UNORDERED_MAP(int, oint, MAP_MAX, int_oint_map)

void test_fs_unordered_map_insert_erase_combinations_observed_value(void) {
    TEST_TM(int_oint_map);
    TEST_ASSERT_GREATER_THAN(0, oint_allocation_count);
    ASSERT_EQUAL(oint_allocation_count, oint_deallocation_count);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed_key);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed_value);
    return UNITY_END();
}
