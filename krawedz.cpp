#include "krawedz.h"

Krawedz::Krawedz()
    :w1(nullptr), w2(nullptr), waga(0), wDrzewie(false)
{

}

Krawedz::Krawedz(Wierzcholek& orgW1, Wierzcholek& orgW2, int& w)
    :w1(&orgW1),w2(&orgW2),waga(w), wDrzewie(false)
{
}

Krawedz::Krawedz(const Krawedz& orginalna)
    :w1(orginalna.w1), w2(orginalna.w2), waga(orginalna.waga), wDrzewie(orginalna.wDrzewie)
{

}

Krawedz::~Krawedz()
{
    if(w1!=nullptr)
    {
        delete w1;
        w1=nullptr;
    }


    if(w2!=nullptr)
    {
        delete w2;
        w2=nullptr;
    }
}

Krawedz & Krawedz::operator=(const Krawedz& inna)
{
    delete w1;
    w1 = inna.w1;
    delete w2;
    w2 = inna.w2;

    return *this;
}

std::ostream& operator<<(std::ostream& ekran, const Krawedz& k)
{
    ekran << "[" << *k.w1 << "]->[" << *k.w2 << "]: " << k.waga << std::endl;
    return ekran;
}
