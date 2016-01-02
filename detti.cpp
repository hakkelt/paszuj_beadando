#include "paszuj.h"
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

void Paszuj::beolvas(string varosok, string hajok) {
    ifstream f("rakomany.txt");
    Kontener k;
    Varos v;
    Paszuj p;
    stringstream ss;
    string temp;
    while(f.good())
    {
        getline(f, k.rakomanyNev, ' ');
        getline(f, temp, ' ');
        ss << temp;
        ss >> k.mennyiseg;
        ss.clear();
        temp.clear();
        getline(f, k.hely, ' ');
        getline(f, k.celHely, ' ');
        getline(f, temp);
        ss << temp;
        ss >> k.bonuszIdo;
        ss.clear();
        temp.clear();
        v.kontenerek.push_back(k);
    }
    p.varosok.insert(pair<string,Varos>(k.hely, v));

    ifstream ff("menetrend.txt");
    Hajo h;
    while(ff.good())
    {
        getline(ff, h.jaratKod, ' ');
        getline(ff, temp, ' ');
        ss << temp;
        ss >> h.kapacitas;
        getline(ff, h.honnanIndul, ' ');
        getline(ff, h.hovaMegy, ' ');
        getline(ff, temp, ' ');
        ss << temp;
        ss >> h.hanyNapAlattOda;
        getline(ff, temp, ' ');
        ss << temp;
        ss >> h.hanyNapAlattVissza;
        getline(ff, temp);
        ss >> temp;
        ss << h.fazisEltolodas;
        p.hajok.push_back(h);
    }
}


void Paszuj::kiir(string fajlNev) {

}
