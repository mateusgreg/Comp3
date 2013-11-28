#include <iostream>

using namespace std;

class Tabela {
public:
  Tabela( string st ): st(st) {}
  ostream& print( ostream& o ) const {
    return o << st;
  }

  Tabela operator + ( Tabela t ) {
    return Tabela( st + ", " + t.st );
  }
private:
  string st;
};

ostream& operator << ( ostream& o, const Tabela& t ) {
  return t.print( o );
}

class Campo {
public:
  Campo( string st ): st(st) {}
  ostream& print( ostream& o ) const {
    return o << st;
  }

  Campo operator + ( Campo c ) {
    return Campo( st + ", " + c.st );
  }

  Campo operator == ( Campo c ) {
    return Campo( st + " == " + c.st );
  }
private:
  string st;
};

ostream& operator << ( ostream& o, const Campo& c ) {
  return c.print( o );
}

Campo id{ "id" };
Campo nome{ "nome" };
Campo matricula{ "matricula" };
Campo endereco{ "endereco" };
Campo turma_id{ "turma_id" };

class Aluno: public Tabela {
public:
  Aluno( string st ): Tabela( st ) {}

  Campo id{ "aluno.id" };
  Campo nome{ "aluno.nome" };
  Campo matricula{ "aluno.matricula" };
  Campo endereco{ "aluno.endereco" };
  Campo turma_id{ "aluno.turma_id" };
} aluno{ "aluno" };

class Turma: public Tabela {
public:
  Turma( string st ): Tabela( st ) {}

  Campo id{ "turma.id" };
} turma{ "turma" };


class SQL3 {
};

class SQL2 {
public:
  SQL3 where( Campo c ) {
    cout << " where " << c;
  }
};

class SQL1 {
public:
  SQL2 from( Tabela tab ) {
    cout << "from " << tab;
    return SQL2();
  }

  template <class... T>
  SQL2 from( Tabela exprA, Tabela exprB, T... resto ) {
    return from( exprA + exprB, resto... );
  }

};

SQL1 select( Campo c ) {
  cout << "select " << c << " ";

  return SQL1();
}

template <class... T>
SQL1 select( Campo exprA, Campo exprB, T... resto ) {
  return select( exprA + exprB, resto... );
}

void operator<<( SQL1 f, Tabela st ) {
  f.from( st );
}

#define SELECT select(
#define FROM   ).from(
#define WHERE  ).where(
#define ENDL   ); cout << endl

int main( int argc, char* argv[] ) {

  select( nome, matricula ).from( aluno );
  // SQL esperado: "select nome, matricula from aluno"

  cout << endl;

  select( nome, matricula, endereco ).from( aluno, turma );
  cout << endl;

  select( nome, matricula, endereco ).from( aluno, turma )
    .where( aluno.turma_id == turma.id );
  cout << endl;

  SELECT id, nome FROM aluno, turma WHERE aluno.turma_id == turma.id ENDL;

  return 0;
}