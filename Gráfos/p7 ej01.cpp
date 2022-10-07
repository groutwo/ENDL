/*
    1. Tu agencia de viajes “OTRAVEZUNGRAFO S.A.” se enfrenta a un curioso cliente.
    Es un personaje sorprendente, no le importa el dinero y quiere hacer el viaje más caro
    posible entre las ciudades que ofertas. Su objetivo es gastarse la mayor cantidad de
    dinero posible (ojalá todos los clientes fueran así), no le importa el origen ni el destino
    del viaje.
    Sabiendo que es imposible pasar dos veces por la misma ciudad, ya que casualmente
    el grafo de tu agencia de viajes resultó ser acíclico, devolver el coste, origen y destino
    de tan curioso viaje. Se parte de la matriz de costes directos entre las ciudades del grafo.
*/
/**
    Maximizador inteligente:
    if( A != INFINITO and B != INFINITO) return max(A,B);
    else if (A == INFINITO) return B;
    else if (B == INFINITO) return A;

    ó

    return (cond1? sol1:(cond2?sol2:sol3);
**/
#include "../alg_grafo_E-S.h"
///#include "../alg_grafoPMC.h" //Floyd -> ya no, pero si para suma
#include "../alg_grafoMA.h" //Warshall
#include <iostream>
using namespace std;

template <typename tCoste> bool viajeCaro(const GrafoP<tCoste>& GrafoCostes,
    typename GrafoP<tCoste>::vertice& origen,typename GrafoP<tCoste>::vertice& destino,
    tCoste& coste);

int main()
{
    GrafoP<int> GGG ("matriz7.01.txt");
    Grafo::vertice origen=0, destino=0;
    GrafoP<int>::tCoste coste;
    if(viajeCaro(GGG,origen,destino,coste))
        cout<<"El viaje mas caro va desde "<<origen<<" hasta "
            <<destino<<" con un coste de "<<coste<<endl;
    else
        cout<<"Como el mapa/el grafo es ciclico, no se puede dar el viaje"<<endl;
    return 0;

}

template <typename tCoste> bool viajeCaro(const GrafoP<tCoste>& GrafoCostes,
    typename GrafoP<tCoste>::vertice& origen,typename GrafoP<tCoste>::vertice& destino,
    tCoste& coste)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    if(tieneCiclos(GrafoCostes))
        return false;
    coste = 0;

    matriz<typename GrafoP<tCoste>::vertice> matrizVertices(GrafoCostes.numVert());
    matriz<tCoste> matriztCostes(GrafoCostes.numVert());
    matriztCostes = Floyd_Maximizador(GrafoCostes, matrizVertices);

    cout<<"Matriz de costes despues de Floyd_Maximizador"<<endl;
    cout<<matriztCostes<<endl;

    for(vertice iii = 0; iii<=GrafoCostes.numVert()-1; iii++)
        for(vertice jjj = 0; jjj<=GrafoCostes.numVert()-1; jjj++)
            if(matriztCostes[iii][jjj] > coste && matriztCostes[iii][jjj] != GrafoP<tCoste>::INFINITO)
                coste = matriztCostes[iii][jjj], origen = iii, destino = jjj;
    return true;
}

template <typename tCoste> bool tieneCiclos(const GrafoP<tCoste>& GrafoCostes)
{
    bool ciclo = false;
    Grafo GrafoAux(GrafoCostes.numVert());

    for(int ii2=0; ii2 < GrafoCostes.numVert(); ii2++)
        for(int jj2=0; jj2 < GrafoCostes.numVert(); jj2++)
                GrafoAux[ii2][jj2] = (GrafoCostes[ii2][jj2] != GrafoP<tCoste>::INFINITO);

    matriz<bool> matrizBools = Warshall(GrafoAux);

    for(int ii3=0; ii3 < matrizBools.dimension() && !ciclo; ii3++)
        if(matrizBools[ii3][ii3])
            ciclo = true;

    return ciclo;
}

template <typename tCoste> tCoste suma(tCoste x, tCoste y)
{ const tCoste INFINITO = GrafoP<tCoste>::INFINITO;
   if (x == INFINITO || y == INFINITO) return INFINITO;
   else return x + y;
}

// Algoritmo de Floyd Modificado para que maximice los costes entre cualesquiera
    // 2 puntos del grafo, en vez de minimizarlo,...
template <typename tCoste>
matriz<tCoste> Floyd_Maximizador(const GrafoP<tCoste>& GrafoCostes,
            matriz<typename GrafoP<tCoste>::vertice>& matrizVertices)
{
    typedef typename GrafoP<tCoste>::vertice mi_vertice;
	matriz<tCoste> matrizCostes(GrafoCostes.numVert());
	matrizVertices = matriz <mi_vertice>(GrafoCostes.numVert());
    tCoste abc;

	for (mi_vertice ii4 = 0; ii4 < GrafoCostes.numVert(); ii4++)
		matrizCostes[ii4] = GrafoCostes[ii4],                    // copia costes del grafo
		matrizCostes[ii4][ii4] = 0,                                 // diagonal a 0
		matrizVertices[ii4] = vector<mi_vertice>(GrafoCostes.numVert(), ii4);   // caminos directos

	// Calcular costes máximos y caminos correspondientes
	// entre cualquier par de vértices i, j
	//k->bbb; i->aaa; j->ccc
	for (mi_vertice bbb = 0; bbb < GrafoCostes.numVert(); bbb++)
		for (mi_vertice aaa = 0; aaa < GrafoCostes.numVert(); aaa++)
			for (mi_vertice ccc = 0; ccc < GrafoCostes.numVert(); ccc++)
				if  ( (abc = suma(matrizCostes[aaa][bbb], matrizCostes[bbb][ccc])) != GrafoP<tCoste>::INFINITO and
                            ///Diferencia con el Floyd normal, seria "abc < matrizCostes[a][c]"
                        ( (abc > matrizCostes[aaa][ccc])  or  (matrizCostes[aaa][ccc] ==  GrafoP<tCoste>::INFINITO) )
                    )
					matrizCostes[aaa][ccc] = abc, matrizVertices[aaa][ccc] = bbb;

	return matrizCostes;
}

