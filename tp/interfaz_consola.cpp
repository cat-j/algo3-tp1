#include "interfaz_consola.h"
#include <chrono>

using namespace std;

// void mostrarPair(pair<int, int> p) {
//     cout << "(" << p.first << "," << p.second << ")";
// }

// void mostrarSet(set<pair<int,int> > s) {
//     cout << "[ ";
//     for (auto it = s.begin(); it != s.end(); ++it) {
//         mostrarPair(*it);
//         cout << " ";
//     }
//     cout << "]" << endl;
// }

InterfazConsola::InterfazConsola(int p1, int p2) : poda1(p1), poda2(p2) {}

void InterfazConsola::meterEnSet(set<pair<int, int> > &e, int x, int y, int a) {
    /* Procesa un solo caso de la entrada y lo guarda en el set de tuplas e.
    GENERA ALIASING, MODIFICA e.*/

    for (int j=0; j<a; j++) {
        cin >> x >> y;
        pair<int, int> p = make_pair(x,y);
        e.insert(p); 
    }
}

void InterfazConsola::procesarEntrada() {

    int x, y;
    cin >> x >> y;

    while (x != 0 || y != 0) {

        /* Parsea cada caso en un set y ejecuta el algoritmo */
        
        int i = x, a = y;
        set<pair<int, int> > encuestas;
        // cout << "Entrada con " << i << " agentes y " << a << " casos" << endl;

        for (int j=0; j<a; j++) {
            cin >> x >> y;
            pair<int, int> p = make_pair(x,y);
            encuestas.insert(p); 
        }

        // mostrarSet(encuestas);

        LicSilverstein silverstein = LicSilverstein(i, encuestas, poda1, poda2);
        int res = silverstein.mayorCantidad();
        // cout << "Mayor cantidad de agentes: " << res << endl;
        cout << res << endl;

        cin >> x >> y; // lee el siguiente caso
    }

}

void InterfazConsola::tomarTiempos(int repeticiones) {
    cout << "i,a,";

    /* campos para el .csv */
    for (unsigned int i=0; i<repeticiones; i++) {
        cout << "tiempo" << i+1;
        if (i<repeticiones-1) { cout << ","; }
        else { cout << endl; }
    }

    int x, y;
    cin >> x >> y;

    while (x != 0 || y != 0) {
        
        /* Parsea cada caso en un set y ejecuta el algoritmo */

        int i = x, a = y;
        set<pair<int, int> > encuestas;

        meterEnSet(encuestas, x, y, a);

        cout << i << "," << a << ",";

        int repeticiones2 = repeticiones;

        if (i>20) {
            repeticiones2 = repeticiones / 4;
        } 
        
        /* 
        Para un unico caso de la entrada, mide el tiempo de ejecucion la cantidad de veces
        que se especifica en repeticiones y lo ingresa en los campos tiempo1, ... tiempok. */
        for (int j=0; j<repeticiones2; j++) { 
            auto start = chrono::system_clock::now();
            LicSilverstein silverstein = LicSilverstein(i, encuestas, poda1, poda2);
            int res = silverstein.mayorCantidad();
            auto end = chrono::system_clock::now();
            auto elapsed = end-start;
            cout << elapsed.count();
            if (j<repeticiones2-1) { cout << ","; }
            else { cout << endl; }
        }

        cin >> x >> y; // lee el siguiente caso
    }
}