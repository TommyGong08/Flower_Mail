/*

author：姜瑜

*/
#include"Struct.h"
#include"Register.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <netinet/in.h>         // for sockaddr_in
#include <sys/types.h>          // for socket
#include <sys/socket.h>         // for socket
#include <string.h> 
#include <sys/stat.h>
#include <malloc.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

//检查注册信息是否合法
int CheckRegisterInput(UserInfo* userInfo)
{

}

//将用户名信息拼接成符合SQL语句的字符串
int SendUserIdToServer(char* UserId)
{

}

//接受服务器发送给用户的指令
int RecUserIdResFromServer()
{

}

//把注册用户的所有信息发送给服务器
int SendRegisterUserInfoToServer(UserInfo* userInfo)
{

}

//接受服务器返回的注册消息
int RecvRegisterResFromServer()
{

}