/*
 * Server.cpp
 *
 *  Created on: May 30, 2015
 *      Author: abrahamon
 */

#include "../com.HARFS.NetworkAccess/Server.h"

int Server::_ListeningPort = 0;
LinkedList<string>* Server::_MessagesList =0;
pthread_mutex_t Server::mutex = PTHREAD_MUTEX_INITIALIZER;

Server::Server( int pPort) {
	_MessagesList = new LinkedList<string>();
	_ListeningPort = pPort;
	pthread_t hilo;
	pthread_create(&hilo,0,Server::threadListen,(void*)this);
}


/* A simple server in the internet domain using TCP
   El puerto es una variable de clase, se pasa como argumento */
void* Server::threadListen(void* pData){
	int sockfd, newsockfd;
	 socklen_t clilen;
	 char buffer[256];
	 struct sockaddr_in serv_addr, cli_addr;
	 int n;
	 sockfd = socket(AF_INET, SOCK_STREAM, 0);
	 if (sockfd < 0)
		error("ERROR opening socket");
	 bzero((char *) &serv_addr, sizeof(serv_addr));
	 serv_addr.sin_family = AF_INET;
	 serv_addr.sin_addr.s_addr = INADDR_ANY;
	 serv_addr.sin_port = htons(_ListeningPort);
	 if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
			  error("ERROR on binding");}
	 listen(sockfd,5);
	 clilen = sizeof(cli_addr);
	 newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
	 if (newsockfd < 0)
		 error("ERROR on accept");
	 while(true){
		sleep(0.2);

		bzero(buffer,256);
		n = read(newsockfd,buffer,255);
		if (n < 0)
		 error("ERROR reading from socket");
		string str = string(buffer);
		if(str.length()>2)

			pthread_mutex_lock(&mutex);
			_MessagesList->insertTail(str);
			pthread_mutex_unlock(&mutex);

	//		cout<<"Mensaje recibido::: "<<str<<endl;

		if( str.compare("CLOSE") == 2 && str.length() == 7){
			break;
		}
//		printf("Here is the message: %s\n",buffer);
		n = write(newsockfd,"Recibi tu mensaje\n ",18);
	//	if (n < 0)
	//	 error("ERROR writing to socket");

	}
	cout<<"Sesion del controller node terminada \n";
	close(newsockfd);
	close(sockfd);
	pthread_exit(NULL);
}

void Server::error(const char *msg)
{
    perror(msg);
    exit(1);
}

string Server::getFirstMessage(){
	pthread_mutex_lock(&mutex);
	if(_MessagesList->getLength()==0){
		pthread_mutex_unlock(&mutex);
		return "-1";
	}
	string ans = _MessagesList->getHead()->getData();
	_MessagesList->deleteData(ans);
	pthread_mutex_unlock(&mutex);
	return ans;
}
