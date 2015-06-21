/*
 * DiskLinkedList.h
 *
 *  Created on: Jun 18, 2015
 *      Author: fabian
 */

#ifndef SRC_COM_HARFS_DATASTRUCTURES_DISKLINKEDLIST_H_
#define SRC_COM_HARFS_DATASTRUCTURES_DISKLINKEDLIST_H_
#include <string>
#include <iostream>
#include <fstream>
#include <bitset>
#include <boost/lexical_cast.hpp>
#include "../com.HARFS.DataStructures/DiskLinkedNode.h"

using namespace std;

template<class k>
class DiskLinkedList{
private:
	std::string listName;
	int length;
	std::string getOffsetformat(int pOffset);
	std::string seekOnFile(FILE* pFile, int pSeek);
	int insertDataIntoFile(k pDato);
	DiskNode<k>* checkNodeData(k pData);

public:
	DiskLinkedList(std::string pName);
	void insertTail(k pData);
	void showData();
	bool findData(k pData);
	void deleteData(k pData);
	DiskNode<k>* getHead();
};

template<class k>
DiskLinkedList<k>::DiskLinkedList(std::string pName){
	listName = DiskConstants::FILES_PATH + pName;
	length = 0;

	std::string dataName = listName + ".bin";
	std::string metaDataName = listName + ".mtd";

	FILE* data;
	data = fopen ( dataName.c_str() , "wb" );
	//fputs ( "#00000#00000#00000\n" , data ); //ESCRIBIR EN EL ARCHIVO
	//long int size =ftell (pFile);		// OBTENER OFFSET
	fclose ( data );

	FILE* metaData;
	metaData = fopen ( metaDataName.c_str() , "wb" );
	fputs ( "#99999#99999#99999#99999#99999#99999#99999#99999#99999\n" , metaData ); //"NODO HEAD"
	fputs ( "#99999#99999#99999#99999#99999#99999#99999#99999#99999\n" , metaData ); //"NODO TAIL"
	fclose ( metaData );


}

template<class k>
void DiskLinkedList<k>::insertTail(k pData){
	FILE* metaDataFile;
	metaDataFile = fopen ((listName+".mtd").c_str() , "r+" );


	std::string spData = boost::lexical_cast<std::string>(pData); //Dato ingresado
	int lengthpData = spData.length();	//Tamaño del dato ingresado(en caracteres)(1caracter=8bits)
	std::string pLengthpData = getOffsetformat(lengthpData); //Obtener formato para el metadato

	string pStringOffset = seekOnFile(metaDataFile,1); //Offset actual(para verificar si hay dato)
	int pOffsetdelNodoHead = atoi(pStringOffset.c_str());

	if(pOffsetdelNodoHead == 99999){	//NO HAY DATO HEAD

		int currentOffset = insertDataIntoFile(pData);

		std::string newOffset = getOffsetformat(currentOffset);

		fseek (metaDataFile, 1 , SEEK_SET );
		fputs (newOffset.c_str(), metaDataFile );

		fseek (metaDataFile, 19 , SEEK_SET );
		fputs (pLengthpData.c_str(), metaDataFile );

	}
	else{//SI HAY DATO EN EL HEAD
		string sOffset = seekOnFile(metaDataFile,56);

		int intOffset = atoi(sOffset.c_str());
		int offsetDeDatoInsertado = insertDataIntoFile(pData)/8; //Dividir entre 8, para representar
																 //la cantidad de bits que se tiene que mover

		if(intOffset == 99999){ //NO HAY DATO EN EL TAIL
			string newOffsetDeDatoInsertado = getOffsetformat(offsetDeDatoInsertado);
			string newOffsetDelNodoHead = getOffsetformat(pOffsetdelNodoHead);
			string sLengthHead = seekOnFile(metaDataFile,19);	  //Obtener length del head

			string OffsetMetadatoTail = getOffsetformat(1);		  //offsetMetadato (Tail)
			string sNextMetadatoTail = getOffsetformat(0);		  //sNextMetadato (Tail)
			string sPreviousMetadatoTail = getOffsetformat(0);	  //sPreviousMetadato (Tail)

			string OffsetMetadatoHead = getOffsetformat(0);		  //sNextMetadato (Head)
			string sNextMetadatoHead = getOffsetformat(1);		  //sNextMetadato (Head)
			string sPreviousMetadatoHead = getOffsetformat(1);	  //sPreviousMetadato (Head)

			fseek (metaDataFile, 7 , SEEK_SET );
			fputs (newOffsetDeDatoInsertado.c_str(), metaDataFile ); //Asigna valor de Next al nodo Head

			fseek (metaDataFile, 13, SEEK_SET );
			fputs (newOffsetDeDatoInsertado.c_str(), metaDataFile ); //Asigna valor de Previous al nodo Head

			fseek (metaDataFile, 25, SEEK_SET );
			fputs (pLengthpData.c_str(), metaDataFile ); 			//Asigna tamaño del Next al nodo Head

			fseek (metaDataFile, 31, SEEK_SET );
			fputs (pLengthpData.c_str(), metaDataFile ); 			//Asigna tamaño del Previous

			fseek (metaDataFile, 37, SEEK_SET );
			fputs (OffsetMetadatoHead.c_str(), metaDataFile ); 	    //Asigna OFFSET a head (metadato)

			fseek (metaDataFile, 43, SEEK_SET );
			fputs (sNextMetadatoHead.c_str(), metaDataFile );       //Asigna OFFSET_Next a head,(metadato)

			fseek (metaDataFile, 49, SEEK_SET );
			fputs (sPreviousMetadatoHead.c_str(), metaDataFile );   //Asigna OFFSET_Previous a head,(metadato)

			fseek (metaDataFile , 56 , SEEK_SET );
			fputs (newOffsetDeDatoInsertado.c_str(), metaDataFile ); //Asigna apuntador al dato del tail

			fseek (metaDataFile , 62 , SEEK_SET );
			fputs (newOffsetDelNodoHead.c_str(), metaDataFile );     //Asigna valor de Next al nodo tail

			fseek (metaDataFile , 68 , SEEK_SET );
			fputs (newOffsetDelNodoHead.c_str(), metaDataFile );     //Asigna valor de Previous al nodo tail

			fseek (metaDataFile , 74 , SEEK_SET );
			fputs (pLengthpData.c_str(), metaDataFile ); 		     //Asigna tamaño del Dato

			fseek (metaDataFile , 80 , SEEK_SET );
			fputs (sLengthHead.c_str(), metaDataFile ); 		     //Asigna tamaño del Next

			fseek (metaDataFile , 86 , SEEK_SET );
			fputs (sLengthHead.c_str(), metaDataFile ); 		     //Asigna tamaño del Previous

			fseek (metaDataFile , 92 , SEEK_SET );
			fputs (OffsetMetadatoTail.c_str(), metaDataFile ); 		 //Asigna Offset a tail,(metadato)

			fseek (metaDataFile , 98 , SEEK_SET );
			fputs (sNextMetadatoTail.c_str(), metaDataFile ); 		 //Asigna OFFSET_Next a tail,(metadato)

			fseek (metaDataFile , 104 , SEEK_SET );
			fputs (sPreviousMetadatoTail.c_str(), metaDataFile );    //Asigna OFFSET_Previous a tail,(metadato)
		}
		else{	//HAY DATO EN EL TAIL


			string sOffsetNext = seekOnFile(metaDataFile,56);	  //Obtener offset del next
			string sOffsetPrevious = seekOnFile(metaDataFile,68); //Obtener offset del previous

			string sLengthHead = seekOnFile(metaDataFile,19);	  //Obtener length del head
			string sLenghtNext = seekOnFile(metaDataFile,80);     //Obtener length del next
			string sLenghtPrevious = seekOnFile(metaDataFile,86); //Obtener length del previous
			string sLenghtTail     = seekOnFile(metaDataFile,74); //Obtener length del tail

			string sNextMetadatoTail = getOffsetformat(0);		  //sNextMetadato (Tail)

			int iOffsetNext = atoi(sOffsetNext.c_str());
			int iOffsetPrevious = atoi(sOffsetPrevious.c_str());


			string OffsetDelNodoTail = getOffsetformat(intOffset);			//Offset del nuevo dato
			string OffsetNextDelNodoTail = getOffsetformat(iOffsetNext);	//Offset Next del tail
			string OffsetPreviousDelNodoTail = getOffsetformat(iOffsetPrevious);//Offset Previous tail


			string newOffsetDeDatoInsertado = getOffsetformat(offsetDeDatoInsertado);
			string newOffsetDelNodoHead = getOffsetformat(pOffsetdelNodoHead);


			string offsetMetadatoTail = getOffsetformat(1); //Asigna offset previuos, al tail(metadato)
			string nextMetadatoTail = getOffsetformat(0);
			string nextMetadatoHead = getOffsetformat(2);

			string currentMetadato = getOffsetformat(length);
			string nextMetadato = getOffsetformat(length+1);
			string previousMetadato = seekOnFile(metaDataFile,104);



			fseek (metaDataFile , 0 , SEEK_END );   //Pone apuntador al fin del archivo
			std::string pStringOffset = boost::lexical_cast<std::string>(offsetDeDatoInsertado);
			std::string nuevoNodo = "#"+OffsetDelNodoTail+"#"+newOffsetDeDatoInsertado+
									"#"+OffsetPreviousDelNodoTail+"#"+sLenghtTail+
									"#"+pLengthpData+"#"+sLenghtPrevious+
									"#"+currentMetadato+"#"+nextMetadato+"#"+previousMetadato+"\n";
			fputs(nuevoNodo.c_str(),metaDataFile);


			//############### ACTUALIZAR DATOS DEL TAIL ######################

			fseek (metaDataFile, 13, SEEK_SET );
			fputs (newOffsetDeDatoInsertado.c_str(), metaDataFile ); //Asigna valor de Previous al nodo Head

			fseek (metaDataFile, 31, SEEK_SET );
			fputs (pLengthpData.c_str(), metaDataFile ); 			//Asigna tamaño del Previous al nodo Head

			fseek (metaDataFile, 43, SEEK_SET );
			fputs (nextMetadatoHead.c_str(), metaDataFile ); //Asigna OFFSET_Next a head,(metadato)

			//fseek (metaDataFile, 49, SEEK_SET );
			//fputs (OffsetTailMetadata.c_str(), metaDataFile );    //Asigna OFFSET_Previous a head,(metadato)

			fseek (metaDataFile , 56 , SEEK_SET );
			fputs (newOffsetDeDatoInsertado.c_str(), metaDataFile ); //Asigna apuntador al dato del tail

			fseek (metaDataFile , 62 , SEEK_SET );
			fputs (newOffsetDelNodoHead.c_str(), metaDataFile ); //Asigna valor de Next al nodo tail

			fseek (metaDataFile , 68 , SEEK_SET );
			fputs (OffsetDelNodoTail.c_str(), metaDataFile ); //Asigna valor de Previous al nodo tail

			fseek (metaDataFile , 74 , SEEK_SET );
			fputs (pLengthpData.c_str(), metaDataFile );      //Asigna tamaño del Nodo

			fseek (metaDataFile , 80 , SEEK_SET );
			fputs (sLengthHead.c_str(), metaDataFile );		 //Asigna tamaño del Next

			fseek (metaDataFile , 86 , SEEK_SET );
			fputs (sLenghtTail.c_str(), metaDataFile ); 	 //Asigna tamaño del Previous

			fseek (metaDataFile , 92 , SEEK_SET );
			fputs (offsetMetadatoTail.c_str(), metaDataFile ); 		 //Asigna OFFSET a tail (metadato)

			fseek (metaDataFile , 98 , SEEK_SET );
			fputs (nextMetadatoTail.c_str(), metaDataFile ); 		 //Asigna OFFSET_Next a tail (metadato)

			fseek (metaDataFile , 104 , SEEK_SET );
			fputs (currentMetadato.c_str(), metaDataFile );    //Asigna OFFSET_Previous a tail,(metadato)

		}

	}
	fclose(metaDataFile);
	length++;
}
template<class k>
int DiskLinkedList<k>::insertDataIntoFile(k pData){
	FILE* realDataFile;
	realDataFile = fopen ((listName+".bin").c_str() , "r+" );

	fseek (realDataFile , 0 , SEEK_END );   //Pone apuntador al fin del archivo
	int currentOffset = ftell (realDataFile);		//Obtiene el nuevo offset

	//cout<< "OFFSET " << currentOffset <<endl;

	string pStringDatos = boost::lexical_cast<std::string>(pData);///Convierte dato tipo k, a string

	//cout<<"DATO A ESCRIBIR: "<<pStringDatos<< endl;

	for (std::size_t i = 0; i < pStringDatos.size(); ++i){
		bitset<8> p = bitset<8>(pStringDatos.c_str()[i]); //Convierte a binario (Valor ascii)
		string x = p.to_string();						   //Convierte a string
		fputs(x.c_str(),realDataFile);					   //Escribe en el archivo, cada caracter
	}

	fclose(realDataFile);

	return currentOffset;
}

template<class k>
std::string DiskLinkedList<k>::seekOnFile(FILE* pFile,int pSeek){
	std::string output;
	fseek (pFile , pSeek , SEEK_SET );
	for(int i=0; i < 5 ; i++){
		int c = fgetc (pFile);
		output.operator +=((char)c);
	}
	return output;
}

template<class k>
std::string DiskLinkedList<k>::getOffsetformat(int pOffset){
	std::string pStringDatos = boost::lexical_cast<std::string>(pOffset);
	int datosLength = pStringDatos.length();

	for(int i = 0; i< 5-datosLength;i++){
		pStringDatos = "0"+pStringDatos;
	}

	return pStringDatos;
}

template<class k>
DiskNode<k>* DiskLinkedList<k>::getHead(){
	DiskNode<k>* n = new DiskNode<k>();

	std::string dataName = listName + ".mtd";

	FILE* data;
	data = fopen ( dataName.c_str() , "r" );

	std::string output;
	fseek (data , 0 , SEEK_SET );

	int c = fgetc(data);
	while(c != 10){
		output.operator +=((char)c);
		c = fgetc (data);
	}
	fclose (data);
	n->setData(output);
	n->setListName(listName,length);
	return n;

}

template<class k>
bool DiskLinkedList<k>::findData(k pData){
	DiskNode<k>* n = getHead();
	for(int i = 0; i < length; i++){
		if(n->getData() == pData){
			return true;
		}
		n = n->getNext();
	}
	return false;
}

template<class k>
DiskNode<k>* DiskLinkedList<k>::checkNodeData(k pData){
	DiskNode<k>* n = getHead();
	for(int i = 0; i < length; i++){
		if(n->getData() == pData){
			return n;
		}
		n = n->getNext();
	}
}

template<class k>
void DiskLinkedList<k>::deleteData(k pData){
	if(findData(pData) == false){ return; }
	else{
		DiskNode<k>* tmp = getHead();					 //Iterador comienza en el head
		DiskNode<k>* nodeToDelete = checkNodeData(pData);//Nodo del dato a borrar

		std::string dataName = listName + ".mtd";

		FILE* metaDataFile;
		metaDataFile = fopen ( dataName.c_str() , "r+" );

		if(tmp->getData() == nodeToDelete->getData()){ //CASO 1: Borrar el head
			if(length == 1){
				fseek (metaDataFile , 0 , SEEK_SET );
				fputs ( "#99999#99999#99999#99999#99999#99999#99999#99999#99999\n" , metaDataFile );
			}
			else{
				DiskNode<k>* pNext = tmp->getNext();
				fseek (metaDataFile , 1 , SEEK_SET );
				fputs((pNext->getPtrData()).c_str(),metaDataFile);

				fseek(metaDataFile,7,SEEK_SET);
				fputs((pNext->getptrNext()).c_str(),metaDataFile);

				fseek(metaDataFile,19,SEEK_SET);
				fputs((pNext->getsizeData()).c_str(),metaDataFile);

				fseek(metaDataFile,25,SEEK_SET);
				fputs((pNext->getsizeNext()).c_str(),metaDataFile);

				fseek(metaDataFile,43,SEEK_SET);
				fputs((pNext->getmetaNext()).c_str(),metaDataFile);

				fseek(metaDataFile,62,SEEK_SET);
				string pNext_Tail = getOffsetformat(pNext->getData());
				fputs((pNext_Tail).c_str(),metaDataFile);

				string sOffset = pNext->getmetaNext();
				int offsetMetaNext = atoi(sOffset.c_str());
				int finalOffset = (offsetMetaNext*55)+49;

				fseek(metaDataFile,finalOffset,SEEK_SET);
				string offsetPreviousNextNode = getOffsetformat(0);
				fputs((offsetPreviousNextNode).c_str(),metaDataFile);


			}
			cout<<"LENGHT ANTES: "<<length<<endl;
			length--;
			cout<<"LENGHT DESPUES: "<<length<<endl;

		}
		fclose (metaDataFile);

	}
}

template<class k>
void DiskLinkedList<k>::showData(){
	DiskNode<k>* n = getHead();
	cout<<"LENGHT SHOWDATA: "<<length<<endl;
	for(int i = 0; i < length; i++){
		cout<< n->getData() <<endl;
		n = n->getNext();
	}
}

#endif /* SRC_COM_HARFS_DATASTRUCTURES_DISKLINKEDLIST_H_ */
