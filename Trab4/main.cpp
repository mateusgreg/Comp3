/*
 * main.cpp
 *
 *  Created on: Oct 11, 2013
 *      Author: mateus
 */

#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

#include "Binder.h"

int main( int argc, char* argv[])
{
	int tab[5] = { 3, 5, 7, 9, 11 };
	for_each( tab, tab+5, bind( printf, "%d " ) );

	return 0;
}
