#include <iostream>
#include"Graphe.h"
#include "Svgfile.h"

HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

void menu( std::string& commande, std::string& fichier, int& nom, int& poids)
{

    Graphe a("graphe.txt");

    a.poidsarete();
    std::cout<<a<<std::endl;
    a.dessiner(svgout);

    SetConsoleTextAttribute(hConsole, 9);

    Graphe a(fichier);
    SetConsoleTextAttribute(hConsole, 13);

    std::cout<<std::endl<<"Options :"<<std::endl;
    SetConsoleTextAttribute(hConsole, 15);
    std::cout<<std::endl<<"exit"<<std::endl<<"dessiner"<<std::endl<<"afficher (graphe console)"<<std::endl<<"Afficher Poids"<<std::endl<<"enlever poids"<<std::endl<<"Afficher Noms"<<std::endl<<"enlever noms"<<std::endl<<"save (dans un fichier)"<<std::endl<<std::endl<<std::endl<<">";
    SetConsoleTextAttribute(hConsole, 10);
    std::getline(std::cin, commande);
    SetConsoleTextAttribute(hConsole, 15);
    fflush(stdin);

    if(commande=="exit")
    {
    }
    else if(commande=="dessiner" )
    {



        std::cout<<std::endl<<"nom du fichier : ";
        std::cin>>fichier;
        fflush(stdin);

        poids=0;
        nom=0;
        a.poidsarete();
        a.dessinerTous(nom, poids);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Votre graphe a ete dessine avec succes"<<std::endl;

    }
    else if(commande=="afficher poids")
    {
        poids=1;
        a.poidsarete();
        a.dessinerTous(nom, poids);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les poids ont ete affiches avec succes "<<std::endl;

    }
    else if(commande=="enlever poids")
    {
        poids=0;
        a.poidsarete();
        a.dessinerTous(nom, poids);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les poids ont ete enleves avec succes "<<std::endl;
    }

    else if(commande=="afficher noms")
    {
        nom=1;
        a.poidsarete();
        a.dessinerTous(nom, poids);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les noms ont ete affiches avec succes "<<std::endl;
    }
    else if(commande=="enlever noms")
    {
        nom=0;
        a.poidsarete();
        a.dessinerTous(nom, poids);
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Les noms ont ete enleves avec succes "<<std::endl;
    }
    else if(commande=="afficher")
    {
        a.poidsarete();
        std::cout<<std::endl<<a<<std::endl;
        SetConsoleTextAttribute(hConsole, 14);
        std::cout<<std::endl<<"Votre graphe a ete affiche avec succes"<<std::endl;
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
    Graphe a("graphe.txt");
    a.centralitedegre();
    a.centralitedegreN();
    a.poidsarete();

    a.centraliteproxi();



    a.affichercentralite();


    /*do
=======
    int poids;
    int nom;

    std::cout<<"nom du fichier : ";
    std::cin>>fichier;

    do
>>>>>>> 6dbd61fb2929f0c52c539797783789af99145ff3
    {
        menu(commande, fichier, nom, poids);
    }
    while(commande!="exit");*/



    return 0;
}
