#include "Graphe.h"
#include<queue>
#include<stack>



Graphe::Graphe( std::string fichier, std::string fichierPoids)
{
    int taille2;
    int taille;
    std::ifstream ifs(fichier);

    if(!ifs)
    {
        SetConsoleTextAttribute(hConsole, 12);
        std::cout<<"Saisie du fichier graphe incorrecte"<<std::endl;
        std::cout<<"Appuyer sur exit pour recommencer"<<std::endl;
        SetConsoleTextAttribute(hConsole, 15);

    }
    else
    {
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
        ifs>>taille;
        if (ifs.fail() )
            throw std::runtime_error("Erreur de lecture de la taille");
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
    }
    std::ifstream is(fichierPoids);
    if(!is)
    {
        SetConsoleTextAttribute(hConsole, 12);
        std::cout<<"Saisie du fichier poids incorrecte"<<std::endl;
        std::cout<<"Appuyer sur (exit) ou (changer fichier poids) pour recommencer "<<std::endl;
    }
    else
    {
        is>>taille2;
        int indice2;
        double poids;
        for(int i=0; i<taille2; ++i)
        {
            is>>indice2>>poids;
            if(indice2==m_aretes[i]->getindice())
                m_aretes[i]->setPoids(poids);
        }
    }
}

Graphe::~Graphe()
{
    for (auto s : m_sommets)
        delete s;
    for (auto s : m_aretes)
        delete s;
}

int Graphe::getOrient()const
{
    return m_orient;
}

int Graphe::getOrdre()const
{
    return (int)m_sommets.size();
}

int Graphe::getTaille()const
{
    return (int)m_aretes.size();
}

void Graphe::enregistrer()
{
    std::string nomFichier;
    this->centralitedegre();
    this->centralitedegreN();
    this->centraliteproxi();
    this->centraliteproxiN();
    this->centralitevp();
    this->centraliteinter();
    this->centraliteinterN();

    std::ofstream ofs{"sauvegarde.txt"};
    if(!ofs)
    {
        std::cerr<<"Erreur  d'ouverture du fichier"<<std::endl;
    }
    else
    {
        for (size_t i=0; i<m_sommets.size(); ++i)
        {
            if(m_sommets[i]->getcp()!=0 && m_sommets[i]->getci()!=-1)
                ofs<<"id: "<<m_sommets[i]->getId()<<"| cd: "<<m_sommets[i]->getcd()<<"| cdn: "<<m_sommets[i]->getcdn()<<"| cvp: "<<m_sommets[i]->getcvp()<<"| cp: "<<m_sommets[i]->getcp()<<"| cpn: "<<m_sommets[i]->getcpn()<<"| ci: "<<m_sommets[i]->getci()<<"| cin: "<<m_sommets[i]->getciN()<<std::endl;
            else if(m_sommets[i]->getcp()==0)
                ofs<<"id: "<<m_sommets[i]->getId()<<"| cd: "<<m_sommets[i]->getcd()<<"| cdn: "<<m_sommets[i]->getcdn()<<"| cvp: "<<m_sommets[i]->getcvp()<<"| cp: incalculable | cpn: incalculable"<<"| ci: "<<m_sommets[i]->getci()<<"| cin: "<<m_sommets[i]->getciN()<<std::endl;
            else if(m_sommets[i]->getci()==-1)
                ofs<<"id: "<<m_sommets[i]->getId()<<"| cd: "<<m_sommets[i]->getcd()<<"| cdn: "<<m_sommets[i]->getcdn()<<"| cvp: "<<m_sommets[i]->getcvp()<<"| cp: "<<m_sommets[i]->getcp()<<"| cpn: "<<m_sommets[i]->getcpn()<<"| ci: incalculable | cin: incalculable "<<std::endl;
        }
    }
}

void Graphe::centralitedegre()
{
    for(size_t i=0; i<m_sommets.size(); ++i)
    {
        m_sommets[i]->setcd((double)m_sommets[i]->get_nb_adj());
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

void Graphe::centraliteproxi()
{
    int i;
    double cp;
    i=this->nb_comp_connexe(m_sommets[0]->getId());

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
                }
            }
            cp=1/cp;
            m_sommets[i]->setcp(cp);
        }
    }
    else
        for(size_t i=0; i<m_sommets.size(); i++)
        {
            m_sommets[i]->setcp(-1);
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
    for (size_t l=0; l<10000; ++l)
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
            m_sommets[i]->setcsi(temp);
        }
        for (size_t k=0; k<m_sommets.size(); ++k)
        {
            lambda[q]+=pow(m_sommets[k]->getcsi(),(2));
        }
        lambda[q]=sqrt(lambda[q]);
        for (size_t i=0; i<m_sommets.size(); ++i)
        {
            m_sommets[i]->setcvp((m_sommets[i]->getcsi())/lambda[q]);
        }
        q++;
        tampon=lambda[q-1]-lambda[q-2];
    }
    while ((q<2)||((tampon>0.001)||(tampon<-0.001)));
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
        }
        std::cout<<"presence ="<<presence<<std::endl;
    }
    return presence;
}

void Graphe::centraliteinter1pcc()
{
    int p;
    double ci1;

    p=this->nb_comp_connexe(m_sommets[0]->getId());

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
                        ci1+=dijkstrainter1pcc(m_sommets[j]->getId(),m_sommets[k]->getId(),m_sommets[i]->getId());
                    }
                }
            }
            m_sommets[i]->setci1(ci1);
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
    }
}

int Graphe::pasParcouru(int x, std::vector<int>& chemin)
{

    for (size_t i = 0; i < chemin.size(); ++i)
        if (chemin[i] == x)
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

        int dernier = chemin[chemin.size() - 1];

        // if last vertex is the desired destination
        // then print the path
        if (dernier == arrivee)

        {
            poidschemin=0;
            for (size_t i=0; i<chemin.size()-1; ++i)
            {
                poidschemin+=trouverpoids(chemin[i],chemin[i+1]);
            }
            if (poidschemin==distance)
            {
                compteurpcc++;
                for (size_t i=0; i<chemin.size(); ++i)
                {
                    if (chemin[i]==sparcouru)
                        presence++;
                }
            }
        }

        S=trouversommetindice(dernier);

        // traverse to all the nodes connected to
        // current vertex and push new path to queue
        for (double i = 0; i < S->get_nb_adj(); ++i)
            {

                S1=S->get_adj(i);
                id=S1->getId();
            if (pasParcouru(id, chemin))

             {
                std::vector<int> nvchemin(chemin);

                id=S1->getId();

                nvchemin.push_back(id);
                touschemins.push(nvchemin);
             }
            }
        }
    ci=presence/compteurpcc;
    return ci;
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
                    }
                }
            }
            m_sommets[i]->setci(ci);
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
    }

}

double Graphe::areteparcourue(int depart, int arrivee, int ex1, int ex2,double distance)
{
    std::queue<std::vector<int>>touschemins;

    Sommet*S;
    Sommet*S1;
    double poidschemin=0;
    double presence=0;
    double ciA;
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

            for (size_t i=0; i<chemin.size()-1; ++i)
            {

                poidschemin+=trouverpoids(chemin[i],chemin[i+1]);

            }
            if (poidschemin==distance)
            {
                compteurpcc++;
                for (size_t i=0; i<chemin.size()-1; ++i)
                {

                    if (((chemin[i]==ex1)&&(chemin[i+1]==ex2))||((chemin[i]==ex2)&&(chemin[i+1]==ex1)))
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
            if (pasParcouru(id, chemin))


            {
                std::vector<int> newpath(chemin);

                id=S1->getId();

                newpath.push_back(id);
                touschemins.push(newpath);
            }
        }
    }
    ciA=presence/compteurpcc;
    return ciA;
    //return cheminsdepartarrivee;
}

void Graphe::centraliteinterarete()
{

    int p;
    double ciA;
    double distance;
    std::vector<std::vector<int>> chemins;
    p=this->nb_comp_connexe(m_sommets[0]->getId());
    if ((p==1) && (m_sommets.size()>1))// on verifie qye la composante est connexe et que le graphe comporte au moins une arete
    {
        for (size_t i=0; i<m_aretes.size(); ++i) // on parcourt tous les sommets et c'est la valeur de ci1 de m_sommets[i]que l'on va determiner
        {
            ciA=0;
            for (size_t j=0; j<m_sommets.size(); ++j)
            {

                for (size_t k=0; k<m_sommets.size(); ++k)
                {
                    if ((m_sommets[j]->getId())<(m_sommets[k]->getId()))
                    {
                        distance=dijkstraproxi(m_sommets[j]->getId(),m_sommets[k]->getId());
                        ciA+=areteparcourue(m_sommets[j]->getId(),m_sommets[k]->getId(),m_aretes[i]->getindiceS1(),m_aretes[i]->getindiceS2(),distance);
                    }

                }
            }
            m_aretes[i]->setciA(ciA);

        }

    }
    else
        for(size_t i=0; i<m_aretes.size(); i++)
        {
            m_aretes[i]->setciA(-1);
        }
}

double Graphe::getcpg()const
{
    return m_cpg;
}

void Graphe::setcpg(double cpg)
{
    m_cpg=cpg;
}

void Graphe::recupcpg()
{
    this->centraliteproxi();
    double maximum=0;
    double tampon=0;
    double cpg=0;
    double denominateur=0;
    for(size_t i=0;i<m_sommets.size();++i)
    {
        if (m_sommets[i]->getcp()>maximum)
            maximum=m_sommets[i]->getcp();
    }
    for(size_t i=0;i<m_sommets.size();++i)
    {
        tampon+=i*(maximum-m_sommets[i]->getcp());
    }
    denominateur=(pow((double)m_sommets.size(),2)-3*(double)m_sommets.size()+2)/(2*(double)m_sommets.size()-3);
    cpg=tampon/denominateur;
    this->setcpg(cpg);
}

void Graphe::affichercentralite()
{
    for (size_t i=0; i<m_sommets.size(); ++i)
    {
        SetConsoleTextAttribute(hConsole, 15);
        std::cout<<std::endl<<"nom : "<<m_sommets[i]->getNom()<<std::endl;
        std::cout<<"centralite degre non normalisee : "<<m_sommets[i]->getcd()<<std::endl;
        std::cout<<"centralite degre normalisee : "<<m_sommets[i]->getcdn()<<std::endl;
        std::cout<<"centralitte vecteur propre : "<<m_sommets[i]->getcvp()<<std::endl;
        if(m_sommets[i]->getcp()==-1)
        {
            SetConsoleTextAttribute(hConsole, 12);
            std::cout<<"impossible de calculer centralite proxi et centralite proxi normalisee car graphe non connexe "<<std::endl;
            std::cout<<"impossible de calculer centralite global proxi car graphe non connexe "<<std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else
        {
            std::cout<<"centralite proxi : "<<m_sommets[i]->getcp()<<std::endl;
            std::cout<<"centralite proxi normalisee : "<<m_sommets[i]->getcpn()<<std::endl;

        }
        if(m_sommets[i]->getci()==-1)
        {
            SetConsoleTextAttribute(hConsole, 12);
            std::cout<<"impossible de calculer centralite intermediarite et centralite intermediarite normalisee car graphe non connexe "<<std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else
        {
            std::cout<<"centralite intermediarite : "<<m_sommets[i]->getci()<<std::endl;
            std::cout<<"centralite intermediarite normalisee : "<<m_sommets[i]->getciN()<<std::endl;
        }

    }
    std::cout<<std::endl;
    for(size_t j=0; j<m_aretes.size(); j++)
    {
        if(m_aretes[j]->getciA()==-1)
        {
            SetConsoleTextAttribute(hConsole, 12);
            std::cout<<"impossible de calculer centralite intermediarite arete "<<std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else
        {

            std::cout<<"arete : "<<m_aretes[j]->trouverNomS1()<<"--"<<m_aretes[j]->trouverNomS2()<<std::endl;
            std::cout<<"centralite intermediarite arete : "<<m_aretes[j]->getciA()<<std::endl;
        }
    }
    std::cout<<std::endl<<"l'indice de centralite de proximite globale du graphe est : "<<this->getcpg()<<std::endl;
}


void Graphe::deleteArete( std::vector<int> id)
{
    Svgfile svgout;
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

    int compteur=0;
    for(size_t i=0; i<m_sommets.size(); i++)
    {
        m_sommets[i]->dessiner(svgout);
        m_sommets[i]->ecrireNom(svgout);
    }
    for(size_t p=0; p<m_aretes.size(); p++)
    {
        compteur=0;
        for(size_t j=0; j<id.size(); j++)
        {
            if(m_aretes[p]->getindice()==id[j])
                {
                    compteur++;
                }
        }
        if(compteur==0)
            m_aretes[p]->dessiner(svgout);
    }
    nbConnex=this->nb_comp_connexe(m_sommets[0]->getId());

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
    Svgfile svgout;
    std::string nomFichier;
    std::vector<double> vect_cd;
    std::vector<double> vect_cdn;
    std::vector<double> vect_cp;
    std::vector<double> vect_cpn;
    std::vector<double> vect_cvp;
    std::vector<double> vect_ci;
    std::vector<double> vect_cin;

    std::vector<std::string> vect_nom;

    this->centralitedegre();
    this->centralitedegreN();
    this->centraliteproxi();
    this->centraliteproxiN();
    this->centralitevp();
    this->centraliteinter();
    this->centraliteinterN();
    this->recupcpg();
    SetConsoleTextAttribute(hConsole, 15);
    std::cout<<std::endl<<"l'indice de centralite de proximite globale du graphe avant suppression est : "<<this->getcpg()<<std::endl;

    for(size_t i=0; i<m_sommets.size(); i++)
    {
        vect_cd.push_back(m_sommets[i]->getcd());
        vect_cdn.push_back(m_sommets[i]->getcdn());
        vect_cp.push_back(m_sommets[i]->getcp());
        vect_cpn.push_back(m_sommets[i]->getcpn());
        vect_cvp.push_back(m_sommets[i]->getcvp());
        vect_ci.push_back(m_sommets[i]->getci());
        vect_cin.push_back(m_sommets[i]->getciN());
        vect_nom.push_back(m_sommets[i]->getNom());
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
    int compteur=0;
    for(size_t i=0; i<m_sommets.size(); i++)
    {
        m_sommets[i]->dessiner(svgout);
        m_sommets[i]->ecrireNom(svgout);
    }
    for(size_t p=0; p<m_aretes.size(); p++)
    {
        compteur=0;
        for(size_t j=0; j<id.size(); j++)
        {
            if(m_aretes[p]->getindice()==id[j])
                {
                    compteur++;
                }
        }
        if(compteur==0)
            m_aretes[p]->dessiner(svgout);
    }
    this->centralitedegre();
    this->centralitedegreN();
    this->centraliteproxi();
    this->centraliteproxiN();
    this->centralitevp();
    this->centraliteinter();
    this->centraliteinterN();
    this->recupcpg();

    for(size_t i=0; i<m_sommets.size(); i++)
    {
        SetConsoleTextAttribute(hConsole, 15);
        std::cout<<std::endl<<"indices de depart : "<<std::endl;
        std::cout<<"nom du sommet : "<<vect_nom[i]<<std::endl;
        std::cout<<"indice centralite degre non normalise : "<<vect_cd[i]<<std::endl;
        std::cout<<"indice centralite degre nomalise : "<<vect_cdn[i]<<std::endl;
        std::cout<<"indice centralite vecteur propre : "<<vect_cvp[i]<<std::endl;
        if(vect_cp[i]==-1)
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
        if(vect_ci[i]==-1)
        {
            SetConsoleTextAttribute(hConsole, 12);
            std::cout<<"impossible de calculer centralite intermideriarite et centralite intermediarite normalise car graphe non connexe "<<std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else
        {
            std::cout<<"indice centralite intermediarite non normalise : "<<vect_ci[i]<<std::endl;
            std::cout<<"indice centralise intermediarite normalise : "<<vect_cin[i]<<std::endl;
        }
        std::cout<<std::endl<<"indices apres suppression : "<<std::endl;
        std::cout<<"nom du sommet : "<<m_sommets[i]->getNom()<<std::endl;
        std::cout<<"indice centralite degre non normalise : "<<m_sommets[i]->getcd()<<std::endl;
        std::cout<<"indice centralite degre nomalise : "<<m_sommets[i]->getcdn()<<std::endl;
        std::cout<<"indice centralite vecteur propre : "<<m_sommets[i]->getcvp()<<std::endl;
        if(m_sommets[i]->getcp()==-1)
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
        if(m_sommets[i]->getci()==-1)
        {
            SetConsoleTextAttribute(hConsole, 12);
            std::cout<<"impossible de calculer centralite intermideriarite et centralite intermediarite normalise car graphe non connexe "<<std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else
        {
            std::cout<<"indice centralite intermediarite non normalise : "<<m_sommets[i]->getci()<<std::endl;
            std::cout<<"indice centralise intermediarite normalise : "<<m_sommets[i]->getciN()<<std::endl;
        }
        std::cout<<std::endl<<"Comparaisons apres suppression : "<<std::endl;
        std::cout<<"nom du sommet : "<<m_sommets[i]->getNom()<<std::endl;
        std::cout<<"difference centralite degre non normalise : "<<(double)abs(vect_cd[i]-m_sommets[i]->getcd())<<std::endl;
        std::cout<<"difference centralite degre normalise : "<<(double)abs(vect_cdn[i]-m_sommets[i]->getcdn())<<std::endl;
        std::cout<<"difference centralite vecteur propre : "<<(double)abs(vect_cvp[i]-m_sommets[i]->getcvp())<<std::endl;
        if(m_sommets[i]->getcp()==-1 && vect_cp[i]!=-1)
        {
            SetConsoleTextAttribute(hConsole, 12);
            std::cout<<std::endl<<"La suppression de l'arete a rendu le graphe non connexe"<<std::endl;
            std::cout<<"l'indice de centralite proxi du sommet "<<m_sommets[i]->getNom()<<" n'est donc plus calculable alors qu'il avait pour valeur "<<vect_cp[i]<<std::endl;
            std::cout<<"de meme pour l'indice de centralite proxi normalise"<<std::endl<<std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else if(vect_cp[i]==-1)
        {
            SetConsoleTextAttribute(hConsole, 12);
            std::cout<<std::endl<<"Les differences des 2 indices de centralite proxi ne sont pas calculables car le graphe"<<std::endl;
            std::cout<<" n'etait pas connexe de base"<<std::endl<<std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else
        {
            std::cout<<"difference centralite degre proxi non normalise : "<<(double)abs(vect_cp[i]-m_sommets[i]->getcp())<<std::endl;
            std::cout<<"difference centralite degre proxi normalise : "<<(double)abs(vect_cpn[i]-m_sommets[i]->getcpn())<<std::endl;
        }
        if(m_sommets[i]->getci()==-1 && vect_ci[i]!=-1)
        {
            SetConsoleTextAttribute(hConsole, 12);
            std::cout<<std::endl<<"La suppression de l'arete a rendu le graphe non connexe"<<std::endl;
            std::cout<<"l'indice de centralite intermediarite du sommet "<<m_sommets[i]->getNom()<<" n'est donc plus calculable alors qu'il avait pour valeur "<<vect_ci[i]<<std::endl;
            std::cout<<"de meme pour l'indice de centralite intermediarite normalise"<<std::endl<<std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else if(vect_ci[i]==-1)
        {
            SetConsoleTextAttribute(hConsole, 12);
            std::cout<<std::endl<<"Les differences des 2 indices de centralite intermediarite ne sont pas calculables car le graphe"<<std::endl;
            std::cout<<" n'etait pas connexe de base"<<std::endl<<std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else
        {
            std::cout<<"difference centralite intermediarite non normalise : "<<(double)abs(vect_ci[i]-m_sommets[i]->getci())<<std::endl;
            std::cout<<"difference centralite intermediarite normalise : "<<(double)abs(vect_cin[i]-m_sommets[i]->getciN())<<std::endl;
        }
    }
    std::cout<<std::endl<<"l'indice de centralite de proximite globale du graphe apres suppression est : "<<this->getcpg()<<std::endl;
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

///Fonctions pour dessiner les différentes centralités

void Graphe::dessinerTous(int& nom, int& poids, int& cdn, int& cd, int& cvp, int& cpn, int& cp, int& ci, int&ciN, int& cia)
{
    Svgfile svgout;
    for(size_t i=0; i<m_sommets.size(); i++)
    {
        m_sommets[i]->dessiner(svgout);//dessin des sommets
        for(size_t j=0; j<m_aretes.size(); j++)
        {
            m_aretes[j]->dessiner(svgout);//dessin des aretes
        }
    }
    if(nom==1)//condition pour dessiner les nom
    {
        for(size_t i=0; i<m_sommets.size(); i++)
        {
            m_sommets[i]->ecrireNom(svgout);//ecrit des prenoms
        }
    }
    if(poids==1)//Condition pour dessiner les poids
    {
        for(size_t i=0; i<m_aretes.size(); i++)
        {
            m_aretes[i]->ecrirePoids(svgout);//dessin des poids
        }
    }
    if (cdn==1)//Condition pour dessiner la centralite degre normalise
        this->dessinerCDN(svgout);
    if (cd==1)//Condition pour dessiner la centralite degre
        this->dessinerCD(svgout);
    if(cvp==1)//Condition pour dessiner la centralite vecteur propre
        this->dessinerCVP(svgout);
    if (cpn==1)//Condition pour dessiner la centralite proxi normalise
        this->dessinerCPN(svgout);
    if (cp==1)//Condition pour dessiner la centralite proxi
        this->dessinerCP(svgout);
    if(ci==1)//Condition pour dessiner la centralite intermediarite
        this->dessinerCI(svgout);
    if(ciN==1)//Condition pour dessiner la centralite intermediarite normalise
        this->dessinerCIN(svgout);
    if(cia==1)//Condition pour dessiner la centralite intermediarite arete
        this->dessinerCIA(svgout);
}


void Graphe::dessinerCDN(Svgfile& svgout)
{
    this->centralitedegreN();//Calcul centralite degre normalise

    std::vector<double> vect_cdn;//Creation vecteur de centralite degre normalise
    for(size_t i=0; i<m_sommets.size(); i++)
    {
        vect_cdn.push_back(m_sommets[i]->getcdn());//On remplit le vecteur des centralites degre normalise
    }
    for (size_t i=0; i<m_sommets.size(); ++i)
        {
            if(m_sommets[i]->getcdn()==*std::max_element(vect_cdn.begin(), vect_cdn.end()))//Condition sur la valeur max des centralites degre normalise du graphe
                m_sommets[i]->dessinerMarque(svgout);//Dessin marqué du sommet ayant la plus grande valeur
            m_sommets[i]->ecrireCentraliteDegreN(svgout);//Dessin des autres sommets
        }
}
void Graphe::dessinerCD(Svgfile& svgout)
{
    this->centralitedegre();//Calcul centralite degre
    std::vector<double> vect_cd;//Creation vecteur de centralite degre
    for(size_t i=0; i<m_sommets.size(); i++)
    {
        vect_cd.push_back(m_sommets[i]->getcd());//On remplit le vecteur des centralites degre
    }
     for (size_t i=0; i<m_sommets.size(); ++i)
        {
            if(m_sommets[i]->getcd()==*std::max_element(vect_cd.begin(), vect_cd.end()))//Condition sur la valeur max des centralites degre du graphe
                m_sommets[i]->dessinerMarque(svgout);//Dessin marqué du sommet ayant la plus grande valeur
            m_sommets[i]->ecrireCentraliteDegre(svgout);//Dessin des autres sommets
        }
}
void Graphe::dessinerCP(Svgfile& svgout)
{
    this->centraliteproxi();//Calcul centralite proxi
    std::vector<double> vect_cp;//Creation vecteur de centralite proxi
    for(size_t i=0; i<m_sommets.size(); i++)
    {
        vect_cp.push_back(m_sommets[i]->getcp());//On remplit le vecteur des centralites proxi
    }
    for (size_t i=0; i<m_sommets.size(); ++i)
        {
            if(m_sommets[i]->getcp()==*std::max_element(vect_cp.begin(), vect_cp.end()))//Condition sur la valeur max des centralites proxi du graphe
                m_sommets[i]->dessinerMarque(svgout);//Dessin marqué du sommet ayant la plus grande valeur
            m_sommets[i]->ecrireCentraliteP(svgout);//Dessin des autres sommets
        }
}
void Graphe::dessinerCPN(Svgfile& svgout)
{
    this->centraliteproxiN();//Calcul centralite proxi normalise
    std::vector<double> vect_cpn;//Creation vecteur de centralite proxi normalise
    for(size_t i=0; i<m_sommets.size(); i++)
    {
        vect_cpn.push_back(m_sommets[i]->getcpn());//On remplit le vecteur des centralites proxi normalise
    }
    for (size_t i=0; i<m_sommets.size(); ++i)
        {
            if(m_sommets[i]->getcpn()==*std::max_element(vect_cpn.begin(), vect_cpn.end()))//Condition sur la valeur max des centralites proxi noramlise du graphe
                m_sommets[i]->dessinerMarque(svgout);//Dessin marqué du sommet ayant la plus grande valeur
            m_sommets[i]->ecrireCentralitePN(svgout);//Dessin des autres sommets
        }
}
void Graphe::dessinerCVP(Svgfile& svgout)
{
    this->centralitevp();//Calcul centralite vecteur propre

    std::vector<double> vect_vp;//Creation vecteur de centralite vecteur propre
    for(size_t i=0; i<m_sommets.size(); i++)
    {
        vect_vp.push_back(m_sommets[i]->getcvp());//On remplit le vecteur des centralites vecteur propre
    }
    for (size_t i=0; i<m_sommets.size(); ++i)
        {
            if(m_sommets[i]->getcvp()==*std::max_element(vect_vp.begin(), vect_vp.end()))//Condition sur la valeur max des centralites vecteur propre du graphe
                m_sommets[i]->dessinerMarque(svgout);//Dessin marqué du sommet ayant la plus grande valeur
            m_sommets[i]->ecrireCentraliteVP(svgout);//Dessin des autres sommets
        }
}
void Graphe::dessinerCI(Svgfile& svgout)
{

    this->centraliteinter();//Calcul centralite intermediarite

    std::vector<double> vect_ci;//Creation vecteur de centralite intermediarite
    for(size_t i=0; i<m_sommets.size(); i++)
    {
        vect_ci.push_back(m_sommets[i]->getci());//On remplit le vecteur des centralites d'intermediarite
    }
    for (size_t i=0; i<m_sommets.size(); ++i)
        {
            if(m_sommets[i]->getci()==*std::max_element(vect_ci.begin(), vect_ci.end()))//Condition sur la valeur max des centralites d'intermediarite du graphe
                m_sommets[i]->dessinerMarque(svgout);//Dessin marqué du sommet ayant la plus grande valeur
            m_sommets[i]->ecrireCentraliteCI(svgout);//Dessin des autres sommets
        }
}
void Graphe::dessinerCIN(Svgfile& svgout)
{
    this->centraliteinterN();//On calcul les centralites d'intermediarite normalise

    std::vector<double> vect_cin;//Creation d'un vecteur de centralites d'intermediarite normalise
    for(size_t i=0; i<m_sommets.size(); i++)
    {
        vect_cin.push_back(m_sommets[i]->getciN());//On remplit le vecteur des centralites d'intermediarite normalise du graphe
    }
    for (size_t i=0; i<m_sommets.size(); ++i)
        {
            if(m_sommets[i]->getciN()==*std::max_element(vect_cin.begin(), vect_cin.end()))//Condition sur la valeur max des centralites d'intermediarite normalise du graphe
                m_sommets[i]->dessinerMarque(svgout);//Dessin marqué du sommet ayant la plus grande valeur
            m_sommets[i]->ecrireCentraliteCIN(svgout);//Dessin des autres sommets
        }
}

void Graphe::dessinerCIA(Svgfile& svgout)
{
    this->centraliteinterarete();//On calcul les centralites d'intermediarite arete
    std::vector<double> vect_cia;//Creation d'un vecteur de centralites d'intermediarite arete
    for(size_t j=0; j<m_aretes.size(); j++)
    {
        vect_cia.push_back(m_aretes[j]->getciA());//On remplit le vecteur des centralites d'intermediarite arete du graphe
    }
    for (size_t i=0; i<m_aretes.size(); ++i)
        {
            if(m_aretes[i]->getciA()==*std::max_element(vect_cia.begin(), vect_cia.end()))//Condition sur la valeur max des centralites d'intermediarite arete du graphe
                m_aretes[i]->marquerArete(svgout);//Dessin marqué de l'arete ayant la plus grande valeur
            m_aretes[i]->ecrireCIA(svgout);//Dessin des autres aretes
        }
}

