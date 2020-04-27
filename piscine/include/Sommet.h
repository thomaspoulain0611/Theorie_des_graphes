#ifndef SOMMET_H
#define SOMMET_H
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include"math.h"


class Sommet
{
    public:

        Sommet(std::istream& is);

        ~Sommet();

        int getId();

        void setId();

    private:
        int m_id;
        std::pair<double,double>m_coords;
        char m_nom;
};

#endif // SOMMET_H
