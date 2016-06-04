#ifndef WIERZCHOLEK_H
#define WIERZCHOLEK_H
#include <iostream>

class Wierzcholek
{
private:
    int wX; //wspolrzedna X
    int wY; //wspolrzedna Y

public:
    Wierzcholek();
    Wierzcholek(int& x, int& y);
    Wierzcholek(const Wierzcholek& orginalny);
    ~Wierzcholek();

    int X() const {return wX;}
    int Y() const {return wY;}

    Wierzcholek operator= (const Wierzcholek& inny);
    inline bool operator==(const Wierzcholek& rhs)
    {if((wX == rhs.wX) && (wY == rhs.wY)) return true; else return false;}
    inline bool operator!=(const Wierzcholek& rhs)
    {if((wX == rhs.wX) && (wY == rhs.wY)) return false; else return true;}
    friend std::ostream& operator<< (std::ostream& ekran, const Wierzcholek& w);
};

inline bool operator==(const Wierzcholek& lhs, const Wierzcholek& rhs)
{if((lhs.X() == rhs.X()) && (lhs.Y() == rhs.Y())) return true; else return false;}

#endif // WIERZCHOLEK_H
