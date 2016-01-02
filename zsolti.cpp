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
    /// TODO
}

/* kovetkezoNap függvény leírása
    Növeld meg a nap változó értékét, majd ürítsd ki a induloHajok vektort és töltsd fel az aktuális
    napon induló hajók adataival. Ha az adott hajó épp visszafele indul el, akkor a honnanIndul változóba
    az eredeti hajok változó szerinti hovaMegy változó értéke kerüljön, a hovaMegy-be pedig a honnanIndul,
    és a mikorErOda változóba pedig az kerüljön, hogy hányadik napon fog legközelebb kikötni (vagyis hányadik
    napon fog odaérni a "hovaMegy" változóban leírt helyre. Az éleket nem kell frissíteni.
*/
void Graf::kovetkezoNap() {
    /// TODO
}


///BANÁNKRUMPLIFECSKEBÉLYEG
