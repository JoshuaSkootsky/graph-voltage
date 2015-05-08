// A C Program to demonstrate adjacency list representation of graphs
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "random64.h"
 
// A structure to represent an adjacency list node
struct AdjListNode
{
    int val;
    struct AdjListNode* next;
};
 
// A structure to represent an adjacency liat
struct AdjList
{
    struct AdjListNode *head;  // pointer to head node of list
};
 
// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{
    int V;
    struct AdjList* array;
};
 
// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int value)
{
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}
 
// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
 
    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
     // Initialize each adjacency list as empty by making head as NULL
    int i;
    for (i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
    }
    return graph;
}
 
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int val)
{
    // Add an edge from src to val.  A new node is added to the adjacency
    // list of src.  The node is added at the begining
    struct AdjListNode* newNode = newAdjListNode(val);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
 
    // Since graph is undirected, add an edge from val to src also
    newNode = newAdjListNode(src);
    newNode->next = graph->array[val].head;
    graph->array[val].head = newNode;
}
 
// A utility function to print the adjacenncy list representation of graph
void pretty_printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; v++)
    {
        struct AdjListNode* nodeSweep = graph->array[v].head; //nodeSweep starts as head
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (nodeSweep)
        {
            printf("-> %d", nodeSweep->val); // val = current node value
            nodeSweep = nodeSweep->next;         // next = next
        }
        printf("\n");
    }
}

// print the adjacency list in a more matrix-like way
void printMatrix (struct Graph* graph) {
    int v;
    for (v = 0; v < graph->V; v++) {
        int count = 0;
        struct AdjListNode *nodeSweep = graph->array[v].head;
        printf("\n Node %d: ", v);
        while (nodeSweep) {
            printf("%d ", nodeSweep->val);
            nodeSweep = nodeSweep->next;
            count++;
        }
    printf(" count = %d ", count);
    }
}

void printEndMatrix(struct Graph *graph) {
    int v;
    for (v = (graph->V - 30); v < graph->V; v++) {
        int count = 0;
        struct AdjListNode *nodeSweep = graph->array[v].head;
                printf("\n Node %d: ", v);
        while (nodeSweep) {
            printf("%d ", nodeSweep->val);
            nodeSweep = nodeSweep->next;
            count++;
        }
    printf(" count = %d ", count);
    }
}

int countNodes(struct Graph *graph) {
    return graph->V;
}

// traverses entire adjacency list in O(n * m) time
int countEdges(struct Graph * graph) {
    int v;
    int total_edges = 0;
    for (v = 0; v < graph->V; v++) {
        struct AdjListNode *nodeSweep = graph->array[v].head;
        while (nodeSweep) {
            total_edges++;
            nodeSweep = nodeSweep->next;
        }
    } 
    return total_edges;
}

// return 0 if graph is empty, else return 1
// the efficiency of this depends on the linked-list formulation graph
int isFull(struct Graph* graph, int node_a, int node_b) {
    struct AdjListNode *nodeSweep = graph->array[node_a].head;
    while (nodeSweep) {
        if(nodeSweep->val == node_b) {
            return 1;
        }
        nodeSweep = nodeSweep->next;
    }
    return 0;
}

// BEGIN NETWORKING
int main()
{
    // create the graph given in above fugure
    clock_t start, finish;
    
    int n;
    printf("How many vertices in the graph?");
    scanf("%d",&n);
    int edges;
    printf("How many edges?");
    scanf("%d", &edges);

    // start timer
    start = clock();

    // make graph with n nodes
    struct Graph* graph = createGraph(n);
   

    int node_a, node_b;
    int i;
    for (i = 0; i < edges; i++) {
        SELECT:
        node_a = floor (n * random64());
        node_b = floor (n * random64());
        if (node_a == node_b) {
            goto SELECT; // reject doubles
        }
        if (isFull(graph, node_a, node_b)) {
            goto SELECT; //reject repeated references
        }
        else {
            // it is okay to add a new node!
            addEdge(graph, node_a, node_b); //an undirected edge
        }
    }
    finish = clock();
    

    // print the adjacency list representation of the above graph
    //pretty_printGraph(graph);
    printEndMatrix(graph);
    
    int size = -1;
    size = countNodes(graph); 
    printf("Made an adjacency list with %d nodes \n", size);

    // count edges    
    int num_edges = -1; // in case of failure
    num_edges = countEdges(graph)/2; // undirected edges
    printf("Adjacency list contains %d unique edges \n", num_edges);
    
    // store time in sec as a double
    double time_create = (double) (finish - start) / CLOCKS_PER_SEC; 
    printf("Time = %f \n", time_create);

    // tear down the graph
    free(graph);    
    
    return 0;
}
