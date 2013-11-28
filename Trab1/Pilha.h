/*
 * Pilha.h
 *
 *  Created on: Sep 5, 2013
 *      Author: mateus
 */

#define MAX_PILHA 10

template <class T>
class Pilha
{
  public:

    Pilha(){
    	//for( int i = 0; i < MAX_PILHA; i++ )
    	    //tab[i] = 0;

    	topo_da_pilha = 0;
    }

    void empilha( T valor_a_ser_empilhado ) {
    	tab[topo_da_pilha++] = valor_a_ser_empilhado;
    }

    int desempilha() {
    	return tab[--topo_da_pilha];
    }

    // const: esse método não altera o estado do objeto
    void print( std::ostream& o ) const {
    	for( int i = 0; i < topo_da_pilha; i++ )
    	    o << tab[i] << " ";
    }

    Pilha& operator << ( T valor_a_ser_empilhado ) {
      empilha( valor_a_ser_empilhado );
      return *this;
    }

    // Sempre que um método não vai alterar o objeto ele deve ser
    // declarado como método 'const'
    bool operator > ( const Pilha& p ) const {
    	return this->tab[this->topo_da_pilha-1] > p.tab[p.topo_da_pilha-1];
    }


  private:
    T tab[MAX_PILHA];
    int topo_da_pilha;
};
