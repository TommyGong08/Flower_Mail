#ifndef  MYSQLLIB_H
#define MYSQLLIB_H

#include "mysql.h"
#include <stdio.h>
#include <stdlib.h>


int OpenSql( char* Host ,char* User , char* PsdWd , char* DbName);

int InsertSql(char * sqltext);

int DeleteSql(char* sqltext);

int UpdateSql(char* sqltext);

int SelectSql(char* sqltext);

void FreeResult();

void CloseSql();

#endif


