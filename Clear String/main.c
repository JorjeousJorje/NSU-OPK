#define _CRTDBG_MAP_ALLOC
#include <assert.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

void strclear(char *str)
{
	int i = 0;
	for (int j = 0; str[j] != '\0'; j++, i++)
	{
		while (isspace(str[j]) != 0 && isspace(str[j + 1]) != 0)
		{
			j++;//двигаемся по строке, находя все пробелы подряд
		}
		str[i] = str[j];//перетаскиваем буквы в сохранность
	}
	str[i] = '\0';//обрубаем пробелы
}

int main()
{
	char str1[] = "he    gr,.ec.   .>>  <<<fe  eegrg     loo";
	strclear(str1);
	assert(strcmp(str1, "he gr,.ec. .>> <<<fe eegrg loo") == 0);//1


	char* big_one = malloc(1000000 * sizeof(char));
	for (int i = 0; i < 1000000; i++)
	{
		big_one[i] = ' ';
	}
	big_one[0] = 'a';
	big_one[14] = 'm';
	big_one[999998] = 'b';
	big_one[999999] = '\0';
	strclear(big_one);
	assert(strcmp(big_one, "a m b") == 0);//2
	free(big_one);

	char str2[] = "    34 55   46   tht ht";
	strclear(str2);
	assert(strcmp(str2, " 34 55 46 tht ht") == 0);//3

	char str3[] = "                   34                   ";
	strclear(str3);
	assert(strcmp(str3, " 34 ") == 0);//4
	
	char str4[] = "  4 4   4      4 asg_ _ _ 34  ";
	strclear(str4);
	assert(strcmp(str4, " 4 4 4 4 asg_ _ _ 34 ") == 0);//5
}