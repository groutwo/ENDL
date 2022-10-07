/*
    5. Se dispone de tres grafos que representan la matriz de costes para viajes en un
    determinado país pero por diferentes medios de transporte, por supuesto todos los grafos
    tendrán el mismo número de nodos. El primer grafo representa los costes de ir por
    carretera, el segundo en tren y el tercero en avión. Dado un viajero que dispone de una
    determinada cantidad de dinero, que es alérgico a uno de los tres medios de transporte, y
    que sale de una ciudad determinada, implementar un subprograma que determine las
    ciudades a las que podría llegar nuestro infatigable viajero.
*/

#include "../alg_grafo_E-S.h"
#include "../alg_grafoPMC.h" //Dijkstra
#include <iostream>

using namespace std;

template <typename tCoste> vector<bool> posiblesDestinos(const GrafoP<tCoste>& C,
const GrafoP<tCoste>& T, const GrafoP<tCoste>& A, const char alergia,
 const tCoste dinero, typename GrafoP<tCoste>::vertice origen);

int main()
{
    GrafoP<GrafoP<int>::tCoste> C ("matriz7.05C.txt");
    GrafoP<GrafoP<int>::tCoste> T ("matriz7.05T.txt");
    GrafoP<GrafoP<int>::tCoste> A ("matriz7.05A.txt");

    char alergia = 'C';
    GrafoP<int>::tCoste dinero = 100;
    typename GrafoP<GrafoP<int>::tCoste>::vertice origen = 0;

    vector<bool> destinosPosibles = posiblesDestinos(C, T, A, alergia, dinero, origen);

    cout << "Ciudades a las que podria llegar nuestro infatigable viajero" << endl;
    for(int i=0; i<C.numVert(); ++i)
        if(i != origen and destinosPosibles[i])
            cout << "Ciudad " << i << endl;
}

template <typename tCoste> vector<bool> posiblesDestinos(const GrafoP<tCoste>& C,
const GrafoP<tCoste>& T, const GrafoP<tCoste>& A, const char alergia,
 const tCoste dinero, typename GrafoP<tCoste>::vertice origen)
{
    int nciudades = C.numVert();
    vector<bool> vctBoolPuedeViajar(nciudades, false);

    vector<typename GrafoP<tCoste>::vertice> vctVrtcMedio1,vctVrtcMedio2;
    vector<tCoste> vctCostesMedio1,vctCostesMedio2;

    if(alergia == 'C' or alergia == 'c')
        vctCostesMedio1 = Dijkstra(T , origen, vctVrtcMedio1),
        vctCostesMedio2 = Dijkstra(A , origen, vctVrtcMedio2);
    else if(alergia == 'T' or alergia == 't')
        vctCostesMedio1 = Dijkstra(C , origen, vctVrtcMedio1),
        vctCostesMedio2 = Dijkstra(A , origen, vctVrtcMedio2);
    else //alergico al avion
        vctCostesMedio1 = Dijkstra(C , origen, vctVrtcMedio1),
        vctCostesMedio2 = Dijkstra(T , origen, vctVrtcMedio2);

    for(GrafoP<int>::tCoste iii=0; iii<nciudades; ++iii)
        if(vctCostesMedio1[iii] <= dinero or vctCostesMedio2[iii] <= dinero)
            vctBoolPuedeViajar[iii] = true;

    return vctBoolPuedeViajar;
}
