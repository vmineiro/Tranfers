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

	Graph<Service> grafoInicial; /* Grafo gerado do Input */

   int capacidadeVan = 10;

   Graph<Service> grafoAlterado;

   vector<Vertex<Service>* > percurso_P;

   vector<Vertex<Service>* > percurso_K;

   vector<Vertex<Service>* > percurso_D;

   vector<Service> percurso_DFS;

   vector<Service> solucao_P;
   vector<Service> solucao_P2;


   Time chegadaMaisTarde;
   Time partidaMaisTarde;


public:
	Transfairs();

   void setGrafoInicial(Graph<Service> grafo);


   // métodos de percurso
   void calculaPrim();
   void printPRIM();

   void calculaKruskal_R();
   void printKruscal();

   void calculaDijkstra();
   void printDijkstra();

   // verificação de restrições
   int numPassageirosTotal();

   //#####################################

   void dfsCalc();
   void dfsCalcPRIM();
   void dfsCalcPRIM_case2();

   vector<Service> my_dfs();

   vector<Service> my_dfs_P();
   vector<Service> my_dfs_P_case2();
	bool my_dfs(Vertex<Service> *v,vector<Service> &res);
   bool my_dfs_case2(Vertex<Service> *v,vector<Service> &res);


	Vertex<Service>* getEarlierService() ;
	Time getEarlierArriveTime() ;

	void calcTempPassagem_DFS();

	bool verificaRestricoes(Vertex<Service> *ori, Vertex<Service> * dest, vector<Service> &res);

   Time calcTempViagem();

   void encontraSolucao();;

   void printSol(vector<Service> solucao) const;

   void atualizaHoraPartida(vector<Service> &res);
   void atualizaHoraPercurso(vector<Service> &res);

   bool verificaChegada(vector<Service> &res);
   bool verificaHorario(vector<Service> &res);

};


#endif /* TRANSFAIRS_H_ */
