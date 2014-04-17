/*
 * Service.cpp
 */

#include "Service.h"

int Service::last_serv_id = 0;

// ======================================================

Service::Service():serv_id(++last_serv_id)
{}

// ======================================================

Service::Service(string nome, int n_passageiros, Time h_max_chegada, int dur_viagem_aero, int overhead):serv_id(++last_serv_id)
{
    try
    {
        setNomServ(nome);
        setNumPassag(n_passageiros);
        setHmaxChegada(h_max_chegada);
        setHmaxRecolha(dur_viagem_aero);
        setHminRecolha(overhead);

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

void Service::setHmaxChegada(Time h_max_chegada)
{
    (this)->h_max_chegada = h_max_chegada;
}

// ======================================================

void Service::setHmaxRecolha(int dur_viagem_aero)
{
	Time t_viagem(dur_viagem_aero / 60,dur_viagem_aero % 60);

    h_max_recolha = h_max_chegada - t_viagem;
}

// ======================================================

void Service::setHminRecolha(int min_overhead)
{
	Time t_overhead(min_overhead / 60,min_overhead % 60);

	h_min_recolha = h_max_recolha - t_overhead;
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

void Service::resetServID()
{
    last_serv_id = 0;
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

Time Service::getHmaxRecolha() const
{
    return h_max_recolha;
}

// ======================================================

Time Service::getHminRecolha() const
{
    return h_min_recolha;
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


