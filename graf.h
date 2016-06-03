#ifndef GRAF_H
#define GRAF_H
#include <vector>
#include "krawedz.h"
#include <string>
#include <random>

using krIt = std::vector<Krawedz*>::iterator;

class Graf
{
private:
    std::vector<Krawedz*> krawedzie;
    std::vector<Wierzcholek*> wierzcholki;
    std::vector<Krawedz*> minimalneDrzewoRozpinajace;
    double gestoscGrafu;
    static std::random_device rd;
    static std::mt19937 mt;
    static std::uniform_int_distribution<int> dist;
public:
    Graf();
    Graf(std::vector<Wierzcholek*>& w);
    Graf(double g);
    ~Graf();
    void stworzGrafZPliku(std::string nazwa1Pliku, std::string nazwa2Pliku); //dla danych z pliku (gestosc grafu == 1)
    void stworzGrafLosowy(); //dla losowania grafu o zadanej gestosci
    void dodajWierzcholek(int x, int y);
    void dodajKrawedzie(std::vector<int>& wagi);
    void pokazGraf();
    void algorytmPrima();
    void znajdzKrMin(std::vector<Wierzcholek*>& rozpatrzone, std::vector<Krawedz*>& krawedzie, Krawedz *&pMin);
    Wierzcholek zwrocNastepny(std::vector<Wierzcholek*>& rozpatrzone, Krawedz* &k);
    void pokazMDR();
    //static int licznik;
};

#endif // GRAF_H

