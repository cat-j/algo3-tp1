#include "interfaz_consola.h"

InterfazConsola::InterfazConsola(int p1, int p2) : poda1(p1), poda2(p2) {}

void InterfazConsola::procesarEntrada() {

    cout << "MAMA CORTASTE TODA LA LOZ" << endl;
    int x, y;
    cin >> x >> y;

    while (x != 0 && y != 0) {
        
        int i = x, a = y;
        set<pair<int, int> > encuestas;

        for (int j=0; j<a; j++) {
            cin >> x >> y;
            pair<int, int> p = make_pair(x,y);
            encuestas.insert(p); 
        }

        LicSilverstein silverstein = LicSilverstein(i, encuestas, false, false);
        int res = silverstein.mayorCantidad();
        cout << res << endl;

        cin >> x >> y; // lee el siguiente caso
    }

}