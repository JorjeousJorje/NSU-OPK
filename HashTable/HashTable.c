#define _CRTDBG_MAP_ALLOC
#include "HashTable.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

static unsigned jenkins_one_at_a_time_hash(char* key) 
{
	unsigned hash = 0;

	for (; *key; ++key) 
	{
		hash += *key;
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}

static List* list_set(List* list, char* key, Pointer data, HashTable* ht, Pointer* buffer)
{
	if (list == NULL)
	{
		list = (List*)malloc(sizeof(List));
		if (list != NULL)
		{
			list->data = data;
			list->key = key;
			list->next = NULL;
		}
	}
	else
		if (list->key == key)
		{
			*buffer = list->data;
			if (ht->dtor != NULL)
			{
				ht->dtor(list->data);
			}
			list->data = data;
		}
		else
			if (list->key != key)
			{
				list->next = list_set(list->next, key, data, ht, buffer);
			}
	return(list);
}

double ht_collision_ratio(HashTable* ht)//сумму квадратов длинн всех списков поделить накол-во элеметнов
{
	double sum = 0;
	for (size_t i = 0; i < ht->size; i++)
	{
		List* list = ht->table[i];
		List* list_next = NULL;
		size_t count = 0;

		while (list != NULL)
		{
			count++;
			list_next = list;
			list = list->next;
		}
		sum += count * count;
	}
	double sum_elem = sum / ht->size;
	double collis = sum_elem / sum;

	return collis;
}

void ht_init(HashTable* ht, size_t size, HashFunction hf, Destructor dtor)
{
	assert(size != 0);
	ht->size = size;
	ht->dtor = dtor;
	ht->hashfunc = hf;

	if (hf == 0)
	{
		ht->hashfunc = jenkins_one_at_a_time_hash;
	}

	ht->table = (List**)malloc(size * sizeof(List*));
	if (ht->table == NULL)
	{
		return NULL;
	}

	for (size_t i = 0; i < size; i++)
	{
		ht->table[i] = NULL;
	}
}

void ht_destroy(HashTable* ht)
{
	if (ht == NULL)
	{
		return;
	}
	for (size_t i = 0; i < ht->size; i++)
	{
		List* list = ht->table[i];
		List* list_next = NULL;

		while (list != NULL)
		{
			list_next = list;
			list = list->next;
			free(list_next);
		}
		ht->table[i] = NULL;
	}
	free(ht->table);
}

Pointer ht_set(HashTable* ht, char* key, Pointer data)
{
	Pointer deleted = NULL;
	size_t position = ht->hashfunc(key) % ht->size;

	List* list = ht->table[position];
	List** prev_table = &ht->table[position];//беру адрес ячейки нужной позиции, пока абстрактной

	while (1)
	{
		if (list == NULL)
		{
			List* list = (List*)malloc(sizeof(List));
			if (list == NULL)
			{
				return NULL;
			}

			*prev_table = list;//ложу этот указатель в массив указателей по нужному адресу
			
			if (list != NULL)
			{
				list->data = data;
				list->key = key;
				list->next = NULL;
				break;
			}
		}
		else
		if (list != NULL)
		{
			if (list->key == key)
			{
				deleted = list->data;
				if (ht->dtor != NULL)
				{
					ht->dtor(list->data);
				}
				list->data = data;
				break;
			}
			else
			{
				prev_table = &list->next;//нужно запомнить куда положить следующий элемент, т.е он может быть NULL
				list = list->next;
			}
		}
	}
	return deleted;
}

Pointer ht_get(HashTable* ht, char* key)
{
	size_t position = ht->hashfunc(key) % ht->size;

	List* list = ht->table[position];

	while (list != NULL)
	{
		if (strcmp(list->key,key) == 0)
		{
			return list->data;
		}
		else
		{
			list = list->next;
		}
	}
}

int ht_has(HashTable* ht, char* key)
{
	return ht_get(ht, key) != NULL;
}

void ht_delete(HashTable* ht, char* key)
{
	size_t position = ht->hashfunc(key) % ht->size;

	List* list = ht->table[position];
	List** prev_table = &ht->table[position];

	while (list != NULL)
	{
		if (strcmp(list->key, key) == 0)
		{
			List* next = list->next;
			*prev_table = next;

			if (ht->dtor != NULL)
			{
				ht->dtor(list->data);
			}
			free(list);
			list = NULL;
		}
		else
		{
			prev_table = &list->next;
			list = list->next;
		}
	}
}

void ht_traverse(HashTable* ht, void(*foreach_func)(char* key, Pointer data))
{
	for (size_t i = 0; i < ht->size; i++)
	{
		List* list = ht->table[i];
		while (list != NULL)
		{
			foreach_func(list->key, list->data);
			list = list->next;
		}
	}
}

void ht_resize(HashTable* ht, size_t new_size)
{
	size_t old_size = ht->size;
	ht->size = new_size;

	List** big_table = (List**)malloc(new_size * sizeof(List*));
	if (big_table == NULL)
	{
		return;
	}

	for (size_t i = 0; i < new_size; i++)
	{
		big_table[i] = NULL;
	}

	for (size_t i = 0; i < old_size; i++)
	{
		List* list = ht->table[i];

		while(list != NULL)
		{
			size_t position = ht->hashfunc(list->key) % ht->size;
			List* new_list = big_table[position];//нашли куда положить

			ht->table[i] = list->next;

			list->next = new_list;
			big_table[position] = list;
			list = ht->table[i];
		}
	}
	free(ht->table);
	ht->table = big_table;
}

//void ht_resize(HashTable* ht, size_t new_size)
//{
//	List** big_table = (List**)malloc(new_size * sizeof(List*));
//	if (big_table == NULL)
//	{
//		return(-1);
//	}
//	for (size_t i = 0; i < new_size; i++)
//	{
//		big_table[i] = NULL;
//	}
//
//
//	size_t old_size = ht->size;
//	ht->size = new_size;
//	for (size_t i = 0; i < old_size; i++)
//	{
//		List* list = ht->table[i];
//		if (list != NULL)
//		{
//			Pointer data = list->data;
//			char* key = list->key;
//			List* next = list->next;
//			free(list);
//			ht->table[i] = next;
//			list = next;
//			Pointer buffer;
//			size_t count = ht->hashfunc(key) % ht->size;
//			big_table[count] = list_set(big_table[count], key, data, ht, &buffer);
//			i--;
//		}
//	}
//	free(ht->table);
//	ht->table = big_table;
//}