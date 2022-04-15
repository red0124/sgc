#include <sgc/fs_unordered_map.h>
#include <sgc/fs_vector.h>
#include <sgc/string.h>
#include <stdio.h>

SGC_INIT_FS(FS_VECTOR, int, 100, vec)

SGC_INIT_STRING(str)
SGC_INIT_FS_DICT(FS_UNORDERED_MAP, str, double, 5, umap)

void fs_vec_example(void) {
    vec v;
    vec_init(&v);

    for (size_t i = 0; i < vec_max(); ++i) {
        vec_push_back(&v, i);
    }

    printf("vec size: %zu\n", vec_size(&v));

    // will not be inserted since the vector is full
    vec_push_back(&v, -1);
    printf("vec size after another insert: %zu\n", vec_size(&v));

    // free is not really needed here
    vec_free(&v);
}

void fs_unordered_map_example(void) {
    umap u;
    umap_init(&u);

    char buff[32];
    for (size_t i = 0; i < umap_max(); ++i) {
        sprintf(buff, "key%zu", i);
        umap_set(&u, buff, i);
    }

    // will not be inserted since the map is full
    umap_set(&u, "full", -1);

    // will update key0 from 0 to -2
    umap_set(&u, "key0", -2);

    for_each(i IN u AS umap) {
        printf("%s -> %.2f\n", i->key, i->value);
    }

    // free needs to be called to free the keys which are allocated strings
    umap_free(&u);
}

int main(void) {
    printf("fixed size vector example: \n");
    fs_vec_example();

    printf("\nfixed size unordered map example: \n");
    fs_unordered_map_example();
}
