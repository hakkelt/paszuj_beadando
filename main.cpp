#include <iostream>
#include <locale.h>
#include "paszuj.h"

using namespace std;

int main()
{
    Paszuj p;
    setlocale (LC_ALL,"");
    cout << "Adatok beolvas�sa..." << endl; cout.flush();
    p.beolvas("varosok.txt", "hajok.txt");
    cout << "�tvonalak keres�se..." << endl; cout.flush();
    p.rum();
    cout << "Utasitasok ki�rasa..." << endl; cout.flush();
    p.kiir("out.txt");
    cout << "A program befejezte fut�s�t." << endl; cout.flush();
    return 0;
}
