#include<stdio.h>

//FUNCTION FOR INSERTING AN ELEMENT

void deletion(int arr[], int ws, int key, int pos)
{
	for(int i=pos-1; i<ws-1; i++)
		arr[i]=arr[i+1];

	printf("\nArray after deletion\n");
	for(int i=0; i<ws-1; i++)
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

	deletion(arr, ws, key, pos);

	return 0;
}