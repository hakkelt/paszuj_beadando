#include "paszuj.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void Paszuj::beolvas(string kontenerekFajl, string hajokFajl) {
    ifstream f(kontenerekFajl);
    Kontener k;
    string temp;
    int mennyiseg;
    stringstream sor;
    getline(f, temp);
    while(f.good())
    {
        getline(f, temp);
        sor << temp;
        sor >> k.rakomanyNev;
        sor >> mennyiseg;
        sor >> k.hely;
        sor >> k.celHely;
        sor >> k.bonuszIdo;
        for (int i=0; i<mennyiseg; i++)
        {
            varosok[k.hely].kontenerek.push_back(k);
        }
    }

    ifstream ff(hajokFajl);
    Hajo h;
    getline(ff, temp);
    while(ff.good())
    {
        getline(ff, temp);
        sor << temp;
        sor >> h.jaratKod;
        sor >> h.kapacitas;
        sor >> h.honnanIndul;
        sor >> h.hovaMegy;
        sor >> h.hanyNapAlattOda;
        sor >> h.hanyNapAlattVissza;
        sor >> h.fazisEltolodas;
        hajok.push_back(h);
    }
}

void Paszuj::kiir(string fajlNev) {

}
