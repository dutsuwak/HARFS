/*
 * HARFS-Disk.cpp
 *
 *  Created on: Jun 18, 2015
 *      Author: tvlenin
 */
#include "HARFS_Disk.h"
#include <boost/lexical_cast.hpp>

HARFS_Disk::HARFS_Disk(){

}

void HARFS_Disk::createStorageBlock(string pData){
	string storageName;
	int storageType;
	int RAIDType;



}

void HARFS_Disk::listStorageBlock() {
}

void HARFS_Disk::deleteStorageBlock() {
}

void HARFS_Disk::defineStorageBlock() {
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
		//cout<<pData[i] << ""<<pData[pData.length()-(i+1)]<<endl;
		//cout<<UID<<endl;
		UID += boost::lexical_cast<std::string>(pData[i])+boost::lexical_cast<std::string>(pData[pData.length()-(i+1)]);

	}
	cout<<pData<<endl;
	cout<<UID<<endl;

	return UID;
}
