#ifndef RECEIVEMODULE_H
#define RECEIRVEMODULE_H
#include "Struct.h"
#include"ClientSocket.h"

//收件箱模块
int ChangeEmailState(char * EmailID,int EmailState);
int  DeleteServerEmail(char * EmailID);
int GetServerEmail(MailInfo* NewMail,char * UserID);
int GetAttanchEmail(char* EmailID);
int ReplyEmail();

#endif