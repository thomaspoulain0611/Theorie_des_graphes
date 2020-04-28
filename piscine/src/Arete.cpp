#include "Arete.h"
#include <Sommet.h>
#include <sstream>

Arete::Arete(int indice, Sommet*s1, Sommet*s2)
{
    m_indice=indice;
    m_vect.first=s1;
    m_vect.second=s2;
    m_poids=0;
}

Arete::~Arete()
{
    //dtor
}

int Arete::getPoids()const
{
    return m_poids;
}

/*std::pair<Sommet*,Sommet*> Arete::getVect()
{
    return m_vect;
}*/

void Arete::setPoids(int poids)
{
    m_poids=poids;
}

/*void Arete::setVect(std::pair<Sommet*, Sommet*> som)
{
    m_vect=som;

}*/
     int Arete::getindice()const
     {
         return m_indice;
     }
      int Arete::getindiceS1()const
      {
          return m_vect.first->getId();
      }
        int Arete::getindiceS2()const
        {
            return m_vect.second->getId();
        }

        Sommet* Arete:: getSommet1()const
        {
            return m_vect.first;
        }

        Sommet* Arete::getSommet2()const
        {
            return m_vect.second;
        }
     void Arete::assimpoids(std::string nomFichier)
     {
         std::ifstream ifs{nomFichier};
         if(!ifs)// on verifie que le fichier existe
        throw std::runtime_error("Impossible d'ouvrir en lecture" + nomFichier );
        int taille;
        ifs>>taille;
        int indice,poids;
        for(int i=0;i<taille;++i)
        {
           ifs>>indice>>poids;
           if(indice==m_indice)
                this->setPoids(poids);
        }
     }



void Arete::dessiner(Svgfile& svgout)
{
    svgout.addLine(m_vect.first->getx(), m_vect.first->gety(), m_vect.second->getx(), m_vect.second->gety(), "grey");
}

std::string Arete::nbToStrg(int nombre)const
{
    std::ostringstream a;
    a<<nombre;
    return a.str();
}

void Arete::ecrirePoids(Svgfile& svgout)
{
    svgout.addText((m_vect.first->getx()+m_vect.second->getx())/2, (m_vect.first->gety()+m_vect.second->gety())/2, nbToStrg(m_poids), "red");
}
