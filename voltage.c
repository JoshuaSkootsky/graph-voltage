#include <stdlib.h>

// a single node in the network
struct VoltNode
{
    double voltageNew;
    double voltageOld;
	double conductance;
	double resistance;
};

// structure represents a list of volt nodes
struct VoltList
{
	struct VoltNode *array;
};

struct NodesVoltages
{
	int n;
	struct VoltList *array;
};


// utility function for new volt nodes
struct VoltNode *newVoltNode(double conductance) {
	
	struct VoltNode *newNode = (struct VoltNode *) malloc(sizeof(struct VoltNode));
	newNode->voltageNew = 0.5;
	newNode->voltageOld = 0.5;
	newNode->conductance = conductance;
	newNode->resistance = (1/conductance);
	return newNode;
};

// utility function creates a list of nodes and voltages
struct NodesVoltages *createNodesVoltages(int n) {
	struct NodesVoltages *nodesVoltages = (struct NodesVoltages*) malloc(sizeof(struct NodesVoltages));
	nodesVoltages->n = n;
	
	// create a VoltList array of pointers to VoltNodes within the container struct
	nodesVoltages->array = (struct VoltList*) malloc(n * sizeof(struct VoltList));
	
	//initialize all fields to NULL
	// aha - you don't have voltage nodes here - FIX THIS
	/* FIX */
	int i;
	for (i = 0; i < n; i++) {
		nodesVoltages->array[i].voltageNew = NULL;
		nodesVoltages->array[i].voltageOld = NULL;
		nodesVoltages->array[i].conductance = NULL;
		nodesVoltages->array[i].resistance = NULL;
	}
	return nodesVoltages;
}

// function to set a node
void setNode(struct NodesVoltages* nodesVoltages, double voltageNew, double voltageOld, double conductance) {
	struct VoltNode* voltNode = newVoltNode();
}

/*
Software engineering:
You need to be able to
- allocate memory for a node


- set a node with initial voltage and resistance
void nodeInit(int nodeNumber, double voltage, double conductance) {

}

- assign a node with a new voltage, and make the old voltage equal to the new voltage
void nodeUpdate(int nodeNumber, double newVoltage) {

}

Special methods:
- assign two nodes to be source and a sink

- calculate the new voltage of a node based on the surrounding nodes' values

- cycle through all nodes, assigning new voltages to all, but not the source or the sink.



*/

