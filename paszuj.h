#ifndef PASZUJ_H_INCLUDED
#define PASZUJ_H_INCLUDED

#include <list>
#include <string>
#include <vector>

struct Paszuj {
private:
	map<string, Varos> varosok; // v�ros neve, kont�nerekb�l �ll� vektor
	vector<hajo> hajok; // navajonmilehet.
public:
	void beolvas(string fajlNev); // Detti �rja meg a beolvas�s fvt
	void kiir(string fajlNev); // Detti �rja meg a ki�r�s fvt
	void parancsol(); // HT
};

struct Varos {
	vector<Kontener> kontenerek;
};
struct Kontener {
	string hely;
	string rakomanyNev;
	string celHely;
	int bonuszIdo;
};
struct Hajo {
	string jaratKod;
	int kapacitas;
	string honnanIndul;
	string hovaMegy;
	int hanyNapAlattOda;
	int hanyNapAlattVissza;
int fazisEltolodas;
};

// ------- Zoca --------------
struct Graf {
	vector<Csucs> csucsok;
	void frissit (); //friss�ti az �sszes cs�cs int �rt�k�t, azaz id�k�lts.-�t
};

struct Csucs {
	vector < pair<Csucs*, int> > elek;
};

// ------- HT -----------
struct Parancs {
	int mikorErkezik;
	string jaratKod;
	string rakomanyNev;
	int bonuszIdo;
	int mennyiseg;

};

#endif // PASZUJ_H_INCLUDED
