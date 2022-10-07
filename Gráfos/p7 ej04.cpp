/*
    4. Eres el orgulloso dueño de la empresa “Cementos de Zuelandia S.A”. Empresa
    dedicada a la fabricación y distribución de cemento, sita en la capital de Zuelandia. Para
    la distribución del cemento entre tus diferentes clientes (ciudades de Zuelandia)
    dispones de una flota de camiones y de una plantilla de conductores zuelandeses.
    El problema a resolver tiene que ver con el carácter del zuelandés. El zuelandés es
    una persona que se toma demasiadas “libertades” en su trabajo, de hecho, tienes
    fundadas sospechas de que tus conductores utilizan los camiones de la empresa para
    usos particulares (es decir indebidos, y a tu costa) por lo que quieres controlar los
    kilómetros que recorren tus camiones.

    Todos los días se genera el parte de trabajo, en el que se incluyen el número de
    cargas de cemento (1 carga = 1 camión lleno de cemento) que debes enviar a cada
    cliente (cliente = ciudad de Zuelandia). Es innecesario indicar que no todos los días hay
    que enviar cargas a todos los clientes, y además, puedes suponer razonablemente que tu
    flota de camiones es capaz de hacer el trabajo diario.
    Para la resolución del problema quizá sea interesante recordar que Zuelandia es un
    país cuya especial orografía sólo permite que las carreteras tengan un sentido de circulación.
    Implementa una función que dado el grafo con las distancias directas entre las
    diferentes ciudades zuelandesas, el parte de trabajo diario, y la capital de Zuelandia,
    devuelva la distancia total en kilómetros que deben recorrer tus camiones en el día, para
    que puedas descubrir si es cierto o no que usan tus camiones en actividades ajenas a la empresa.
*/

#include "../alg_grafo_E-S.h"
#include "../alg_grafoPMC.h" //Dijkstra
#include <iostream>
using namespace std;

template <typename tCoste> tCoste distanciaCamiones(const GrafoP<tCoste>& G, const typename GrafoP<tCoste>::vertice capital, const vector<tCoste>& vectorTcosteCarga);

int main()
{
    GrafoP<GrafoP<int>::tCoste> G ("matriz7.04.txt");
    vector<GrafoP<int>::tCoste> partes = {0, 6, 2, 4, 2};
    cout << "Kilometros totales a recorrer por los camiones: " << distanciaCamiones<GrafoP<int>::tCoste>(G, 0, partes) << " Km" << endl;
}

template <typename tCoste> tCoste distanciaCamiones(const GrafoP<tCoste>& G, const typename GrafoP<tCoste>::vertice capital, const vector<tCoste>& vectorTcosteCarga)
{
    typedef typename GrafoP<tCoste>::vertice vertice;

    tCoste coste = 0;
    vector<vertice> vectorVerticesIda,vectorVerticesVuelta;
    vector<tCoste> vectorTcosteIda = Dijkstra(G, capital, vectorVerticesIda), vectorTcosteVuelta = DijkstraInv(G, capital, vectorVerticesVuelta);

    for(vertice iii=0; iii<vectorTcosteCarga.size(); ++iii)
        if(iii!=capital) coste += vectorTcosteCarga[iii]*(vectorTcosteIda[iii] + vectorTcosteVuelta[iii]);

    return coste;
}
