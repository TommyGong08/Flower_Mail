#ifndef  CONTACTMODULE_H
#define  CONTACTMODUEL_H
#define CONTACT_SIZE 100 // 100个好友
#include"ClientSocket.h"

int GetContactInfo(char * UserID,char* text);//text 为传入的字符串
int AddContact (char* UserID , char* ContactID);
int DeleteContact (char* UserID,int ContactID);

#endif