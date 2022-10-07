#include <iostream>
#include <fstream>
#include "01 abin.hpp"
#include "0 abin_E-S.hpp"

using namespace std;

typedef char tElto;
const tElto fin = '#'; // fin de lectura
int main ()
{
    setlocale(LC_CTYPE, "Spanish");
    Abin<tElto> A, B;
    cout << "*** Lectura del árbol binario A ***\n";
    rellenarAbin(A, fin); // desde std::cin
    ofstream fs("abin.txt"); // abrir fichero de salida
    imprimirAbin(fs, A, fin); // en fichero
    fs.close();
    cout << "\n*** Árbol A guardado en fichero abin.txt ***\n";
    cout << "\n*** Lectura de árbol binario B de abin.txt ***\n";
    ifstream fe("abin.txt"); // abrir fichero de entrada
    rellenarAbin(fe, B); // desde fichero
    fe.close();
    cout << "\n*** Mostrar árbol binario B ***\n";
    imprimirAbin(B); // en std::cout

    system("pause");
    return 0;
}
