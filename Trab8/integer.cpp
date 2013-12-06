/*
 * integer.cpp
 *
 *  Created on: Nov 29, 2013
 *      Author: mateus
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


int main( int argc, char* argv[] ) {
  Integer a = 798747327497297389275473298748937584695475873_ai;
  Integer b = 798747327497297389275473298748937584695475873_ai;
  Integer c = 2_ai;

  cout << "Soma:" << endl;
  cout << a + b << endl << endl;

  cout << "Subtração:" << endl;
  cout << a - b << endl << endl;

  cout << "Multiplicação:" << endl;
  cout << a * c << endl << endl;

  cout << "Divisão:" << endl;
  cout << (a * 4_ai) / c << endl << endl;


  return 0;
}