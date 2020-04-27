#include "Sommet.h"

Sommet::Sommet(std::istream& is)
{
    double x;
    double y;
    char nom;
    is>>m_id>>m_nom>>x>>y;
    m_coords.first=x;
    m_coords.second=y;

}

Sommet::~Sommet()
{
    //dtor
}

int Sommet::getId()
{
    return m_id;
}

void Sommet::setId()
{

}
