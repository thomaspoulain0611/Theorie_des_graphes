#ifndef GRAPHE_H
#define GRAPHE_H
#include <iostream>
#include <vector>

#include <Sommet.h>
#include <Arete.h>

class Graphe
{
    public:
        Graphe();
        ~Graphe();

        int getOrdre();
        int getTaille();
        int getOrient();

        void setOrdre();
        void setTaille();
        void setOrient();

    private:
        int m_ordre;
        int m_taille;
        int m_orient;
        std::vector<Sommet*> m_vect_som;
        std::vector<Arete*> m_vect_aret;
};

#endif // GRAPHE_H
