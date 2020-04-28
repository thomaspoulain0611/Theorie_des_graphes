#include "Graphe.h"
#include<queue>
#include<stack>


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


/*     int taille;
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


void Graphe::poidsarete ()

{
    for(size_t i=0; i<m_aretes.size(); ++i)
    {
        m_aretes[i]->assimpoids("poids.txt");
    }
}

void Graphe::centralitedegre()
{

    this->rempliradj();
    for(size_t i=0; i<m_sommets.size(); ++i)
    {

        m_sommets[i]->setcd((double)m_sommets[i]->get_nb_adj());
       /* cd=0;
        for(size_t j=0; j<m_aretes.size(); ++j)
        {
            if (m_aretes[j]->getindiceS1()==m_sommets[i]->getId()||m_aretes[j]->getindiceS2()==m_sommets[i]->getId())
           cd+=1;
        }
        m_sommets[i]->setcd(cd);*/


    }
}


void Graphe::centralitedegreN()
{

    double cd;
    for (size_t i=0; i<m_sommets.size(); ++i)
    {

        cd=m_sommets[i]->getcd();


        m_sommets[i]->setcdn(cd/((float)m_sommets.size()-1));

    }
}


double Graphe::trouverpoids(int s1,int s2)
{
    double poids;

    for(size_t i=0; i<m_aretes.size(); ++i)
    {
        if (((m_aretes[i]->getindiceS1()==s1)&&(m_aretes[i]->getindiceS2()==s2))||((m_aretes[i]->getindiceS1()==s2)&&(m_aretes[i]->getindiceS2()==s1)))
           {

           poids=m_aretes[i]->getPoids();
            std::cout<<"trouver poids :"<<poids<<std::endl;
           }
           std::cout<<"lilian"<<std::endl;
    }

    return poids;

}

Sommet*Graphe::trouversommetindice(int indice)
{
    Sommet*s1;
    for(size_t i=0; i<m_sommets.size();++i)
    {
        if (m_sommets[i]->getId()==indice)
            s1=m_sommets[i];
    }
    return s1;
}


double Graphe::dijkstraproxi(int depart,int arrivee)


{

    std::vector<int> I_preds;//I_preds[i] donne le prédécesseur du sommet i
    std::priority_queue<double, std::vector<double>, std::greater<double> > distances; //file de priorite avec le plus petit element en top
//initialisation variables temporaires
    int succ=0;
    int dist=0;
    int sommet=-6;
    size_t nb=0;
    double poids=0;
    Sommet*S=nullptr;
//initialisation: chaque case vecteur de predecesseurs à -1 et tous les sommets sont blancs/non parcourus
    for(size_t i=0; i<m_sommets.size(); ++i)
    {
        m_sommets[i]->set_color('B');//sommets non marqués
        m_sommets[i]->set_distance(1000000000000000000);//distance infinie
         I_preds.push_back(-1);//autant de cases que de sommets
    }

    S=trouversommetindice(depart);


    nb=S->get_nb_adj();//on recupère le nombre de successeurs du sommet parcouru

    sommet=depart;//sommet actuel est celui de depart


//tant qu'on arrive pas au sommet dont on souhaite connaitre le chemin
    while(sommet!=arrivee)
    {
        S=trouversommetindice(sommet);

        nb=S->get_nb_adj();//on recupère le nombre de successeurs du sommet parcouru



        for(size_t x=0; x<nb; ++x)//pour chaque successeur de sommet
        {

        S=trouversommetindice(sommet);




            succ=S->get_adj(x)->getId();//on récupère le sommet x



            poids=trouverpoids(sommet,succ);



            S=trouversommetindice(succ);




                if(S->get_color()=='B')//si successeur non découvert
                {

                    //si poids de l'arête entre le sommet et son voisin + distance séparant le sommet actuel et le sommet de départ
                    //donne une distance plus petite que la distance qu'il avait jusque là
                    if(dist+poids<S->get_distance())
                    {

                        S->set_distance(dist+poids);//on donne à succ la nouvelle distance du chemin plus court

                        I_preds.at(succ)=sommet;//on marque sommet comme prédécesseur de succ/

                        //std::cout<<"sommet:"<<sommet->getId()<<std::endl;
                        distances.push(dist+poids);//on ajoute cette nouvelle distance à la file de priorité

                    }
                    else
                        distances.push(dist+S->get_distance());//sinon on ajoute l'ancienne distance (entre succ et sommet de départ) à la file
                }
            }


            S=trouversommetindice(sommet);
            S->set_color('N');//on marque le sommet parcouru
            dist=distances.top();//distance du chemin le plus court est la valeur au top de la file de priorité
            distances.pop();//on supprimme cette distance de la file

            //on parcourt tous les sommets
            for(size_t y=0; y<m_sommets.size(); ++y)
            {
                //si on trouve le sommet correspondant au chemin le plus court et qu'il est non parcouru
                if((m_sommets[y]->get_distance()==dist)&&(m_sommets[y]->get_color()=='B'))
                {
                    sommet=m_sommets[y]->getId();
                    //ce sommet est le nouveau sommet de parcours
                }
            }

        }
        std::cout<<" distance entre sommet"<<depart<<"et sommet"<<arrivee<<"="<<dist<<std::endl;

         return dist;


}
/*double Graphe::distanceproxi(std::vector<int> nouv,int depart, int arrivee)
{

    int pred=0;
    double somme=0;
    std::cout<<"depart :"<<depart<<std::endl;
    std::cout<<"arrivee :"<<arrivee<<std::endl;

    for(size_t i=0; i<nouv.size(); ++i) // on parcourt tous les prédecesseurs
    {
        std::cout<<"i :"<<i<<std::endl;
        if((int)i==arrivee)// si numero case correspond au sommet d'arrivée
        {
            //std::cout<<i;// on affiche le sommet d'arrivée
            pred=nouv[i];//on note son predecesseur
            std::cout<<"pred :"<<pred<<std::endl;

            while(pred!=depart)// tant que le prédecesseur n'est pas le sommet de départ
            {
                std::cout<<"<-- pred:"<<pred;// on affiche "<--"

                pred=nouv[pred];// predecesseur prend la valeur du predecesseur du sommet alors traité
            }
            std::cout<<"<--"<<depart<<" : longueur ";// on affiche le sommet de départ

            //affichage poids
            pred=nouv[i];// on remet à pred la valeur du prédecesseur de notre nombre d'arrivée
            int parcours=pred;

            double poids;
            poids=trouverpoids(pred,nouv[i]);

            // on initialise le sommet parcours et la somme(longueur chemin)
            //std::cout<<m_sommets[pred]->get_poids(i);// on affiche le poids correspondant à l'arete entre le prédécesseur de i et i
            somme+=poids;// on ajoute cette valeur à notre somme

            while(parcours!=depart)// tant que parcours est différent de départ
            {
                pred=nouv[parcours];
                poids=trouverpoids(pred,parcours);

                // on assimile à pred la valeur du prédecesseur du sommet étudié
                std::cout<<"+"<<poids;// on affiche le poids de l'arête entre ces deux sommets
                somme+=poids;// on l'ajoute à la somme
                parcours=pred;//maj du sommet parcouru
            }


        }
    }
    std::cout<<"somme :"<<somme<<std::endl;
    return somme;
}*/


void Graphe::centraliteproxi()
{
    double cp;
    this->rempliradj();



    for (size_t i=0; i<m_sommets.size(); ++i)
    {
        cp=0;

        for (size_t j=0; j<m_sommets.size(); ++j)
        {
            if ((m_sommets[i]->getId())!=(m_sommets[j]->getId()))
                {



            cp+=dijkstraproxi(m_sommets[i]->getId(),m_sommets[j]->getId());
            //cp+=distanceproxi(preds,m_sommets[i]->getId(),m_sommets[j]->getId());
                }
            //ideal:: dijkstraproxi(m_sommets[i],m_sommets[j]

        }
        cp=1/cp;
       m_sommets[i]->setcp(cp);

    }
}

void Graphe::centraliteproxiN()
{

    double cp;
    for (size_t i=0; i<m_sommets.size(); ++i)
    {

        cp=m_sommets[i]->getcp();


        m_sommets[i]->setcpn(cp*(m_sommets.size()-1));

    }
}

/*void Graphe::centralitevp()
{

    double lambda=0;
    double csi=0;
    std::stack<double>slambda;

    this->rempliradj();
    for(size_t i=0;i<m_sommets.size();++i)
    {
        m_sommets[i]->setcvp(1);
    }


        while ()
        {
               for(size_t i=0;i<m_sommets.size();++i)
               {
                   csi=0;




            for(size_t j=0;j<m_sommets[i]->get_nb_adj();++j)
            {
               csi+=m_sommets[i]->get_adj(j)->getcvp();
            }
            m_sommets[i]->setcsi(csi);

               }
            for (size_t k=0; k<m_sommets.size();++k)
            {
                lambda+=pow(m_sommets[k]->getcsi(),2);
            }
            lambda=pow(lambda,1/2);
            std::cout<<"lambda :"<<lambda<<std::endml;
            for (size_t i=0; i<m_sommets.size();++i)
            {
                m_sommets[i]->setcvp((m_sommets[i]->getcsi())/lambda);
            }

           // for (size_t l=0; )
        }
    }*/


void Graphe::rempliradj()
{
    for (size_t i=0; i<m_sommets.size(); ++i)
    {
        for(size_t j=0; j<m_aretes.size(); ++j)
        {
            if((m_aretes[j]->getindiceS1())==m_sommets[i]->getId())
            {
                m_sommets[i]->setadj(m_aretes[j]->getSommet2());
            }
            if ((m_aretes[j]->getindiceS2()==m_sommets[i]->getId()))
            {
                m_sommets[i]->setadj(m_aretes[j]->getSommet1());
            }
        }
    }
}
void Graphe::affichercentralite()
{
    for (size_t i=0; i<m_sommets.size(); ++i)
    {
        std::cout<<"indice :"<<m_sommets[i]->getId()<<", centralite degre non normalisee:"<<m_sommets[i]->getcd()<<", centralite degre normalisee:"<<m_sommets[i]->getcdn()<<", centralite proxi :"<<m_sommets[i]->getcp();
        std::cout<<", centralite proxi normalisee:"<<m_sommets[i]->getcpn()<<std::endl;

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

void Graphe::enregistrer(std::ofstream& ofs)
{


}

/*void Graphe::addSommet()
{
    Sommet *s= new Sommet;
    std::cout<<"id : "<<std::endl;
    std::cin>>s->
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
