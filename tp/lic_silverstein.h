#include <set>
#include <iostream>

using namespace std;

#ifndef LIC_SILVERSTEIN_H
#define LIC_SILVERSTEIN_H

// #define DEBUG
// #define MSJPODA

void mostrarPair(pair<int, int> p);
void mostrarSet(set<pair<int,int> > s);

class LicSilverstein {

    /* Esta clase encapsula todas las variables necesarias para resolver el problema planteado:
    las preguntas respondidas, la cantidad de agentes, el tamano de la mejor solucion encontrada
    y la solucion parcial que se esta probando. Los conjuntos se representan con la clase std::set, que
    esta implementada con un red-black tree, para asegurar un orden de complejidad logaritmico en las
    busquedas, inserciones y borrados de los metodos auxiliares. */

    public:
        LicSilverstein(int i, set<pair<int,int> > e, int p1, int p2);

        int mayorCantidad();

    private:

        // metodos auxiliares, ver detalles en implementacion

        int mayorCantidadAux(const int n, set<int> s);

        bool esValidoAgregar(int n, set<int> &s);
        bool esValidoNoAgregar(int n, set<int> &s);

        bool estaEnSolucion(int j, set<int> &s);
        
        bool condicionPoda1(int n, set<int> &s);
        bool condicionPoda2(int n, set<int> &s);
        
        int cantAgentesNoDescartados(int n, set<int> &s);

        set<pair<int,int> > encuestas; //conjunto de preguntas respondidas
        int cantAgentes; //tamano del conjunto de agentes
        int maxCantidadEncontrada; //tamano de la mejor solucion hallada; variable auxiliar para hacer las podas
        set<int> solucionParcial;
        /* esta variable va mutando durante la ejecucion del algoritmo; su estado representa
        el nodo del arbol en el que estamos parados */
        int poda1;
        int poda2;

};

#endif