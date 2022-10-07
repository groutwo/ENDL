/*
    2. Definiremos el pseudocentro de un grafo conexo como el nodo del mismo que
    minimiza la suma de las distancias mínimas a sus dos nodos más alejados. Definiremos
    el diámetro del grafo como la suma de las distancias mínimas a los dos nodos más
    alejados del pseudocentro del grafo.
    Dado un grafo conexo representado mediante matriz de costes, implementa un
    subprograma que devuelva la longitud de su diámetro.
*/

#include "../alg_grafo_E-S.h"
#include "../alg_grafoPMC.h" //Dijkstra y Floyd
#include <iostream>
using namespace std;

template <typename tCoste> tCoste diametroGrafoConexo(GrafoP<tCoste>& G);

int main()
{
    GrafoP<int> G ("matriz6.2.txt");
    cout << "El diametro del grafo es: " << diametroGrafoConexo(G) << endl;
    return 0;
}

template <typename tCoste> tCoste diametroGrafoConexo(GrafoP<tCoste>& GrafoCostes)
{
    typename GrafoP<tCoste>::vertice pseudocentro;
    matriz<typename GrafoP<tCoste>::vertice> matrizVertices(GrafoCostes.numVert());
    matriz<tCoste> matrizCostes = Floyd(GrafoCostes, matrizVertices);
    cout<<"La matriz de costes es :\n"<<matrizCostes;
    tCoste paresAlejados[2] = {0,0};
    tCoste diametro = GrafoP<tCoste>::INFINITO;

    for(size_t iii = 0; iii < matrizCostes.dimension(); iii++)
    {   paresAlejados[0] = paresAlejados[1] = 0;
        for(size_t jjj = 0; jjj < matrizCostes.dimension(); jjj++)
            if(matrizCostes[iii][jjj] > paresAlejados[0])
                paresAlejados[1] = paresAlejados[0],
                paresAlejados[0] = matrizCostes[iii][jjj];
            else
                if(matrizCostes[iii][jjj] > paresAlejados[1])
                    paresAlejados[1] = matrizCostes[iii][jjj];

        if(paresAlejados[0] + paresAlejados[1] < diametro)
            diametro = paresAlejados[0]+paresAlejados[1], pseudocentro = iii;
    }
    cout<<"\nEl primer par mas alejado es "<< paresAlejados[0];
    cout<<"\nEl segundo par mas alejado es "<< paresAlejados[1];

    cout<<"\nEl pseudocentro es " <<pseudocentro<<endl;
    return diametro;
}
