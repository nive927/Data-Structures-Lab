#include<stdio.h>

//FUNCTION TO SORT ARRAY USING INSERTION SORT

void insertion_sort(int arr[], int ws)
{
	int small, j;

	for(int i=1; i<ws; i++)
	{
		small=arr[i];
		j=i-1;

		while((j>=0)&&(small<arr[j]))
		{
			arr[j+1]=arr[j];
			j--;
		}

		arr[j+1]=small;
	}
}

void binary_search(int arr[], int ws, int key)
{
	//CALLING FUNCTION TO SORT THE ARRAY

	insertion_sort(arr, ws);

	for(int i=0; i<ws; i++)
		printf("%d\n", arr[i]);

	int lb=0, ub=ws-1, mid, pos=-1;

	while((pos==-1)&&(lb<=ub))
	{
		mid=(lb+ub)/2;

		if(arr[mid]==key)
		{
			pos=mid;
			break;
		}

		else if(arr[mid]>key)
			ub=mid-1;
		else
			lb=mid+1;
	}

	if(pos==-1)
		printf("Element NOT FOUND\n");
	else
		printf("Element FOUND at position %d\n", pos+1);
}

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

	//CALLING FUNCTION FOR BINARY SEARCH

	binary_search(arr, ws, key);

	return 0;
}