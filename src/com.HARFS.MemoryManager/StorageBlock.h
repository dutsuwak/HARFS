/*
 * StorageBlock.h
 *
 *  Created on: Jun 18, 2015
 *      Author: tvlenin
 */

#ifndef SRC_COM_HARFS_MEMORYMANAGER_STORAGEBLOCK_H_
#define SRC_COM_HARFS_MEMORYMANAGER_STORAGEBLOCK_H_
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>
#include "../com.HARFS.DataStructures/LinkedList.h"
#include "../com.HARFS.DataStructures/LinkedNode.h"
using namespace std;

class StorageBlock{

public:
	StorageBlock(string pName, string pType, string pRaid, string UID);
	void getInfo();
	string getUID();
	void setScheme(LinkedList<string>* pList);
private:
	LinkedList <string> *schemeDisk = new LinkedList<string>();
	string storageName;
	string storageType;
	string RAIDType;
	string UID;

};




#endif /* SRC_COM_HARFS_MEMORYMANAGER_STORAGEBLOCK_H_ */