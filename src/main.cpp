/*
 * main.cpp
 */

#include <iostream>

#include "Transfairs.h"

using namespace std;

Transfairs iniciaProblema();

int main()
{

   Transfairs transfers;

   transfers = iniciaProblema();

   transfers.encontraSolucao();

   /*
   cout << "\n============================ Nº Passageiros ==========================\n" << endl;

   cout << transfers.numPassageirosTotal() << endl;
   */

   /*
   cout << "\n================================ PRIM ================================\n" << endl;

   transfers.calculaPrim();

   transfers.printPRIM();
   */

   /*
   cout << "\n=============================== KRUSKAL ==============================\n" << endl;

   transfers.calculaKruskal_R();

   transfers.printKruscal();
   */

   /*
   cout << "\n============================== Dijkstra ==============================\n" << endl;

   transfers.calculaDijkstra();

   transfers.printDijkstra();
   */


   return 0;
}


Transfairs iniciaProblema(){

	Service::resetServID();

	Graph<Service> transf_graph;

	// NÓS - GRAFO
	Service aero("A", 0, Time(), 0, 0); // Aeroporto
	Service serv_b("B", 2, Time(11,0), 60, 60);
	Service serv_c("C", 2, Time(11,0), 75, 60);
	Service serv_d("D", 2, Time(10,30), 75, 60);
	Service serv_e("E", 2, Time(10,0), 75, 60);
	Service serv_f("F", 2, Time(10,0), 60, 60);

	transf_graph.addVertex(aero);
	transf_graph.addVertex(serv_b);
	transf_graph.addVertex(serv_c);
	transf_graph.addVertex(serv_d);
	transf_graph.addVertex(serv_e);
	transf_graph.addVertex(serv_f);

	// ARESTAS - GRAFO
	/* Arestas ligadas ao aeroporto */
	transf_graph.addEdge(aero, serv_b, 60.0);
	transf_graph.addEdge(serv_b, aero, 60.0);

	transf_graph.addEdge(aero, serv_c, 75.0);
	transf_graph.addEdge(serv_c, aero, 75.0);

	transf_graph.addEdge(aero, serv_d, 75.0);
	transf_graph.addEdge(serv_d, aero, 75.0);

	transf_graph.addEdge(aero, serv_e, 75.0);
	transf_graph.addEdge(serv_e, aero, 75.0);

	transf_graph.addEdge(aero, serv_f, 60.0);
	transf_graph.addEdge(serv_f, aero, 60.0);

	/* Arestas ligadas ao servico B */
	transf_graph.addEdge(serv_b, serv_c, 15.0);
	transf_graph.addEdge(serv_c, serv_b, 15.0);

	transf_graph.addEdge(serv_b, serv_d, 30.0);
	transf_graph.addEdge(serv_d, serv_b, 30.0);

	transf_graph.addEdge(serv_b, serv_e, 35.0);
	transf_graph.addEdge(serv_e, serv_b, 35.0);

	transf_graph.addEdge(serv_b, serv_f, 40.0);
	transf_graph.addEdge(serv_f, serv_b, 40.0);

	/* Arestas ligadas ao servico C */
	transf_graph.addEdge(serv_c, serv_d, 15.0);
	transf_graph.addEdge(serv_d, serv_c, 15.0);

	transf_graph.addEdge(serv_c, serv_e, 30.0);
	transf_graph.addEdge(serv_e, serv_c, 30.0);

	transf_graph.addEdge(serv_c, serv_f, 35.0);
	transf_graph.addEdge(serv_f, serv_c, 35.0);

	/* Arestas ligadas ao servico D */
	transf_graph.addEdge(serv_d, serv_e, 15.0);
	transf_graph.addEdge(serv_e, serv_d, 15.0);

	transf_graph.addEdge(serv_d, serv_f, 35.0);
	transf_graph.addEdge(serv_f, serv_d, 35.0);

	/* Arestas ligadas ao E servico */
	transf_graph.addEdge(serv_e, serv_f, 15.0);
	transf_graph.addEdge(serv_f, serv_e, 15.0);

	Transfairs transfair;

	transfair.setGrafoInicial(transf_graph);

	return transfair;

}


