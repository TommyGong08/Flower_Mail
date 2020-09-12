/*

author: 姜瑜

*/
#include"Login.h"
#include"Struct.h"
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

//判断输入的字符串
int CheckLoginInput(char* UserName, char* PsWd)
{

}

//将登陆的用户信息发送给服务器
int SendLoginUserInfoToServer(char* UserName , char* PsWd)
{

}

//客户端接受服务器返回的登陆指令，登陆成功在本地创建文件夹
int RecLoginResFromServer()
{

}

//登陆成功后创建本地文件夹
int CreaterUserFolder(char* UserName)
{

}

int CreateUserFolder(char *userName)
{

}