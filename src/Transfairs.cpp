/*
 * Transfairs.cpp
 *
 *  Created on: Apr 17, 2014
 *      Author: vmineiro
 */


#include "Transfairs.h"

Transfairs::Transfairs():aero("A", 0, Time(), 0, 0){
	//aero = new Service("A", 0, Time(), 0, 0); // Aeroporto
}

void Transfairs::setAero(Service & aero){
	this->aero = aero;
}

void Transfairs::setTransfGraph(Graph<Service> & transf_graph){
	this->transf_graph = transf_graph;
}

Service Transfairs::getAero() const {
	return aero;
}


Graph<Service> Transfairs::getTransfGraph() const {
	return transf_graph;
}

void Transfairs::printInitialStatus() const{

	// GRAFO - IMPRIME ARESTAS CRIADAS
	cout << endl << "*** DADOS - GRAFO INICIAL - ARESTAS ***" << endl;
	transf_graph.print();

}


void Transfairs::kruskal_ALT(){

	// Algoritmo de Kruskal - Função alterada para criar um grafo com a Minimum Spanning Tree

	vector<Vertex<Service>*> kruskalSol= transf_graph.calculateKruskal_ALT(&mst_graph);

}

void Transfairs::printMST() const{
	cout << endl << "*** ETAPA 1 - GRAFO Minimum Spanning Tree - ARESTAS ***" << endl;
	mst_graph.print();
}

int Transfairs::calcNumPassageiros(){

	vector<Vertex<Service>* > temp = transf_graph.getVertexSet();

	int totalPassageiros = 0;

	for (int i = 0; i < temp.size(); i++){
		Vertex<Service>* serv = temp[i];
		totalPassageiros += serv->getInfo().getNumPassag();

	}

	return totalPassageiros;

}

void Transfairs::dfsCalc(){

    cout << endl << "*** ETAPA 2 - ROTA DO VEICULO PELOS SERVICOS ***" << endl;

    mst_graph.rotateVertexSet(aero); // A rota inicia-se no aerorporto

    dfs_vec = mst_graph.dfs();

    for(int i=0;i<dfs_vec.size();i++)
    {
        cout << "STOP #" << i+1 << " - " << dfs_vec[i] << "\n";//endl;
    }

}



