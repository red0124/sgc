#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SGC/vector.h>
#include <SGC/string.h>
#include <SGC/algorithm.h>

SGC_INIT(STRING, string);
SGC_INIT(VECTOR, string, vector, QSORT, ITERATE);

int main(void)
{

	char buff[32];
	string s = buff;

	vector v;
	vector_init(&v);

	while(string_buffer_read_until(buff, stdin, "\n "))
	{
		int palindrome = 1;
		// for each intersect
		for_eachi(i in s, s as string)
		{
			if(*i.first != *i.second)
			{
				palindrome = 0;
				break;
			}
			if(i.first == i.second)
			{
				break;
			}
		}
		if(palindrome)
		{
			printf("Perfectly balanced. As all things shoud be.\n");
			vector_push_back(&v, s);
		}
	}

	vector_sort(&v, NULL);

	FILE* f = fopen("out.txt", "w");
	if(!f)
	{
		exit(EXIT_FAILURE);
	}

	vector_fprintf(&v, "%s\n", f);
	fclose(f);

	vector_free(&v);
        return 0;
}
