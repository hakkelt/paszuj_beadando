#include "paszuj.h"
#include <set>
#include <queue>

using namespace std;

/*
    Két konténer-prioritás párt hasonlít össze, az lesz a nagyobb, amelyiknek nagyobb a prioritása.
    Ha egyenlő a két elem prioritása, akkor a bónuszidő dönt. A prioritás ebben az esetben azt írja le,
    hogy ha a konténer átkerülne egy másik helyre, akkor megbecsüli alulról, hogy onnan kb hány nappal
    kevesebb idő alatt ér át a rendeltetési helyére, ezért az lesz a nagyobb prioritású, amelyiknek
    kisebb az így kapott úthossza, ezért van fordítva a relációs jel.
    Ezt a funktort a parancsol függvényben deklarált prioritásos sorhoz hoztam létre.
*/
struct Compare {
    bool operator() (const pair<list<Kontener>::iterator, int> &v1, const pair<list<Kontener>::iterator, int> &v2) {
        if (v1.second == v2.second)
            return v1.first->bonuszIdo > v2.first->bonuszIdo;
        else
            return v1.second > v2.second;
    }
};

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
bool Paszuj::parancsol() {
    bool good = false;

    for (auto h : graf.induloHajok) {
        if (graf.csucsok[h.honnanIndul].kontenerek.size()) {
            good = true;

            priority_queue< pair<list<Kontener>::iterator, int>,
                        vector< pair<list<Kontener>::iterator, int> >,
                        Compare> kontenerLista;

            for (list<Kontener>::iterator k = graf.csucsok[h.honnanIndul].kontenerek.begin();
                k != graf.csucsok[h.honnanIndul].kontenerek.end(); k++) {
                    int kulonbseg = Dijkstra(h.hovaMegy, k->celHely) + h.menetido - Dijkstra(h.honnanIndul, k->celHely);
                    if (0 < kulonbseg)
                        kontenerLista.push( make_pair(k, kulonbseg));
                }

            for(int i = 0; i < h.kapacitas; i++) {
                if (kontenerLista.empty()) break;

                list<Kontener>::iterator act = kontenerLista.top().first;
                kontenerLista.pop();

                Parancs uj;
                uj.bonuszIdo = act->bonuszIdo - graf.nap;
                uj.jaratKod = h.jaratKod;
                uj.mennyiseg = 1;
                uj.mikorErkezik = graf.nap + h.mikorErOda;
                uj.rakomanyNev = act->rakomanyNev;

                graf.csucsok[h.honnanIndul].kontenerek.erase(act);
                if (h.hovaMegy != act->celHely) {
                    act->hely = h.hovaMegy;
                    graf.csucsok[h.hovaMegy].kontenerek.push_back(*act);
                }
            }
        }
    }

    return good;
}

/*
    Megkeresi a legrövidebb utat a gráfban a "honnan" változóban tárolt városból a "hova" változóban tárolt
    városig. A keresés során a gráfot statikusnak tekinti, vagyis eltekint attól, hogy ha mondjuk 3 napot
    utazik, akkor az eltelt három nap alatt meg kéne, hogy változzanak a gráfban az élek súlyai.
*/
int Paszuj::Dijkstra(string honnan, string hova) {
    set<string> visited;

    for (auto i : graf.csucsok)
        i.second.dist = INF;

    int min_weight = 0;
    string min_name = honnan;

    while (min_name != hova){
        visited.insert(min_name);
        int min_search = INF;
        for (auto i : graf.csucsok[min_name].elek)
            if (i.second < INF and visited.count(i.first) and
                (min_name == hova ? min_weight + i.second < graf.csucsok[i.first].dist :
                 min_weight + i.second <= graf.csucsok[i.first].dist)) {
                        graf.csucsok[i.first].dist = min_weight + i.second;
                        if (min_weight + i.second < min_search) {
                            min_search =  min_weight + i.second;
                            min_name = i.first;
                        }
            }
        min_weight = min_search;
    }

    return min_weight;
}

