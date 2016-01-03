#include <iostream>
#include <locale.h>
#include "paszuj.h"

using namespace std;

int main()
{
    Paszuj p;
    setlocale (LC_ALL,"");
    cout << "Adatok beolvasása..." << endl; cout.flush();
    p.beolvas("varosok.txt", "hajok.txt");
    cout << "Útvonalak keresése..." << endl; cout.flush();
    p.rum();
    cout << "Utasitasok kiírasa..." << endl; cout.flush();
    p.kiir("out.txt");
    cout << "A program befejezte futását." << endl; cout.flush();
    return 0;
}
