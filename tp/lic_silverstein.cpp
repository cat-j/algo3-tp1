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

LicSilverstein::LicSilverstein(int i, set<pair<int,int> > &e, int p1, int p2) :
cantAgentes(i), encuestas(e), poda1(p1), poda2(p2) {
    maxCantidadEncontrada = 0;
}

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

        if (esValidoAgregar(n)) {
            #ifdef DEBUG
            cout << "Llegamos a una hoja. Agregamos " << n << " al conjunto ";
            mostrarSetInts(solucionParcial);
            #endif

            solucionParcial.insert(n);
        } // O(a*log(i))

        int cantidadEncontrada = solucionParcial.size();

        if (cantidadEncontrada > maxCantidadEncontrada) {
            #ifdef DEBUG
            cout << "La cantidad actual " << cantidadEncontrada << " es mayor a "
            << maxCantidadEncontrada << ". Actualizamos." << endl;
            cout << "Mejor solucion encontrada: ";
            mostrarSetInts(solucionParcial);
            #endif

            maxCantidadEncontrada = cantidadEncontrada;
        }


        solucionParcial.erase(n);
        
        return cantidadEncontrada;

    } else {

        /* Caso recursivo: elegimos la maxima cantidad a la que se puede llegar en cada subarbol
        valido (agregar a n o no agregar a n). */

        int sinAgregar = 0;
        int agregando = 0;

        /* Los siguientes ifs aseguran que esta recursion se corresponde con un arbol de backtracking y
        no con uno de fuerza bruta, puesto que las llamadas recursivas no se efectuan cuando una decision
        resultaria en una solucion invalida que no puede extenderse a una valida.
        Ademas, en caso de estar podando el arbol, evitan explorar un subarbol si se cumplen las condiciones
        de poda: o no quedan suficientes agentes en total para superar la maxima cantidad encontrada,
        o no quedan suficientes agentes que no contradigan a los agregados para superar la maxima
        cantidad encontrada. */

        if ( esValidoNoAgregar(n) && !condicionPoda1(n+1) && !condicionPoda2(n+1) ) { // O( max( a*log(i), i^2*log(a) ) )
            #ifdef DEBUG
            cout << "Maximo actual: " << maxCantidadEncontrada << endl;
            cout << "Subarbol izquierdo, nivel " << n << ". No agregamos " << n << " al conjunto ";
            mostrarSetInts(solucionParcial);
            #endif

            sinAgregar = mayorCantidadAux(n+1);
        }

        if ( esValidoAgregar(n) && !condicionPoda1(n) && !condicionPoda2(n) ) { // O( max( a*log(i), i^2*log(a) ) )
            #ifdef DEBUG
            cout << "Maximo actual: " << maxCantidadEncontrada << endl;
            cout << "Subarbol derecho, nivel " << n << ". Agregamos " << n << " al conjunto ";
            mostrarSetInts(solucionParcial);
            #endif

            solucionParcial.insert(n);
            agregando = mayorCantidadAux(n+1);
            solucionParcial.erase(n); // vuelve para atras: el "backtrack" en backtracking
        }

        return max(sinAgregar,agregando);
    }
}

bool LicSilverstein::esValidoAgregar(int n) { // O(a*log(i))

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

        /* Revisa si hay algun agente agregado que no sea considerado confiable por n,
        si n no considera confiable a algun agente agregado o si n no se considera
        confiable a si mismo. */
        if ( k==n && (estaEnSolucion( -j ) || -j == n) ) { return false; } // O(log(i))
        if ( estaEnSolucion(k) && j == -n ) { return false; } // O(log(i))
    
        /* Revisa si hay algun agente considerado confiable por n que no haya sido agregado a la solucion parcial
        y no vaya a ser agregado en un nodo descendiente del actual. */
        //if ( k==n && jDeberiaEstarSegunNYNoEsta(n,j) ) { return false; } // O(log(i))
    }

    return true;
}

bool LicSilverstein::esValidoNoAgregar(int n) { // O(a*log(i))

    /* Similar a la funcion anterior. Si algun agente ya agregado dice que n es confiable
    o n dice que el mismo es confiable, devuelve false, puesto que seria obligatorio agregar
    a n dada esa informacion. */

    for (auto pregunta = encuestas.begin(); pregunta != encuestas.end(); ++pregunta) { // peor caso: a iteraciones
        int k = pregunta->first, j = pregunta->second;
        if ( (estaEnSolucion(k) || k==n) && j==n ) { return false; } // O(log(i))
    }

    return true;
}

bool LicSilverstein::estaEnSolucion(int j) {
    return solucionParcial.find(j) != solucionParcial.end(); // O(log(i))
}

bool LicSilverstein::estaEnEncuestas(std::pair<int, int> j) {
    return encuestas.find(j) != encuestas.end(); // O(log(i))
}

bool LicSilverstein::jDeberiaEstarSegunNYNoEsta(int n, int j) {

    /* Devuelve true si j es confiable segun n y podria haber sido agregado en una llamada recursiva anterior pero no lo fue.
    Precondicion: hay alguna tupla (n, k) en las encuestas, con abs(k) == j. */

    /* si j es mayor o igual que n, todavia no llegamos a la llamada que le corresponde; si es negativo, no es confiable segun n */
    if (abs(j) >= n || j < 0) { return false; }
    return estaEnSolucion(j); // O (log(i))
}

bool LicSilverstein::condicionPoda1(int n) {
    return ( poda1 && solucionParcial.size() + cantAgentes - n + 1 <= maxCantidadEncontrada );
}

bool LicSilverstein::condicionPoda2(int n) {
    int puedenAgregarse = cantAgentesNoDescartados(n); // O(i^2*log(a))
    return ( poda2 && solucionParcial.size() + puedenAgregarse <= maxCantidadEncontrada );
}

int LicSilverstein::cantAgentesNoDescartados(int n) { // O(i^2*log(a))
    int res = 0;
    for (int j=n+1; j<= cantAgentes; j++) { // peor caso: i iteraciones
        for ( auto k = solucionParcial.begin(); k != solucionParcial.end(); ++k ) { // peor caso: i iteraciones
            auto jnok = std::make_pair(j, -(*k));
            auto knoj = std::make_pair(*k, -j);
            if ( !estaEnEncuestas(jnok) && !estaEnEncuestas(knoj) ) { res++; } // O(log(a))
        }
    }

    return res;
}