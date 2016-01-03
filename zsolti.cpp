#include "paszuj.h"

using namespace std;

/* epitGraf f�ggv�ny le�r�sa
    Teljes gr�fot kell �p�tened (b�rmelyik k�t cs�cs k�zt van �l ;) ), amiben a cs�cspontok
    az egyes v�rosok,�s az �lek s�lya legyen egyenl� az utaz�si id�vel.
    Az �lek legyenek minim�lisak, vagyis ha t�bb j�rat is van a k�t v�ros k�zt,
    akkor v�laszd ki azt, ami a leggyorsabban oda�r. A nap v�ltoz� �rt�k�t �ll�tsd 0-ra.
    Az induloHajok vectorba azoknak a haj�knak az adata ker�lj�n, amelyek a 0.napon indulnak el.
*/
void Paszuj::epitGraf() {
    graf.nap=0;                                                                                ///nap nullara allitva
    for (map<string, Varos>::iterator it=varosok.begin(); it!=varosok.end(); ++it)             ///varosok es kontenerek betoltese a csucsokba
        graf.csucsok[it->first].kontenerek = &(it->second.kontenerek);

    for (size_t i=0; i<hajok.size(); i++){                                                      /// csucsbol indulo elek es sulyaik hozzaadasa
            if (graf.csucsok[hajok[i].honnanIndul].elek[hajok[i].hovaMegy] == 0 or
                graf.csucsok[hajok[i].honnanIndul].elek[hajok[i].hovaMegy] > hajok[i].hanyNapAlattOda)
                    graf.csucsok[hajok[i].honnanIndul].elek[hajok[i].hovaMegy] = hajok[i].hanyNapAlattOda;
            if (graf.csucsok[hajok[i].hovaMegy].elek[hajok[i].honnanIndul] == 0 or
                graf.csucsok[hajok[i].hovaMegy].elek[hajok[i].honnanIndul] > hajok[i].hanyNapAlattVissza)
                    graf.csucsok[hajok[i].hovaMegy].elek[hajok[i].honnanIndul] = hajok[i].hanyNapAlattVissza;

            if (hajok[i].fazisEltolodas == 0) {                                                /// 0ik napon indulo hajok betoltese
                InduloHajo x;
                x.honnanIndul=hajok[i].honnanIndul;
                x.hovaMegy=hajok[i].hovaMegy;
                x.jaratKod=hajok[i].jaratKod;
                x.kapacitas=hajok[i].kapacitas;
                x.menetido=hajok[i].hanyNapAlattOda;
                graf.induloHajok.push_back(x);
            }
    }
}

/* kovetkezoNap f�ggv�ny le�r�sa
    N�veld meg a nap v�ltoz� �rt�k�t, majd �r�tsd ki a induloHajok vektort �s t�ltsd fel az aktu�lis
    napon indul� haj�k adataival. Ha az adott haj� �pp visszafele indul el, akkor a honnanIndul v�ltoz�ba
    az eredeti hajok v�ltoz� szerinti hovaMegy v�ltoz� �rt�ke ker�lj�n, a hovaMegy-be pedig a honnanIndul,
    �s a mikorErOda v�ltoz�ba pedig az ker�lj�n, hogy h�nyadik napon fog legk�zelebb kik�tni (vagyis h�nyadik
    napon fog oda�rni a "hovaMegy" v�ltoz�ban le�rt helyre. Az �leket nem kell friss�teni.
*/
void Paszuj::kovetkezoNap() {
    graf.nap++;
    graf.induloHajok.clear();

    for (size_t i=0; i<hajok.size(); i++) {
        if (graf.nap >= hajok[i].fazisEltolodas and
            (graf.nap - hajok[i].fazisEltolodas) % (hajok[i].hanyNapAlattOda + hajok[i].hanyNapAlattVissza) == 0)
        {                                            /// x. napon indulo hajok betoltese
            InduloHajo x;
            x.honnanIndul=hajok[i].honnanIndul;
            x.hovaMegy=hajok[i].hovaMegy;
            x.jaratKod=hajok[i].jaratKod;
            x.kapacitas=hajok[i].kapacitas;
            x.menetido=hajok[i].hanyNapAlattOda;
            graf.induloHajok.push_back(x);

        }
        else if (graf.nap >= hajok[i].fazisEltolodas + hajok[i].hanyNapAlattOda and
            (graf.nap - hajok[i].fazisEltolodas - hajok[i].hanyNapAlattOda) % (hajok[i].hanyNapAlattOda + hajok[i].hanyNapAlattVissza) == 0)
        {                                       /// x. napon visszaindulo hajok betoltese
            InduloHajo x;
            x.honnanIndul=hajok[i].honnanIndul;
            x.hovaMegy=hajok[i].hovaMegy;
            x.jaratKod=hajok[i].jaratKod;
            x.kapacitas=hajok[i].kapacitas;
            x.menetido=hajok[i].hanyNapAlattVissza;
            graf.induloHajok.push_back(x);
        }
    }
}
