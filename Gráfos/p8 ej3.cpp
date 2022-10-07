/*
    3. Implementa un subprograma para encontrar un árbol de extensión máximo. ¿Es más
    difícil que encontrar un árbol de extensión mínimo?
*/
////Nota-->Ya está definido en "alg_grafoPMC.h", de ahí que esté comentado

/**
template <typename tCoste> GrafoP<tCoste> PrimMaximo(const GrafoP<tCoste>& G)
{
    const size_t n = G.numVert();
    GrafoP<tCoste> g(n); 			// Árbol generador de coste mínimo.
    vector<bool> U(n, false); 			// Conjunto de vértices incluidos en g.
    Apo<aristaP<tCoste> > A(n*(n-1)/2-n+2); 	// Aristas adyacentes a g ordenadas por costes.
    U[0] = true;

    for (vertice v = 1; v < n; v++) 		// Introducir en el APO las aristas adyacentes al primer vértice.
        if (G[0][v] < GrafoP<tCoste>::INFINITO)
            A.insertar(aristaP<tCoste>(0, v, -1*G[0][v]));

    for (int i = 0; i < n-1; i++) {	// Seleccionar n-1 aristas.
        // Buscar una arista a de coste mínimo que no forme un ciclo.
        aristaP<tCoste> a;
        do {
            a = A.cima();
            A.suprimir();
        }while (U[a.orig] && U[a.dest]);

        // Incluir la arista a en el árbol g y el nuevo vértice en U.
        g[a.orig][a.dest] = g[a.dest][a.orig] = a.coste*-1;
        vertice u = U[a.orig] ? a.dest : a.orig;
        U[u] = true;

        // Introducir en el APO las aristas adyacentes al vértice u que no formen ciclos.
        for (vertice v = 0; v < n; v++)
            if (!U[v] && G[u][v] < GrafoP<tCoste>::INFINITO)
                A.insertar(aristaP<tCoste>(u, v, -1*G[u][v]));
    }

    return g;
}
*/
