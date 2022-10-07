/*
    13. El archipiélago de las Huríes acaba de ser devastado por un maremoto de
    dimensiones desconocidas hasta la fecha. La primera consecuencia ha sido que todos y
    cada uno de los puentes que unían las diferentes ciudades de las tres islas han sido
    destruidos. En misión de urgencia las Naciones Unidas han decidido construir el
    mínimo número de puentes que permitan unir las tres islas. Asumiendo que el coste de
    construcción de los puentes implicados los pagará la ONU, por lo que se considera
    irrelevante, nuestro problema es decidir qué puentes deben construirse. Las tres islas de
    las Huríes tienen respectivamente N1, N2 y N3 ciudades, de las cuales C1, C2 y C3 son
    costeras (obviamente C1 <= N1 , C2 <= N2 y C3 <= N3) . Nuestro problema es elegir los
    puentes a construir entre todos los posibles. Por tanto, escogeremos aquellos puentes
    que minimicen el coste global de viajar entre todas las ciudades de las tres islas,
    teniendo en cuenta las siguientes premisas:
    1. Se asume que el coste viajar entre las ciudades que unan los puentes es 0.
    2. La ONU subvencionará únicamente el número mínimo de puentes necesario
            para comunicar las tres islas.
    3. Para poder plantearse las mejoras en el transporte que implica la construcción de
            un puente frente a cualquier otro, se asume que se realizarán exactamente el
            mismo número de viajes entre cualesquiera ciudades del archipélago. Dicho de
            otra forma, todos los posibles trayectos a realizar dentro del archipiélago son
            igual de importantes.
    Dadas las matrices de costes directos de las tres islas y las listas de ciudades costeras
    del archipiélago, implementad un subprograma que calcule los puentes a construir en las
    condiciones anteriormente descritas.
*/

#include "../alg_grafo_E-S.h"
#include "../alg_grafoPMC.h" //Dijkstra
#include <iostream>

using namespace std;

struct puente
{ typename GrafoP<GrafoP<int>::tCoste>::vertice A, B; };

struct presupuestoPuente{
    puente P;
    int precio;
};

template <typename tCoste> vector<puente> HuriesDevastacion(const GrafoP<tCoste>& isla1,
const GrafoP<tCoste>& isla2, const GrafoP<tCoste>& isla3, Lista<typename GrafoP<tCoste>::vertice>& C1,
 Lista<typename GrafoP<tCoste>::vertice>& C2, Lista<typename GrafoP<tCoste>::vertice>& C3);

int main()
{
    GrafoP<int> i1 ("matriz7.11isla1.txt");
    GrafoP<int> i2 ("matriz7.11isla2.txt");
    GrafoP<int> i3 ("matriz7.11isla3 .txt");

    vector<puente> puentes;
    Lista<typename GrafoP<GrafoP<int>::tCoste>::vertice> C1, C2, C3;

    C1.insertar(0, C1.fin());
    C1.insertar(1, C1.fin());
    C2.insertar(2, C2.fin());
    C2.insertar(4, C2.fin());
    C3.insertar(5, C3.fin());
    C3.insertar(7, C3.fin());

    puentes = HuriesDevastacion(i1, i2, i3, C1, C2, C3);

    cout << "Puente 1 va de " << puentes[0].A << " a " << puentes[0].B << endl;
    cout << "Puente 2 va de " << puentes[1].A << " a " << puentes[1].B << endl;
}

template <typename tCoste> tCoste costePuente2(const GrafoP<tCoste>& isla1,
    const GrafoP<tCoste>& isla2, typename GrafoP<tCoste>::vertice Cf, typename GrafoP<tCoste>::vertice Cd, size_t N3)
{
    typedef Grafo::vertice vertice;
    tCoste costeGlobal;
    const size_t N1 = isla1.numVert(), N2 = isla2.numVert();

    matriz<vertice> P(N1+N2+N3);
    matriz<tCoste> F(N1+N2+N3);

    GrafoP<tCoste> archipielago(N1+N2+N3);
    for(int i=0; i<N1; ++i)
        for(int j=0; j<N1; ++j)
            archipielago[i][j] = isla1[i][j];
    for(int i=N1; i<N1+N2; ++i)
        for(int j=N1; j<N1+N2; ++j)
            archipielago[i][j] = isla2[i-N1][j-N1];

    archipielago[Cf][Cd] = 0;
    archipielago[Cd][Cf] = 0;

    F = Floyd(archipielago, P);
    // Descomentar para comprobar las matrices de costes minimos segun el puente y su sumatorio
    //cout << endl << "PUENTE DE: " << Cf << " a " << Cd << endl;
    //F.pintarMatriz();
    //cout << "TOTAL: " << sumatorioMatriz(F) << endl;
    return sumatorioMatriz(F);
}

template <typename tCoste> presupuestoPuente HacerPresupuesto(const GrafoP<tCoste>& i1,
    const GrafoP<tCoste>& i2, Lista<typename GrafoP<tCoste>::vertice>& Ci1, Lista<typename GrafoP<tCoste>::vertice>& Ci2, size_t N3)
{
    typedef Grafo::vertice vertice;
    presupuestoPuente Pres;
    puente mejorPuente;
    tCoste costeActual;
    tCoste mejorCoste = GrafoP<tCoste>::INFINITO;
    Lista<vertice>::posicion posCi1;
    Lista<vertice>::posicion posCi2;

    posCi1 = Ci1.primera();
    while(posCi1 != Ci1.fin())
    {
        posCi2 = Ci2.primera();
        while(posCi2 != Ci2.fin())
        {
            costeActual = costePuente2(i1, i2, Ci1.elemento(posCi1), Ci2.elemento(posCi2), N3);
            if(costeActual < mejorCoste)
            {
                mejorCoste = costeActual;
                mejorPuente.A = Ci1.elemento(posCi1);
                mejorPuente.B = Ci2.elemento(posCi2);
            }
            posCi2 = Ci2.siguiente(posCi2);
        }
        posCi1 = Ci1.siguiente(posCi1);
    }
    Pres.P = mejorPuente;
    Pres.precio = mejorCoste;

    return Pres;
}

template <typename tCoste> vector<puente> HuriesDevastacion(const GrafoP<tCoste>& isla1,
const GrafoP<tCoste>& isla2, const GrafoP<tCoste>& isla3, Lista<typename GrafoP<tCoste>::vertice>& C1,
 Lista<typename GrafoP<tCoste>::vertice>& C2, Lista<typename GrafoP<tCoste>::vertice>& C3)
{
    vector<puente> puentes(2); //minimo nº de puentes para unir 3 islas, seran los 2 mas baratos del presupuesto
    vector<presupuestoPuente> presupuesto(3); //presupuestos para 3 puentes p1: C1-C2; p2: C1-C3; p3: C2-C3
    vector<presupuestoPuente> DosPres(2); //los 2 presupuestos mas baratos

    presupuesto[0] = HacerPresupuesto(isla1, isla2, C1, C2, isla3.numVert());
    presupuesto[1] = HacerPresupuesto(isla1, isla3, C1, C3, isla2.numVert());
    presupuesto[2] = HacerPresupuesto(isla2, isla3, C2, C3, isla1.numVert());

    //ya solo falta de los 3 presupuestos, elegir los 2 mas bajos

    DosPres[0] = presupuesto[0];
    DosPres[1] = presupuesto[1];

    if(presupuesto[2].precio < DosPres[0].precio)
        DosPres[0] = presupuesto[2];
    else if(presupuesto[2].precio < DosPres[1].precio)
        DosPres[1] = presupuesto[2];

    puentes[0] = DosPres[0].P;
    puentes[1] = DosPres[1].P;

    return puentes;
}
}
