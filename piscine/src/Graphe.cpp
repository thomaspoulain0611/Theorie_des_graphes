#include "Graphe.h"
#include<queue>
#include<stack>


Graphe::Graphe(std::string nomFichier)
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

    std::vector<int> I_preds;//I_preds[i] donne le pr�d�cesseur du sommet i
    std::priority_queue<double, std::vector<double>, std::greater<double> > distances; //file de priorite avec le plus petit element en top
//initialisation variables temporaires
    int succ=0;
    int dist=0;
    int sommet=-6;
    size_t nb=0;
    double poids=0;
    Sommet*S=nullptr;
//initialisation: chaque case vecteur de predecesseurs � -1 et tous les sommets sont blancs/non parcourus
    for(size_t i=0; i<m_sommets.size(); ++i)
    {
        m_sommets[i]->set_color('B');//sommets non marqu�s
        m_sommets[i]->set_distance(1000000000000000000);//distance infinie
        I_preds.push_back(-1);//autant de cases que de sommets
    }

    S=trouversommetindice(depart);

    nb=S->get_nb_adj();//on recup�re le nombre de successeurs du sommet parcour
    sommet=depart;//sommet actuel est celui de depart
//tant qu'on arrive pas au sommet dont on souhaite connaitre le chemin
    while(sommet!=arrivee)
    {
        S=trouversommetindice(sommet);
        nb=S->get_nb_adj();//on recup�re le nombre de successeurs du sommet parcouru
        for(size_t x=0; x<nb; ++x)//pour chaque successeur de sommet
        {
            S=trouversommetindice(sommet);
            succ=S->get_adj(x)->getId();//on r�cup�re le sommet x
            poids=trouverpoids(sommet,succ);
            S=trouversommetindice(succ);

            if(S->get_color()=='B')//si successeur non d�couvert
            {

                //si poids de l'ar�te entre le sommet et son voisin + distance s�parant le sommet actuel et le sommet de d�part
                //donne une distance plus petite que la distance qu'il avait jusque l�
                if(dist+poids<S->get_distance())
                {

                    S->set_distance(dist+poids);//on donne � succ la nouvelle distance du chemin plus court

                    I_preds.at(succ)=sommet;//on marque sommet comme pr�d�cesseur de succ/

                    //std::cout<<"sommet:"<<sommet->getId()<<std::endl;
                    distances.push(dist+poids);//on ajoute cette nouvelle distance � la file de priorit�

                }
                else
                    distances.push(dist+S->get_distance());//sinon on ajoute l'ancienne distance (entre succ et sommet de d�part) � la file
            }
        }
        S=trouversommetindice(sommet);
        S->set_color('N');//on marque le sommet parcouru
        dist=distances.top();//distance du chemin le plus court est la valeur au top de la file de priorit�
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
    double somme=0;
    std::cout<<"depart :"<<depart<<std::endl;
    std::cout<<"arrivee :"<<arrivee<<std::endl;

    for(size_t i=0; i<nouv.size(); ++i) // on parcourt tous les pr�decesseurs
    {
        std::cout<<"i :"<<i<<std::endl;
        if((int)i==arrivee)// si numero case correspond au sommet d'arriv�e
        {
            //std::cout<<i;// on affiche le sommet d'arriv�e
            pred=nouv[i];//on note son predecesseur
            std::cout<<"pred :"<<pred<<std::endl;

            while(pred!=depart)// tant que le pr�decesseur n'est pas le sommet de d�part
            {
                std::cout<<"<-- pred:"<<pred;// on affiche "<--"

                pred=nouv[pred];// predecesseur prend la valeur du predecesseur du sommet alors trait�
            }
            std::cout<<"<--"<<depart<<" : longueur ";// on affiche le sommet de d�part

            //affichage poids
            pred=nouv[i];// on remet � pred la valeur du pr�decesseur de notre nombre d'arriv�e
            int parcours=pred;

            double poids;
            poids=trouverpoids(pred,nouv[i]);

            // on initialise le sommet parcours et la somme(longueur chemin)
            //std::cout<<m_sommets[pred]->get_poids(i);// on affiche le poids correspondant � l'arete entre le pr�d�cesseur de i et i
            somme+=poids;// on ajoute cette valeur � notre somme

            while(parcours!=depart)// tant que parcours est diff�rent de d�part
            {
                pred=nouv[parcours];
                poids=trouverpoids(pred,parcours);

                // on assimile � pred la valeur du pr�decesseur du sommet �tudi�
                std::cout<<"+"<<poids;// on affiche le poids de l'ar�te entre ces deux sommets
                somme+=poids;// on l'ajoute � la somme
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
        std::cout<<std::endl<<"indice : "<<m_sommets[i]->getId()<<std::endl;
        std::cout<<"centralite degre non normalisee : "<<m_sommets[i]->getcd()<<std::endl;
        std::cout<<"centralite degre normalisee : "<<m_sommets[i]->getcdn()<<std::endl;
        std::cout<<"centralite proxi : "<<m_sommets[i]->getcp()<<std::endl;
        std::cout<<"centralite proxi normalisee : "<<m_sommets[i]->getcpn()<<std::endl;
    }
}


/*if(m_orient==1)
    std::cout<<"Le graphe est orient�"<<std::endl;
else
    std::cout<<"Le graphe n'est pas orient�"<<std::endl;
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

    this->centralitedegre();
    this->centralitedegreN();
    this->centraliteproxi();
    this->centraliteproxiN();
}

std::vector<int> Graphe::bfs (int id)//recup�re sommet de d�part et retourne vecteur de pr�d�cesseurs
{
    int sommet=-6;
    std::vector<int> I_preds;//I_preds[i] donne le pr�d�cesseur du sommet i
    std::queue<int> file;//file d�claration
    int adj=0;
    size_t nb=0;
    Sommet* S=nullptr;
    //on met tous les sommets en blanc: non parcourus
    for(size_t i=0; i<m_sommets.size(); ++i)
    {
        m_sommets[i]->set_color('B');
    }
    //on cr�e un vecteur de predecesseurs avec chaque case initialis�e � -1
    for(size_t y=0; y<m_sommets.size(); ++y)
    {
        I_preds.push_back(-1);
    }
    S=trouversommetindice(id);
    //on ajoute le sommet initial � la file et on le colorie en gris
    sommet=id;
    file.push(sommet);
    S->set_color('G');
    while(!file.empty())//tant que la file n'est pas vide
    {
        S=trouversommetindice(sommet);
        nb=S->get_nb_adj();//on recup�re le nombre de successeurs du sommet parcouru
        file.pop();//on supprime premier �l�ment de la file
        for(size_t i=0; i<nb; ++i)//tant que successeur
        {
            S=trouversommetindice(sommet);
            adj=S->get_adj(i)->getId();//on r�cup�re valeur du successeur i
            S=trouversommetindice(adj);
            if(S->get_color()=='B')//s'il n'a pas �t� parcouru, on le met en gris
            {
                S->set_color('G');
                I_preds.at(adj)=sommet;//sommet est son predecesseur
                file.push(adj);//on l'ajoute � la file
            }
        }
        S=trouversommetindice(sommet);
        S->set_color('N');//sommet parcouru donc noir
        if(!file.empty())//si la file n'est pas vide
            sommet=file.front();//le sommet de parcours est le sommet en t�te de file
    }
    return I_preds;//on retourne le vecteur affectant � chaque sommet un pr�d�cesseur (case 0: pr�d�cesseur du sommet 0, etc)
}

int Graphe::nb_comp_connexe(int idSommet)
{

    //d�claration et initialisation des variables
    std::vector<int> composante;//pour stocker tous les sommets d�couverts dans une composante
    std::vector<int> I_preds;//vecteur des pr�d�cesseurs
    int j=1;
    bool s;
    do//tant qu'il y a des sommets non d�couverts
    {
        s=false;//on part du principe que tout a �t� d�couvert
        I_preds=bfs(idSommet);//parcours bfs � partir d'un sommet pour marquer sommets de sa composante
        SetConsoleTextAttribute(hConsole, 8);
        std::cout<<std::endl<<"composante connexe "<<j<<" : ";
        //on cherche dans le vecteur I_preds tous les sommets de la composante de sommet apr�s d�couverte par bfs
        for(size_t i=0; i<I_preds.size(); ++i)
        {
            if((I_preds[i]!=-1)||((int)i==idSommet))//s'il sagit du sommet de d�part ou de sommets de sa composante
            {
                composante.push_back(i);//sommet d�couvert
                SetConsoleTextAttribute(hConsole, 8);
                std::cout<<i<<" ";
            }
        }
        ++j;//incr�mente pour ji�me composante
        I_preds.clear();//vide le vecteur
        for(size_t w=0; w<m_sommets.size(); ++w)//pour chaque sommet du graphe
        {
            int compt=0;
            if((m_sommets[w]->get_color()=='B'))
            {
                for(size_t h=0; h<composante.size(); ++h)//on cherche si ce sommet a �t� d�couvert avant
                {
                    if((int)w!=composante[h])
                        ++compt;
                }
                if(compt==(int)composante.size())//si le sommet n'a jamais �t� d�couvert lors des parcours pr�c�dents
                {
                    s=true;//il reste des sommets non marqu�s
                    idSommet=w;//le nouveau sommet de parcours est ce sommet non marqu�
                    w=m_sommets.size();//on sort de la boucle
                }
            }
        }
    }
    while(s);//tant qu'il reste des sommets non d�couvert

    return j-1;
}

void Graphe::dessinerTous(int& nom, int& poids, int& cdn, int& cd, int& cpn, int& cp)
{
    Svgfile svgout;
    Sommet* t1, t2, t3, t4;

    if(nom==0 && poids==0 && cdn==0 && cdn==0 && cd==0 && cpn==0 && cp==0)
    {
        for(size_t i=0; i<m_sommets.size(); i++)
        {
            m_sommets[i]->dessiner(svgout);
        }
    }
    if(nom==1)
    {
        for(size_t i=0; i<m_sommets.size(); i++)
        {
            m_sommets[i]->dessiner(svgout);
            m_sommets[i]->ecrireNom(svgout);
        }
    }
    if (cdn==1)
    {
        for (size_t i=0; i<m_sommets.size(); ++i)
        {
            m_sommets[i]->ecrireCentraliteDegreN(svgout);
            if(m_sommets[i+1]->getcdn()> m_sommets[i]->getcdn())
            {
                t1=m_sommets[i+1];
            }
        }
        svgout.addDisk(t1->getx(),t1->gety(),12,"red");
        for ()
    }

    if (cd==1)
    {
        for (size_t i=0; i<m_sommets.size(); ++i)
        {
            m_sommets[i]->ecrireCentraliteDegre(svgout);
            if(m_sommets[i+1]->getcd()> m_sommets[i]->getcd())
            {
                t2=m_sommets[i+1];
            }
        }
        svgout.addDisk(t2->getx(),t2->gety(),12,"red");
    }

    if (cpn==1)
    {
        for (size_t i=0; i<m_sommets.size(); ++i)
        {
            m_sommets[i]->ecrireCentralitePN(svgout);
            if(m_sommets[i+1]->getcpn()> m_sommets[i]->getcpn())
            {
                t3=m_sommets[i+1];
            }
        }
        svgout.addDisk(t3->getx(),t3->gety(),12,"red");
    }

    if (cp==1)
    {
        for (size_t i=0; i<m_sommets.size(); ++i)
        {
            m_sommets[i]->ecrireCentraliteP(svgout);
            if(m_sommets[i+1]->getcp()> m_sommets[i]->getcp())
            {
                t4=m_sommets[i+1];
            }
        }
        svgout.addDisk(t4->getx(),t4->gety(),12,"red");
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
