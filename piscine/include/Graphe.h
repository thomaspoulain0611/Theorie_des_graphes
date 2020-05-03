#ifndef GRAPHE_H
#define GRAPHE_H

#include <Arete.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <Svgfile.h>
#include <iterator>
#include <numeric>
#include <algorithm>

class Graphe
{
public:
    Graphe(std::string fichier, std::string fichierPoids);

    virtual ~Graphe();


    int getOrient()const;
    int getOrdre()const;
    int getTaille()const;


    void setOrient(int orient);
    void poidsarete(std::string nomFichier);
    double trouverpoids(int s1,int s2);
    void interunpcc();


    void enregistrer();

    void centralitedegre();
    void rempliradj();
    Sommet*trouversommetindice(int indice);

    void centralitedegreN();
    void centraliteproxi();
    double dijkstraproxi(int depart,int arrivee);
    // double distanceproxi(std::vector<int>preds, int depart, int arrivee);
    void centraliteproxiN();

    void centralitevp();
    void centraliteinter1pcc();
    void centraliteinter1Npcc();
    int  dijkstrainter1pcc( int depart, int arrivee, int sparcouru);


void dijkstrainter(int depart, int arrivee, int sparcouru);
double presencesparcouru(int depart, int arrivee, int sparcouru, double distance);
int pasParcouru(int x, std::vector<int>& chemin);
void centraliteinterarete();

double areteparcourue(int depart, int arrivee, int ex1, int ex2,double distance);


void centraliteinter();
void centraliteinterN();
void recupcpg();
double getcpg()const;
void setcpg(double cpg);








    void affichercentralite();

    void dessinerTous(int& nom, int& poids,int&cdn,int&cd,int&cvp,int&cpn,int&cp,int&ci,int&ciN,int& cia);

    std::vector<int> bfs (int id);
    int nb_comp_connexe(int idSommet);
    void deleteArete(std::vector<int> id);
    void deleteAreteIndice(std::vector<int> id);

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
    double m_cpg;
    std::vector<Sommet*> m_sommets;
    std::vector<Arete*> m_aretes;


};

#endif // GRAPHE_H
