/*
    1. A�adir una funci�n gen�rica, llamada DijkstraInv, en el fichero
    alg_grafoPMC.h para resolver el problema inverso al de Dijkstra, con los mismos
    tipos de par�metros y de resultado que la funci�n ya incluida para �ste. La nueva
    funci�n, por tanto, debe hallar el camino de coste m�nimo hasta un destino desde cada
    v�rtice del grafo y su correspondiente coste.
*/


#include <vector>
#include<iostream>
#include "../alg_grafo_E-S.h"
#include "../alg_grafoPMC.h" //Dijkstra y Floyd
using namespace std;
//Nota-->Ya est� definido en "alg_grafoPMC.h", de ah� que est� comentado
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
