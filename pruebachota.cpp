#include <set>
#include <iostream>

using namespace std;

class LicSilverstein {
    
    public:
        LicSilverstein(int i, int a, set<pair<int,int> > e) : cantAgentes(i), cantEncuestas(a), encuestas(e) {}
        ~LicSilverstein();

        int mayorCantidad() {
            return mayorCantidadAux(1);
        }

        int mayorCantidadAux(const int n) {
            if (n==cantAgentes) {
                if (esValidoAgregar(n)) { solucionParcial.insert(n); }
                maxCantidadEncontrada = solucionParcial.size();
            	return solucionParcial.size();
            } else {
                int sinAgregar = 0;
                int agregando = 0;

                if (esValidoAgregar(n)) {
                    solucionParcial.insert(n);
                    agregando = mayorCantidadAux(n+1);
                    solucionParcial.erase(n);
                }

                if (esValidoNoAgregar(n)) {
                    sinAgregar = mayorCantidadAux(n+1);
                }

                return max(sinAgregar,agregando);
            }
        }

        bool esValidoAgregar(int n) {
            int j = 1;
            while(j < solucionParcial.size()) {
                if (noConfiableSegunJ(n,j)) { return false; }
                j++;
            }
            return true;
        }

        bool esValidoNoAgregar(int n) {
        }

        bool noConfiableSegunJ(int n, int j) {
            for (auto pregunta = encuestas.begin(); pregunta != encuestas.end(); ++pregunta) {
                if ( ( pregunta->first == j && pregunta->second == -n ) || ( pregunta->first == n && pregunta->second == -j ) ) {
                    return false;
                }
            }
            return true;
        }

    private:
        set<pair<int,int> > encuestas;
        int cantAgentes;
        int cantEncuestas;
        int maxCantidadEncontrada;
        set<int> solucionParcial;
};

int main() {
    return 0;
}
