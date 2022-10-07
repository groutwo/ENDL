/*
    1. Añadir una función genérica, llamada DijkstraInv, en el fichero
    alg_grafoPMC.h para resolver el problema inverso al de Dijkstra, con los mismos
    tipos de parámetros y de resultado que la función ya incluida para éste. La nueva
    función, por tanto, debe hallar el camino de coste mínimo hasta un destino desde cada
    vértice del grafo y su correspondiente coste.
*/


#include <vector>
#include<iostream>
#include "../alg_grafo_E-S.h"
#include "../alg_grafoPMC.h" //Dijkstra y Floyd
using namespace std;
//Nota-->Ya está definido en "alg_grafoPMC.h", de ahí que esté comentado
/*
template <typename tCoste> vector<tCoste> DijkstraInv(const GrafoP<tCoste>& GrafoCostes,
      typename GrafoP<tCoste>::vertice destino, vector<typename GrafoP<tCoste>::vertice>& vv_)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    vertice verticeV, verticeW;
    const size_t nVert = GrafoCostes.numVert();
    vector<bool> vectorBool(nVert, false);
    vector<tCoste> vectorCostes(nVert);
    for(size_t fila=0; fila<nVert; fila++)
        vectorCostes[fila] = GrafoCostes[fila][destino];
    vectorCostes[destino] = 0;
    vv_ = vector<vertice>(nVert, destino);
    vectorBool[destino] = true;

    for (size_t iii = 1; iii <= nVert-2; iii++)
    {
        tCoste costeMin = GrafoP<tCoste>::INFINITO;
        for (verticeV = 0; verticeV < nVert; verticeV++)
            if (!vectorBool[verticeV] && vectorCostes[verticeV] <= costeMin)
                costeMin = vectorCostes[verticeV], verticeW = verticeV;

        vectorBool[verticeW] = true;
        for (verticeV = 0; verticeV < nVert; verticeV++)
            if (!vectorBool[verticeV])
            {
                tCoste Owv=suma(GrafoCostes[verticeV][verticeW], vectorCostes[verticeW]);
                if (Owv < vectorCostes[verticeV])
                    vectorCostes[verticeV] = Owv, vv_[verticeV] = verticeW;
            }
    }
    return vectorCostes;
}
*/

int main()
{
    cout<<"No probado, pero compila descomentado el c\242digo aqu\241, y coment\240ndolo en el";
     cout<<" otro fichero(alg_grafoPMC.h, aprox l\241nea 130)"<<endl;

    return 0;
}
