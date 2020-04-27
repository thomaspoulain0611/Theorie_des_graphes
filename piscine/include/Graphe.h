#ifndef GRAPHE_H
#define GRAPHE_H

#include <Sommet.h>
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

        int getOrdre();
        int getTaille();
        int getOrient();

        void setOrdre(int ordre);
        void setTaille(int taille);
        void setOrient(int orient);

        void dessiner(Svgfile& svgout);

    private:
        int m_ordre;
        int m_taille;
        int m_orient;
        std::vector<Sommet*> m_sommets;
        std::vector<Arete*> m_aretes;

};

#endif // GRAPHE_H
