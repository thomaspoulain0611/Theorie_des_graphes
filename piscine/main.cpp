#include <iostream>
#include"Graphe.h"



int main()
{
    Svgfile svgout;
    Graphe a("graphe.txt");
    a.poidsarete();
    std::cout<<a<<std::endl;
    a.dessiner(svgout);
<<<<<<< HEAD
=======





>>>>>>> 8d26d411f18301f909c0d7e0c8c3cfb2484b3588
    return 0;
}
