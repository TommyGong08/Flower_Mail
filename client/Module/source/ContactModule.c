/*
author：龚海龙
*/
#include"ContactModule.h"
#include"Struct.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <netinet/in.h>         
#include <sys/types.h>         
#include <sys/socket.h>       
#include <string.h> 
#include <sys/stat.h>
#include <malloc.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

//解析通讯录字符串
int StringDisintergrate(char* string)
{
  
}

//获得通讯录信息
int GetContactInfo(char * UserID)
{
  char buffer[BUFFER_SIZE]={0};
	int length=0;
  int client_socket=0;
  if(UserID == NULL ){
		return -1;
  }
	client_socket = connect_socket(SERVER_IP,SERVER_PORT);
	sprintf(buffer,"GetContactInfo|%s",UserID);
	printf ("send message to server: %s\n",buffer);
	if(send_msg(client_socket,buffer,BUFFER_SIZE)<0){
		return -2;
  }
  bzero (buffer, BUFFER_SIZE);
  length = recv_msg(client_socket,buffer,BUFFER_SIZE);
  if(length<0){
    printf("can't receive message from server!\n");
  }else{
    printf("receive message from server: %s \n",buffer);
    //解析字符串buffer   ：  以“Tom|Mary|Jack|”的方式分隔开
    int IfDisintergrate = StringDisintergrate(buffer);
    if(IfDisintergrate < 0){
      printf("Disintergrate Failed!\n");
    }
  }
  close_socket(client_socket);
  return length;
}

int AddContact (char* UserID , char* FriendID)
{
  char buffer[BUFFER_SIZE]={0};
	int length=0;
  int client_socket=0;
  if(UserID == NULL ){
		return -1;
  }
	client_socket = connect_socket(SERVER_IP,SERVER_PORT);
	sprintf(buffer,"insert|Insert into ContactTable(UserID,FriendID )values('%s','%s')",UserID,FriendID);
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

int DeleteContact (char* UserID,int FriendID)
{
  char buffer[BUFFER_SIZE]={0};
	int length=0;
  int client_socket=0;
  if(UserID == NULL ){
		return -1;
  }
	client_socket = connect_socket(SERVER_IP,SERVER_PORT);
	sprintf(buffer,"delete|delete from UserTable Where UserId = '%s' and FriendID = '%s'",UserID,FriendID);
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