/*
    2. Se dispone de un laberinto de NxN casillas del que se conocen las casillas de entrada
    y salida del mismo. Si te encuentras en una casilla sólo puedes moverte en las siguientes
    cuatro direcciones (arriba, abajo, derecha, izquierda). Por otra parte, entre algunas de las
    casillas hay una pared que impide moverse entre las dos casillas que separa dicha pared
    (en caso contrario no sería un verdadero laberinto).
    Implementa un subprograma que dados
    · N (dimensión del laberinto),
    · la lista de paredes del laberinto,
    · la casilla de entrada, y
    · la casilla de salida,
    calcule el camino más corto para ir de la entrada a la salida y su longitud.
*/

#include "../alg_grafo_E-S.h"
#include "../alg_grafoPMC.h" //Dijkstra
#include <iostream>
using namespace std;

struct casilla  {   int fila, columna;  casilla(int i,int j)        :fila(i),columna(j) {}  };
struct pared    {   casilla c1_,c2_;    pared(casilla c1,casilla c2):c1_(c1),c2_(c2) {}     };

/*-----------------------------------------------------------------------------------------------------------------------*/
template <typename tCoste> casilla verticeToCasilla(typename GrafoP<tCoste>::vertice v,size_t n)
{ return casilla((int)(v/n),(int)(v%n)); }

template <typename tCoste> typename GrafoP<tCoste>::vertice casillaToVertice(casilla c, size_t  n)
{ typename GrafoP<tCoste>::vertice v = c.fila*n+c.columna; return v; }


template <typename tCoste> bool hayPared(typename GrafoP<tCoste>::vertice vertice1, typename GrafoP<tCoste>::vertice vertice2, vector<pared> paredes, size_t N)
{ for(int iii=0; iii<paredes.size(); ++iii)
        if((  casillaToVertice<GrafoP<tCoste>>(paredes[iii].c1_, N) == vertice1 and casillaToVertice<GrafoP<tCoste>>(paredes[iii].c2_, N) == vertice2) or
             (casillaToVertice<GrafoP<tCoste>>(paredes[iii].c2_, N) == vertice1 and casillaToVertice<GrafoP<tCoste>>(paredes[iii].c1_, N) == vertice2))
            return true;
    return false;
}

template <typename tCoste> vector<typename GrafoP<tCoste>::vertice> laberinto
        (casilla casillaEntrada, casilla casillaSalida,int dimensionLaberinto, vector<pared> vectorParedes);

int main()
{
    size_t tamTablero = 3;
    vector<pared> vectorParedes = {    {{0,0},{1,0}},
    {{0,1},{1,1}}, {{1,1},{1,2}}, {{2,0},{2,1}}     };
    vector<Grafo::vertice> vectorVertices;
    GrafoP<int>::tCamino ruta;

    casilla entrada{0,2}, salida{2,0};
    vectorVertices = laberinto<GrafoP<int>::tCoste>(entrada, salida,tamTablero, vectorParedes);

    ruta = camino<GrafoP<int>::tCoste>(casillaToVertice<GrafoP<int>::tCoste>(entrada, tamTablero),
                    casillaToVertice<GrafoP<int>::tCoste>(salida, tamTablero), vectorVertices);

    GrafoP<unsigned int>::tCamino::posicion pos;

    cout << "----------------------" << endl;
    cout << "El camino a seguir es:" << endl;
    cout << "----------------------" << endl;
    cout << "NODO\tCASILLA" << endl;
    pos = ruta.primera();
    while(pos != ruta.fin())
        cout << ruta.elemento(pos) << "\t\
            ("  << verticeToCasilla<GrafoP<int>::tCoste>(ruta.elemento(pos), tamTablero).fila       << ", "
                << verticeToCasilla<GrafoP<int>::tCoste>(ruta.elemento(pos), tamTablero).columna    << ")" << endl,
        pos = ruta.siguiente(pos);
    return 0;
}

template <typename tCoste> vector<typename GrafoP<tCoste>::vertice> laberinto
    (casilla casillaEntrada, casilla casillaSalida, int dimensionLaberinto, vector<pared> vectorParedes)
{
    size_t dimensiones = dimensionLaberinto * dimensionLaberinto;
    typedef typename GrafoP<tCoste>::vertice vertice;
    GrafoP<tCoste> grafoCostes(dimensiones);
    vertice verticeEntrada = casillaToVertice<GrafoP<tCoste>>(casillaEntrada,dimensionLaberinto);
    vertice verticeSalida  = casillaToVertice<GrafoP<tCoste>>(casillaSalida,dimensionLaberinto);
    vector<tCoste> vectorCostes(dimensiones);
    vector<Grafo::vertice> vectorVertices(dimensiones);

    for(int iii=0; iii<grafoCostes.numVert(); ++iii)
    {   grafoCostes[iii][iii] = 0;
        if((iii%dimensionLaberinto) and                         !hayPared<GrafoP<int>::tCoste>(iii, iii-1, vectorParedes, dimensionLaberinto))
            grafoCostes[iii][iii-1] = 1; //izq

        if(((iii+1)%dimensionLaberinto) and                     !hayPared<GrafoP<int>::tCoste>(iii, iii+1, vectorParedes, dimensionLaberinto))
            grafoCostes[iii][iii+1] = 1; //dch

        if(iii > dimensionLaberinto and                         !hayPared<GrafoP<int>::tCoste>(iii, iii-dimensionLaberinto, vectorParedes, dimensionLaberinto))
            grafoCostes[iii][iii-dimensionLaberinto] = 1;//arriba

        if(iii < ((dimensionLaberinto-1)*dimensionLaberinto) and !hayPared<GrafoP<int>::tCoste>(iii, iii+dimensionLaberinto, vectorParedes, dimensionLaberinto))
            grafoCostes[iii][iii+dimensionLaberinto] = 1; //abajo
    }
    cout<<"\tgrafoCostes \n"<< grafoCostes;
    cout<<"\n\tvertices " << verticeEntrada<<" y " <<verticeSalida<<endl;

    vectorCostes = Dijkstra(grafoCostes, verticeEntrada, vectorVertices);
    cout<<"\n\tvectorCostes:"<<endl;
    for(int i=0; i<9;++i)
        cout<<vectorCostes.at(i)<<" ";

    cout << "\n\n\n\tEl coste de ir de " << verticeEntrada << " a " << verticeSalida << " es: " << vectorCostes[verticeSalida] << endl;
    return vectorVertices;
}
