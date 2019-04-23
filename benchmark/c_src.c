#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"
#define BUFF_SIZE 64

#define REPEAT(N) for(size_t _i = 0; _i < N; ++_i)

#define SGC_ST
#include "../lib/algorithm.h"
#include "../lib/list.h"
#include "../lib/map.h"
#include "../lib/priority_queue.h"
#include "../lib/static_types.h"
#include "../lib/static_unordered_map.h"
#include "../lib/unordered_map.h"
#include "../lib/vector.h"

#define STATIC_MAX 400000

SGC_INIT(PRIORITY_QUEUE, int, pqueue);
SGC_INIT(LIST, int, list);
SGC_INIT(VECTOR, int, vector);
SGC_INIT_PAIR(MAP, int, int, map);
SGC_INIT_PAIR(UNORDERED_MAP, int, int, umap);
SGC_INIT_STATIC_PAIR(UNORDERED_MAP, int, int, STATIC_MAX, sumap);

/*
   ===========================
      function to measure
   ===========================
*/

#define MEASURE test_vector_push_back

/*
   ===========================
   ===========================
*/

void test_pqueue_pop(size_t num_el, size_t num_rep)
{
        pqueue p;
        pqueue_init(&p);

        REPEAT(num_rep)
        {
                for(size_t i = 0; i < num_el; ++i)
                {
                        pqueue_push(&p, i);
                }

                while(!pqueue_empty(&p))
                {
                        pqueue_pop(&p);
                }
        }

        pqueue_free(&p);
}

void test_pqueue_push(size_t num_el, size_t num_rep)
{
        pqueue p;
        pqueue_init(&p);

        REPEAT(num_rep)
        for(size_t i = 0; i < num_el; ++i)
        {
                pqueue_push(&p, i);
        }

        pqueue_free(&p);
}

void test_list_iterate(size_t num_el, size_t num_rep)
{
        list l;
        list_init(&l);

        for(size_t i = 0; i < num_el; ++i)
        {
                list_push_back(&l, i);
        }

        REPEAT(num_rep)
        {
                sgc_for_each(i, l, list)
                {
                        ++*i;
                }
        }

        list_free(&l);
}

void test_list_push_back(size_t num_el, size_t num_rep)
{
        list l;
        list_init(&l);

        REPEAT(num_rep)
        for(size_t i = 0; i < num_el; ++i)
        {
                list_push_back(&l, i);
        }

        list_free(&l);
}

void test_map_iterate(size_t num_el, size_t num_rep)
{
        map m;
        map_init(&m);

        for(size_t i = 0; i < num_el; ++i)
        {
                map_set_at(&m, i * 9999, i);
        }

        REPEAT(num_rep)
        {
                sgc_for_each(i, m, map)
                {
                        ++i->value;
                }
        }

        map_free(&m);
}

void test_map_fetch(size_t num_el, size_t num_rep)
{
        map m;
        map_init(&m);

        for(size_t i = 0; i < num_el; ++i)
        {
                map_set_at(&m, i * 9999, i);
        }

        REPEAT(num_rep)
        for(size_t i = 0; i < num_el; ++i)
        {
                ++*map_at(&m, i * 9999);
        }

        map_free(&m);
}

void test_map_insert(size_t num_el, size_t num_rep)
{
        map m;
        map_init(&m);

        REPEAT(num_rep)
        for(size_t i = 0; i < num_el; ++i)
        {
                map_set_at(&m, i * 9999, i);
        }

        map_free(&m);
}

void test_sumap_iterate(size_t num_el, size_t num_rep)
{
        sumap m;
        sumap_init(&m);

        for(size_t i = 0; i < num_el; ++i)
        {
                sumap_set_at(&m, i * 9999, i);
        }

        REPEAT(num_rep)
        {
                sgc_for_each(i, m, sumap)
                {
                        ++i->value;
                }
        }

        sumap_free(&m);
}

void test_sumap_insert(size_t num_el, size_t num_rep)
{
        sumap m;
        sumap_init(&m);

        REPEAT(num_rep)
        for(size_t i = 0; i < num_el; ++i)
        {
                sumap_set_at(&m, i * 9999, i);
        }

        sumap_free(&m);
}

void test_sumap_fetch(size_t num_el, size_t num_rep)
{
        sumap m;
        sumap_init(&m);

        for(size_t i = 0; i < num_el; ++i)
        {
                sumap_set_at(&m, i * 9999, i);
        }

        REPEAT(num_rep)
        for(size_t i = 0; i < num_el; ++i)
        {
                ++*sumap_at(&m, i * 9999);
        }

        sumap_free(&m);
}

void test_umap_iterate(size_t num_el, size_t num_rep)
{
        umap m;
        umap_init(&m);

        for(size_t i = 0; i < num_el; ++i)
        {
                umap_set_at(&m, i * 9999, i);
        }

        REPEAT(num_rep)
        {
                sgc_for_each(i, m, umap)
                {
                        ++i->value;
                }
        }

        umap_free(&m);
}

void test_umap_fetch(size_t num_el, size_t num_rep)
{
        umap m;
        umap_init(&m);

        for(size_t i = 0; i < num_el; ++i)
        {
                umap_set_at(&m, i * 9999, i);
        }

        REPEAT(num_rep)
        for(size_t i = 0; i < num_el; ++i)
        {
                ++*umap_at(&m, i * 9999);
        }

        umap_free(&m);
}

void test_umap_insert(size_t num_el, size_t num_rep)
{
        umap m;
        umap_init(&m);

        REPEAT(num_rep)
        for(size_t i = 0; i < num_el; ++i)
        {
                umap_set_at(&m, i * 9999, i);
        }

        umap_free(&m);
}

void test_vector_fetch(size_t num_el, size_t num_rep)
{
        vector v;
        vector_init(&v);

        for(size_t i = 0; i < num_el; ++i)
        {
                vector_push_back(&v, i);
        }

        REPEAT(num_rep)
        for(size_t i = 0; i < num_el; ++i)
        {
                ++*vector_at(&v, i);
        }

        vector_free(&v);
}

void test_vector_push_back(size_t num_el, size_t num_rep)
{
        vector v;
        vector_init(&v);

        REPEAT(num_rep)
        for(size_t i = 0; i < num_el; ++i)
        {
                vector_push_back(&v, i);
        }

        vector_free(&v);
}

int main(int argc, char *argv[])
{
        FILE *in = fopen(INPUT_FILE, "r");
        char buff[BUFF_SIZE];

        fgets(buff, BUFF_SIZE - 1, in);
        size_t num_of_elements = atoi(buff);

        fgets(buff, BUFF_SIZE - 1, in);
        size_t num_of_repetitions = atoi(buff);

        fclose(in);

        MEASURE(num_of_elements, num_of_repetitions);

        return 0;
}
