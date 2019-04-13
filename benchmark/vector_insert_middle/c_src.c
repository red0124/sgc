#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SGC_ST
#include "../lib/algorithm.h"
#include "../lib/static_types.h"
#include "../lib/vector.h"

SGC_INIT(VECTOR, int, vector);

#define INPUT_FILE "input.txt"
#define BUFF_SIZE 64

static void meassure(size_t num_of_elements)
{
	vector v;
	vector_init(&v);

	for(size_t i = 0; i < num_of_elements; ++i)
	{
		vector_insert(&v, vector_size(&v) / 2, i);
	}

	vector_free(&v);
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
