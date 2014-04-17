/*
 * main.cpp
 */

#include <iostream>


#include "Transfairs.h"

using namespace std;

int main()
{
    Transfairs transfers;// = new Transfairs();
    
    transfers.createGraph();

    transfers.printInitialStatus();

    /* ======================================================================
     *
     * ETAPA 1 - CALCULO DA MINIMUN SPANNING TREE - ALGORITMO DE KRUSKAL
     *
     * ======================================================================
     */
    
    // Algoritmo de Kruskal - Função original
    //transf1.calculateKruskal();
    //cout << endl;
    
    // Algoritmo de Kruskal - Função alterada para criar um grafo com a Minimum Spanning Tree
    
    transfers.kruskal_ALT();
    //transf_graph.calculateKruskal_ALT(&mst_graph);
    
    transfers.printMST();
    
    /* ======================================================================
     *
     * ETAPA 2 - DETERMINACAO DA ROTA DO VEICULO PELOS SERVICOS - PESQUISA EM PROFUNDIDADE (DEPTH-FIRST-SEARCH)
     *
     * ======================================================================
     */
    
    transfers.mstCalc();
    
    // ATENCAO - com a funcao calcTempViagem utilizar sempre o grafo transf_graph, unico com todas as arestas existentes
   // cout << endl << "Tempo de viagem total - Inicio e fim no aeroporto (minutos): " << transf_graph.calcTempViagem(dfs_vec, aero) << endl;
    
    
    return 0;
}



