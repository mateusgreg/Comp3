/*
 * rational.cpp
 *
 *  Created on: Nov 04, 2013
 *      Author: mateus
 *
 *  Descrição: Implementação de classe que encapsula as principais funções da biblioteca GMP
 *  utilizadas para manipulação de números inteiros e racionais de tamanho arbitrário.
 */

#include <iostream>
#include <gmpxx.h>

using namespace std;

class Integer {
public:
  Integer( string st ): st(st) {}
  Integer(): st("0") {}

  string _st() {
    return st;
  }

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

  bool operator!= ( Integer x ) {
    return st != x.st;
  }

  Integer mmc(Integer x) {
    mpz_t a, b, c;

    mpz_init( a );
    mpz_init_set_str( b, st.c_str(), 10 );
    mpz_init_set_str( c, x.st.c_str(), 10 );

    mpz_lcm( a, b, c );

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

Integer power ( Integer& a, unsigned long int x ) {
  return a.power(x);
}

Integer mmc(Integer a, Integer b) {
  return a.mmc(b);
}




class Rational {
public:
  Rational( Integer num, Integer den = 1_ai ) {
    numerador = num;

    if (den != 0_ai)
      denominador = den;
    else
      denominador = 1_ai;
  }

  Rational() {
    numerador = 0_ai;
    denominador = 1_ai;
  }

  ostream& print( ostream& o ) const {
    return o << numerador << " / " << denominador;
  } 

  Rational operator+ ( Rational x ) {
    Rational result;

    result.denominador = mmc(denominador, x.denominador);
    result.numerador = numerador*(result.denominador/denominador) + x.numerador*(result.denominador/x.denominador);

    return result;
  }

  Rational operator- ( Rational x ) {
    Rational result;

    result.denominador = mmc(denominador, x.denominador);
    result.numerador = numerador*(result.denominador/denominador) - x.numerador*(result.denominador/x.denominador);

    return result;
  }

private:
  Integer numerador;
  Integer denominador;
};

ostream& operator << ( ostream& o, const Rational r ) {
  return r.print( o );
}


int main( int argc, char* argv[] ) {
  //Integer a = 798747327497297389275473298748937584695475874_ai;
  Integer a = 30_ai;
  Integer b = 18_ai;
  Integer c = 2_ai;

  Rational r1(a, b);
  Rational r2(a, c);

  cout << "Racionais:" << endl;
  cout << r1 << endl;
  cout << r2 << endl << endl;

  cout << "Soma:" << endl;
  cout << r1 + r2 << endl << endl;

  cout << "Subtracao:" << endl;
  cout << r1 - r2 << endl << endl;


  return 0;
}