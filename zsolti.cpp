#include "paszuj.h"

using namespace std;

/* epitGraf függvény leírása
    Teljes gráfot kell építened (bármelyik két csúcs közt van él ;) ), amiben a csúcspontok
    az egyes városok,és az élek súlya legyen egyenlõ az utazási idõvel. Azon az élek súlya, melyek
    két olyan város kötnek össze, melyek közt nincs közvetlen hajójárat, legyen végtelen
    (használd az INF konstanst! - a paszuj.h-ban hoztam létre, itt simán az INF szó begépelésével
    tudsz rá hivatkozni). Az élek legyenek minimálisak, vagyis ha több járat is van a két város közt,
    akkor válaszd ki azt, ami a leggyorsabban odaér. A nap változó értékét állítsd 0-ra.
    Az induloHajok vectorba azoknak a hajóknak az adata kerüljön, amelyek a 0.napon indulnak el.
*/
void Paszuj::epitGraf() {
    graf.nap=0;                                                                                ///nap nullara allitva
    for (map<string, Varos>::iterator it=varosok.begin(); it!=varosok.end(); ++it){            ///varosok es kontenerek betoltese a csucsokba

        graf.csucsok[it->first];                                                               ///egy csucs hozzaadasa
        for (int i=0; i< it->second.kontenerek.size(); i++){                                   ///hozza valo kontenerek hozzaadasa
            graf.csucsok[it->first].kontenerek.push_back(it->second.kontenerek[i]);
        }
    }

    for (int i=0; i<hajok.size(); i++){                                                        /// csucsbol indulo elek es sulyaik hozzaadasa
            if (graf.csucsok[hajok[i].honnanIndul].elek[hajok[i].hovaMegy]==0 or
                graf.csucsok[hajok[i].honnanIndul].elek[hajok[i].hovaMegy]>hajok[i].hanyNapAlattOda)
            graf.csucsok[hajok[i].honnanIndul].elek[hajok[i].hovaMegy]=hajok[i].hanyNapAlattOda;
            if (graf.csucsok[hajok[i].hovaMegy].elek[hajok[i].honnanIndul]==0 or
                graf.csucsok[hajok[i].hovaMegy].elek[hajok[i].honnanIndul]>hajok[i].hanyNapAlattVissza)
            graf.csucsok[hajok[i].hovaMegy].elek[hajok[i].honnanIndul]=hajok[i].hanyNapAlattVissza;

            if (hajok[i].fazisEltolodas == 0) {                                                /// 0ik napon indulo hajok betoltese
                InduloHajo x;
                x.honnanIndul=hajok[i].honnanIndul;
                x.hovaMegy=hajok[i].hovaMegy;
                x.jaratKod=hajok[i].jaratKod;
                x.kapacitas=hajok[i].kapacitas;
                x.menetido=hajok[i].hanyNapAlattOda;
                x.mikorErOda=hajok[i].hanyNapAlattOda;
                graf.induloHajok.push_back(x);
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
    induloHajok.clear();

    for (int i=0; i<hajok.size(); i++) {
        if (hajok[i].fazisEltolodas == graf.nap or
            graf.nap % (hajok[i].hanyNapAlattOda + hajok[i].hanyNapAlattOdaVissza) == hajok[i].fazisEltolodas or
            graf.nap % (hajok[i].hanyNapAlattOda + hajok[i].hanyNapAlattOdaVissza)==
            (hajok[i].fazisEltolodas+hajok[i].hanyNapAlattOda)%(hajok[i].hanyNapAlattOda + hajok[i].hanyNapAlattOdaVissza)
            ) {                                                /// x. napon indulo hajok betoltese
            InduloHajo x;
            x.honnanIndul=hajok[i].honnanIndul;
            x.hovaMegy=hajok[i].hovaMegy;
            x.jaratKod=hajok[i].jaratKod;
            x.kapacitas=hajok[i].kapacitas;
            x.menetido=hajok[i].hanyNapAlattOda;
            x.mikorErOda=hajok[i].hanyNapAlattOda;
            graf.induloHajok.push_back(x);
        }
    }
}
