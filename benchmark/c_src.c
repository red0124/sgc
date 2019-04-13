#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"
#define BUFF_SIZE 64

#define REPEAT(N) for(size_t _i = 0; _i < N; ++_i)

#define SGC_ST
#include "../lib/algorithm.h"
#include "../lib/static_types.h"
#include "../lib/vector.h"
#include "../lib/map.h"
#include "../lib/list.h"
#include "../lib/unordered_map.h"

SGC_INIT(VECTOR, int, vector);
SGC_INIT_PAIR(UNORDERED_MAP, int, int, umap);

/*
   ===========================
      function to meassure
   ===========================
*/

#define MEASSURE test_umap_fetch

/*
   ===========================
   ===========================
*/

void test_umap_fetch(size_t num_el, size_t num_rep)
{
	umap m;
	umap_init(&m);

	for(size_t i = 0; i < num_el; ++i)
	{
		umap_set_at(&m, i, i);
	}

	REPEAT(num_rep)
	for(size_t i = 0; i < num_el; ++i)
	{
		++*umap_at(&m, i);
	}

	umap_free(&m);
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

int main(int argc, char* argv[])
{
	FILE* in = fopen(INPUT_FILE, "r");
	char buff[BUFF_SIZE];

	fgets(buff, BUFF_SIZE-1, in);
	size_t num_of_elements = atoi(buff);

	fgets(buff, BUFF_SIZE-1, in);
	size_t num_of_repetitions = atoi(buff);

	fclose(in);

	MEASSURE(num_of_elements, num_of_repetitions);

        return 0;
}
