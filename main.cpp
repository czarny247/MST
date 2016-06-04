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
    //G.pokazGraf();
    //G.algorytmPrima();
    //G.pokazMDR();
    G.algorytmKruskala();
    G.pokazMDR();
//    vector<Graf*> Grafy;
//    for(int i = 0; i < 100; ++i)
//    {
//        Grafy.push_back(new Graf());
//        Grafy.at(i)->stworzGrafLosowy();
//    }

//    if(!Grafy.empty())
//    {
//        for(auto it = Grafy.begin(); it != Grafy.end(); ++it)
//        {
//            delete (*it);
//        }
//    }
    return 0;
}

