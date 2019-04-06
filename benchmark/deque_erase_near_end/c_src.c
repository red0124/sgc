#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SGC_ST
#include "../../lib/algorithm.h"
#include "../../lib/static_types.h"
#include "../../lib/deque.h"

SGC_INIT(DEQUE, int, deque);

#define INPUT_FILE "input.txt"
#define BUFF_SIZE 64

static void meassure(size_t num_of_elements)
{
	deque d;
	deque_init(&d);

	for(size_t i = 0; i < num_of_elements; ++i)
	{
		deque_push_back(&d, i);
	}

	while(!deque_empty(&d))
	{
		deque_erase_at(&d, 2 * deque_size(&d) / 3);
	}

	deque_free(&d);
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
