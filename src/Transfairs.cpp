#include "Transfairs.h"

Transfairs::Transfairs(){};


void Transfairs::setGrafoInicial(Graph<Service> grafo)
{
   this->grafoInicial = grafo;
}


//###############################################################################################################################

void Transfairs::calculaPrim() {

   Graph<Service> grafoTemp = grafoInicial.clone();

   percurso_P = grafoTemp.myCalculatePrim();

}

void Transfairs::printPRIM(){
   for (int i = 0; i < percurso_P.size(); i++){
      cout << percurso_P[i]->getInfo() << " dist: " << percurso_P[i]->getDist() << " path: " << percurso_P[i]->getPath() << endl;
   }
}


//###############################################################################################################################

void Transfairs::calculaKruskal_R() {

   Graph<Service> grafoTemp  = grafoInicial.clone();

   percurso_K = grafoTemp.calculateKruskal_ALT(&grafoAlterado);

   grafoAlterado.rotateVertexSet(grafoInicial.getVertexSet()[0]->getInfo());

}

void Transfairs::printKruscal(){
   for (int i = 0; i < percurso_K.size(); i++){
      cout << percurso_K[i]->getInfo() << " dist: " << percurso_K[i]->getDist() << " path: " << percurso_K[i]->getPath() << endl;
   }
}


//###############################################################################################################################

void Transfairs::calculaDijkstra() {

   Graph<Service> grafoTemp = grafoInicial.clone();

   grafoTemp.dijkstraShortestPath(grafoInicial.getVertexSet()[0]->getInfo());

   grafoTemp.print();
}

void Transfairs::printDijkstra(){
   for (int i = 0; i < percurso_D.size(); i++){
      cout << percurso_D[i]->getInfo() << " dist: " << percurso_D[i]->getDist() << " path: " << percurso_D[i]->getPath() << endl;
   }
}


//###############################################################################################################################

size_t Transfairs::numPassageirosTotal(){

   vector<Vertex<Service>* > temp = grafoInicial.getVertexSet();

   size_t nServ = temp.size();

   int totalPassag = 0;

   for (int i = 0 ; i < nServ; i++){
      totalPassag += temp[i]->getInfo().getNumPassag();
   }

   return totalPassag;
}

size_t Transfairs::numServices(){

   return grafoInicial.getVertexSet().size()-1;
}

//###############################################################################################################################
//###############################################################################################################################
//###############################################################################################################################


void Transfairs::printSol(vector<Service> solucao) const{


	for (int i = 0; i < solucao.size(); i++){
		Service serv = solucao[i];
		cout << serv << " - hora passagem: " << serv.getHPassagem() << " - hora min: " << serv.getHminRecolha()<< " - hora max: " << serv.getHmaxRecolha() << endl;
	}

}


void Transfairs::dfsCalc(){

   Graph<Service> grafoTemp = grafoAlterado.clone();

   percurso_DFS = grafoAlterado.dfs();

	percurso_DFS.push_back(grafoInicial.getVertexSet()[0]->getInfo());

   size_t nAux = percurso_DFS.size();

   int ultimaViagem = grafoInicial.edgeCost(percurso_DFS[nAux-2].getServId()-1, percurso_DFS[nAux-1].getServId()-1);

   Time ultimoPercurso(ultimaViagem/60,ultimaViagem%60);

   percurso_DFS[nAux-1].setHPassagem(percurso_DFS[nAux-2].getHPassagem()+ultimoPercurso);

}



void Transfairs::dfsCalcPRIM(){

   solucao_P = my_dfs_P();

	solucao_P.push_back(grafoInicial.getVertexSet()[0]->getInfo());

   size_t nAux = solucao_P.size();

   int ultimaViagem = grafoInicial.edgeCost(solucao_P[nAux-2].getServId()-1, solucao_P[nAux-1].getServId()-1);

   Time ultimoPercurso(ultimaViagem/60,ultimaViagem%60);

   solucao_P[nAux-1].setHPassagem(solucao_P[nAux-2].getHPassagem()+ultimoPercurso);

}


void Transfairs::calcTempPassagem_DFS(){

	vector<Service> temp = percurso_DFS;

	Time horaChegada = getEarlierArriveTime();

	size_t nServ = temp.size() - 1;

	Service oriTemp = temp[nServ];
	oriTemp.setHPassagem(horaChegada);
	temp[nServ] = oriTemp;

	for (; nServ > 0; nServ--){
		Service oriTemp = temp[nServ-1];
		Service destTemp = temp[nServ];

		int duracao = grafoInicial.edgeCost(oriTemp.getServId()-1,destTemp.getServId()-1);

		Time timeTravel(duracao/60,duracao%60);

		Time horaPassagem = destTemp.getHPassagem()-timeTravel;

		oriTemp.setHPassagem(horaPassagem);
		temp[nServ-1] = oriTemp;

	}
	percurso_DFS = temp;

}


vector<Service> Transfairs::my_dfs() {

   Graph<Service> grafoTemp = grafoAlterado.clone();

   grafoTemp.resetVisited();

	vector<Vertex<Service>*> mst_vec = grafoTemp.getVertexSet();

	vector<Vertex<Service>*>::iterator it= mst_vec.begin();
	vector<Vertex<Service>*>::iterator ite= mst_vec.end();

	for (; it !=ite; it++)
		(*it)->setVisited(false);

	vector<Service> res;
	it=mst_vec.begin();

	for (; it !=ite; it++)
		if ( (*it)->getVisited()==false ){
			my_dfs(*it,res);
		}

   size_t resSize = res.size();

   if (resSize != 1){
      int viagemAnterior = grafoInicial.edgeCost(res[resSize-2].getServId()-1, res[resSize-1].getServId()-1);

      Time tempoAnterior(viagemAnterior/60,viagemAnterior%60);

      Time paragemOri = res[resSize-2].getHPassagem() + tempoAnterior;

      res[resSize-1].setHPassagem(paragemOri);
   }


	return res;
}


vector<Service> Transfairs::my_dfs_P() {

   Graph<Service> grafoTemp = grafoInicial.clone();

   grafoTemp.resetVisited();

	vector<Vertex<Service>*> mst_vec = grafoTemp.getVertexSet();

	vector<Vertex<Service>*>::iterator it= mst_vec.begin();
	vector<Vertex<Service>*>::iterator ite= mst_vec.end();

	for (; it !=ite; it++)
		(*it)->setVisited(false);

	vector<Service> res;
	it=mst_vec.begin();

   (*it)->setVisited(true);
   res.push_back((*it)->getInfo());
   it++;

   for (; it !=ite; it++)
      if ( (*it)->getVisited()==false ){
         my_dfs(*it,res);
		}

   size_t resSize = res.size()-1;

   if (resSize != 0){
      int viagemAnterior = grafoInicial.edgeCost(res[resSize-1].getServId()-1, res[resSize].getServId()-1);

      Time tempoAnterior(viagemAnterior/60,viagemAnterior%60);

      Time paragemOri = res[resSize-1].getHPassagem() + tempoAnterior;

      res[resSize-0].setHPassagem(paragemOri);
   }

	return res;
}

bool Transfairs::my_dfs(Vertex<Service> *v,vector<Service> &res) {

   v->setVisited(true);

	res.push_back(v->getInfo());

   bool validPoint = false;

   if (res.size() == 2){

      atualizaHoraPartida(res);

      if (res[0].getHPassagem() > partidaMaisTarde) {

         v->setVisited(false);
         res.pop_back();
         return false;

      }

      for (int i = 0 ; i < (v->getAdj()).size(); i++){
         if ( (v->getAdj())[i].getDest()->getVisited() == false ){
            validPoint = my_dfs((v->getAdj())[i].getDest(), res);
         }
      }

      //vector<Edge<Service> >::iterator it= (v->getAdj()).begin();
      //vector<Edge<Service> >::iterator ite= (v->getAdj()).end();

      //for (; it !=ite; it++){
      //  if ( it->getDest()->getVisited() == false ){
      //    validPoint = my_dfs(it->getDest(), res);
      // }
      //}

   } else {

      atualizaHoraPercurso(res);

      if (!verificaHorario(res)){

         v->setVisited(false);
         res.pop_back();
         return false;

      }

      for (int i = 0 ; i < (v->getAdj()).size(); i++){
         if ( (v->getAdj())[i].getDest()->getVisited() == false ){
            validPoint = my_dfs((v->getAdj())[i].getDest(), res);
         }
      }

      //vector<Edge<Service> >::iterator it= (v->getAdj()).begin();
      //vector<Edge<Service> >::iterator ite= (v->getAdj()).end();

      //for (; it !=ite; it++){
      // if ( it->getDest()->getVisited() == false ){
      //    validPoint = my_dfs(it->getDest(), res);
      // }
      //}

   }

   if (res.size() == grafoInicial.getVertexSet().size()) {
      validPoint = verificaChegada(res);
   }

   if (!validPoint){
      v->setVisited(false);
      res.pop_back();
   }
   return validPoint;
}

//##################################################################################################################
//##################################################################################################################

void Transfairs::dfsCalcPRIM_case2(){

   solucao_P2 = my_dfs_P_case2();

	solucao_P2.push_back(grafoInicial.getVertexSet()[0]->getInfo());

   size_t nAux = solucao_P.size();

   int ultimaViagem = grafoInicial.edgeCost(solucao_P2[nAux-2].getServId()-1, solucao_P2[nAux-1].getServId()-1);

   Time ultimoPercurso(ultimaViagem/60,ultimaViagem%60);

   solucao_P2[nAux-1].setHPassagem(solucao_P2[nAux-2].getHPassagem()+ultimoPercurso);
}

vector<Service> Transfairs::my_dfs_P_case2() {

   Graph<Service> grafoTemp = grafoInicial.clone();

   grafoTemp.resetVisited();

   bool regresso = false;

	vector<Vertex<Service>*> mst_vec = grafoTemp.getVertexSet();

	vector<Vertex<Service>*>::iterator it= mst_vec.begin();
	vector<Vertex<Service>*>::iterator ite= mst_vec.end();

	for (; it !=ite; it++)
		(*it)->setVisited(false);


	vector<Service> res;
	it=mst_vec.begin();

   (*it)->setVisited(true);
   res.push_back((*it)->getInfo());
   it++;

   for (; it !=ite; it++)
      if ( (*it)->getVisited()==false ){
         my_dfs_case2(*it,res, &regresso);
         if (regresso) {
            res.push_back(mst_vec[0]->getInfo());
            atualizaHoraPercurso(res);
            regresso = false;
         }
		}

   size_t resSize = res.size();

   if (resSize != 1){
      int viagemAnterior = grafoInicial.edgeCost(res[resSize-2].getServId()-1, res[resSize-1].getServId()-1);

      Time tempoAnterior(viagemAnterior/60,viagemAnterior%60);

      Time paragemOri = res[resSize-2].getHPassagem() + tempoAnterior;

      res[resSize-1].setHPassagem(paragemOri);
   }

	return res;
}

bool Transfairs::my_dfs_case2(Vertex<Service> *v,vector<Service> &res, bool* regresso) {

   v->setVisited(true);

	res.push_back(v->getInfo());

   bool validPoint = false;

   if (res.size() == 2){

      atualizaHoraPartida(res);

      if (res[0].getHPassagem() > partidaMaisTarde) {

         v->setVisited(false);

         return false;

      }

      int nPass = atualizaPassageiros(res);

      for (int i = 0 ; i < (v->getAdj()).size(); i++){
         if (regresso) return true;
         if ( (v->getAdj())[i].getDest()->getVisited() == false ){

            if (!continua(res[res.size()-1], (v->getAdj())[i].getDest(), nPass)) {

            *regresso = true;

               return true;

            }

            validPoint = my_dfs_case2((v->getAdj())[i].getDest(), res, regresso);
         }
      }

   } else {

      atualizaHoraPercurso(res);

      if (!verificaHorario(res)){

         v->setVisited(false);
         res.pop_back();
         return false;

      }

      int nPass = atualizaPassageiros(res);

      for (int i = 0 ; i < (v->getAdj()).size(); i++){
         if (regresso) return true;
         if ( (v->getAdj())[i].getDest()->getVisited() == false ){

            if (!continua(res[res.size()-1], (v->getAdj())[i].getDest(), nPass)) {

               *regresso = true;

               return true;

            }

            validPoint = my_dfs_case2((v->getAdj())[i].getDest(), res, regresso);
         }
      }


   }

   if (regresso) return true;
   /*
   if () {
      validPoint = verificaChegada(res);
   }
   */
   if (!validPoint){
      v->setVisited(false);
      res.pop_back();
   }

   return validPoint;
}


//##################################################################################################################
//##################################################################################################################

void Transfairs::atualizaHoraPercurso(vector<Service> &res){

   size_t ultimoPonto = res.size() -1;

   int duracaoPercurso = grafoInicial.edgeCost(res[ultimoPonto-1].getServId()-1, res[ultimoPonto].getServId()-1);

   Time horasPercurso(duracaoPercurso/60,duracaoPercurso%60);

   Time horaPartida = res[ultimoPonto-1].getHPassagem() + horasPercurso;

   res[ultimoPonto].setHPassagem(horaPartida);
}

void Transfairs::atualizaHoraPartida(vector<Service> &res){

   Time horaParagem = res[1].getHminRecolha();
   res[1].setHPassagem(res[1].getHminRecolha());
   int duracaoPercurso = grafoInicial.edgeCost(0, res[1].getServId()-1);
   Time horasPercurso(duracaoPercurso/60,duracaoPercurso%60);
   Time horaPartida = horaParagem - horasPercurso;

   res[0].setHPassagem(horaPartida);
}

int Transfairs::atualizaPassageiros(vector<Service> &res){

   int nPass = 0;

   for (int i = 1; i < res.size(); i++){
      if (res[i].getServId() == 1){
         nPass = 0;
      } else {
         nPass += res[i].getNumPassag();
      }
   }

   return nPass;
}

bool Transfairs::verificaChegada(vector<Service> &res){

   int duracaoPercurso = grafoInicial.edgeCost(res[res.size()-2].getServId()-1, res[res.size()-1].getServId()-1);

   Time horasPercurso(duracaoPercurso/60,duracaoPercurso%60);

   Time horaUltimoPonto = res[res.size()-2].getHPassagem() + horasPercurso;

   int duracaoRegresso = grafoInicial.edgeCost(res[res.size()-1].getServId()-1, 0);

   Time horasPercRegresso(duracaoRegresso/60,duracaoRegresso%60);

   Time horaFim = horaUltimoPonto + horasPercRegresso;

   if ( horaFim > chegadaMaisTarde ) return false;

   res[res.size()-1].setHPassagem(horaUltimoPonto);

   return true;
}

bool Transfairs::verificaHorario(vector<Service> &res)
{
   size_t ultimo = res.size() - 1;
   if (res[ultimo].getHPassagem() < res[ultimo].getHminRecolha() || res[ultimo].getHPassagem() > res[ultimo].getHmaxRecolha()){
      return false;
   }
   return true;
}

bool Transfairs::continua(Service ori, Vertex<Service> * dest, int nPass){

   int totalPassag = dest->getInfo().getNumPassag() + nPass;

   if (totalPassag > capacidadeVan ) {
      return false;
   }

   int duracaoViagem = grafoInicial.edgeCost(ori.getServId()-1, dest->getInfo().getServId()-1);

   Time horasViagem(duracaoViagem/60,duracaoViagem%60);

   Time chegada = ori.getHPassagem() + horasViagem;

   if (chegada < dest->getInfo().getHminRecolha() || chegada > dest->getInfo().getHmaxRecolha()) {
      return false;
   }
   return true;

}


//##################################################################################################################
//##################################################################################################################

//##################################################################################################################
//##################################################################################################################


Time Transfairs::calcTempViagem(){

   int duracao = grafoInicial.calcTempViagem(percurso_DFS, grafoInicial.getVertexSet()[0]->getInfo());

   Time horasViagem(duracao/60,duracao%60);

   return horasViagem;

}


void Transfairs::encontraSolucao(){

   chegadaMaisTarde = getEarlierArriveTime();

   calculaKruskal_R();
   dfsCalc();
   partidaMaisTarde =  chegadaMaisTarde - calcTempViagem();

   if ((numPassageirosTotal() > capacidadeVan)) {

      cout << "\nExcesso de Passageiro para utilizar apenas a uma carrinha/viagem\n" << endl;

      //dfsCalcPRIM_case2();
      //printSol(solucao_P2);

   } else {

      calculaPrim();
      dfsCalcPRIM();

      if (solucao_P.size() == (numServices()+2)) {

         cout << "\nSituação resolvida com apenas uma carrinha.\n" << endl;

         printSol(solucao_P);

      } else {

         cout << "\nViagem longa demais. É necessário mais do que uma viagem\n" << endl <<endl;

         //dfsCalcPRIM_case2();
         //printSol(solucao_P2);
      }
   }
}

Vertex<Service>* Transfairs::getEarlierService() {

	Vertex<Service>* temp;
	size_t numServices = grafoInicial.getVertexSet().size();

	temp = grafoInicial.getVertexSet()[1];

	for (int i = 2; i < numServices; i++){
		Vertex<Service>* aux = grafoInicial.getVertexSet()[i];
		if (aux->getInfo().getHminRecolha() < temp->getInfo().getHminRecolha()){
			temp = aux;
		}
	}

	return temp;

}

Time Transfairs::getEarlierArriveTime() {

	size_t numServices = grafoInicial.getVertexSet().size();

   Vertex<Service>* temp;
	temp = grafoInicial.getVertexSet()[1];

   Time minTime = temp->getInfo().getHmaxChegada();

	for (int i = 2; i < numServices; i++){
		Vertex<Service>* aux = grafoInicial.getVertexSet()[i];
		if (aux->getInfo().getHmaxChegada() < minTime){
         minTime = aux->getInfo().getHmaxChegada();
		}
	}

	return minTime;

}




