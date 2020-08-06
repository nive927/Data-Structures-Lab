#include<stdio.h>
#include<stdlib.h>

struct cNode
{
	char c;
	struct cNode *next;
};

void cpush(struct cNode **top, char input)
{
	struct cNode *newNode = (struct cNode*)malloc(sizeof(struct cNode*));

	newNode->c = input;

	if(*top == NULL)
		newNode->next = NULL;

	else
		newNode->next = *top;

	*top = newNode;

}

char cpop(struct cNode **top)
{
	if(*top == NULL)
		return 0;	// To check empty Stack condition

	else
	{
		struct cNode *temp = (struct cNode*)malloc(sizeof(struct cNode*));
		char ch;

		temp = *top;
		ch = temp->c;
		*top = (*top)->next;
		free(temp);
		return ch;
	}
}

void cdisplay(struct cNode **top)
{
	if(*top == NULL)
		printf("\n\n\t\tStack is EMPTY!");

	else
	{
		struct cNode *temp = (struct cNode*)malloc(sizeof(struct cNode*));

		printf("\n\n\t\tSTACK AS VIEWED FROM THE TOP\n");
		for(temp = *top; temp != NULL; temp = temp->next)
			printf("%c ", temp->c);

		printf("\n");
	}
}
