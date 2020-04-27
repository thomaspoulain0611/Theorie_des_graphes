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
        Sommet(int id);

        ~Sommet();

        int getId()const;
        char getNom()const;
        double getx()const;
        double gety()const;

        void setId(int id);

       friend std::ostream& operator<<(std::ostream&out, const Sommet&a)
        {
           std::cout<<"("<<a.getId()<<","<<a.getNom()<<","<<a.getx()<<","<<a.gety()<<")"<<std::endl;
        return out;
        }

    private:
        int m_id;
        std::pair<double,double>m_coords;
        char m_nom;
};

#endif // SOMMET_H
