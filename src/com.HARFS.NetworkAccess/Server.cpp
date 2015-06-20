/*
 * Server.cpp
 *
 *  Created on: May 30, 2015
 *      Author: abrahamon
 */

#include "../com.HARFS.NetworkAccess/Server.h"

int Server::_ListeningPort = 0;
LinkedList<string>* Server::_MensajesRecibidosDelUsuario =0;
LinkedList<string>* Server::_MensajesRecibidosDelDiskNode;
LinkedList<user*>* Server::_UserList;
pthread_mutex_t Server::mutex = PTHREAD_MUTEX_INITIALIZER;

Server::Server( int pPort) {
	_MensajesRecibidosDelUsuario = new LinkedList<string>();
	_MensajesRecibidosDelDiskNode = new LinkedList<string>();
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
	char buffer[256];
	bzero(buffer,256);
	string username, password;
	bool opc = true;
	while(true){
		write(newsockfd,"digite 'ingresar' O 'registrar' usuario \n",42);
		read(newsockfd,buffer,sizeof(buffer)-1);

		//string str(buffer);
		string str = Server::getWordIn(buffer);
		//string str(buffer, sizeof(buffer));
		bzero(buffer,256);
		if(str == "registrar"){
		//if(ans.compare("registrar") == 2){
			break;
		}
		else if(str == "ingresar"){
		//else if(ans.compare("ingresar") == 2){
			opc = false;
			break;
		}
	}


	if(opc == true){//recibir los nuevos datos
		write(newsockfd,"Ingrese su nuevo nombre de usuario: \n",38);
		read(newsockfd,buffer,sizeof(buffer)-1);
		username = getWordIn(buffer);
		//username =(string)buffer;
		bzero(buffer,256);
		write(newsockfd,"Ingrese su nueva contraseña: \n",32);
		read(newsockfd,buffer,sizeof(buffer)-1);
		//password =(string)buffer;
		password =getWordIn(buffer);
		bzero(buffer,256);
		write(newsockfd,"Vuelva a conectarse con sus nueva credencial \n",47);
		cout<<"user: "<<username<<"."<<endl;
		cout<<"password: "<<password<<"."<<endl;
		pthread_mutex_lock(&mutex);
		user* newUser = new user(username,password);
		_UserList->insertTail(newUser);
		pthread_mutex_unlock(&mutex);
		if(ControllerConstants::DEBUG=="true")
			cout<<"Server.receiveNewClient() 		Nuevo usuario: "<<username<<" pass: "<<password<<" creado \n";
		close(newsockfd);
		pthread_exit(NULL);
	}else{//validar las credenciales
		if(_UserList->getLength()==0){
			write(newsockfd,"No hay usuarios registrados \n",31);
			close(newsockfd);
			pthread_exit(NULL);
		}
		write(newsockfd,"Ingrese su nombre de usuario: \n",32);
		read(newsockfd,buffer,sizeof(buffer)-1);
		username = getWordIn(buffer);
		bzero(buffer,256);
		write(newsockfd,"Ingrese su contraseña: \n",25);
		read(newsockfd,buffer,sizeof(buffer)-1);
		password = getWordIn(buffer);;
		bzero(buffer,256);

		cout<<"user: "<<username<<"."<<endl;
		cout<<"password: "<<password<<"."<<endl;
		Node<user*>* tmp = _UserList->getHead();
		for(int i=0; i<_UserList->getLength();i++){
			if(!(tmp->getData()->SoyEste(username,password))){
				break;
			}
			if(tmp->getNext()==0){
				write(newsockfd,"Credenciales erroneas \n",24);
				close(newsockfd);
				pthread_exit(NULL);
			}
			tmp = tmp->getNext();
		}
		if(ControllerConstants::DEBUG =="true")
			cout<<"Login con exito de: VACIO!"<<endl;
		write(newsockfd,"Credenciales correctas \n",25);
		write(newsockfd,"--HELP para visualizar los comandos \n",38);
		//cout<<"usuario: "<<userName<<endl;
		//cout<<"pass: "<<password<<endl;
	}

	while(true){
		bzero(buffer,256);
		n = read(newsockfd,buffer,sizeof(buffer)-1);
		if (n < 0)
			error("ERROR reading from socket");
		string str = string(buffer);

		if( str.compare("CLOSE") == 2){
			break;
		}
		if(str.compare("--HELP")==2){
			write(newsockfd,"------------------AYUDA------------- \n",40);
			write(newsockfd,"1. csb + nombre + Tipo de Organizacion(LinkedList) + Tipo de Raid(NoRaid,Raid) \n",81);
			write(newsockfd,"2. lsb  \n",10);
			write(newsockfd,"3. bst + UID \n",15);
			write(newsockfd,"4. desb + Name:Type:Size + … + NameN:TypeN:SizeN \n",52);
			write(newsockfd,"5. ar  \n",9);
			write(newsockfd,"6. br  \n",9);
			write(newsockfd,"7. b + Clave De Busqueda + Columna \n",37);
			write(newsockfd,"8. or + Desplazamiento  \n",26);
			write(newsockfd,"9. CLOSE  \n",12);
		}
		else if(str.length() > 2 ){
			if(formatoCorrecto(str)){
				write(newsockfd,"Mensaje enviado correctamente \n",32);
				pthread_mutex_lock(&mutex);
				_MensajesRecibidosDelUsuario->insertTail(str);
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

	if(tmp->getData().compare("csb")==0){			//Creat storage block
		tmp = tmp->getNext()->getNext();
		if(internal->getLength() == 4 && tmp->getData().compare("LinkedList")==0 && ( tmp->getNext()->getData().compare("NoRaid") || tmp->getNext()->getData().compare("Raid")))
			ans = true;
	}
	else if(tmp->getData().compare("lsb")==0 && internal->getLength()==1){		//Listar Storage Block
			ans =true;
	}
	else if(tmp->getData().compare("bst")==0 && internal->getLength()==2){		//Borrar storage block
		ans =true;
	}
	else if(tmp->getData().compare("desb")==0 && internal->getLength()>1){		//definir esquema sobre el storage block
		ans =true;
	}
	else if(tmp->getData().compare("ar")==0 && internal->getLength()==1){		//Almacenar registro
		ans =true;
	}
	else if(tmp->getData().compare("br")==0 && internal->getLength()==1){		//Borrar registro
		ans =true;
	}
	else if(tmp->getData().compare("b")==0 && internal->getLength()==3){		//Buscar registro
		ans =true;
	}
	else if(tmp->getData().compare("or")==0 && internal->getLength()==2){		//Obtener registro
		ans =true;
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
	if(_MensajesRecibidosDelUsuario->getLength()==0){
		pthread_mutex_unlock(&mutex);
		return "-1";
	}
	string ans = _MensajesRecibidosDelUsuario->getHead()->getData();
	_MensajesRecibidosDelUsuario->deleteData(ans);
	pthread_mutex_unlock(&mutex);
	return ans;
}

string Server::getWordIn(char pData[]){
	std::string str="";
	int asciiValue;
	for(int i =0; i<=sizeof(pData);i++){
		asciiValue = pData[i];
		if (pData[i] != ' ' && pData[i] != '\t' && pData[i] != '\r' && pData[i] != '\n' && pData[i] != '\x0b' && asciiValue !=13 && asciiValue != 10){
			str= str+pData[i];
		}else{
			return str;
		}
	}
	return str;
}

LinkedList<string>* Server::getListOfWordsIn(char pData[]){
	LinkedList<string>* lista = new LinkedList<string>();

}




