/*
    6. La empresa EMASAJER S.A. tiene que unir mediante canales todas las ciudades del
    valle del Jerte (C�ceres), teniendo en cuenta las siguientes premisas:
        - El coste de abrir cada nuevo canal es casi prohibitivo, luego la soluci�n final debe
    tener un n�mero m�nimo de canales.
        - El Ministerio de Fomento nos subvenciona por m3/sg de caudal, luego el conjunto
        de los canales debe admitir el mayor caudal posible, pero por otra parte, el coste
        de abrir cada canal es proporcional a su longitud, por lo que el conjunto de los
        canales tambi�n deber�a medir lo menos posible. As� pues, la soluci�n �ptima
        deber�a combinar adecuadamente ambos factores.
    Dada la matriz de distancias entre las diferentes ciudades del valle del Jerte, otra
    matriz con los diferentes caudales m�ximos admisibles entre estas ciudades teniendo en
    cuenta su orograf�a, la subvenci�n que nos da Fomento por m3/sg. de caudal y el coste
    por km. de canal, implementen un subprograma que calcule qu� canales y de qu�
    longitud y caudal deben construirse para minimizar el coste total de la red de canales.
*/

#include "../alg_grafo_E-S.h"
#include "../alg_grafoPMC.h"//PrimMaximo//del ejercicio anterior
#include <iostream>

using namespace std;

template <typename tCoste> GrafoP<tCoste> emasajer2(GrafoP<tCoste>& distancias,
    GrafoP<tCoste>& caudales, tCoste subvencion, tCoste km);

int main()
{
    GrafoP<int> distancias ("matriz8.6distancias.txt");
    GrafoP<int> caudales ("matriz8.6caudales.txt");
    int subvencion = 5,costePorKm = 100;
    GrafoP<int> resultado = emasajer2(distancias, caudales, subvencion, costePorKm);

    cout << "Los canales a construir son" << endl;
    cout << "CANAL\tLONGITUD\tCAUDAL" << endl;
    for(int i=0; i< resultado.numVert(); ++i)
        for(int j=i; j<resultado.numVert(); ++j)
            if(resultado[i][j] != GrafoP<int>::INFINITO)
                cout << i << "-" << j << "\t" << distancias[i][j] << " Km\t\t" << caudales[i][j] << " m3/sg" << endl;
    return 0;
}

template <typename tCoste> GrafoP<tCoste> emasajer2(GrafoP<tCoste>& distancias,
    GrafoP<tCoste>& caudales, tCoste subvencion, tCoste km)
{
    GrafoP<tCoste> grafoCoste(distancias.numVert());

    for(int i=0; i<distancias.numVert(); ++i)
        for(int j=0; j<distancias.numVert(); ++j)
            grafoCoste[i][j] = distancias[i][j] * km - caudales[i][j] * subvencion;
    return Prim(grafoCoste);
}
