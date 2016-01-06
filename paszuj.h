#ifndef PASZUJ_H_INCLUDED
#define PASZUJ_H_INCLUDED

#include <list>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <vector>
#include <limits.h>
#include <iostream>
#include <locale.h>
#include <queue>

/// Ha ezt a fájlt módosítjátok, akkor gyorsan szinkronizáljátok, nehogy felülírjuk egymás munkáját

/// -------- Detti -----------
struct Kontener {
	std::string hely;
	std::string rakomanyNev;
	std::string celHely;
	int mennyiseg;
	int bonuszIdo;
	int ID;
};
struct Varos {
	std::list<Kontener> kontenerek;
};
struct Hajo {
	std::string jaratKod;
	int kapacitas;
	std::string honnan;
	std::string hova;
	int hanyNapAlattOda;
	int hanyNapAlattVissza;
    int fazisEltolodas;
};

/// ------- Zsolti --------------
struct Csucs {
    std::list<Kontener> * kontenerek;                   // ezt az elején fel kéne tölteni
	std::unordered_map<std::string, int> elek;          // ugyanúgy működik mint a sima map, csak sokkal gyorsabb
	int dist;                                           // Ezzel Zsoltinak nincs dolga, ez nekem kell (Tamás)
    std::unordered_map<std::string, int> min_dist;
};
struct InduloHajo {                                     // Ez abban különbözik a hajo struct-tól, hogy a hajo struct-ban oda-vissza utak kerültek tárolásra, addíg ebben csak az oda- vagy a visszaút adatait tartalmazza
	std::string jaratKod;
	int kapacitas;
	std::string honnan, hova;
	int menetido;
};
struct HajonKontener {
    Kontener kontener;
    std::string honnan, hova;
    int mikor;
};
struct NapPrioritas {
    bool operator() (const HajonKontener & v1, const HajonKontener & v2) const
        { return v1.mikor > v2.mikor; }
};
struct Graf {
    int nap;                                            // Éppen hanyadik napon járunk
	std::unordered_map<std::string, Csucs> csucsok;
	std::unordered_map<std::string, std::vector<InduloHajo> > induloHajok;                // Adott napon induló hajók listája
	std::priority_queue<HajonKontener, std::vector<HajonKontener>, NapPrioritas> hajonKontenerek;
	void epitGraf();
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
	std::map<std::string, Varos> varosok;               // város neve, konténerekbõl álló vektor
	std::vector<Hajo> hajok;                            // navajonmilehet.
	int kontenerekSzama;
	int MAX_ID = 0;
	int bonuszIdore;
	Graf graf;
	std::vector<Parancs> parancsok;

	void epitGraf();                                    // Gráf építése - Zsolti feladata
	void parancsol();                                   // Tamás írja
    void kovetkezoNap();                                // Növeli a nap változó értékét, eljésziti az adott napon induló hajók listáját és, frissíti az összes csúcs int értékét, azaz idõkölts.-ét
	int Dijkstra(std::string honnan, std::string hova);

public:
	void beolvas(std::string kontenerekFajl, std::string hajokFajl);// Detti írja meg a beolvasós fvt
	void kiir(std::string fajlNev);                     // Detti írja meg a kiírós fvt
	void rum() {
	    bonuszIdore = 0;
        epitGraf();
        while(graf.nap < 20000 and 0 < kontenerekSzama) {
            parancsol();
            kovetkezoNap();
        }
        std::cout << "Nap: " << graf.nap << "  \tKontenerek szama: " << kontenerekSzama << std::endl;
        std::cout << "Parancsok szama: " << parancsok.size() << std::endl;
        std::cout << "Bonuszidore teljesitet kontenerek szama: " << bonuszIdore << std::endl << std::endl;
	}
};

#endif // PASZUJ_H_INCLUDED
