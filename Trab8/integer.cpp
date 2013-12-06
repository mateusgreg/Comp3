/*
 * integer.cpp
 *
 *  Created on: Nov 29, 2013
 *      Author: mateus
 *
 *  Descrição: Implementação de classe que encapsula as principais funções da biblioteca GMP
 *  utilizadas para manipulação de números inteiros de tamanho arbitrário.
 */

#include <iostream>
#include <gmpxx.h>

using namespace std;

class Integer {
public:
  Integer( string st ): st(st) {}

  ostream& print( ostream& o ) const {
    return o << st;
  }

  Integer operator+ ( Integer x ) {
    mpz_t a, b, c;

    mpz_init( a );
    mpz_init_set_str( b, st.c_str(), 10 );
    mpz_init_set_str( c, x.st.c_str(), 10 );

    mpz_add( a, b, c );

    return Integer( mpz_get_str(NULL, 10, a) );
  }

  Integer operator- ( Integer x ) {
    mpz_t a, b, c;

    mpz_init( a );
    mpz_init_set_str( b, st.c_str(), 10 );
    mpz_init_set_str( c, x.st.c_str(), 10 );

    mpz_sub( a, b, c );

    return Integer( mpz_get_str(NULL, 10, a) );
  }

  Integer operator* ( Integer x ) {
    mpz_t a, b, c;

    mpz_init( a );
    mpz_init_set_str( b, st.c_str(), 10 );
    mpz_init_set_str( c, x.st.c_str(), 10 );

    mpz_mul( a, b, c );

    return Integer( mpz_get_str(NULL, 10, a) );
  }

  Integer operator/ ( Integer x ) {
    mpz_t a, b, c;

    mpz_init( a );
    mpz_init_set_str( b, st.c_str(), 10 );
    mpz_init_set_str( c, x.st.c_str(), 10 );

    mpz_div( a, b, c );

    return Integer( mpz_get_str(NULL, 10, a) );
  }

  Integer operator% ( Integer x ) {
    mpz_t a, b, c;

    mpz_init( a );
    mpz_init_set_str( b, st.c_str(), 10 );
    mpz_init_set_str( c, x.st.c_str(), 10 );

    mpz_mod( a, b, c );

    return Integer( mpz_get_str(NULL, 10, a) );
  }

  Integer power ( unsigned long int x ) {
    mpz_t a, base;

    mpz_init( a );
    mpz_init_set_str( base, st.c_str(), 10 );

    mpz_pow_ui( a, base, x );

    return Integer( mpz_get_str(NULL, 10, a) );
  }

  Integer operator() ( unsigned long int x ) {
    return power(x);
  }

private:
  string st;
};


ostream& operator << ( ostream& o, const Integer i ) {
  return i.print( o );
}


// operator user-defined literal
Integer operator"" _ai( const char* st ) {
  return Integer( st );
}

Integer power ( Integer& a, unsigned long int x ) {
  return a.power(x);
}


int main( int argc, char* argv[] ) {
  Integer a = 798747327497297389275473298748937584695475873_ai;
  Integer b = 898747327497297389275473298748937584695475873_ai;
  Integer c = 2_ai;

  cout << "Soma:" << endl;
  cout << a + b << endl << endl;

  cout << "Subtracao:" << endl;
  cout << a - b << endl << endl;

  cout << "Multiplicacao:" << endl;
  cout << a * c << endl << endl;

  cout << "Divisao:" << endl;
  cout << (a * 4_ai) / c << endl << endl;

  cout << "Modulo da Divisao:" << endl;
  cout << a % c << endl << endl;

  cout << "Exponenciacao (metodo):" << endl;
  cout << a.power(12345) << endl << endl;

  cout << "Exponenciacao (funcao):" << endl;
  cout << power(b, 3) << endl << endl;

  cout << "Exponenciacao (operador):" << endl;
  cout << a(12345) << endl << endl;


  return 0;
}