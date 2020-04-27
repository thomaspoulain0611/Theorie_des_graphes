#include "Arete.h"
#include <Sommet.h>

Arete::Arete(std::istream& is)
{
     int S1,S2;
    is>>m_indice>>S1>>S2;
    m_vect.first=S1;
    m_vect.second=S2;

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
