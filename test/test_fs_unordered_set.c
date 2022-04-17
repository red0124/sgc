#include "test_common.h"
#include <sgc/fs_unordered_set.h>

#define SET_MAX 128

SGC_INIT_FS_UNORDERED_SET(int, SET_MAX, set)

void test_fs_unordered_setinsert_erase_combinations(void) {
    TEST_TS(set);
}

SGC_INIT_FS_UNORDERED_SET(oint, SET_MAX, oset)

void test_fs_unordered_setinsert_erase_combinations_observed(void) {
    TEST_TS(oset);
    TEST_ASSERT_GREATER_THAN(0, oint_allocation_count);
    ASSERT_EQUAL(oint_allocation_count, oint_deallocation_count);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_fs_unordered_setinsert_erase_combinations);
    RUN_TEST(test_fs_unordered_setinsert_erase_combinations_observed);
    return UNITY_END();
}
