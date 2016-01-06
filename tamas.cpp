#include "paszuj.h"
#include <set>
#include <cmath>

using namespace std;

/*
    Azért használok iterátorokat és nem magukat a konténereket, mert így módosítani tudom őket (ok, erre még
    egy pointer is jó lenne), és ki tudom törölni abból a listából, amiben vannak (na, ehhez kell az iterátor!).
    Eltárolom, hogy melyik hajóra nézve kb mennyivel jutna közelebb a céljához
        (alsó becslést végzek Dijkstra algoritmussal).
*/
struct MennyireEriMegSzallitani {
    list<Kontener>::iterator kontener;
    vector<InduloHajo>::iterator melyikHajon;
    int mennyivelLeszKozelebb;
};

/*
    Két MennyireEriMegSzallitani típusú változót hasonlít össze, az lesz a nagyobb, amelyiknek nagyobb a
    mennyivelLeszKozelebb típusú mezője, vagyis  ha a konténer átkerülne egy másik helyre, akkor
    onnan kb hány nappal kevesebb idő alatt ér át a rendeltetési helyére (ezt Dijkstra algoritmussal fogom
    alulról becsülni). Ez lesz az elem prioritása. Ha egyenlő a két elem prioritása, akkor a bónuszidő dönt.
    A prioritás ebben az esetben azt írja le, ezért az lesz a nagyobb prioritású, amelyiknek kisebb az
    így kapott úthossza, ezért van fordítva a relációs jel.
    Ezt a funktort a parancsol függvényben deklarált prioritásos sorhoz hoztam létre.
*/
bool CompareMennyireEriMegSzallitani (const MennyireEriMegSzallitani &v1, const MennyireEriMegSzallitani &v2)  {
    if (v1.mennyivelLeszKozelebb == v2.mennyivelLeszKozelebb)
        return v1.kontener->bonuszIdo > v2.kontener->bonuszIdo;
    else
        return v1.mennyivelLeszKozelebb < v2.mennyivelLeszKozelebb;
}

/*
    Ez a függvény prioritásos sorokat hasonlít össze prioritásos sorok legnagyobb eleme szerint.
    (Pontosabban a legkisebb eleme szerint, de az előző összehasonlító függvény és ezt úgy írtam meg, hogy
     megfordítsa a sorrendet, vagyis a kisebbet tüntesse föl nagyobbnak).
    A feladatra nézve ez azt jelenti, hogy melyik az az a konténer, ami a legtöbbet halad, ha felkerül
    az "álom hajóra", ami az összes közül neki a legjobb.
*/
bool ComparePriorityQueue (const vector<MennyireEriMegSzallitani> v1, const vector<MennyireEriMegSzallitani> v2)  {
    return CompareMennyireEriMegSzallitani(v1[0], v2[0]);
}

/*
    Egy adott napra nézve minden egyes aznap induló hajót végignézi, és felállít egy prioritásos listát
    a konténerek közt aszerint, hogy az induló hajóra felkerülne, akkor mennyivel jutna közelebb a céljához
    (persze ez csak egy durva becslés lesz, mert nem a gráfot statikusnak veszem, vagyis nem veszem
    figyelembe, hogy az egyes hajójáratok nem indulnak minden nap. A felállított prioritásos sor
    első n elemét elszállítom, ahol n a vizsgált hajó kapacitása - a parancsok structba beleírom az
    utasításokat, és kitörlöm annak a városnak a megfelelő gráf-csúcsból, ahonnan elszállítom, és a
    hajó célhelyéhez meg hozzáadom, ha az nem a konténer célhelye. Így csak olyan konténereim lesznek a
    gráfban amiket szállítani kell. Amikor elfogytak a szállítandó konténerek, akkor a függvény hamissal tér
    vissza.
*/
void Paszuj::parancsol() {
    /*A belső prioritásos sorba (vectort használok praktikus okokból, de úgy rendezem, hogy prioritásos sor legyen)
     az fog kerülni, hogy az adott konténert ha felrakom a tartózkodási helye szerini
    városból induló hajókra, akkor az egyes hajók mennyivel viszik közelebb a konténert a végcéljához.
    Ez a map csoportosítja a kapott priotásos sorokat aszerint, hogy melyik konténerre vonatkoznak.
    Kulcsként iterátort használok, mert az (remélem) minden konténerre különböző*/
    map< int, vector<MennyireEriMegSzallitani> > gyujto;
    // Végigmegyek azokon a városokon, ahonnan az adott nap indul hajó..
    //cout << "Varosok szama, ahonnan hajo indul: " << graf.induloHajok.size() << endl;
    for (unordered_map<string, vector<InduloHajo>>::iterator v = graf.induloHajok.begin(); v != graf.induloHajok.end(); v++) {
        // ...végigmegyek a városban található konténereken... (Azért használok iterátoros ciklus és nem rage-based-et, mert szükségem lesz az iterátorra magára)
      for (list<Kontener>::iterator k = graf.csucsok[v->first].kontenerek->begin();
        k != graf.csucsok[v->first].kontenerek->end(); k++) {
            // ... és végigmegyek az adott városból induló összes hajón minden egyes konténer esetében vizsgálva azt, hogy mennyivel jutna közelebb az adott konténer, ha felkerül az adott hajóra
            for(vector<InduloHajo>::iterator h = v->second.begin(); h != v->second.end(); h++) {
                // Ennyivel javulna a konténer aktuális tartózkodási helye a célhelyhez képest, ha felkerülne az adott hajóra
                int kulonbseg = Dijkstra(h->hova, k->celHely) + h->menetido - Dijkstra(v->first, k->celHely);
                if (0 < kulonbseg) {
                    MennyireEriMegSzallitani uj;
                    uj.kontener = k;
                    uj.melyikHajon = h;
                    uj.mennyivelLeszKozelebb = kulonbseg;
                    gyujto[k->ID].push_back(uj);
                }
            }
        }
    }

    /* Ez egy konténereket tároló lista itarátoraiból álló prioritásos sorok prioritásos sora. ...huh...
    A belső prioritásos sorba (itt BelsoPriorityQueue-ként van rövidítve egy korábbi #define-nak
    köszönhetően) az fog kerülni, hogy az adott konténert ha felrakom a tartózkodási helye szerini
    városból induló hajókra, akkor az egyes hajók mennyivel viszik közelebb a konténert a végcéljához.
    A külső prioritásos sor pedig aszerint rendezi sorba a konténereket, hogy  melyik halad a legnagyobbat,
    ha felkerül az "álom hajóra", vagyis arra a hajóra,ami leginkább rövidít az útján.*/
    vector< vector<MennyireEriMegSzallitani> > kivansagok;
    for (auto k : gyujto) {
        make_heap(k.second.begin(), k.second.end(), CompareMennyireEriMegSzallitani);
        kivansagok.push_back(k.second);
    }
    make_heap(kivansagok.begin(), kivansagok.end(), ComparePriorityQueue);

    while (not kivansagok.empty()) {
        // A prioritásos sorból a top() függvénnyel tudom lekérdezni a legkisebb elemet
        // Bevezetek két rövidítést (actKontener és az actHajo), mert átláthatóbb, ha ezeken nem írom le ezerszer.
        list<Kontener>::iterator actKontener = kivansagok[0][0].kontener;       // Ez az a konténer lesz, aminek a legszebb a kívánsága: az összes közül ez ígér a legtöbbet, hogy mennyivel fog közelebb kerülni, ha feltesszük arra a hajóra, amire kéri
        vector<InduloHajo>::iterator actHajo = kivansagok[0][0].melyikHajon;    // Ez pedig a legszebb kívánságban szereplő hajó
        //cout << kivansagok[0][0].mennyivelLeszKozelebb << " ";
        // Ha teljesíthető a kívánság, mert a hajón van még hely...
        if (0 < actHajo->kapacitas) {
            Parancs uj;
            uj.bonuszIdo = // Ha már lejárt a bónuszidő, akkor ne negatív legyen ez az érték, amit fájlba majd kiírok, hanem nulla (ez benne volt a feladatleírásban)
                (actKontener->bonuszIdo - graf.nap < 0 ? 0 : actKontener->bonuszIdo - graf.nap);
            uj.jaratKod = actHajo->jaratKod;
            uj.mikorErkezik = graf.nap + actHajo->menetido;
            uj.rakomanyNev = actKontener->rakomanyNev;

            // Ha konténerek mind beleférnek az adott hajóba
            if (actKontener->mennyiseg <= actHajo->kapacitas) {
                uj.mennyiseg = actKontener->mennyiseg;  // Felrakom az összes konténert
                actHajo->kapacitas -= uj.mennyiseg;     // Kiszámolom, hogy mennyi hely maradt a hajón
                // Ha a konténerek még nem érkeztek meg a célhelyükre, akkor hozzáadom az épp vizen levő konténerek listájába (pontosabban prioritásos sorába)
                if (actHajo->hova != actKontener->celHely) {
                    HajonKontener k;
                    k.hova = actHajo->hova;
                    k.kontener = *actKontener;
                    k.mikor = graf.nap + actHajo->menetido;
                    //cout << "Fer - Nap: " << graf.nap << "   menetido: " << actHajo->menetido << endl;
                    graf.hajonKontenerek.push(k);
                }
                // Ha nem akkor "véletlenül" elfelejtem hozzáadni a listához, nem érkezik meg, úgyhogy eltűnik a gráfból, de nem is baj, hiszen nincs több dolgunk vele
                else {
                    // Ezek csak azért számlálom, hogy legyen mit kiírni a konzolra.
                    kontenerekSzama -= actKontener->mennyiseg;
                    if (0 < uj.bonuszIdo - actHajo->menetido) bonuszIdore += actKontener->mennyiseg;
                }
                graf.csucsok[actHajo->honnan].kontenerek->erase(actKontener); // törlöm a gráfból ezeket a konténereket az adott helyről, mert már nincsenek ott
                pop_heap(kivansagok.begin(), kivansagok.end(), ComparePriorityQueue);
                kivansagok.pop_back();
            }
            // Ha nem fér be az összes konténer, akkor felrakok annyi konténert a hajóra, amennyit csak tudok
            else {
                uj.mennyiseg = actHajo->kapacitas;              // Felrakok a hajóra annyit, amennyit csak tudok
                actHajo->kapacitas = 0;                         // Jelzem, hogy betelt a hajó

                int temp = actKontener->mennyiseg;              // Ketté fogom osztani a konténereket (egy rész meg a hajóval, többi marad), ezért elmentem, hogy mennyi volt
                actKontener->mennyiseg = uj.mennyiseg;          // Ez utazik
                if (actHajo->hova != actKontener->celHely) {    // Fel is teszem a hajóra, hacsak nem megy a hajó a konténerek célállomása felé, mert akkor nem tartom őket számon a továbbiakban, mert tudom, hogy sínen vannak
                    HajonKontener k;
                    k.hova = actHajo->hova;
                    k.kontener = *actKontener;                  // Itt másolat készül a konténerről (csökkentett mennyiseg mezővel), így a továbbiakban, ha megváltoztathatom az actKontener értékeit, a kikötőben maradó konténer fog változni
                    k.mikor = graf.nap + actHajo->menetido;
                    //cout << "Nem fer - Nap: " << graf.nap << "   menetido: " << actHajo->menetido << endl;
                    graf.hajonKontenerek.push(k);
                }
                else {                                          // Ha odaérnek a helyhez, akkor
                    kontenerekSzama -= uj.mennyiseg;
                    if (0 < uj.bonuszIdo - actHajo->menetido) bonuszIdore += uj.mennyiseg;
                }
                actKontener->ID = MAX_ID++;
                actKontener->mennyiseg = temp - uj.mennyiseg;   // Ennyi marad a kikötőben
            }
            parancsok.push_back(uj);
        }
        // Ha nem teljesíthető a kívánsága, akkor törlöm a kívánságot, és újrarendezem a kívánságlistát úgy, hogy törlöm az adott elemet, és újra beszúrom (így nem kell az egész rendszert megbolygatni, hanem pár cserével megúszom)
        else {
            pop_heap(kivansagok[0].begin(), kivansagok[0].end(), CompareMennyireEriMegSzallitani);
            kivansagok[0].pop_back();
            if (kivansagok[0].size() != 0) {
                pop_heap(kivansagok.begin(), kivansagok.end(), ComparePriorityQueue);
                push_heap(kivansagok.begin(), kivansagok.end(), ComparePriorityQueue);
            }
            else {
                pop_heap(kivansagok.begin(), kivansagok.end(), ComparePriorityQueue);
                kivansagok.pop_back();
            }
        }
    }

//    int cnt = 0;
//    for (auto v : varosok)
//        for (auto k : v.second.kontenerek)
//            cnt += k.mennyiseg;
//    //cout << cnt << endl;
//    std::priority_queue<HajonKontener, std::vector<HajonKontener>, NapPrioritas> temp = graf.hajonKontenerek;
//    int cnt2 = 0;
//    while (not temp.empty()) {
//        cnt2 += temp.top().kontener.mennyiseg;
//        //cout << temp.top().mikor << endl;
//        temp.pop();
//    }

    if (graf.nap % 200 == 0)
        cout << "Nap: " << graf.nap << "  \tKontenerek szama: " << kontenerekSzama << endl; // << " <> " << cnt << " + " << cnt2 << " = " << cnt+cnt2 << endl;
}

/// ---------------------------------------------------------------------------------------------------
/*
    Megkeresi a legrövidebb utat a gráfban a "honnan" változóban tárolt városból a "hova" változóban tárolt
    városig. A keresés során a gráfot statikusnak tekinti, vagyis eltekint attól, hogy ha mondjuk 3 napot
    utazik, akkor az eltelt három nap alatt meg kéne, hogy változzanak a gráfban az élek súlyai.
*/
int Paszuj::Dijkstra(string honnan, string hova) {
    int min_weight =  graf.csucsok[honnan].min_dist[hova];  // Betöltöm a korábban elvégzett számolás eredményét. Ha eddig még nem végeztem volna el a számolást, akkor az előző sor 0-ra állítja a min_weight-et (mivel új elemet hozott létre a map-ben)
    if (min_weight != 0) return min_weight;                 // Ha már egyszer elvégeztem a számítást, akkor nem kell még egyszer kiszámolni.

    string min_name = honnan;
    set<string> unvisited;                                  // Azokat a csúcsokat tárolom benne, amikről nem tudom, hogy milyen hosszú a belé vezető legrövidebb út.

    const int INF = INT_MAX;

    for (auto i : graf.csucsok) {                           // Kezdetben felteszem, hogy minden csúcsba végtelen hosszú út vezet, és a későbbiekben ezen fogok javítani
        graf.csucsok[i.first].dist = INF;
        unvisited.insert(i.first);
    }

    /* Ez a ciklus azt csinálja, hogy mindig kiválasztja a legkisebb értékkel rendelkező csúcsot
    (vagyis azt a csúcsot, ahova a legrövidebb út vezet, és még nem vizsgáltam),
    és onnan kiindulva megnézem, hogy a többi csúcs értékét tudom-e javítani.
    A ciklus addig tart, míg el nem érek odáig, hogy azt mondhatom, a cél hely jelenleg kiszámolt értékén
    (a legrövidebb útvonal hosszán) már nem tudok javítani, ezért onnan kiindulva készülnék
    javítani a többi csúcs értékén >> erre viszont már nincs szükség, az nem érdekel. */
    while (min_name != hova) {
        unvisited.erase(min_name);
        int min_search = INF;                               // Ezt arra fogom használni, hogy megkeressem, hogy a javított értékű csúcsok közül megkeressem a legkisebbet, ahonnan a következő körben ki fogok indulni.
        Csucs * actual = &(graf.csucsok[min_name]);         // Ez a ciklusmag előző futása során talált legkisebb értékű csúcs, ebből fogok kiindulni
        for (auto i : unvisited) {
            int old_dist = graf.csucsok[i].dist;            // A csúcs eddigi (talán javításra váró értéke)
            if (actual->elek.count(i)) {                    // Ha vezet egyáltalán út a vizsgált csúcsból a javítandó csúcsba
                // A ciklusmag ezen része javít az élek értékén, ha tud
                int new_dist = min_weight + actual->elek[i];// Ennyi lenne az út hossza, ha abból a csúcsból indulnék, amit az előző körben a legkisebb értékűnek találtam
                if (new_dist < old_dist)                    // Ha javít, akkor átírom a csúcs értékét
                        graf.csucsok[i].dist = new_dist;
                // Ez a rész pedig a minimális, eddig még meg nem látogatott csúcsot keresi, ahonnan a következő körben kiindulva próbálok javítani
                if (min_name == hova ? new_dist < min_search : new_dist <= min_search) { // Ezt azért írtam ilyen bonyolultan, hogy a legkisebb élű csúccsal sok egyenlő értékű csúcs van, akkor, ha köztük van a célhely, akkor ezt válassza ki legkisebbnek, mert akkor véget érhet a ciklus (a célhely értékén pedig akkor már úgyse tudok javítani)
                    min_search =  new_dist;
                    min_name = i;
                }
            }   // Ez a rész is a legkisebb értékű csúcsot keresi azok közt az elemek közt, ahova nem vezet él az előző körben minimálisnak talált csúcsból
            else if (old_dist < min_search) {
                min_search =  old_dist;
                min_name = i;
            }
        }
        min_weight = min_search;                            // Ha a belső ciklus véget ért, akkor tudhatjuk, hogy megtaláltuk a minimális értékű csúcsot, aminek eltárolom az értékét a következő kör számára
    }

    graf.csucsok[honnan].min_dist[hova] = min_weight;       // Elmentem a számítás értékét, vagyis, ha legközelebb pontosan e két csúcs közti legrövidebb utat keresem, akkor simán le tudom kérdezni a függvény elején, és nem kell újraszámolnom
    return min_weight;
}

