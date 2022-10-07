/*
    6. Al due�o de una agencia de transportes se le plantea la siguiente situaci�n. La
    agencia de viajes ofrece distintas trayectorias combinadas entre N ciudades espa�olas
    utilizando tren y autob�s. Se dispone de dos grafos que representan los costes (matriz de
    costes) de viajar entre diferentes ciudades, por un lado en tren, y por otro en autob�s
    (por supuesto entre las ciudades que tengan l�nea directa entre ellas). Adem�s coincide
    que los taxis de toda Espa�a se encuentran en estos momentos en huelga general, lo que
    implica que s�lo se podr� cambiar de transporte en una ciudad determinada en la que,
    por casualidad, las estaciones de tren y autob�s est�n unidas.
    Implementa una funci�n que calcule la tarifa m�nima (matriz de costes m�nimos) de
    viajar entre cualesquiera de las N ciudades disponiendo del grafo de costes en autob�s,
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
