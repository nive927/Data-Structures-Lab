#include<stdio.h>

//FUNCTION FOR INSERTING AN ELEMENT

void insert(int arr[], int ws, int key, int pos)
{
	for(int i=ws; i>=pos-1; i--)
		arr[i]=arr[i-1];

	arr[pos-1]=key;

	printf("\nArray after insertion\n");
	for(int i=0; i<=ws; i++)
		printf("Element %d: %d\n", i+1, arr[i]);
}

//MAIN

int main()
{
	int arr[20], ws, key, pos;

	printf("\nEnter the size of array: ");
	scanf("%d", &ws);

	//READING THE ARRAY

	printf("\nEnter the elements of the array\n");
	for(int i=0; i<ws; i++)
	{
		printf("Element %d: ", i+1);
		scanf("%d", &arr[i]);
	}

	printf("\nEnter the element to be inserted: ");
	scanf("%d", &key);

	printf("\nEnter the position of insertion: ");
	scanf("%d", &pos);

	//CALLING FUNCTION FOR INSERTION

	insert(arr, ws, key, pos);

	return 0;
}