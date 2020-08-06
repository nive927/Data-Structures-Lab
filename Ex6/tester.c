#include "queue.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	struct Node *front = NULL, *rear = NULL;
	enqueue(&front, &rear, 1, 6);
	display(&front, &rear);
}