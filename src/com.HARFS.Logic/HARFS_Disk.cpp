/*
 * HARFS-Disk.cpp
 *
 *  Created on: Jun 18, 2015
 *      Author: tvlenin
 */
#include "HARFS_Disk.h"
#include <boost/lexical_cast.hpp>
#include "../com.HARFS.DataStructures/LinkedNode.h"

HARFS_Disk::HARFS_Disk(){

}
/**
 * createStorageBlock lee un texto con la informacion de un nuevo
 * storageblock y luego lo crea
 * */
void HARFS_Disk::createStorageBlock(string pData){
	string storageName;
	string storageType;
	string RAIDType;
	int cont = 0;

	for(int i = 0; i < pData.length(); i++ ){
		if(pData[i] == '#'){cont++;i++;}
		if(cont == 0){storageName += pData[i];}
		if(cont == 1){storageType += pData[i];}
		if(cont == 2){RAIDType += pData[i];}
	}
	string UIDText = storageName + boost::lexical_cast<std::string>(storageType) + boost::lexical_cast<std::string>(RAIDType);
	string UIDStorageBlock = HARFS_Disk::createUID(UIDText);

	StorageBlock * storageBlock = new StorageBlock(storageName, storageType, RAIDType, UIDStorageBlock);

	listStorageBlocks->insertTail(storageBlock);
}

void HARFS_Disk::listStorageBlock() {
	Node<StorageBlock*>* tmp;
	tmp = listStorageBlocks->getHead();
	for (int i = 0; i < listStorageBlocks->getLength(); i++){
		tmp->getData()->getInfo();
		tmp = tmp->getNext();
	}
}

void HARFS_Disk::deleteStorageBlock(string pUID) {
	StorageBlock *tmp;
	tmp = listStorageBlocks->getHead()->getData();
	for (int i = 0; i < listStorageBlocks->getLength(); i++){
		if (tmp->getUID() == pUID){
			listStorageBlocks->deleteData(tmp);
		}
		tmp = listStorageBlocks->getHead()->getNext()->getData();
	}

}

void HARFS_Disk::defineStorageBlock(string pUID) {

}

void HARFS_Disk::saveRecord() {
}

void HARFS_Disk::deleteRecord() {
}

void HARFS_Disk::SearchRecord() {
}

void HARFS_Disk::getRecord() {
}

void HARFS_Disk::newUser() {

}

void HARFS_Disk::linkUserToStorageBlock() {
}

//bool HARFS_Disk::trySecurity() {
	//return true;
//}

string HARFS_Disk::createUID(string pData) {
	string UID = "";
	int lData = pData.length();
	int i = 0;
	if (lData<32){
		while(lData < 32){
			if(i==10){i = 0;}
			pData += boost::lexical_cast<std::string>(i);
			lData += 1;
			i += 1;
		}

	}
	for (int i = 0; i < (16); i++){
		UID += boost::lexical_cast<std::string>(pData[i])+boost::lexical_cast<std::string>(pData[pData.length()-(i+1)]);

	}


	return UID;
}
