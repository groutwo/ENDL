/*
    8. “UN SOLO TRANSBORDO, POR FAVOR”. Este es el título que reza en tu
    flamante compañía de viajes. Tu publicidad explica, por supuesto, que ofreces viajes
    combinados de TREN y/o AUTOBÚS (es decir, viajes en tren, en autobús, o usando
    ambos), entre N ciudades del país, que ofreces un servicio inmejorable, precios muy
    competitivos, y que grafoTrenrantizas ante notario algo que no ofrece ninguno de tus
    competidores: que en todos tus viajes COMO MÁXIMO se hará un solo transbordo
    (cambio de medio de transporte).
    Bien, hoy es 1 de Julio y comienza la temporada de viajes.
    ¡Qué suerte! Acaba de aparecer un cliente en tu oficina. Te explica que quiere viajar
    entre dos ciudades, Origen y Destino, y quiere saber cuánto le costará.
    Para responder a esa pregunta dispones de dos grafos de costes directos (matriz de
    costes) de viajar entre las N ciudades del país, un grafo con los costes de viajar
    en tren y otro en autobús.
    Implementa un subprograma que calcule la tarifa mínima en estas condiciones.
    Mucha suerte en el negocio, que la competencia es dura.
*/

#include "../alg_grafo_E-S.h"
#include "../alg_grafoPMC.h" //Dijkstra
#include <iostream>

using namespace std;

template <typename tCoste> tCoste unTransbordo(const GrafoP<tCoste> grafoTren, const GrafoP<tCoste> grafoBus,
    const typename GrafoP<tCoste>::vertice origen, const typename GrafoP<tCoste>::vertice destino);

int main()
{
    GrafoP<int> tren ("matriz7.08Tren.txt");
    GrafoP<int> bus_ ("matriz7.08Bus.txt");

    typename GrafoP<GrafoP<int>::tCoste>::vertice vOrigen = 3, vDestino = 1;

    cout << "El coste minimo para viajar entre la ciudad "<<vOrigen<<" y "<< vDestino;
    cout << " es "<<unTransbordo(tren,bus_,vOrigen,vDestino)<< endl;
}

template <typename tCoste> tCoste unTransbordo(const GrafoP<tCoste> grafoTren, const GrafoP<tCoste> grafoBus,
    const typename GrafoP<tCoste>::vertice origen, const typename GrafoP<tCoste>::vertice destino)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    vector<vertice> vectorTren(grafoTren.numVert()), vectorBus(grafoBus.numVert());
    vector<tCoste>  vectorCostesTren    = Dijkstra(grafoTren,origen,vectorTren),
                    vectorCostesBus     = Dijkstra(grafoBus,origen,vectorBus),
                    vectorCostesTrenInv = DijkstraInv(grafoTren,destino,vectorTren),
                    vectorCostesBusInv  = DijkstraInv(grafoBus,destino,vectorBus);

    for(vertice kkk = 0; kkk < grafoTren.numVert(); kkk++)
        vectorCostesTren[destino] = min(vectorCostesTren[destino], vectorCostesTren[kkk] + vectorCostesBusInv[kkk] ),
        vectorCostesBus[destino] = min(vectorCostesBus[destino] , vectorCostesBus[kkk]+vectorCostesTrenInv[kkk]);

    return min(vectorCostesTren[destino], vectorCostesBus[destino]);
}
