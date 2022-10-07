/*
    5. Escribir una función genérica que implemente el algoritmo de Dijkstra usando un
    grafo ponderado representado mediante listas de adyacencia.
*/


#include "../alg_grafoPMC.h" //Dij


template <typename tCoste>vector<tCoste> Dijkstra2(const GrafoP<tCoste>& GrafoCostes,
    typename GrafoP<tCoste>::vertice VerticeOrigen,vector<typename GrafoP<tCoste>::vertice>& vectorVertices)
/*
    Calcula los caminos de coste mínimo entre origen y todos los
    vértices del grafo G. En el vector D de tamaño G.numVert()
    devuelve estos costes mínimos y P es un vector de tamaño
    G.numVert() tal que P[i] es el último vértice del camino de origen a i.
*/
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    vertice verticeV, verticeW;

    vector<bool> vectorBool(GrafoCostes.numVert(), false); // Conjunto de vértices vacío.
    vectorBool[VerticeOrigen] = true;            // Incluir vértice origen en vectorBool.

    typedef typename GrafoP<tCoste>::vertice_coste vC_;
    vC_ verticeCoste;

    vector<tCoste> vectorCostes(GrafoCostes.numVert(), GrafoP<tCoste>::INFINITO); // inicializamos los coste minimos a infinito.
    vectorVertices = vector<vertice>(GrafoCostes.numVert(), VerticeOrigen);
    // Iniciar vectorCostes y vectorVertices con caminos directos desde el vértice origen.

    typename Lista<vC_>::posicion pos;

    for (   pos = GrafoCostes.adyacentes(VerticeOrigen).primera();
            pos != GrafoCostes.adyacentes(VerticeOrigen).fin();
            pos = GrafoCostes.adyacentes(VerticeOrigen).siguiente(pos)
        )
            vectorCostes[GrafoCostes.adyacentes(VerticeOrigen).elemento(pos).v] = GrafoCostes.adyacentes(VerticeOrigen).elemento(pos).c;

    vectorCostes[VerticeOrigen] = 0;                              // Coste origen-origen es 0.

    // Calcular caminos de coste mínimo hasta cada vértice.
    for (size_t iii = 1; iii <= GrafoCostes.numVert()-2; iii++)
    {
        // Seleccionar vértice w no incluido en vectorBool con menor coste desde origen.
        tCoste costeMin = GrafoP<tCoste>::INFINITO;

        for (verticeV = 0; verticeV < GrafoCostes.numVert(); verticeV++)
            if (!vectorBool[verticeV] && vectorCostes[verticeV] <= costeMin)
                costeMin = vectorCostes[verticeV], verticeW = verticeV;

        vectorBool[verticeW] = true;        // Incluir vértice w en vectorBool.
        // Recalcular coste hasta cada v no incluido en vectorBool a través de w.
        for (verticeV = 0; verticeV < GrafoCostes.numVert(); verticeV++)
            if (!vectorBool[verticeV])
            {
                tCoste Owv;/*Como no es un tipo básico, no se puede declarar en el if (?)*/
                verticeCoste.v = vectorVertices;
                if(
                        (   pos = GrafoCostes.adyacentes(verticeW).buscar(verticeCoste) != GrafoCostes.adyacentes(verticeW).fin()   )
                            &&
                        (   vectorCostes[verticeV] > ( /*tCoste*/ Owv = suma(vectorCostes[verticeW], GrafoCostes.adyacentes(verticeW).elemento(pos).c ))  )
                  )
                    vectorCostes[verticeV] = Owv, vectorVertices[verticeV] = verticeW;
            }
    }
    return vectorCostes;
}

int main()
{
    //No está probado a1 l00%
    return 0;
}
