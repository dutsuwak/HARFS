/*
 * ControllerNode.cpp
 *
 *  Created on: May 29, 2015
 *      Author: abrahamon
 */

#include "ControllerNode.h"

Server* ControllerNode::_Server;
pthread_mutex_t ControllerNode::mutex = PTHREAD_MUTEX_INITIALIZER;
Client* ControllerNode::_Client;

ControllerNode::ControllerNode() {

	_SharedSecret = ControllerConstants::SHARED_SECRET;
	_Port = ControllerConstants::LISTENINGPORT;
	_DiskNodes = new LinkedList<string>();
	if(ControllerConstants::DEBUG=="true")
		cout<<"controllerNode() 	 Escucha en: "<<_Port<<endl;
	_Server = new Server(_Port);

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
		cout<<"controllerNode() envia a: "<<pIP<<":"<<pPort<<endl;
	pthread_t hiloCliente;
	pthread_create(&hiloCliente,0,ControllerNode::getMessageFromSocket,(void*)this);
			cout<<"Envia a: "<<pIP<<":"<<pPort<<endl;
}

void* ControllerNode::getMessageFromSocket(void* pData) {
	while(true){
		//los mensajes direccion  usuario >>>>>> disk node
		pthread_mutex_lock(&mutex);
		string msj=_Server->getFirstMessage();
		pthread_mutex_unlock(&mutex);
		if(msj != "-1"){
			string str = msj;
			char delimiter = ' ';
			LinkedList<string>* internal = new LinkedList<string>();
			stringstream ss(str); // Turn the string into a stream.
			string tok;
			while(getline(ss, tok, delimiter)) {
				internal->insertTail(tok);
			}
			Node<string>* tmp = internal->getHead();
			msj=""+tmp->getData();
			tmp = tmp->getNext();
			for(int i=1; i<internal->getLength();i++){
				msj=msj+"#"+tmp->getData();
				tmp = tmp->getNext();
			}
			cout<<"enviar msj al disk Node: "<<msj<<endl;
			_Client->receiveMessage(msj);
		}

		//los mensajes con direccion: disk node >>>>>> usuario
		////_Client->getMessageReceived();

	}
	pthread_exit(NULL);
}

