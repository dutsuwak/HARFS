/*
 * ControllerNode.cpp
 *
 *  Created on: May 29, 2015
 *      Author: abrahamon
 */

#include "ControllerNode.h"

SocketServer* ControllerNode::_ServerSocket;
Server* ControllerNode::_Server;
pthread_mutex_t ControllerNode::mutex = PTHREAD_MUTEX_INITIALIZER;
Client* ControllerNode::_Client;
ControllerNode::ControllerNode() {

	_SharedSecret = ControllerConstants::SHARED_SECRET;
	_Port = ControllerConstants::LISTENINGPORT;
	_DiskNodes = new LinkedList<string>();
	if(ControllerConstants::DEBUG=="true")
		cout<<"CREANDO controller node, escucha en: "<<_Port<<endl;
	//_Server = new Server(_Port);
	_ServerSocket = new SocketServer(_Port);
	_ServerSocket->run();
	pthread_t hiloCliente;
	pthread_create(&hiloCliente,0,ControllerNode::getMessageFromSocket,(void*)this);

	string TmpIPS = ControllerConstants::DISK_NODES->getHead()->getData();
	char sep = ':';
	string ans[2];
	int i =0;
	for(size_t p=0, q=0; p!=TmpIPS.npos; p=q){
		ans[i]=TmpIPS.substr(p+(p!=0), (q=TmpIPS.find(sep, p+1))-p-(p!=0));
		i++;
	}
	int pPort = atoi(ans[1].c_str());
	char* pIP = ans[0].c_str();
	_Client = new Client(pIP,pPort);
	if(ControllerConstants::DEBUG=="true")
			cout<<"Envia a: "<<pIP<<":"<<pPort<<endl;
}

void* ControllerNode::getMessageFromSocket(void* pData) {
	while(true){
		sleep(0.2);

		pthread_mutex_lock(&mutex);

		string msj=_Server->getFirstMessage();
		if(msj != "-1"){
			_Client->receiveMessage(msj);
		}
		pthread_mutex_unlock(&mutex);

	}
	pthread_exit(NULL);
}

