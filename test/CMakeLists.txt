cmake_minimum_required(VERSION 3.14)

project(sgc_tests C)
enable_testing()

# ---- Dependencies ----

set(
    sgc_INCLUDE_WITHOUT_SYSTEM
    YES
    CACHE
    INTERNAL
    "Turn the warning guard off to have errors appear in test builds"
)

include(FetchContent)
FetchContent_Declare(sgc SOURCE_DIR "${PROJECT_SOURCE_DIR}/..")
FetchContent_MakeAvailable(sgc)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(sgc INTERFACE -Wall -Wextra)
endif()

# ---- Dependencies ----

include(FetchContent)
FetchContent_Declare(
  unity
  GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity
  GIT_TAG origin/master
  GIT_SHALLOW TRUE)

FetchContent_MakeAvailable(unity)
set(unity "${FETCHCONTENT_BASE_DIR}/unity-src")

# ---- Test ----

enable_testing()

foreach(name IN ITEMS test_algorithm test_deque test_forward_list test_list
        test_map test_priority_queue test_queue test_set test_stack
        test_fs_deque test_fs_priority_queue test_fs_queue
        test_fs_stack test_fs_unordered_map test_fs_unordered_set
        test_fs_vector test_string test_unordered_map test_unordered_set
        test_vector test_utils)
  add_executable("${name}" "${name}.c")
  target_link_libraries("${name}" PRIVATE sgc::sgc unity)
  target_compile_definitions("${name}" PRIVATE CMAKE_GITHUB_CI)
  add_test("${name}" "${name}" "./${name}")
endforeach()
