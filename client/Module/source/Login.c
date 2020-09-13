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

//用户登陆成功后创建文件夹,用于保存草稿
int CreateUserFolder(char *userID)
{
  char buffer[80];
	char dBuffer[85];//草稿箱路径
	char ABuffer[85];//附件存储

	memset(buffer, '\0', 80);
	memset(dBuffer, '\0', 105);
	memset(ABuffer,'\0',85);
	//获取执行程序当前路径
	getcwd(buffer, sizeof(buffer));
	//data文件夹
	sprintf(dBuffer, "../user/%s/draft", userID);
	sprintf(ABuffer,"../user/%s/attach",userID);
	
	//创建user/userID/draft 文件夹
	mkdir(dBuffer, 0755);
	mkdir(ABuffer,0755);

	return 0;
}


