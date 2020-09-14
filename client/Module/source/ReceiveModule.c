/*

author：龚海龙

*/
#include"Struct.h"
#include"ReceiveModule.h"
#include"WriteModule.h"
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

/*分割“UserID|EmailTheme|state|邮件内容～”
int GetServerStringDisintergrate(char* string)
{

}*/

int ChangeEmailState(char* emailID ,int emailState)
{
  char buffer[BUFFER_SIZE]={0};
	int length=0;
  int client_socket=0;
  if(emailID == NULL){
		return -1;//
  }
	client_socket = connect_socket(SERVER_IP,SERVER_PORT);
	sprintf(buffer,"update|UPDATE EmailTable SET state=%d WHERE EmailID=%s",emailState,emailID);
	printf ("send message to server:%s\n",buffer);
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

//删除数据库及服务器本地的邮件信息
int DeleteServerEmail(char* emailID)
{
  char buffer[BUFFER_SIZE]={0};
	int length=0;
  int client_socket=0;
  if(emailID == NULL){
		return -1;
  }
	client_socket = connect_socket(SERVER_IP,SERVER_PORT);
	sprintf(buffer,"Delete|%s",emailID);
	printf ("send message to server:%s\n",buffer);
	if(send_msg(client_socket,buffer,BUFFER_SIZE)<0){
		return -1;
  }
  bzero(buffer, BUFFER_SIZE);
  length = recv_msg(client_socket,buffer,BUFFER_SIZE);
  if(length<0){
    printf("can't receive message from server!\n");
    return -1;
  }else{
    	printf("receive message from server: %s\n",buffer);
  }
  close_socket(client_socket);
  return 0;  
}

//点击“打开附件”自动下载附件到本地文件夹
//text用于存放附件内容
int GetAttachEmail(char* UserID,char* EmailID)
{
  char text[BUFFER_SIZE]={0};
  char getMailID[50];
  char buffer[BUFFER_SIZE]={0};
	int length=0;
  int client_socket=0;
  if(EmailID == NULL){
		return -1;
  }
	client_socket = connect_socket(SERVER_IP,SERVER_PORT);
	sprintf(buffer,"AttachSerToCli|%s",EmailID);
	printf ("send message to server:%s\n",buffer);
	if(send_msg(client_socket,buffer,BUFFER_SIZE)<0){
		return -1;
  }
  bzero(buffer, BUFFER_SIZE);
  length = recv_msg(client_socket,buffer,BUFFER_SIZE);
  if(length<0){
    printf("can't receive message from server!\n");
    return -1;
  }else{
    //buffer内容为：EmailID|附件内容
    	printf("receive message from server: %s\n",buffer);
	    char *  temp_text=strchr(buffer,'|');
      strncpy (getMailID, buffer,strlen(buffer)-strlen(text)); 
	    temp_text++;
      //附件内容存入到text中
      strcpy(text,temp_text);
  }
  close_socket(client_socket);
  //把附件内容保存到本地attach文件夹下
  SaveAttachFile(UserID,EmailID,text);
  return 0;
}

//向服务器发送请求，从服务器获取邮件,
//****收件模块最重要的函数****// 
int GetServerEmail(char* UserID)
{
//需要获取附件
  char buffer[BUFFER_SIZE]={0};
	int length=0;
  int client_socket=0;
  if(UserID == NULL){
		return -1;
  }
	client_socket = connect_socket(SERVER_IP,SERVER_PORT);
	sprintf(buffer,"EmailSerToCli|%s",UserID);
	printf ("send message to server:%s\n",buffer);
	if(send_msg(client_socket,buffer,BUFFER_SIZE)<0){
		return -1;
  }
  bzero(buffer, BUFFER_SIZE);
  length = recv_msg(client_socket,buffer,BUFFER_SIZE);
  if(length<0){
    printf("can't receive message from server!\n");
    return -1;
  }else{
    	printf("receive message from server: %s\n",buffer);
  }
  //写一个解析字符串的函数
  int getIntergrate = GetServerStringDisintergrate(buffer);
  if( getIntergrate < 0){
    print("string Disintergrate failed!\n");
    return -1;
  }else{
    printf("string disintergrate success!");
  }
  close_socket(client_socket);
  return 0;

}