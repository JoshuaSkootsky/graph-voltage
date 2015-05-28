extern struct VoltNode *newVoltNode(double conductance);

extern struct NodesVoltages* createNodesVoltages(int n);

extern void setNode(struct NodesVoltages* nodesVoltages, double voltageNew, double voltageOld, double conductance);

