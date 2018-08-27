#pragma once

typedef char *string;

int string_is_static()
{
        return 0;
}

void string_copy(string *first, const string *const second)
{
        *first = (string)malloc(sizeof(char) * (1 + strlen(*second)));
        strcpy(*first, *second);
}

void string_init(string *s)
{
        *s = NULL;
}

void string_free(string *s)
{
        free(*s);
}

int string_equal(const string *const first, const string *const second)
{
        return strcmp(*first, *second) == 0;
}

int string_compare(const string *const first, const string *const second)
{
        return strcmp(*first, *second);
}

int string_void_compare(const void *const first, const void *const second)
{
        return strcmp(*(string*)first, *(string*)second);
}

int string_read_buffer(string *s, FILE *f, char *buff, size_t buff_size)
{
        char *tmp = fgets(buff, buff_size, f);
        if(tmp)
        {
                size_t size = strlen(buff);
                buff[size - 1] = '\0';
                *s = (string)malloc(sizeof(char) * (size));
                memcpy(*s, buff, sizeof(char) * (size));
        }
        return (int)tmp;
}

int string_read_untill(string *s, FILE *f, char *del)
{
        *s = NULL;
        char c;
        size_t size = 0;
        size_t max = 0;
        while(1)
        {
                if(fscanf(f, "%c", &c) == EOF)
                {
                        break;
                }
                int finish = 0;
                for(size_t i = 0; i < strlen(del); ++i)
                {
                        if(del[i] == c)
                        {
                                finish = 1;
                                break;
                        }
                }
                if(finish == 1)
                {
                        break;
                }
                if(size == max)
                {
                        max = (max == 0) ? 1 : 2 * max;
                        *s = (string)realloc(*s, sizeof(char) * (max + 1));
                }
                (*s)[size++] = c;
        }
        if(size)
        {
                (*s)[size] = '\0';
        }
        return size;
}

int string_read(string *s, FILE *f)
{
        return string_read_untill(s, f, " \n");
}

int string_read_file(string *s, const char * const file_name)
{
	FILE *f = fopen(file_name, "r");
	int ret = string_read_untill(s, f, "");
	fclose(f);
	return ret;
}
