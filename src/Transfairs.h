/*
 * Transfairs.h
 *
 *  Created on: Apr 17, 2014
 *      Author: vmineiro
 */

#ifndef TRANSFAIRS_H_
#define TRANSFAIRS_H_

#include "Service.h"
#include "Graph.h"


class Transfairs{

	Service aero;
	Graph<Service> transf_graph; /* Grafo gerado do Input */
	Graph<Service> mst_graph;
	vector<Service> dfs_vec;

	vector<Service> bestPath;

public:


	Transfairs();

	Service getAero() const;
	Graph<Service> getTransfGraph() const;

	void setAero(Service& aero);
	void setTransfGraph(Graph<Service>& transf_graph);

	void printInitialStatus() const;
	void printMST() const;
	void printDFS() const;

	void kruskal_ALT();
	void dfsCalc();

	int calcNumPassageiros();

	Vertex<Service>* getEarlierService() const;
	Vertex<Service>* getEarlierMaxArrive() const;

	void calcTempPassagem();

};


#endif /* TRANSFAIRS_H_ */
