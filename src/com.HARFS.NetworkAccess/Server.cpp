/*
 * Server.cpp
 *
 *  Created on: May 30, 2015
 *      Author: abrahamon
 */

#include "../com.HARFS.NetworkAccess/Server.h"

int Server::_Port = 0;

Server::Server(int pPort) {
	_Port = pPort;
	pthread_t hilo;
	pthread_create(&hilo,0,Server::threadListen,(void*)this);
}

Server::~Server() {
}

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
	 serv_addr.sin_port = htons(_Port);
	 if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
			  error("ERROR on binding");}
	 listen(sockfd,5);
	 clilen = sizeof(cli_addr);
	 newsockfd = accept(sockfd,
				 (struct sockaddr *) &cli_addr,
				 &clilen);
	 if (newsockfd < 0)
		  error("ERROR on accept");

	while(true){
		sleep(0.5);

		bzero(buffer,256);
		n = read(newsockfd,buffer,255);
		if (n < 0)
		 error("ERROR reading from socket");
		string str = string(buffer);
		if(str.length()>2)
			cout<<"Mensaje recibido::: "<<str<<endl;

		if( str.compare("CLOSE") == 2 && str.length() == 7){
			break;
		}
//		printf("Here is the message: %s\n",buffer);
		n = write(newsockfd,"I got your message\n ",18);
	//	if (n < 0)
	//	 error("ERROR writing to socket");

	}
	cout<<"Sesion del controller node terminada \n";
	close(newsockfd);
	close(sockfd);
	pthread_exit(NULL);
}

void Server::conect(){
	int sockfd, newsockfd, portno;
			socklen_t clilen;
			char buffer[256];
			struct sockaddr_in serv_addr, cli_addr;
			int n;
			if (_Port< 2){
				fprintf(stderr,"ERROR, no port provided\n");
				exit(1);
			}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = _Port;
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd,
                 (struct sockaddr *) &cli_addr,
                 &clilen);
     if (newsockfd < 0)
          error("ERROR on accept");
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     if (n < 0)
    	 error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);
     n = write(newsockfd,"I got your message",18);
     if (n < 0)
    	 error("ERROR writing to socket");
     close(newsockfd);
     close(sockfd);
     return;
}

void Server::error(const char *msg)
{
    perror(msg);
    exit(1);
}
