/*
 * main.cpp
 *
 *  Created on: 20/6/2015
 *      Author: mauricio
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "com.HARFS.Logic/endecrypte.h"
using namespace std;

int main() {
	endecrypte* c= new endecrypte();
	string respuesta=c->encrypte("perro de respuesta 123 ");
	string salida=c->decrypte(respuesta);
	cout<<respuesta;
	cout<<"viva la birra y minecraft";
}
