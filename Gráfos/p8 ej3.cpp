/*
    3. Implementa un subprograma para encontrar un �rbol de extensi�n m�ximo. �Es m�s
    dif�cil que encontrar un �rbol de extensi�n m�nimo?
*/
////Nota-->Ya est� definido en "alg_grafoPMC.h", de ah� que est� comentado

/**
template <typename tCoste> GrafoP<tCoste> PrimMaximo(const GrafoP<tCoste>& G)
{
    const size_t n = G.numVert();
    GrafoP<tCoste> g(n); 			// �rbol generador de coste m�nimo.
    vector<bool> U(n, false); 			// Conjunto de v�rtices incluidos en g.
    Apo<aristaP<tCoste> > A(n*(n-1)/2-n+2); 	// Aristas adyacentes a g ordenadas por costes.
    U[0] = true;

    for (vertice v = 1; v < n; v++) 		// Introducir en el APO las aristas adyacentes al primer v�rtice.
        if (G[0][v] < GrafoP<tCoste>::INFINITO)
            A.insertar(aristaP<tCoste>(0, v, -1*G[0][v]));

    for (int i = 0; i < n-1; i++) {	// Seleccionar n-1 aristas.
        // Buscar una arista a de coste m�nimo que no forme un ciclo.
        aristaP<tCoste> a;
        do {
            a = A.cima();
            A.suprimir();
        }while (U[a.orig] && U[a.dest]);

        // Incluir la arista a en el �rbol g y el nuevo v�rtice en U.
        g[a.orig][a.dest] = g[a.dest][a.orig] = a.coste*-1;
        vertice u = U[a.orig] ? a.dest : a.orig;
        U[u] = true;

        // Introducir en el APO las aristas adyacentes al v�rtice u que no formen ciclos.
        for (vertice v = 0; v < n; v++)
            if (!U[v] && G[u][v] < GrafoP<tCoste>::INFINITO)
                A.insertar(aristaP<tCoste>(u, v, -1*G[u][v]));
    }

    return g;
}
*/
