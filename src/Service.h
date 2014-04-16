/*
 * Service.h
 */

#ifndef SERVICE_H_
#define SERVICE_H_

#include <iostream>
#include <string>

#include "Time.h"

using namespace std;

class Service
{
    static int last_serv_id;
    
    int serv_id;
    string nom_serv;
    int n_passageiros;
    Time h_max_chegada;
    Time h_min_recolha;
    Time h_max_chegada;

public:
    Service();
    Service(string nome, Time h_max_chegada, int min_overhead);
    
    void setNomServ(string nom);
    void setNumPassag(int num);
    void setHmaxChegada(int hour, int minute, int second);
    
    static int getLastServId();
    
    string getNomServ() const;
    int getServId() const;
    int getNumPassag() const;
    Time getHmaxChegada() const;
    
    
    bool operator == (const Service &s2) const;
    friend ostream & operator << (ostream &os, const Service &s);
    
    class NumPassagInvalid
    {
        int n_passag;
        
    public:
        NumPassagInvalid(int num)
        {
            n_passag = num;
        }
        void getMsg()
        {
            cout << "Num de Passageiros: " << n_passag << endl;
        }
    };
    
};


#endif
