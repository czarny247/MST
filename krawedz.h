#ifndef KRAWEDZ_H
#define KRAWEDZ_H
#include "wierzcholek.h"

class Krawedz
{
private:
    Wierzcholek* w1 = nullptr;
    Wierzcholek* w2 = nullptr;
    int waga;
    bool wDrzewie; //wywalic

public:
    Krawedz();
    Krawedz(Wierzcholek& orgW1, Wierzcholek& orgW2,int& w);
    Krawedz(const Krawedz& orginalna);
    ~Krawedz();

    Krawedz & operator=(const Krawedz& inna);

    Wierzcholek* getW1() const { return w1; }
    Wierzcholek* getW2() const { return w2; }
    int zwrocWaga() const { return waga; }
    bool zwrocWDrzewie() const { return wDrzewie; }
    void ustawWDrzewie(bool wd) { wDrzewie = wd; }
    inline bool operator==(const Krawedz& rhs)
    {if(w1 == rhs.w1 && w2 == rhs.w2 && waga == rhs.waga) return true; else return false;}
    friend std::ostream& operator<<(std::ostream& ekran, const Krawedz& k);
};

#endif // KRAWEDZ_H
