/*
 * ControllerNode.cpp
 *
 *  Created on: May 29, 2015
 *      Author: abrahamon
 */

#include "ControllerNode.h"

Server* ControllerNode::_Server;
pthread_mutex_t ControllerNode::mutex = PTHREAD_MUTEX_INITIALIZER;

ControllerNode::ControllerNode() {

	_SharedSecret = ControllerConstants::SHARED_SECRET;
	_Port = ControllerConstants::PORT;
	_DiskNodes = new LinkedList<string>();
	if(ControllerConstants::DEBUG=="true")
		cout<<"CREANDO controller node en: "<<_Port<<endl;
	_Server = new Server(_Port);

	pthread_t hiloCliente;
	pthread_create(&hiloCliente,0,ControllerNode::getMessageFromSocket,(void*)this);
}

void* ControllerNode::getMessageFromSocket(void* pData) {
	while(true){
		sleep(0.2);

		pthread_mutex_lock(&mutex);

		string msj=_Server->getFirstMessage();
		if(msj != "-1"){
			cout<<msj<<endl;
		}
		pthread_mutex_unlock(&mutex);

	}
	pthread_exit(NULL);
}

