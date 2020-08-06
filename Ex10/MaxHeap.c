#include<stdio.h>
#include<stdlib.h>

#define L 45
#define maxData 100000

struct employee
{
	int id;
	char name[L];
	float salary;
};

struct heap
{
	int capacity;
	int size;
	struct employee *e;
};

typedef struct heap* maxHeap;

maxHeap create(int n)
{
	maxHeap h = (struct heap*)malloc(sizeof(struct heap));
	h->e = (struct employee*)malloc(sizeof(struct employee) * (n+1));
	h->capacity = n;
	h->size = 0;
	h->e[0].salary = maxData;

	return h;
}

void insert(struct employee data, maxHeap pq)
{
	int i;

	if(pq->capacity == pq->size)
	{
		printf("\nPriority Queue is FULL !");
		return;
	}

	for(i=++pq->size; pq->e[i/2].salary < data.salary; i/=2)
		pq->e[i] = pq->e[i/2];

	pq->e[i] = data;
}

struct employee del(maxHeap pq)
{
	int i, child;

	struct employee max, last;

	if(pq->size == 0)
	{
		printf("\nPriority Queue is EMPTY !");
		return pq->e[0];
	}

	max = pq->e[1];
	last = pq->e[pq->size--];

	for(i=1;(i *2) <= pq->size; i=child)
	{
		child = i*2;

		if(child != pq->size && pq->e[child+1].salary > pq->e[child].salary)
			child++;

		if(last.salary < pq->e[child].salary)
			pq->e[i] = pq->e[child];

		else
			break;
	}

	pq->e[i] = last;
	return max;
}

void display(maxHeap pq)
{
	for(int i=1; i<pq->size+1; i++)
	{
		printf("\n\nEmployee at Node %d", i);
		printf("\nID: %d", pq->e[i].id);
		printf("\nName: %s", pq->e[i].name);
		printf("\nSalary: %.2f", pq->e[i].salary);
	}
}

int main()
{
	int choice, n;

	struct employee emp;

	maxHeap pq;

	do
	{
		printf("\n\n+-------------------------------+");
		printf("\nMENU for Priority Queue using MAX HEAP");
		printf("\n+-------------------------------+");
		printf("\n1. INSERT new Employee");
		printf("\n2. RELIEVE Employee");
		printf("\n3. DISPLAY Priority Queue");
		printf("\n4. EXIT");
		printf("\n+-------------------------------+\n");

		printf("\nEnter choice: ");
		scanf(" %d", &choice);

		switch(choice)
		{
			case 1:	printf("\nEnter number of employee records to be inserted: ");
					scanf(" %d", &n);

					pq = create(n);

					for(int i=0; i<n; i++)
					{
						printf("\nEmployee Record %d", i+1);
						printf("\nEnter ID: ");
						scanf(" %d", &emp.id);
						printf("Enter Name: ");
						scanf(" %s", emp.name);
						printf("Enter Salary: ");
						scanf(" %f", &emp.salary);

						insert(emp, pq);
					}

					break;

			case 2:	emp = del(pq);

					printf("\nDetails of Relieved Employee\n");
					printf("\nID: %d", emp.id);
					printf("\nName: %s", emp.name);
					printf("\nSalary: %.2f", emp.salary);

					break;

			case 3:	printf("\nList of all Employee Records\n");

					display(pq);

					break;

			case 4:	return 0;

			default: printf("\nINVALID INPUT\nRETRY !\n");
		}

	}while(choice != 4);
}