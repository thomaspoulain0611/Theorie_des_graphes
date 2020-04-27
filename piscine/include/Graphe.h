#ifndef GRAPHE_H
#define GRAPHE_H

#include <Sommet.h>
#include <Arete.h>
#include <iostream>
#include <vector>

class Graphe
{
    public:
        Graphe(std::string nomFichier);
        virtual ~Graphe();

        int getOrdre();
        int getTaille();
        int getOrient();

        void setOrdre(int ordre);
        void setTaille(int taille);
        void setOrient(int orient);

    private:
        int m_ordre;
        int m_taille;
        int m_orient;
        std::vector<Sommet*> m_vect_som;
        std::vector<Arete*> m_vect_aret;

};

#endif // GRAPHE_H
