#include "lic_silverstein.h"

LicSilverstein::LicSilverstein(int i, int a, set<pair<int,int> > e, bool p1, bool p2) : cantAgentes(i),
cantEncuestas(a), encuestas(e), poda1(p1), poda2(p2), maxCantidadEncontrada(0) {}

int LicSilverstein::mayorCantidad() {
    // Metodo principal.
    return mayorCantidadAux(1);
}

int LicSilverstein::mayorCantidadAux(const int n) {

    /* Metodo auxiliar que extiende a mayorCantidad con un parametro n sobre el que hace recursion.
    En cada llamada, n representa el numero de agente sobre el que tomamos una decision;
    crece hasta que no quedan mas agentes para agregar.
    Complejidad: O(2**cantAgentes * cantAgentes * log(cantAgentes) * cantEncuestas) */

    if (n==cantAgentes) {

        // Caso base: n es el ultimo agente

        if (esValidoAgregar(n)) { solucionParcial.insert(n); }
        maxCantidadEncontrada = max( maxCantidadEncontrada, solucionParcial.size() );
        return solucionParcial.size();

    } else {

        /* Caso recursivo: elegimos la maxima cantidad a la que se puede llegar en cada subarbol
        valido (agregar a n o no agregar a n). */

        int sinAgregar = 0;
        int agregando = 0;

        /* Los siguientes ifs aseguran que esta recursion se corresponde con un arbol de backtracking y
        no con uno de fuerza bruta, puesto que las llamadas recursivas no se efectuan cuando una decision
        resultaria en una solucion invalida que no puede extenderse a una valida. */

        if (esValidoNoAgregar(n)) {
            sinAgregar = mayorCantidadAux(n+1);
        }

        if (esValidoAgregar(n)) {
            solucionParcial.insert(n);
            agregando = mayorCantidadAux(n+1);
            solucionParcial.erase(n); // vuelve para atras: el "backtrack" en backtracking
        }

        return max(sinAgregar,agregando);
    }
}

bool LicSilverstein::esValidoAgregar(int n) {

    /* Verifica si es posible extender solucionParcial a una solucion valida agregando a n.
    Es importante destacar que esta funcion NO DICE si solucionParcial union n es valida por si sola,
    sino que verifica que ningun agente ya agregado diga que el agente n no es confiable, que n
    diga que algun agente ya agregado no es confiable o que n diga que es confiable un agente
    que ya NO puede ser agregado a esta solucion.
    Si esValidoAgregar verificara la validez de esa solucion, seria imposible extender un conjunto
    que es valido como solucion parcial a uno que es valido como solucion candidata, no se exploraria
    todo el espacio de soluciones y el algoritmo no resolveria el problema. */

    int j = 1;

    // Revisa si todos los agentes ya agregados son confiables segun n.
    while(j < solucionParcial.size()) { // peor caso: i iteraciones
        if (noConfiableSegunJ(n,j)) { return false; }
        j++;
    }

    /* Revisa si hay algun agente considerado confiable por n que no haya sido agregado a la solucion parcial
    y no vaya a ser agregado en un nodo descendiente del actual. */
    for (auto pregunta = encuestas.begin(); pregunta != encuestas.end(); ++pregunta) { // peor caso: a iteraciones
        j = pregunta->second;
        if ( pregunta->first == n && jDeberiaEstarSegunNYNoEsta(n, j) ) { return false; } // peor caso: O(log(i))
    }

    return true;
}

bool LicSilverstein::esValidoNoAgregar(int n) {

    /* Similar a la funcion anterior. Si algun agente ya agregado dice que n es confiable, devuelve
    False, puesto que seria obligatorio agregar a n dada esa informacion. */

    int j = 1;
    while(j < solucionParcial.size()) {
        if (confiableSegunJ(n,j)) { return false; }
    }
}

bool LicSilverstein::noConfiableSegunJ(int n, int j) {
    for (auto pregunta = encuestas.begin(); pregunta != encuestas.end(); ++pregunta) {
        if ( ( pregunta->first == j && pregunta->second == -n ) || ( pregunta->first == n && pregunta->second == -j ) ) {
            return false;
        }
    }
    return true;
}

bool LicSilverstein::confiableSegunJ(int n, int j) {
    for (auto pregunta = encuestas.begin(); pregunta != encuestas.end(); ++pregunta) {
        if ( pregunta->first == j && pregunta->second == n ) { return false; }
    }

    return true;
}

bool LicSilverstein::jDeberiaEstarSegunNYNoEsta(int n, int j) {

    /* Devuelve true si j es confiable segun n y podria haber sido agregado en una llamada recursiva anterior pero no lo fue.
    Precondicion: hay alguna tupla (n, k) en las encuestas, con abs(k) == j. */

    if (abs(j) >= n) { return false; } // si j es mayor que n, todavia no llegamos a la llamada que le corresponde
    bool estaJ = solucionParcial.find( abs(j) ) != solucionParcial.end();
    return j>0 && !estaJ;
}

bool LicSilverstein::condicionPoda1(int n) {
    return ( poda1 && solucionParcial.size() + cantAgentes - n + 1 <= maxCantidadEncontrada );
}