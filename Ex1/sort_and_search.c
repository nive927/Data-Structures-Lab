#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<termios.h>
# define N 20

//FUNCTION TO IMPLEMENT getch() DUE TO THE ABSENCE OF <conio.h> IN gcc COMPILER

char getch()
{
	char buf=0;

	struct termios old={0};

	fflush(stdout);

	if(tcgetattr(0, &old)<0)
		perror("tcsetattr()");

	old.c_lflag&=~ICANON;
    	old.c_lflag&=~ECHO;
    	old.c_cc[VMIN]=1;
    	old.c_cc[VTIME]=0;

	if(tcsetattr(0, TCSANOW, &old)<0)
		perror("tcsetattr ICANON");

	if(read(0,&buf,1)<0)
		perror("read()");

	old.c_lflag|=ICANON;
   	old.c_lflag|=ECHO;

	if(tcsetattr(0, TCSADRAIN, &old)<0)
		perror ("tcsetattr ~ICANON");

	return buf;
 }

//FUNCTION TO COPY ARRAY CONTENTS INTO A TEMPORARY ARRAY

void arr_copy(int t[], int arr[], int ws)
{
	for(int i=0; i<ws; i++)
		t[i]=arr[i];
}

//FUNCTION TO DISPLAY ARRAY CONTENTS

void arr_display(int arr[], int ws)
{
	for(int i=0; i<ws; i++)
		printf("%d ", arr[i]);

	printf("\n");
}

//FUNCTION TO SORT ARRAY USING SELECTION SORT

void selection_sort(int arr[], int ws)
{
	int small, pos, temp;

	for(int i=0; i<ws; i++)
	{
		small=arr[i];
		pos=i;

		for(int j=i+1; j<ws; j++)
		{
			if(small>arr[j])
			{
				small=arr[j];
				pos=j;
			}
		}

		temp=arr[i];
		arr[i]=arr[pos];
		arr[pos]=temp;
	}
}

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

//FUNCTION TO SEARCH ARRAY USING LINEAR SEARCH

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
		printf("\n\tElement NOT FOUND\n");
	else
		printf("\n\tElement FOUND at position %d\n", pos+1);
}

//FUNCTION TO SEARCH ARRAY USING BINARY SEARCH

void binary_search(int arr[], int ws, int key)
{
	//CALLING FUNCTION TO SORT THE ARRAY

	insertion_sort(arr, ws);

	printf("\n\tSORTED ARRAY  : ");
	arr_display(arr, ws);

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
		printf("\n\tElement NOT FOUND\n");
	else
		printf("\n\tElement FOUND at position %d\n", pos+1);
}

//MAIN PROGRAM

int main()
{
	int arr[N], ws, key, t[N];
	char choice;

	system("clear");

	printf("\n\n\t+----------------------------+\n");
	printf("\t\tARRAY INPUT\n");
	printf("\t+----------------------------+\n\n");

	printf("\n\tEnter the size of array: ");
	scanf("%d", &ws);

	//READING THE CONTENTS OF THE ARRAY

	printf("\n\tEnter the elements of the array\n");
	for(int i=0; i<ws; i++)
	{
		printf("\tElement %d: ", i+1);
		scanf("%d", &arr[i]);
	}

	//DISPLAYING THE MENU

	do
		{
			system("clear");

			printf("\n\n\t+----------------------------+\n");
			printf("\t\tMENU OPTIONS\n");
			printf("\t+----------------------------+\n\n");

			printf("\t1. SORT array using Selection Sort\n\n");
			printf("\t2. SORT array using Insertion Sort\n\n");
			printf("\t3. SEARCH array using Linear Search\n\n");
			printf("\t4. SEARCH array using Binary Search\n\n");
			printf("\t5. EXIT\n\n");

			printf("\n\n\tENTER choice: ");
			scanf(" %c", &choice);

			switch(choice)
			{
				case '1':	arr_copy(t, arr, ws);
							selection_sort(t, ws);
							printf("\n\n\tORIGINAL ARRAY: ");
							arr_display(arr, ws);
							printf("\n\tSORTED ARRAY  : ");
							arr_display(t, ws);
							getch();
							break;

				case '2':	arr_copy(t, arr, ws);
							insertion_sort(t, ws);
							printf("\n\n\tORIGINAL ARRAY: ");
							arr_display(arr, ws);
							printf("\n\tSORTED ARRAY  : ");
							arr_display(t, ws);
							getch();
							break;

				case '3':	printf("\n\n\tORIGINAL ARRAY: ");
							arr_display(arr, ws);
							printf("\n\tEnter the element to be searched: ");
							scanf("%d", &key);
							arr_copy(t, arr, ws);
							linear_search(t, ws, key);
							getch();
							break;

				case '4':	printf("\n\n\tORIGINAL ARRAY: ");
							arr_display(arr, ws);
							printf("\n\tEnter the element to be searched: ");
							scanf("%d", &key);
							arr_copy(t, arr, ws);
							binary_search(t, ws, key);
							getch();
							break;

				case '5':	system("clear");
							return 0;
							break;

				default:	printf("\n\tINVALID OPTION .....!!!!!\n\n");
							getch();

			}
		}while(choice!=5);
}
