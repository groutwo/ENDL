/*
    12. El archipiélago de Grecoland (Zuelandia) está formado únicamente por dos islas,
    Fobos y Deimos, que tienen N1 y N2 ciudades, respectivamente, de las cuales C1 y C2
    ciudades son costeras (obviamente C1 <= N1 y C2 <= N2). Se desea construir un puente
    que una ambas islas. Nuestro problema es elegir el puente a construir entre todos los
    posibles, sabiendo que el coste de construcción del puente se considera irrelevante. Por
    tanto, escogeremos aquel puente que minimice el coste global de viajar entre todas las
    ciudades de las dos islas, teniendo en cuenta las siguientes premisas:
    1. Se asume que el coste viajar entre las dos ciudades que una el puente es 0.
    2. Para poder plantearse las mejoras en el transporte que implica la construcción de
        un puente frente a cualquier otro, se asume que se realizarán exactamente el
        mismo número de viajes entre cualesquiera ciudades del archipiélago. Por
        ejemplo, se considerará que el número de viajes entre la ciudad P de Fobos y la
        Q de Deimos será el mismo que entre las ciudades R y S de la misma isla. Dicho
        de otra forma, todos los posibles trayectos a realizar dentro del archipiélago son
        igual de importantes.
    Dadas las matrices de costes directos de Fobos y Deimos y las listas de ciudades
    costeras de ambas islas, implementa un subprograma que calcule las dos ciudades que
    unirá el puente.
*/

#include "../alg_grafo_E-S.h"
#include "../alg_grafoPMC.h" //Dijkstra
#include <iostream>

using namespace std;

struct puente
{ typename GrafoP<GrafoP<int>::tCoste>::vertice A, B; };

template <typename tCoste> puente Grecoland(const GrafoP<tCoste>& Fobos,
    const GrafoP<tCoste>& Deimos, Lista<typename GrafoP<tCoste>::vertice>& Cf,
     Lista<typename GrafoP<tCoste>::vertice>& Cd, tCoste& P);

int main(){

    GrafoP<int> F ("matriz7.12Fobos.txt");
    GrafoP<int> D ("matriz7.12Deimos.txt");
    puente mejorPuente;
    int precio;

    Lista<typename GrafoP<GrafoP<int>::tCoste>::vertice> costerasF, costerasD;

    costerasF.insertar(1, costerasF.fin());
    costerasF.insertar(2, costerasF.fin());
    costerasD.insertar(3, costerasD.fin());
    costerasD.insertar(4, costerasD.fin());

    mejorPuente = Grecoland(F, D, costerasF, costerasD, precio);
    cout << "El mejor puente va de la ciudad " << mejorPuente.A << " a la ciudad " << mejorPuente.B << endl;
    cout << "El precio global es de: " << precio << endl;

}

template <typename tCoste> puente Grecoland(const GrafoP<tCoste>& Fobos,
    const GrafoP<tCoste>& Deimos, Lista<typename GrafoP<tCoste>::vertice>& Cf,
     Lista<typename GrafoP<tCoste>::vertice>& Cd, tCoste& P)
{
    typedef Grafo::vertice vertice;

    puente mejorPuente;
    tCoste costeActual, mejorCoste = GrafoP<tCoste>::INFINITO;
    Lista<vertice>::posicion posF, posD;

    posF = Cf.primera();
    while(posF != Cf.fin())
    {
        posD = Cd.primera();
        while(posD != Cd.fin())
        {
            costeActual = costePuente(Fobos, Deimos, Cf.elemento(posF), Cd.elemento(posD));
            if(costeActual < mejorCoste)
            {
                mejorCoste = costeActual;
                mejorPuente.A = Cf.elemento(posF);
                mejorPuente.B = Cd.elemento(posD);
            }
            posD = Cd.siguiente(posD);
        }
        posF = Cf.siguiente(posF);
    }
    P = mejorCoste;
    return mejorPuente;
}

template <typename tCoste> tCoste sumatorioMatriz(matriz<tCoste> M)
{
    tCoste sum=0;
    for(int i=0; i<M.dimension(); ++i)
        for(int j=0; j<M.dimension(); ++j)
            if(M[i][j] != GrafoP<tCoste>::INFINITO)
                sum += M[i][j];
    return sum;
}

template <typename tCoste> tCoste costePuente(const GrafoP<tCoste>& isla1,
    const GrafoP<tCoste>& isla2, typename GrafoP<tCoste>::vertice Cf,
    typename GrafoP<tCoste>::vertice Cd)
{
    typedef Grafo::vertice vertice;
    tCoste costeGlobal;
    const size_t N1 = isla1.numVert();
    const size_t N2 = isla2.numVert();

    matriz<vertice> P(N1+N2);
    matriz<tCoste> F(N1+N2);

    GrafoP<tCoste> archipielago(N1+N2);

    for(int i=0; i<N1; ++i)
        for(int j=0; j<N1; ++j)
            archipielago[i][j] = isla1[i][j];

    for(int i=N1; i<N1+N2; ++i)
        for(int j=N1; j<N1+N2; ++j)
            archipielago[i][j] = isla2[i-N1][j-N1];

    archipielago[Cf][Cd] = 0;
    archipielago[Cd][Cf] = 0;

    F = Floyd(archipielago, P);
    // Descomentar para comprobar las matrices de costes minimos segun el puente y su sumatorio
    //cout << endl << "PUENTE DE: " << Cf << " a " << Cd << endl;
    //F.pintarMatriz();
    //cout << "TOTAL: " << sumatorioMatriz(F) << endl;
    return sumatorioMatriz(F);
}

