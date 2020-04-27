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

void Sommet::setId(int id)
{
    m_id=id;
}

int Sommet::getX()
{
    return m_coords.first;
}

int Sommet::getY()
{
    return m_coords.second;
}

void Sommet::dessiner(Svgfile& svgout)
{
    svgout.addDisk(m_coords.first, m_coords.second, 1, "red");
}
