/*
 * Server.h
 *
 *  Created on: May 30, 2015
 *      Author: abrahamon
 */

#ifndef NETWORKACCESS_SERVER_H_
#define NETWORKACCESS_SERVER_H_

#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

class Server {
private:
	static int _Port;
public:
	Server(int pPort);
	static void* threadListen(void* pData);
	static void error(const char *msg);
};

#endif /* NETWORKACCESS_SERVER_H_ */




