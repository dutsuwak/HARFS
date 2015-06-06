/*
 * ControllerNode.cpp
 *
 *  Created on: May 29, 2015
 *      Author: abrahamon
 */

#include "ControllerNode.h"
Server* ControllerNode::_Server;

ControllerNode::ControllerNode() {
	_SharedSecret = ControllerConstants::SHARED_SECRET;
	_Port = ControllerConstants::PORT;
	_DiskNodes = new LinkedList<string>();
	cout<<"CREANDO controller node en: "<<_Port<<endl;
	_Server = new Server(_Port);

	pthread_t hiloCliente;
	pthread_create(&hiloCliente,0,ControllerNode::senToDiskNode,(void*)this);
}

void* ControllerNode::senToDiskNode(void* pData) {
//	cout<<_Server->getFirstMessage()<<endl;
	while(true){
		sleep(1);
	//	cout<<"MENSAJE: "<<_Server->getFirstMessage();
	}

	pthread_exit(NULL);
}

