#include "Graphe.h"


Graphe::Graphe(std::string nomFichier)
{
    std::ifstream ifs{nomFichier};//
    if(!ifs)// on verifie que le fo
        throw std::runtime_error("Impossible d'ouvrir en lecture" + nomFichier );

    ifs>>m_orient;
    if (ifs.fail() )
        throw std::runtime_error("Erreur de lecture d'orientation");
    int ordre;
    ifs>>ordre;
    if (ifs.fail() )
        throw std::runtime_error("Erreur de lecture d'ordre");


    for (int i=0; i<ordre; ++i)
    {
        m_sommets.push_back(new Sommet(ifs));
    }
    int taille;
    ifs>>taille;
    if (ifs.fail() )
        throw std::runtime_error("Erreur de lecture d'ordre");
    int indice;
    int s1;
    int s2;

    for (int i=0; i<taille; ++i)
    {
        ifs>>indice>>s1>>s2;
        for (size_t i=0; i<m_sommets.size(); ++i)
        {

            for (size_t j=0; j<m_sommets.size(); ++j)
            {

                if((s1==m_sommets[i]->getId())&&(s2==m_sommets[j]->getId()))
                {

                    m_aretes.push_back(new Arete(indice,m_sommets[i],m_sommets[j]));

                }

            }


        }

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




int Graphe::getOrdre()const
{
    return (int) m_sommets.size();
}

int Graphe::getOrient()const
{
    return m_orient;
}

int Graphe::getTaille()const
{
    return (int) m_aretes.size();
}

/*void Graphe::setOrdre(int ordre)
{
    m_ordre=ordre;
}*/

void Graphe::setOrient(int orient)
{
    m_orient=orient;
}

/*void Graphe::setTaille(int taille)
{
    m_taille=taille;
}*/

/*void Graphe::dessiner()
{

}
*/
void Graphe::poidsarete ()

{
    for(size_t i=0; i<m_aretes.size(); ++i)
    {
        m_aretes[i]->assimpoids("poids.txt");
    }
}





/*if(m_orient==1)
    std::cout<<"Le graphe est orienté"<<std::endl;
else
    std::cout<<"Le graphe n'est pas orienté"<<std::endl;
std::cout<<"Ordre du graphe :"<<m_sommets.size()<<std::endl;
for (size_t i=0; i<m_sommets.size();++i)
{

}*/

void Graphe::dessinerTous(int& nom, int& poids)
{
    Svgfile svgout;
    for(size_t i=0; i<m_sommets.size(); i++)
    {
        m_sommets[i]->dessiner(svgout);
    }
    if(nom==1)
    {
        for(size_t i=0; i<m_sommets.size(); i++)
        {
            m_sommets[i]->ecrireNom(svgout);
        }
    }

    for(size_t i=0; i<m_aretes.size(); i++)
    {

        m_aretes[i]->dessiner(svgout);
    }
    if(poids==1)
    {
        for(size_t i=0; i<m_aretes.size(); i++)
        {
            m_aretes[i]->ecrirePoids(svgout);
        }
    }

}

/*void Graphe::ecrireTousPoids(Svgfile& svgout)
{
    for(size_t i=0; i<m_aretes.size(); i++)
    {
        m_aretes[i]->ecrirePoids(svgout);
    }
}

void Graphe::ecrireTousNoms(Svgfile& svgout)
{
    for(size_t i=0; i<m_sommets.size(); i++)
    {
        m_sommets[i]->ecrireNom(svgout);
    }
}*/
