/*
 * Server.h
 *
 *  Created on: May 30, 2015
 *      Author: abrahamon
 */

#ifndef NETWORKACCESS_SERVER_H_
#define NETWORKACCESS_SERVER_H_

class Server {
private:
	int _Port;
public:
	Server(int pPort);
	virtual ~Server();
	void conect();
	void error(const char *msg);
};

#endif /* NETWORKACCESS_SERVER_H_ */


/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>




