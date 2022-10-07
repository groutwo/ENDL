/*
    7. El archipiélago de Grecoland (Zuelandia) está formado únicamente por dos islas,
    Fobos y Deimos, que tienen N1 y N2 ciudades, respectivamente, de las cuales C1 y C2
    ciudades son costeras (obviamente C1 <= N1 y C2 <= N2 ). Se dispone de las coordenadas
    cartesianas (x, y) de todas y cada una de las ciudades del archipiélago. El huracán
    Isadore acaba de devastar el archipiélago, con lo que todas las carreteras y puentes
    construidos en su día han desaparecido. En esta terrible situación se pide ayuda a la
    ONU, que acepta reconstruir el archipiélago (es decir volver a comunicar todas las
    ciudades del archipiélago) siempre que se haga al mínimo coste.
    De cara a poder comparar costes de posibles reconstrucciones se asume lo siguiente:
        1. El coste de construir cualquier carretera o cualquier puente es proporcional a su
            longitud (distancia euclídea entre las poblaciones de inicio y fin de la carretera o
            del puente).
        2. Cualquier puente que se construya siempre será más caro que cualquier carretera
            que se construya.
    De cara a poder calcular los costes de VIAJAR entre cualquier ciudad del
    archipiélago se considerará lo siguiente:
        1. El coste directo de viajar, es decir de utilización de una carretera o de un puente,
            coincidirá con su longitud (distancia euclídea entre las poblaciones origen y
            destino de la carretera o del puente).
    En estas condiciones, implementa un subprograma que calcule el coste mínimo
    de viajar entre dos ciudades de Grecoland, origen y destino, después de haberse
    reconstruido el archipiélago, dados los siguientes datos:
        1. Lista de ciudades de Fobos representadas mediante sus coordenadas cartesianas.
        2. Lista de ciudades de Deimos representadas mediante sus coordenadas cartesianas.
        3. Lista de ciudades costeras de Fobos.
        4. Lista de ciudades costeras de Deimos.
        5. Ciudad origen del viaje.
        6. Ciudad destino del viaje.
*/

#include "../alg_grafo_E-S.h"
#include "../alg_grafoPMC.h"//PrimMaximo//del ejercicio anterior
#include <iostream>
#include <cmath>

using namespace std;

struct ciudad
{
    typename GrafoP<GrafoP<int>::tCoste>::vertice v;  double x, y;
    ciudad(typename GrafoP<int>::vertice vvv = typename GrafoP<int>::vertice(),
            double xxx = 0.0,  double yyy = 0.0): v(vvv),x(xxx),y(yyy){}
};

template <typename tCoste> struct bridge
{
    ciudad A, B; tCoste distancia;
    bridge(ciudad a=ciudad(), ciudad b=ciudad(), tCoste c=tCoste()): A(a), B(b), distancia(c) {}
};

template <typename T> size_t elementosLista(Lista<T>& L)
{
    typename Lista<T>::posicion p = L.primera();
    size_t num = 0;
    while(p != L.fin())     num++, p = L.siguiente(p);
    return num;
}

void inicializaIslas(Lista<ciudad>& Fobos, Lista<ciudad> &Deimos,
Lista<ciudad>& FobosCosteras, Lista<ciudad>& DeimosCosteras, vector<ciudad> vectorCiudades);

template <typename tCoste> tCoste GrecolandIsadore(Lista<ciudad>& F, Lista<ciudad>& D,
Lista<ciudad>& FobosCosteras, Lista<ciudad>& DeimosCosteras, typename GrafoP<tCoste>::vertice origen, typename GrafoP<tCoste>::vertice destino);

template <typename tCoste> bridge<tCoste> puenteMasCorto(Lista<ciudad>& costa1, Lista<ciudad>& costa2);

template <typename tCoste> GrafoP<tCoste> crearGrafodeLista(Lista<ciudad>& L);

double distanciaCiudades(ciudad& A, ciudad& B)
{ return sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2)); }

int main()
{
    vector<ciudad> vectorCiudades = { {0,3,8}, {1,6,3}, {2,9,9}, {3,28,9}, {4,29,4}, {5,33,9} };
    Lista<ciudad> Fobos, Deimos, FobosCosteras, DeimosCosteras;

    typename GrafoP<GrafoP<int>::tCoste>::vertice origen=1, destino=5;

    inicializaIslas(Fobos, Deimos,FobosCosteras, DeimosCosteras, vectorCiudades );

    cout << "El coste minimo para viajar entre las ciudades origen y destino es: ";
    cout << GrecolandIsadore<float>(Fobos, Deimos, FobosCosteras, DeimosCosteras, origen, destino) << endl;


}

void inicializaIslas(Lista<ciudad>& Fobos, Lista<ciudad> &Deimos,
Lista<ciudad>& FobosCosteras, Lista<ciudad>& DeimosCosteras, vector<ciudad> vectorCiudades)
{
    Fobos.insertar(vectorCiudades[0],Fobos.fin());
    Fobos.insertar(vectorCiudades[1],Fobos.fin());
    Fobos.insertar(vectorCiudades[2],Fobos.fin());

    Deimos.insertar(vectorCiudades[3],Deimos.fin());
    Deimos.insertar(vectorCiudades[4],Deimos.fin());
    Deimos.insertar(vectorCiudades[5],Deimos.fin());


    FobosCosteras.insertar(vectorCiudades[1],FobosCosteras.fin());
    FobosCosteras.insertar(vectorCiudades[2],FobosCosteras.fin());

    DeimosCosteras.insertar(vectorCiudades[3],DeimosCosteras.fin());
    DeimosCosteras.insertar(vectorCiudades[4],DeimosCosteras.fin());

}

template <typename tCoste> tCoste GrecolandIsadore(Lista<ciudad>& Fobos, Lista<ciudad>& Deimos,
    Lista<ciudad>& FobosCosteras, Lista<ciudad>& DeimosCosteras,
    typename GrafoP<tCoste>::vertice origen, typename GrafoP<tCoste>::vertice destino)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    vector<tCoste> vectorCostes;
    vector<vertice> vectorVertices;
    bridge<tCoste> unPuente = puenteMasCorto<tCoste>(FobosCosteras, DeimosCosteras);

    GrafoP<tCoste> GFobos = crearGrafodeLista<tCoste>(Fobos);
    GrafoP<tCoste> GDeimos = crearGrafodeLista<tCoste>(Deimos);
    const size_t NFobos = GFobos.numVert();
    const size_t NDeimos = GDeimos.numVert();

    GrafoP<tCoste> PrimGF = Prim(GFobos);
    GrafoP<tCoste> PrimGD = Prim(GDeimos);
    GrafoP<tCoste> GGG(NFobos+NDeimos);

    for(int iii=0; iii<NFobos; ++iii)
        for(int jjj=0; jjj<NFobos; ++jjj)
            GGG[iii][jjj] = PrimGF[iii][jjj];
    for(int iiii = NFobos; iiii < NFobos + NDeimos; ++iiii)
        for(int jjjj = NFobos; jjjj < NFobos+NDeimos; ++jjjj)
            GGG[iiii][jjjj] = PrimGD[iiii-NFobos][jjjj-NFobos];

    GGG[unPuente.A.v][unPuente.B.v] = unPuente.distancia;
    GGG[unPuente.B.v][unPuente.A.v] = unPuente.distancia;

    //cout << GGG;

    vectorCostes = Dijkstra(GGG, origen, vectorVertices);
    return vectorCostes[destino];
}

template <typename tCoste> bridge<tCoste> puenteMasCorto(Lista<ciudad>& costa1, Lista<ciudad>& costa2)
{
    bridge<tCoste> puente;
    tCoste menor = GrafoP<tCoste>::INFINITO;

    for( Lista<ciudad>::posicion p1 = costa1.primera(); p1 != costa1.fin(); p1 = costa1.siguiente(p1) )
    for( Lista<ciudad>::posicion p2 = costa2.primera(); p2 != costa2.fin(); p2 = costa2.siguiente(p2) )
        if(double distancia = distanciaCiudades(costa1.elemento(p1), costa2.elemento(p2))  < menor)
            menor = distancia, puente = bridge<tCoste>(costa1.elemento(p1),costa2.elemento(p2),distancia);
    return puente;
}

template <typename tCoste> GrafoP<tCoste> crearGrafodeLista(Lista<ciudad>& L)
{
    GrafoP<tCoste> GGG(elementosLista(L));
    size_t iii=0,jjj = 0 ;
    for( Lista<ciudad>::posicion pos_i = L.primera() ; pos_i != L.fin(); pos_i = L.siguiente(pos_i),++iii, jjj = 0 )
    for( Lista<ciudad>::posicion pos_j = L.primera() ; pos_j != L.fin(); pos_j = L.siguiente(pos_j),++jjj )
        if(iii != jjj)
            GGG[iii][jjj] = distanciaCiudades(L.elemento(pos_i), L.elemento(pos_j));

    return GGG;
}

