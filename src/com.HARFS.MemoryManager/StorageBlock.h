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
using namespace std;

class StorageBlock{

public:
	StorageBlock(string pName, int pType, int pRaid);


};




#endif /* SRC_COM_HARFS_MEMORYMANAGER_STORAGEBLOCK_H_ */
