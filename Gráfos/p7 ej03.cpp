/*
    3. Eres el orgulloso due�o de una empresa de distribuci�n. Tu misi�n radica en distribuir
    todo tu stock entre las diferentes ciudades en las que tu empresa dispone de almac�n.
    Tienes un grafo representado mediante la matriz de costes, en el que aparece el coste
    (por unidad de producto) de transportar los productos entre las diferentes ciudades del grafo.
    Pero adem�s resulta que los Ayuntamientos de las diferentes ciudades en las que
    tienes almac�n est�n muy interesados en que almacenes tus productos en ellas, por lo
    que est�n dispuestos a subvencionarte con un porcentaje de los gastos m�nimos de
    transporte hasta la ciudad. Para facilitar el problema, consideraremos despreciables los
    costes de volver el cami�n a su base (centro de producci�n).
    He aqu� tu problema. Dispones de
    � el centro de producci�n, nodo origen en el que tienes tu producto (no tiene almac�n),
    � una cantidad de unidades de producto (cantidad),
    � la matriz de costes del grafo de distribuci�n con N ciudades,
    � la capacidad de almacenamiento de cada una de ellas,
    � el porcentaje de subvenci�n (sobre los gastos m�nimos) que te ofrece cada Ayuntamiento.
    Las diferentes ciudades (almacenes) pueden tener distinta capacidad, y adem�s la
    capacidad total puede ser superior a la cantidad disponible de producto, por lo que
    debes decidir cu�ntas unidades de producto almacenas en cada una de las ciudades.
    Debes tener en cuenta adem�s las subvenciones que recibir�s de los diferentes
    Ayuntamientos, las cuales pueden ser distintas en cada uno y estar�n entre el 0% y el
    100% de los costes m�nimos.
    La soluci�n del problema debe incluir las cantidades a almacenar en cada ciudad bajo
    estas condiciones y el coste m�nimo total de la operaci�n de distribuci�n para tu empresa.
*/

#include "../alg_grafo_E-S.h"
#include "../alg_grafoPMC.h" //Dijkstra
#include <iostream>
using namespace std;

struct almacen{
    float subvencion;
    size_t capacidad, actual=0;
    almacen(float a, size_t b):subvencion(a),capacidad(b){}
};

template <typename tCoste> void empresaDistribucion
    (typename GrafoP<tCoste>::vertice origen, size_t unidades,
      const GrafoP<float>& GGG, vector<almacen>& almacenes);

int main()
{
    vector<almacen> almacenes = {{0,0},{0.1,500},{0.05,600},{0.15,400},{0.2,800}};

    GrafoP<float> GGGG ("matriz7.03.txt");
    size_t unidades = 2000;
    Grafo::vertice origen = 0;

    empresaDistribucion<GrafoP<int>::tCoste>(origen, unidades, GGGG, almacenes);
}

template <typename tCoste> void empresaDistribucion
    (typename GrafoP<tCoste>::vertice origen, size_t unidades,
      const GrafoP<float>& GGG, vector<almacen>& almacenes)
{
    typedef Grafo::vertice vertice;
    vector<vertice> vectorVertices;
    vector<float> costes;
    size_t descargas;
    float costeTotal = 0;

    costes = Dijkstra(GGG, origen, vectorVertices);

    //Costes almacenamiento previo a la subvencion
    cout << "Costes unitarios sin subvenciones" << endl;
    for(vertice iii=1; iii<costes.size(); ++iii)
        cout << "Ciudad " << iii << ": " << costes[iii] << endl;

    //Costes almacenamiento tras aplicar a la subvencion
    cout << endl << "Costes unitarios aplicando subvenciones" << endl;
    for(vertice iii=1; iii<costes.size(); ++iii)
        cout << "Ciudad " << iii << ": " << (costes[iii] *=  (1-almacenes[iii].subvencion) )<< endl;

    descargas = GGG.numVert() - 1;
    while(unidades>0 and descargas>0 )
    {
        vertice ciudadMinCoste; //ciudad con el minimo coste unitario almacenamiento y que tenga sitio.
        float minCoste = GrafoP<float>::INFINITO;
        for(vertice iii=1; iii<costes.size(); ++iii)
            if(costes[iii] < minCoste and almacenes[iii].actual < almacenes[iii].capacidad)
                ciudadMinCoste = iii,
                minCoste = costes[iii];

        if(almacenes[ciudadMinCoste].capacidad <= unidades)
            unidades -= almacenes[ciudadMinCoste].capacidad,
            almacenes[ciudadMinCoste].actual = almacenes[ciudadMinCoste].capacidad;
        else
            almacenes[ciudadMinCoste].actual = unidades,    unidades = 0;

        costeTotal = costeTotal + (almacenes[ciudadMinCoste].actual * minCoste);
        descargas--;
    }

    // Distribucion de las unidades en los almacenes
    cout << endl << "Distribucion de las unidades en los almacenes" << endl;
    for(vertice iii=1; iii<costes.size(); ++iii)
        cout << "Ciudad " << iii << ": " << almacenes[iii].actual << " unidades" << endl;

    cout << "Coste Minimo Total de la distribucion: " << costeTotal << " euros" << endl;
    cout << "Quedan por repartir " << unidades << " unidades" << endl;
}
