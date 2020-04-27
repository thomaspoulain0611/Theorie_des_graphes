#include "Graphe.h"



    Graphe::Graphe(std::string nomFichier)
{
    std::ifstream ifs{nomFichier};//
    if(!ifs)// on verifie que le fo
        throw std::runtime_error("Impossible d'ouvrir en lecture" + nomFichier );
        int orientation;
        ifs>>orientation;
    int ordre;
    ifs>>ordre;
    if (ifs.fail() )
        throw std::runtime_error("Erreur de lecture d'ordre");


        for (size_t i=0;i<ordre;++i)
        {
            m_sommets.push_back(new Sommet(ifs));
        }
        int taille;
        ifs>>taille;
        if (ifs.fail() )
        throw std::runtime_error("Erreur de lecture d'ordre");
        for (size_t i=0;i<taille;++i)
        {
            m_aretes.push_back(new Arete(ifs));
        }


   /* int taille;
    ifs>>taille;
    if ( ifs.fail() )
        throw std::runtime_error("Erreur de lecture de taille");
    for (int i=0; i<ordre; ++i)
    {
        m_sommets.push_back(new Sommet{i+1});// vu que ca part de 0 on lui attribue la valeur i+1
    }
    for (int i=0; i<taille; ++i)
    {
        m_aretes.push_back(new Arete(ifs));// lire le prochain truc que le flux va lire
    }*/
}

Graphe::~Graphe()
{
    for (auto s : m_sommets)
        delete s;
    for (auto s : m_aretes)
        delete s;
}


Graphe::~Graphe()
{
    //dtor
}

int Graphe::getOrdre()
{
    return m_ordre;
}

int Graphe::getOrient()
{
    return m_orient;
}

int Graphe::getTaille()
{
    return m_taille;
}

void Graphe::setOrdre(int ordre)
{
    m_ordre=ordre;
}

void Graphe::setOrient(int orient)
{
    m_orient=orient;
}

void Graphe::setTaille(int taille)
{
    m_taille=taille;
}

void Graphe::dessiner()
{

}
