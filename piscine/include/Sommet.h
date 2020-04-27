#ifndef SOMMET_H
#define SOMMET_H


class Sommet
{
    public:
        Sommet();
        ~Sommet();

        int getId();

        void setId(int id);

    private:
        int m_id;
};

#endif // SOMMET_H
