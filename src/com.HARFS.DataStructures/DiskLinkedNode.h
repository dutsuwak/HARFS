/*
 * DiskLinkedNode.h
 *
 *  Created on: Jun 19, 2015
 *      Author: fabian
 */

#ifndef SRC_COM_HARFS_DATASTRUCTURES_DISKLINKEDNODE_H_
#define SRC_COM_HARFS_DATASTRUCTURES_DISKLINKEDNODE_H_
#include <string>
#include "../com.HARFS.DataAccess/DiskConstants.h"
#include <boost/lexical_cast.hpp>

using namespace std;

template<class k>
class DiskNode{
private:
	int _ptrData;
	int _ptrNext;
	int _ptrPrevious;
	int _sizeData;
	int _sizeNext;
	int _sizePrevious;
	int _metaData;
	int _metaNext;
	int _metaPrevious;
	string _listName;
	int _length;

	void setPtrData(string pData);
	void setptrNext(string pData);
	void setptrPrevious(string pData);
	void setsizeData(string pData);
	void setsizeNext(string pData);
	void setsizePrevious(string pData);
	void setmetaData(string pData);
	void setmetaNext(string pData);
	void setmetaPrevious(string pData);

	int binaryToIntegerint(string numArray,int ind,int resultado,int maxType);
	int arrayToInt(int pArray[],int ind,int resultado, int length, int potencia);

public:
	DiskNode();
	void setData(string pData);
	void setListName(string pData, int pLength);

	k getData();
	DiskNode<k>* getNext();
	DiskNode<k>* getPrevious();

};

template<class k>
DiskNode<k>::DiskNode(){
	_ptrData= 0; _ptrNext = 0; _ptrPrevious= 0;
	_sizeData= 0; _sizeNext= 0; _sizePrevious= 0;
	_metaData= 0; _metaNext= 0; _metaPrevious= 0;
	_length= 0;
}

template<class k>
void DiskNode<k>::setData(string pData){
	int i;
	for(i = 1; i < pData.length(); i++){
		int j;
		string info = "";
		for(j=i; j < (i+5); j++){
			info.operator +=(pData[j]);
			//cout<<pData[j];
		}
		i=j;
		int datoInfo = i/6;
		switch (datoInfo) {
		case 1:
			setPtrData(info);
			break;
		case 2:
			setptrNext(info);
			break;
		case 3:
			setptrPrevious(info);
			break;
		case 4:
			setsizeData(info);
			break;
		case 5:
			setsizeNext(info);
			break;
		case 6:
			setsizePrevious(info);
			break;
		case 7:
			setmetaData(info);
			break;
		case 8:
			setmetaNext(info);
			break;
		case 9:
			setmetaPrevious(info);
			break;
		}
		//cout<<endl;
	}
}

template<class k>
DiskNode<k>* DiskNode<k>::getNext(){
	DiskNode<k>* n = new DiskNode<k>();

	std::string dataName = _listName + ".mtd";

	FILE* data;
	data = fopen ( dataName.c_str() , "r" );

	std::string output;
	if(_metaNext == 0){ fseek (data , 0 , SEEK_SET ); }
	else if(_metaNext == 1){ fseek(data,55,SEEK_SET); }
	else if(_metaNext == _length){ fseek(data,55,SEEK_SET);}
	else{fseek(data,55*_metaNext,SEEK_SET); }

	int c = fgetc(data);
	while(c != 10){
		output.operator +=((char)c);
		c = fgetc (data);
	}
	//cout<<output<<endl;
	fclose (data);
	n->setData(output);
	n->setListName(_listName,_length);
	return n;
}

template<class k>
DiskNode<k>* DiskNode<k>::getPrevious(){
	DiskNode<k>* n = new DiskNode<k>();

	std::string dataName = _listName + ".mtd";

	FILE* data;
	data = fopen ( dataName.c_str() , "r" );

	std::string output;
	if(_metaPrevious == 0){ fseek (data , 0 , SEEK_SET ); }
	else if(_metaPrevious == 1){ fseek(data,55,SEEK_SET); }
	else if(_metaPrevious == _length){ fseek(data,55,SEEK_SET);}
	else{fseek(data,55*_metaPrevious,SEEK_SET); }

	int c = fgetc(data);
	while(c != 10){
		output.operator +=((char)c);
		c = fgetc (data);
	}
	//cout<<output<<endl;
	fclose (data);
	n->setData(output);
	n->setListName(_listName,_length);
	return n;
}

template<class k>
k DiskNode<k>::getData(){
	std::string dataName = _listName + ".bin";

	FILE* data;
	data = fopen ( dataName.c_str() , "r" );

	std::string output;
	fseek (data , _ptrData * 8 , SEEK_SET );
	for(int i=0; i < _sizeData * 8 ; i++){
		int c = fgetc (data);
		output.operator +=((char)c);
	}
	fclose (data);

	int arregloDeNumeros[_sizeData];

	int i;
	for(i=0; i<output.length();i++){
		int j;
		string pDatoN = "";
		for(j=i; j <(i+8); j++){
			pDatoN += output[j];
		}
		i=j-1;
		int n = strtoull(pDatoN.c_str(),0,2);
		arregloDeNumeros[(j/8)-1] = (char)n;
	}
	int datoFinal = arrayToInt(arregloDeNumeros,0,0,_sizeData,_sizeData-1);


	//cout<<"DATO: "<< output<<endl;
	//int x = strtoull(output.c_str(),0,2);

	return datoFinal;

}

template<class k>
int DiskNode<k>::arrayToInt(int pArray[], int ind, int resultado, int length,int potencia){
	if(ind >= length){
		return resultado;
	}
	else{
		int x = pArray[ind]-48;
		int y = (char)x *pow(10,potencia);
		resultado+=y;
		arrayToInt(pArray,ind+1,resultado,length,potencia-1);
	}
}

template<class k>
int DiskNode<k>::binaryToIntegerint(string numArray,int ind,int resultado,int maxType){
	  if(ind == maxType){
	    return resultado;
	  }
	  else if(numArray[ind] == '1'){
	    resultado+= pow(2,ind);
	    binaryToIntegerint(numArray,ind+=1,resultado,maxType);

	  }
	  else{
		  binaryToIntegerint(numArray,ind+=1,resultado,maxType);

	  }
	}

template<class k>
void DiskNode<k>::setListName(string pData, int pLength){_listName = pData; _length = pLength;}

template<class k>
void DiskNode<k>::setPtrData(string pData){_ptrData = atoi(pData.c_str());}

template<class k>
void DiskNode<k>::setptrNext(string pData){_ptrNext = atoi(pData.c_str());}

template<class k>
void DiskNode<k>::setptrPrevious(string pData){_ptrPrevious = atoi(pData.c_str());}

template<class k>
void DiskNode<k>::setsizeData(string pData){_sizeData = atoi(pData.c_str());}

template<class k>
void DiskNode<k>::setsizeNext(string pData){_sizeNext = atoi(pData.c_str());}

template<class k>
void DiskNode<k>::setsizePrevious(string pData){_sizePrevious = atoi(pData.c_str());}

template<class k>
void DiskNode<k>::setmetaData(string pData){_metaData = atoi(pData.c_str());}

template<class k>
void DiskNode<k>::setmetaNext(string pData){_metaNext = atoi(pData.c_str());}

template<class k>
void DiskNode<k>::setmetaPrevious(string pData){_metaPrevious = atoi(pData.c_str());}



#endif /* SRC_COM_HARFS_DATASTRUCTURES_DISKLINKEDNODE_H_ */
