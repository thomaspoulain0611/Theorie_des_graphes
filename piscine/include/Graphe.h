#ifndef GRAPHE_H
#define GRAPHE_H


#include <Arete.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <Svgfile.h>

class Graphe
{
public:
    Graphe(std::string nomFichier);
    virtual ~Graphe();

    int getOrdre()const;
    int getTaille()const;
    int getOrient()const;

    //void setOrdre(int ordre);
    //void setTaille(int taille);
    void setOrient(int orient);
    void poidsarete();
    void dessiner(Svgfile& svgout);
    friend std::ostream& operator<<(std::ostream& out, const Graphe& r)
    {

        out<<"Graphe d'orientation :"<<r.getOrient()<<std::endl;
        out <<"Graphe d'ordre :"<< r.getOrdre()<<std::endl;
        for (const auto t:r.m_sommets)
            out<<*t;
        out<< "Graphe de taille :"<<r.getTaille()<<std::endl;

        for (const auto s:r.m_aretes )
            out<<*s;
        return out;
    }

private:


    int m_orient;
    std::vector<Sommet*> m_sommets;
    std::vector<Arete*> m_aretes;


};

#endif // GRAPHE_H
