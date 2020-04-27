#include "Arete.h"
#include <Sommet.h>

Arete::Arete(std::istream& is)
{
     int S1,S2;
    is>>m_indice>>S1>>S2;

    Sommet *s1=new Sommet (S1);
    Sommet *s2=new Sommet(S2);

    m_vect.first=s1;
    m_vect.second=s2;

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
