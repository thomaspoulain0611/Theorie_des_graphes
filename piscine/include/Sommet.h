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

        int getId()const;
        std::string getNom()const;
        double getx()const;
        double gety()const;

        double getcd()const;
        double getcdn()const;
        double getcp()const;
        double getcpn()const;
        char get_color() const;
        double get_distance()const;

        size_t get_nb_adj() const;
        Sommet* get_adj(int x) const;

        void rempliradj();




        void setId(int id);
        void setcd(double cd);
        void setcdn(double cdn);
        void setcp(double cp);
        void setcpn(double cpn);
        void setadj(Sommet* s1);
        void set_color(char color);
        void set_distance(double distance);


        void dessiner(Svgfile& svgout);
        void ecrireNom(Svgfile& svgout);

       friend std::ostream& operator<<(std::ostream&out, const Sommet&a)
        {
           std::cout<<"("<<a.getId()<<","<<a.getNom()<<","<<a.getx()<<","<<a.gety()<<")"<<std::endl;
        return out;
        }

    private:
        int m_id;
        std::vector<Sommet*>m_adj;
        char m_couleur;
        double m_distance;
        double m_cd;
       double m_cdn;
       double m_cp;
       double m_cpn;


        std::pair<double,double>m_coords;
        std::string m_nom;
};

#endif // SOMMET_H
