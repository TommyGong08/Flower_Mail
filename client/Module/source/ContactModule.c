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

/*解析通讯录字符串
字符串以“|”分隔开
int StringDisintergrate(char* string )
{
  
}
*/

//获得通讯录信息
char*  GetContactInfo(char* UserID)
{
  char buffer[BUFFER_SIZE]={0};
	int length=0;
	char* text_pointer;
  int client_socket=0;
  if(UserID == NULL ){
	printf("UserID is NULL!");
  }
	sprintf(buffer,"getcontactinfo|%s",UserID);
//	strcpy(text,"FriendID1|FriendID2|FriendID3");
	printf ("send message to server: %s\n",buffer);
	client_socket = connect_socket(SERVER_IP,SERVER_PORT);
	if(send_msg(client_socket,buffer,BUFFER_SIZE)<0){
  }
  bzero (buffer, BUFFER_SIZE);
  length = recv_msg(client_socket,buffer,BUFFER_SIZE);
  if(length<0){
    printf("can't receive message from server!\n");
  }else{
    printf("receive message from server: %s \n",buffer);
    //解析字符串buffer   ：  以“Tom|Mary|Jack|”的方式分隔开
		 text_pointer = buffer;
   /* int IfDisintergrate = StringDisintergrate(buffer);
    if(IfDisintergrate < 0){
      printf("Disintergrate Failed!\n");
    }
		*/
  }
  close_socket(client_socket);
  return text_pointer;
}

//添加通讯录好友
int AddContact(char* UserID , char* FriendID)
{
  char buffer[BUFFER_SIZE]={0};
	int length=0;
  int client_socket=0;
  if(UserID == NULL ){
		return -1;
  }
	sprintf(buffer,"contactinsert|INSERT INTO Contact Table(UserID,FriendID )VALUES('%s','%s')",UserID,FriendID);
	printf ("%s\n",buffer);
	client_socket = connect_socket(SERVER_IP,SERVER_PORT);
	if(send_msg(client_socket,buffer,BUFFER_SIZE)<0){
		return -2;
  }
  bzero (buffer, BUFFER_SIZE);
  length = recv_msg(client_socket,buffer,BUFFER_SIZE);
  if(length<0){
    printf("can't receive message from server!\n");
    return -1;
  }else{
    	printf("receive message from server: %s \n",buffer);
  }
  close_socket(client_socket);
  return 0;  
}

//删除通讯录好友
int DeleteContact (char* UserID,char* FriendID)
{
  char buffer[BUFFER_SIZE]={0};
	int length=0;
  int client_socket=0;
  if(UserID == NULL ){
		return -1;
  }
	sprintf(buffer,"contactdelete|DELETE FROM Contact Table WHERE UserId = '%s' and FriendID = '%s'",UserID,FriendID);
	printf ("send message to server:%s\n",buffer);
	client_socket = connect_socket(SERVER_IP,SERVER_PORT);
	if(send_msg(client_socket,buffer,BUFFER_SIZE)<0){
		return -1;
  }
  bzero (buffer, BUFFER_SIZE);
  length = recv_msg(client_socket,buffer,BUFFER_SIZE);
  if(length<0){
    printf("can't receive message from server!\n");
    return -1;
  }else{
    	printf("receive message from server: %s \n",buffer);
  }
  close_socket(client_socket);
  return 0;  
}