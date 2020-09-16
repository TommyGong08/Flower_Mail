#ifndef REGISTER_H
#define REGISTER_H
#include "Struct.h"
#include"ClientSocket.h"

//检查注册信息是否合法
int CheckRegisterInput(char* UserName, char* Password,char* Telephone);

//将用户名信息拼接成符合SQL语句的字符串
int SendUserIdToServer(char* UserId);

//接受服务器发送给用户的指令
int RecUserIdResFromServer();

//把注册用户的所有信息发送给服务器
int SendRegisterUserInfoToServer(char* UserName,char* PassWord, char* LoginState,char* Telephone);

#endif