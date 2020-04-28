#include <iostream>
#include"Graphe.h"
#include "Svgfile.h"

HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

void menu( std::string& commande, std::string& fichier, int& nom, int& poids, int& cdn, int& cd, int& cpn, int& cp)
{



    Graphe a(fichier);
    SetConsoleTextAttribute(hConsole, 13);

    std::cout<<std::endl<<"Options :"<<std::endl;
    SetConsoleTextAttribute(hConsole, 15);
    std::cout<<std::endl<<"exit"<<std::endl<<"dessiner"<<std::endl<<"afficher (graphe console)"<<std::endl<<"Afficher Poids"<<std::endl<<"enlever poids"<<std::endl<<"Afficher Noms"<<std::endl<<"enlever noms"<<std::endl<<"indice centralite degrenormalise"<<std::endl<<"indice centralite degre"<<std::endl<<"incide centralite poids normalise"<<std::endl<<"indice centralite poids"<<std::endl<<"save (dans un fichier)"<<std::endl<<std::endl<<std::endl<<">";
    SetConsoleTextAttribute(hConsole, 10);
    std::getline(std::cin, commande);
    SetConsoleTextAttribute(hConsole, 15);
    fflush(stdin);

    if(commande=="exit")
    {
    }

    else if(commande=="dessiner")
    {
        cdn=0;
        cd=0;
        cp=0;
        cpn=0;
        poids=0;
        nom=0;
        a.poidsarete();
        a.dessinerTous(nom, poids, cdn, cd, cp, cpn);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Votre graphe a ete dessine avec succes"<<std::endl;

    }
    else if(commande=="afficher poids")
    {
        poids=1;
        a.poidsarete();
        a.dessinerTous(nom, poids, cdn, cd, cp, cpn);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les poids ont ete affiches avec succes "<<std::endl;

    }
    else if(commande=="enlever poids")
    {
        poids=0;
        a.poidsarete();
        a.dessinerTous(nom, poids, cdn, cd, cp, cpn);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les poids ont ete enleves avec succes "<<std::endl;
    }

    else if(commande=="afficher noms")
    {
        nom=1;
        a.poidsarete();
        a.dessinerTous(nom, poids, cdn, cd, cp, cpn);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les noms ont ete affiches avec succes "<<std::endl;
    }
    else if(commande=="enlever noms")
    {
        nom=0;
        a.poidsarete();
        a.dessinerTous(nom, poids, cdn, cd, cp, cpn);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les noms ont ete enleves avec succes "<<std::endl;
    }
    else if(commande=="afficher")
    {
        a.poidsarete();
        std::cout<<std::endl<<a<<std::endl;
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Votre graphe a ete affiché avec succes"<<std::endl;
    }
    else if(commande=="indice centralité degré normalisé")
    {
        cdn=1;
        a.poidsarete();
        a.dessinerTous(nom, poids, cdn, cd, cp, cpn);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les incides de centralité des degrés normalisés ont ete affichés avec succes "<<std::endl;
    }
    else if(commande=="incide centralité degré")
    {
        cd=1;
        a.poidsarete();
        a.dessinerTous(nom, poids, cdn, cd, cp, cpn);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les indices de centralité des degrés non normalisés ont été affichés avec succes "<<std::endl;
    }
    else if (commande=="incide centralité p normalisé")
    {
        cpn=1;
        a.poidsarete();
        a.dessinerTous(nom, poids, cdn, cd, cp, cpn);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les incides ce dentralité des poids normalisés ont été affichés avec succes "<<std::endl;
    }
    else if (commande=="incide centralité p")
    {
        cp=1;
        a.poidsarete();
        a.dessinerTous(nom, poids, cdn, cd, cp, cpn);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les indices de centralité des poids non normalisés ont été affichés avec succes "<<std::endl;
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

    std::string commande;
    std::string fichier;

    /*a.centralitedegre();
    a.centralitedegreN();
    a.poidsarete();

    a.centraliteproxi();



    a.affichercentralite();*/

    int poids;
    int nom;
    int cdn;
    int cd;
    int cpn;
    int cp;

    std::cout<<"nom du fichier : ";
    std::cin>>fichier;


    do
    {
        menu(commande, fichier, nom, poids,cdn, cd, cpn, cp);
    }
    while(commande!="exit");



    return 0;
}
