#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SGC_ST
#include "../lib/algorithm.h"
#include "../lib/static_types.h"
#include "../lib/unordered_map.h"

SGC_INIT_PAIR(UNORDERED_MAP, int, int, map);

#define INPUT_FILE "input.txt"
#define BUFF_SIZE 64

static void meassure(size_t num_of_elements)
{
	map m;
	map_init(&m);
	map_set_share(&m, 1);

	for(size_t i = 0; i < num_of_elements; ++i)
	{
		map_set_at(&m, i, i);
	}

	for(size_t i = 0; i < num_of_elements; ++i)
	{
		for(size_t j = 0; j < 9; ++j)
		{
			++*map_at(&m, i);
		}
	}

	map_free(&m);
}

int main(int argc, char* argv[])
{
	FILE* in = fopen(INPUT_FILE, "r");
	char buff[BUFF_SIZE];
	fgets(buff, BUFF_SIZE-1, in);
	fclose(in);

	size_t num_of_elements = atoi(buff);
	meassure(num_of_elements);

        return 0;
}
