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
        double getciA()const;
        double getciAN()const;
        //std::pair<Sommet*, Sommet*> getVect();
        void assimpoids(std::string nomFichier);

        void setPoids(int poids);

        void setciA(double ciA);
        void setciAN(double ciAN);


        void dessiner(Svgfile& svgout);
        void ecrirePoids(Svgfile& svgout);
        std::string nbToStrg(double nombre)const;

         friend std::ostream& operator<<(std::ostream&out, const Arete&a)
    {

        std::cout<<"(indice arete :"<<a.m_indice<<", premiere extremite:"<<a.m_vect.first->getId()<<", premieres coordonnees x:"<<a.m_vect.first->getx()<<", deuxieme extremite:"<<a.m_vect.second->getId()<<", poids:"<<a.m_poids<<")"<<std::endl;
        return out;
    }


    private:
        int m_poids;
        std::pair<Sommet*, Sommet*> m_vect;
        double m_ciA;
        double m_ciAN;
        int m_indice;
};

#endif // ARETE_H
