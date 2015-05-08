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
void addEdgeAdjList(struct Graph* graph, int node_a, int node_b) {
    // Add node_b to node_a. The node is added at the begining of the linked list
    struct AdjListNode* newNode = newAdjListNode(node_b);
    newNode->next = graph->array[node_a].head;
    graph->array[node_a].head = newNode;
 
    // add node_a to node_b as well (undirected graph)
    newNode = newAdjListNode(node_a);
    newNode->next = graph->array[node_b].head;
    graph->array[node_b].head = newNode;
}
 
// A utility function to print the adjacenncy list representation of graph
void pretty_printGraph(struct Graph* graph) {
    int v;
    for (v = 0; v < graph->V; v++)
    {
        struct AdjListNode* sweeperNode = graph->array[v].head; //sweeperNode starts as head
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (sweeperNode)
        {
            printf("-> %d", sweeperNode->val); // val = current node value
            sweeperNode = sweeperNode->next;         // next = next
        }
        printf("\n");
    }
}

// print the adjacency list in a more matrix-like way
void printMatrix (struct Graph* graph) {
    int v;
    for (v = 0; v < graph->V; v++) {
        int count = 0;
        struct AdjListNode *sweeperNode = graph->array[v].head;
        printf("\nNode %d: ", v);
        while (sweeperNode) {
            printf("%d ", sweeperNode->val);
            sweeperNode = sweeperNode->next;
            count++;
        }
    printf(" count = %d ", count);
    }
}

void printEndMatrix(struct Graph *graph) {
    int v  = 0;
    // print last 30 rows if there are more than 30 nodes
    if (graph->V > 30) {
        v  = graph->V - 30;
    }
    for( ; v < graph->V; v++) {
        int count = 0;
        struct AdjListNode *sweeperNode = graph->array[v].head;
                printf("\n Node %d: ", v);
        while (sweeperNode) {
            printf("%d ", sweeperNode->val);
            sweeperNode = sweeperNode->next;
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
        struct AdjListNode *sweeperNode = graph->array[v].head;
        while (sweeperNode) {
            total_edges++;
            sweeperNode = sweeperNode->next;
        }
    } 
    return total_edges;
}

// return 0 if graph does not contain node_a, node_b pair, else return 1
// the efficiency of this depends on the linked-list formulation graph
int isFull(struct Graph* graph, int node_a, int node_b) {
    struct AdjListNode *sweeperNode = graph->array[node_a].head;
    while (sweeperNode) {
        if(sweeperNode->val == node_b) {
            return 1; // found a pair match
        }
        sweeperNode = sweeperNode->next;
    }
    return 0;
}

void destroyGraph(struct Graph *graph) {
    int i;
    for (i = 0; i < graph->V; i++) {
        free(graph->array[i].head);
    }
    // finally
    free(graph);
}

// make a linked-list representation of a Laplacian matrix
// L(G) = degree matrix - adjacency matrix if 
// L_i,j = deg(v_i) if i=j
//       = -1 if i != j and v_i adjacent to v_j 
//       = 0 otherwise
// represent the zeros as nothing in the adjacency list
// node needs two fields j, and val {-1, deg(v_i}
struct LaplaceNode
{
    int j;
    int val;
    struct LaplaceNode *next;    
};

struct AdjLaplaceList
{
    LaplaceNode *head;
};





// Create an adjacency list representation of a network
// This is justified if the number of edges is several orders of magnitude
// less than the number of nodes squares
// Will scale according to the number of edges
int main()
{
    clock_t start, finish;
    
    int n;
    printf("How many vertices in the graph? \n");
    scanf("%d",&n);
    int edges;
    printf("How many edges? \n");
    scanf("%d", &edges);

    // start timer
    start = clock();

    // make graph with n nodes
    struct Graph* graph = createGraph(n);
   
    int node_a, node_b;
    int i;
    // choose edges number of edges, rejecting parallel edges and loops
    for (i = 0; i < edges; i++) {
        SELECT:
        node_a = floor (n * random64());
        node_b = floor (n * random64());
        if (node_a == node_b) {
            goto SELECT; // reject loops
        }
        if (isFull(graph, node_a, node_b)) {
            goto SELECT; //reject parallel edges
        }
        else {
            // it is okay to add a new node!
            addEdgeAdjList(graph, node_a, node_b); //an undirected edge
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
    destroyGraph(graph);  
    
    return 0;
}
