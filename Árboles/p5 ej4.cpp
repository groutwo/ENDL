/*Implementa un subprograma que dado un árbol ternario (grado 3) devuelva una copia
del mismo. La representación de árboles debe ser una estructura de datos enlazada con
puntero al padre*/
#include <iostream>
#include "08 Ater.hpp"
#include "08 Ater_E-S.hpp"
/*
q a b q q q c e g q q q h q m q q q q i q q q q f j q q q k q n q q q q l q q q d q q q
*/
int main()
{
    char nodoNulo;
    std::cout << "Define elemento NULO para arbol: ";
    std::cin >> nodoNulo;

    Ater<char> A = leerAter(nodoNulo);

    imprimirAter(A);
}
