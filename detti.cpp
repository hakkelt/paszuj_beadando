#include "paszuj.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void Paszuj::beolvas(string kontenerekFajl, string hajokFajl) {
    ifstream f(kontenerekFajl);
    kontenerekSzama = 0;
    string temp;
    getline(f, temp);
    while(f.good())
    {
        getline(f, temp);
        if (temp == "") continue;
        stringstream sor(temp);
        Kontener k;
        sor >> k.rakomanyNev;
        sor >> k.mennyiseg;
        kontenerekSzama += k.mennyiseg;
        sor >> k.hely;
        sor >> k.celHely;
        sor >> k.bonuszIdo;
        varosok[k.hely].kontenerek.push_back(k);
    }

    ifstream ff(hajokFajl);
    getline(ff, temp);
    while(ff.good())
    {
        getline(ff, temp);
        if (temp == "") continue;
        stringstream sor(temp);
        Hajo h;
        sor >> h.jaratKod;
        sor >> h.kapacitas;
        sor >> h.honnanIndul;
        sor >> h.hovaMegy;
        sor >> h.hanyNapAlattOda;
        sor >> h.hanyNapAlattVissza;
        sor >> h.fazisEltolodas;
        hajok.push_back(h);
    }

    setlocale (LC_ALL,"");
    cout << "Városok száma: " << varosok.size() << endl;
    cout << "Hajók száma: " << hajok.size() << endl << endl;
}

void Paszuj::kiir(string fajlNev) {

}
