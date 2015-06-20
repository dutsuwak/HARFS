/*
 * endecrypte.h
 *
 *  Created on: Jun 19, 2015
 *      Author: Mauricio
 */

#ifndef SRC_COM_HARFS_LOGIC_ENDECRYPTE_H_
#define SRC_COM_HARFS_LOGIC_ENDECRYPTE_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string>

using namespace std;

class endecrypte{
private:

public:
	static int number;
	static int numbermin;
	static int numbermax;
	endecrypte();
    string encrypte(string word);
    string decrypte(string word);
};
#endif /* SRC_COM_HARFS_LOGIC_ENDECRYPTE_H_*/
