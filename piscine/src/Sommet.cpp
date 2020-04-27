#include "Sommet.h"

Sommet::Sommet(std::istream& is)
{
    double x;
    double y;
    //char nom;
    is>>m_id>>m_nom>>x>>y;
    m_coords.first=x;
    m_coords.second=y;

}

Sommet::Sommet(int id)
{
    m_id=id;
}

Sommet::~Sommet()
{
    //dtor
}

int Sommet::getId()const
{
    return m_id;
}

void Sommet::setId(int id)
{
    m_id=id;
}

   char Sommet::getNom()const
   {
       return m_nom;

   }
        double Sommet::getx()const
        {
            return m_coords.first;

        }
        double Sommet::gety()const
        {
            return m_coords.second;

        }






void Sommet::dessiner(Svgfile& svgout)
{
    svgout.addDisk(m_coords.first, m_coords.second, 5, "red");
}

