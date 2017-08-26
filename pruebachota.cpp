#include <set>
#include <iostream>

using namespace std;

class LicSilverstein {

    /* Esta clase encapsula todas las variables necesarias para resolver el problema planteado:
    las preguntas respondidas, la cantidad de agentes, el tamaño de la mejor solución encontrada
    y la solución parcial que se está probando. Los conjuntos representan con la clase std::set, que
    está implementada con un red-black tree, para asegurar un orden de complejidad logarítmico en las
    búsquedas, inserciones y borrados de los métodos auxiliares. */
    
    public:
        LicSilverstein(int i, int a, set<pair<int,int> > e, bool p) : cantAgentes(i), cantEncuestas(a), encuestas(e) {}
        ~LicSilverstein();

        int mayorCantidad() {
            // Método principal.
            return mayorCantidadAux(1);
        }

        int mayorCantidadAux(const int n) {

            /* Método auxiliar que extiende a mayorCantidad con un parámetro n sobre el que hace recursión.
            En cada llamada, n representa el número de agente sobre el que tomamos una decisión;
            crece hasta que no quedan más agentes para agregar.
            Complejidad: O(2**cantAgentes * cantAgentes * log(cantAgentes) * cantEncuestas) */

            if (n==cantAgentes) {

                // Caso base: n es el último agente

                if (esValidoAgregar(n)) { solucionParcial.insert(n); }
                maxCantidadEncontrada = solucionParcial.size();
                return solucionParcial.size();

            } else {

                /* Caso recursivo: elegimos la máxima cantidad a la que se puede llegar en cada subárbol
                válido (agregar a n o no agregar a n). */

                int sinAgregar = 0;
                int agregando = 0;

                /* Los siguientes ifs aseguran que esta recursión se corresponde con un árbol de backtracking y
                no con uno de fuerza bruta, puesto que las llamadas recursivas no se efectúan cuando una decisión
                resultaría en una solución inválida que no puede extenderse a una válida. */

                if (esValidoAgregar(n)) {
                    solucionParcial.insert(n);
                    agregando = mayorCantidadAux(n+1);
                    solucionParcial.erase(n); // vuelve para atrás: el "backtrack" en backtracking
                }

                if (esValidoNoAgregar(n)) {
                    sinAgregar = mayorCantidadAux(n+1);
                }

                return max(sinAgregar,agregando);
            }
        }

        bool esValidoAgregar(int n) {

            /* Verifica si es posible extender solucionParcial a una solución válida agregando a n.
            Es importante destacar que esta función NO DICE si solucionParcial unión n es válida por sí sola,
            sino que verifica que ningún agente ya agregado diga que el agente n no es confiable o que n
            diga que algún agente ya agregado no es confiable.
            Si esValidoAgregar verificara la validez de esa solución, sería imposible extender un conjunto
            que es válido como solución parcial a uno que es válido como solución candidata, no se exploraría
            todo el espacio de soluciones y el algoritmo no resolvería el problema. */

            int j = 1;
            while(j < solucionParcial.size()) {
                if (noConfiableSegunJ(n,j)) { return false; }
                j++;
            }
            return true;
        }

        bool esValidoNoAgregar(int n) {

            /* Similar a la función anterior. Si algún agente ya agregado dice que n es confiable, devuelve
            False, puesto que sería obligatorio agregar a n dada esa información. */

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
        int cantAgentes; //tamaño del conjunto de agentes
        int cantEncuestas; //tamaño del conjunto de preguntas respondidas; variable auxiliar para hacer más declarativo el código
        int maxCantidadEncontrada; //tamaño de la mejor solución hallada; variable auxiliar para hacer las podas
        set<int> solucionParcial;
        /* esta variable va mutando durante la ejecución del algoritmo; su estado representa
        el nodo del árbol en el que estamos parados */
};

int main() {
    return 0;
}
