
//HEADER FILES
#include<stdio.h>
#include<stdlib.h>

//STACK NODE STRUCTURE DEFINITION
struct fNode
{
	float c;
	struct fNode *next;
};

//PUSH FUNCTION
void fpush(struct fNode **top, float input)
{
	struct fNode *newNode = (struct fNode*)malloc(sizeof(struct fNode*));

	newNode->c = input;

	if(*top == NULL)
		newNode->next = NULL;

	else
		newNode->next = *top;

	*top = newNode;

}

//POP FUNCTION
float fpop(struct fNode **top)
{
	if(*top == NULL)
		return 0;	// To check empty Stack condition

	else
	{
		struct fNode *temp = (struct fNode*)malloc(sizeof(struct fNode*));
		float ch;

		temp = *top;
		ch = temp->c;
		*top = (*top)->next;
		free(temp);
		return ch;
	}
}

//STACK DISPLAY
void fdisplay(struct fNode **top)
{
	if(*top == NULL)
		printf("\n\n\t\tStack is EMPTY!");

	else
	{
		struct fNode *temp = (struct fNode*)malloc(sizeof(struct fNode*));

		printf("\n\n\t\tSTACK AS VIEWED FROM THE TOP\n");
		for(temp = *top; temp != NULL; temp = temp->next)
			printf("%.2f ", temp->c);

		printf("\n");
	}
}