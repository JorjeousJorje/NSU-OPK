#pragma once
#include <stdio.h>
typedef void* Pointer;

typedef unsigned (*HashFunction)(char* key);

typedef void (*Destructor)(Pointer);

typedef struct tList 
{
	char* key;
	Pointer data;
	struct tList* next;
} List;

typedef struct HashTable 
{
	size_t size;
	List** table;
	HashFunction hashfunc;
	Destructor dtor;
} HashTable;

/* ���������������� �������.
 *
 * size - ������ �������� �������;
 * hf   - ���-�������;
 * dtor - ����������. ���� ������� ����� ������������ data ��������� ���������
 *        (ht_destroy, ht_delete, � ����� ��� ���������� ��������� � ht_set).
 *
 * ���� hf=0, ������� ����������� ������� (��������).
 * ���� dtor=0, ���������� ����������� (�� ����� ����������).
 */
double ht_collision_ratio(HashTable* ht);

void ht_init(HashTable* ht, size_t size, HashFunction hf, Destructor dtor);

/* ���������� ������� */
void ht_destroy(HashTable* ht);

/* �������� � ������� ������������ key -> data. ���� key ��� �����������,
 * �����. ���� data ����� ������� (dtor) � ������������ */
Pointer ht_set(HashTable* ht, char* key, Pointer data);

/* �������� �������� �� �����. ���� ����� ��� � �������, ������� 0. */
Pointer ht_get(HashTable* ht, char* key);

/* �������� ������������� ����� key � �������. 1 - ����, 0 - ���. */
int ht_has(HashTable* ht, char* key);

/* ������� ������� � ������ key �� ������� (���� �� ����) */
void ht_delete(HashTable* ht, char* key);

/* ����� ������� � ���������� ���� ���������. ������� f ����� ������� ���
 * ���� ��� (key, data) �� ������� */
void ht_traverse(HashTable* ht, void (*f)(char* key, Pointer data));

/* �������� ������ �������� �������.
 *
 * ��������� ��������: �������� ����� ������ table � ��������� � ���� ���
 * ������������ ��������� List �� ������ table, ����� ������ ���������� �
 * �������� �����.
 *
 * ��� �����������, ��� ��������� ����� ������� � ������ � ��� �����������
 * �������.
 */
void ht_resize(HashTable* ht, size_t new_size);