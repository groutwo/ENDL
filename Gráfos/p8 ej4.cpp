/*
    4. La empresa EMASAJER S.A. tiene que unir mediante canales todas las ciudades del
    valle del Jerte (Cáceres). Calcula qué canales y de qué longitud deben construirse
    partiendo del grafo con las distancias entre las ciudades y asumiendo las siguientes
    premisas:
    - el coste de abrir cada nuevo canal es casi prohibitivo, luego la solución final
        debe tener un número mínimo de canales.
    - el Ministerio de Fomento nos subvenciona por Kms de canal, luego los canales
        deben ser de la longitud máxima posible
*/
#include "../alg_grafo_E-S.h"
#include "../alg_grafoPMC.h"//PrimMaximo//del ejercicio anterior
#include <iostream>

using namespace std;

template<typename tCoste>GrafoP<tCoste>emasajer(GrafoP<tCoste>&distancias,tCoste km_);

int main()
{
    GrafoP<int> distancias("matriz8.4distancias.txt");
    int costePorKm = 100;

    GrafoP<int> resultado = emasajer(distancias, costePorKm);

    cout << "Los canales a construir son" << endl;

    cout << "CANAL\tLONGITUD" << endl;
    for(int i=0; i< resultado.numVert(); ++i)
        for(int j=i; j<resultado.numVert(); ++j)
            if(resultado[i][j] != GrafoP<int>::INFINITO)
                cout << i << "-" << j << "\t" << distancias[i][j] << endl;
    return 0;
}

template<typename tCoste>GrafoP<tCoste>emasajer(GrafoP<tCoste>&distancias,tCoste km_)
{
    const size_t n = distancias.numVert();
    GrafoP<tCoste> g(n);

    for(int i=0; i<n; ++i)
        for(int j=0; j<n; ++j)
            g[i][j] = distancias[i][j] * km_;

    g = PrimMaximo(g);

    return g;
}
