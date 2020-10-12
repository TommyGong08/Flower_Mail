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
#include <QDebug>


//success
int CheckRegisterInput(char* UserName, char* Password,char* Telephone)
{
    int i;
	int iUserIDLength = strlen(UserName);
	int iPasswdLength = strlen(Password);
    //int iTeleLength = strlen(Telephone);
	if (iUserIDLength < 6 || iUserIDLength > 20){
		return 1;//帐户ID非法
	}
    qDebug()<<"hello5";
	if (UserName[0] >= '0' && UserName[0] <= '9'){
		return 1;
	}
	for (i=0; i < iUserIDLength; i++){
		if ((UserName[i] >= '0' && UserName[i] <= '9') || (UserName[i] >= 'a' && UserName[i] <= 'z') || (UserName[i] >= 'A' &&UserName[i] <= 'Z') || UserName[i] == '_')
		{
			continue;
		}else{
			return 1;
		}
	}
	//密码长度判断
	//设定密码长度为6-20
	if (iPasswdLength < 6 || iPasswdLength > 20)
	{
		return 2;//密码非法
	}
	//遍历分析用户输入的密码字符
	int flag = 0; //记录字符种数
	int flag_num = 0;
	int flag_a = 0;
	int flag__ = 0;
	for (i = 0; i < iPasswdLength; i++)
	{
		if (Password[i] >= '0' &&Password[i] <= '9')//数字
    {
			if (!flag_num){ flag += 1; }
			flag_num++;
			continue;
	}else if (Password[i] >= 'a' && Password[i] <= 'z')//小写字母
	{
			if (!flag_a) { flag += 1; }
			flag_a++;
			continue;
		}else if (Password[i] >= 'A' && Password[i] <= 'Z')//大写字母
		{
			if (!flag_a) { flag += 1; }
			flag_a++; //大小写字母都记作字母 flag_a计数
			continue;
		}else if (Password[i] == '_'){
			if (!flag__) { flag += 1; }
			flag__++;
			continue;
		}else{
			return -2; //密码不合法
		}
	}
	if (flag < 2){
		return -2; //密码不合法
	}
	return 0;//注册信息合法
}

//success
int SendUserIdToServer(char* UserId)
{
 int client_socket=0;  
  int length = 0;
	char buffer[LONG_CONTENT_SIZE];
	memset(buffer, '\0', LONG_CONTENT_SIZE);
  int iresocketfd = 0;
	sprintf(buffer, "registerselect|SELECT UserID FROM UserTable WHERE UserID = '%s'", UserId);
  //registerselect|SELECT UserID FROM UserTable WHERE UserID = 'aw'
  qDebug()<<buffer;
	iresocketfd = connect_socket(SERVER_IP, SERVER_PORT);
  if(iresocketfd < 0){
    qDebug()<<"client connect failed!\n";
    return -1;
  }else qDebug()<<"client connect success!\n";
	client_socket = send_msg(iresocketfd, buffer, LONG_CONTENT_SIZE);
	if (client_socket < 0){
   qDebug()<<"client send message failed!\n";
		return -1;//调用socket失败
	}else{
    qDebug()<<"client send message success!\n";
  }
  bzero(buffer, LONG_CONTENT_SIZE);
  length = recv(iresocketfd, buffer, LONG_CONTENT_SIZE, 0);
  qDebug()<<buffer;
  qDebug()<<length;
 // length = recv_msg(client_socket,buffer,BUFFER_SIZE);
  if(length<0){
    qDebug()<<"can't receive message from server!\n";
        close_socket(iresocketfd);
    return -1;
  }else printf("client receive message success!\n");
  if(strcmp(buffer,"-1") == 0){//exist
      //close_socket(client_socket);
      qDebug()<<"jasf";
    return -1;
  }
  //close_socket(client_socket);
    qDebug()<<"jasfgrsrgd";
	return 0;//发送成功，跳转到登陆页面
}

//success
//把注册用户的所有信息发送给服务器
int SendRegisterUserInfoToServer(char* UserName,char* PassWord, int LoginState,char* Telephone)
{
  int sendResult;
	char buffer[LONG_CONTENT_SIZE];
  int iresocketfd = 0;
  int length = 0;
	memset(buffer, '\0', LONG_CONTENT_SIZE);
	sprintf(buffer, "registerinsert|%s|%s|%d|%s|",UserName,PassWord, LoginState, Telephone);
 // registerinsert|TommyGong08|432784hjgf|0|13667584563|
  printf("%s\n",buffer);
	iresocketfd = connect_socket(SERVER_IP, SERVER_PORT);
  if(iresocketfd < 0){
    printf("connect failed!\n");
  }else printf("connected success!\n");
	sendResult = send_msg(iresocketfd, buffer, LONG_CONTENT_SIZE);
	if (sendResult <0)	{
		close_socket(iresocketfd);
		return -1;//调用socket失败
	}
  bzero(buffer, BUFFER_SIZE);
  length = recv(iresocketfd, buffer, LONG_CONTENT_SIZE, 0);
  printf("%s\n",buffer);
  //sendResult = send_msg(iresocketfd, buffer, LONG_CONTENT_SIZE);
  if(length<0){
    printf("can't receive message from server!\n");
		close_socket(iresocketfd);
    return -1;
  }
  if(strcmp(buffer,"-1") == 0){//返回查询失败
	close_socket(iresocketfd);
    return -1;
  }
    close_socket(iresocketfd);
		return 0;
}
