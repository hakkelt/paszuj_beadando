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
        k.ID = MAX_ID++;
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
        sor >> h.honnan;
        sor >> h.hova;
        sor >> h.hanyNapAlattOda;
        sor >> h.hanyNapAlattVissza;
        sor >> h.fazisEltolodas;
        hajok.push_back(h);
    }

    setlocale (LC_ALL,"");
    cout << "\tVárosok száma: " << varosok.size() << endl;
    cout << "\tHajók száma: " << hajok.size() << endl << endl;
}

void Paszuj::kiir(string fajlNev) {
    ofstream fff(fajlNev);
    for (unsigned int i=0; i<parancsok.size(); i++)
    {
        fff << parancsok[i].mikorErkezik << ' ' <<
        parancsok[i].jaratKod << ' ' << parancsok[i].rakomanyNev <<
        ' ' << parancsok[i].bonuszIdo << ' ' << parancsok[i].mennyiseg << endl;

    }
}
