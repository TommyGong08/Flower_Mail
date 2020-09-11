#ifndef  CONTACTMODULE_H
#define  CONTACTMODUEL_H
#include"ClientSocket.h"

int GetContactInfo(char * UserID, char *pacContact[50], int *item);
int AddContact (char * UserID,char * ContactID);
int DeleteContact (char * UserID,int ContactID);

#endif
