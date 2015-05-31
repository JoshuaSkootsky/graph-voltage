// A C Program to demonstrate adjacency list representation of graphs
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "random64.h"
 
 
//////
// Voltage List
/////
 
// a single node in the network
struct VoltNode
{
    double voltageNew;
    double voltageOld;
	double conductance;
};

// structure represents a list of volt nodes
struct VoltList
{
	struct VoltNode *head; // pointer to the head
};

struct NodesVoltages
{
	int n;
	struct VoltList *array;
};


// utility function for new volt nodes
// initializes to default value
struct VoltNode* newVoltNode(double initVoltage, double conductance) {
	struct VoltNode *newNode = (struct VoltNode *) malloc(sizeof(struct VoltNode));
	newNode->voltageNew = initVoltage;
	newNode->voltageOld = initVoltage;
	newNode->conductance = conductance;
	return newNode;
};

// utility function creates a list of nodes and voltages
struct NodesVoltages* createNodesVoltages(int n) {
	struct NodesVoltages *nodesVoltages = (struct NodesVoltages*) malloc(sizeof(struct NodesVoltages));
	nodesVoltages->n = n;
	
	// create a VoltList array of pointers to VoltNodes within the container struct
	nodesVoltages->array = (struct VoltList*) malloc(n * sizeof(struct VoltList));
	
	//initialize all fields to NULL
	int i;
	for (i = 0; i < nodesVoltages->n; i++) {
		nodesVoltages->array[i].head = NULL;
	}
	return nodesVoltages;
}

// function to initialize a node
void initNode(struct NodesVoltages* nodesVoltages, int nodeNum, double voltage, double conductance) {
	struct VoltNode* voltNode = newVoltNode(voltage, conductance);
	// place (pointer to) new node in the array of voltage nodes
	nodesVoltages->array[nodeNum].head = voltNode;
}

void initAllNodes(struct NodesVoltages* nodesVoltages, double voltage, double conductance) {
	int i;
	for (i = 0; i< nodesVoltages->n; i++ ) {
		initNode(nodesVoltages, i, voltage, conductance);
	}
}

//////
// Adjacency List
/////
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
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
 
    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
     // Initialize each adjacency list as empty by making head as NULL
    int i;
    for (i = 0; i < V; i++) {
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
 
    // add node_a to node_b as well, since this an undirected graph
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



///
/// Voltage list and Adjacency List interface
///
// function to calculate newVoltage for a node
void setNewVoltage(struct Graph* graph, struct NodesVoltages* nodesVoltages, int nodeNum) {
    // add own value to the new voltage sum
	double sum = nodesVoltages->array[nodeNum].head->voltageOld; 
	
    int count = 1; // start count with 1
	
	// access adjacency list at nodeNum to get neighbors
	struct AdjListNode *sweeperNode = graph->array[nodeNum].head;
    while (sweeperNode) {
		int neighborNum = sweeperNode->val;
    	sweeperNode = sweeperNode->next;	
		// use neighbor as the number of the node, access nodesVoltages with it
		double neighborVoltage = nodesVoltages->array[neighborNum].head->voltageOld;
		count++;
		sum += neighborVoltage;
    }
	// set new voltage using nodeNum
	double average = (double) sum/count;
	nodesVoltages->array[nodeNum].head->voltageNew = average;
}

void calculateAllNewVoltages(struct Graph* graph, struct NodesVoltages* nodesVoltages) {
	int i;
	for (i = 0; i< graph->V; i++) {
		setNewVoltage(graph, nodesVoltages, i);
	}
}

//function to update a node
void updateNodeOldVoltage(struct NodesVoltages* nodesVoltages, int nodeNum) {
	nodesVoltages->array[nodeNum].head->voltageOld = nodesVoltages->array[nodeNum].head->voltageNew;
}

void globalNodeUpdate(struct NodesVoltages* nodesVoltages) {
	int i;
	for (i = 0; i< nodesVoltages->n; i++) {
		updateNodeOldVoltage(nodesVoltages, i);
	}
}

void printVoltages(struct NodesVoltages* nodesVoltages) {
	int nodeNum = 0;
	if (nodesVoltages->n > 30) {
		nodeNum = nodesVoltages->n - 30;
	}
	for ( ; nodeNum < nodesVoltages->n; nodeNum++) {
		double val = nodesVoltages->array[nodeNum].head->voltageOld;
		printf("\nNode %d: Voltage %lf", nodeNum, val);
	}
}

void writeVoltages(struct NodesVoltages* nodesVoltages) {
    int nodeNum = 0;

    FILE* ff;
    char fname[100];
    
    for (nodeNum = 0; nodeNum < nodesVoltages->n; nodeNum++) {
        double val = nodesVoltages->array[nodeNum].head->voltageOld;
        // write to file
        scanf("%s", fname);
        ff = fopen(fname,"w+"); // ff is a pointer
        if(!ff) {
            // 0 is false, so !ff will execute if ff is equal to zero
            printf("\n Failed to write to file \n");
            exit(1); // exit with error
        }
        fprintf(ff,"%lf\n", val);
    }
    printf("\nwritten to file: %s \n", fname);
}
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
    int seed;
    printf("Random seed integer \n");
    scanf("%d", &seed);
    seed_random64(seed);

    // start timer
    start = clock();
    // make graph with n nodes
    struct Graph* graph = createGraph(n);
   
    // fill the graph with edges between nodes
    int node_a, node_b;
    int edge_count = 0;
    while(edge_count < edges) {
        node_a = floor (n * random64()); // make new nodes in the range of nodes
        node_b = floor (n * random64());
        // reject parallel edges (more than one edge between two nodes)
        //  and loops (edges from a node to itself)
        if (!isFull(graph, node_a, node_b) && node_a != node_b ) {
            addEdgeAdjList(graph, node_a, node_b);
            edge_count++;
            }
        // else repeat while loop, since edge_count is not incremented
    }
    
    finish = clock();
    
    // print the adjacency list representation of the above graph
    printEndMatrix(graph);
    
    // count nodes
    int size = 0;
    size = countNodes(graph); 
    printf("Made an adjacency list with %d nodes \n", size);

    // count edges    
    int num_edges = -1; // in case of failure
    num_edges = countEdges(graph)/2; // undirected edges
    printf("Adjacency list contains %d unique edges \n", num_edges);
    
    // print out time
    double time_create = (double) (finish - start) / CLOCKS_PER_SEC; 
    printf("Time = %f \n", time_create);
	
	
	////
	/// Do Voltage calculations
	///
	
	// initialize all nodes - n is the number of verticies
	struct NodesVoltages* nodesVoltages = createNodesVoltages(n);	
    initAllNodes(nodesVoltages, 0.5, 1);
    
    //
    // Use graph adjacency list and voltage list together
    //
    
    // arbitrary sources and sinks written in for testing purposes
    int sink = 3;
    int source = 8;
    nodesVoltages->array[source].head->voltageOld = 1;
    nodesVoltages->array[sink].head->voltageOld = 0;
	
	// start timer
	start = clock();
	
    // iterate a certain number of times - 100 chosen for testing purposes
    int i;
	
	for (i = 0; i < 10000; i++) {
        // calculate using old values
        calculateAllNewVoltages(graph, nodesVoltages);
        // assign all members of voltage list their new values to old values
        globalNodeUpdate(nodesVoltages);
        // before the loop, assign the sink to 0 again and the source to 1
        nodesVoltages->array[source].head->voltageOld = 1;
        nodesVoltages->array[sink].head->voltageOld = 0; 
    }
	
	
	// end timer
	finish = clock();
	time_create = (double) (finish - start) / CLOCKS_PER_SEC; 
	
	printVoltages(nodesVoltages);
    writeVoltages(nodesVoltages);	
    printf("Time = %f for %d iterations\n", time_create, i);
    // tear down the graph
    destroyGraph(graph);  
    
    return 0;
}
