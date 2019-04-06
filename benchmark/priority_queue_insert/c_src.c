#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SGC_ST
#include "../../lib/algorithm.h"
#include "../../lib/static_types.h"
#include "../../lib/priority_queue.h"

SGC_INIT(PRIORITY_QUEUE, int, pqueue);

#define INPUT_FILE "input.txt"
#define BUFF_SIZE 64

static void meassure(size_t num_of_elements)
{
	pqueue p;
	pqueue_init(&p);

	for(size_t i = 0; i < num_of_elements; ++i)
	{
		pqueue_push(&p, i);
	}

	pqueue_free(&p);
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
