#include "interfaz_consola.h"

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

void InterfazConsola::procesarEntrada() {

    int x, y;
    cin >> x >> y;

    while (x != 0 && y != 0) {
        
        int i = x, a = y;
        set<pair<int, int> > encuestas;
        cout << "Entrada con " << i << " agentes y " << a << " casos" << endl;

        for (int j=0; j<a; j++) {
            cin >> x >> y;
            pair<int, int> p = make_pair(x,y);
            encuestas.insert(p); 
        }

        mostrarSet(encuestas);

        LicSilverstein silverstein = LicSilverstein(i, encuestas, poda1, poda2);
        int res = silverstein.mayorCantidad();
        cout << "Mayor cantidad de agentes: " << res << endl;

        cin >> x >> y; // lee el siguiente caso
    }

}