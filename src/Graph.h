/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <iostream>
using namespace std;

template <class T> class Edge;
template <class T> class Graph;

const int NOT_VISITED = 0;
const int BEING_VISITED = 1;
const int DONE_VISITED = 2;
const int INT_INFINITY = INT_MAX;

/* ================================================================================================
 * Class Vertex
 * ================================================================================================
 */

template <class T>
class Vertex {
	T info;
	vector<Edge<T>  > adj;
	bool visited;
	bool processing;
	double dist;
	int set;
public:
	Vertex(T in);
	friend class Graph<T>;

	void addEdge(Vertex<T> *dest, double w);
	void addEdge(Vertex<T> *dest, double w, double f);
	bool removeEdgeTo(Vertex<T> *d);

	T getInfo() const;
	void setInfo(T info);

	int getDist() const;
	int getIndegree() const;
	vector<Edge<T> > getAdj() const;
	Vertex<T>* getPath() const;

	bool operator<(const Vertex<T> vertex);

	Vertex* path;

	void updateEdgeFlow(unsigned int index, float f);

	//###################################################

	bool getVisited() const;
	void setVisited(bool condition);

};


template <class T>
struct vertex_greater_than {
	bool operator()(Vertex<T> * a, Vertex<T> * b) const {
		return a->getDist() > b->getDist();
	}
};


template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	typename vector<Edge<T> >::iterator it= adj.begin();
	typename vector<Edge<T> >::iterator ite= adj.end();
	while (it!=ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}

//atualizado pelo exercÌcio 5
template <class T>
Vertex<T>::Vertex(T in): info(in), visited(false), processing(false), dist(0) {
	path = NULL;
}


template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w) {
	Edge<T> edgeD(dest,w);
	edgeD.orig = this;
	adj.push_back(edgeD);
}

template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w, double f)
{
	Edge<T> edgeD(dest, w, f);
	edgeD.orig = this;
	adj.push_back(edgeD);
}


template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

//###################################################

template <class T>
bool Vertex<T>::getVisited() const {
	return visited;
}


template <class T>
void Vertex<T>::setVisited(bool condition) {
	visited = condition;
}

//###################################################

template <class T>
int Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
vector<Edge<T> > Vertex<T>::getAdj() const {
	return this->adj;
}

template <class T>
Vertex<T>* Vertex<T>::getPath() const {
	return this->path;
}


template <class T>
void Vertex<T>::setInfo(T info) {
	this->info = info;
}


template <class T>
void Vertex<T>::updateEdgeFlow(unsigned int index, float f)
{
	if (index >= adj.size())
		return;
	adj[index].flow = f;
}



/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */
template <class T>
class Edge {
	Vertex<T> * dest;
	Vertex<T> * orig;
	double weight;
	double flow;
public:
	Edge(Vertex<T> *d, double w, double f=0);
	double getFlow() const;
	double getWeight() const;
	Vertex<T> *getDest() const;
	bool operator<(const Edge<T> &other) const;

	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w, double f): dest(d), weight(w), flow(f){}

template <class T>
double Edge<T>::getFlow() const {
	return flow;
}

template <class T>
double Edge<T>::getWeight() const {
	return weight;
}

template <class T>
Vertex<T>* Edge<T>::getDest() const {
	return dest;
}

template <class T>
bool Edge<T>::operator<(const Edge<T> &other) const {
	return this->weight < other.weight;
}

template <class T>
struct edge_greater_than {
	bool operator()(Edge<T> a, Edge<T>  b) const {
		return a.getWeight() > b.getWeight();
	}
};



/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	void dfs(Vertex<T> *v, vector<T> &res) const;

	//exercicio 5
	int numCycles;
	void dfsVisit(Vertex<T> *v);
	void dfsVisit();
	void getPathTo(Vertex<T> *origin, list<T> &res);

	//exercicio 6
	int ** W;   //weight
	int ** P;   //path

public:
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w,double f=0);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(Vertex<T> *v) const;
	vector<Vertex<T> * > getVertexSet() const;
	int getNumVertex() const;

	//exercicio 5
	Vertex<T>* getVertex(const T &v) const;
	void resetIndegrees();
	vector<Vertex<T>*> getSources() const;
	int getNumCycles();
	vector<T> topologicalOrder();
	vector<T> getPath(const T &origin, const T &dest);
	void unweightedShortestPath(const T &v);
	bool isDAG();

	//exercicio 6
	void bellmanFordShortestPath(const T &s);
	void dijkstraShortestPath(const T &s);
	void floydWarshallShortestPath();
	int edgeCost(int vOrigIndex, int vDestIndex);
	vector<T> getfloydWarshallPath(const T &origin, const T &dest);
	void getfloydWarshallPathAux(int index1, int index2, vector<T> & res);

	//exercicio 8
	Graph<T> clone();
	vector<Vertex<T>*> calculatePrim();
	vector<Vertex<T>*> myCalculatePrim();
	vector<Vertex<T>*> calculateKruskal();



	/* =======================================================================
	 *
	 * PLANEAMENTO DE TRANSFERS - Funções acrescentadas
	 *
	 * =======================================================================
	 */

	void print() const;
	vector<Vertex<T>*> calculateKruskal_ALT(Graph<T>* mst_graph);
	int rotateVertexSet(const T &v_info);
	int calcTempViagem(vector<T> &vec_viagem, const T &local_partida);

	void resetVisited();

};

//============================================================================

/*
 * Função para imprimir as arestas do grafo
 */
template <class T>
void Graph<T>::print() const
{
	for(int i=0;i<vertexSet.size();i++)
	{
		Vertex<T>* v = vertexSet[i];

		for(int j=0;j<v->adj.size();j++)
		{
			cout << v->adj[j].orig->info << " <-- " << v->adj[j].weight << " --> " << v->adj[j].dest->info << endl;
		}
	}
}


/*
 * Função para imprimir as arestas do grafo
 */
template <class T>
void Graph<T>::resetVisited()
{
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
}
/*
 * Função para colocar na 1a posicao do vertexSet, o vertice com info igual a v_info
 */

template <class T>
int Graph<T>::rotateVertexSet(const T &v_info)
{
	if(vertexSet[0]->info == v_info)
	{
		return 0;
	}

	for(int i=0;i<vertexSet.size();i++)
	{
		rotate(vertexSet.begin(),vertexSet.begin()+1,vertexSet.end());

		if(vertexSet[0]->info == v_info)
		{
			return 0;
		}
	}

	return 1;
}

/*
 * Função para calcular o tempo de viagem total, a iniciar e a terminar no local de partida
 */

template<class T>
int Graph<T>::calcTempViagem(vector<T> &vec_viagem, const T &local_partida)
{
	int temp_viagem = 0;

	for(int i=0;i<vec_viagem.size();i++)
	{
		Vertex<T>* orig = NULL;

		for(int j=0;j<vertexSet.size();j++)
		{
			if(vertexSet[j]->info == vec_viagem[i])
			{
				orig = vertexSet[j];
				break;
			}
		}

		if(i != vec_viagem.size()-1)
		{
			for(int z=0;z<orig->adj.size();z++)
			{
				if(orig->adj[z].dest->info == vec_viagem[i+1])
				{
					temp_viagem = temp_viagem + orig->adj[z].weight;
				}
			}
		}
		else
		{
			for(int z=0;z<orig->adj.size();z++)
			{
				if(orig->adj[z].dest->info == local_partida)
				{
					temp_viagem = temp_viagem + orig->adj[z].weight;
				}
			}
		}


	}

	return temp_viagem;
}



/*
 *
 * Esta função implementa o algoritmo de Prim para encontrar
 * a árvore de expansão mínima a partir do primeiro vértice v do grafo a todos os outros vértices.
 *
 */

template <class T>
vector<Vertex<T>* > Graph<T>::myCalculatePrim()
{
	for(unsigned int i = 0; i < this->vertexSet.size(); i++) {
		this->vertexSet[i]->path = NULL;
		this->vertexSet[i]->dist = INT_INFINITY;
		this->vertexSet[i]->visited = false;
	}

	Vertex<T>* v = this->vertexSet[0];
	v->dist = 0;

	vector< Vertex<T>* > pq;
	pq.push_back(v);

	make_heap(pq.begin(), pq.end(), vertex_greater_than<T>());

	// a kind of Dijkstra modified
	while( !pq.empty() ) {

		v = pq.front();
		pop_heap(pq.begin(), pq.end());
		pq.pop_back();
		if(!v->visited)
		{
			v->visited = true;
			for(unsigned int i = 0; i < v->adj.size(); i++) {

				Vertex<T>* w = v->adj[i].dest;

				if(!w->visited)
				{
					if(v->adj[i].weight < w->dist ) {
						w->dist = v->adj[i].weight;
						w->path = v;
						pq.push_back(w);
					}
				}
			}
		}
		make_heap(pq.begin(), pq.end(), vertex_greater_than<T>());
	}
	return this->vertexSet;
}


//============================================================================

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}
template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
	return vertexSet;
}

template <class T>
int Graph<T>::getNumCycles() {
	numCycles = 0;
	dfsVisit();
	return this->numCycles;
}

/*
 *
 * Esta função verifica se o grafo dirigido é acíclico (Directed Acyclic Graph)
 *
 */

template <class T>
bool Graph<T>::isDAG() {
	return (getNumCycles() == 0);
}

/*
 *
 * Esta função adiciona o nó in ao grafo.
 * Retorna true se o nó foi adicionado com sucesso e false se não é possível inserir esse nó (se já existe um nó igual).
 *
 */

template <class T>
bool Graph<T>::addVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++)
		if ((*it)->info == in) return false;
	Vertex<T> *v1 = new Vertex<T>(in);
	vertexSet.push_back(v1);
	return true;
}

/*
 *
 * Esta função remove o nó in. Retorna true se o nó foi removido com sucesso e false senão (nó não existe).
 * A remoção de um nó implica a remoção de todas as arestas com origem e/ou destino nesse nó.
 *
 */

template <class T>
bool Graph<T>::removeVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++) {
		if ((*it)->info == in) {
			Vertex<T> * v= *it;
			vertexSet.erase(it);
			typename vector<Vertex<T>*>::iterator it1= vertexSet.begin();
			typename vector<Vertex<T>*>::iterator it1e= vertexSet.end();
			for (; it1!=it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}

			typename vector<Edge<T> >::iterator itAdj= v->adj.begin();
			typename vector<Edge<T> >::iterator itAdje= v->adj.end();
			for (; itAdj!=itAdje; itAdj++) {
				itAdj->dest->indegree--;
			}
			delete v;
			return true;
		}
	}
	return false;
}


/*
 *
 * Esta função adiciona ao grafo a aresta com origem no nó sourc, destino no nó dest e peso w.
 * Retorna true se a aresta foi adicionado com sucesso e false se não é possível inserir essa aresta.
 *
 */

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w, double f) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
		{ vS=*it; found++;}
		if ( (*it)->info == dest )
		{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	vS->addEdge(vD,w,f);

	return true;
}


/*
 *
 * Esta função remove a aresta com origem no nó sourc e destino no nó dest.
 * Retorna true se a aresta foi removida com sucesso e false senão (aresta não existe).
 *
 */

template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
		{ vS=*it; found++;}
		if ( (*it)->info == dest )
		{ vD=*it; found++;}
		it ++;
	}
	if (found!=2)
		return false;

	vD->indegree--;

	return vS->removeEdgeTo(vD);
}

/* ================================================================================================
 *
 * DEPTH FIRST SEARCH - UTILIZADO NO TRABALHO
 *
 * ================================================================================================
 *
 * Esta função retorna um vetor contendo os elementos do grafo (conteúdo dos nós)
 * quando sobre este é efectuada uma pesquisa em profundidade.
 *
 */

template <class T>
vector<T> Graph<T>::dfs() const {
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	vector<T> res;
	it=vertexSet.begin();
	for (; it !=ite; it++)
		if ( (*it)->visited==false )
			dfs(*it,res);
	return res;
}

template <class T>
void Graph<T>::dfs(Vertex<T> *v,vector<T> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge<T> >::iterator it= (v->adj).begin();
	typename vector<Edge<T> >::iterator ite= (v->adj).end();
	for (; it !=ite; it++)
		if ( it->dest->visited == false ){
			//cout << "ok ";
			dfs(it->dest, res);
		}
}


/*
 *
 * Esta função retorna um vetor contendo os elementos do grafo (conteúdo dos nós)
 * quando sobre este é efectuada uma pesquisa em largura a partir de v.
 *
 */

template <class T>
vector<T> Graph<T>::bfs(Vertex<T> *v) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
			}
		}
	}
	return res;
}

template <class T>
Vertex<T>* Graph<T>::getVertex(const T &v) const {
	for(unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == v) return vertexSet[i];
	return NULL;
}

/*
 *
 * Atualiza, para todos os vértices do grafo, o valor do membro-dado indegree
 *
 */

template<class T>
void Graph<T>::resetIndegrees() {
	//colocar todos os indegree em 0;
	for(unsigned int i = 0; i < vertexSet.size(); i++) vertexSet[i]->indegree = 0;

	//actualizar os indegree
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		//percorrer o vector de Edges, e actualizar indegree
		for(unsigned int j = 0; j < vertexSet[i]->adj.size(); j++) {
			vertexSet[i]->adj[j].dest->indegree++;
		}
	}
}


/*
 *
 * Esta função retorna um vetor contendo apontadores para os vértices-fonte do grafo.
 *
 */

template<class T>
vector<Vertex<T>*> Graph<T>::getSources() const {
	vector< Vertex<T>* > buffer;
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		if( vertexSet[i]->indegree == 0 ) buffer.push_back( vertexSet[i] );
	}
	return buffer;
}


template <class T>
void Graph<T>::dfsVisit() {
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	it=vertexSet.begin();
	for (; it !=ite; it++)
		if ( (*it)->visited==false )
			dfsVisit(*it);
}

template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v) {
	v->processing = true;
	v->visited = true;
	typename vector<Edge<T> >::iterator it= (v->adj).begin();
	typename vector<Edge<T> >::iterator ite= (v->adj).end();
	for (; it !=ite; it++) {
		if ( it->dest->processing == true) numCycles++;
		if ( it->dest->visited == false ){
			dfsVisit(it->dest);
		}
	}
	v->processing = false;
}


/*
 *
 * Esta função retorna um vetor com a sequência dos elementos do grafo
 * representando os vértices do caminho de origin até dest, inclusivé
 *
 */

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest){

	list<T> buffer;
	Vertex<T>* v = getVertex(dest);

	buffer.push_front(v->info);
	while ( v->path != NULL &&  v->path->info != origin) {
		v = v->path;
		buffer.push_front(v->info);
	}
	if( v->path != NULL )
		buffer.push_front(v->path->info);


	vector<T> res;
	while( !buffer.empty() ) {
		res.push_back( buffer.front() );
		buffer.pop_front();
	}
	return res;
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &origin, const T &dest){

	int originIndex = -1, destinationIndex = -1;

	for(unsigned int i = 0; i < vertexSet.size(); i++)
	{
		if(vertexSet[i]->info == origin)
			originIndex = i;
		if(vertexSet[i]->info == dest)
			destinationIndex = i;

		if(originIndex != -1 && destinationIndex != -1)
			break;
	}


	vector<T> res;

	//se nao foi encontrada solucao possivel, retorna lista vazia
	if(W[originIndex][destinationIndex] == INT_INFINITY)
		return res;

	res.push_back(vertexSet[originIndex]->info);

	//se houver pontos intermedios...
	if(P[originIndex][destinationIndex] != -1)
	{
		int intermedIndex = P[originIndex][destinationIndex];

		getfloydWarshallPathAux(originIndex, intermedIndex, res);

		res.push_back(vertexSet[intermedIndex]->info);

		getfloydWarshallPathAux(intermedIndex,destinationIndex, res);
	}

	res.push_back(vertexSet[destinationIndex]->info);


	return res;
}



template<class T>
void Graph<T>::getfloydWarshallPathAux(int index1, int index2, vector<T> & res)
{
	if(P[index1][index2] != -1)
	{
		getfloydWarshallPathAux(index1, P[index1][index2], res);

		res.push_back(vertexSet[P[index1][index2]]->info);

		getfloydWarshallPathAux(P[index1][index2],index2, res);
	}
}


/*
 *
 * Esta função implementa o algoritmo de Dijkstra para encontrar
 * os caminhos mais curtos a partir do elemento v do grafo (vértice cujo conteúdo é s)
 * a todos os outros vértices, no caso de grafos pesados.
 *
 */

template<class T>
void Graph<T>::dijkstraShortestPath(const T &s) {

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
		vertexSet[i]->processing = false;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;

	vector< Vertex<T>* > pq;
	pq.push_back(v);

	make_heap(pq.begin(), pq.end());


	while( !pq.empty() ) {

		v = pq.front();
		pop_heap(pq.begin(), pq.end());
		pq.pop_back();

		for(unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;

			if(v->dist + v->adj[i].weight < w->dist ) {

				w->dist = v->dist + v->adj[i].weight;
				w->path = v;

				//se j· estiver na lista, apenas a actualiza
				if(!w->processing)
				{
					w->processing = true;
					pq.push_back(w);
				}

				make_heap (pq.begin(),pq.end(),vertex_greater_than<T>());
			}
		}
	}
}

template<class T>
int Graph<T>::edgeCost(int vOrigIndex, int vDestIndex)
{
	if(vertexSet[vOrigIndex] == vertexSet[vDestIndex])
		return 0;

	for(unsigned int i = 0; i < vertexSet[vOrigIndex]->adj.size(); i++)
	{
		if(vertexSet[vOrigIndex]->adj[i].dest == vertexSet[vDestIndex])
			return vertexSet[vOrigIndex]->adj[i].weight;
	}

	return INT_INFINITY;
}


/*
 *
 * Esta função implementa o algoritmo de Floyd-Warshall para encontrar
 * os caminhos mais curtos entre todos os vértices v do grafo, no caso de grafos pesados.
 *
 */

template<class T>
void Graph<T>::floydWarshallShortestPath() {

	W = new int * [vertexSet.size()];
	P = new int * [vertexSet.size()];
	for(unsigned int i = 0; i < vertexSet.size(); i++)
	{
		W[i] = new int[vertexSet.size()];
		P[i] = new int[vertexSet.size()];
		for(unsigned int j = 0; j < vertexSet.size(); j++)
		{
			W[i][j] = edgeCost(i,j);
			P[i][j] = -1;
		}
	}

	for(unsigned int k = 0; k < vertexSet.size(); k++)
		for(unsigned int i = 0; i < vertexSet.size(); i++)
			for(unsigned int j = 0; j < vertexSet.size(); j++)
			{
				//se somarmos qualquer coisa ao valor INT_INFINITY, ocorre overflow, o que resulta num valor negativo, logo nem convÈm considerar essa soma
				if(W[i][k] == INT_INFINITY || W[k][j] == INT_INFINITY)
					continue;

				int val = min ( W[i][j], W[i][k]+W[k][j] );
				if(val != W[i][j])
				{
					W[i][j] = val;
					P[i][j] = k;
				}
			}

}



template <class T>
Graph<T> Graph<T>::clone()
{
	Graph<T> ret;
	for (unsigned int i = 0; i < this->vertexSet.size(); i++)
		ret.addVertex(this->vertexSet[i]->info);

	for (unsigned int i = 0; i < this->vertexSet.size(); i++)
	{
		vector<Edge<T> > edges = this->vertexSet[i]->adj;
		for (unsigned int a = 0; a < edges.size(); a++)
			ret.addEdge(this->vertexSet[i]->info, edges[a].dest->info, edges[a].weight, edges[a].flow);
	}

	return ret;
}


/*
 *
 * Esta função implementa o algoritmo de Prim para encontrar
 * a árvore de expansão mínima a partir do primeiro vértice v do grafo a todos os outros vértices.
 *
 */

template <class T>
vector<Vertex<T>* > Graph<T>::calculatePrim()
{
	for(unsigned int i = 0; i < this->vertexSet.size(); i++) {
		this->vertexSet[i]->path = NULL;
		this->vertexSet[i]->dist = INT_INFINITY;
		this->vertexSet[i]->visited = false;
	}

	Vertex<T>* v = this->vertexSet[0];
	v->dist = 0;

	vector< Vertex<T>* > pq;
	pq.push_back(v);

	make_heap(pq.begin(), pq.end(), vertex_greater_than<T>());

	// a kind of Dijkstra modified
	while( !pq.empty() ) {

		v = pq.front();
		pop_heap(pq.begin(), pq.end());
		pq.pop_back();
		if(!v->visited)
		{
			v->visited = true;
			for(unsigned int i = 0; i < v->adj.size(); i++) {

				Vertex<T>* w = v->adj[i].dest;

				if(!w->visited)
				{
					if(v->adj[i].weight < w->dist ) {
						w->dist = v->adj[i].weight;
						w->path = v;
						pq.push_back(w);
					}
				}
			}
		}
		make_heap(pq.begin(), pq.end(), vertex_greater_than<T>());
	}
	return this->vertexSet;
}

/* ================================================================================================
 * ALGORITMO DE KRUSKAL
 * analisar as arestas por ordem crescente de peso e aceitar as que não provocarem ciclos (ganancioso)
 * ================================================================================================
 *
 * Esta função implementa o algoritmo de Kruskal para encontrar a árvore de expansão mínima no grafo.
 *
 */

template <class T>
vector<Vertex<T>*> Graph<T>::calculateKruskal()
{
	//Initialize the var edges_accepted
	unsigned edges_accepted = 0;
	if (vertexSet.size() == 0)
		return this->vertexSet;

	// Initialize the forest of vertex
	vector<Vertex<T>*> forest;
	for (unsigned int i = 0; i < this->vertexSet.size(); i++)
	{
		Vertex<T>* v = new Vertex<T>(this->vertexSet[i]->info);
		v->set = i;
		forest.push_back(v);
	}

	//Initialize the list of edges
	vector<Edge<T> > allEdges;
	for (unsigned int i = 0; i < this->vertexSet.size(); i++)
	{
		Vertex<T>* v = this->vertexSet[i];
		v->set = i;
		for (unsigned int a = 0; a < v->adj.size(); a++)
			allEdges.push_back(v->adj[a]);
	}

	//Make heap from vector
	make_heap(allEdges.begin(), allEdges.end(), edge_greater_than<T>());

	while (edges_accepted < vertexSet.size()-1)
	{
		sort_heap(allEdges.begin(), allEdges.end());

		Edge<T> minEdge = allEdges[0];		// get edge with minimum weight
		allEdges.erase(allEdges.begin());

		//Get the vertices
		T o = minEdge.orig->info;
		T d = minEdge.dest->info;

		Vertex<T>* origin = NULL;
		Vertex<T>* dest = NULL;

		for (unsigned int i = 0; i < forest.size(); i++)
		{
			if (o == forest[i]->info)
				origin = forest[i];
			if (d == forest[i]->info)
				dest = forest[i];
		}

		if (origin->set != dest->set)
		{
			int minSet = min(origin->set, dest->set);
			int maxSet = max(origin->set, dest->set);
			for (unsigned int k = 0; k < forest.size(); k++) {
				if (forest[k]->set == maxSet)
					forest[k]->set = minSet;
			}
			if (dest->path == NULL)
				dest->path=origin;
			else if (origin->path == NULL)
				origin->path=dest;
			edges_accepted++;
			cout << "Adding edge from vertex " << origin->info << " to vertex " << dest->info << endl;
		}
	}

	return forest;
}

/* ================================================================================================
 *
 * ALGORITMO DE KRUSKAL - ALTERADO para receber um grafo e criar nesse grado a minimum spanning tree
 * 
 * ================================================================================================
 *
 * Esta função implementa o algoritmo de Kruskal para encontrar a árvore de expansão mínima no grafo.
 *
 */

template <class T>
vector<Vertex<T>*> Graph<T>::calculateKruskal_ALT(Graph<T>* mst_graph)
{
	//Initialize the var edges_accepted
	unsigned edges_accepted = 0;
	if (vertexSet.size() == 0)
		return this->vertexSet;

	// Initialize the forest of vertex
	vector<Vertex<T>*> forest;
	for (unsigned int i = 0; i < this->vertexSet.size(); i++)
	{
		Vertex<T>* v = new Vertex<T>(this->vertexSet[i]->info);
		v->set = i;
		forest.push_back(v);
	}

	//Initialize the list of edges
	vector<Edge<T> > allEdges;
	for (unsigned int i = 0; i < this->vertexSet.size(); i++)
	{
		Vertex<T>* v = this->vertexSet[i];
		v->set = i;
		for (unsigned int a = 0; a < v->adj.size(); a++)
			allEdges.push_back(v->adj[a]);
	}

	//Make heap from vector
	make_heap(allEdges.begin(), allEdges.end(), edge_greater_than<T>());

	while (edges_accepted < vertexSet.size()-1)
	{
		sort_heap(allEdges.begin(), allEdges.end());

		Edge<T> minEdge = allEdges[0];		// get edge with minimum weight
		allEdges.erase(allEdges.begin());

		//Get the vertices
		T o = minEdge.orig->info;
		T d = minEdge.dest->info;

		Vertex<T>* origin = NULL;
		Vertex<T>* dest = NULL;

		for (unsigned int i = 0; i < forest.size(); i++)
		{
			if (o == forest[i]->info)
				origin = forest[i];
			if (d == forest[i]->info)
				dest = forest[i];
		}

		if (origin->set != dest->set)
		{
			int minSet = min(origin->set, dest->set);
			int maxSet = max(origin->set, dest->set);
			for (unsigned int k = 0; k < forest.size(); k++) {
				if (forest[k]->set == maxSet)
					forest[k]->set = minSet;
			}
			if (dest->path == NULL)
				dest->path=origin;
			else if (origin->path == NULL)
				origin->path=dest;
			edges_accepted++;

			//cout << "Adding edge from vertex " << origin->info << " to vertex " << dest->info << endl;

			// Minimum Spanning Tree Graph - Creation
			mst_graph->addVertex(origin->info);
			mst_graph->addVertex(dest->info);

			// arestas nos dois sentidos
			mst_graph->addEdge(origin->info,dest->info,minEdge.weight);
			mst_graph->addEdge(dest->info,origin->info,minEdge.weight);
		}
	}

	return forest;
}


#endif /* GRAPH_H_ */
