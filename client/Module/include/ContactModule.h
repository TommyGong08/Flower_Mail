#ifndef  CONTACTMODULE_H
#define  CONTACTMODUEL_H
#define CONTACT_SIZE 100 // 100个好友
#include"ClientSocket.h"
#include"Struct.h"

char*  GetContactInfo(char* UserID);
int AddContact (char* UserID , char* ContactID);
int DeleteContact (char* UserID,char* FriendID);

#endif