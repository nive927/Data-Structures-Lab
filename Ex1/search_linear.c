#include<stdio.h>

//FUNCTION FOR LINEAR SEARCH

void linear_search(int arr[], int ws, int key)
{
	int pos=-1;

	for(int i=0; i<ws; i++)
	{
		if(arr[i]==key)
		{
			pos=i;
			break;
		}
	}

	if(pos==-1)
		printf("Element NOT FOUND\n");
	else
		printf("Element FOUND at position %d\n", pos+1);
}

//MAIN

int main()
{
	int arr[20], ws, key;

	printf("Enter the size of array: ");
	scanf("%d", &ws);

	//READING THE ARRAY

	printf("Enter the elements of the array\n");
	for(int i=0; i<ws; i++)
	{
		printf("Element %d: ", i+1);
		scanf("%d", &arr[i]);
	}

	printf("Enter the element to be searched: ");
	scanf("%d", &key);

	//CALLING FUNCTION FOR LINEAR SEARCH

	linear_search(arr, ws, key);

	return 0;
}