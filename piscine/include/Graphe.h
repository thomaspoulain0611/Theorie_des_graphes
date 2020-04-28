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
    Graphe();
    virtual ~Graphe();

    int getOrdre()const;
    int getTaille()const;
    int getOrient()const;

    //void setOrdre(int ordre);
    //void setTaille(int taille);
    void setOrient(int orient);
    void poidsarete();
    double trouverpoids(int s1,int s2);



    void centralitedegre();
    void rempliradj();
    Sommet*trouversommetindice(int indice);

    void centralitedegreN();
    void centraliteproxi();
    double dijkstraproxi(int depart,int arrivee);
   // double distanceproxi(std::vector<int>preds, int depart, int arrivee);
   void centraliteproxiN();

   void centralitevp();
    void affichercentralite();

    void dessinerTous(int& nom, int& poids,int&cdn,int&cd,int&cpn,int&cp);

    void enregistrer(std::ofstream& ofs);

    std::vector<int> bfs (Sommet s);
    void comp_connexe(Sommet s);


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
