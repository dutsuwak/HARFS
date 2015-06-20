/*
 *endecrypte.cpp

 *
 *  Created on: Jun 19, 2015
 *      Author: Mauricio
 */

#include "endecrypte.h";

int endecrypte::number=rand()%21+4;
int endecrypte::numbermin=97;
int endecrypte::numbermax=122;

endecrypte::endecrypte(){
	srand(time(0));
};
//metodo que se encarga de encriptar frases
string endecrypte::encrypte(string word){

	int i=0;
	int encrypte = 0;
	while(word[i]!='\0')
	{
		//Convertimos a minúscula
		word[i] = tolower(word[i]);
		//Tomamos el código ascii
		if (word[i]+number > numbermax)
		{
			encrypte = numbermin + ((word[i]+number) - numbermax);
		}
		else
		{
			encrypte = word[i]+number;
		}
		word[i]=encrypte;
		i++;
	}
		return word;
}

string endecrypte::decrypte(string word){
	int i=0;
    int encrypte = 0;
    while(word[i]!='\0')
    	{
    		//Tomamos el código ascii
    		if (word[i]>=numbermin && word[i]<=numbermax)
    		{
    			if (word[i]-number < numbermin && word[i]-number >= (numbermin-number))
    			{
    				encrypte = numbermax - (numbermin - (word[i]-number));
    			}
    			else
    			{
    				encrypte = word[i]-number;
    			}
    		}
    		else
    		{
    			encrypte = word[i]-number;
    		}
    		word[i]=encrypte;
    		i++;
    	}

}
