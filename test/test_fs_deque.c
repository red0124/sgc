#include "test_common.h"
#include <sgc/fs_deque.h>

#define GENERATE_FS_DEQUE_TESTS(S)                                             \
    SGC_INIT_FS_DEQUE(int, S, deque##S)                                        \
                                                                               \
    void test_fs_deque_insert_erase_combinations##S(void) {                    \
        TEST_INSERT_ERASE_COMBINATIONS_ARRAY_MAX(deque##S,                     \
                                                 TEST_RANDOM_ACCESS_ITERATOR,  \
                                                 S);                           \
    }                                                                          \
                                                                               \
    SGC_INIT_FS_DEQUE(oint, S, odeque##S)                                      \
                                                                               \
    void test_fs_deque_insert_erase_combinations_observed##S(void) {           \
        TEST_INSERT_ERASE_COMBINATIONS_ARRAY_MAX(odeque##S,                    \
                                                 TEST_RANDOM_ACCESS_ITERATOR,  \
                                                 S);                           \
        ASSERT_ALLOCATION_COUNT                                                \
    }

GENERATE_FS_DEQUE_TESTS(1)
GENERATE_FS_DEQUE_TESTS(2)
GENERATE_FS_DEQUE_TESTS(3)
GENERATE_FS_DEQUE_TESTS(4)
GENERATE_FS_DEQUE_TESTS(5)
GENERATE_FS_DEQUE_TESTS(6)
GENERATE_FS_DEQUE_TESTS(256)

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_fs_deque_insert_erase_combinations1);
    RUN_TEST(test_fs_deque_insert_erase_combinations_observed1);

    RUN_TEST(test_fs_deque_insert_erase_combinations2);
    RUN_TEST(test_fs_deque_insert_erase_combinations_observed2);

    RUN_TEST(test_fs_deque_insert_erase_combinations3);
    RUN_TEST(test_fs_deque_insert_erase_combinations_observed3);

    RUN_TEST(test_fs_deque_insert_erase_combinations4);
    RUN_TEST(test_fs_deque_insert_erase_combinations_observed4);

    RUN_TEST(test_fs_deque_insert_erase_combinations5);
    RUN_TEST(test_fs_deque_insert_erase_combinations_observed5);

    RUN_TEST(test_fs_deque_insert_erase_combinations6);
    RUN_TEST(test_fs_deque_insert_erase_combinations_observed6);

    RUN_TEST(test_fs_deque_insert_erase_combinations256);
    RUN_TEST(test_fs_deque_insert_erase_combinations_observed256);

    enable_moveing();
    RUN_TEST(test_fs_deque_insert_erase_combinations256);
    RUN_TEST(test_fs_deque_insert_erase_combinations_observed256);

    disable_moveing();
    enable_sharing();
    RUN_TEST(test_fs_deque_insert_erase_combinations256);
    RUN_TEST(test_fs_deque_insert_erase_combinations_observed256);
    return UNITY_END();
}
