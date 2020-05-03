#include "Sommet.h"
#include <sstream>

// constructeur a partir d'un flux
Sommet::Sommet(std::istream& is)
{
    double x;
    double y;
    //char nom;
    is>>m_id>>m_nom>>x>>y;
    m_coords.first=x;
    m_coords.second=y;
    m_cd=0;
    m_cdn=0;
    m_cp=0;
    m_cpn=0;
    m_couleur='B';

}


Sommet::~Sommet()
{
    //dtor
}
// getter permettant d'avoir l'id du sommet
int Sommet::getId()const
{
    return m_id;
}
// setter attribuant une valeur à l'id du sommet
void Sommet::setId(int id)
{
    m_id=id;
}

//getter permettant d'obtenir le nom du sommet
std::string Sommet::getNom()const
{
    return m_nom;

}
//getter permettant d'avoir la coordonnee en x du sommet
double Sommet::getx()const
{
    return m_coords.first;
}
//getter permettant d'avoir la coordonnee en y du sommet
double Sommet::gety()const
{
    return m_coords.second;
}
// getter permettant d'obtenir la valeur de l'indice de centralite de degret du sommet
double Sommet::getcd()const
{
    return m_cd;
}
//getter permettant d'obtenir la liste de tous les adjacents du sommet etudie
std::vector<Sommet*> Sommet::getAdj()const
{
    return m_adj;
}
// setter permettant d'attribuer un vecteur au vecteur 'adjacence du sommet
void Sommet::setVectAdj(std::vector<Sommet*> thomaslpb)
{
    m_adj=thomaslpb;
}
// getter permettant d'obtenir la valeur de l'indice de centralite de degret normalise du sommet
double Sommet::getcdn()const
{
    return m_cdn;
}
// setter permettant d'attribuer une valeur à l'indice de centralite de degre normalise du sommet
void Sommet::setcdn(double cdn)
{
    m_cdn=cdn;
}
// getter permettant d'obtenir la valeur de l'indice de centralite de proximite du sommet
double Sommet::getcp()const
{
    return m_cp;
}
// setter permettant d'attribuer une valeur à l'indice de centralite de proximite du sommet
void Sommet::setcp(double cp)
{
    m_cp=cp;
}
// getter permettant d'obtenir la valeur de l'indice de centralite de proximite normalise du sommet
double Sommet::getcpn()const
{
    return m_cpn;
}
// setter permettant d'attribuer une valeur à l'indice de centralite de proximite normalise du sommet
void Sommet::setcpn(double cpn)
{
    m_cpn=cpn;
}

// getter permettant d'obtenir la valeur de l'indice de centralite de vecteur propre du sommet
double Sommet::getcvp()const
{
    return m_cvp;
}
// setter permettant d'attribuer une valeur à l'indice de centralite de vecteur propre du sommet
void Sommet::setcvp(double cvp)
{
    m_cvp=cvp;
}
// setter permettant d'attribuer une valeur à l'indice de centralite de degre du sommet
void Sommet::setcd( double cd)
{
    m_cd=cd;
}
// getter permettant d'obtenir la valeur de csi du sommet
double Sommet::getcsi()const
{
    return m_csi;

}
// setter permettant d'attribuer une valeur au csi( qui sert pour trouver l'indice de vecteur propre) du sommet
void Sommet::setcsi(double csi)
{
    m_csi=csi;

}

// getter permettant d'obtenir la valeur de l'indice de centralite d'intermediarite du sommet dans le cas ou il n'y a qu'un pcc entre chaque sommet
double Sommet::getci1()const
{
    return m_ci1;
}
// getter permettant d'obtenir la valeur de l'indice de centralite d'intermediarite normalise du sommet dans le cas ou il n'ya qu'un pcc entre chaque sommet
double Sommet::getci1n()const
{
    return m_ci1n;
}
// setter permettant d'attribuer une valeur à l'indice de centralite d'intermediarite du sommet dans le cas ou il n'y a qu'un pcc entre chaque sommet
void Sommet::setci1(double ci1)
{
    m_ci1=ci1;
}
// setter permettant d'attribuer une valeur à l'indice de centralite d'intermediarite normalise du sommet dans le cas ou il n'y a qu'un pcc entre chaque sommet
void Sommet::setci1n (double ci1n)
{
    m_ci1n=ci1n;
}
// getter permettant d'obtenir la valeur de l'indice de centralite d'intermediarite du sommet
double Sommet::getci()const
{
    return m_ci;
}
// setter permettant d'attribuer une valeur à l'indice de centralite d'intermediarite du sommet
void Sommet::setci(double ci)
{
    m_ci=ci;
}
// getter permettant d'obtenir la valeur de l'indice de centralite d'intermediarite normalisedu sommet
double Sommet::getciN()const
{
    return m_ciN;
}
// setter permettant d'attribuer une valeur à l'indice de centralite d'intermediarite normalise du sommet
void Sommet::setciN(double ciN)
{
    m_ciN=ciN;
}
// getter permettant d'obtenir la couleur du sommet
char Sommet::get_color() const

{
    return m_couleur;// on récupère la couleur du sommet
}
// setter permettant d'attribuer une couleur au sommet
void Sommet::set_color(char color)
{
    m_couleur=color;// on attribue une couleur au sommmet considéré
}
// setter permettant d'attribuer une distance(pour dijkstra) au sommet
void Sommet::set_distance(double distance)
{
    m_distance=distance;// on attribue la distance entre le sommet considéré et le sommet d'arrivée
}
// getter permettant d'obtenir la distance du sommet (pour dijkstra)
double Sommet::get_distance() const
{
    return m_distance;// on récupère cette distance
}
// getter permettant d'obtenir la valeur de la taille de la liste d'adjacence du sommet
size_t Sommet::get_nb_adj() const
{
    return m_adj.size();// on récupère le nombre de successeurs du sommet considéré
}
// getter permettant d'obtenir le sommet situe à la case x de la liste d'adjacence du sommet etudie
Sommet* Sommet::get_adj(int x) const
{
    return m_adj[x];// on récupère le successeur de la case i du vecteur des successeurs du sommet considéré
}
// setter permettant de rajouter un sommet dans la liste d'adjacence du sommet parcouru
void Sommet::setadj(Sommet* s1)
{
    m_adj.push_back(s1);
}

///Fonction dessin

void Sommet::dessiner(Svgfile& svgout)
{
    svgout.addDisk(this->m_coords.first, this->m_coords.second, 3, "blue");//Dessin d'un cercle de rayon 3 et de couleur blue pour un sommet
}

void Sommet::dessinerMarque(Svgfile& svgout)
{
    svgout.addDisk(this->m_coords.first, this->m_coords.second, 8, "red");//Dessin d'un cercle de rayon 8 et de couleur rouge pour un sommet
}

void Sommet::ecrireNom(Svgfile& svgout)
{
    svgout.addText(this->m_coords.first, this->m_coords.second, this->m_nom, "black");//Ecriture nom d'un sommet
}

void Sommet::ecrireCentraliteDegreN(Svgfile& svgout)
{
    svgout.addText(this->m_coords.first, this->m_coords.second, this->nbToStrg(m_cdn),"black");//Ecriture centralite d'un sommet
}

void Sommet::ecrireCentraliteDegre(Svgfile& svgout)
{
    svgout.addText(this->m_coords.first, this->m_coords.second, this->nbToStrg(m_cd),"black");//Ecriture centralite d'un sommet
}

void Sommet::ecrireCentraliteP(Svgfile& svgout)
{
    svgout.addText(this->m_coords.first, this->m_coords.second, this->nbToStrg(m_cp),"black");//Ecriture centralite d'un sommet
}

void Sommet::ecrireCentralitePN(Svgfile& svgout)
{
    svgout.addText(this->m_coords.first, this->m_coords.second, this->nbToStrg(m_cpn),"black");//Ecriture centralite d'un sommet
}

void Sommet::ecrireCentraliteVP(Svgfile& svgout)
{
    svgout.addText(this->m_coords.first, this->m_coords.second, this->nbToStrg(m_cvp),"black");//Ecriture centralite d'un sommet
}

void Sommet::ecrireCentraliteCI(Svgfile& svgout)
{
    svgout.addText(this->m_coords.first, this->m_coords.second, this->nbToStrg(m_ci),"black");//Ecriture centralite d'un sommet
}

void Sommet::ecrireCentraliteCIN(Svgfile& svgout)
{
    svgout.addText(this->m_coords.first, this->m_coords.second, this->nbToStrg(m_ciN),"black");//Ecriture centralite d'un sommet
}

///Transformation d'un nombre en string

std::string Sommet::nbToStrg(double nombre)const
{
    std::ostringstream a;
    a<<nombre;
    return a.str();
}
