/*
 * Server.cpp
 *
 *  Created on: May 30, 2015
 *      Author: abrahamon
 */

#include "../com.HARFS.NetworkAccess/Server.h"

int Server::_ListeningPort = 0;
LinkedList<string>* Server::_MessagesList =0;
LinkedList<user*>* Server::_UserList;
pthread_mutex_t Server::mutex = PTHREAD_MUTEX_INITIALIZER;

Server::Server( int pPort) {
	_MessagesList = new LinkedList<string>();
	_UserList = new LinkedList<user*>();
	_ListeningPort = pPort;
	pthread_t hilo;
	pthread_create(&hilo,0,Server::threadListen,(void*)this);
}


/* A simple server in the internet domain using TCP
   El puerto es una variable de clase, se pasa como argumento */
void* Server::threadListen(void* pData){
	int sockfd, newsockfd;
	 socklen_t clilen;
	 //char buffer[256];int n;
	 struct sockaddr_in serv_addr, cli_addr;
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

void* Server::receiveNewClient(void* pNewsockfd){
	int newsockfd = pNewsockfd;
	if(ControllerConstants::DEBUG == "true")
		cout<<"Server.receiveNewClient()		 Nuevo cliente se ha conectado\n";
	int n;
	char buffer[256], userName[128], password[128];
	bzero(buffer,256);
	bzero(userName,128);
	bzero(password,128);
	string ans="";
	bool opc = true;
	while(true){
		write(newsockfd,"digite 'INGRESAR' O 'REGISTRAR' \n",34);
		read(newsockfd,buffer,sizeof(buffer)-1);
		ans = string(buffer);
		if(ans.compare("REGISTRAR") == 2)
			break;
		if(ans.compare("INGRESAR") == 2){
			opc = false;
			break;
		}
		bzero(buffer,256);
	}


	if(opc == true){//recibir los nuevos datos
		write(newsockfd,"Ingrese su nombre de usuario: \n",32);
		read(newsockfd,userName,sizeof(userName)-1);
		write(newsockfd,"Ingrese su contraseña: \n",sizeof("Ingrese su contraseña: \n"));
		read(newsockfd,password,sizeof(password)-1);
		write(newsockfd,"Vuelva a conectarse con sus nueva credencial\n",sizeof("Vuelva a conectarse con sus nueva credencial\n"));
		pthread_mutex_lock(&mutex);
		user* newUser = new user(string(userName),(string)(password));
		_UserList->insertTail(newUser);
		pthread_mutex_unlock(&mutex);
		if(ControllerConstants::DEBUG=="true")
		cout<<"Server.receiveNewClient() 		Nuevo usuario '"<<(string)userName;
		close(newsockfd);
		pthread_exit(NULL);
	}else{//validar las credenciales

		write(newsockfd,"Ingrese su nombre de usuario: \n",32);
		read(newsockfd,userName,128);
		write(newsockfd,"Ingrese su contraseña: \n",25);
		read(newsockfd,password,128);

		if(_UserList->getLength()==0){
			write(newsockfd,"No hay usuarios registrados \n",32);
			close(newsockfd);
			pthread_exit(NULL);
		}
		Node<user*>* tmp = _UserList->getHead();
		for(int i=0; i<_UserList->getLength();i++){
			if(!(tmp->getData()->SoyEste(userName,password))){
				write(newsockfd,"Credenciales erroneas \n",25);
				close(newsockfd);
				pthread_exit(NULL);
			}
			tmp = tmp->getNext();
		}
		if(ControllerConstants::DEBUG =="true")
			cout<<"Login con exito de: "<<userName<<endl;
		write(newsockfd,"Credenciales correctas \n",25);
		write(newsockfd,"--HELP para visualizar los comandos \n",38);
		//cout<<"usuario: "<<userName<<endl;
		//cout<<"pass: "<<password<<endl;
	}

	while(true){
		bzero(buffer,256);
		n = read(newsockfd,buffer,255);
		if (n < 0)
			error("ERROR reading from socket");
		string str = string(buffer);

		if( str.compare("CLOSE") == 2){
			break;
		}
		if(str.compare("--HELP")==2){
			write(newsockfd,"------------------AYUDA------------- \n",40);
			write(newsockfd,"1. CSB + nombre + Tipo de Organizacion(LinkedList) + Tipo de Raid(NoRaid,Raid) \n",81);
			write(newsockfd,"2. LSB  \n",10);
			write(newsockfd,"3. BST + UID \n",15);
			write(newsockfd,"4. DESB + Name:Type:Size + … + NameN:TypeN:SizeN \n",52);
			write(newsockfd,"5. AR  \n",9);
			write(newsockfd,"6. BR  \n",9);
			write(newsockfd,"7. B + Clave De Busqueda + Columna \n",37);
			write(newsockfd,"8. OR + Desplazamiento  \n",26);
			write(newsockfd,"9. CLOSE  \n",12);
		}
		else if(str.length()>2 ){
			if(formatoCorrecto(str)){
				write(newsockfd,"Mensaje enviado correctamente \n",32);
				pthread_mutex_lock(&mutex);
				_MessagesList->insertTail(str);
				pthread_mutex_unlock(&mutex);
			}else{
				write(newsockfd,"Comando desconocido \n",21);
			}
		}

	}
	cout<<"Server.receiveNewClient() 		Sesion del cliente terminada \n";
	close(newsockfd);
	pthread_exit(NULL);
}

bool Server::formatoCorrecto(string pCommand){
	bool ans = false;

	string str = pCommand;
	char delimiter = ' ';
	LinkedList<string>* internal = new LinkedList<string>();
	stringstream ss(str); // Turn the string into a stream.
	string tok;
	while(getline(ss, tok, delimiter)) {
		//internal.push_back(tok);
		internal->insertTail(tok);
	}
	Node<string>* tmp = internal->getHead();

	cout<<"comando: "<<pCommand<<endl;
	cout<<"Largo del comando: "<<internal->getLength()<<endl;
	cout<<"head dato: "<<tmp->getData()<<endl;
	if(internal->getLength() == 4 && tmp->getData()=="CSB"){
		tmp = tmp->getNext()->getNext();
		if(tmp->getData()=="LinkedList" && (tmp->getNext()->getData()=="NoRaid"||tmp->getNext()->getData()=="Raid"))
		ans = true;
	}

	return ans;
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
