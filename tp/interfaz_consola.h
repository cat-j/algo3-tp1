#include <set>
#include <iostream>
#include "lic_silverstein.h"

using namespace std;

#ifndef INTERFAZ_CONSOLA
#define INTERFAZ_CONSOLA

using namespace std;

class InterfazConsola {
    public:
        InterfazConsola(int p1, int p2);
        void meterEnSet(set<pair<int, int> > &e, int x, int y, int a);
        void procesarEntrada();
        void tomarTiempos(int repeticiones);

    private:
    	int poda1, poda2;
};

#endif