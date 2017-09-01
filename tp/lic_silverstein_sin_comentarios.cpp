#include "lic_silverstein.h"

LicSilverstein::LicSilverstein(int i, int a, set<pair<int,int> > e, bool p1, bool p2) : cantAgentes(i),
cantEncuestas(a), encuestas(e), poda1(p1), poda2(p2), maxCantidadEncontrada(0) {}

int LicSilverstein::mayorCantidad() {
    return mayorCantidadAux(1);
}

int LicSilverstein::mayorCantidadAux(const int n) {

    if (n==cantAgentes) {
        if (esValidoAgregar(n)) { solucionParcial.insert(n); } // O(a*log(i))
        maxCantidadEncontrada = max( maxCantidadEncontrada, solucionParcial.size() );
        return solucionParcial.size();
    } else {
        int sinAgregar = 0;
        int agregando = 0;

        if ( esValidoNoAgregar(n) && !condicionPoda1(n+1) ) { // O(a*log(i))
            sinAgregar = mayorCantidadAux(n+1);
        }

        if ( esValidoAgregar(n) && !condicionPoda1(n) ) { // O(a*log(i))
            solucionParcial.insert(n);
            agregando = mayorCantidadAux(n+1);
            solucionParcial.erase(n); // vuelve para atras: el "backtrack" en backtracking
        }

        return max(sinAgregar,agregando);
    }
}

bool LicSilverstein::esValidoAgregar(int n) { // O(a*log(i))
    for (auto pregunta = encuestas.begin(); pregunta != encuestas.end(); ++pregunta) { // peor caso: a iteraciones
        int k = pregunta->first, j = pregunta->second;

        if ( k==n && estaEnSolucion( -j ) ) { return false }; // O(log(i))
        if ( estaEnSolucion(k) && j == -n ) { return false }; // O(log(i))
        if ( k==n && jDeberiaEstarSegunNYNoEsta(n,j) ) { return false; } // O(log(i))
    }

    return true;
}

bool LicSilverstein::esValidoNoAgregar(int n) { // O(a*log(i))
    for (auto pregunta = encuestas.begin(); pregunta != encuestas.end(); ++pregunta) { // peor caso: a iteraciones
        int k = pregunta->first, j = pregunta->second;
        if ( estaEnSolucion(k) && j==n ) { return false; } // O(log(i))
    }

    return true;
}

bool estaEnSolucion(int j) {
    return solucionParcial.find(j) != solucionParcial.end(); // O(log(i))
}

bool LicSilverstein::jDeberiaEstarSegunNYNoEsta(int n, int j) {
    if (abs(j) >= n || j < 0) { return false; }
    return estaEnSolucion(j); // O (log(i))
}

bool LicSilverstein::condicionPoda1(int n) {
    return ( poda1 && solucionParcial.size() + cantAgentes - n + 1 <= maxCantidadEncontrada );
}

bool LicSilverstein::condicionPoda2(int n) {
    int puedenAgregarse = cantAgentesNoDescartados(n);
    return ( poda2 && solucionParcial.size() + puedenAgregarse <= maxCantidadEncontrada );
}

int LicSilverstein::cantAgentesNoDescartados(int n) {
    int res = 0, j = n+1;
    return res;
}