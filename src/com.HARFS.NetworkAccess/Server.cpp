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
	 while(true){
		 newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
	 	 if (newsockfd < 0)
		 	 error("ERROR on accept");
		 pthread_t hiloNuevoCliente;
		 pthread_create(&hiloNuevoCliente,0,Server::receiveNewClient,(void*)newsockfd);
	 }

	close(sockfd);
	pthread_exit(NULL);
}

void* Server::receiveNewClient(void* newsockfd){
	sleep(0.2);
	if(ControllerConstants::DEBUG == "true")
		cout<<"Server.receiveNewClient()		 Nuevo cliente se ha conectado\n";
	int n;
	char buffer[256], userName[128], password[128];
	bzero(buffer,256);
	bzero(userName,128);
	bzero(password,128);

	n=write(newsockfd,"-------------Bienvenido------------- \n",41);
	n=write(newsockfd,"digite (L) para ingresar (R) para registrarse \n",48);
	n=read(newsockfd,buffer,1);

	//string opcion = string(buffer);
	//int a = opcion.compare("R")==0;

	if(strcmp ("R",buffer) == 0){//recibir los nuevos datos
		read(newsockfd,buffer,128);
		write(newsockfd,"Ingrese su nombre de usuario: \n",33);
		read(newsockfd,userName,128);
		write(newsockfd,"Ingrese su contraseña: \n",25);
		read(newsockfd,password,128);
		write(newsockfd,"Vuelva a conectarse con sus nueva credencial\n",45);
//		pthread_mutex_lock(&mutex);
		//{"records":[{"time":"0"}]}  Formato Json
		//_UserList->insertTail(string(userName)+string(password));
		//_MessagesList->insertTail("{\"Accion\":\""+opcion+"\",\"Usuario\":\""+string(userName)+"\",\"Contrasena\":\""+string(password))+"\"}"; //mensaje en formato jSon
//		pthread_mutex_unlock(&mutex);
		if(ControllerConstants::DEBUG=="true")
		cout<<"Server.receiveNewClient() 		Nuevo usuario creado\n";
		close(newsockfd);
		pthread_exit(NULL);
	}else{//validar las credenciales
		n=read(newsockfd,buffer,128);
		n=write(newsockfd,"Ingrese su nombre de usuario: \n",33);
		n=read(newsockfd,userName,128);
		n=write(newsockfd,"Ingrese su contraseña: \n",25);
		n=read(newsockfd,password,128);

		cout<<"usuario: "<<userName<<endl;
		cout<<"pass: "<<password<<endl;
	}

	while(true){
		bzero(buffer,256);
		n = read(newsockfd,buffer,255);
		if (n < 0)
			error("ERROR reading from socket");
		string str = string(buffer);


		pthread_mutex_lock(&mutex);
		_MessagesList->insertTail(str);
		pthread_mutex_unlock(&mutex);

		if(str.length()>2)
			cout<<"Mensaje recibido::: "<<str<<endl;

		if( str.compare("CLOSE") == 2){
			break;
		}
//		if( str.compare("CLOSE") == 2 && str.length() == 7){
//			break;
//		}
		//	printf("Here is the message: %s\n",buffer);
		//	n = write(newsockfd,"Recibi tu mensaje\n ",18);
		//	if (n < 0)
		//	 error("ERROR writing to socket");

	}
	cout<<"Server.receiveNewClient() 		Sesion del cliente terminada \n";
	close(newsockfd);

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
