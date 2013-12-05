/*
 * main.cpp
 *
 *  Created on: Oct 11, 2013
 *      Author: mateus
 */

#include <iostream>
using namespace std;

#include "Matriz.h"

// Exemplo de template
template <class T>
inline T maximo( T a, T b ) {
  return a > b ? a : b;
}

// Protótipo padrão para o operador '<<' para imprimir
template <class T>
ostream& operator<< ( ostream& o, const Matriz<T>& m ) {
  m.print( o );
  return o;
}

int main( int argc, char* argv[])
{
	Matriz<double> a( 10, 10 ), b( 10, 5 ), c, d, e;

	a[0][1] = 5.3;
	c[1][0] = 2;
	d = a+c;
	cout << endl << "SOMA:\n" << d << endl;

	b[1][1] = 2;
	d = a*b;
	cout << endl << "MULTIPLICAÇÃO:\n" << d << endl;

	return 0;
}
