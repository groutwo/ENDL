/*
    11. Disponemos de tres grafos (matriz de costes) que representan los costes directos de
    viajar entre las ciudades de tres de las islas del archipiélago de las Huríes (Zuelandia).
    Para poder viajar de una isla a otra se dispone de una serie de puentes que conectan
    ciudades de las diferentes islas a un precio francamente asequible (por decisión del
    Prefecto de las Huríes, el uso de los puentes es absolutamente gratuito).
    Si el alumno desea simplificar el problema, puede numerar las N1 ciudades de la isla
    1, del 0 al N1-1, las N2 ciudades de la isla 2, del N1 al N1+N2-1, y las N3 de la última, del
    N1+ N2 al N1+N2+ N3-1.
    Disponiendo de las tres matrices de costes directos de viajar dentro de cada una de
    las islas, y la lista de puentes entre ciudades de las mismas, calculad los costes mínimos
    de viajar entre cualesquiera dos ciudades de estas tres islas.
    ¡¡¡ QUE DISFRUTÉIS EL VIAJE !!!
*/
#include "../alg_grafo_E-S.h"
#include "../alg_grafoPMC.h" //Dijkstra
#include <iostream>

using namespace std;

struct puente
{ typename GrafoP<GrafoP<int>::tCoste>::vertice A, B; };

template <typename tCoste> matriz<tCoste> Huries(const GrafoP<tCoste>& isla1,
const GrafoP<tCoste>& isla2, const GrafoP<tCoste>& isla3, Lista<puente>& puentes);

template <typename tCoste> tCoste sumatorioMatriz(matriz<tCoste> M)
{   tCoste sum=0;
    for(int i=0; i<M.dimension(); ++i)
        for(int j=0; j<M.dimension(); ++j)
            if(M[i][j] != GrafoP<tCoste>::INFINITO)
                sum += M[i][j];
    return sum;
}

int main()
{
    GrafoP<int> i1 ("matriz7.11isla1.txt");
    GrafoP<int> i2 ("matriz7.11isla2.txt");
    GrafoP<int> i3 ("matriz7.11isla3.txt");
    puente p1, p2, p3;
    Lista<puente> puentes;

    p1.A=0; p1.B=2;
    p2.A=1; p2.B=5;
    p3.A=4; p3.B=7;

    puentes.insertar(p1, puentes.fin());
    puentes.insertar(p2, puentes.fin());
    puentes.insertar(p3, puentes.fin());

    cout << "Costes minimos de viajar entre cualesquiera dos ciudades de estas tres islas es: " << endl;
    cout<<Huries(i1, i2, i3, puentes);
}

template <typename tCoste> matriz<tCoste> Huries(const GrafoP<tCoste>& isla1,
const GrafoP<tCoste>& isla2,const GrafoP<tCoste>& isla3, Lista<puente>& puentes)
{
    typedef Grafo::vertice vertice;

    const size_t N1 = isla1.numVert(), N2 = isla2.numVert(), N3 = isla3.numVert();
    Lista<puente>::posicion pos;

    matriz<vertice> PPP(N1+N2+N3);
    matriz<tCoste> FFF(N1+N2+N3);

    GrafoP<tCoste> archipielago(N1+N2+N3);

    for(int i=0; i<N1; ++i)
        for(int j=0; j<N1; ++j)
            archipielago[i][j] = isla1[i][j];

    for(int i=N1; i<N1+N2; ++i)
        for(int j=N1; j<N1+N2; ++j)
            archipielago[i][j] = isla2[i-N1][j-N1];

    for(int i=N1+N2; i<N1+N2+N3; ++i)
        for(int j=N1+N2; j<N1+N2+N3; ++j)
            archipielago[i][j] = isla3[i-N1-N2][j-N1-N2];

    pos = puentes.primera();
    while(pos != puentes.fin())
    {
        archipielago[puentes.elemento(pos).A][puentes.elemento(pos).B] = 0;
        archipielago[puentes.elemento(pos).B][puentes.elemento(pos).A] = 0;
        pos = puentes.siguiente(pos);
    }
    FFF = Floyd(archipielago, PPP);
    return FFF;
}
