/*
 * Service.cpp
 */

#include "Service.h"

int Service::last_serv_id = 0;

// ======================================================

Service::Service():serv_id(++last_serv_id)
{}

// ======================================================

Service::Service(string nome, int n_passageiros, int hour_serv, int min_serv, int sec_serv, int min_overhead):serv_id(++last_serv_id)
{
    try
    {
        setNomServ(nome);
        setNumPassag(n_passageiros);
        setHmaxChegada(hour_serv, min_serv, sec_serv);
        setHminChegada(h_max_chegada,min_overhead);

    }
    catch(Service::NumPassagInvalid &p)
    {
        p.getMsg();
    }
}

// ======================================================

void Service::setNomServ(string nom)
{
    nom_serv = nom;
}

// ======================================================

void Service::setNumPassag(int num)
{
    if(num < 0)
    {
        throw NumPassagInvalid(num);
    }
    
    n_passageiros = num;
    
}

// ======================================================

void Service::setHmaxChegada(int hour, int minute, int second)
{
    h_max_chegada.setTime(hour, minute, second);
}

// ======================================================

void setHminChegada(Time h_max_chegada, int& min_overhead) {
	h_min_chegada.setTime() = h_max_chegada - new Time (0,min_overhead,0);
}

// ======================================================

string Service::getNomServ() const
{
    return nom_serv;
}

// ======================================================

int Service::getLastServId()
{
    return last_serv_id;
}

// ======================================================

int Service::getServId() const
{
    return serv_id;
}

// ======================================================

int Service::getNumPassag() const
{
    return n_passageiros;
}

// ======================================================

Time Service::getHmaxChegada() const
{
    return h_max_chegada;
}

// ======================================================

ostream & operator << (ostream &os, const Service &s)
{
    os << "# " << s.getServId() << " Nome: " << s.getNomServ() << " - " << s.getHmaxChegada() << " - " << s.getNumPassag();
    return os;
}

// ======================================================

bool Service::operator == (const Service &s2) const
{
    return (serv_id == s2.serv_id);
}


