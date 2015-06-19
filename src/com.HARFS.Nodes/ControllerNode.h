/*
 * ControllerNode.h
 *
 *  Created on: May 29, 2015
 *      Author: abrahamon
 */

#ifndef COM_HARFS_DATASTRUCTURES_COM_HARFS_RESOURCES_CONTROLLERNODE_H_
#define COM_HARFS_DATASTRUCTURES_COM_HARFS_RESOURCES_CONTROLLERNODE_H_

#include <pthread.h>
#include <unistd.h>
#include "../com.HARFS.DataAccess/ControllerConstants.h"
#include "../com.HARFS.DataStructures/LinkedList.h"
#include "../com.HARFS.NetworkAccess/Server.h"
#include "../com.HARFS.NetworkAccess/Client.h"
#include "../com.HARFS.NetworkAccess/user.h"

using namespace std;

class ControllerNode{

private:
	string _SharedSecret;
	int _Port;
	LinkedList<string>* _DiskNodes;
	static pthread_mutex_t mutex;
	static Server* _Server;
	static Client* _Client;

public:
	ControllerNode();
	static void* getMessageFromSocket(void* pData);
};

#endif /* COM_HARFS_DATASTRUCTURES_COM_HARFS_RESOURCES_CONTROLLERNODE_H_ */
