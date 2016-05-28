#include "wierzcholek.h"

//int Wierzcholek::licznik = 0;

Wierzcholek::Wierzcholek()
    :wX(0), wY(0), wKrawedzi(false), odwiedzony(false)
{
    //std::cout << "\nWierzcholek()\n";
    //++licznik;
}

Wierzcholek::Wierzcholek(int &x, int &y)
    :wX(x),wY(y), wKrawedzi(false), odwiedzony(false)
{
    //this->wX = x;
    //this->wY = y;
    //++licznik;
}
Wierzcholek::Wierzcholek(const Wierzcholek& orginalny)
    :wX(orginalny.wX), wY(orginalny.wY), wKrawedzi(orginalny.wKrawedzi), odwiedzony(orginalny.odwiedzony)
{
    //++licznik;
}

Wierzcholek::~Wierzcholek()
{
}

bool Wierzcholek::zwrocCzyWkrawedzi() const
{
    return wKrawedzi;
}

void Wierzcholek::ustawCzyWkrawedzi(bool wk)
{
    wKrawedzi = wk;
}

bool Wierzcholek::zwrocOdwiedzony() const
{
    return odwiedzony;
}

void Wierzcholek::ustawOdwiedzony(bool o)
{
    odwiedzony = o;
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
    wKrawedzi = inny.wKrawedzi;
    odwiedzony = inny.odwiedzony;

    return *this;
}
