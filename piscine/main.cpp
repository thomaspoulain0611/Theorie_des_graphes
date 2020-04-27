#include <iostream>
#include"Graphe.h"
#include "Svgfile.h"

HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

void menu(Svgfile& svgout,std::string& commande, std::string& fichier)
{
    Graphe a("graphe.txt");
    SetConsoleTextAttribute(hConsole, 9);
    std::cout<<std::endl<<"Options :"<<std::endl;
    SetConsoleTextAttribute(hConsole, 15);
    std::cout<<std::endl<<"exit"<<std::endl<<"load (fichier)"<<std::endl<<"reload (fichier)"<<std::endl<<"afficher (graphe console)"<<std::endl<<"dessiner (Graphe)"<<std::endl<<"Afficher Poids"<<std::endl<<"Afficher Noms"<<std::endl<<"save (dans un fichier)"<<std::endl<<std::endl<<std::endl<<">";
    SetConsoleTextAttribute(hConsole, 10);
    std::getline(std::cin, commande);
    SetConsoleTextAttribute(hConsole, 15);
    fflush(stdin);
    if(commande=="exit")
    {
    }
    /*else if(commande=="load")
    {

        std::cout<<std::endl<<"nom du fichier : ";
        std::cin>>fichier;
        fflush(stdin);

    }
    else if(commande=="load")
    {
        SetConsoleTextAttribute(hConsole, 12);
        std::cerr<<std::endl<<"Vous avez deja charge un fichier"<<std::endl;
        SetConsoleTextAttribute(hConsole, 15);
    }*/
    else if(commande=="afficher")
    {
        a.poidsarete();
        std::cout<<a<<std::endl;
    }
    else if(commande=="dessiner")
    {
        a.poidsarete();
        a.dessiner(svgout);
    }
    else if(commande=="afficher poids")
    {
        a.poidsarete();
        a.ecrireTousPoids(svgout);
    }
    else if(commande=="afficher noms")
    {
        a.poidsarete();
        a.ecrireTousNoms(svgout);
    }
}

int main()
{
    Svgfile svgout;
    std::string commande;
    std::string fichier;

    do
    {
        menu(svgout, commande, fichier);
    }
    while(commande!="exit");

    return 0;
}
