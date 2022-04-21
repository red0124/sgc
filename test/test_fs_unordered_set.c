#include "test_common.h"
#include <sgc/fs_unordered_set.h>

#define GENERATE_FS_UNORDERED_SET_TESTS(S)                                     \
    SGC_INIT_FS_UNORDERED_SET(int, S, unordered_set##S)                        \
                                                                               \
    void test_fs_unordered_set_insert_erase_combinations##S(void) {            \
        TEST_INSERT_ERASE_COMBINATIONS_SET_MAX(unordered_set##S, S);           \
    }                                                                          \
                                                                               \
    SGC_INIT_FS_UNORDERED_SET(oint, S, ounordered_set##S)                      \
                                                                               \
    void test_fs_unordered_set_insert_erase_combinations_observed##S(void) {   \
        TEST_INSERT_ERASE_COMBINATIONS_SET_MAX(ounordered_set##S, S);          \
        ASSERT_ALLOCATION_COUNT                                                \
    }

GENERATE_FS_UNORDERED_SET_TESTS(1)
GENERATE_FS_UNORDERED_SET_TESTS(2)
GENERATE_FS_UNORDERED_SET_TESTS(3)
GENERATE_FS_UNORDERED_SET_TESTS(4)
GENERATE_FS_UNORDERED_SET_TESTS(5)
GENERATE_FS_UNORDERED_SET_TESTS(6)
GENERATE_FS_UNORDERED_SET_TESTS(256)

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_fs_unordered_set_insert_erase_combinations1);
    RUN_TEST(test_fs_unordered_set_insert_erase_combinations_observed1);

    RUN_TEST(test_fs_unordered_set_insert_erase_combinations2);
    RUN_TEST(test_fs_unordered_set_insert_erase_combinations_observed2);

    RUN_TEST(test_fs_unordered_set_insert_erase_combinations3);
    RUN_TEST(test_fs_unordered_set_insert_erase_combinations_observed3);

    RUN_TEST(test_fs_unordered_set_insert_erase_combinations4);
    RUN_TEST(test_fs_unordered_set_insert_erase_combinations_observed4);

    RUN_TEST(test_fs_unordered_set_insert_erase_combinations5);
    RUN_TEST(test_fs_unordered_set_insert_erase_combinations_observed5);

    RUN_TEST(test_fs_unordered_set_insert_erase_combinations6);
    RUN_TEST(test_fs_unordered_set_insert_erase_combinations_observed6);

    RUN_TEST(test_fs_unordered_set_insert_erase_combinations256);
    RUN_TEST(test_fs_unordered_set_insert_erase_combinations_observed256);

    enable_allocation();
    enable_moveing();
    RUN_TEST(test_fs_unordered_set_insert_erase_combinations256);
    RUN_TEST(test_fs_unordered_set_insert_erase_combinations_observed256);

    disable_moveing();
    enable_sharing();
    RUN_TEST(test_fs_unordered_set_insert_erase_combinations256);
    RUN_TEST(test_fs_unordered_set_insert_erase_combinations_observed256);
    return UNITY_END();
}
