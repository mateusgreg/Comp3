/*
 * main.cpp
 *
 *  Created on: Sep 5, 2013
 *      Author: mateus
 */

#include <iostream>
using namespace std;

#include "Pilha.h"

// Exemplo de template
template <class T>
inline T maximo( T a, T b ) {
  return a > b ? a : b;
}

// Protótipo padrão para o operador '<<' para imprimir
template <class T>
ostream& operator << ( ostream& o, const Pilha<T>& p ) {
  p.print( o );
  return o;
}

int main( int argc, char* argv[])
{
  Pilha<string> a, b;
  Pilha< Pilha<string> > c;

  a << "1" << "2" << "27";
  b << "3" << "12" << "8" << "32";
  c << a << b;

  cout << a << endl;

  if( a > b )
    cout << "a" << endl;
  else
    cout << "b" << endl;

  cout << maximo( a, b ) << endl;

  cout << c << endl;

  return 0;
}
