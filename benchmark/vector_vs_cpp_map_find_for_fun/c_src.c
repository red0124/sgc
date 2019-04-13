#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SGC_ST
#include "../lib/algorithm.h"
#include "../lib/static_types.h"
#include "../lib/deque.h"

SGC_INIT(DEQUE, int, deque, BINARY_FIND);

#define INPUT_FILE "input.txt"
#define BUFF_SIZE 64

static void meassure(size_t num_of_elements)
{
	deque v;
	deque_init(&v);

	for(size_t i = 0; i < num_of_elements; ++i)
	{
		deque_push_back(&v, i);
	}

	for(size_t i = 0; i < num_of_elements; ++i)
	{
		for(size_t j = 0; j < 9; ++j)
		{
			deque_binary_find_el(&v, i);
		}
	}

	deque_free(&v);
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
