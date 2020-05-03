#include "Graphe.h"
#include<queue>
#include<stack>


//constructeur qui prend en parametre les deux fichiers
Graphe::Graphe( std::string fichier, std::string fichierPoids)
{
    int taille2;//declaration taille fichier 2 puis fichier 1
    int taille;
    std::ifstream ifs(fichier);// on lit le fichier graphe
//on blinde l'ouverture du fichier
    if(!ifs)//si la saisie est mauvaise
    {
        SetConsoleTextAttribute(hConsole, 12);
        std::cout<<"Saisie du fichier graphe incorrecte"<<std::endl;
        std::cout<<"Appuyer sur exit pour recommencer"<<std::endl;
        SetConsoleTextAttribute(hConsole, 15);

    }
    else//si la saisie est mauvaise
    {
        ifs>>m_orient;// on lit l'orientation
        if (ifs.fail() )//on verifie que la lecture a bien ete effectuee
            throw std::runtime_error("Erreur de lecture d'orientation");
        int ordre;
        ifs>>ordre;//on lit l'ordre
        if (ifs.fail() )// on verifie que ca a bien marche
            throw std::runtime_error("Erreur de lecture d'ordre");
        for (int i=0; i<ordre; ++i)// on parcourt tous les sommets grace à l'ordre que l'on a recupere
        {
            m_sommets.push_back(new Sommet(ifs)); //on ajoute à m_sommets un nouveau sommet que l'on construit par la meme occassion grace a un flux
        }
        ifs>>taille;// on lit la taille
        if (ifs.fail() )//on verifie qu'il n'y a pas d'erreur
            throw std::runtime_error("Erreur de lecture de la taille");
        int indice;
        int s1;
        int s2;
        for (int i=0; i<taille; ++i)//on parcourt toutes les aretes grace a la taille que l'on a recuperee
        {
            ifs>>indice>>s1>>s2;// on lit l'indice de l'arete et ses deux extremites
            for (size_t i=0; i<m_sommets.size(); ++i)// on cherche dans m_sommets les deux extremites grace à leur id
            {
                for (size_t j=0; j<m_sommets.size(); ++j)// pour cela on fait une double boucle for
                {
                    if((s1==m_sommets[i]->getId())&&(s2==m_sommets[j]->getId()))//si on tombe sur deux sommets qui ont le meme indice
                    {
                        m_aretes.push_back(new Arete(indice,m_sommets[i],m_sommets[j]));// on ajoute a notre vecteur m_aretes une arete que l'on construit par le meme temps grace à son indice et aux deux extremites
                    }
                }
            }
        }
        //on remplit les vecteurs d'adjacence de chaque sommet
        for (size_t i=0; i<m_sommets.size(); ++i)// on parcourt tous les sommets
        {
            for(size_t j=0; j<m_aretes.size(); ++j)// on parcourt toutes les aretes
            {
                if((m_aretes[j]->getindiceS1())==m_sommets[i]->getId())// si l'indice du S1  de l'arete correspond à celui du sommet parcouru
                {
                    m_sommets[i]->setadj(m_aretes[j]->getSommet2());// on ajoute S2 à son vecteur d'adjacence
                }
                if ((m_aretes[j]->getindiceS2()==m_sommets[i]->getId()))// si l'indice du S2  de l'arete correspond à celui du sommet parcouru
                {
                    m_sommets[i]->setadj(m_aretes[j]->getSommet1());// on ajoute S1 à son vecteur d'adjacence
                }
            }
        }
    }
    std::ifstream is(fichierPoids);// on lit le fichier poids
    if(!is)//blindage
    {
        SetConsoleTextAttribute(hConsole, 12);
        std::cout<<"Saisie du fichier poids incorrecte"<<std::endl;
        std::cout<<"Appuyer sur (exit) ou (changer fichier poids) pour recommencer "<<std::endl;
    }
    else
    {
        is>>taille2;//on lit la taille
        if (taille!=taille2 )//verification que la taille est bien celle du fichier graphe
            throw std::runtime_error("Les tailles du fichier graphe et poids sont differentes, le programme se ferme");
        int indice2;
        double poids;
        for(int i=0; i<taille2; ++i)
        {
            is>>indice2>>poids;//on lit l'indice de l'arete et son poids
            if(indice2==m_aretes[i]->getindice())
                m_aretes[i]->setPoids(poids);//on assimile le poids lu a l'arete ayant le meme indice que celle lue
        }
    }
}
//destructeur
Graphe::~Graphe()
{
    for (auto s : m_sommets)//on parcourt chaque sommet et on le delete
        delete s;
    for (auto s : m_aretes)// on parcourt chaque arete et on la delete
        delete s;
}
//getter de l'orientation du graphe
int Graphe::getOrient()const
{
    return m_orient;
}
// getter de l'ordre du graphe
int Graphe::getOrdre()const
{
    return (int)m_sommets.size();
}
//getter de la taille du graphe
int Graphe::getTaille()const
{
    return (int)m_aretes.size();
}

//enregistre les indices de centralite de chaque sommet dans un fichier
void Graphe::enregistrer()
{
    // on calcule tous les indices de chaque sommet du graphe que l'on etudie
    std::string nomFichier;
    this->centralitedegre();
    this->centralitedegreN();
    this->centraliteproxi();
    this->centraliteproxiN();
    this->centralitevp();
    this->centraliteinter();
    this->centraliteinterN();

    std::ofstream ofs{"sauvegarde.txt"};// on cree un fichier dans lequel on va ecrire
    if(!ofs)// on teste l'ouverture
    {
        std::cerr<<"Erreur  d'ouverture du fichier"<<std::endl;
    }
    else
    {
        for (size_t i=0; i<m_sommets.size(); ++i)
        {
            // pour chaque sommet, on ecrit dans le fichier son indice puis tous ses indices de centralite
            if(m_sommets[i]->getcp()!=-1 && m_sommets[i]->getci()!=-1)
                ofs<<"id: "<<m_sommets[i]->getId()<<"| cd: "<<m_sommets[i]->getcd()<<"| cdn: "<<m_sommets[i]->getcdn()<<"| cvp: "<<m_sommets[i]->getcvp()<<"| cp: "<<m_sommets[i]->getcp()<<"| cpn: "<<m_sommets[i]->getcpn()<<"| ci: "<<m_sommets[i]->getci()<<"| cin: "<<m_sommets[i]->getciN()<<std::endl;
            else if(m_sommets[i]->getcp()==-1 && m_sommets[i]->getci()!=-1)
                ofs<<"id: "<<m_sommets[i]->getId()<<"| cd: "<<m_sommets[i]->getcd()<<"| cdn: "<<m_sommets[i]->getcdn()<<"| cvp: "<<m_sommets[i]->getcvp()<<"| cp: incalculable | cpn: incalculable"<<"| ci: "<<m_sommets[i]->getci()<<"| cin: "<<m_sommets[i]->getciN()<<std::endl;
            else if(m_sommets[i]->getci()==-1 && m_sommets[i]->getcp()!=-1)
                ofs<<"id: "<<m_sommets[i]->getId()<<"| cd: "<<m_sommets[i]->getcd()<<"| cdn: "<<m_sommets[i]->getcdn()<<"| cvp: "<<m_sommets[i]->getcvp()<<"| cp: "<<m_sommets[i]->getcp()<<"| cpn: "<<m_sommets[i]->getcpn()<<"| ci: incalculable | cin: incalculable "<<std::endl;
            else if(m_sommets[i]->getci()==-1 && m_sommets[i]->getcp()==-1)
                ofs<<"id: "<<m_sommets[i]->getId()<<"| cd: "<<m_sommets[i]->getcd()<<"| cdn: "<<m_sommets[i]->getcdn()<<"| cvp: "<<m_sommets[i]->getcvp()<<"| cp: incalculable | cpn: incalculable"<<"| ci: incalculable | cin: incalculable"<<std::endl;
        }
    }
}

//recuperer l'indice de centralite de degre de chaque sommet
void Graphe::centralitedegre()
{
    for(size_t i=0; i<m_sommets.size(); ++i)//parcours de toues les sommets
    {
        m_sommets[i]->setcd((double)m_sommets[i]->get_nb_adj());// on recupere son indice de centralite de degre grace à la taille de son vecteur d'adjacence
    }
}

//calcule l'indice de centralite de degre normalise de chaque sommet
void Graphe::centralitedegreN()
{
    this->centralitedegre();//on calcule d'abord l'indice decentralite de degre de tous les sommetx
    double cd;
    for (size_t i=0; i<m_sommets.size(); ++i)// on parcourt tous les sommets
    {
        cd=m_sommets[i]->getcd();//
        m_sommets[i]->setcdn(cd/((float)m_sommets.size()-1));// on applique la formule pour obtenir l'indice normalise
    }
}

//permet de trouver le poids de l'arete en fonction des deux extremites
double Graphe::trouverpoids(int s1,int s2)// on envoie en parametre deux indices de sommet
{
    double poids;
    for(size_t i=0; i<m_aretes.size(); ++i)// on parcourt toutes les aretes
    {
        // on cherche l'arete qui a pour extremites les deux sommets qui ont pour indice ceux envoye en parametre
        if (((m_aretes[i]->getindiceS1()==s1)&&(m_aretes[i]->getindiceS2()==s2))||((m_aretes[i]->getindiceS1()==s2)&&(m_aretes[i]->getindiceS2()==s1)))
        {
            poids=m_aretes[i]->getPoids();// on recupere donc le poids de cet arete
        }
    }
    return poids;
}

//trouve un sommet à partir de son indice
Sommet*Graphe::trouversommetindice(int indice)
{
    Sommet*s1;
    for(size_t i=0; i<m_sommets.size(); ++i)// parcourt tous les sommets
    {
        if (m_sommets[i]->getId()==indice)// si le sommet parcouru a le meme indice que celui envoye en aprametr
            s1=m_sommets[i];// on le recupere et on le renvoie
    }
    return s1;
}

//dijkstra qui renvoie la distance minimum entre le sommet de depart et celui d'arrivee
// programme modifie par rapport au programme utilise lors du TP3 par Thomas et sa partenaire Laure Audouy
double Graphe::dijkstraproxi(int depart,int arrivee)
{
    std::vector<int> I_preds;//I_preds[i] donne le prédécesseur du sommet i
    std::priority_queue<double, std::vector<double>, std::greater<double> > distances; //file de priorite avec le plus petit element en top
//initialisation variables temporaires
    int succ=0;
    double dist=0;
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

    S=trouversommetindice(depart);// on recupere le sommet de depart grace a l'id de depart

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
            succ=S->get_adj(x)->getId();//on récupère le sommet se trouvant à la case x du vecteur d'adjacence du sommet
            poids=trouverpoids(sommet,succ);
            S=trouversommetindice(succ);// on recupere le sommet à partir de son indice

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
        S=trouversommetindice(sommet);// on recupere le sommet grace a son indice
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
    return dist;// on retourne la derniere valeur que prend distance : elle correspond a la distance entre le sommet d'arrivee et le sommet de depart
}

// calcule  l'indice de centralite de proximite de chaque sommmet
void Graphe::centraliteproxi()
{
    int i;
    double cp;
    i=this->nb_comp_connexe(m_sommets[0]->getId());
//on verifie bien que le nb de comp connexe est de 1 sinon on ne peut calculer l'indice
    if (i==1)
    {

        for (size_t i=0; i<m_sommets.size(); ++i)
        {
            cp=0;// on reinitialise cp a chaque tour de boucle

            for (size_t j=0; j<m_sommets.size(); ++j)
            {
                if ((m_sommets[i]->getId())!=(m_sommets[j]->getId()))//on verifie bien que les deux sommets sont differents
                {
                    cp+=dijkstraproxi(m_sommets[i]->getId(),m_sommets[j]->getId());// on ajoute a cp la plus courte distance entre m_sommet[i] et m_sommets[j]
                }
            }
            cp=1/cp;//apres avoir somme toutes les distances on passe à l'inverse
            m_sommets[i]->setcp(cp);//on attribue la valeur trouvee
        }
    }
    else// s'il y a plusieurs composantes connexes
        for(size_t i=0; i<m_sommets.size(); i++)
        {
            m_sommets[i]->setcp(-1);// on attribue à l'indice de centralite de proximite de chaque sommet -1, une valeur impossible à obtenir s'il n'ya qu'une comp connexe
        }
}
//calcule l'indice de centralite de proximite normalise de chaque sommet
void Graphe::centraliteproxiN()
{
    this->centraliteproxi();//on calcule tout d'abord l'indice de centralite de proximite de tous les sommets du graphe etudie
    double cp;
    for (size_t i=0; i<m_sommets.size(); ++i)
    {
        cp=m_sommets[i]->getcp();
        m_sommets[i]->setcpn(cp*(m_sommets.size()-1));// on applique la formule
    }
}
// calcule l'indice de centralite de vecteur propre de chaque sommet
void Graphe::centralitevp()
{
    //initialisation variables
    double temp=0;
    double tampon;
    int q=0;
    std::vector<double>lambda;// on cree un vecteur qui va contenir les differentes valeur de lambda
    for(size_t i=0; i<m_sommets.size(); ++i)
    {
        m_sommets[i]->setcvp(1);// on initialise tous les indices de centralite de vecteur propre à 1
    }
    for (size_t l=0; l<10000; ++l)
    {
        lambda.push_back(0);// on initialise à 0 les 100 premieres cases du vecteur lambda
    }
    do
    {
        lambda[q]=0;
        for(size_t i=0; i<m_sommets.size(); ++i)//on parcourt tous les sommets
        {
            temp=0;// on reinitialise la valeur de temp a chaque tour de boucle
            for(size_t j=0; j<m_sommets[i]->get_nb_adj(); ++j)// on parcourt tous les adjacents du sommet parcouru
            {
                temp+=m_sommets[i]->get_adj(j)->getcvp();// on ajoute a temp la valeur du cvp du sommet adjacent parcouru
            }
            m_sommets[i]->setcsi(temp);// on attribue au csi du sommet i parcouru la valeur temp
        }
        // on ajoute à lambda [q] tous les csi au carre
        for (size_t k=0; k<m_sommets.size(); ++k)
        {
            lambda[q]+=pow(m_sommets[k]->getcsi(),(2));//utilisation de la fonction pow
        }
        // on fait la racine de lambda[q]
        lambda[q]=sqrt(lambda[q]);

        for (size_t i=0; i<m_sommets.size(); ++i)
        {
            // on attribue au cvp du sommet parcouru la valeur de son csi divise par lambda
            m_sommets[i]->setcvp((m_sommets[i]->getcsi())/lambda[q]);
        }
        q++;// on incremente q
        tampon=lambda[q-1]-lambda[q-2];
    }
    while ((q<2)||((tampon>0.001)||(tampon<-0.001))); // on effectue cette boucle tant que q<2 ( sinon cela n'a pas de sens de faire lambda[q-1]-lambda[q-2], et on verifie que l'ecart entre les deux dernieres valeurs de lambda est inferieur à 0.001

}

//algo qui verifie la presence d'un sommet dans un pcc entre deux sommets
// programme modifie à partir du programme utilise lors du TP3 par Thomas et sa partenaire Laure Audouy
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
                    // si un des predecesseur est le sommet dont on voulait etudier la presence dans le pcc alors presence=1
                    presence=1;
                }
                pred=I_preds[pred];// predecesseur prend la valeur du predecesseur du sommet alors traité
            }
            // affichage du chemin
            std::cout<<"<--"<<depart<<std::endl;
        }
        std::cout<<"presence ="<<presence<<std::endl;
    }
    // on retourne la valeur de la variable presence
    return presence;
}

//algo qui permet de trouver l'indice de cenralite d'intermediarite en supposant qu'il n'y a qu'un seul pcc
void Graphe::centraliteinter1pcc()
{
    // initialisation des variables
    int p;
    double ci1;
// On regarde le nombre de composantes connexes du graphe etudie
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
    // si le nombre de composante connexe n'est pas 1
    else
        for(size_t i=0; i<m_sommets.size(); i++)
        {
            // on attribue a ci1 61, une valeur impossible s'il n'y a qu'une cpp
            m_sommets[i]->setci1(-1);
        }
}

//on normalise ensuite ces valeurs
void Graphe::centraliteinter1Npcc()
{
    this->centraliteinter1pcc();
    double ci1N=0;
    for (size_t i=0; i<m_sommets.size(); ++i)
    {
        //on parcourt tous les sommets et on recupere la valeur de ci1
        ci1N=0;
        ci1N=m_sommets[i]->getci1();
        // on applique la formule pour normaliser cette expression
        m_sommets[i]->setci1n((2*ci1N)/(pow((double)m_sommets.size(),2)-3*(double)m_sommets.size()+2));
    }
}

//code inspiré du site https://tutorialspoint.dev/data-structure/graph-data-structure/print-paths-given-source-destination-using-bfs
//il permet de savoir si un sommet a ete totalement parcouru
int Graphe::pasParcouru(int x, std::vector<int>& chemin)
{
// on parcourt tous les id des sommets de chemin
    for (size_t i = 0; i < chemin.size(); ++i)
        if (chemin[i] == x)// si la case i du chemin correspond à celle envoyee en parametre
            return 0;
    return 1;
}

//code inspiré du site https://tutorialspoint.dev/data-structure/graph-data-structure/print-paths-given-source-destination-using-bfs
//ce site explique comment obtenir tous les chemins d'un sommet a a un somment b
//Nous  avons arrange le code pour qu'il retourne un terme de la somme permettant de calculer l'indice de centralite d'intermediaritte
double Graphe::presencesparcouru(int depart, int arrivee, int sparcouru,double distance)
{
    // initialisations de toutes les variables
    std::queue<std::vector<int>>touschemins;
    Sommet*S;
    Sommet*S1;
    double poidschemin=0;
    double presence=0;
    double ci;
    std::vector<int>chemin;
    chemin.push_back(depart);// on ajoute a chemin l'id de depart vu que l'on veut trouver tous les chemins qui partent de depart et qui arrivent a arrivee
    double compteurpcc=0;
    int id; //chaque chemin devra aller du depart donc on le push_back
    touschemins.push(chemin);
    //tant que la file n'est pas vide
    while (!touschemins.empty())
    {
        // chemin est le premier element du vecteur tous chemins
        chemin = touschemins.front();
        // on supprime ensuite la premiere case de la file
        touschemins.pop();
        //on attribue à dernier la valeur de la derniere case du vecteur chemin
        int dernier = chemin[chemin.size() - 1];
        // si le dernier id est le meme que arrivee qui a ete envoye en parametre
        if (dernier == arrivee)
        {
            // initialisation du poids du chemin à 0
            poidschemin=0;
            for (size_t i=0; i<chemin.size()-1; ++i)
            {
                // on parcourt toutes les aretes qui constituent ce chemin
                // on ajoute le poids de cet arete au poids du chemin
                poidschemin+=trouverpoids(chemin[i],chemin[i+1]);
            }
            // si le poids du chemin est similaire à la distance envoye en parametre qui est la distance la plus courte entre le sommet ayant pour id depart et celui ayant pour id arrivee
            if (poidschemin==distance)
            {
                // on incrementre le nb de plus court chemin
                compteurpcc++;
                // on parcourt ensuite ce chemin
                for (size_t i=0; i<chemin.size(); ++i)
                {
                    // si la case i de ce chemin est l'id envoye en parametre en tant que sparcouru
                    if (chemin[i]==sparcouru)
                        //on incremente la presence du sparcouru sur les pcc entre depart et arrivee
                        presence++;
                }
            }
        }

        // on trouve le sommet qui a pour indice dernier
        S=trouversommetindice(dernier);
        //on traverse tous les adjacents de ce sommet
        // on cree a chaque fois de nouveaux chemins qui sont push dans la file
        for (double i = 0; i < S->get_nb_adj(); ++i)
        {
            // on recupere le sommet
            S1=S->get_adj(i);
            id=S1->getId();
            // voir commentaires au dessus
            if (pasParcouru(id, chemin))
            {
                // on cree un nouveau chemin
                std::vector<int> nvchemin(chemin);
                id=S1->getId();
// on ajoute l'id au nouveau chemin
                nvchemin.push_back(id);
                // on ajoute le nv chemin a la file
                touschemins.push(nvchemin);
            }
        }
    }

    ci=presence/compteurpcc;
    return ci;
}


//fonction qui opermet de calculer l'indice de centralite d'intermediarite de chaque indice
void Graphe::centraliteinter()
{
// initialisation des variables
    int p;
    double ci;
    double distance;
    // on verifie le nombre de comp connexes
    p=this->nb_comp_connexe(m_sommets[0]->getId());
    if ((p==1) && (m_sommets.size()>2))// on verifie qye la composante est connexe et que le graphe comporte au moins trois sommets
    {
        for (size_t i=0; i<m_sommets.size(); ++i) // on parcourt tous les sommets et c'est la valeur de ci1 de m_sommets[i]que l'on va determiner
        {
            // on reinitialise ci
            ci=0;
            for (size_t j=0; j<m_sommets.size(); ++j)
            {

                for (size_t k=0; k<m_sommets.size(); ++k)
                {
                    // on verifie bien que id de i different de id de j et de id de k et que id de j<id de k
                    if ((m_sommets[j]->getId())<(m_sommets[k]->getId()) &&(m_sommets[i]->getId()!=m_sommets[j]->getId())&&(m_sommets[i]->getId()!=m_sommets[k]->getId()))
                    {
                        // on recupere la distance la plus courte entre m_sommets[j] et m_sommets[k]
                        distance=dijkstraproxi(m_sommets[j]->getId(),m_sommets[k]->getId());
                        ci+=presencesparcouru(m_sommets[j]->getId(),m_sommets[k]->getId(),m_sommets[i]->getId(),distance);
                    }
                }
            }
            m_sommets[i]->setci(ci);

        }
    }
    // si nb comp connexe different de 1
    else
        for(size_t i=0; i<m_sommets.size(); i++)
        {
            // on attribue a ci du m_sommets[i] une valeur impossible a atteindre si nb comp connexe=1
            m_sommets[i]->setci(-1);
        }
}
//normalise les valeurs des indices de centralite d'intermediarite
void Graphe::centraliteinterN()
{
    // on applique centralite inter pour attribuer a chaque sommet le ci
    this->centraliteinter();
    double ciN=0;
    for (size_t i=0; i<m_sommets.size(); ++i)
    {
        ciN=0;
        ciN=m_sommets[i]->getci();
        // on applique la formule pour avoir l'indice normalise
        m_sommets[i]->setciN((2*ciN)/(pow((double)m_sommets.size(),2)-3*(double)m_sommets.size()+2));
    }

}

//meme principe que l'algorithme "presence parcouru" sauf qu'il ne verifie pas la presence d'un sommet sur les differents pcc entre un sommet a et un sommet b mais la presence d'une arete
// Nous avons encore une fois suivi le template du code present sur https://tutorialspoint.dev/data-structure/graph-data-structure/print-paths-given-source-destination-using-bfs
double Graphe::areteparcourue(int depart, int arrivee, int ex1, int ex2,double distance)
{
    //initialisation varaible
    std::queue<std::vector<int>>touschemins;
    Sommet*S;
    Sommet*S1;
    double poidschemin=0;
    double presence=0;
    double ciA;
    std::vector<int>chemin;
    chemin.push_back(depart);// on ajoute a chemin l'id de depart vu que l'on veut trouver tous les chemins qui partent de depart et qui arrivent a arrivee
    double compteurpcc=0;
    int id; //chaque chemin devra aller du depart donc on le push_back

    touschemins.push(chemin);
    //tant que la file n'est pas vide
    while (!touschemins.empty())
    {
        // chemin est le premier element du vecteur tous chemins
        chemin = touschemins.front();
        // on supprime ensuite la premiere case de la file
        touschemins.pop();
        //on attribue à dernier la valeur de la derniere case du vecteur chemin
        int last = chemin[chemin.size() - 1];
        // si le dernier id est le meme que arrivee qui a ete envoye en parametre
        if (last == arrivee)
        {
            // initialisation du poids du chemin à 0
            poidschemin=0;

            for (size_t i=0; i<chemin.size()-1; ++i)
            {
                // on parcourt toutes les aretes qui constituent ce chemin
                // on ajoute le poids de cet arete au poids du chemin
                poidschemin+=trouverpoids(chemin[i],chemin[i+1]);
            }
            // si le poids du chemin est similaire à la distance envoye en parametre qui est la distance la plus courte entre le sommet ayant pour id depart et celui ayant pour id arrivee
            if (poidschemin==distance)
            {
                 // on incrementre le nb de plus court chemin
                compteurpcc++;
                // on parcourt ensuite ce chemin
                for (size_t i=0; i<chemin.size()-1; ++i)
                {
                    // on parcourt toutes les aretes de ce chemin pour verifier si l'arete envoyee en parametre est parcourue, si oui on incremente presence
                    if (((chemin[i]==ex1)&&(chemin[i+1]==ex2))||((chemin[i]==ex2)&&(chemin[i+1]==ex1)))
                        presence++;
                }
            }
        }
        // on trouve le sommet qui a pour indice last
        S=trouversommetindice(last);
        //on traverse tous les adjacents de ce sommet
        // on cree a chaque fois de nouveaux chemins qui sont push dans la file
        for (double i = 0; i < S->get_nb_adj(); ++i)
        {
            // on recupere le sommet
            S1=S->get_adj(i);
            id=S1->getId();
            // voir commentaires au dessus
            if (pasParcouru(id, chemin))
            {
                // on cree un nouveau chemin
                std::vector<int> newpath(chemin);
                id=S1->getId();
                // on ajoute l'id au nouveau chemin
                newpath.push_back(id);
                // on ajoute le nv chemin a la file
                touschemins.push(newpath);
            }
        }
    }
    ciA=presence/compteurpcc;
    return ciA;
}

//permet de determiner l'indice de centralite d'intermediarite d'une arete
void Graphe::centraliteinterarete()
{
    //initialisation variables
    int p;
    double ciA;
    double distance;
    // on regrarde le nombre de comp connexes
    p=this->nb_comp_connexe(m_sommets[0]->getId());
    if ((p==1) && (m_sommets.size()>1))// on verifie qye la composante est connexe et que le graphe comporte au moins une arete
    {
        for (size_t i=0; i<m_aretes.size(); ++i) // on parcourt tous les sommets et c'est la valeur de ci1 de m_sommets[i]que l'on va determiner
        {
            //reinitialisation de cia
            ciA=0;
            for (size_t j=0; j<m_sommets.size(); ++j)
            {

                for (size_t k=0; k<m_sommets.size(); ++k)
                {
                    if ((m_sommets[j]->getId())<(m_sommets[k]->getId()))
                    {
                        // on recupere la distance la plus courte entre m_sommets[j] et m_sommets[k]
                        distance=dijkstraproxi(m_sommets[j]->getId(),m_sommets[k]->getId());
                        ciA+=areteparcourue(m_sommets[j]->getId(),m_sommets[k]->getId(),m_aretes[i]->getindiceS1(),m_aretes[i]->getindiceS2(),distance);
                    }

                }
            }
            m_aretes[i]->setciA(ciA);

        }

    }
    // si nb comp connexe different de 1
    else
        for(size_t i=0; i<m_aretes.size(); i++)
        {
            // on met une valeur impossible
            m_aretes[i]->setciA(-1);
        }
}

//getter recuperant la valeur de l'indice de centralite de proximite global du graphe
double Graphe::getcpg()const
{
    return m_cpg;
}

//setter attribuant une valeur à l'indice de centralite de proximite global du graphe
void Graphe::setcpg(double cpg)
{
    m_cpg=cpg;
}

//fonction permettant de calculer l'indice de centralite de proximite global du graphe
void Graphe::recupcpg()
{
    //on applique centralite proxi pour recuperer la valeur de cp de tous les indices
    this->centraliteproxi();
    // initialisation des variables
    int p;
    double maximum=0;
    double tampon=0;
    double cpg=0;
    double denominateur=0;
    // on regarde le nombre de composante connexe
    p=nb_comp_connexe(m_sommets[0]->getId());
    if (p==1)
    {


        for(size_t i=0; i<m_sommets.size(); ++i)
        {
            if (m_sommets[i]->getcp()>maximum)
                maximum=m_sommets[i]->getcp();
        }
        // on recupere le cp maximum
        // on recupere tous les termes de la somme du numerateur
        for(size_t i=0; i<m_sommets.size(); ++i)
        {
            tampon+=i*(maximum-m_sommets[i]->getcp());
        }
        // on calcule le denominateur
        denominateur=(pow((double)m_sommets.size(),2)-3*(double)m_sommets.size()+2)/(2*(double)m_sommets.size()-3);
        // on calcule la valeur du cp globale
        cpg=tampon/denominateur;
        this->setcpg(cpg);
    }
    // si le nb de comp connexe est different de 1
    else
        this->setcpg(-1);
}

//getter recuperant la valeur de l'indice de centralite de degre global du graphe
double Graphe::getcdg()const
{
    return m_cdg;
}

//setter attribuant une valeur à l'indice de centralite de degre global du graphe
void Graphe::setcdg(double cdg)
{
    m_cdg=cdg;
}
//formule pour l'indice de centralite de degre global trouvé page 6 dans ce lien https://cs.brynmawr.edu/Courses/cs380/spring2013/section02/slides/05_Centrality.pdf
//fonction permettant de calculer l'indice de centralite de degre global du graphe
void Graphe::recupcdg()
{
    // on applique centralitedegre pour recuper les valeurs de cd de tous les sommets
    this->centralitedegre();
    // initialisation des variables
    double maximum=0;
    double tampon=0;
    double cdg=0;
    double denominateur=0;
    for(size_t i=0; i<m_sommets.size(); ++i)
    {
        if (m_sommets[i]->getcd()>maximum)
            maximum=m_sommets[i]->getcd();
    }
    // on recupere la valeur max de cd
    for(size_t i=0; i<m_sommets.size(); ++i)
    {
        tampon+=(maximum-m_sommets[i]->getcd());// application de la formiule trouvee
    }
    denominateur=(pow((double)m_sommets.size(),2)-3*(double)m_sommets.size()+2);
    cdg=tampon/denominateur;
    this->setcdg(cdg);
}

//getter recuperant la valeur de l'indice de centralite d'intermediarite global du graphe
double Graphe::getcig()const
{
    return m_cig;
}

//setter attribuant une valeur à l'indice de centralite d'intermediarite global du graphe
void Graphe::setcig(double cig)
{
    m_cig=cig;
}

// formule pour l'indice de centralite d'intermediarite global trouvé page 16 de ce leinhttp://moreno.ss.uci.edu/27.pdf
//fonction permettant de calculer l'indice de centralite d'intermediarite global du graphe
void Graphe::recupcig()
{
    // on applique centralite inter pour recuper tous les ci de tous les sommets
    this->centraliteinter();
    // initialisation de toutes les variables
    int p;
    double maximum=0;
    double tampon=0;
    double cig=0;
    double denominateur=0;
    // recuperation du nb de comp connexe
    p=nb_comp_connexe(m_sommets[0]->getId());
    // si nb comp connexe=1
    if (p==1)
    {
        for(size_t i=0; i<m_sommets.size(); ++i)
        {

            if (m_sommets[i]->getci()>maximum)
                maximum=m_sommets[i]->getci();
        }
        // on recupere la valeur max de ci
        // on recupere la valeur du numerateur
        for(size_t i=0; i<m_sommets.size(); ++i)
        {
            tampon+=(maximum-m_sommets[i]->getci());
        }
        denominateur=(m_sommets.size()-1);
        cig=tampon/denominateur;
        this->setcig(cig);
    }
    // si nomb comp connexe!= 1
    else
        this->setcig(-1);


}

//programme qui affiche tous les indices de chaque sommet, de chaque arete, et les indices globaux du graphe
void Graphe::affichercentralite()
{
    // on parcourt tous les ommets
    for (size_t i=0; i<m_sommets.size(); ++i)
    {
        // dans tous les cas on affiche la valeur de l'indice de centralite de degre et de degre normalise et de vecteur propre
        SetConsoleTextAttribute(hConsole, 15);
        std::cout<<std::endl<<"nom : "<<m_sommets[i]->getNom()<<std::endl;
        std::cout<<"centralite degre non normalisee : "<<m_sommets[i]->getcd()<<std::endl;
        std::cout<<"centralite degre normalisee : "<<m_sommets[i]->getcdn()<<std::endl;
        std::cout<<"centralitte vecteur propre : "<<m_sommets[i]->getcvp()<<std::endl;
        // si cp=-1 donc si nb comp connexe !=1
        if(m_sommets[i]->getcp()==-1)
        {
            SetConsoleTextAttribute(hConsole, 12);
            std::cout<<"impossible de calculer centralite proxi et centralite proxi normalisee car graphe non connexe "<<std::endl;
            std::cout<<"impossible de calculer centralite global proxi car graphe non connexe "<<std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else
        {
            // sinon affichage de la valeur
            std::cout<<"centralite proxi : "<<m_sommets[i]->getcp()<<std::endl;
            std::cout<<"centralite proxi normalisee : "<<m_sommets[i]->getcpn()<<std::endl;

        }
        // pareil pour ci
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
    // on parcourt toutes les aretes
    for(size_t j=0; j<m_aretes.size(); j++)
    {
        // si cia=-1 donc si nb comp connexe !=1
        if(m_aretes[j]->getciA()==-1)
        {
        // on affique que c'est impossible de calculer l'indice
            SetConsoleTextAttribute(hConsole, 12);
            std::cout<<"impossible de calculer centralite intermediarite arete "<<std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else
        {
            //sinon on affiche normalement
            std::cout<<"arete : "<<m_aretes[j]->trouverNomS1()<<"--"<<m_aretes[j]->trouverNomS2()<<std::endl;
            std::cout<<"centralite intermediarite arete : "<<m_aretes[j]->getciA()<<std::endl;
        }
    }
    // affichage des indices de centralite globaux
    //affichage de celui de degre
    std::cout<<std::endl<<"l'indice de centralite de degre global est : "<<this->getcdg()<<std::endl;
    // si cpg=-1 alors on affiche message d'erreur car incalculable
    if(this->getcpg()==-1)
        std::cout<<std::endl<<"l'indice de centralite de proximite global est incalculable car le graphe n'est pas connexe"<<std::endl;
    else
        std::cout<<std::endl<<"l'indice de centralite de proximite global du graphe est : "<<this->getcpg()<<std::endl;
        // pareil pour cig
    if(this->getcig()==-1)
        std::cout<<std::endl<<"l'indice de centralite d'intermediarite global est incalculable car le graphe n'est pas connexe"<<std::endl;
    else
        std::cout<<std::endl<<"l'indice de centralite d'intermediarite global du graphe est : "<<this->getcig()<<std::endl;
}

//programme qui teste la connexite du graphe suite à la suppression d'une ou plusieurs aretes
void Graphe::deleteArete( std::vector<int> id)
{
    // initialisation des variables
    Svgfile svgout;
    int s1,s2;
    int nbConnex;
    std::vector<Sommet*> vect1, vect2;
    // on parcourt tous les id des aretes a supprimer
    for (size_t x=0; x<id.size(); x++)
    {
        // pour chaque id nous parcourons toutes les aretes à la recherche de celle ayant le meme id
        for(size_t i=0; i<m_aretes.size(); i++)
        {
            if(m_aretes[i]->getindice()==id[x])
            {
                // si on la trouve on attribue s1 a l'indice de sa premiere extremite et s2 à sa deuxieme
                s1=m_aretes[i]->getindiceS1();
                s2=m_aretes[i]->getindiceS2();
                for(size_t j=0; j<m_sommets.size(); j++)
                {
                    // on cherche s1
                    if(m_sommets[j]->getId()==s1)
                    {
                        for(size_t k=0; k<m_sommets[j]->get_nb_adj(); k++)
                        {
                            if(m_sommets[j]->get_adj(k)->getId()==s2)
                            {
                                // on enelve s2 des adjacents de s1
                                vect1=m_sommets[j]->getAdj();
                                vect1.erase(vect1.begin()+k);
                                m_sommets[j]->setVectAdj(vect1);
                            }
                        }
                    }
                    // on cherche s2
                    if(m_sommets[j]->getId()==s2)
                    {
                        for(size_t k=0; k<m_sommets[j]->get_nb_adj(); k++)
                        {
                            if(m_sommets[j]->get_adj(k)->getId()==s1)
                            {
                                //on enleve s1 des adjacents de s2
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

    // on dessine tous ls sommets
    int compteur=0;
    for(size_t i=0; i<m_sommets.size(); i++)
    {
        m_sommets[i]->dessiner(svgout);
        m_sommets[i]->ecrireNom(svgout);
    }
    // on parcourt toutes les aretes
    for(size_t p=0; p<m_aretes.size(); p++)
    {
        compteur=0;
        // on parcourt tous les id d'aretes a supprimer
        for(size_t j=0; j<id.size(); j++)
        {
            // si m_aretes[p] a le meme indice que id[j]
            if(m_aretes[p]->getindice()==id[j])
            {
                compteur++;
            }
        }
        // si le compteur vaut 0 on dessine sinon non
        if(compteur==0)
            m_aretes[p]->dessiner(svgout);
    }
    // on recupere le nb de comp connexe
    nbConnex=this->nb_comp_connexe(m_sommets[0]->getId());
    SetConsoleTextAttribute(hConsole, 14);
    // on affiche le nb de comp connexes
    std::cout<< "le graphe obtenu a "<<nbConnex<<" composante(s) connexe(s)"<<std::endl;

    // s'il vaut 1 alors le graphe ne devient pas vulnerable apres ces suppression, sinon il devient vulnerable
    if(nbConnex==1)
    {
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<std::endl<<"Le graphe ne devient pas vulnerable si vous supprimez cette ou cettes aretes"<<std::endl;
    }
    else
    {
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<std::endl<<"Le graphe devient vulnerable si vous supprimez cette arete"<<std::endl;
    }
}

//programme qui calcule les valeurs des indices suite à la suppression d'une ou plusieurs aretes
void Graphe::deleteAreteIndice(std::vector<int> id)
{
    //initialisation des variables
    Svgfile svgout;
    std::string nomFichier;
    std::vector<double> vect_cd;
    std::vector<double> vect_cdn;
    std::vector<double> vect_cp;
    std::vector<double> vect_cpn;
    std::vector<double> vect_cvp;
    std::vector<double> vect_ci;
    std::vector<double> vect_cin;
    double cdg;
    double cpg;
    double cig;

    std::vector<std::string> vect_nom;

    // on applique toutes les fonctions pour calculer les indices avant la suppression
    this->centralitedegre();
    this->centralitedegreN();
    this->centraliteproxi();
    this->centraliteproxiN();
    this->centralitevp();
    this->centraliteinter();
    this->centraliteinterN();
    this->recupcpg();
    this->recupcdg();
    this->recupcig();
    SetConsoleTextAttribute(hConsole, 15);
    // on attribue à chaque sommet la valeur de ses indices
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
    // on calcule tous les indices globaux
    cdg=this->getcdg();
    cpg=this->getcpg();
    cig=this->getcig();


    int s1,s2;
    std::vector<Sommet*> vect1, vect2;
    // meme processus qu ela fonction d'avant concernant la suppression d'un sommet dans la liste d'adjacence d'un autre
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
    // meme processus pour savoir quelle arete dessiner
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
    // on reapplique toutes les fonctions pour les indices avec le nouveau graphe
    this->centralitedegre();
    this->centralitedegreN();
    this->centraliteproxi();
    this->centraliteproxiN();
    this->centralitevp();
    this->centraliteinter();
    this->centraliteinterN();
    this->recupcpg();
    this->recupcdg();
    this->recupcig();

    // affichage de toutes les valeurs de tous les indices avant et apres suppression et valeur absolue de la difference de tous les indices de tous les sommets et arretes et du graphe
    for(size_t i=0; i<m_sommets.size(); i++)
    {
        // affichage des indices des sommets avant suppression
        SetConsoleTextAttribute(hConsole, 15);
        std::cout<<std::endl<<"indices de depart : "<<std::endl;
        std::cout<<"nom du sommet : "<<vect_nom[i]<<std::endl;
        std::cout<<"indice centralite degre non normalise : "<<vect_cd[i]<<std::endl;
        std::cout<<"indice centralite degre nomalise : "<<vect_cdn[i]<<std::endl;
        std::cout<<"indice centralite vecteur propre : "<<vect_cvp[i]<<std::endl;
        // on verifie les valeurs de cp et de ci afin de soit les afficher soit d'afficher que leur calcul n'etait pas possible
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
        // affichages des valeurs des indices apres suppression
        std::cout<<std::endl<<"indices apres suppression : "<<std::endl;
        std::cout<<"nom du sommet : "<<m_sommets[i]->getNom()<<std::endl;
        std::cout<<"indice centralite degre non normalise : "<<m_sommets[i]->getcd()<<std::endl;
        std::cout<<"indice centralite degre nomalise : "<<m_sommets[i]->getcdn()<<std::endl;
        std::cout<<"indice centralite vecteur propre : "<<m_sommets[i]->getcvp()<<std::endl;
        // on verifie les valeurs de cp et de ci afin de soit les afficher soit d'afficher que leur calcul n'etait pas possible
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
        // affichage des differences des indices avant et apres suppresion
        std::cout<<std::endl<<"Comparaisons apres suppression : "<<std::endl;
        std::cout<<"nom du sommet : "<<m_sommets[i]->getNom()<<std::endl;
        std::cout<<"difference centralite degre non normalise : "<<(double)abs(vect_cd[i]-m_sommets[i]->getcd())<<std::endl;
        std::cout<<"difference centralite degre normalise : "<<(double)abs(vect_cdn[i]-m_sommets[i]->getcdn())<<std::endl;
        std::cout<<"difference centralite vecteur propre : "<<(double)abs(vect_cvp[i]-m_sommets[i]->getcvp())<<std::endl;
        // si le graphe est devenu non connexe apres suppression
        if(m_sommets[i]->getcp()==-1 && vect_cp[i]!=-1)
        {
            SetConsoleTextAttribute(hConsole, 12);
            std::cout<<std::endl<<"La suppression de l'arete a rendu le graphe non connexe"<<std::endl;
            std::cout<<"l'indice de centralite proxi du sommet "<<m_sommets[i]->getNom()<<" n'est donc plus calculable alors qu'il avait pour valeur "<<vect_cp[i]<<std::endl;
            std::cout<<"de meme pour l'indice de centralite proxi normalise"<<std::endl<<std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
         // si le graphe etait deja non connexe avant suppression
        else if(vect_cp[i]==-1)
        {
            SetConsoleTextAttribute(hConsole, 12);
            std::cout<<std::endl<<"Les differences des 2 indices de centralite proxi ne sont pas calculables car le graphe"<<std::endl;
            std::cout<<" n'etait pas connexe de base"<<std::endl<<std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        // si la suppression n'a pas rendu le graphe vulnerable
        else
        {
            std::cout<<"difference centralite degre proxi non normalise : "<<(double)abs(vect_cp[i]-m_sommets[i]->getcp())<<std::endl;
            std::cout<<"difference centralite degre proxi normalise : "<<(double)abs(vect_cpn[i]-m_sommets[i]->getcpn())<<std::endl;
        }
        // meme processus pour ci
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
    // affichage des indices globaux avant et apres suppression
    std::cout<<std::endl<<"l'indice de centralite de degre global du graphe avant suppression est : "<<cdg<<std::endl;
    std::cout<<std::endl<<"l'indice de centralite de degre global apres suppression est : "<<this->getcdg()<<std::endl;
    std::cout<<std::endl<<" Difference indice de centralite de degre global est : "<<(double)abs(cdg-this->getcdg())<<std::endl;
    if (cpg==-1)
    {
        std::cout<<std::endl<<"Graphe non connexe des le depart, indice de centralite de proximite global incalculable"<<std::endl;
        std::cout<<" Meme chose apres la suppression"<<std::endl;
    }
    else
    {
        std::cout<<std::endl<<"L'indice de centralite de proximite global avant suppression est : "<<cpg<<std::endl;
        if (this->getcpg()==-1)
        {
            std::cout<<std::endl<<"l'indice de centralite de proximite global n'est pas calculable apres suppresion car le graphe n'est pas connexe"<<std::endl;
        }
        else
        {

            std::cout<<std::endl<<"l'indice de centralite de proximite global du graphe apres suppression est : "<<this->getcpg()<<std::endl;
            std::cout<<std::endl<<" DIfference indice de centralite de proximite global est : "<<(double)abs(cpg-this->getcpg())<<std::endl;
        }
    }
    if (cig==-1)
    {
        std::cout<<std::endl<<"Graphe non connexe des le depart, indice de centralite d'intermediarite global incalculable"<<std::endl;
        std::cout<<" Meme chose apres la suppression"<<std::endl;
    }
    else
    {
        std::cout<<std::endl<<"L'indice de centralite d'intermediarite global avant suppression est : "<<cig<<std::endl;
        if (this->getcig()==-1)
        {
            std::cout<<std::endl<<"l'indice de centralite d'intermediarite globale n'est pas calculable apres suppresion car le graphe n'est pas connexe"<<std::endl;
        }
        else
        {

            std::cout<<std::endl<<"l'indice de centralite d'intermediarite global du graphe apres suppression est : "<<this->getcig()<<std::endl;
            std::cout<<std::endl<<" DIfference indice de centralite d'intermediarite global est : "<<(double)abs(cig-this->getcig())<<std::endl;
        }
    }
}

// programme utilise lors du TP2 par Thomas et sa partenaire Laure Audouy
// il permet d'effectuer un bfs a partir d'un sommet donne
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

// programme utilise lors du TP2 par Thomas et sa partenaire Laure Audouy
// il permet de tester la connexite d'un graphe en envoyant en parametre un sommet du graphe
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
        //std::cout<<std::endl<<"composante connexe "<<j<<" : ";
        //on cherche dans le vecteur I_preds tous les sommets de la composante de sommet après découverte par bfs
        for(size_t i=0; i<I_preds.size(); ++i)
        {
            if((I_preds[i]!=-1)||((int)i==idSommet))//s'il sagit du sommet de départ ou de sommets de sa composante
            {
                composante.push_back(i);//sommet découvert
                SetConsoleTextAttribute(hConsole, 8);
                //std::cout<<i<<" ";
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

//fonction qui affiche l'indice de centralite de degre normalise de tous les sommets
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
//fonction qui affiche l'indice de centralite de degre de tous les sommets
void Graphe::dessinerCD(Svgfile& svgout)
{
    this->centralitedegre();//Calcul centralite degre
    this->recupcdg();
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
    svgout.addText(600,15,"indice de centralite de degre global : "+this->nbToStrg(this->getcdg()),"blue");
}
//fonction qui affiche l'indice de centralite de proximite de tous les sommets
void Graphe::dessinerCP(Svgfile& svgout)
{


    this->centraliteproxi();//Calcul centralite proxi
    this->recupcpg();
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
    svgout.addText(600,15,"indice de centralite de proximite global : "+this->nbToStrg(this->getcpg()),"blue");

}

//fonction qui affiche l'indice de centralite de proximite normalise de tous les sommets
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
//fonction qui affiche l'indice de centralite de vecteur propre  de tous les sommets
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
//fonction qui affiche l'indice de centralite d'intermediarite  de tous les sommets
void Graphe::dessinerCI(Svgfile& svgout)
{

    this->centraliteinter();//Calcul centralite intermediarite
    this->recupcig();

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
    svgout.addText(600,15,"indice de centralite d'intermediarite global : "+this->nbToStrg(this->getcig()),"blue");
}
//fonction qui affiche l'indice de centralite d'intermediarite normalise  de tous les sommets
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
//fonction qui affiche l'indice de centralite d'intermediarite de toutes les aretes
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

std::string Graphe::nbToStrg(double nombre)const
{
    std::ostringstream a;
    a<<nombre;
    return a.str();
}
