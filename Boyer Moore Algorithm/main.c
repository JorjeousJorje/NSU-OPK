#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

char* my_strstr(char* haystack, const char* needle)
{
	size_t N = strlen(haystack);
	size_t M = strlen(needle);

	int d[256];

	for (int i = 0; i < 256; i++)
	{
		d[i] = M;
	}

	for (int i = 0; i < M - 1; i++)
	{
		d[needle[i]] = M - 1 - i;
	}
	
	for (int i = M - 1; i < N;)
	{
		for (int k = i, j = M - 1; j >= 0; k--, j--)
		{
			if (haystack[k] != needle[j])
			{
				i += d[haystack[i]];
				break;
			}

			if (j == 0)
			{
				return (haystack + k);
			}
		}
	}
	return NULL;


}

int check_strstr(char* haystack, const char* needle)
{
	char* str = my_strstr(haystack, needle);
	if (str != NULL)
	{
		return my_strstr(haystack, needle) - haystack;
	}
	else
	{
		return -1;
	}
}

int main() 
{
	assert(check_strstr("datadata", "datadata") == 0);

	assert(check_strstr("23erfedfdf2vgerf", "2vgerf") == 10) ;

	assert(check_strstr("vdfvrggrgefrf", "fv") == 2);

	assert(check_strstr("efbtbhhththtgtg", "f") == 1);

	assert(check_strstr("rrrarlerll", "rlerl") == 4);

	assert(check_strstr("aaarrrarlerlle", "rlerlle") == 7);

	assert(check_strstr("rrrarlerlle", "ay") == -1);

	assert(check_strstr("arrarlerllerrr", "rrr") == 11);

	assert(check_strstr("arrrarlerllb", "rlerllb") == 5);

	assert(check_strstr("SDL2_GFXPRIMITIVES_SCOPE int filledCircleRGBA", "GFX") == 5);

	char* haystack = (char*)malloc(sizeof(char) * 100000);

	if (haystack == NULL) 
	{
		return 1;
	}

	for (int i = 0; i < 100000; i++)
	{
		haystack[i] = 'r';
	}
	haystack[89000] = 'r'; 
	haystack[89001] = 's'; 
	haystack[89002] = 'a'; 
	haystack[89003] = 'r'; 
	haystack[89004] = '1'; 
	haystack[89005] = '1';
	assert(check_strstr(haystack, "rsar11") == 89000);

	free(haystack);

	return 0;
}

