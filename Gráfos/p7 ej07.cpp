/*
    7. Se dispone de dos grafos (matriz de costes) que representan los costes de viajar entre
    N ciudades españolas utilizando el tren (primer grafo) y el autobús (segundo grafo).
    Ambos grafos representan viajes entre las mismas N ciudades.
    Nuestro objetivo es hallar el camino de coste mínimo para viajar entre dos ciudades
    concretas del grafo, origen y destino, en las siguientes condiciones:
    · La ciudad origen sólo dispone de transporte por tren.
    · La ciudad destino sólo dispone de transporte por autobús.
    · El sector del taxi, bastante conflictivo en nuestros problemas, sigue en huelga,
    por lo que únicamente es posible cambiar de transporte en dos ciudades del
    grafo, cambio1 y cambio2, donde las estaciones de tren y autobús están unidas.
    Implementa un subprograma que calcule la ruta y el coste mínimo para viajar entre
    las ciudades Origen y Destino en estas condiciones.
*/

#include "../alg_grafo_E-S.h"
#include "../alg_grafoPMC.h" //Dijkstra
#include <iostream>

using namespace std;

template <typename tCoste> tCoste viajarTrenBus(const GrafoP<tCoste>& Tren,
    const GrafoP<tCoste>& Bus, typename GrafoP<tCoste>::vertice origen,
    typename GrafoP<tCoste>::vertice destino, typename GrafoP<tCoste>::vertice cambio1,
    typename GrafoP<tCoste>::vertice cambio2);

int main()
{
    GrafoP<int> tren ("matriz7.07Tren.txt");
    GrafoP<int> bus_ ("matriz7.07Bus.txt");

    typename GrafoP<GrafoP<int>::tCoste>::vertice vOrigen = 1, vDestino = 3,
    ciudad1 = 0, ciudad2 = 2;

    cout << "El coste minimo para viajar entre las ciudades origen y destino es: ";
    cout << viajarTrenBus(tren, bus_, vOrigen, vDestino, ciudad1, ciudad2) << endl;

    return 0;
}

template <typename tCoste> tCoste viajarTrenBus(const GrafoP<tCoste>& Tren,
    const GrafoP<tCoste>& Bus, typename GrafoP<tCoste>::vertice origen,
    typename GrafoP<tCoste>::vertice destino, typename GrafoP<tCoste>::vertice cambio1,
    typename GrafoP<tCoste>::vertice cambio2)
{
    typedef Grafo::vertice vertice;

    vector<vertice> P_tren, Pi_bus;
    vector<tCoste> D_tren, Di_bus;

    D_tren = Dijkstra(Tren, origen, P_tren);
    Di_bus = DijkstraInv(Bus, destino, Pi_bus);

    return min(suma(D_tren[cambio1], Di_bus[cambio1]), suma(D_tren[cambio2], Di_bus[cambio2]));

}
