#ifndef  SERVERINTERFACE_H
#define SERVERLIB_H

int Select(char*  Rescmd , char* buffer);

int Insert(char* Rescmd);

int Delete(char* Rescmd);

int Update(char* Rescmd);

int Delete(char* Rescmd);

int RecFile(char* Rescmd , int socket);

int SendFile(char* Rescmd ,int socket);

int RecAttachFile(char* Rescmd , int socket);

int RecSendAttachFile(char* Rescmd , int socket);


#endif