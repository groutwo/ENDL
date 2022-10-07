/*
    3. Tu empresa de transportes “PEROTRAVEZUNGRAFO S.A.” acaba de recibir la
    lista de posibles subvenciones del Ministerio de Fomento en la que una de las más
    jugosas se concede a las empresas cuyo grafo asociado a su matriz de costes sea
    acíclico. ¿Puedes pedir esta subvención?
    Implementa un subprograma que a partir de la matriz de costes nos indique si tu
    empresa tiene derecho a dicha subvención.
*/

#include "../alg_grafo_E-S.h"
#include "../alg_grafoMA.h" //Warshall
#include <iostream>
using namespace std;

template <typename tCoste>bool tieneCiclos(const GrafoP<tCoste>& G);

int main()
{
    GrafoP<int> G_1 ("matriz6-3A.txt");
    GrafoP<int> G_2 ("matriz6-3B.txt");
    GrafoP<int> G_3 ("matriz6-3C.txt");

    tieneCiclos(G_1)? cout << "NO ": cout << " SI ";
    cout<<"puedes pedir la subvencion en la matriz 1\n\
    ----------------------------------------------------"<< endl;

    tieneCiclos(G_2)? cout << "NO ": cout << " SI ";
    cout<<"puedes pedir la subvencion en la matriz 2\n\
    ----------------------------------------------------"<< endl;

    tieneCiclos(G_3)? cout << "NO ": cout << " SI ";
    cout<<"puedes pedir la subvencion en la matriz 3\n\
    ----------------------------------------------------"<< endl;
}

template <typename tCoste> bool tieneCiclos(const GrafoP<tCoste>& GrafoCostes)
{
    bool ciclo = false;
    Grafo GrafoAux(GrafoCostes.numVert());

    for(int iii=0; iii < GrafoCostes.numVert(); iii++)
        for(int jjj=0; jjj < GrafoCostes.numVert(); jjj++)
            GrafoAux[iii][jjj] = (GrafoCostes[iii][jjj] != GrafoP<tCoste>::INFINITO);

    matriz<bool> matrizBools = Warshall(GrafoAux);
    cout << matrizBools;

    for(int iou=0; iou < matrizBools.dimension() && !ciclo; iou++)
        if(matrizBools[iou][iou])
            ciclo = true;

    return ciclo;
}
