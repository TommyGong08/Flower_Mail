#ifndef RECEIVEMODULE_H
#define RECEIRVEMODULE_H
#include "Struct.h"
#include"ClientSocket.h"
#define GET_MAIL_LIST 100

//收件箱模块
int ChangeEmailState(char * EmailID , int emailState);
int DeleteServerEmail(char * EmailID);
int GetServerEmail(char* UserID , char* GetMailList[GET_MAIL_LIST] , int &num);
int GetAttachEmail(char* EmailID);
int ReplyEmail(); //lqy负责

#endif