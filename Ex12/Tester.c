#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef int bool;
#define true 1
#define false 0

struct AdjListNode
{
	int dest;
	int weight;
	struct AdjListNode* next;
};

struct AdjList
{
	struct AdjListNode *head;
};

struct Graph
{
	int V;
	struct AdjList* array;
};

struct AdjListNode* newAdjListNode(int dest, int weight)
{
	struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
	newNode->dest = dest;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
}

struct Graph* createGraph(int V)
{
	struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
	graph->V = V;

	graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));

	for (int i = 0; i < V; ++i)
		graph->array[i].head = NULL;

	return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight)
{
	// Add an edge from src to dest. The node is added at the beginning
	struct AdjListNode* newNode = newAdjListNode(dest, weight);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	/* Since graph is undirected, add an edge from dest to src also
	newNode = newAdjListNode(src, weight);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;*/
}

struct MinHeapNode
{
	int v;
	int dist;
};

typedef struct MinHeapNode MinHeapNode;

struct MinHeap
{
	int size;
	int capacity;
	int *pos;
	struct MinHeapNode **array;
};

struct MinHeapNode* newMinHeapNode(int v, int dist)
{
	struct MinHeapNode* minHeapNode =
		(struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
	minHeapNode->v = v;
	minHeapNode->dist = dist;
	return minHeapNode;
}

typedef struct MinHeap MinHeap;

struct MinHeap* createMinHeap(int capacity)
{
	struct MinHeap* minHeap =
		(struct MinHeap*) malloc(sizeof(struct MinHeap));
	minHeap->pos = (int *)malloc(capacity * sizeof(int));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array =
		(struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

//Insert into minHeap
void minHeapify(struct MinHeap* minHeap, int idx)
{
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;

	if (left < minHeap->size &&
		minHeap->array[left]->dist < minHeap->array[smallest]->dist )
	smallest = left;

	if (right < minHeap->size &&
		minHeap->array[right]->dist < minHeap->array[smallest]->dist )
	smallest = right;

	if (smallest != idx)
	{
		MinHeapNode *smallestNode = minHeap->array[smallest];
		MinHeapNode *idxNode = minHeap->array[idx];

		minHeap->pos[smallestNode->v] = idx;
		minHeap->pos[idxNode->v] = smallest;

		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

		minHeapify(minHeap, smallest);
	}
}

int isEmpty(struct MinHeap* minHeap)
{
	return minHeap->size == 0;
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
	if (isEmpty(minHeap))
		return NULL;

	struct MinHeapNode* root = minHeap->array[0];

	struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
	minHeap->array[0] = lastNode;

	minHeap->pos[root->v] = minHeap->size-1;
	minHeap->pos[lastNode->v] = 0;

	--minHeap->size;
	minHeapify(minHeap, 0);

	return root;
}

// Function to decreasy dist value of a given vertex v.
void decreaseKey(struct MinHeap* minHeap, int v, int dist)
{
	// Get the index of v in heap array
	int i = minHeap->pos[v];

	// Get the node and update its dist value
	minHeap->array[i]->dist = dist;

	// Travel up while the complete tree is not hepified.
	// This is a O(Logn) loop
	while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
	{
		// Swap this node with its parent
		minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
		minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
		swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

		// move to parent index
		i = (i - 1) / 2;
	}
}

bool isInMinHeap(struct MinHeap *minHeap, int v)
{
if (minHeap->pos[v] < minHeap->size)
	return true;
return false;
}

void printArr(int dist[], int n)
{
	printf("\nVERTEX\t\tDISTANCE\n");
	for (int i = 0; i < n; ++i)
		printf("%d \t\t %d\n", i+1, dist[i]);
}

void dijkstra(struct Graph* graph, int src)
{
	int V = graph->V;
	int dist[V];

	struct MinHeap* minHeap = createMinHeap(V);

	for (int v = 0; v < V; ++v)
	{
		dist[v] = INT_MAX;
		minHeap->array[v] = newMinHeapNode(v, dist[v]);
		minHeap->pos[v] = v;
	}

	minHeap->array[src] = newMinHeapNode(src, dist[src]);
	minHeap->pos[src] = src;
	dist[src] = 0;
	decreaseKey(minHeap, src, dist[src]);

	minHeap->size = V;

	while (!isEmpty(minHeap))
	{
		// Extract the vertex with minimum distance value
		struct MinHeapNode* minHeapNode = extractMin(minHeap);
		int u = minHeapNode->v; // Store the extracted vertex number

		// Traverse through all adjacent vertices of u (the extracted
		// vertex) and update their distance values
		struct AdjListNode* pCrawl = graph->array[u].head;
		while (pCrawl != NULL)
		{
			int v = pCrawl->dest;

			// If shortest distance to v is not finalized yet, and distance to v
			// through u is less than its previously calculated distance
			if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX &&
										pCrawl->weight + dist[u] < dist[v])
			{
				dist[v] = dist[u] + pCrawl->weight;

				// update distance value in min heap also
				decreaseKey(minHeap, v, dist[v]);
			}
			pCrawl = pCrawl->next;
		}
	}

	// print the calculated shortest distances
	printArr(dist, V);
}

int main()
{
	// creating the graphs
	int V = 7;
	struct Graph* graph1 = createGraph(V);

	printf("SHORTEST DISTANCE FROM SOURCE BY DIJKSTRA'S ALGRITHM\n");

	printf("\nGRAPH 1\n");

	addEdge(graph1, 0, 1, 2);
	addEdge(graph1, 0, 3, 1);
	addEdge(graph1, 1, 3, 3);
	addEdge(graph1, 1, 4, 10);
	addEdge(graph1, 2, 0, 4);
	addEdge(graph1, 3, 2, 2);
	addEdge(graph1, 3, 4, 2);
	addEdge(graph1, 3, 5, 8);
	addEdge(graph1, 3, 6, 4);
	addEdge(graph1, 4, 6, 6);
	addEdge(graph1, 6, 5, 1);

	dijkstra(graph1, 0);

	V = 6;

	struct Graph* graph2 = createGraph(V);

	printf("\nGRAPH 2\n");

	addEdge(graph2, 0, 1, 5);
	addEdge(graph2, 0, 3, 6);
	addEdge(graph2, 0, 4, 10);
	addEdge(graph2, 1, 2, 1);
	addEdge(graph2, 1, 4, 2);
	addEdge(graph2, 1, 5, 7);
	addEdge(graph2, 2, 1, 1);
	addEdge(graph2, 2, 5, 8);
	addEdge(graph2, 3, 0, 6);
	addEdge(graph2, 3, 4, 3);
	addEdge(graph2, 4, 0, 10);
	addEdge(graph2, 4, 1, 2);
	addEdge(graph2, 4, 5, 4);
	addEdge(graph2, 5, 1, 7);
	addEdge(graph2, 5, 2, 8);
	addEdge(graph2, 5, 4, 4);

	dijkstra(graph2, 0);

	return 0;
}
