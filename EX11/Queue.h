#include<stdlib.h>
#include<stdio.h>

/* Queue node structure definition
front and rear will be manipulated from the driver function
or will be passed as parameters for other function */
struct Node
{
	char c;
	struct Node *next;
};

// Function to display nodes in queue
void display(struct Node **front, struct Node **rear)
{
	if(*front == NULL)
		printf("\nEMPTY Queue!");

	else
	{
		struct Node *tempNode = (struct Node*)malloc(sizeof(struct Node));
		tempNode = *front;

	    if ((tempNode == NULL) && (*rear == NULL))
	    {
	        printf("\nEMPTY Queue!");
	        return;
	    }

	    while (tempNode != *rear)
	    {
			printf("\nDATA: %c", tempNode->c);

			tempNode = tempNode->next;
		}

		if (tempNode == *rear)
		{
			printf("\nDATA: %c", tempNode->c);
		}
	}
}

/* Function to insert new node at the end of the queue.
In queue, insertion always happens at the rear */
void enqueue(struct Node **front, struct Node **rear, char c)
{
	struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));

	newNode->c = c;
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
char dequeue(struct Node **front)
{
	if(*front == NULL)
		return '\0';

	else
	{
		struct Node *tempNode = (struct Node*)malloc(sizeof(struct Node));

		tempNode = *front;
		*front = (*front)->next;

		char ch = tempNode->c;

		free(tempNode);

		return ch;
	}
}


