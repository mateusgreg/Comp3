/*
 * main.cpp
 *
 *  Created on: Oct 11, 2013
 *      Author: mateus
 */

#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdlib.h>
#include <iostream>

#define DEFAULT_SIZE 10


class MatrizIndexOutOfBounds {
	public:
		MatrizIndexOutOfBounds( const char* msg ): msg(msg) {}
	private:
		const char* msg;
};

class MatrizesIncompativeis {
public:
		MatrizesIncompativeis( const char* msg ): msg(msg) {}
	private:
		const char* msg;
};

template <class T>
class Matriz {

public:

	class Linha {
		public:
			//usando lista de inicialização: mais otimizado pelo compilador!
			Linha (unsigned i, Matriz* mat): i(i), matriz(mat) {}

			T& operator[] (unsigned j) {
				return matriz->elemento(i, j);
			}

		private:
			unsigned i;
			Matriz* matriz;
	};

	Matriz() {
		lins = (cols = DEFAULT_SIZE);
		this->matriz = new T[lins*cols];
	}

	Matriz(unsigned linhas, unsigned colunas) {
		if (linhas == 0  && colunas == 0) {
			lins = (cols = DEFAULT_SIZE);
		} else {
			lins = linhas;
			cols = colunas;
		}
		this->matriz = new T[lins*cols];

		//DEBUG:
		//cout << "linhas = " << lins << "; colunas = " << cols << endl;
	}

	virtual ~Matriz() {
		delete [] matriz;
	}

	Linha operator[] (unsigned i) {
		return Linha(i, this);
	}

	T& elemento(unsigned i, unsigned j) {
		//DEBUG:
		//cout << "posicao " << (i*cols + j) << endl;

		if (i >= lins) throw new MatrizIndexOutOfBounds("Indice da linha maior que o número de linhas da matriz!");
		else if (j >= cols) throw new MatrizIndexOutOfBounds("Indice da coluna maior que o número de colunas da matriz!");

		return this->matriz[i*cols + j];
	}


	void operator= (Matriz* mat) {
		this->matriz(mat->lins, mat->cols);

		for (int i=0; i < mat->lins; i++) {
			for (int j=0; j < mat->cols; j++) {
				this->matriz[i*cols + j] = mat[i*mat->cols + j];
			}
		}
	}


	//soma a matriz referenciada por this com a passada por parametro e guarda o resultado na primeira
	Matriz& operator+ (Matriz& mat) {
		if (this->lins != mat.lins  || this->cols != mat.cols) {
			throw new MatrizesIncompativeis("Matrizes não podem ser somadas, pois não possuem o mesmo numero de linhas e colunas.");
		}

		Matriz<T> *resultado = new Matriz<T>(this->lins, this->cols);

		for (unsigned i=0; i<lins; i++) {
			for (unsigned j=0; j<cols; j++) {
				resultado->matriz[i*cols + j] = this->matriz[i*cols + j] + mat[i][j];
			}
		}

		return *resultado;
	}

	//operador aritmetico: multiplicacao
	Matriz& operator* (Matriz& mat) {
		if (this->cols != mat.lins) {
			throw new MatrizesIncompativeis("Matrizes não podem ser multiplicadas, pois o numero de colunas da primeira matriz eh diferente do numero de linhas da segunda.");
		}

		Matriz<T> *resultado = new Matriz<T>(this->lins, mat.cols);
		T soma;

		for (unsigned i=0; i<this->lins; i++) {
			for (unsigned j=0; j<mat.cols; j++) {
				soma = 0;
				for (unsigned k=0; k<this->cols; k++) {
					soma += this->matriz[i*cols + k] * mat[k][j];
				}
				resultado->matriz[i*mat.cols + j] = soma;
			}
		}

		return *resultado;
	}

	// const: esse método não altera o estado do objeto
	void print (std::ostream& o) const {
		for (unsigned i=0; i<lins; i++) {
			for (unsigned j=0; j<cols; j++) {
				o << this->matriz[i*cols + j] << "     ";
			}
			o << endl;
		}
	}

	Matriz& resize(unsigned linhas, unsigned colunas) {
		if(this->lins != linhas && this->cols != colunas) {
			//DEBUG:
			cout << "resizing...   tamanho das matrizes:" << endl;
			cout << "antiga[" << this->lins << "][" << this->cols << "];   ";
			cout << "nova[" << linhas << "][" << colunas << "];   ";
			cout << endl << endl;

			T *antiga = this->matriz;
			this->matriz = new T[linhas*colunas];

			unsigned menorLinhas = (this->lins < linhas? this->lins : linhas);
			unsigned menorColunas = (this->cols < colunas? this->cols : colunas);

			for(unsigned i=0; i<menorLinhas; i++) {
				for (unsigned j=0; j<menorColunas; j++) {
					this->matriz[i*colunas + j] = antiga[i*this->cols + j];

					//DEBUG:
					cout << "resizing...   nova[" << i*colunas << "][" << j << "]  =  antiga[" << i*this->cols << "][" << j << "];\n";
				}
				//DEBUG:
				cout << "resizing...   NOVA LINHA!\n";
			}

			this->lins = linhas;
			this->cols = colunas;

			delete[] antiga;
		}

		return *this;
	}

private:
	T* matriz;	//vetor de tamanho lins*cols
	unsigned lins, cols;
};

#endif	//MATRIZ_H
