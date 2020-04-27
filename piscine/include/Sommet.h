#ifndef SOMMET_H
#define SOMMET_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "math.h"
#include <Svgfile.h>


class Sommet
{
    public:

        Sommet(std::istream& is);

        ~Sommet();

        int getId();

        int getX();
        int getY();

        void setId(int id);

        void dessiner(Svgfile& svgout);

    private:
        int m_id;
        std::pair<double,double>m_coords;
        char m_nom;
};

#endif // SOMMET_H
