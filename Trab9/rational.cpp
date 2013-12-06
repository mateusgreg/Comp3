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
#include <math.h>

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

  Integer mdc(Integer x) {
    mpz_t a, b, c;

    mpz_init( a );
    mpz_init_set_str( b, st.c_str(), 10 );
    mpz_init_set_str( c, x.st.c_str(), 10 );

    mpz_gcd( a, b, c );

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

Integer mdc(Integer a, Integer b) {
  return a.mdc(b);
}




class Rational {
public:
  Rational( Integer num, Integer den = 1_ai ) {
    numerador = num;

    if (den != 0_ai)
      denominador = den;
    else
      denominador = 1_ai;

    simplifica();
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

    return result.simplifica();
  }

  Rational operator- ( Rational x ) {
    Rational result;

    result.denominador = mmc(denominador, x.denominador);
    result.numerador = numerador*(result.denominador/denominador) - x.numerador*(result.denominador/x.denominador);

    return result.simplifica();
  }

  Rational operator* ( Rational x ) {
    Rational result;

    result.numerador = numerador * x.numerador;
    result.denominador = denominador * x.denominador;

    return result.simplifica();
  }

  Rational operator/ ( Rational x ) {
    Rational result;

    result.numerador = numerador * x.denominador;
    result.denominador = denominador * x.numerador;

    return result.simplifica();
  }

  Rational power ( long int x ) {
    Rational result;

    if (x < 0) {
      result.numerador = denominador.power(abs(x));
      result.denominador = numerador.power(abs(x));
    } else {
      result.numerador = numerador.power(x);
      result.denominador = denominador.power(x);
    }

    return result.simplifica();
  }

  Rational operator() ( long int x ) {
    return power(x);
  }

private:
  Integer numerador;
  Integer denominador;

  Rational simplifica() {
    Integer fator = mdc(numerador, denominador);

    numerador = numerador/fator;
    denominador = denominador/fator;

    return *this;
  }
};

ostream& operator << ( ostream& o, const Rational r ) {
  return r.print( o );
}

Rational power ( Rational& r, long int x ) {
  return r.power(x);
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

  cout << "Multiplicacao:" << endl;
  cout << r1 * r2 << endl << endl;

  cout << "Divisao:" << endl;
  cout << r1 / r2 << endl << endl;

  cout << "Exponenciacao (operador):" << endl;
  cout << r1(-2) << endl << endl;

  cout << "Exponenciacao (metodo):" << endl;
  cout << r1.power(-2) << endl << endl;

  cout << "Exponenciacao (funcao):" << endl;
  cout << power(r1, -2) << endl << endl;


  return 0;
}