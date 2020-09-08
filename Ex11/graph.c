#include<stdio.h>
#include<stdlib.h>

struct node
{
	int name;
	struct node* next;
};

struct graph
{
	int numVertices;
	struct node** adjLists;
};

struct node* createNode(int name)
{
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	newNode->name = name;
	newNode->next = NULL;

	 return newNode;
}

struct graph* createGraph(vnames[], int n)
{
	struct graph* g = (struct graph*)malloc(sizeof(struct graph));

	for(int i=0; i<n; i++)
	{
		adjLists[i] = (struct node*)malloc(sizeof(struct node)*n);
		adjLists[i]->name = vnames[i];
		adjlists[i]->next = NULL;
	}
}

int main()
{
	return 0;
}