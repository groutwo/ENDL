/*
    5. La nueva compa��a de telefon�a RETEUNI3 tiene que conectar entre s�, con fibra
    �ptica, todas y cada una de las ciudades del pa�s. Partiendo del grafo que representa las
    distancias entre todas las ciudades del mismo, implementad un subprograma que
    calcule la longitud m�nima de fibra �ptica necesaria para realizar dicha conexi�n.
*/

#include "../alg_grafo_E-S.h"
#include "../alg_grafoPMC.h"//PrimMaximo//del ejercicio anterior
#include <iostream>

using namespace std;

template <typename tCoste> tCoste reteuni3(const GrafoP<tCoste>& G);

int main()
{
    GrafoP<int> G ("matriz8.5.txt");
    cout << "Km minimos de fibra optica para conectar todas las provincias andaluzas es " << reteuni3(G);
    return 0;
}

template <typename tCoste> tCoste reteuni3(const GrafoP<tCoste>& GGG)
{
    GrafoP<tCoste> grafoCoste = Prim(GGG);
    tCoste sum = 0;

    cout << grafoCoste;

    for(int i=0; i< grafoCoste.numVert(); ++i)
        for(int j=0; j<grafoCoste.numVert(); ++j)
            if(GGG[i][j] != GrafoP<tCoste>::INFINITO)
                sum += grafoCoste[i][j];
    return sum/2;
}
