#include <iostream>
#include <graf.h>
#include <time.h>

using namespace std;

int main()
{
    //srand(time(NULL));
    Graf G;
    //G.stworzGrafZPliku("wierzcholki.txt","wagi.txt");
    G.stworzGrafLosowy();
    G.pokazGraf();
    G.algorytmPrima();
    G.pokazMDR();
    return 0;
}

