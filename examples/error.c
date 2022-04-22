#include <stdio.h>

#define SGC_USE_CUSTOM_ALLOCATOR
#define SGC_USE_CUSTOM_NO_SPACE_LEFT_HANDLER
#include <sgc/fs_vector.h>
#include <sgc/vector.h>

static bool fail_realloc = false;

void* my_malloc(size_t size) {
    return malloc(size);
}

void* my_realloc(void* ptr, size_t size) {
    printf("realloc %zu bytes\n", size);
    printf("new capacity should be: %zu\n", size / sizeof(int));

    if (fail_realloc) {
        fprintf(stderr, "error: invalid realloc\n\n");
        return NULL;
    }

    printf("\n");
    return realloc(ptr, size);
}

void my_free(void* ptr) {
    free(ptr);
}

// all allocations will use my_malloc, my_realloc and my_free
SGC_SET_ALLOCATOR(my_malloc, my_realloc, my_free)

SGC_INIT(VECTOR, int, vec)

void allocation_errors_example(void) {
    vec v;
    vec_init(&v);

    vec_push_back(&v, 0);
    vec_push_back(&v, 1);
    vec_push_back(&v, 2);
    printf("vec size: %zu\n", vec_size(&v));

    fail_realloc = true;

    vec_push_back(&v, 3);

    // will be ignored
    vec_push_back(&v, 4);
    vec_push_back(&v, 5);

    // size should be 4 since that was the capacity after the last valid realloc
    printf("vec size: %zu\n", vec_size(&v));

    vec_free(&v);
}

void my_handler() {
    fprintf(stderr, "data structure full\n");
}

// my_handler will be triggered when inserting something to an already full
// data structure
SGC_SET_NO_SPACE_LEFT_HANDLER(my_handler)

SGC_INIT_FS(FS_VECTOR, int, 3, fs_vec)

void fs_full_example(void) {
    fs_vec v;
    fs_vec_init(&v);

    fs_vec_push_back(&v, 0);
    fs_vec_push_back(&v, 1);
    fs_vec_push_back(&v, 2);

    // will be ignored
    fs_vec_push_back(&v, 3);

    // size should be 3 since that is the capacity of the vector
    printf("vec size: %zu\n", fs_vec_size(&v));

    fs_vec_free(&v);
}

int main(void) {
    printf("-- allocation errors example:\n");
    allocation_errors_example();

    printf("\n-- fixed size data structure full example\n");
    fs_full_example();
    return 0;
}
