#include "test_common.h"
#include <sgc/fs_stack.h>

#define STACK_MAX 512

SGC_INIT_FS_STACK(int, STACK_MAX, stack)

void test_stack_push_pop_combinations(void) {
    TEST_TSTK(stack);
}

SGC_INIT_FS_STACK(oint, STACK_MAX, ostack)

void test_stack_push_pop_combinations_observed(void) {
    TEST_TSTK(ostack);
    TEST_ASSERT_GREATER_THAN(0, oint_allocation_count);
    ASSERT_EQUAL(oint_allocation_count, oint_deallocation_count);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_stack_push_pop_combinations);
    RUN_TEST(test_stack_push_pop_combinations_observed);
    return UNITY_END();
}
