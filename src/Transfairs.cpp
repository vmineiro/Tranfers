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

Vertex<Service>* Transfairs::getEarlierService() const {

	Vertex<Service>* temp;
	int numServices = transf_graph.getVertexSet().size();

	temp = transf_graph.getVertexSet()[1];

	for (int i = 2; i < numServices; i++){
		Vertex<Service>* aux = transf_graph.getVertexSet()[i];
		if (aux->getInfo().getHminRecolha() < temp->getInfo().getHminRecolha()){
			temp = aux;
		}
	}

	return temp;

}

Vertex<Service>* Transfairs::getEarlierMaxArrive() const {

	Vertex<Service>* temp;
	int numServices = transf_graph.getVertexSet().size();

	temp = transf_graph.getVertexSet()[1];

	for (int i = 2; i < numServices; i++){
		Vertex<Service>* aux = transf_graph.getVertexSet()[i];
		if (aux->getInfo().getHmaxChegada() < temp->getInfo().getHmaxChegada()){
			temp = aux;
		}
	}

	return temp;

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
    dfs_vec.push_back(aero);

    for(int i=0;i<dfs_vec.size();i++)
    {
        cout << "STOP #" << i+1 << " - " << dfs_vec[i] << "\n";//endl;
    }

}

void Transfairs::calcTempPassagem(){

	vector<Service> temp = dfs_vec;

	Time horaChegada = getEarlierMaxArrive()->getInfo().getHmaxChegada();

	int nServ = temp.size();

	Service oriTemp = temp[nServ];
	oriTemp.setHPassagem(horaChegada);
	temp[nServ] = oriTemp;

	for (; nServ >= 0; nServ--){
		Service oriTemp = temp[nServ-1];
		Service destTemp = temp[nServ];

		int duracao = transf_graph.edgeCost(oriTemp.getServId()-1,destTemp.getServId()-1);

		Time timeTravel(duracao/60,duracao%60);

		Time horaPassagem = destTemp.getHPassagem()-timeTravel;

		oriTemp.setHPassagem(horaPassagem);
		temp[nServ-1] = oriTemp;

	}
	dfs_vec = temp;
}

void Transfairs::printDFS() const{

	vector<Service> temp = dfs_vec;

	for (int i = 0; i < dfs_vec.size(); i++){
		Service serv = temp[i];
		cout << serv << " hora passagem: " << serv.getHPassagem() << endl;
	}

}



