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


/*
author        :		姜渝

function name :		CheckRegisterInput

description   :		本地检查注册信息，判断用户输入的帐号及密码是否合法,并弹出错误提示

Parameter     :		UserInfo* userInfo

return value  :		0 成功
					1 帐户ID非法
						Checkresult（string）输出错误提示
						1） 用户名长度不对
						2） 用户名首位为数字
						3） 用户名包含非法字符
					2 密码非法
						1） 密码长度不对
						2） 密码包含非法字符
						3） 密码不包含两种字符
*/
int CheckRegisterInput(UserInfo* userInfo)
{
	int i;
	int iUserIDLength = strlen(userInfo->UserName);
	int iPasswdLength = strlen(userInfo->Password);
	int iTeleLength = strlen(userInfo->Telephone);
	if (iUserIDLength < 6 || iUserIDLength > 20){
		return 1;//帐户ID非法
	}
	if (userInfo->UserName[0] >= '0' && userInfo->UserName[0] <= '9'){
		return 1;
	}
	for (i=0; i < iUserIDLength; i++){
		if ((userInfo->UserName[i] >= '0' && userInfo->UserName[i] <= '9') || (userInfo->UserName[i] >= 'a' && userInfo->UserName[i] <= 'z') || (userInfo->UserName[i] >= 'A' && userInfo->UserName[i] <= 'Z') || userInfo->UserName[i] == '_')
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
		if (userInfo->Password[i] >= '0' && userInfo->Password[i] <= '9')//数字
    {
			if (!flag_num){ flag += 1; }
			flag_num++;
			continue;
	}else if (userInfo->Password[i] >= 'a' && userInfo->Password[i] <= 'z')//小写字母
	{
			if (!flag_a) { flag += 1; }
			flag_a++;
			continue;
		}else if (userInfo->Password[i] >= 'A' && userInfo->Password[i] <= 'Z')//大写字母
		{
			if (!flag_a) { flag += 1; }
			flag_a++; //大小写字母都记作字母 flag_a计数
			continue;
		}else if (userInfo->Password[i] == '_'){
			if (!flag__) { flag += 1; }
			flag__++;
			continue;
		}else{
			return -2; //密码不合法
		}
	}
	if (flag < 2){
		return 2; //密码不合法
	}
	return 0;//注册信息合法
}

/*
author        :		姜渝

function name :		SendUserInfoToServer

description   :		将用户名拼接成符合SQL语句的字符串，调用socket函数发送字符串到服务器

Parameter     :		char* UserId

return value  :		0 发送成功
					-1 调用socket失败

*/
int SendUserIdToServer(char* UserId)
{
 int client_socket=0;  
	int i;
  int length = 0;
	char buffer[LONG_CONTENT_SIZE];
	memset(buffer, '\0', LONG_CONTENT_SIZE);
  int iresocketfd = 0;
	sprintf(buffer, "select|SELECT UserID FROM UserTable WHERE UserID='%s'", UserId);
	iresocketfd = connect_socket(SERVER_IP, SERVER_PORT);
	client_socket = send_msg(iresocketfd, buffer, LONG_CONTENT_SIZE);
	if (client_socket < 0){
		return -1;//调用socket失败
	}
  bzero(buffer, BUFFER_SIZE);
  length = recv_msg(client_socket,buffer,BUFFER_SIZE);
  if(length<0){
    printf("can't receive message from server!\n");
    return -1;
  }
  int num = buffer -'0';
  if(num < 0){//返回查询失败
    return -1;
  }
  close_socket(client_socket);
	return 0;//发送成功，跳转到登陆页面
}

//把注册用户的所有信息发送给服务器
int SendRegisterUserInfoToServer(UserInfo* userInfo)
{
  int sendResult;
	char buffer[LONG_CONTENT_SIZE];
  int iresocketfd = 0;
  int length = 0;
	memset(buffer, '\0', LONG_CONTENT_SIZE);
	sprintf(buffer, "insert|INSERT INTO UserTable(UserID, Passwd, state, Telephone) VALUES ('%s','%s',%d, '%s')", userInfo->UserName, userInfo->Password, userInfo->LoginState, userInfo->Telephone);
	iresocketfd = connect_socket(SERVER_IP, SERVER_PORT);
	sendResult = send_msg(iresocketfd, buffer, LONG_CONTENT_SIZE);
	if (sendResult <0)	{
		return -1;//调用socket失败
	}
   bzero(buffer, BUFFER_SIZE);
  length = recv_msg(iresocketfd,buffer,BUFFER_SIZE);//返回0表示查询成功，数据库中存在相应字段
  if(length<0){
    printf("can't receive message from server!\n");
    return -1;
  }
  int num = buffer -'0';
  if(num < 0){//返回查询失败
    return -1;
  }
  close_socket(iresocketfd);
  return 0;

		return 0;
}