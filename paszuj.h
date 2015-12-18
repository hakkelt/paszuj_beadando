#ifndef PASZUJ_H_INCLUDED
#define PASZUJ_H_INCLUDED

#include <list>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>

/// Ha ezt a fájlt módosítjátok, akkor gyorsan szinkronizáljátok, nehogy felülírjuk egymás munkáját

/// -------- Detti -----------
struct Kontener {
	std::string hely;
	std::string rakomanyNev;
	std::string celHely;
	int bonuszIdo;
};
struct Varos {
	std::vector<Kontener> kontenerek;
};
struct Hajo {
	std::string jaratKod;
	int kapacitas;
	std::string honnanIndul;
	std::string hovaMegy;
	int hanyNapAlattOda;
	int hanyNapAlattVissza;
int fazisEltolodas;
};

/// ------- Zsolti --------------
struct Csucs {
    std::list<Kontener> kontenerek;          // ezt az elején fel kéne tölteni
	std::unordered_map<Csucs*, int> elek;    // ugyanúgy működik mint a sima map, csak sokkal gyorsabb
	std::string nev;                         // Város neve
};
struct Graf {
	std::vector<Csucs> csucsok;
	void frissit ();                    //frissíti az összes csúcs int értékét, azaz idõkölts.-ét
};

/// ------- HT -----------
struct Parancs {
	int mikorErkezik;
	std::string jaratKod;
	std::string rakomanyNev;
	int bonuszIdo;
	int mennyiseg;
};

struct Paszuj {
private:
	std::map<std::string, Varos> varosok;   // város neve, konténerekbõl álló vektor
	std::vector<Hajo> hajok;                // navajonmilehet.
	Graf graf;
	void epitGraf();                        // Gráf építése - Zsolti feladata
	void parancsol();                       // Tamás írja
public:
	void beolvas(std::string varosok, std::string hajok);      // Detti írja meg a beolvasós fvt
	void kiir(std::string fajlNev);         // Detti írja meg a kiírós fvt
	void rum() {
        epitGraf();
        parancsol();
	}
};

#endif // PASZUJ_H_INCLUDED
