#include "paszuj.h"

using namespace std;

/* epitGraf függvény leírása
    Teljes gráfot kell építened (bármelyik két csúcs közt van él ;) ), amiben a csúcspontok
    az egyes városok,és az élek súlya legyen egyenlõ az utazási idõvel.
    Az élek legyenek minimálisak, vagyis ha több járat is van a két város közt,
    akkor válaszd ki azt, ami a leggyorsabban odaér. A nap változó értékét állítsd 0-ra.
    Az induloHajok vectorba azoknak a hajóknak az adata kerüljön, amelyek a 0.napon indulnak el.
*/
void Paszuj::epitGraf() {
    graf.nap=0;                                                                                ///nap nullara allitva
    for (map<string, Varos>::iterator it=varosok.begin(); it!=varosok.end(); ++it)             ///varosok es kontenerek betoltese a csucsokba
        graf.csucsok[it->first].kontenerek = &(it->second.kontenerek);

    for (size_t i=0; i<hajok.size(); i++){                                                      /// csucsbol indulo elek es sulyaik hozzaadasa
            if (graf.csucsok[hajok[i].honnan].elek[hajok[i].hova] == 0 or
                graf.csucsok[hajok[i].honnan].elek[hajok[i].hova] > hajok[i].hanyNapAlattOda)
                    graf.csucsok[hajok[i].honnan].elek[hajok[i].hova] = hajok[i].hanyNapAlattOda;
            if (graf.csucsok[hajok[i].hova].elek[hajok[i].honnan] == 0 or
                graf.csucsok[hajok[i].hova].elek[hajok[i].honnan] > hajok[i].hanyNapAlattVissza)
                    graf.csucsok[hajok[i].hova].elek[hajok[i].honnan] = hajok[i].hanyNapAlattVissza;

            if (hajok[i].fazisEltolodas == 0) {                                                /// 0ik napon indulo hajok betoltese
                InduloHajo x;
                x.honnan=hajok[i].honnan;
                x.hova=hajok[i].hova;
                x.jaratKod=hajok[i].jaratKod;
                x.kapacitas=hajok[i].kapacitas;
                x.menetido=hajok[i].hanyNapAlattOda;
                graf.induloHajok[hajok[i].honnan].push_back(x);
            }
    }
}

/* kovetkezoNap függvény leírása
    Növeld meg a nap változó értékét, majd ürítsd ki a induloHajok vektort és töltsd fel az aktuális
    napon induló hajók adataival. Ha az adott hajó épp visszafele indul el, akkor a honnanIndul változóba
    az eredeti hajok változó szerinti hovaMegy változó értéke kerüljön, a hovaMegy-be pedig a honnanIndul,
    és a mikorErOda változóba pedig az kerüljön, hogy hányadik napon fog legközelebb kikötni (vagyis hányadik
    napon fog odaérni a "hovaMegy" változóban leírt helyre. Az éleket nem kell frissíteni.
*/
void Paszuj::kovetkezoNap() {
    graf.nap++;
    graf.induloHajok.clear();

    while(graf.hajonKontenerek.size() != 0 and graf.hajonKontenerek.top().mikor<=graf.nap){
        varosok[graf.hajonKontenerek.top().hova].kontenerek.push_back(graf.hajonKontenerek.top().kontener);
        graf.hajonKontenerek.pop();
    }

    for (size_t i=0; i<hajok.size(); i++) {
        if (graf.nap >= hajok[i].fazisEltolodas and
            (graf.nap - hajok[i].fazisEltolodas) % (hajok[i].hanyNapAlattOda + hajok[i].hanyNapAlattVissza) == 0)
        {                                            /// x. napon indulo hajok betoltese
            InduloHajo x;
            x.honnan=hajok[i].honnan;
            x.hova=hajok[i].hova;
            x.jaratKod=hajok[i].jaratKod;
            x.kapacitas=hajok[i].kapacitas;
            x.menetido=hajok[i].hanyNapAlattOda;
            graf.induloHajok[hajok[i].honnan].push_back(x);

        }
        else if (graf.nap >= hajok[i].fazisEltolodas + hajok[i].hanyNapAlattOda and
            (graf.nap - hajok[i].fazisEltolodas - hajok[i].hanyNapAlattOda) % (hajok[i].hanyNapAlattOda + hajok[i].hanyNapAlattVissza) == 0)
        {                                       /// x. napon visszaindulo hajok betoltese
            InduloHajo x;
            x.honnan=hajok[i].hova;
            x.hova=hajok[i].honnan;
            x.jaratKod=hajok[i].jaratKod;
            x.kapacitas=hajok[i].kapacitas;
            x.menetido=hajok[i].hanyNapAlattVissza;
            graf.induloHajok[hajok[i].honnan].push_back(x);
        }
    }
}
