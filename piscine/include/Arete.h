#ifndef ARETE_H
#define ARETE_H
#include <iostream>

#include <math.h>
#include <Sommet.h>


class Arete
{
    public:
        Arete(int indice, Sommet*s1,Sommet*s2);
        //Arete(std::istream& is);
        ~Arete();

        int getPoids()const;
        int getindice()const;
        int getindiceS1()const;
        int getindiceS2()const;
        Sommet* getSommet1()const;
        Sommet* getSommet2()const;
        //std::pair<Sommet*, Sommet*> getVect();
        void assimpoids(std::string nomFichier);

        void setPoids(int poids);
        //void setVect(std::pair<Sommet*, Sommet*> som);

        void dessiner(Svgfile& svgout);
        void marquerArete(Svgfile& svgout);
        void ecrirePoids(Svgfile& svgout);
        std::string nbToStrg(double nombre)const;

         friend std::ostream& operator<<(std::ostream&out, const Arete&a)
    {

        std::cout<<"(indice arete :"<<a.m_indice<<", premiere extremite:"<<a.m_vect.first->getId()<<", deuxieme extremite:"<<a.m_vect.second->getId()<<", poids:"<<a.m_poids<<")"<<std::endl;
        return out;
    }


    private:
        int m_poids;
        std::pair<Sommet*, Sommet*> m_vect;
        int m_indice;
};

#endif // ARETE_H
