#ifndef PASZUJ_H_INCLUDED
#define PASZUJ_H_INCLUDED

#include <list>
#include <string>
#include <vector>

struct Paszuj {
private:
	map<string, Varos> varosok; // város neve, konténerekbõl álló vektor
	vector<hajo> hajok; // navajonmilehet.
public:
	void beolvas(string fajlNev); // Detti írja meg a beolvasós fvt
	void kiir(string fajlNev); // Detti írja meg a kiírós fvt
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
	void frissit (); //frissíti az összes csúcs int értékét, azaz idõkölts.-ét
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
