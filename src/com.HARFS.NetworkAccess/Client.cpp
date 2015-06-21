/*
 * Client.cpp
 *
 *  Created on: 6/6/2015
 *      Author: abraham
 */

#include "Client.h"

int Client::_SendPort = 0;
char* Client::_IP;
LinkedList<string>* Client::_MensajesParaDiskNode;
LinkedList<string>* Client::_MessagesListReceived;
pthread_mutex_t Client::mutex = PTHREAD_MUTEX_INITIALIZER;

Client::Client(char* pIP,int pPort) {
	_SendPort = pPort;
	_IP = pIP;
	_MensajesParaDiskNode = new LinkedList<string>();
	_MessagesListReceived= new LinkedList<string>();
	pthread_t hilo;
	pthread_create(&hilo,0,Client::threadSendToPort,(void*)this);
}

void* Client::threadSendToPort(void* pData){
	int sockfd, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[256];
	char bufferRecibir[256];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	server = gethostbyname(_IP);
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
		 (char *)&serv_addr.sin_addr.s_addr,
		 server->h_length);
	serv_addr.sin_port = htons(_SendPort);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
		error("ERROR connecting");
	while(true){
		bzero(buffer,256);
		bzero(bufferRecibir,256);
		pthread_mutex_lock(&mutex);
		while(_MensajesParaDiskNode->getLength()!=0){
			char *cstr = _MensajesParaDiskNode->getHead()->getData().c_str();
			write(sockfd, cstr ,strlen(cstr));
			cout<<"El mensaje enviado fue: "<<_MensajesParaDiskNode->getHead()->getData()<<"\n";
			_MensajesParaDiskNode->deleteData(_MensajesParaDiskNode->getHead()->getData());
			//read(sockfd,bufferRecibir,sizeof(bufferRecibir)-1);
			//_MessagesListReceived->insertTail((string)bufferRecibir);
			//bzero(bufferRecibir,256);
		}
		pthread_mutex_unlock(&mutex);
		bzero(buffer,256);
	}
	close(sockfd);
	pthread_exit(NULL);
}

void Client::error(const char *msg)
{
    perror(msg);
    exit(1);
}

string Client::getMessageReceived(){
	pthread_mutex_lock(&mutex);
	string ans = _MessagesListReceived->getHead()->getData();
	_MessagesListReceived->deleteData(ans);
	pthread_mutex_unlock(&mutex);
	return ans;
}

void Client::receiveMessage(string pMsj){
	pthread_mutex_lock(&mutex);
	_MensajesParaDiskNode->insertTail(pMsj);
	pthread_mutex_unlock(&mutex);
}
