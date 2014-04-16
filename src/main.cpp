/*
 * main.cpp
 */

#include <iostream>

#include "Graph.h"
#include "Service.h"
#include "Time.h"

using namespace std;

int main()
{
    Graph<Service> transf_graph;
    Graph<Service> mst_graph;
    vector<Service> dfs_vec;
    
    // EXEMPLO - ENUNCIADO DO TRABALHO - TEMA 6
    
    // NÓS - GRAFO
    Service aero("A",0,0,0,0); // Aeroporto
    Service serv_b("B",2,10,0,0);
    Service serv_c("C",2,10,0,0);
    Service serv_d("D",2,10,30,0);
    Service serv_e("E",2,11,0,0);
    Service serv_f("F",2,11,0,0);
    
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
    
    
    // EXEMPLO - SLIDES DAS AULAS - ALGORITMO DE KRUSKAL
    
    /*
    transf.addEdge(s1, s2, 2.0);
    transf.addEdge(s1, s3, 4.0);
    transf.addEdge(s1, s4, 1.0);
    
    transf.addEdge(s2, s4, 3.0);
    transf.addEdge(s2, s5, 10.0);
    
    transf.addEdge(s3, s4, 2.0);
    transf.addEdge(s3, s6, 5.0);
    
    transf.addEdge(s4, s5, 7.0);
    transf.addEdge(s4, s6, 8.0);
    transf.addEdge(s4, s7, 4.0);
    
    transf.addEdge(s5, s7, 6.0);
    
    transf.addEdge(s6, s7, 1.0);
    */
    
    // GRAFO - IMPRIME ARESTAS CRIADAS
    cout << endl << "*** DADOS - GRAFO INICIAL - ARESTAS ***" << endl;
    transf_graph.print();
    
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
    
    transf_graph.calculateKruskal_ALT(&mst_graph);
    
    cout << endl << "*** ETAPA 1 - GRAFO Minimum Spanning Tree - ARESTAS ***" << endl;
    mst_graph.print();
    
    /* ======================================================================
     *
     * ETAPA 2 - DETERMINACAO DA ROTA DO VEICULO PELOS SERVICOS - PESQUISA EM PROFUNDIDADE (DEPTH-FIRST-SEARCH)
     *
     * ======================================================================
     */
    
    cout << endl << "*** ETAPA 2 - ROTA DO VEICULO PELOS SERVICOS ***" << endl;
    
    mst_graph.rotateVertexSet(aero); // A rota inicia-se no aerorporto
    
    dfs_vec = mst_graph.dfs();
    
    for(int i=0;i<dfs_vec.size();i++)
    {
        cout << "STOP #" << i+1 << " - " << dfs_vec[i] << endl;
    }
    
    // ATENCAO - com a funcao calcTempViagem utilizar sempre o grafo transf_graph, unico com todas as arestas exitentes 
    cout << endl << "Tempo de viagem total - Inicio e fim no aeroporto (minutos): " << transf_graph.calcTempViagem(dfs_vec, aero) << endl;
    
    
    return 0;
}



