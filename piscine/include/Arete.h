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
        void assimpoids(std::string nomFichier);

        void setPoids(int poids);

        void setciA(double ciA);

        std::string trouverNomS1()const;
        std::string trouverNomS2()const;

        void dessiner(Svgfile& svgout);
        void effacer(Svgfile& svgout);
        void marquerArete(Svgfile& svgout);
        void ecrirePoids(Svgfile& svgout);
        void ecrireCIA(Svgfile& svgout);
        std::string nbToStrg(double nombre)const;

         friend std::ostream& operator<<(std::ostream&out, const Arete&a)
    {

        std::cout<<"(indice arete :"<<a.m_indice<<", premiere extremite:"<<a.m_vect.first->getId()<<", deuxieme extremite:"<<a.m_vect.second->getId()<<", poids:"<<a.m_poids<<")"<<std::endl;
        return out;
    }


    private:
        int m_poids;
        std::pair<Sommet*, Sommet*> m_vect;
        double m_ciA;
        int m_indice;
};

#endif // ARETE_H
