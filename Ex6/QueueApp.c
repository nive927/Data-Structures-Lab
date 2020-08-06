#include "queue.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

static float totWaitTime1 = 0, totWaitTime2 = 0, totBurst1 = 0, totBurst2 = 0;
static int n1 = 0, n2 = 0;

/* Function to calculate the waiting time for
a particular job in both queues*/
void calcNodeWaiting(struct Node **frontQ1, struct Node **rearQ1, struct Node **frontQ2, struct Node **rearQ2, int jobNo, float burstTime)
{
	float waitTime1 = 0, waitTime2 = 0;
	struct Node *temp1 = *frontQ1, *temp2 = *frontQ2;

	if(temp1 != NULL || temp2 != NULL)
	{
		while (temp1 != *rearQ1)
		{
			waitTime1 += temp1->burstTime;
			temp1 = temp1->next;
		}

		if (temp1 == *rearQ1)
			waitTime1 += temp1->burstTime;

		while (temp2 != *rearQ2)
		{
			waitTime2 += temp2->burstTime;
			temp2 = temp2->next;
		}

		if (temp2 == *rearQ2 && temp2 != NULL)
			waitTime2 += temp2->burstTime;
	}

	if(waitTime1 <= waitTime2)
	{	enqueue(frontQ1, rearQ1, jobNo, burstTime);
		totBurst1 += burstTime;
		totWaitTime1 += totBurst1;
		n1++;
	}

	else
	{	enqueue(frontQ2, rearQ2, jobNo, burstTime);
		totBurst2 += burstTime;
		totWaitTime2 += totBurst2;
		n2++;
	}
}

int main()
{
	char choice = 'y';

	int jobNo;
	float burstTime;

	struct Node *frontQ1 = NULL, *rearQ1 = NULL;
	struct Node *frontQ2 = NULL, *rearQ2 = NULL;

	while(choice == 'y' || choice == 'Y')
	{
		printf("\nEnter Job Number: ");
		scanf("%d", &jobNo);
		printf("Enter Burst Time: ");
		scanf("%f", &burstTime);

		calcNodeWaiting(&frontQ1, &rearQ1, &frontQ2, &rearQ2, jobNo, burstTime);

		printf("\nDo you want to continue? YES:Y/y NO:ANYTHING BUT Y/y\n");
		printf("Enter choice: ");
		scanf(" %c", &choice);
	}

	printf("\nDisplay Q1\n");
	display(&frontQ1, &rearQ1);
	printf("\n\tAverage Wait Time of Q1: %.2f\n", totWaitTime1/n1);
	printf("\nDisplay Q2\n");
	display(&frontQ2, &rearQ2);
	printf("\n\tAverage Wait Time of Q2: %.2f\n", totWaitTime2/n2);

}