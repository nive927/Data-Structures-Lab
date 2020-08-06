#include<stdio.h>
#include<stdlib.h>

#include "CharStack.h"
#include "Queue.h"

//max number of vertices in a graph - used for naming the vertices in an array
#define N 10

struct node
{
    char name;
    struct node* next;
};

struct Graph
{
    int numVertices;
    struct node** adjLists;
};

struct node* createNode(char v)
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->name = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(char vNames[], int vertices)
{
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));

    graph->numVertices = vertices;

    graph->adjLists = (struct node**)malloc(vertices * sizeof(struct node*));

    for (int i = 0; i < vertices; i++)
    {
		graph->adjLists[i] = (struct node*)malloc(vertices * sizeof(struct node));
    	graph->adjLists[i]->name = vNames[i];
    	graph->adjLists[i]->next = NULL;
    }

    return graph;
}

//src is the node for which we are passing dest as the adjacent nodes
void addEdge(struct Graph* graph, char src, char dest)
{
    struct node* newNode;
    int srcIndex;

    for(int i=0; i < graph->numVertices; i++)
    	if(graph->adjLists[i]->name == src)
    	{
    		srcIndex = i;
    		break;
    	}

    /*newNode = createNode(dest);
    newNode->next = graph->adjLists[srcIndex];
    graph->adjLists[srcIndex] = newNode;*/

	newNode = createNode(dest);

	//To insert at the end of the list
    struct node* temp = graph->adjLists[srcIndex];

	while(temp->next != NULL)
		temp = temp->next;

	temp->next = newNode;
}

void printGraph(struct Graph* graph)
{
	printf("\nADJACENCY LISTS OF THE GRAPH:\n");

    for (int v = 0; v < graph->numVertices; v++)
    {
        struct node* temp = graph->adjLists[v];
        printf("Adjacency list of vertex %c: ", temp->name);

		//First Node is the source node itself
        temp = temp->next;

        while (temp != NULL)
        {
            printf("%c ", temp->name);
            temp = temp->next;
        }

        printf("\n");
    }
}

int visitedSearch(char visited[], char vName, int n)
{
	for(int k=0; k <= n; k++)
		if(visited[k] == vName)
			return 1;

	return 0;
}

void DFS(struct Graph* graph, struct node* startNode)
{
	//printf("\nEnter Function\n");

	struct node* temp = startNode;
	struct cNode* stack = NULL;
	char vName;

	char visited[10];

	int visitIndex = 0;

	cpush(&stack, temp->name);

	while(stack != NULL)
	{
		//printf("\nStack display after push\n");

		//printf("\nEnter while Loop\n");
		int vIndex = -1;
		vName = cpop(&stack);

		//printf("\nStack display after pop\n");

		if(!visitedSearch(visited, vName, visitIndex))
		{
		//	printf("\nEnter unvisted Loop\n");
			visited[visitIndex] = vName;
			visitIndex++;

			for(int j=0; j < graph->numVertices; j++)
				if(graph->adjLists[j]->name == vName)
				{
					vIndex = j;
					break;
				}

			temp = 	graph->adjLists[vIndex]->next;

			while (temp != NULL)
			{
				cpush(&stack, temp->name);
				temp = temp->next;
        	}

        //	printf("\nStack display after push in unvisted if\n");
		}
	}

	printf("\nDFS ORDER with startnode %c: ", startNode->name);
	for(int i=0; i < visitIndex; i++)
		printf("%c ", visited[i]);

	printf("\n");

}

void BFS(struct Graph* graph, struct node* startNode)
{
	//printf("\nEnter Function\n");

	struct node* temp = startNode;
	struct Node *front = NULL, *rear = NULL;
	char vName;

	char visited[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	int visitIndex = 0;

	enqueue(&front, &rear, temp->name);

	while(!((front == NULL) || (rear == NULL)))
	{
		//printf("\nQUEUE display after push\n");
		//display(&front, &rear);

		//printf("\nEnter while Loop\n");
		int vIndex = -1;
		vName = dequeue(&front);

		//printf("\nvname: %c\n", vName);

		//printf("\nQUEUE display after pop\n");
		//display(&front, &rear);

		//printf("\nsearchVisited: %d\n", visitedSearch(visited, vName, visitIndex));

		if(!(visitedSearch(visited, vName, visitIndex)))
		{
			//printf("\nEnter unvisted Loop\n");
			visited[visitIndex] = vName;
			visitIndex++;

			for(int j=0; j < graph->numVertices; j++)
				if(graph->adjLists[j]->name == vName)
				{
					vIndex = j;
					break;
				}

			temp = 	graph->adjLists[vIndex]->next;

			while (temp != NULL)
			{
				if(!visitedSearch(visited, temp->name, visitIndex))
				{	enqueue(&front, &rear, temp->name);
					visitIndex++;
				}

				temp = temp->next;
        	}

        	//printf("\nQUEUE display after push in unvisted if\n");
			//display(&front, &rear);
		}
	}

	printf("\nBFS ORDER with startnode %c: ", startNode->name);
	for(int i=0; i < visitIndex; i++)
		printf("%c ", visited[i]);

	printf("\n");

}

int main()
{
    int numVertices, numAdj;
    struct Graph* graph = NULL;
    char vNames[N], adjName;
    struct node* startNode = (struct node*)malloc(sizeof(struct node));

    printf("\nEnter the number of vertices: ");
    scanf("%d", &numVertices);

    printf("\nNAMES OF THE VERTICES IN THE GRAPH\n");

    for(int i=0; i < numVertices; i++)
    {
    	printf("Enter the name of vertex: ");
    	scanf(" %c",&vNames[i]);
    }

	graph = createGraph(vNames, numVertices);

    for(int i=0; i < numVertices; i++)
    {
    	printf("\nEnter the number of adjacent vertices for vertex %c: ", graph->adjLists[i]->name);
    	scanf(" %d",&numAdj);

		if(numAdj != 0)
    		printf("\nNAMES OF THE ADJACENT NODES OF %c:\n", graph->adjLists[i]->name);

    	for(int j=0; j < numAdj; j++)
    	{
    		printf("Enter the adjacent node name: ");
    		scanf(" %c", &adjName);

    		addEdge(graph, graph->adjLists[i]->name, adjName);
    	}
    }

    printGraph(graph);

    printf("\nEnter the start node name: ");
    scanf(" %c", &startNode->name);

    startNode->next = NULL;

    DFS(graph, startNode);

    BFS(graph, startNode);

    return 0;
}

/*int main()
{
	int choice, n;

	do
	{
		printf("\n\n+-------------------------------+");
		printf("\nMENU for GRAPH TRAVERSAL");
		printf("\n+-------------------------------+");
		printf("\n1. CREATE Adjacency List for graph");
		printf("\n2. Perform DFS");
		printf("\n3. Perform BFS");
		printf("\n4. EXIT");
		printf("\n+-------------------------------+\n");

		printf("\nEnter choice: ");
		scanf(" %d", &choice);

		switch(choice)
		{
			case 1:	printf("\nEnter number of employee records to be inserted: ");
					scanf(" %d", &n);

					break;

			case 2:

					break;

			case 3:

					break;

			case 4:	return 0;

			default: printf("\nINVALID INPUT\nRETRY !\n");
		}

	}while(choice != 4);
}*/