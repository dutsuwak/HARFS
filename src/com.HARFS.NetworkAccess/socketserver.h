#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <unistd.h>


using namespace std;

struct dataSocket{
    int descriptor;
    sockaddr_in info;
};

class SocketServer
{
public:
    SocketServer(int pPort);
    static void* run(void* pData);
    void setMensaje(const char *msn);
private:
    static int _Port;
    static int descriptor;
    static sockaddr_in info;
    static vector<int> clientes;
    static bool crear_Socket();
    static bool ligar_kernel();
    static void * controladorCliente(void *obj);

};

#endif // SOCKETSERVER_H
