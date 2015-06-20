
/*
 * StorageName.cpp
 *
 *  Created on: Jun 18, 2015
 *      Author: tvlenin
 */
#include "../com.HARFS.MemoryManager/StorageBlock.h"
#include "../com.HARFS.DataAccess/DiskConstants.h"

StorageBlock::StorageBlock(string pName, string pType, string pRaid, string pUID){
	storageName = pName;
	storageType = pType;
	RAIDType = pRaid;
	UID = pUID;
	if(DiskConstants::DEBUG == "true"){
		cout<<"Nombre del Storage Block: "<<storageName<<endl;
		cout<<"Tipo de Storage Block: "<<storageType<<endl;
		cout<<"Tipo de Raid del Storage Block: "<<RAIDType<<endl;
		cout<<"UID del Storage Block: "<<UID<<endl;
	}

}
void StorageBlock::getInfo(){
	cout<<"Nombre del Storage Block: "<<storageName<<endl;
	cout<<"UID del Storage Block: "<<UID<<endl;

}

string StorageBlock::getUID() {
	return UID;
}


void StorageBlock::setScheme(LinkedList<string>* pList) {
	schemeDisk =  pList;
}
