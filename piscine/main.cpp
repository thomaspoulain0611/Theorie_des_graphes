#include <iostream>
#include"Graphe.h"
#include "Svgfile.h"

HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

void menu( std::string& commande, std::string& fichier, int& nom, int& poids, int& cdn, int& cd, int& cpn, int& cp, std::vector<int>& id, std::vector<int>& id2, int& taille, int& taille2, int& idArete, int& idArete2)
{
    Graphe a(fichier);

    SetConsoleTextAttribute(hConsole, 13);
    std::cout<<std::endl<<"Options :"<<std::endl;
    SetConsoleTextAttribute(hConsole, 15);
    std::cout<<std::endl<<"exit"<<std::endl<<"dessiner"<<std::endl<<"afficher (graphe console)"<<std::endl<<"afficher centralite (console)"<<std::endl<<"afficher/enlever poids"<<std::endl<<"afficher/enlever noms"<<std::endl<<"indice centralite degre normalise"<<std::endl<<"indice centralite degre"<<std::endl<<"incide centralite proxi normalise"<<std::endl<<"indice centralite proxi"<<std::endl<<"enlever centralite"<<std::endl<<"vulnerabilite connexe"<<std::endl<<"vulnerabilite indice"<<std::endl<<"save (dans un fichier)"<<std::endl<<std::endl<<std::endl<<">";
    SetConsoleTextAttribute(hConsole, 10);
    std::getline(std::cin, commande);
    SetConsoleTextAttribute(hConsole, 15);
    fflush(stdin);

    if(commande=="exit")
    {
    }
    else if(commande=="afficher")
    {
        a.poidsarete();
        std::cout<<std::endl<<a<<std::endl;
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Votre graphe a ete affiche avec succes"<<std::endl;
    }
    else if(commande=="save")
    {
        a.enregistrer();
    }
    else if(commande=="dessiner")
    {
        cdn=0;
        cd=0;
        cp=0;
        cpn=0;
        poids=0;
        nom=0;
        a.dessinerTous(nom, poids, cdn, cd, cp, cpn);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Votre graphe a ete dessine avec succes"<<std::endl;
    }
    else if(commande=="afficher poids")
    {
        poids=1;
        a.dessinerTous(nom, poids, cdn, cd, cp, cpn);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les poids ont ete affiches avec succes "<<std::endl;
    }
    else if(commande=="enlever poids")
    {
        poids=0;
        a.dessinerTous(nom, poids, cdn, cd, cp, cpn);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les poids ont ete enleves avec succes "<<std::endl;
    }
    else if(commande=="afficher noms")
    {
        nom=1;
        a.dessinerTous(nom, poids, cdn, cd, cp, cpn);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les noms ont ete affiches avec succes "<<std::endl;
    }
    else if(commande=="enlever noms")
    {
        nom=0;
        a.dessinerTous(nom, poids, cdn, cd, cp, cpn);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les noms ont ete enleves avec succes "<<std::endl;
    }
    else if(commande=="indice centralite degre normalise")
    {
        cdn=1;
        a.dessinerTous(nom, poids, cdn, cd, cp, cpn);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les incides de centralite degres normalises ont ete affiches avec succes "<<std::endl;
        std::cout<<std::endl<<"Le sommet marque est celui comportant le plus haut indice de centralite degre normalise"<<std::endl;
    }
    else if(commande=="indice centralite degre")
    {
        cd=1;
        a.dessinerTous(nom, poids, cdn, cd, cp, cpn);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les indices de centralite degres non normalises ont ete affiches avec succes "<<std::endl;
        std::cout<<std::endl<<"Le sommet marque est celui comportant le plus haut indice de centralite degre non normalise"<<std::endl;
    }
    else if (commande=="indice centralite proxi normalise")
    {
        cpn=1;
        a.dessinerTous(nom, poids, cdn, cd, cp, cpn);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les incides de centralite proxi normalises ont ete affiches avec succes "<<std::endl;
        std::cout<<std::endl<<"Le sommet marque est celui comportant le plus haut indice de centralite proxi normalise"<<std::endl;
    }
    else if (commande=="indice centralite proxi")
    {
        cp=1;
        a.dessinerTous(nom, poids, cdn, cd, cp, cpn);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les indices de centralite proxi non normalises ont ete affiches avec succes "<<std::endl;
        std::cout<<std::endl<<"Le sommet marque est celui comportant le plus haut indice de centralite proxi non normalise"<<std::endl;
    }
    else if (commande=="enlever centralite")
    {
        cdn=0;
        cd=0;
        cp=0;
        cpn=0;
        a.dessinerTous(nom, poids, cdn, cd, cp, cpn);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les indices de centralite ont ete retire avec succes "<<std::endl;
    }
    else if(commande=="vulnerabilite connexe")
    {
        SetConsoleTextAttribute(hConsole, 15);
        std::cout<<"Combien d'arete voulez-vous supprimer ? "<<std::endl;
        SetConsoleTextAttribute(hConsole, 10);
        std::cin>>taille;
        for(size_t x=1; (int)x<taille+1;x++)
        {
            SetConsoleTextAttribute(hConsole, 15);
            std::cout<<"Entrez id de l'arete n"<<x<<" a supprimer : ";
            SetConsoleTextAttribute(hConsole, 10);
            std::cin>>idArete;
            id.push_back(idArete);
        }
        fflush(stdin);
        a.poidsarete();
        a.rempliradj();
        a.deleteArete(id);

    }
    else if(commande=="vulnerabilite indice")
    {
        SetConsoleTextAttribute(hConsole, 15);
        std::cout<<"Combien d'arete voulez-vous supprimer ? "<<std::endl;
        SetConsoleTextAttribute(hConsole, 10);
        std::cin>>taille2;
        for(size_t x=1; (int)x<taille2+1;x++)
        {
            SetConsoleTextAttribute(hConsole, 15);
            std::cout<<"Entrez id de l'arete n"<<x<<" a supprimer : ";
            SetConsoleTextAttribute(hConsole, 10);
            std::cin>>idArete2;
            id2.push_back(idArete2);
        }
        fflush(stdin);
        a.poidsarete();
        a.rempliradj();
        a.deleteAreteIndice(id2);
    }
    else if(commande=="afficher centralite")
    {
        //a.centralitevp();
        a.rempliradj();
        a.centralitedegre();
        a.centralitedegreN();
        a.poidsarete();
        a.centraliteproxi();
        a.centraliteproxiN();
        a.affichercentralite();

    }
    else
    {
        SetConsoleTextAttribute(hConsole, 12);
        std::cerr<<std::endl<<"Commande invalide ou impossible"<<std::endl;
        SetConsoleTextAttribute(hConsole, 15);
    }
}

int main()
{
    //Graphe a("test.txt");
    std::string commande;
    std::string fichier;

    /*a.rempliradj();
    a.centralitevp();
    a.centralitedegre();
    a.centralitedegreN();
    a.poidsarete();
    a.centraliteproxi();
    a.centraliteproxiN();
    a.affichercentralite();*/

    //a.comp_connexe(1);
    //std::cout<<std::endl;
   // std::cout<<"nb compo connexes "<<a.nb_comp_connexe(1, idArete);
    //a.deleteArete(0);

    int taille;
    int taille2;
    int poids;
    int nom;
    int cdn;
    int cd;
    int cpn;
    int cp;
    int idArete;
    int idArete2;

    std::vector<int> id;
    std::vector<int> id2;

    SetConsoleTextAttribute(hConsole, 15);
    std::cout<<"Nom du fichier : ";
    SetConsoleTextAttribute(hConsole, 10);
    std::cin>>fichier;
    fflush(stdin);
    do
    {
        menu(commande, fichier, nom, poids,cdn, cd, cpn, cp, id, id2, taille, taille2, idArete, idArete2);
    }
    while(commande!="exit");



    return 0;
}
