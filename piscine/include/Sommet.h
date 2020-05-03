#ifndef SOMMET_H
#define SOMMET_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "math.h"
#include <Svgfile.h>
#include <queue>


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
    double getcvp()const;
    double getcsi()const;
    double getci1()const;
    double getci1n()const;
    double getci()const;
    double getciN()const;

    char get_color() const;
    double get_distance()const;

    size_t get_nb_adj() const;
    Sommet* get_adj(int x) const;
    std::vector<Sommet*> getAdj()const;

    void rempliradj();

    void setVectAdj(std::vector<Sommet*> thomaslpb);
    void setId(int id);
    void setcd(double cd);
    void setcdn(double cdn);
    void setcp(double cp);
    void setcpn(double cpn);
    void setcvp(double cvp);
    void setcsi(double csi);
    void setci1(double ci1);
    void setci1n (double ci1n);
    void setci (double ci);
    void setciN(double ciN);

    void setadj(Sommet* s1);
    void set_color(char color);
    void set_distance(double distance);

    void dessiner(Svgfile& svgout);
    void dessinerMarque(Svgfile& svgout);
    void ecrireNom(Svgfile& svgout);
    void ecrireCentraliteDegreN(Svgfile& svgout);
    void ecrireCentraliteDegre(Svgfile& svgout);
    void ecrireCentraliteP(Svgfile& svgout);
    void ecrireCentralitePN(Svgfile& svgout);
    void ecrireCentraliteVP(Svgfile& svgout);
    void ecrireCentraliteCI(Svgfile& svgout);
    void ecrireCentraliteCIN(Svgfile& svgout);
    std::string nbToStrg(double nombre) const;

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
    double m_cvp;
    double m_csi;
    double m_ci1;
    double m_ci1n;
    double m_ci;
    double m_ciN;

    std::pair<double,double>m_coords;
    std::string m_nom;

};

#endif // SOMMET_H
