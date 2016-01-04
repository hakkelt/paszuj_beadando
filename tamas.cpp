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
void Paszuj::parancsol() {

    for (auto h : graf.induloHajok) {
        if (graf.csucsok[h.honnanIndul].kontenerek->size()) {
            priority_queue< pair<list<Kontener>::iterator, int>,
                        vector< pair<list<Kontener>::iterator, int> >,
                        Compare> kontenerLista;

            for (list<Kontener>::iterator k = graf.csucsok[h.honnanIndul].kontenerek->begin();
                k != graf.csucsok[h.honnanIndul].kontenerek->end(); k++) {
                    int kulonbseg = Dijkstra(h.hovaMegy, k->celHely) + h.menetido - Dijkstra(h.honnanIndul, k->celHely);
                        kontenerLista.push( make_pair(k, kulonbseg));
                }

            int i = 0;
            while (i < h.kapacitas and not kontenerLista.empty()) {

                list<Kontener>::iterator act = kontenerLista.top().first;
                kontenerLista.pop();

                Parancs uj;
                uj.bonuszIdo = (act->bonuszIdo - graf.nap < 0 ? 0 : act->bonuszIdo - graf.nap);
                uj.jaratKod = h.jaratKod;
                uj.mikorErkezik = graf.nap + h.menetido;
                uj.rakomanyNev = act->rakomanyNev;
                if (i + act->mennyiseg <= h.kapacitas) {
                    uj.mennyiseg = act->mennyiseg;
                    if (h.hovaMegy != act->celHely)
                        graf.csucsok[h.hovaMegy].kontenerek->push_back(*act);
                    else {
                        kontenerekSzama -= act->mennyiseg;
                        if (0 < uj.bonuszIdo) bonuszIdore += act->mennyiseg;
                    }
                    graf.csucsok[h.honnanIndul].kontenerek->erase(act);
                }
                else {
                    uj.mennyiseg = h.kapacitas - i;
                    int temp = act->mennyiseg;
                    act->mennyiseg = h.kapacitas - i;
                    if (h.hovaMegy != act->celHely)
                        graf.csucsok[h.hovaMegy].kontenerek->push_back(*act);
                    else {
                        kontenerekSzama -= act->mennyiseg;
                        if (0 < uj.bonuszIdo) bonuszIdore += act->mennyiseg;
                    }
                    act->mennyiseg = temp - act->mennyiseg;
                }
                parancsok.push_back(uj);
                i += uj.mennyiseg;
            }
        }
    }

    if (graf.nap % 200 == 0)
        cout << "Nap: " << graf.nap << "  \tKontenerek szama: " << kontenerekSzama << endl;
}

/*
    Megkeresi a legrövidebb utat a gráfban a "honnan" változóban tárolt városból a "hova" változóban tárolt
    városig. A keresés során a gráfot statikusnak tekinti, vagyis eltekint attól, hogy ha mondjuk 3 napot
    utazik, akkor az eltelt három nap alatt meg kéne, hogy változzanak a gráfban az élek súlyai.
*/
int Paszuj::Dijkstra(string honnan, string hova) {
    int min_weight =  graf.csucsok[honnan].min_dist[hova];
    if (min_weight != 0) return min_weight;

    string min_name = honnan;

    set<string> unvisited;

    const int INF = INT_MAX;

    for (auto i : graf.csucsok) {
        graf.csucsok[i.first].dist = INF;
        unvisited.insert(i.first);
    }

    while (min_name != hova) {
        unvisited.erase(min_name);
        int min_search = INF;
        Csucs * actual = &(graf.csucsok[min_name]);
        for (auto i : unvisited) {
            int old_dist = graf.csucsok[i].dist;
            if (actual->elek.count(i)) {
                int new_dist = min_weight + actual->elek[i];
                if (min_name == hova ? new_dist < old_dist : new_dist <= old_dist) {
                        graf.csucsok[i].dist = new_dist;
                        }
                if (new_dist < min_search) {
                    min_search =  new_dist;
                    min_name = i;
                }
            }
            else if (old_dist < min_search) {
                min_search =  old_dist;
                min_name = i;
            }
        }
        min_weight = min_search;
    }

    graf.csucsok[honnan].min_dist[hova] = min_weight;
    return min_weight;
}

