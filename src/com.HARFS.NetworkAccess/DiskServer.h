/*
 * DiskServer.h
 *
 *  Created on: Jun 18, 2015
 *      Author: abrahamon
 */

#ifndef COM_HARFS_NETWORKACCESS_DISKSERVER_H_
#define COM_HARFS_NETWORKACCESS_DISKSERVER_H_

#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../com.HARFS.DataStructures/LinkedList.h"
#include "../com.HARFS.DataAccess/ControllerConstants.h"

using namespace std;

class DiskServer{
private:
	static int _ListeningPort;
	static LinkedList<string>* _MessagesList;
	static pthread_mutex_t mutex;
	//static LinkedList<string>* _UserList;
public:
	DiskServer(int pPort);
	static void* threadListen(void* pData);
	static void* receiveNewClient(void* newsockfd);
	static void error(const char *msg);
	string getFirstMessage();

};

#endif /* COM_HARFS_NETWORKACCESS_DISKSERVER_H_ */
