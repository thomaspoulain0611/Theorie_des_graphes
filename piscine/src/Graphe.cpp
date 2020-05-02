#include "Graphe.h"
#include<queue>
#include<stack>



Graphe::Graphe(std::string nomFichier, std::string nomFichierPoids)
{
    std::ifstream ifs{nomFichier};//
    if(!ifs)// on verifie que le f
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


    std::ifstream is{nomFichierPoids};
    if(!is)// on verifie que le fichier existe
        throw std::runtime_error("Impossible d'ouvrir en lecture" + nomFichier );
    int taille2;
    is>>taille2;
    int indice2;
    int poids;
    for(int i=0; i<taille; ++i)
    {
        is>>indice2>>poids;
        if(indice2==m_aretes[i]->getindice())
            m_aretes[i]->setPoids(poids);
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

void Graphe::enregistrer()
{
    std::string nomFichier;
//    this->rempliradj();
    // this->poidsarete(nomFichier);
    this->centralitedegre();
    this->centralitedegreN();
    this->centraliteproxi();
    this->centraliteproxiN();

    std::ofstream ofs{"sauvegarde.txt"};
    if(!ofs)
    {
        std::cerr<<"Erreur  d'ouverture du fichier"<<std::endl;
    }
    else
    {
        for (size_t i=0; i<m_sommets.size(); ++i)
        {
            if(m_sommets[i]->getcp()!=0)
                ofs<<"id: "<<m_sommets[i]->getId()<<"| cd: "<<m_sommets[i]->getcd()<<"| cdn: "<<m_sommets[i]->getcdn()<<"| cp: "<<m_sommets[i]->getcp()<<"| cpn: "<<m_sommets[i]->getcpn()<<std::endl;
            else
                ofs<<"id: "<<m_sommets[i]->getId()<<"| cd: "<<m_sommets[i]->getcd()<<"| cdn: "<<m_sommets[i]->getcdn()<<"| cp: incalculable | cpn: incalculable"<<std::endl;
        }
    }
}

/*void Graphe::poidsarete (std::string nomFichier)

{
    for(size_t i=0; i<m_aretes.size(); ++i)
    {
        m_aretes[i]->assimpoids(nomFichier);
    }
}*/

void Graphe::centralitedegre()
{

    //this->rempliradj();
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

        }

    }

    return poids;

}

Sommet*Graphe::trouversommetindice(int indice)
{
    Sommet*s1;
    for(size_t i=0; i<m_sommets.size(); ++i)
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

    nb=S->get_nb_adj();//on recupère le nombre de successeurs du sommet parcour
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
    return dist;
}
/*double Graphe::distanceproxi(std::vector<int> nouv,int depart, int arrivee)
{

    int pred=0;
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

}*/


void Graphe::centraliteproxi()
{
    int i;
    double cp;
    i=this->nb_comp_connexe(1);

    if (i==1)
    {

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
                //ideal:: dijkstraproxi(m_sommets[i],m_sommets[j
            }
            cp=1/cp;
            m_sommets[i]->setcp(cp);
        }
    }
    else
        for(size_t i=0; i<m_sommets.size(); i++)
        {
            m_sommets[i]->setcp(0);
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

void Graphe::centralitevp()
{


    double temp=0;
    double tampon;

    int q=0;
    std::vector<double>lambda;



    for(size_t i=0; i<m_sommets.size(); ++i)
    {
        m_sommets[i]->setcvp(1);
    }

    for (size_t l=0;l<10000;++l)
    {
        lambda.push_back(0);
    }



    do

    {
        lambda[q]=0;
        for(size_t i=0; i<m_sommets.size(); ++i)
        {
            temp=0;
            for(size_t j=0; j<m_sommets[i]->get_nb_adj(); ++j)
            {
                temp+=m_sommets[i]->get_adj(j)->getcvp();



            }
           // std::cout<<"temp ="<<temp<<std::endl;
            m_sommets[i]->setcsi(temp);


        }
        for (size_t k=0; k<m_sommets.size(); ++k)
        {
            lambda[q]+=pow(m_sommets[k]->getcsi(),(2));
        }

        lambda[q]=sqrt(lambda[q]);
        std::cout<<"lambda :"<<lambda[q]<<std::endl;

        for (size_t i=0; i<m_sommets.size(); ++i)
        {
            m_sommets[i]->setcvp((m_sommets[i]->getcsi())/lambda[q]);
            //std::cout<<"cvp "<<i<<":"<< m_sommets[i]->getcvp()<<std::endl;
        }

        q++;
        std::cout<<"i="<<q<<std::endl;
        tampon=lambda[q-1]-lambda[q-2];
        std::cout<<" tampon="<<tampon<<std::endl;

    }while ((q<2)||((tampon>0.001)||(tampon<-0.001)));
    for (size_t i=0;i<m_sommets.size();++i)
    {
        std::cout<<"csi :"<<m_sommets[i]->getcsi()<<std::endl;
        std::cout<<"cvp :"<<m_sommets[i]->getcvp()<<std::endl;
    }

}

int Graphe::dijkstrainter1pcc( int depart, int arrivee, int sparcouru)
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

    nb=S->get_nb_adj();//on recupère le nombre de successeurs du sommet parcour
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



    int pred=0;
    int presence=0;

    for(size_t i=0; i<I_preds.size(); ++i) // on parcourt tous les prédecesseurs
    {
        if((int)i==arrivee)// si numero case correspond au sommet d'arrivée
        {
            std::cout<<i;
             // on affiche le sommet d'arrivée
            pred=I_preds[i];//on note son predecesseur


            while(pred!=depart)// tant que le prédecesseur n'est pas le sommet de départ
            {

                std::cout<<"<--"<<pred;// on affiche "<--"
                 if (pred==sparcouru)
                {
                    presence=1;
                }


                pred=I_preds[pred];// predecesseur prend la valeur du predecesseur du sommet alors traité




            }
              std::cout<<"<--"<<depart<<std::endl;



            //affichage poids
            //pred=nouveau[i];// on remet à pred la valeur du prédecesseur de notre nombre d'arrivée
            /*int parcours=pred;// on initialise le sommet parcours et la somme(longueur chemin)


            while(parcours!=depart)// tant que parcours est différent de départ
            {
                pred=nouveau[parcours];// on assimile à pred la valeur du prédecesseur du sommet étudié



                parcours=pred;//maj du sommet parcouru*/
            }



        }
          std::cout<<"presence ="<<presence<<std::endl;
    return presence;





}





void Graphe::centraliteinter1pcc()

{
    int p;
    double ci1;

    p=this->nb_comp_connexe(1);


    if ((p==1) && (m_sommets.size()>2))// on verifie qye la composante est connexe et que le graphe comporte au moins trois sommets
    {
        for (size_t i=0; i<m_sommets.size(); ++i) // on parcourt tous les sommets et c'est la valeur de ci1 de m_sommets[i]que l'on va determiner
        {
            ci1=0;
            for (size_t j=0; j<m_sommets.size(); ++j)
            {
                for (size_t k=0; k<m_sommets.size(); ++k)
                {
                    if ((m_sommets[j]->getId())<(m_sommets[k]->getId()) &&(m_sommets[i]->getId()!=m_sommets[j]->getId())&&(m_sommets[i]->getId()!=m_sommets[k]->getId()))
                    {



std::cout<<" sommet de depart: "<<m_sommets[j]->getId()<<" sommet d'arrivee: "<<m_sommets[k]->getId()<<" sommet etudie "<<m_sommets[i]->getId()<<std::endl;
                        //preds=dijkstrainter1pcc(m_sommets[j]->getId(),m_sommets[k]->getId(),m_sommets[i]->getId());
                        //ci1+=affichagePCC(preds,m_sommets[j]->getId(),m_sommets[k]->getId(),m_sommets[i]->getId());
                        ci1+=dijkstrainter1pcc(m_sommets[j]->getId(),m_sommets[k]->getId(),m_sommets[i]->getId());

                    }


                }
            }
            m_sommets[i]->setci1(ci1);
            std::cout<< "sommet "<<m_sommets[i]->getId()<<" ci1 ="<< m_sommets[i]->getci1()<<std::endl;


        }

    }
    else
        for(size_t i=0; i<m_sommets.size(); i++)
        {
            m_sommets[i]->setcp(-1);
        }
}

void Graphe::centraliteinter1Npcc()
{
     double ci1N=0;
    for (size_t i=0; i<m_sommets.size(); ++i)
    {
        ci1N=0;

        ci1N=m_sommets[i]->getci1();


        m_sommets[i]->setci1n((2*ci1N)/(pow((double)m_sommets.size(),2)-3*(double)m_sommets.size()+2));
        std::cout<<" affichage ci1N :"<<m_sommets[i]->getci1n();

    }

}

int Graphe::isNotVisited(int x, std::vector<int>& path)
{

    for (size_t i = 0; i < path.size(); i++)
        if (path[i] == x)
            return 0;
    return 1;
}


double Graphe::presencesparcouru(int depart, int arrivee, int sparcouru,double distance)
{
    std::queue<std::vector<int>>touschemins;

    Sommet*S;
    Sommet*S1;
    double poidschemin=0;
    double presence=0;
    double ci;
    std::vector<int>chemin;
    chemin.push_back(depart);
    double compteurpcc=0;
    int id; //chaque chemin devra aller du depart donc on le push_back

    touschemins.push(chemin);
    while (!touschemins.empty())
        {

        chemin = touschemins.front();
        touschemins.pop();
        int last = chemin[chemin.size() - 1];

        // if last vertex is the desired destination
        // then print the path
        if (last == arrivee)
        {
            poidschemin=0;

            for (size_t i=0;i<chemin.size()-1;++i)
            {

                poidschemin+=trouverpoids(chemin[i],chemin[i+1]);

            }


            if (poidschemin==distance)
            {
                compteurpcc++;
                for (size_t i=0;i<chemin.size();++i)
                {
                    if (chemin[i]==sparcouru)
                        presence++;
                }

            }





        }
        S=trouversommetindice(last);

        // traverse to all the nodes connected to
        // current vertex and push new path to queue
        for (double i = 0; i < S->get_nb_adj(); ++i)
            {

                S1=S->get_adj(i);
                id=S1->getId();
            if (isNotVisited(id, chemin))

             {
                std::vector<int> newpath(chemin);

                id=S1->getId();

                newpath.push_back(id);
                touschemins.push(newpath);



             }
            }
    }

    ci=presence/compteurpcc;

    return ci;
    //return cheminsdepartarrivee;
}



void Graphe::centraliteinter()
{

    int p;
    double ci;
    double distance;
    std::vector<std::vector<int>> chemins;
    std::vector<std::vector<int>>pluscourtschemins;


    p=this->nb_comp_connexe(1);


    if ((p==1) && (m_sommets.size()>2))// on verifie qye la composante est connexe et que le graphe comporte au moins trois sommets
    {
        for (size_t i=0; i<m_sommets.size(); ++i) // on parcourt tous les sommets et c'est la valeur de ci1 de m_sommets[i]que l'on va determiner
        {
            ci=0;
            for (size_t j=0; j<m_sommets.size(); ++j)
            {

                for (size_t k=0; k<m_sommets.size(); ++k)
                {
                    if ((m_sommets[j]->getId())<(m_sommets[k]->getId()) &&(m_sommets[i]->getId()!=m_sommets[j]->getId())&&(m_sommets[i]->getId()!=m_sommets[k]->getId()))
                    {





                        distance=dijkstraproxi(m_sommets[j]->getId(),m_sommets[k]->getId());
                        ci+=presencesparcouru(m_sommets[j]->getId(),m_sommets[k]->getId(),m_sommets[i]->getId(),distance);

                        //chemins=trouvertouschemins(m_sommets[j]->getId(),m_sommets[k]->getId());
                        //pluscourtschemins=pcc(chemins,distance);
                        // programme permettant de

                    }


                }
            }
            m_sommets[i]->setci(ci);
            std::cout<< "sommet "<<m_sommets[i]->getId()<<" ci ="<< m_sommets[i]->getci()<<std::endl;


        }

    }
    else
        for(size_t i=0; i<m_sommets.size(); i++)
        {
            m_sommets[i]->setci(-1);
        }
}



void Graphe::centraliteinterN()
{
    double ciN=0;
    for (size_t i=0; i<m_sommets.size(); ++i)
    {
        ciN=0;

        ciN=m_sommets[i]->getci();


        m_sommets[i]->setciN((2*ciN)/(pow((double)m_sommets.size(),2)-3*(double)m_sommets.size()+2));
        std::cout<<" affichage ci1N :"<<m_sommets[i]->getciN();

    }

}

/*void Graphe::rempliradj()
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
}*/

void Graphe::affichercentralite()
{
    for (size_t i=0; i<m_sommets.size(); ++i)
    {
        SetConsoleTextAttribute(hConsole, 15);
        std::cout<<std::endl<<"indice : "<<m_sommets[i]->getId()<<std::endl;
        std::cout<<"centralite degre non normalisee : "<<m_sommets[i]->getcd()<<std::endl;
        std::cout<<"centralite degre normalisee : "<<m_sommets[i]->getcdn()<<std::endl;
        if(m_sommets[i]->getcp()==0)
        {
            SetConsoleTextAttribute(hConsole, 12);
            std::cout<<"impossible de calculer centralite proxi et centralite proxi normalisee car graphe non connexe "<<std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else
        {
            std::cout<<"centralite proxi : "<<m_sommets[i]->getcp()<<std::endl;
            std::cout<<"centralite proxi normalisee : "<<m_sommets[i]->getcpn()<<std::endl;
        }
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
void Graphe::deleteArete( std::vector<int> id)
{
    int s1,s2;
    int nbConnex;
    std::vector<Sommet*> vect1, vect2;
    for (size_t x=0; x<id.size(); x++)
    {
        for(size_t i=0; i<m_aretes.size(); i++)
        {
            if(m_aretes[i]->getindice()==id[x])
            {
                s1=m_aretes[i]->getindiceS1();
                s2=m_aretes[i]->getindiceS2();
                for(size_t j=0; j<m_sommets.size(); j++)
                {
                    if(m_sommets[j]->getId()==s1)
                    {
                        for(size_t k=0; k<m_sommets[j]->get_nb_adj(); k++)
                        {
                            if(m_sommets[j]->get_adj(k)->getId()==s2)
                            {
                                vect1=m_sommets[j]->getAdj();
                                vect1.erase(vect1.begin()+k);
                                m_sommets[j]->setVectAdj(vect1);
                            }
                        }
                    }
                    if(m_sommets[j]->getId()==s2)
                    {
                        for(size_t k=0; k<m_sommets[j]->get_nb_adj(); k++)
                        {
                            if(m_sommets[j]->get_adj(k)->getId()==s1)
                            {
                                vect2=m_sommets[j]->getAdj();
                                vect2.erase(vect2.begin()+k);
                                m_sommets[j]->setVectAdj(vect2);
                            }
                        }
                    }
                }
            }
        }
    }
    nbConnex=this->nb_comp_connexe(1);
    if(nbConnex==1)
    {
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<std::endl<<"Le graphe ne devient pas vulnerable si vous supprimez cette arete"<<std::endl;
    }
    else
    {
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<std::endl<<"Le graphe devient vulnerable si vous supprimez cette arete"<<std::endl;
    }
}

void Graphe::deleteAreteIndice(std::vector<int> id)
{
    std::string nomFichier;
    std::vector<double> vect_cd;
    std::vector<double> vect_cdn;
    std::vector<double> vect_cp;
    std::vector<double> vect_cpn;
    std::vector<int> vect_id;

    //this->poidsarete(nomFichier);
    this->centralitedegre();
    this->centralitedegreN();
    this->centraliteproxi();
    this->centraliteproxiN();
    //this->centralitevp();

    for(size_t i=0; i<m_sommets.size(); i++)
    {
        vect_cd.push_back(m_sommets[i]->getcd());
        vect_cdn.push_back(m_sommets[i]->getcdn());
        vect_cp.push_back(m_sommets[i]->getcp());
        vect_cpn.push_back(m_sommets[i]->getcpn());
        vect_id.push_back(m_sommets[i]->getId());
    }

    int s1,s2;
    std::vector<Sommet*> vect1, vect2;
    for (size_t x=0; x<id.size(); x++)
    {
        for(size_t i=0; i<m_aretes.size(); i++)
        {
            if(m_aretes[i]->getindice()==id[x])
            {
                s1=m_aretes[i]->getindiceS1();
                s2=m_aretes[i]->getindiceS2();
                for(size_t j=0; j<m_sommets.size(); j++)
                {
                    if(m_sommets[j]->getId()==s1)
                    {
                        for(size_t k=0; k<m_sommets[j]->get_nb_adj(); k++)
                        {
                            if(m_sommets[j]->get_adj(k)->getId()==s2)
                            {
                                vect1=m_sommets[j]->getAdj();
                                vect1.erase(vect1.begin()+k);
                                m_sommets[j]->setVectAdj(vect1);
                            }
                        }
                    }
                    if(m_sommets[j]->getId()==s2)
                    {
                        for(size_t k=0; k<m_sommets[j]->get_nb_adj(); k++)
                        {
                            if(m_sommets[j]->get_adj(k)->getId()==s1)
                            {
                                vect2=m_sommets[j]->getAdj();
                                vect2.erase(vect2.begin()+k);
                                m_sommets[j]->setVectAdj(vect2);
                            }
                        }
                    }
                }
            }
        }
    }

    //this->poidsarete(nomFichier);
    this->centralitedegre();
    this->centralitedegreN();
    this->centraliteproxi();
    this->centraliteproxiN();
    //this->centralitevp();

    for(size_t i=0; i<m_sommets.size(); i++)
    {
        SetConsoleTextAttribute(hConsole, 15);
        std::cout<<std::endl<<"indices de depart : "<<std::endl;
        std::cout<<"indice du sommet : "<<vect_id[i]<<std::endl;
        std::cout<<"indice centralite degre non normalise : "<<vect_cd[i]<<std::endl;
        std::cout<<"indice centralite degre nomalise : "<<vect_cdn[i]<<std::endl;
        if(vect_cp[i]==0)
        {
            SetConsoleTextAttribute(hConsole, 12);
            std::cout<<"impossible de calculer centralite proxi et centralite proxi normalise car graphe non connexe "<<std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else
        {
            std::cout<<"indice centralite proxi non normalise : "<<vect_cp[i]<<std::endl;
            std::cout<<"indice centralise proxi normalise : "<<vect_cpn[i]<<std::endl;
        }
        std::cout<<std::endl<<"indices apres suppression : "<<std::endl;
        std::cout<<"indice du sommet : "<<m_sommets[i]->getId()<<std::endl;
        std::cout<<"indice centralite degre non normalise : "<<m_sommets[i]->getcd()<<std::endl;
        std::cout<<"indice centralite degre nomalise : "<<m_sommets[i]->getcdn()<<std::endl;
        if(m_sommets[i]->getcp()==0)
        {
            SetConsoleTextAttribute(hConsole, 12);
            std::cout<<"impossible de calculer centralite proxi et centralite proxi normalise car graphe non connexe "<<std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else
        {
            std::cout<<"indice centralite proxi non normalise : "<<m_sommets[i]->getcp()<<std::endl;
            std::cout<<"indice centralise proxi normalise : "<<m_sommets[i]->getcpn()<<std::endl;
        }
        std::cout<<std::endl<<"Comparaisons apres suppression : "<<std::endl;
        std::cout<<"indice du sommet : "<<m_sommets[i]->getId()<<std::endl;
        std::cout<<"difference centralite degre non normalise : "<<vect_cd[i]-m_sommets[i]->getcd()<<std::endl;
        std::cout<<"difference centralite degre normalise : "<<vect_cdn[i]-m_sommets[i]->getcdn()<<std::endl;
        if(m_sommets[i]->getcp()==0 && vect_cp[i]!=0)
        {
            SetConsoleTextAttribute(hConsole, 12);
            std::cout<<std::endl<<"La suppression de l'arete a rendu le graphe non connexe"<<std::endl;
            std::cout<<"l'indice de centralite proxi du sommet "<<m_sommets[i]->getId()<<" n'est donc plus calculable alors qu'il avait pour valeur "<<vect_cp[i]<<std::endl;
            std::cout<<"de meme pour l'indice de centralite proxi normalise"<<std::endl<<std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else if(vect_cp[i]==0)
        {
            SetConsoleTextAttribute(hConsole, 12);
            std::cout<<std::endl<<"Les differences des 2 indices de centralite proxi ne sont pas calculables car le graphe"<<std::endl;
            std::cout<<" n'etait pas connexe de base"<<std::endl<<std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else
        {
            std::cout<<"difference centralite degre proxi non normalise : "<<vect_cp[i]-m_sommets[i]->getcp()<<std::endl;
            std::cout<<"difference centralite degre proxi normalise : "<<vect_cpn[i]-m_sommets[i]->getcpn()<<std::endl;
        }
    }
}

std::vector<int> Graphe::bfs (int id)//recupère sommet de départ et retourne vecteur de prédécesseurs
{
    int sommet=-6;
    std::vector<int> I_preds;//I_preds[i] donne le prédécesseur du sommet i
    std::queue<int> file;//file déclaration
    int adj=0;
    size_t nb=0;
    Sommet* S=nullptr;
    //on met tous les sommets en blanc: non parcourus
    for(size_t i=0; i<m_sommets.size(); ++i)
    {
        m_sommets[i]->set_color('B');
    }
    //on crée un vecteur de predecesseurs avec chaque case initialisée à -1
    for(size_t y=0; y<m_sommets.size(); ++y)
    {
        I_preds.push_back(-1);
    }
    S=trouversommetindice(id);
    //on ajoute le sommet initial à la file et on le colorie en gris
    sommet=id;
    file.push(sommet);
    S->set_color('G');
    while(!file.empty())//tant que la file n'est pas vide
    {
        S=trouversommetindice(sommet);
        nb=S->get_nb_adj();//on recupère le nombre de successeurs du sommet parcouru
        file.pop();//on supprime premier élément de la file
        for(size_t i=0; i<nb; ++i)//tant que successeur
        {
            S=trouversommetindice(sommet);
            adj=S->get_adj(i)->getId();//on récupère valeur du successeur i
            S=trouversommetindice(adj);
            if(S->get_color()=='B')//s'il n'a pas été parcouru, on le met en gris
            {
                S->set_color('G');
                I_preds.at(adj)=sommet;//sommet est son predecesseur
                file.push(adj);//on l'ajoute à la file
            }
        }
        S=trouversommetindice(sommet);
        S->set_color('N');//sommet parcouru donc noir
        if(!file.empty())//si la file n'est pas vide
            sommet=file.front();//le sommet de parcours est le sommet en tête de file
    }
    return I_preds;//on retourne le vecteur affectant à chaque sommet un prédécesseur (case 0: prédécesseur du sommet 0, etc)
}

int Graphe::nb_comp_connexe(int idSommet)
{

    //déclaration et initialisation des variables
    std::vector<int> composante;//pour stocker tous les sommets découverts dans une composante
    std::vector<int> I_preds;//vecteur des prédécesseurs
    int j=1;
    bool s;
    do//tant qu'il y a des sommets non découverts
    {
        s=false;//on part du principe que tout a été découvert
        I_preds=bfs(idSommet);//parcours bfs à partir d'un sommet pour marquer sommets de sa composante
        SetConsoleTextAttribute(hConsole, 8);
        std::cout<<std::endl<<"composante connexe "<<j<<" : ";
        //on cherche dans le vecteur I_preds tous les sommets de la composante de sommet après découverte par bfs
        for(size_t i=0; i<I_preds.size(); ++i)
        {
            if((I_preds[i]!=-1)||((int)i==idSommet))//s'il sagit du sommet de départ ou de sommets de sa composante
            {
                composante.push_back(i);//sommet découvert
                SetConsoleTextAttribute(hConsole, 8);
                std::cout<<i<<" ";
            }
        }
        ++j;//incrémente pour jième composante
        I_preds.clear();//vide le vecteur
        for(size_t w=0; w<m_sommets.size(); ++w)//pour chaque sommet du graphe
        {
            int compt=0;
            if((m_sommets[w]->get_color()=='B'))
            {
                for(size_t h=0; h<composante.size(); ++h)//on cherche si ce sommet a été découvert avant
                {
                    if((int)w!=composante[h])
                        ++compt;
                }
                if(compt==(int)composante.size())//si le sommet n'a jamais été découvert lors des parcours précédents
                {
                    s=true;//il reste des sommets non marqués
                    idSommet=w;//le nouveau sommet de parcours est ce sommet non marqué
                    w=m_sommets.size();//on sort de la boucle
                }
            }
        }
    }
    while(s);//tant qu'il reste des sommets non découvert
    std::cout<<std::endl;

    return j-1;
}

void Graphe::dessinerTous(int& nom, int& poids, int& cdn, int& cd, int& cpn, int& cp)
{
    Svgfile svgout;
    std::vector<double> vect_cd;
    std::vector<double> vect_cdn;
    std::vector<double> vect_cp;
    std::vector<double> vect_cpn;
    std::string nomFichier;

//    this->rempliradj();
    // this->poidsarete(nomFichier);
    this->centralitedegre();
    this->centralitedegreN();
    this->centraliteproxi();
    this->centraliteproxiN();

    for(size_t i=0; i<m_sommets.size(); i++)
    {
        vect_cd.push_back(m_sommets[i]->getcd());
        vect_cdn.push_back(m_sommets[i]->getcdn());
        vect_cp.push_back(m_sommets[i]->getcp());
        vect_cpn.push_back(m_sommets[i]->getcpn());
    }
    for(size_t i=0; i<m_sommets.size(); i++)
    {
        m_sommets[i]->dessiner(svgout);
        for(size_t j=0; j<m_aretes.size(); j++)
        {
            m_aretes[j]->dessiner(svgout);
        }
    }
    if(nom==1)
    {
        for(size_t i=0; i<m_sommets.size(); i++)
        {
            m_sommets[i]->ecrireNom(svgout);
        }
    }
    if(poids==1)
    {
        for(size_t i=0; i<m_aretes.size(); i++)
        {
            m_aretes[i]->ecrirePoids(svgout);
        }
    }
    if (cdn==1)
    {
        for (size_t i=0; i<m_sommets.size(); ++i)
        {
            if(m_sommets[i]->getcdn()==*std::max_element(vect_cdn.begin(), vect_cdn.end()))
                m_sommets[i]->dessinerMarque(svgout);
            m_sommets[i]->ecrireCentraliteDegreN(svgout);
        }
    }

    if (cd==1)
    {
        for (size_t i=0; i<m_sommets.size(); ++i)
        {
            if(m_sommets[i]->getcd()==*std::max_element(vect_cd.begin(), vect_cd.end()))
                m_sommets[i]->dessinerMarque(svgout);
            m_sommets[i]->ecrireCentraliteDegre(svgout);
        }
    }

    if (cpn==1)
    {
        for (size_t i=0; i<m_sommets.size(); ++i)
        {
            if(m_sommets[i]->getcpn()==*std::max_element(vect_cpn.begin(), vect_cpn.end()))
                m_sommets[i]->dessinerMarque(svgout);
            m_sommets[i]->ecrireCentralitePN(svgout);
        }
    }

    if (cp==1)
    {
        for (size_t i=0; i<m_sommets.size(); ++i)
        {
            if(m_sommets[i]->getcp()==*std::max_element(vect_cp.begin(), vect_cp.end()))
                m_sommets[i]->dessinerMarque(svgout);
            m_sommets[i]->ecrireCentraliteP(svgout);
        }
    }
}
