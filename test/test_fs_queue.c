#include "test_common.h"
#include <sgc/fs_queue.h>

#define GENERATE_FS_QUEUE_TESTS(S)                                             \
    SGC_INIT_FS_QUEUE(int, S, queue##S)                                        \
                                                                               \
    void test_fs_queue_push_pop_combinations##S(void) {                        \
        TEST_PUSH_POP_COMBINATIONS_QUEUE_MAX(queue##S, S);                     \
    }                                                                          \
                                                                               \
    SGC_INIT_FS_QUEUE(oint, S, oqueue##S)                                      \
                                                                               \
    void test_fs_queue_push_pop_combinations_observed##S(void) {               \
        TEST_PUSH_POP_COMBINATIONS_QUEUE_MAX(oqueue##S, S);                    \
        ASSERT_ALLOCATION_COUNT                                                \
    }

GENERATE_FS_QUEUE_TESTS(1)
GENERATE_FS_QUEUE_TESTS(2)
GENERATE_FS_QUEUE_TESTS(3)
GENERATE_FS_QUEUE_TESTS(4)
GENERATE_FS_QUEUE_TESTS(5)
GENERATE_FS_QUEUE_TESTS(6)
GENERATE_FS_QUEUE_TESTS(256)

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_fs_queue_push_pop_combinations1);
    RUN_TEST(test_fs_queue_push_pop_combinations_observed1);

    RUN_TEST(test_fs_queue_push_pop_combinations2);
    RUN_TEST(test_fs_queue_push_pop_combinations_observed2);

    RUN_TEST(test_fs_queue_push_pop_combinations3);
    RUN_TEST(test_fs_queue_push_pop_combinations_observed3);

    RUN_TEST(test_fs_queue_push_pop_combinations4);
    RUN_TEST(test_fs_queue_push_pop_combinations_observed4);

    RUN_TEST(test_fs_queue_push_pop_combinations5);
    RUN_TEST(test_fs_queue_push_pop_combinations_observed5);

    RUN_TEST(test_fs_queue_push_pop_combinations6);
    RUN_TEST(test_fs_queue_push_pop_combinations_observed6);

    RUN_TEST(test_fs_queue_push_pop_combinations256);
    RUN_TEST(test_fs_queue_push_pop_combinations_observed256);

    enable_allocation();
    enable_moveing();
    RUN_TEST(test_fs_queue_push_pop_combinations256);
    RUN_TEST(test_fs_queue_push_pop_combinations_observed256);

    disable_moveing();
    enable_sharing();
    RUN_TEST(test_fs_queue_push_pop_combinations256);
    RUN_TEST(test_fs_queue_push_pop_combinations_observed256);
    return UNITY_END();
}
