/*
 * DiskNode.h
 *
 *  Created on: May 29, 2015
 *      Author: abrahamon
 */

#ifndef COM_HARFS_DATASTRUCTURES_COM_HARFS_RESOURCES_DISKNODE_H_
#define COM_HARFS_DATASTRUCTURES_COM_HARFS_RESOURCES_DISKNODE_H_

#include "../com.HARFS.DataAccess/DiskConstants.h";
#include "../com.HARFS.DataStructures/LinkedList.h";
#include "../com.HARFS.NetworkAccess/Server.h"

using namespace std;

class DiskNode {

private:
	Server* _Server;
	string _SharedSecret;
	string _Path;
	int _DiskSize;
	int _Port;

public:
	DiskNode();
	virtual ~DiskNode();

	int createStorageBlock(string pName, string pTypeOfOrganization, bool pRaid);
	LinkedList<string>* listStorageBlock(string pUID);
	void eraseStorageBlock();
	void defineSchemeOfStorageBlock(string comoEsElregistro);
	void storeRegisterInStorageBlock();
	void EraseRegisterOfFile();
	int search(string pUID, int column);
	void getRegister(int pShift);
	string createUser();
	void associateUser(string pUser, string pUID);
	bool licenseTest(string userSharedSecret, string pUIDOfStorageBlock);

};

#endif /* COM_HARFS_DATASTRUCTURES_COM_HARFS_RESOURCES_DISKNODE_H_ */
