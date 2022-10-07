/*
    4. Se necesita hacer un estudio de las distancias mínimas necesarias para viajar entre
    dos ciudades cualesquiera de un país llamado Zuelandia. El problema es sencillo pero
    hay que tener en cuenta unos pequeños detalles:

        a) La orografía de Zuelandia es un poco especial, las carreteras son muy estrechas
    y por tanto solo permiten un sentido de la circulación.

        b) Actualmente Zuelandia es un país en guerra. Y de hecho hay una serie de
    ciudades del país que han sido tomadas por los rebeldes, por lo que no pueden
    ser usadas para viajar.

        c) Los rebeldes no sólo se han apoderado de ciertas ciudades del país, sino que
    también han cortado ciertas carreteras, (por lo que estas carreteras no pueden ser
    usadas).

        d) Pero el gobierno no puede permanecer impasible ante la situación y ha exigido
    que absolutamente todos los viajes que se hagan por el país pasen por la capital
    del mismo, donde se harán los controles de seguridad pertinentes.

    Dadas estas cuatro condiciones, se pide implementar un subprograma que dados
    · el grafo (matriz de costes) de Zuelandia en situación normal,
    · la relación de las ciudades tomadas por los rebeldes,
    · la relación de las carreteras cortadas por los rebeldes
    · y la capital de Zuelandia,
    calcule la matriz de costes mínimos para viajar entre cualesquiera dos ciudades
    zuelandesas en esta situación.
*/

#include "../alg_grafo_E-S.h"
#include "../alg_grafoPMC.h" //Dij y DijInv
#include <iostream>
using namespace std;

template <typename tCoste> matriz<tCoste> Zuelandia
    (const GrafoP<tCoste>& GrafoCostes, vector<bool> ciudadesTomadas,
     matriz<bool> carreterasCortadas, typename GrafoP<tCoste>::vertice capital);

int main()
{
    GrafoP<int> GGG ("matriz6.4.txt");
    vector<bool> ciudadesTomadas(GGG.numVert(), false);
    matriz<bool> carreterasCortadas(GGG.numVert(), false);
    Grafo::vertice capital = 0;
    ciudadesTomadas[1] = true; // la ciudad 2 está tomada
    carreterasCortadas[3][4] = carreterasCortadas[3][0] = true; // cortamos la carretera de 3->4 y la 3->0

    matriz<int> matrizCostes = Zuelandia(GGG, ciudadesTomadas, carreterasCortadas, capital);

    cout<<"La matriz de costes pedida es: \n"<<matrizCostes<<endl;
    return 0;
}

template <typename tCoste> matriz<tCoste> Zuelandia
    (const GrafoP<tCoste>& GrafoCostes, vector<bool> ciudadesTomadas,
     matriz<bool> carreterasCortadas, typename GrafoP<tCoste>::vertice capital)
{
    GrafoP<tCoste> GrafoAux(GrafoCostes.numVert());
    GrafoAux = actualizarGrafo(GrafoCostes,carreterasCortadas,ciudadesTomadas);
    cout<<"Los resultados de aplicar los cortes en las ciudades y carreteras son: \n"<<GrafoAux<<endl;

    vector<typename GrafoP<tCoste>::vertice> vectorVertices(GrafoCostes.numVert());
    vector<tCoste>  vectorCostes1 = DijkstraInv (GrafoAux, capital, vectorVertices),//coste de cada ciudad a la capital
                    vectorCostes2 = Dijkstra    (GrafoAux, capital, vectorVertices);//costes de capital a cada ciudad
    cout<<"El resultado de aplicar Dijktra inverso es: "<<vectorCostes1<<endl;
    cout<<"El resultado de aplicar Dijktra normal es: "<<vectorCostes2<<endl;

    matriz<tCoste>matrizCostes(GrafoCostes.numVert());

    for(size_t iii = 0; iii < GrafoCostes.numVert(); iii++)
        for(size_t jjj = 0; jjj < GrafoCostes.numVert(); jjj++)
            if((vectorCostes1[iii] != GrafoP<tCoste>::INFINITO && vectorCostes2[jjj] != GrafoP<tCoste>::INFINITO )&& (iii!=jjj))
                matrizCostes[iii][jjj] = vectorCostes1[i] + vectorCostes2[j];
            else if((iii==jjj) && (vectorCostes1[iii] != GrafoP<tCoste>::INFINITO && vectorCostes2[jjj] != GrafoP<tCoste>::INFINITO))
                matrizCostes[iii][jjj] = 0;
            else
                matrizCostes[iii][jjj] = GrafoP<tCoste>::INFINITO;

    return matrizCostes;
}

template <typename tCoste> GrafoP<tCoste> actualizarGrafo
    (const GrafoP<tCoste>& GrafoCostes, matriz<bool> carreterasCortadas,
     vector<bool> ciudadesTomadas)
{
    GrafoP<tCoste> GrafoAux(GrafoCostes.numVert());

    for(size_t ii2 = 0; ii2 < GrafoCostes.numVert(); ii2++)
        for(size_t jj2 = 0; jj2 < GrafoCostes.numVert(); jj2++)
            //Recordemos que true significa que está cortada/tomada; es decir, no accesible, luego coste infinito
            if(ciudadesTomadas[ii2] || ciudadesTomadas[jj2])   GrafoAux[ii2][jj2] = GrafoP<tCoste>::INFINITO;
            else    GrafoAux[ii2][jj2] = (carreterasCortadas[ii2][jj2] ? GrafoP<tCoste>::INFINITO : GrafoCostes[ii2][jj2]);

    return GrafoAux;
}
