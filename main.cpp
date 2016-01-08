#include "paszuj.h"

using namespace std;

int main()
{
    Paszuj p;
    setlocale(LC_ALL, "hu_HU.utf8");
    cout << "Adatok beolvasasa..." << endl; cout.flush();
    p.beolvas("rakomany.txt", "menetrend.txt");
    cout << "Konténerek szállítása..." << endl; cout.flush();
    p.rum();
    cout << "Utasítások kiírása..." << endl; cout.flush();
    p.kiir("out.txt");
    cout << "A program befejezte futását." << endl; cout.flush();
    return 0;
}
