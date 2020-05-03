#include <iostream>
#include"Graphe.h"
#include "Svgfile.h"
///Pour la coloration du menu
HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

///menu
void menu( std::string& commande, std::string& fichier, std::string& fichierpoids, int& nom, int& poids, int& cdn, int& cd,int& cvp, int& cpn, int& cp,int& ci, int& ciN, int& cia, std::vector<int>& id, std::vector<int>& id2, int& taille, int& taille2, int& idArete, int& idArete2)
{

    Graphe a(fichier, fichierpoids);//On cré le graphe grâce au nom du fichier poids et celui du fichier graphe

    SetConsoleTextAttribute(hConsole, 13);//Couleur rose
    std::cout<<std::endl<<"Options :"<<std::endl;
    SetConsoleTextAttribute(hConsole, 15);//Couleur blanc
    std::cout<<std::endl<<"exit"<<std::endl<<"dessiner"<<std::endl<<"changer fichier poids"<<std::endl<<"afficher (graphe console)"<<std::endl<<"afficher centralite (console)"<<std::endl<<"afficher/enlever poids"<<std::endl<<"afficher/enlever noms"<<std::endl<<"indice centralite degre normalise"<<std::endl<<"indice centralite degre"<<std::endl<<"indice centralite vecteur propre"<<std::endl<<"incide centralite proxi normalise"<<std::endl<<"indice centralite proxi"<<std::endl<<"indice centralite intermediarite"<<std::endl<<"indice centralite intermediarite normalise"<<std::endl<<"indice cia"<<std::endl<<"enlever centralite"<<std::endl<<"vulnerabilite connexe"<<std::endl<<"vulnerabilite indice"<<std::endl<<"save (dans un fichier)"<<std::endl<<std::endl<<std::endl<<">";
    SetConsoleTextAttribute(hConsole, 10);//couleur vert
    std::getline(std::cin, commande);// rentrer la commande
    SetConsoleTextAttribute(hConsole, 15);
    fflush(stdin);

    if(commande=="exit")
    {
    }
    else if(commande=="afficher")
    {
        std::cout<<std::endl<<a<<std::endl;
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Votre graphe a ete affiche avec succes"<<std::endl;
    }
    else if(commande=="save")
    {
        a.enregistrer();//appel la fonction pour sauvegarder un graphe
    }
    else if (commande=="changer fichier poids")
    {
        std::cout<<"nouveau fichier poids : ";
        SetConsoleTextAttribute(hConsole, 10);
        std::cin>>fichierpoids;
        fflush(stdin);
    }
    else if(commande=="dessiner")
    {
        cdn=0;
        cd=0;
        cp=0;
        cpn=0;
        cvp=0;
        ci=0;
        ciN=0;
        poids=0;
        cia=0;
        nom=0;
        a.dessinerTous(nom, poids, cdn, cd, cvp, cpn, cp, ci, ciN, cia);//Appel fonction pour dessiner
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Votre graphe a ete dessine avec succes"<<std::endl;
    }
    else if(commande=="afficher poids")
    {
        poids=1;
        a.dessinerTous(nom, poids, cdn, cd, cvp, cpn, cp, ci, ciN, cia);//Appel fonction pour dessiner
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les poids ont ete affiches avec succes "<<std::endl;
    }
    else if(commande=="enlever poids")
    {
        poids=0;
        a.dessinerTous(nom, poids, cdn, cd, cvp, cpn, cp, ci, ciN,cia);//Appel fonction pour dessiner
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les poids ont ete enleves avec succes "<<std::endl;
    }
    else if(commande=="afficher noms")
    {
        nom=1;
        a.dessinerTous(nom, poids, cdn, cd,cvp, cpn, cp, ci, ciN,cia);//Appel fonction pour dessiner
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les noms ont ete affiches avec succes "<<std::endl;
    }
    else if(commande=="enlever noms")
    {
        nom=0;
        a.dessinerTous(nom, poids, cdn, cd, cvp, cpn, cp, ci, ciN,cia);//Appel fonction pour dessiner
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les noms ont ete enleves avec succes "<<std::endl;
    }
    else if(commande=="indice centralite degre normalise")
    {
        cdn=1;
        a.dessinerTous(nom, poids, cdn, cd, cvp, cpn, cp, ci, ciN,cia);//Appel fonction pour dessiner
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les incides de centralite degres normalises ont ete affiches avec succes "<<std::endl;
        std::cout<<std::endl<<"Le sommet marque est celui comportant le plus haut indice de centralite degre normalise"<<std::endl;
    }
    else if(commande=="indice centralite degre")
    {
        cd=1;
        a.dessinerTous(nom, poids, cdn, cd, cvp, cpn, cp, ci, ciN,cia);//Appel fonction pour dessiner
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les indices de centralite degres non normalises ont ete affiches avec succes "<<std::endl;
        std::cout<<std::endl<<"Le sommet marque est celui comportant le plus haut indice de centralite degre non normalise"<<std::endl;
    }
    else if (commande=="indice centralite proxi normalise")
    {
        cpn=1;
        a.dessinerTous(nom, poids, cdn, cd, cvp, cpn, cp, ci, ciN,cia);//Appel fonction pour dessiner
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les incides de centralite proxi normalises ont ete affiches avec succes "<<std::endl;
        std::cout<<std::endl<<"Le sommet marque est celui comportant le plus haut indice de centralite proxi normalise"<<std::endl;
    }
    else if (commande=="indice centralite vecteur propre")
    {
        cvp=1;
        a.dessinerTous(nom, poids, cdn, cd, cvp, cpn, cp, ci, ciN,cia);//Appel fonction pour dessiner
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les indices de centralite vecteur propre ont ete affiches avec succes "<<std::endl;
        std::cout<<std::endl<<"Le sommet marque est celui comportant le plus haut indice de centralite vecteur propre"<<std::endl;
    }
    else if (commande=="indice centralite intermediarite")
    {
        ci=1;
        a.dessinerTous(nom, poids, cdn, cd, cvp, cpn, cp, ci, ciN,cia);//Appel fonction pour dessiner
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les indices de centralite intermediarite non normalises ont ete affiches avec succes "<<std::endl;
        std::cout<<std::endl<<"Le sommet marque est celui comportant le plus haut indice de centralite intermediarite non normalise"<<std::endl;
    }
    else if (commande=="indice centralite intermediarite normalise")
    {
        ciN=1;
        a.dessinerTous(nom, poids, cdn, cd, cvp, cpn, cp, ci, ciN,cia);//Appel fonction pour dessiner
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les indices de centralite intermediarite normalises ont ete affiches avec succes "<<std::endl;
        std::cout<<std::endl<<"Le sommet marque est celui comportant le plus haut indice de centralite intermediarite normalise"<<std::endl;
    }
    else if (commande=="indice centralite proxi")
    {
        cp=1;
        a.dessinerTous(nom, poids, cdn, cd, cvp, cpn, cp, ci, ciN,cia);//Appel fonction pour dessiner
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les indices de centralite proxi non normalises ont ete affiches avec succes "<<std::endl;
        std::cout<<std::endl<<"Le sommet marque est celui comportant le plus haut indice de centralite proxi non normalise"<<std::endl;
    }
    else if (commande=="indice cia")
    {
        cia=1;
        a.dessinerTous(nom, poids, cdn, cd, cvp, cpn, cp, ci, ciN,cia);//Appel fonction pour dessiner
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les indices de centralite intermediarite non normalises ont ete affiches avec succes "<<std::endl;
        std::cout<<std::endl<<"L arete marque est celle comportant le plus haut indice de centralite intermediarite non normalise"<<std::endl;
    }
    else if (commande=="enlever centralite")
    {
        cdn=0;
        cd=0;
        cp=0;
        cpn=0;
        cvp=0;
        ci=0;
        ciN=0;
        cia=0;
        a.dessinerTous(nom, poids, cdn, cd, cvp, cpn, cp, ci, ciN,cia);//Appel fonction pour dessiner
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les indices de centralite ont ete retire avec succes "<<std::endl;
    }
    else if(commande=="vulnerabilite connexe")
    {
        SetConsoleTextAttribute(hConsole, 15);
        std::cout<<"Combien d'arete voulez-vous supprimer ? "<<std::endl;
        SetConsoleTextAttribute(hConsole, 10);
        std::cin>>taille;
        if(taille>a.getTaille())//Blindage sur le nombre d'arete à saisir
        {
            SetConsoleTextAttribute(hConsole, 12);
            std::cout<<"Le nombre d'arete a supprimer est trop eleve"<<std::endl;
            fflush(stdin);
        }
        else
        {
            for(size_t x=1; (int)x<taille+1; x++)
            {
                SetConsoleTextAttribute(hConsole, 15);
                std::cout<<"Entrez id de l'arete n"<<x<<" a supprimer : ";
                SetConsoleTextAttribute(hConsole, 10);
                std::cin>>idArete;
                id.push_back(idArete);
            }
            fflush(stdin);
            a.deleteArete(id);//Appel fonction pour montrer la vulnerabilite Connexe
            id.clear();//On supprime le vecteur d'id pour eviter qu'il se cumule si on effectue deux fois la vulnerabilite connexe
        }
    }
    else if(commande=="vulnerabilite indice")
    {
        SetConsoleTextAttribute(hConsole, 15);
        std::cout<<"Combien d'arete voulez-vous supprimer ? "<<std::endl;
        SetConsoleTextAttribute(hConsole, 10);
        std::cin>>taille2;
        if(taille2>a.getTaille())//blindage de la saisie d'arete a supprimer
        {
            SetConsoleTextAttribute(hConsole, 12);
            std::cout<<"Le nombre d'arete a supprimer est trop eleve"<<std::endl;
            fflush(stdin);
        }
        else
        {
            for(size_t x=1; (int)x<taille2+1; x++)
            {
                SetConsoleTextAttribute(hConsole, 15);
                std::cout<<"Entrez id de l'arete n"<<x<<" a supprimer : ";
                SetConsoleTextAttribute(hConsole, 10);
                std::cin>>idArete2;
                id2.push_back(idArete2);
            }
            fflush(stdin);
            a.deleteAreteIndice(id2);//Appel fonction pour montrer la vulnerabilite indice
            id2.clear();//On supprime le vecteur d'id pour eviter qu'il se cumule si on effectue deux fois la vulnerabilite indice
        }
    }
    else if(commande=="afficher centralite")
    {
        a.centralitevp();//Appel fonction qui calcule l'indice de centralite vecteur propre
        a.centralitedegre();//Appel fonction qui calcule l'indice de centralite de degre
        a.centralitedegreN();//Appel fonction qui calcule l'indice de centralite de degre normalise
        a.centraliteproxi();//Appel fonction qui calcule l'indice de centralite de proximite
        a.centraliteproxiN();//Appel fonction qui calcule l'indice de centralite de proximite nomarlise
        a.centraliteinter();//Appel fonction qui calcule l'indice de centralite d'intermediarite
        a.centraliteinterN();//Appel fonction qui calcule l'indice de centralite d'intermediarite normalise
        a.centraliteinterarete();//Appel fonction qui calcule l'indice de centralite d'intermediarite pour les aretes
        a.recupcdg();//Appel fonction qui calcule l'indice de centralite de degre global
        a.recupcpg();//Appel fonction qui calcule l'indice de centralite globale de proximite
        a.recupcig();
        a.affichercentralite();//Appel fonction qui affiche tous les indices de centralite

    }
    else//Blindage si commande invalide
    {
        SetConsoleTextAttribute(hConsole, 12);
        std::cerr<<std::endl<<"Commande invalide ou impossible"<<std::endl;
        SetConsoleTextAttribute(hConsole, 15);
    }
}

int main()
{

    std::string commande;
    std::string fichier;
    std::string fichierpoids;

    int taille;
    int taille2;
    int poids;
    int nom;
    int cdn;
    int cd;
    int cpn;
    int cp;
    int cvp;
    int ci;
    int ciN;
    int cia;
    int idArete;
    int idArete2;

    std::vector<int> id;
    std::vector<int> id2;

///Saisie nom du fichier graphe
    SetConsoleTextAttribute(hConsole, 15);
    std::cout<<"Nom du fichier : ";
    SetConsoleTextAttribute(hConsole, 10);
    std::cin>>fichier;

///Saisie nom du fichier poids
    SetConsoleTextAttribute(hConsole, 15);
    std::cout<<"Nom fichier poids : ";
    SetConsoleTextAttribute(hConsole, 10);
    std::cin>>fichierpoids;
    fflush(stdin);

    do
    {
        menu( commande, fichier,fichierpoids,nom, poids,cdn, cd,cvp, cpn, cp,ci,ciN,cia,id, id2, taille, taille2, idArete, idArete2);
    }
    while(commande!="exit");//la commande "exit" met fin au programme

    return 0;
}
