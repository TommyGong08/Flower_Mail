/*

author：龚海龙

*/
#include"Struct.h"
#include"ReceiveModule.h"
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
#define GET_MAIL_LIST 100

int ChangeEmailState(char* emailID ,int emailState)
{
  char buffer[BUFFER_SIZE]={0};
	int length=0;
  int client_socket=0;
  if(emailID == NULL){
		return -1;//
  }
	client_socket = connect_socket(SERVER_IP,SERVER_PORT);
	sprintf(buffer,"update|update EmailTable set state=%d where EmailID=%s",emailState,emailID);
	printf ("send message to server:%s\n",buffer);
	if(send_msg(client_socket,buffer,BUFFER_SIZE)<0){
		return -2;
  }
  bzero (buffer, BUFFER_SIZE);
  length = recv_msg(client_socket,buffer,BUFFER_SIZE);
  if(length<0){
    printf("can't receive message from server!\n");
  }else{
    	printf("receive message from server: %s \n",buffer);
  }
  close_socket(client_socket);
  return length;  
}

int DeleteServerEmail(char* emailID)
{
  char buffer[BUFFER_SIZE]={0};
	int length=0;
  int client_socket=0;
  if(emailID == NULL){
		return -1;
  }
	client_socket = connect_socket(SERVER_IP,SERVER_PORT);
	sprintf(buffer,"delete|delete  from EmailTable where EmailID = %s",emailID);
	printf ("send message to server:%s\n",buffer);
	if(send_msg(client_socket,buffer,BUFFER_SIZE)<0){
		return -2;
  }
  bzero(buffer, BUFFER_SIZE);
  length = recv_msg(client_socket,buffer,BUFFER_SIZE);
  if(length<0){
    printf("can't receive message from server!\n");
  }else{
    	printf("receive message from server: %s\n",buffer);
  }
  close_socket(client_socket);
  return length;  
}

//点击“打开附件”下载附件
int DownloadAttachEmail(char* EmailID) 
{
  
}

//从服务器获取邮件
int GetServerEmail(char* UserID , char* GetMailList[GET_MAIL_LIST] , int num)//num为
{
//需要获取附件
}

//跳转到写信界面后
int ReplyEmail()
{
  
} //lsy负责