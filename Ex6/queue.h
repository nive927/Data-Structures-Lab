#include<stdlib.h>
#include<stdio.h>

/* Queue node structure definition
front and rear will be manipulated from the driver function
or will be passed as parameters for other function */
struct Node
{
	int jobNo;
	float burstTime;

	struct Node *next;
};

// Function to display nodes in queue
void display(struct Node **front, struct Node **rear)
{
	if(*front == NULL)
		printf("\n\tEMPTY Queue!");

	else
	{
		struct Node *tempNode = (struct Node*)malloc(sizeof(struct Node));
		tempNode = *front;

	    if ((tempNode == NULL) && (*rear == NULL))
	    {
	        printf("\n\tEMPTY Queue!");
	        return;
	    }

	    while (tempNode != *rear)
	    {
			printf("\n\tJob Number: %d\n", tempNode->jobNo);
 			printf("\tBurst Time: %.2f\n", tempNode->burstTime);

			tempNode = tempNode->next;
		}

		if (tempNode == *rear)
		{
			printf("\n\tJob Number: %d\n", tempNode->jobNo);
			printf("\tBurst Time: %.2f\n", tempNode->burstTime);
		}
	}
}

/* Function to insert new node at the end of the queue.
In queue, insertion always happens at the rear */
void enqueue(struct Node **front, struct Node **rear, int jobNo, float burstTime)
{
	struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));

	newNode->jobNo = jobNo;
	newNode->burstTime = burstTime;
	newNode->next = NULL;

	if((*front == NULL) || (*rear == NULL))
		*front = *rear = newNode;

	else
	{
		(*rear)->next = newNode;
		*rear = newNode;
	}
}

/* Function to delete new node at the beginning of the queue.
In queue, deletion always happens at the front */
void dequeue(struct Node **front)
{
	if(*front == NULL)
		printf("\n\tEMPTY Queue!");

	else
	{
		struct Node *tempNode = (struct Node*)malloc(sizeof(struct Node));

		tempNode = *front;
		*front = (*front)->next;
		free(tempNode);
	}
}


