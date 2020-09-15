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


/*
author        :		姜渝

function name :		CheckLoginInput

description   :		在客户端本地判断用户输入的帐号及密码是否合法,并弹出错误提示

Parameter     :		char *UserName,char* PsWd

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
//判断输入的字符串
int CheckLoginInput(char* UserName, char* PsWd)
{
// 用户名长度6-20位，由数字，字母，下划线组成，且不能以数字开头，字母不区分大小写。
	// 密码长度为6-20位，由数字，字母，下划线组成，且至少包含两种及以上字符，字母区分大小写。
	int iPasswdLength;
	int iUserIdLength;
	int i;
	iUserIdLength = strlen(UserName);
	iPasswdLength = strlen(PsWd);
	//遍历分析用户输入的用户名字符
	if (iUserIdLength < 6 || iUserIdLength > 20){
		return 1;//帐户ID非法
	}
	if (UserName[0] >= '0' && UserName[0] <= '9'){
		return -1;
	}
	for (i = 0; i < iUserIdLength; i++){
		if ((UserName[i] >= '0' && UserName[i] <= '9') || 
					(UserName[i] >= 'a' && UserName[i] <= 'z') || 
					(UserName[i] >= 'A' && UserName[i] <= 'Z') || 
					UserName[i] == '_'){
			continue;
		}else{
			return -1;
		}
	}
	//密码长度判断
	//设定密码长度为6-20
	if (iPasswdLength < 6 || iPasswdLength > 20){
		return -2;//密码非法
	}
	//遍历分析用户输入的密码字符
	int flag = 0; //记录字符种数
	int flag_num = 0;
	int flag_a = 0;
	int flag__ = 0;
	for (i = 0; i < iPasswdLength; i++)
	{
		if (PsWd[i] >= '0' && PsWd[i] <= '9')//数字
		{
			if (!flag_num) { flag += 1; }
			flag_num++;
			continue;
		}else if (PsWd[i] >= 'a' && PsWd[i] <= 'z')//小写字母
		{
			if (!flag_a) { flag += 1; }
			flag_a++;
			continue;
		}else if (PsWd[i] >= 'A' && PsWd[i] <= 'Z')//大写字母
		{
			if (!flag_a) { flag += 1; }
			flag_a++; //大小写字母都记作字母 flag_a计数
			continue;
		}else if (PsWd[i] == '_'){
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
	return 0;
}

//success
int SendLoginUserInfoToServer(char* UserName , char* PsWd)
{
	int sendResult1;//用户名密码匹配结果
	char buffer1[LONG_CONTENT_SIZE];
	char receBuffer[LONG_CONTENT_SIZE];
	memset(buffer1, '\0', LONG_CONTENT_SIZE);
	memset(receBuffer, '\0', LONG_CONTENT_SIZE);
	//数据库操作
	char event[10] = "select";//选择
	int isocketfd = 0;
	//查询用户名与密码是否匹配
	sprintf(buffer1, "loginselect|SELECT Passwd FROM UserTable WHERE UserID='%s' ",UserName);
  printf("%s\n",buffer1);
  isocketfd = connect_socket(SERVER_IP, SERVER_PORT);
	sendResult1 = send_msg(isocketfd, buffer1, LONG_CONTENT_SIZE);
	//发送失败
	if (sendResult1<0){
		return -1;
	}
  bzero(buffer1, BUFFER_SIZE);
	int length = 0;
  length = recv(isocketfd, buffer1, LONG_CONTENT_SIZE, 0);
	if(length < 0){
		printf("receive message failed!\n");
	}
  printf("%s\n",buffer1);
	printf("%s\n",PsWd);
	int close = 0;
	if(strcmp(buffer1,PsWd) == 0){
		printf("Login success!\n");
		return close;
	}
	close = close_socket(isocketfd);
	printf("%d\n",close);
	return -1;
}

//success
int SendLoginStateToServer(char* UserName)
{
		int sendResult1;//用户名密码匹配结果
	char buffer1[LONG_CONTENT_SIZE];
	char receBuffer[LONG_CONTENT_SIZE];
	memset(buffer1, '\0', LONG_CONTENT_SIZE);
	memset(receBuffer, '\0', LONG_CONTENT_SIZE);
	//数据库操作
	char event[10] = "select";//选择
	int isocketfd = 0;
	//查询用户名与密码是否匹配
	sprintf(buffer1, "loginstateselect|SELECT UserID, state FROM UserTable WHERE UserID='%s' ",UserName);
  printf("%s\n",buffer1);
  isocketfd = connect_socket(SERVER_IP, SERVER_PORT);
	sendResult1 = send_msg(isocketfd, buffer1, LONG_CONTENT_SIZE);
	//发送失败
	if (sendResult1<0){
		return -1;
	}
  bzero(buffer1, BUFFER_SIZE);
	int length = 0;
  length = recv(isocketfd, buffer1, LONG_CONTENT_SIZE, 0);
	if(length < 0){
		printf("receive message failed!\n");
		close_socket(isocketfd);
		return -1;
	}
  printf("%s\n",buffer1);
 if(strcmp(buffer1,"0") != 0){
	 	close_socket(isocketfd);
	 	return -1;//已登陆
 }
	close_socket(isocketfd);
//	printf("%d\n",close);
	return -1;
}

//success
//将退出信息发送给服务器
int  SendLoginOutInfoToServer(char* UserName , char* PsWd)
{
	int sendResult1;//用户名密码匹配结果
	char buffer1[LONG_CONTENT_SIZE];
	char receBuffer[LONG_CONTENT_SIZE];
	memset(buffer1, '\0', LONG_CONTENT_SIZE);
	memset(receBuffer, '\0', LONG_CONTENT_SIZE);
	//数据库操作
	char event[10] = "select";//选择
	int isocketfd = 0;
	//将state设置成1，表示用户为为登陆状态
	sprintf(buffer1, "logoutupdate|UPDATE UserTable SET state = '1' WHERE UserID='%s'",UserName);
  printf("%s\n",buffer1);
  isocketfd = connect_socket(SERVER_IP, SERVER_PORT);
	sendResult1 = send_msg(isocketfd, buffer1, LONG_CONTENT_SIZE);
	//发送失败
	if (sendResult1<0){
		return -1;
	}
	int length =0;
	length = recv(isocketfd, receBuffer, BUFFER_SIZE,0);
	int state = -1;
	//假设receBuffer格式如：1#
	printf("receive message: %s\n", receBuffer);
	if(receBuffer[0]=='0'){
		printf("Logout Success!\n");
	}else if(receBuffer[0]=='-'){
		printf("LogOut Failed!\n");
    return -1;
	}
	close_socket(isocketfd);
	return 0;
}

//创建文件夹函数,success
int MakeDirectory(const char* FileName)
{
	char DirName[256];
	strcpy(DirName,FileName);
	int i=0 ,len = strlen(DirName);
	for(int i=1;i<len;i++){
		if(DirName[i] == '/'){
			DirName[i]=0;
			if(access(DirName,0)!=0){
				if((mkdir(DirName,0755))==-1){
					printf("Problem creating directory : %s\n",FileName);
					return -1;
				}
			}
			DirName[i] = '/';
		}
	}
	printf("Directory was successfully created!\n");
	return 0;
}

//success
//用户登陆成功后创建两个文件夹，分别用于存放草稿和下载的附件
int CreateUserFolder(char *userID)
{
  char buffer[80];
	char draftbuffer[85];//草稿箱路径
	char attachbuffer[85];//附件存储

	memset(buffer, '\0', 80);
	memset(draftbuffer, '\0', 105);
	memset(attachbuffer,'\0',85);
	//data文件夹
	sprintf(draftbuffer, "../data/%s/draft", userID);
	sprintf(attachbuffer,"../data/%s/attach",userID);
	
	//创建user/userID/draft 文件夹
	int make_draftfile = MakeDirectory(draftbuffer);
	if(make_draftfile< 0){
			printf("make draft file failed\n!");
	}else{
		printf("make draft file success!");
	}
	MakeDirectory(attachbuffer);
	//mkdir(dbuffer, 0755);
	//mkdir(Abuffer,0755);
	return 0;
}


