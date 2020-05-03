#include "Arete.h"
#include <Sommet.h>
#include <sstream>

// constructeur d'arete
Arete::Arete(int indice, Sommet*s1, Sommet*s2)
{
    m_indice=indice;
    m_vect.first=s1;
    m_vect.second=s2;

}

Arete::~Arete()
{
    //dtor
}
//getter qui permet d'obtenir le poids de l'arete
double Arete::getPoids()const
{
    return m_poids;
}
// setter qui permet d'attribuer un poids à l'arete
void Arete::setPoids(double poids)
{
    m_poids=poids;
}
//getter qui permet d'obtenir l'indice de l'arete
int Arete::getindice()const
{
    return m_indice;
}
//getter qui permet d'obtenir l'indice du sommet 1 de l'arete
int Arete::getindiceS1()const
{
    return m_vect.first->getId();
}
//getter qui permet d'obtenir l'indice du sommet 2 de l'arete
int Arete::getindiceS2()const
{
    return m_vect.second->getId();
}
//getter qui permet d'obtenir le sommet 1 de l'arete
Sommet* Arete:: getSommet1()const
{
    return m_vect.first;
}
//getter qui permet d'obtenir le sommet 2 de l'arete
Sommet* Arete::getSommet2()const
{
    return m_vect.second;
}
//getter qui permet d'obtenir l'indice de centralite d'intermediarite de l'arete
double Arete::getciA()const
{
    return m_ciA;
}
//// setter qui permet d'attribuer une valeur à la centralite d'intermediarite de l'arete
void Arete::setciA(double ciA)
{
    m_ciA=ciA;
}
//getter qui permet d'obtenir le nom du sommet 1 de l'arete
std::string Arete::trouverNomS1()const
{
    return m_vect.first->getNom();
}
//getter qui permet d'obtenir le nom du sommet 2 de l'arete
std::string Arete::trouverNomS2()const
{
    return m_vect.second->getNom();
}

///Fonction qui transforme un double en string

std::string Arete::nbToStrg(double nombre)const
{
    std::ostringstream a;
    a<<nombre;
    return a.str();
}

///Fonction dessin des aretes

void Arete::dessiner(Svgfile& svgout)
{
    svgout.addLine(this->m_vect.first->getx(), this->m_vect.first->gety(), this->m_vect.second->getx(), this->m_vect.second->gety(), "grey");//Dessin d'un arete en gris
}

void Arete::ecrirePoids(Svgfile& svgout)
{
    svgout.addText((this->m_vect.first->getx()+this->m_vect.second->getx())/2, (this->m_vect.first->gety()+this->m_vect.second->gety())/2, nbToStrg(m_poids), "red");//Ecriture du poids d'une arete en rouge
}

void Arete::ecrireCIA(Svgfile& svgout)
{
    svgout.addText((this->m_vect.first->getx()+this->m_vect.second->getx())/2, (this->m_vect.first->gety()+this->m_vect.second->gety())/2, nbToStrg(m_ciA), "black");//Ecriture de l'indice de centralite d'intermediarite d'une arete
}

void Arete::marquerArete(Svgfile& svgout)
{
    svgout.addLine(this->m_vect.first->getx(), this->m_vect.first->gety(), this->m_vect.second->getx(), this->m_vect.second->gety(), "red");//Dessin d'un arete en rouge
}


