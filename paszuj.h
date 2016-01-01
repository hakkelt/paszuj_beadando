#ifndef PASZUJ_H_INCLUDED
#define PASZUJ_H_INCLUDED

#include <list>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <vector>
#include <limits.h>

/// Ha ezt a fájlt módosítjátok, akkor gyorsan szinkronizáljátok, nehogy felülírjuk egymás munkáját

const int INF = INT_MAX;

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
    std::list<Kontener> kontenerek;                     // ezt az elején fel kéne tölteni
	std::unordered_map<std::string, int> elek;          // ugyanúgy működik mint a sima map, csak sokkal gyorsabb
	int dist;                                           // Ezzel Zsoltinak nincs dolga, ez nekem kell (Tamás)
};
struct InduloHajo {                                     // Ez abban különbözik a hajo struct-tól, hogy a hajo struct-ban oda-vissza utak kerültek tárolásra, addíg ebben csak az oda- vagy a visszaút adatait tartalmazza
	std::string jaratKod;
	int kapacitas;
	std::string honnanIndul;
	std::string hovaMegy;
	int mikorErOda;
	int menetido;
};
struct Graf {
    int nap;                                            // Éppen hanyadik napon járunk
	std::unordered_map<std::string, Csucs> csucsok;
	std::vector<InduloHajo> induloHajok;                // Adott napon induló hajók listája
	void epitGraf();
	void kovetkezoNap();                                // Növeli a nap változó értékét, eljésziti az adott napon induló hajók listáját és, frissíti az összes csúcs int értékét, azaz idõkölts.-ét
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
	Graf graf;
	std::vector<Parancs> parancsok;

	void epitGraf();                                    // Gráf építése - Zsolti feladata
	bool parancsol();                                   // Tamás írja
	int Dijkstra(std::string honnan, std::string hova);

public:
	void beolvas(std::string varosok, std::string hajok);// Detti írja meg a beolvasós fvt
	void kiir(std::string fajlNev);                     // Detti írja meg a kiírós fvt
	void rum() {
        epitGraf();
        while(parancsol())                              // A parancsol() akkor fog hamissal visszatérni, ha az összes konténer a célhelyen van
            graf.kovetkezoNap();
	}
};

#endif // PASZUJ_H_INCLUDED
