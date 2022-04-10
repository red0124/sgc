#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "words.txt"

#include <SGC/string.h>
#include <SGC/unordered_map.h>

SGC_INIT(STRING, string);
SGC_INIT_PAIR(UNORDERED_MAP, string, int, map);

int main(void)
{
        map m;
        map_init(&m);

        fs_string buff;

        FILE *fin = fopen(FILE_NAME, "r");
	if(!fin)
	{
		exit(EXIT_FAILURE);
	}

	while(string_buffer_read_until(buff, fin, "\n"))
	{
		++*map_at(&m, buff);
	}
	fclose(fin);

        for_each(i in m as map)
        {
	        if(i->value > 1)
	        {
		        printf("%s -> %d", i->key, i->value);
		}
	}
        map_free(&m);
        return 0;
}

