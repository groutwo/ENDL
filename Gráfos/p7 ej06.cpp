/*
    6. Al dueño de una agencia de transportes se le plantea la siguiente situación. La
    agencia de viajes ofrece distintas trayectorias combinadas entre N ciudades españolas
    utilizando tren y autobús. Se dispone de dos grafos que representan los costes (matriz de
    costes) de viajar entre diferentes ciudades, por un lado en tren, y por otro en autobús
    (por supuesto entre las ciudades que tengan línea directa entre ellas). Además coincide
    que los taxis de toda España se encuentran en estos momentos en huelga general, lo que
    implica que sólo se podrá cambiar de transporte en una ciudad determinada en la que,
    por casualidad, las estaciones de tren y autobús están unidas.
    Implementa una función que calcule la tarifa mínima (matriz de costes mínimos) de
    viajar entre cualesquiera de las N ciudades disponiendo del grafo de costes en autobús,
    del grafo de costes en tren, y de la ciudad que tiene las estaciones unidas.
*/

#include "../alg_grafo_E-S.h"
#include "../alg_grafoPMC.h" //Dijkstra
#include <iostream>

using namespace std;

template <typename tCoste> matriz<tCoste> agenciaTransportes(const GrafoP<tCoste>& GGG,
    const GrafoP<tCoste>& GrafoCostes, typename GrafoP<tCoste>::vertice vrtcIntmedio);

template <typename tCoste> tCoste minimo (tCoste A, tCoste B, tCoste C, tCoste D)
{ return min(min(min(A, B), C),D); }

int main()
{
    GrafoP<GrafoP<int>::tCoste> GrafoTren ("matriz7.06Tren.txt");
    GrafoP<GrafoP<int>::tCoste> GrafoBus_ ("matriz7.06Bus.txt");
    typename GrafoP<GrafoP<int>::tCoste>::vertice vrtcIntmedio = 3;

    cout<<agenciaTransportes(GrafoTren, GrafoBus_, vrtcIntmedio);

    return 0;
}

template <typename tCoste> matriz<tCoste> agenciaTransportes(const GrafoP<tCoste>& GGG,
    const GrafoP<tCoste>& GrafoCostes, typename GrafoP<tCoste>::vertice vrtcIntmedio)
{
    typedef Grafo::vertice vertice;
    matriz<vertice> matrizVerticesA, matrizVerticesB;
    matriz<tCoste> costesT, costesA;
    matriz<tCoste> costes(GGG.numVert());

    costesT = Floyd(GGG, matrizVerticesA);
    costesA = Floyd(GrafoCostes, matrizVerticesB);

    for(vertice i=0; i<GGG.numVert(); i++)
        for(vertice j=0; j<GGG.numVert(); j++)
           costes[i][j] = minimo(suma(costesT[i][vrtcIntmedio], costesA[vrtcIntmedio][j]),
                                 suma(costesA[i][vrtcIntmedio], costesT[vrtcIntmedio][j]),
                                 costesT[i][j],
                                 costesA[i][j]);

    return costes;
}
