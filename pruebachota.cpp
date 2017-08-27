#include <set>
#include <iostream>

using namespace std;

// NO VOY A USAR NI TILDES NI ENIES EN LOS COMENTARIOS PORQUE QUIERO QUE ESTO COMPILE DE UNA

class LicSilverstein {

    /* Esta clase encapsula todas las variables necesarias para resolver el problema planteado:
    las preguntas respondidas, la cantidad de agentes, el tamano de la mejor solucion encontrada
    y la solucion parcial que se esta probando. Los conjuntos se representan con la clase std::set, que
    esta implementada con un red-black tree, para asegurar un orden de complejidad logaritmico en las
    busquedas, inserciones y borrados de los metodos auxiliares. */
    
    public:
        LicSilverstein(int i, int a, set<pair<int,int> > e, bool p) : cantAgentes(i), cantEncuestas(a), encuestas(e) {}
        ~LicSilverstein();

        int mayorCantidad() {
            // Metodo principal.
            return mayorCantidadAux(1);
        }

        int mayorCantidadAux(const int n) {

            /* Metodo auxiliar que extiende a mayorCantidad con un parametro n sobre el que hace recursion.
            En cada llamada, n representa el numero de agente sobre el que tomamos una decision;
            crece hasta que no quedan mas agentes para agregar.
            Complejidad: O(2**cantAgentes * cantAgentes * log(cantAgentes) * cantEncuestas) */

            if (n==cantAgentes) {

                // Caso base: n es el ultimo agente

                if (esValidoAgregar(n)) { solucionParcial.insert(n); }
                maxCantidadEncontrada = solucionParcial.size();
                return solucionParcial.size();

            } else {

                /* Caso recursivo: elegimos la maxima cantidad a la que se puede llegar en cada subarbol
                valido (agregar a n o no agregar a n). */

                int sinAgregar = 0;
                int agregando = 0;

                /* Los siguientes ifs aseguran que esta recursion se corresponde con un arbol de backtracking y
                no con uno de fuerza bruta, puesto que las llamadas recursivas no se efectuan cuando una decision
                resultaria en una solucion invalida que no puede extenderse a una valida. */

                if (esValidoAgregar(n)) {
                    solucionParcial.insert(n);
                    agregando = mayorCantidadAux(n+1);
                    solucionParcial.erase(n); // vuelve para atras: el "backtrack" en backtracking
                }

                if (esValidoNoAgregar(n)) {
                    sinAgregar = mayorCantidadAux(n+1);
                }

                return max(sinAgregar,agregando);
            }
        }

        bool esValidoAgregar(int n) {

            /* Verifica si es posible extender solucionParcial a una solucion valida agregando a n.
            Es importante destacar que esta funcion NO DICE si solucionParcial union n es valida por si sola,
            sino que verifica que ningun agente ya agregado diga que el agente n no es confiable o que n
            diga que algun agente ya agregado no es confiable.
            Si esValidoAgregar verificara la validez de esa solucion, seria imposible extender un conjunto
            que es valido como solucion parcial a uno que es valido como solucion candidata, no se exploraria
            todo el espacio de soluciones y el algoritmo no resolveria el problema. */

            int j = 1;
            while(j < solucionParcial.size()) {
                if (noConfiableSegunJ(n,j)) { return false; }
                j++;
            }
            return true;
        }

        bool esValidoNoAgregar(int n) {

            /* Similar a la funcion anterior. Si algun agente ya agregado dice que n es confiable, devuelve
            False, puesto que seria obligatorio agregar a n dada esa informacion. */

            int j = 1;
            while(j < solucionParcial.size()) {
                if (confiableSegunJ(n,j)) { return false; }
            }
        }

        bool noConfiableSegunJ(int n, int j) {
            for (auto pregunta = encuestas.begin(); pregunta != encuestas.end(); ++pregunta) {
                if ( ( pregunta->first == j && pregunta->second == -n ) || ( pregunta->first == n && pregunta->second == -j ) ) {
                    return false;
                }
            }
            return true;
        }

        bool confiableSegunJ(int n, int j) {
            for (auto pregunta = encuestas.begin(); pregunta != encuestas.end(); ++pregunta) {
                if ( pregunta->first == j && pregunta->second == n ) { return false; }
            }

            return true;
        }

    private:
        set<pair<int,int> > encuestas; //conjunto de preguntas respondidas
        int cantAgentes; //tamano del conjunto de agentes
        int cantEncuestas; //tamano del conjunto de preguntas respondidas; variable auxiliar para hacer mas declarativo el codigo
        int maxCantidadEncontrada; //tamano de la mejor solucion hallada; variable auxiliar para hacer las podas
        set<int> solucionParcial;
        /* esta variable va mutando durante la ejecucion del algoritmo; su estado representa
        el nodo del arbol en el que estamos parados */
};

int main() {
    return 0;
}
