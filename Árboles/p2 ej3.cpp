/*
    3. El TAD árbol binario puede albergar expresiones matemáticas mediante un árbol de
    expresión. Dentro del árbol binario los nodos hojas contendrán los operandos, y el resto
    de los nodos los operadores.

        a) Define el tipo de los elementos del árbol para que los nodos puedan almacenar
    operadores y operandos.

        b) Implementa una función que tome un árbol binario de expresión (aritmética) y
    devuelva el resultado de la misma. Por simplificar el problema se puede asumir que el
    árbol representa una expresión correcta. Los operadores binarios posibles en la
    expresión aritmética serán suma, resta, multiplicación y división.

    Nota: En el programa de prueba podemos usar las funciones rellenarAbin() de abin_ES.
    h para introducir por teclado o desde un fichero el árbol de expresión a evaluar. Sin
    embargo, en este caso, será necesario sobrecargar los operadores utilizados internamente
    en dichas funciones, es decir >>, << y != para el tipo de los elementos del árbol.
*/

#include "01 abin.hpp"
#include "0 abin_E-S.hpp"

using namespace std;

struct operacion
{
    char operador;
    float operando;
    operacion(char c='_',float f=0):operador{c},operando{f} {}
};

template <typename T> float evaluarRec(typename Abin<T>::nodo n,const Abin<T>& A )
{
    if(A.hijoIzqdoB(A.elemento(n) == Abin<T>::NODO_NULO)
        return A.elemento(n).operando;
    else
    {
        switch(A.elemento(n).operador)
        {
        case '+':
            return evaluarRec(A.hijoIzqdoB(n), A) + evaluarRec(A.hijoDrchoB(n), A);
            break;
        case '-':
            return evaluarRec(A.hijoIzqdoB(n), A) - evaluarRec(A.hijoDrchoB(n), A);
            break;
        case '*':
            return evaluarRec(A.hijoIzqdoB(n), A) * evaluarRec(A.hijoDrchoB(n), A);
            break;
        case '/':
            return evaluarRec(A.hijoIzqdoB(n), A) / evaluarRec(A.hijoDrchoB(n), A);
            break;
        default:
            cout<<"Nada";
        }
    }
    return 0;
}

template <typename T> float evaluar(const Abin<T>& A)
{
    if( !A.arbolVacioB())
        return evaluarRec( A.raizB(), A);
    else
        return 0;
}

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    Abin<operacion> arbol;
    rellenarAbin(arbol, operacion());

    float resultado = evaluar(arbol);
    cout<<"El resultado es: "<<resultado<<endl;

    return 0;
}

istream& operator >> (istream& is, const operacion op)
{
    cout<<endl;
    int numero;
    cout<<"Pulsa 1 si quieres introducir un numero: ";
    cin>>numero;
    if(numero == 1)
    {
        cout<<"Numero a introducir";
        is>>op.operando;
    }
    else
    {
        cout<<"Introduce la operacion a realizar ";
        is>>op.operador;
    }
    return is;
}

bool operator != (operacion& op1,const operacion& op2)
{
    return op1.operando!=op2.operando && op1.operador!=op2.operador;
}


ostream& operator << (ostream& os, const operacion op)
{
    os<<"El operando es "<<op.operando<<" y el operador es "<<op.operador;
    return os;
}
