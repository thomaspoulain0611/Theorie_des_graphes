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
        Sommet(int id);

        ~Sommet();

        int getId()const;
        std::string getNom()const;
        double getx()const;
        double gety()const;

        void setId(int id);

        void dessiner(Svgfile& svgout);
        void ecrireNom(Svgfile& svgout);

       friend std::ostream& operator<<(std::ostream&out, const Sommet&a)
        {
           std::cout<<"("<<a.getId()<<","<<a.getNom()<<","<<a.getx()<<","<<a.gety()<<")"<<std::endl;
        return out;
        }

    private:
        int m_id;
        std::pair<double,double>m_coords;
        std::string m_nom;
};

#endif // SOMMET_H
