#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAX 2069

void insert(char id[], char *hash_table[]);
int search_element(char key[], char *hash_table[]);
void show(char *hash_table[]);
int hash_function(char key[]);

int main()
{
	char *hash_table[MAX];
	int n, count, option;
	char id[45], key[45];

	for(count = 0; count < MAX; count++)
	{
		hash_table[count] = NULL;
	}

	while(1)
	{
		printf("\n----------------------------------------\n");
		printf("\tMENU FOR MOD HASH TABLE\n");
		printf("----------------------------------------\n");
		printf("1. Insert a String into the Hash Table\n");
		printf("2. Search for a String\n");
		printf("3. Show Hash Table\n");
		printf("4. Quit\n");
		printf("----------------------------------------\n");

		printf("\nEnter your option: ");
		scanf("%d", &option);

		switch(option)
		{
			case 1:	printf("\nEnter the number of Strings to be inserted: ");
					scanf("%d", &n);

					for(int j = 0; j < n; j++)
					{
						printf("Enter the string: ");
						scanf(" %s", id);

						insert(id, hash_table);
					}

					break;

			case 2:	printf("\nEnter the string to search: ");
					scanf("%s", key);

					count = search_element(key, hash_table);

					if(count == -1)
					{
						printf("Element NOT FOUND !\n");
					}

					else
					{
						printf("Element FOUND in Chain: %d\n", count);
					}

					break;

			case 3:	show(hash_table);

					break;

			case 4: return 0;
		}
	}
 }

void insert(char id[], char *hash_table[])
{
	char key[MAX];
	int h;

	strcpy(key, id);

	if(search_element(key, hash_table) != -1)
	{
		printf("Element already present in this location !\nCannot insert %s !\n", id);
		return;
	}

	h = hash_function(key);

	hash_table[h] = id;
}

void show(char *hash_table[])
{
	int count;
	char ptr[45];

	for(count = 0; count < 45; count++)
	{
		printf("\n[ %d ]", count);

		if(hash_table[count] != NULL)
		{
			strcpy(ptr, hash_table[count]);

			printf(" %s ", ptr);

		}
	}
	printf("\n");
}

int search_element(char key[], char *hash_table[])
{
	int h;

	h = hash_function(key);

	if(hash_table[h] != NULL)
		return h;

	return -1;
}

int hash_function(char key[])
{
	int sum = 0;

	for(int i = 0; i < strlen(key); i++)
	{
		sum += 	key[i]	 * (i + 1);
	}

	return (sum % 2069);
}