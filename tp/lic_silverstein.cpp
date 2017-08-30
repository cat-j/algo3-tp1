#include "lic_silverstein.h"

/* -- FUNCIONES AUXILIARES PARA DEBUGGEAR -- */

void mostrarPair(pair<int, int> p) {
    cout << "(" << p.first << "," << p.second << ")";
}

void mostrarSet(set<pair<int,int> > s) {
    cout << "[ ";
    for (auto it = s.begin(); it != s.end(); ++it) {
        mostrarPair(*it);
        cout << " ";
    }
    cout << "]" << endl;
}

void mostrarSetInts(set<int> s) {
    cout << "[ ";
    for (auto it = s.begin(); it != s.end(); ++it) {
        cout << *it << " ";
    }
    cout << "]" << endl;   
}

/* -- CLASE QUE RESUELVE EL PROBLEMA -- */

LicSilverstein::LicSilverstein(int i, set<pair<int,int> > e, int p1, int p2) :
cantAgentes(i), encuestas(e), poda1(p1), poda2(p2) {
    maxCantidadEncontrada = 0;
}

int LicSilverstein::mayorCantidad() {
    // Metodo principal.

    #ifdef MSJPODA
    if (poda1) {
        cout << "Poda 1 activada" << endl;
    }

    if (poda2) {
        cout << "Poda 2 activada" << endl;
    }
    #endif

    return mayorCantidadAux(1, solucionParcial);
}

int LicSilverstein::mayorCantidadAux(const int n, set<int> s) {

    /* Metodo auxiliar que extiende a mayorCantidad con un parametro n sobre el que hace recursion.
    En cada llamada, n representa el numero de agente sobre el que tomamos una decision;
    crece hasta que no quedan mas agentes para agregar.
    Complejidad: O(2**i * i * log(i) * a) */

    if (n==cantAgentes) {
        set<int> solucionHoja = s;

        #ifdef DEBUG
        cout << "Llegamos a una hoja. ";
        mostrarSetInts(solucionParcial);
        #endif

        if (esValidoAgregar(n,solucionHoja)) {
            #ifdef DEBUG
            cout << "Agregamos " << n << " al conjunto ";
            mostrarSetInts(solucionHoja);
            #endif
            solucionHoja.insert(n);
        } else {
            #ifdef DEBUG
            cout << "No agregamos " << n << " al conjunto ";
            mostrarSetInts(solucionHoja);
            #endif
        }

        if ( solucionHoja.size() > maxCantidadEncontrada ) {
            #ifdef DEBUG
            cout << "La cantidad nueva " << solucionHoja.size() << " es mayor a la maxima cantidad encontrada " << maxCantidadEncontrada << ". Actualizamos." << endl;
            #endif 
            maxCantidadEncontrada = solucionHoja.size();
        } 

        return solucionHoja.size();

    } else {
        int sinAgregar = 0, agregando = 0;
        if ( esValidoNoAgregar(n, s) && !condicionPoda1(n, s) && !condicionPoda2(n, s) ) {
            #ifdef DEBUG
            cout << "Maximo actual: " << maxCantidadEncontrada << endl;
            cout << "Padre: ";
            mostrarSetInts(s);
            cout << "Subarbol izquierdo, nivel " << n << ". No agregamos " << n << " al conjunto ";
            mostrarSetInts(s);

            #endif
            sinAgregar = mayorCantidadAux(n+1, s);
        }
        if ( esValidoAgregar(n, s) && !condicionPoda1(n, s) && !condicionPoda2(n, s) ) {
            #ifdef DEBUG
            cout << "Maximo actual: " << maxCantidadEncontrada << endl;
            cout << "Subarbol derecho, nivel " << n << ". Agregamos " << n << " al conjunto ";
            mostrarSetInts(s);
            cout << "Padre: ";
            mostrarSetInts(s);
            #endif
            set<int> s2 = s;
            s2.insert(n);
            agregando = mayorCantidadAux(n+1, s2);
        }
        return max(sinAgregar, agregando);
    }
}

bool LicSilverstein::esValidoAgregar(int n, set<int> &s) { // O(a*log(i))

    /* Verifica si es posible extender solucionParcial a una solucion valida agregando a n.
    Es importante destacar que esta funcion NO DICE si solucionParcial union {n} es valida por si sola,
    sino que verifica que ningun agente ya agregado diga que el agente n no es confiable, que n
    no diga que algun agente ya agregado no es confiable o que n diga que es confiable un agente
    que ya NO puede ser agregado a esta solucion.
    Si esValidoAgregar verificara la validez de esa solucion, seria imposible extender un conjunto
    que es valido como solucion parcial a uno que es valido como solucion candidata, no se exploraria
    todo el espacio de soluciones y el algoritmo no resolveria el problema. */

    for (auto pregunta = encuestas.begin(); pregunta != encuestas.end(); ++pregunta) { // peor caso: a iteraciones

        int k = pregunta->first, j = pregunta->second;

        /* si n dice que un agente en la solucion no es confiable, no podemos agregarlo */
        if ( k==n && estaEnSolucion(-j,s) ) {
            #ifdef DEBUG
            cout << n << " dice que " << -j << " no es confiable, pero " << -j << " esta en la solucion. No podemos agregar a " << n << "." << endl;
            #endif
            return false;
        }

        /* si un agente de la solucion dice que n no es confiable o n no confia en si mismo,
        tampoco podemos agregarlo */
        if ( ( estaEnSolucion(k,s) || k==n ) && j==-n ) {
            #ifdef DEBUG
            cout << k << " dice que " << n << " no es confiable, pero " << k << " esta en la solucion. No podemos agregar a " << n << "." << endl;
            #endif
            return false;
        }

        /* si n dice que un agente j que no esta en la solucion es confiable y no podemos agregar a j
        porque ya deberiamos haberlo hecho en una llamada recursiva anterior, tampoco podemos */
        if ( k==n && j<n && j>0 && !estaEnSolucion(j,s) ) { return false; }
    }

    return true;
}

bool LicSilverstein::esValidoNoAgregar(int n, set<int> &s) { // O(a*log(i))

    /* Similar a la funcion anterior. Si algun agente ya agregado dice que n es confiable
    o n dice que el mismo es confiable, devuelve false, puesto que seria obligatorio agregar
    a n dada esa informacion. */

    for (auto pregunta = encuestas.begin(); pregunta != encuestas.end(); ++pregunta) { // peor caso: a iteraciones

        int k = pregunta->first, j = pregunta->second;

        /* si un agente de la solucion dice que n es confiable, si o si hay que agregarlo */
        if ( estaEnSolucion(k,s) && j==n ) {
            #ifdef DEBUG
            cout << k << " dice que " << n << " no es confiable y " << k << " esta en la solucion. No podemos no agregar a " << n << "." << endl;
            #endif
            return false;
        }
    }

    return true;
}

bool LicSilverstein::estaEnSolucion(int j, set<int> &s) {
    return s.find(j) != s.end(); // O(log(i))
}

bool LicSilverstein::condicionPoda1(int n, set<int> &s) {
    /* Dice si la cantidad de agentes que potencialmente podrian agregarse
    a la solucion parcial s desde el nivel n NO ALCANZA para superar la
    maxima cantidad encontrada hasta el momento. */
    int agentesNoRevisados = cantAgentes - n + 1;
    return ( poda1 && s.size() + agentesNoRevisados <= maxCantidadEncontrada );
}

bool LicSilverstein::condicionPoda2(int n, set<int> &s) {
    int puedenAgregarse = cantAgentesNoDescartados(n, s); // O(i^2*log(a))
    return ( poda2 && s.size() + puedenAgregarse <= maxCantidadEncontrada );
}

int LicSilverstein::cantAgentesNoDescartados(int n, set<int> &s) {
    /* Busca la maxima cantidad de agentes aun no agregados (cuando estamos
    en el nivel n) que no son considerados no confiables por los que ya agregamos
    a la solucion parcial, o que no consideran no confiable a algun agente
    ya agregado a la solucion parcial. */

    /* para empezar asumimos que podemos agregar a todos los agentes que faltan */
    int res = cantAgentes - n + 1;

    for ( auto pregunta = encuestas.begin(); pregunta != encuestas.end(); ++pregunta ) {
        int k = pregunta->first, j = pregunta->second;

        if ( k >= n && estaEnSolucion(-j, s) ) {
            /* algun agente por agregar dice que un agente ya agregado no es confiable,
            por lo que disminuimos la cantidad potencial en 1 */
            res--;
        } else if ( estaEnSolucion(k,s) && -j >= n ) {
            /* algun agente ya agregado dice que un agente por agregar no es confiable,
            por lo que disminuimos la cantidad potencial en 1 */
            res--;
        }
    }
    return res;
}