#include <iostream>
#include"Graphe.h"



int main()
{
    Svgfile svgout;
    Graphe a("graphe.txt");
    a.poidsarete();
    std::cout<<a<<std::endl;
    a.dessiner(svgout);
    return 0;
}
