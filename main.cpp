#include "paszuj.h"

using namespace std;

int main()
{
    Paszuj p;
    setlocale(LC_ALL, "hu_HU.utf8");
    cout << "Adatok beolvasasa..." << endl; cout.flush();
    p.beolvas("rakomany.txt", "menetrend.txt");
    cout << "Kont�nerek sz�ll�t�sa..." << endl; cout.flush();
    p.rum();
    cout << "Utas�t�sok ki�r�sa..." << endl; cout.flush();
    p.kiir("out.txt");
    cout << "A program befejezte fut�s�t." << endl; cout.flush();
    return 0;
}
