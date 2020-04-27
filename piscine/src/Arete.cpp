#include "Arete.h"
#include <Sommet.h>

Arete::Arete()
{
    //ctor
}

Arete::~Arete()
{
    //dtor
}

int Arete::getPoids()
{
    return m_poids;
}

std::pair<Sommet*,Sommet*> Arete::getVect()
{
    return m_vect;
}

void Arete::setPoids(int poids)
{
    m_poids=poids;
}

void Arete::setVect(std::pair<Sommet*, Sommet*> som)
{
    m_vect=som;
}
