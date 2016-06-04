#include "graf.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <algorithm> //std::min_element, std::random_shuffle
#include <time.h>

//std::random_device Graf::rd;
//std::mt19937 Graf::mt(rd());
//std::uniform_int_distribution<int> Graf::dist(0,1);

Graf::Graf()
    :gestoscGrafu(1)
{
    srand(time(NULL));
}

Graf::Graf(std::vector<Wierzcholek*> &w)
    :wierzcholki(w)
{
    srand(time(NULL));
}

Graf::Graf(double g)
    :gestoscGrafu(g)
{
    srand(time(NULL));
}

void Graf::stworzGrafZPliku(std::string nazwa1Pliku, std::string nazwa2Pliku)
{
    //TO-DO!
    //obsluzyc sytuacje gdy w pliku bedzie tylko 1 wierzcholek!
    //obsluzyc sytuacje gdy ilosc wierzcholkow i ilosc wag dla krawedzi nie beda odpowiednie!
    //1.wczytywanie wierzcholkow
    int x = 0, y = 0, w = 0;
    char delimiter = '0';
    //otwarcie pliku
    std::fstream plik1(nazwa1Pliku,std::ios::in);
    if(plik1.good())
    {
        //wczytujemy dane do grafu
        std::string wiersz;
        do
        {
            std::getline(plik1,wiersz);
            std::cout << wiersz << std::endl;
            std::istringstream iss(wiersz);
            //std::cout << "Jestem w pliku.\n";
            iss >> x >> delimiter >> y;
            //std::cout << x << delimiter << y << std::endl;
            dodajWierzcholek(x,y);
        }while(!plik1.eof());

        plik1.close();
    }
    else
    {
        std::cout << "Problem z otwarciem pliku.\n";
        //komunikat o niepoprawnym zachowaniu pliku
    }

    //2.wczytywanie krawedzi
    std::vector<int> wagi;
    std::fstream plik2(nazwa2Pliku,std::ios::in);
    if(plik2.good())
    {
        //wczytujemy dane do grafu
        std::string wiersz;
        do
        {
            std::getline(plik2,wiersz);
            std::cout << wiersz << std::endl;
            std::istringstream iss(wiersz);
            //std::cout << "Jestem w pliku.\n";
            iss >> w;
            wagi.push_back(w);

        }while(!plik2.eof());

        plik2.close();
    }
    else
    {
        std::cout << "Problem z otwarciem pliku.\n";
        //komunikat o niepoprawnym zachowaniu pliku
    }
    //dodaj krawedzie
    dodajKrawedzie(wagi);
}

void Graf::dodajWierzcholek(int x, int y)
{
    //std::cout << "Dodaje wierzcholek.\n";
    wierzcholki.push_back(new Wierzcholek(x,y));
}

void Graf::dodajKrawedzie(std::vector<int>& wagi)
{
    int w = 0;
    for(int i = 0; i < wierzcholki.size()-1; ++i)
    {
        for(int j = i+1; j < wierzcholki.size(); j++)
        {
            //std::cout << "[i=" << i << "][j=" << j << "],[w=" << w << "]" << std::endl;
            krawedzie.push_back(new Krawedz(new Wierzcholek(*wierzcholki[i]),new Wierzcholek(*wierzcholki[j]),w));
            w++;
        }
    }


    //w[1] - j.w. poza [0]
    //w[2] - j.w. poza [0],[1]
}

void Graf::pokazGraf()
{
    if(!wierzcholki.empty())
    {
        //std::cout << "Jest przynajmniej jeden wierzcholek w grafie.\n";
        for(auto it = wierzcholki.begin(); it != wierzcholki.end(); ++it)
        {
            //(**it).pokazWierzcholek();
            std::cout << "w[" << wierzcholki.size()-std::distance(it,wierzcholki.end()) << "]" << **it << std::endl;
        }

        std::cout << "Sposob prezentacji krawedzi grafu:\n";
        std::cout << "[Wierzcholek]->[Inny_Wierzcholek]: Waga\n";
        for(auto it = krawedzie.begin(); it != krawedzie.end(); ++it)
        {
            std::cout << **it;
        }
    }
}

Graf::~Graf()
{
    for (auto it = wierzcholki.begin() ; it != wierzcholki.end(); ++it)
       {
        delete (*it);
       }
       wierzcholki.clear();
}

void Graf::stworzGrafLosowy() //zadana gestosc oraz ilosc wierzcholkow, losowe polaczenia
{
    //pytanie o gestosc
    //dodac sprawdzenie czy gestosc jest poprawna - mozesz to dopisac w watku dotyczacym przyszlych usprawnien programu
    //nie zaimplementowales tego z powodu ograniczonego czasu
    std::cout << "Podaj gestosc grafu(100%->1): "; //zapobiec wprowadzeniom niepoprawnych danych
    std::cin >> gestoscGrafu;
    if(gestoscGrafu>1.0) gestoscGrafu=1.0; //narazie zamiast obslugi wyjatku
    //tworzenie macierzy sasiedztwa
    int liczbaWierzcholkow = 0;
    std::cout << "Podaj liczbe wierzcholkow: ";
    std::cin >> liczbaWierzcholkow;

    //gestoscGrafu = liczbaKrawedzi/liczbaKrawedziMax
    int liczbaKrawedziMax = (liczbaWierzcholkow*(liczbaWierzcholkow-1))/2;
    int liczbaKrawedzi = gestoscGrafu*liczbaKrawedziMax;
    //std::cout << "\nliczbaKrawedzi: " << liczbaKrawedzi << std::endl;
    int licznikStworzonychKrawedzi = 0;
    //std::vector<bool> v(liczbaWierzcholkow*liczbaWierzcholkow);
    //std::fill(v.begin(), v.begin() + liczbaKrawedzi, 1);
    //std::fill(v.begin() + (liczbaKrawedzi+1),v.end(),0);
    //for(auto iv : v) std::cout << iv << std::endl;
    //tworzenie macierzy sasiedztwa - pozniej przeniesc do osobnej metody
    bool MS[liczbaWierzcholkow][liczbaWierzcholkow];
    std::fill(MS[0],MS[0] + liczbaWierzcholkow*liczbaWierzcholkow,0);
    std::vector<bool> potencjalne(liczbaWierzcholkow*liczbaWierzcholkow);
    std::fill(potencjalne.begin(),potencjalne.end(),0);
    if(gestoscGrafu==1.0)
    {
        while(licznikStworzonychKrawedzi!=liczbaKrawedzi)
        {
            for(int i = 0; i < liczbaWierzcholkow; ++i)
            {
                for(int j = 0; j < liczbaWierzcholkow-1; ++j) //z kazdego w. maksymalnie W-1 krawedzi
                {
                    if(i!=j) //wierzcholek nie sasiaduje ze soba...
                    {
                    //jesli gdzies nie ma krawedzi to probujemy ja wylosowac
                    //oraz jesli stworzonych krawedzi jest mniej niz ma byc
                    //oraz jesli dane sasiedztwo juz jest (tylko w druga strone)
                        if(!MS[i][j] && licznikStworzonychKrawedzi<liczbaKrawedzi)
                        {
                            if(!MS[j][i]) MS[i][j] = true; //zeby nie powielac krawedzi
                            if(MS[i][j]) ++licznikStworzonychKrawedzi; //std::cout << licznikStworzonychKrawedzi << std::endl;
                        }
                    }
                    else MS[i][j] = false; //...dlatego wartosc jego sasiedztwa to false(0)
                }
            }
        //std::cout << licznikStworzonychKrawedzi << std::endl;
        }
    }
    else
    {
        int suma = 0;
        while(suma<=liczbaKrawedzi)
        {
            //srand(time(NULL));
            for(int i = 0; i < potencjalne.size(); ++i) //na przekatnej sa "false", poniewaz nie tworzymy petli
            //np. nie mozemy stworzyc krawedzi [0]->[0]
            {
                if(i % (liczbaWierzcholkow+1) != 0)
                {
                   potencjalne[i] = true;
                   if(potencjalne[i] == true)
                   {
                       if(i*(liczbaWierzcholkow+1) < potencjalne.size()-1)
                       {
                           potencjalne[i*liczbaWierzcholkow] = true;
                           //std::cout << i << " " << i*liczbaWierzcholkow << std::endl;
                       }
                       ++suma;
                   }
                }
            }
        }

        //std::cout << suma << std::endl;
        //for(auto z : potencjalne) std::cout << " " << z;
        int i = 0 , j = 0;
        while(licznikStworzonychKrawedzi<liczbaKrawedzi)
        {
            //std::cout << (i*liczbaWierzcholkow)+j << std::endl;
            if(potencjalne[(i*liczbaWierzcholkow)+j]==true)
            {
                MS[i][j] = rand() % 2;
                //std::cout << MS[i][j] << std::endl;
                if(MS[i][j]==true)
                {
                    ++licznikStworzonychKrawedzi;
                    if(((i*liczbaWierzcholkow)+j)*liczbaWierzcholkow < (liczbaWierzcholkow*liczbaWierzcholkow))
                    {
                        potencjalne[(i*liczbaWierzcholkow)+j]=false;
                    }
                }
            }
            ++j;
            if(j==liczbaWierzcholkow) ++i;
            if(i==liczbaWierzcholkow) i = 0;
            if(j==liczbaWierzcholkow) j = 0;
            //std::cout << licznikStworzonychKrawedzi << std::endl;
        }

    }


    //wyswietlanie macierzy sasiedztwa - bylo potrzebne do testow
//    std::cout << "    ";
//    for(int i=0; i<liczbaWierzcholkow; ++i)
//    {
//        std::cout << "[" << i << "]";
//    }

//    std::cout << std::endl;

//    for(int i=0; i<liczbaWierzcholkow; ++i)
//    {
//        std::cout << "[" << i << "] ";
//        for(int j=0; j<liczbaWierzcholkow; ++j)
//        {
//            std::cout << " " << MS[i][j] << " ";
//        }

//        std::cout << std::endl;
//    }
    //tworzenie grafu na podstawie macierzy sasiedztwa

    for(int i = 0; i < liczbaWierzcholkow; ++i)
    {
        dodajWierzcholek(rand()%50,rand()%50); //dodac niepowtarzanie sie wspolrzednych
    }

    for(int i = 0; i < liczbaWierzcholkow; ++i)
    {
        for(int j = 0; j < liczbaWierzcholkow; ++j)
        {
            int w = rand() % 100 + 1; //losowanie wagi
            if(MS[i][j])krawedzie.push_back(new Krawedz(new Wierzcholek(*wierzcholki[i]),new Wierzcholek(*wierzcholki[j]),w));
        }
    }
}

void Graf::algorytmPrima()
{
    int idxStart = 0;
    std::cout << "Podaj numer wierzcholka startowego (numerowane od [0]!): ";
    std::cin >> idxStart;

    std::vector<Krawedz*> kr = krawedzie; //z tego wektora bedziemy usuwac krawedzie ktore beda juz wykorzystane w drzewie rozpinajacym
    std::vector<Wierzcholek*> rozpatrzone {wierzcholki[idxStart]}; //z tych wierzcholkow bedziemy szukac krawedzi do innych
    //std::cout << **it_WierzAktual << std::endl;
    Krawedz* k = nullptr;
    while(minimalneDrzewoRozpinajace.size() < wierzcholki.size()-1)
    {
        znajdzKrMin(rozpatrzone,kr,k); //dziala dobrze
        //std::cout << **it_WierzAktual << std::endl;
        minimalneDrzewoRozpinajace.emplace_back(k); //dziala dobrze
        //for(auto k : kr) std::cout << *k << std::endl;
        kr.erase(std::remove(kr.begin(),kr.end(),k),kr.end()); //dziala dobrze
        //std::cout << "\npo usunieciu:\n";
        //for(auto k : kr) std::cout << *k << std::endl;
        std::cout << "Rozpatrzone:\n";
        //for(auto r: rozpatrzone) std::cout << *r << std::endl;
    }
}

void Graf::algorytmKruskala()
{
    std::sort(krawedzie.begin(),krawedzie.end(),[](Krawedz* a, Krawedz* b) -> bool
    {
        return a->zwrocWaga() < b->zwrocWaga();
    });
//    for(auto it = krawedzie.begin(); it != krawedzie.end(); ++it)
//    {
//        std::cout << **it << std::endl;
//    }

    auto it = krawedzie.begin();
    while(minimalneDrzewoRozpinajace.size() < wierzcholki.size()-1)
    {
        Wierzcholek* wa = (*it)->getW1();
        Wierzcholek* wb = (*it)->getW2();

        if(!minimalneDrzewoRozpinajace.empty())
        {
            auto fit_a = std::find_if(minimalneDrzewoRozpinajace.begin(),minimalneDrzewoRozpinajace.end(),[&wa](Krawedz* ka)
            {
                return ((ka->getW1() == wa) || (ka->getW2() == wa));
            });
            auto fit_b = std::find_if(minimalneDrzewoRozpinajace.begin(),minimalneDrzewoRozpinajace.end(),[&wb](Krawedz* kb)
            {
                return ((kb->getW1() == wb) || (kb->getW2() == wb));
            });

            if(fit_a != minimalneDrzewoRozpinajace.end() && fit_b != minimalneDrzewoRozpinajace.end())
            {
                ++it;
            }
            else minimalneDrzewoRozpinajace.push_back(new Krawedz(**it));
        }
        else minimalneDrzewoRozpinajace.push_back(new Krawedz(**it));
    }
}

Wierzcholek Graf::zwrocNastepny(std::vector<Wierzcholek*>& rozpatrzone, Krawedz* &k)
{
    if(std::find(rozpatrzone.begin(),rozpatrzone.end(),k->getW1()) != rozpatrzone.end()) return Wierzcholek(*(k->getW2()));
    if(std::find(rozpatrzone.begin(),rozpatrzone.end(),k->getW2()) != rozpatrzone.end()) return Wierzcholek(*(k->getW1()));
}

void Graf::znajdzKrMin(std::vector<Wierzcholek*>& rozpatrzone, std::vector<Krawedz*>& krawedzie, Krawedz* &pMin) //ma zwrocic iterator do krMin
{
    std::vector<Krawedz*> potencjalne;
    for(auto it = rozpatrzone.begin(); it != rozpatrzone.end(); ++it)
    {
        for(auto ti = krawedzie.begin(); ti != krawedzie.end(); ++ti) //wybieramy potencjalne krawedzie tzn wychodza z/do w. rozpatrzonych
        {
                if(((*ti)->getW1() == (*it)))
                {
                    auto find_w2 = std::find(rozpatrzone.begin(),rozpatrzone.end(),(*ti)->getW2());
                    if(find_w2 == rozpatrzone.end()) potencjalne.emplace_back(*ti);
                }
                if(((*ti)->getW2() == (*it)))
                {
                    auto find_w1 = std::find(rozpatrzone.begin(),rozpatrzone.end(),(*ti)->getW1());
                    if(find_w1 == rozpatrzone.end()) potencjalne.emplace_back(*ti);
                }
        }
    }

    std::cout << "Potencjalne:\n";
    for(auto it = potencjalne.begin(); it != potencjalne.end(); ++it)
    {
        std::cout << **it << std::endl;
    }

    auto min = std::min_element(potencjalne.begin(),potencjalne.end(),
                        [](Krawedz* &a, Krawedz* &b)
                        {return a->zwrocWaga() < b->zwrocWaga();});

    std::cout << "min: " << **min << std::endl;
    //std::cout << "aktualny: " << *rozpatrzone.back() << std::endl;
    Wierzcholek* nast = new Wierzcholek(zwrocNastepny(rozpatrzone,*min));
    std::cout << "nastepny: " << *nast << std::endl;
    auto it_find = std::find(rozpatrzone.begin(),rozpatrzone.end(),nast);
    if(it_find==rozpatrzone.end()) rozpatrzone.emplace_back(new Wierzcholek(zwrocNastepny(rozpatrzone,*min)));
    pMin = *min;
}

void Graf::pokazMDR()
{
    std::cout << "MDR:\n";
    for(auto it = minimalneDrzewoRozpinajace.begin(); it != minimalneDrzewoRozpinajace.end(); ++it)
    {
        std::cout << **it << std::endl;
    }
}
