#include <iostream>
#include <map>

using namespace std;

class Variavel;

class Polinomio {
public:
  Polinomio( int n ) {
    termo[ 0 ] = n;
  }

  Polinomio( const Variavel& x, int n = 1 ) {
    termo[ n ] = 1;
  }

  // equivalente a x^n
  Polinomio operator()( int n ) const;

  Polinomio soma( const Polinomio& b ) const;

  ostream& print( ostream& ) const;


private:
  map< int, int > termo;
};

class Variavel {
public:
  Polinomio operator()( int n ) {
    return Polinomio( *this, n );
  }
};

Variavel x;

Polinomio operator + ( const Polinomio& a, const Polinomio& b ) {
  return a.soma( b );
}

Polinomio operator - ( const Polinomio& a, const Polinomio& b );
Polinomio operator * ( const Polinomio& a, const Polinomio& b );
Polinomio power( const Polinomio& a, int n ) {
  return a( n );
}


int main( int argc, char* argv[])
{
  Polinomio a, b;

  a = x(2) + x(3);
  b = x + 2*x(3);

  cout << a + b << endl;


  return 0;
}