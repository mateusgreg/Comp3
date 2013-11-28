/*
 * Binder.h
 *
 *  Created on: Oct 22, 2013
 *      Author: mateus
 */

#ifndef BINDER_H_
#define BINDER_H_

template <class F, class Arg1>
class Binder {

public:
	Binder(F& fn, const Arg1& arg): funcao(fn), argumento(arg) {}

	template <class Arg2>
	void operator()(Arg2& x) {
		funcao(argumento, x);
	}
private:
	F& funcao;
	const Arg1& argumento;
};

template <class F, class Arg1>
Binder<F, Arg1>* bind(F& funcao, const Arg1& arg) {
	return new Binder<F, Arg1>(funcao, arg);
}

#endif /* BINDER_H_ */
