#include <iostream>
#include "paszuj.h"

using namespace std;

int main()
{
    Paszuj p;
    cout << "Adatok beolvasasa..." << endl; cout.flush();
    p.beolvas("varosok.txt", "hajok.txt");
    cout << "Utvonalak keresese..." << endl; cout.flush();
    p.rum();
    cout << "Utasitasok kiirasa..." << endl; cout.flush();
    p.kiir("out.txt");
    cout << "Be van fejezve mar." << endl; cout.flush();
    return 0;
}
