/*
 * ControllerNode.h
 *
 *  Created on: May 29, 2015
 *      Author: abrahamon
 */

#ifndef COM_HARFS_DATASTRUCTURES_COM_HARFS_RESOURCES_CONTROLLERNODE_H_
#define COM_HARFS_DATASTRUCTURES_COM_HARFS_RESOURCES_CONTROLLERNODE_H_

#include <pthread.h>
#include "../com.HARFS.DataAccess/ControllerConstants.h"
#include "../com.HARFS.NetworkAccess/Server.h"
#include "../com.HARFS.DataStructures/LinkedList.h"

using namespace std;

class ControllerNode {

private:
	static Server* _Server;
	string _SharedSecret;
	int _Port;
	LinkedList<string>* _DiskNodes;

public:
	ControllerNode();
	static void* senToDiskNode(void* pData);
};

#endif /* COM_HARFS_DATASTRUCTURES_COM_HARFS_RESOURCES_CONTROLLERNODE_H_ */
