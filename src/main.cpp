/*
 * main.cpp
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include "Transfairs.h"
#include "graphviewer.h"

using namespace std;

Transfairs iniciaProblema();

vector<Service> servicos;

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
	Service aero("A", 0, Time(23,59), 0, 1439); // Aeroporto
	Service serv_b("B", 10, Time(16,00), 60, 60);
	Service serv_c("C", 10, Time(16,00), 75, 60);
	Service serv_d("D", 10, Time(10,30), 75, 60);
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

vector<vector<string>> csvReader(string filename) {

	vector<vector<string>> vec;
	vector <string> subVec;
	ifstream file(filename);

	while (!file.eof())
	{
		if (file)
		{
			string line;
			if (!getline(file, line)) break;

			istringstream content(line);
			subVec.clear();

			while (content)
			{
				string subContent;
				if (!getline(content, subContent, ',')) break;
				subVec.push_back(subContent);
			}

			vec.push_back(subVec);
		}
		else {
			cout << "File not found.";
			break;
		}
	}

	return vec;
}

//Retorna um vetor de vetores, sendo que cada subvetor apresenta a informacao relativa a cada servico
vector<vector<string>> csvGraphReader(string filename) {

	return csvReader("Graph.csv");
}

vector<vector<string>> csvDistancesReader(string filename) {

	return csvReader("Distances.csv");
}

int stringToInt(string str) {
	int n;
	istringstream(str) >> n;
	return n;
}

Service getService(vector<vector<string>> graphs, int i) {

	//Nome do servico
	string serviceName = graphs[i][0];

	//Num de passageiros
	string str_numPassag = graphs[i][1];
	int numPassag = stringToInt(str_numPassag);

	//Tempo de chegada ao aeroporto
	string str_hChegadaAero = graphs[i][2];
	string str_mChegadaAero = graphs[i][3];
	int hChegadaAero = stringToInt(str_hChegadaAero);
	int mChegadaAero = stringToInt(str_mChegadaAero);

	Time hMaxChegada;
	hMaxChegada.setTime(hChegadaAero, mChegadaAero);

	//Tempo de overhead
	string str_minOverhead = graphs[i][5];
	int minOverhead = stringToInt(str_minOverhead);

	//Tempo de chegada ao aeroporto
	string str_chegadaAero = graphs[i][4];
	int chegadaAero = stringToInt(str_chegadaAero);

	//Definicao do servico com os parametros correspondentes
	Service temp = Service(serviceName, numPassag, hMaxChegada, chegadaAero, minOverhead);

	return temp;
}

Graph<Service> csvGraphCreator(string filename) {

	vector<vector<string>> graphs = csvGraphReader(filename);

	Graph<Service> G = Graph<Service>();

	for (unsigned int i = 0; i < graphs.size(); i++) {

		Service S = getService(graphs, i);

		if (graphs[i][0] == S.getNomServ) {
			servicos.push_back(S);
			G.addVertex(S);
		}

		if (i != 0) {
			Service lastS = servicos[servicos.size() - 2];
			G.addEdge(lastS, S, 50);
		}
	}

	return G;
}

void drawGraph(Graph<Service> G) {

	//GraphViewer *gv = new GraphViewer(600, 600, true);
	//gv->createWindow(600, 600);

	//gv->defineVertexColor("blue");
	//gv->defineEdgeColor("black");

	int edgeID = 0;

	vector<Vertex<Service> *> vertexSet = G.getVertexSet();

	for (unsigned int i = 0; i < servicos.size(); i++) {

		Service temp = servicos[i];
		string nomeServico = temp.getNomServ;
		//gv->addNode(i);
		//gv->setVertexLabel(i, nomeServico);

		if (i != 0) {
			//gv->addEdge(edgeID, i - 1, i, EdgeType::UNDIRECTED);
			edgeID++;
		}
	}
}
