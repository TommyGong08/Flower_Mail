#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#ifdef __cplusplus
extern "C" {
#endif
int connect_socket(char* server,int);
int send_msg(int socket,char* sendBuff,int length);
//int recv_msg(int socket,char* buffer,int bufflength);
int close_socket(int socket);
 #ifdef __cplusplus
}
#endif

#include "Struct.h"

#endif
