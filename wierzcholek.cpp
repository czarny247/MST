#include "wierzcholek.h"

//int Wierzcholek::licznik = 0;

Wierzcholek::Wierzcholek()
    :wX(0), wY(0)
{
    //std::cout << "\nWierzcholek()\n";
    //++licznik;
}

Wierzcholek::Wierzcholek(int &x, int &y)
    :wX(x),wY(y)
{
    //this->wX = x;
    //this->wY = y;
    //++licznik;
}
Wierzcholek::Wierzcholek(const Wierzcholek& orginalny)
    :wX(orginalny.wX), wY(orginalny.wY)
{
    //++licznik;
}

Wierzcholek::~Wierzcholek()
{
}

std::ostream& operator<< (std::ostream& ekran, const Wierzcholek& w)
{
    ekran << "(" << w.wX << "," << w.wY << ")";
    return ekran;
}

Wierzcholek Wierzcholek::operator= (const Wierzcholek& inny)
{
    wX = inny.wX;
    wY = inny.wY;
    return *this;
}
