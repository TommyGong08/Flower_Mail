/*

author：龚海龙

*/
#include"Login.h"
#include"Struct.h"
#include"ClientSocket.h"
#include"WriteModule.h"
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

/*分割“UserID|EmailTheme|state|邮件内容～”
int GetServerStringDisintergrate(char* string)
{

}*/

//success
int ChangeEmailState(char* emailID)
{
    int sendResult1;
 // char receBuffer[LONG_CONTENT_SIZE];
  char buffer[LONG_CONTENT_SIZE]={0};
  memset(buffer, '\0', LONG_CONTENT_SIZE);
 // memset(receBuffer, '\0', LONG_CONTENT_SIZE);
 int client_socket =0 ;
	client_socket = connect_socket(SERVER_IP,SERVER_PORT);
	sprintf(buffer,"changeemailstate|UPDATE EmailTable SET state = '%d' WHERE EmailID= '%s'",1,emailID);
	printf ("send message to server:%s\n",buffer);
	sendResult1 = send_msg(client_socket, buffer, LONG_CONTENT_SIZE);
	if (sendResult1<0){
		return -1;
	}
  int length = 0;
  bzero (buffer, BUFFER_SIZE);
  length = recv(client_socket, buffer, BUFFER_SIZE, 0);
  if(length<0){
    printf("can't receive message from server!\n");
      close_socket(client_socket);
    return -1;
  }else{
    	printf("receive message from server: %s \n",buffer);
  }
  close_socket(client_socket);
  return 0; 
}

//删除数据库及服务器本地的邮件信息
//success
int DeleteServerEmail(char* emailID)
{
int sendResult1;
 // char receBuffer[LONG_CONTENT_SIZE];
  char buffer[LONG_CONTENT_SIZE]={0};
  memset(buffer, '\0', LONG_CONTENT_SIZE);
 // memset(receBuffer, '\0', LONG_CONTENT_SIZE);
	int length=0;
  int client_socket=0;
	client_socket = connect_socket(SERVER_IP,SERVER_PORT);
	sprintf(buffer,"deleteemail|%s",emailID);
	printf ("send message to server:%s\n",buffer);
	sendResult1 = send_msg(client_socket, buffer, LONG_CONTENT_SIZE);
	if (sendResult1<0){
		return -1;
	}
  bzero(buffer, BUFFER_SIZE);
  length = recv(client_socket, buffer, BUFFER_SIZE, 0);
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
//success
int  GetAttachEmail(char* UserID,char* EmailID)
{
  char text[BUFFER_SIZE]={0};
  char getMailID[50];
  char buffer[BUFFER_SIZE]={0};
	int length=0;
  int client_socket=0;
  if(EmailID == NULL){
		return -1;
  }
	sprintf(buffer,"attachsertocli|%s",EmailID);
	printf ("send message to server:%s\n",buffer);
  client_socket = connect_socket(SERVER_IP,SERVER_PORT);
	if(send_msg(client_socket,buffer,BUFFER_SIZE)<0){
		return -1;
  }
  bzero(buffer, BUFFER_SIZE);
  length = recv(client_socket, buffer, BUFFER_SIZE, 0);
  if(length<0){
    printf("can't receive message from server!\n");
    return -1;
  }else{
    //buffer内容为：EmailID|附件内容
    	printf("receive message from server: %s\n",buffer);
	    char *  temp_text=strchr(buffer,'|');
      strncpy(getMailID, buffer,strlen(buffer)-strlen(text)); 
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
//success
char* GetServerEmail(char* UserID)
{
 int sendResult1;
 // char receBuffer[LONG_CONTENT_SIZE];
  char buffer[LONG_CONTENT_SIZE]={0};
  memset(buffer, '\0', LONG_CONTENT_SIZE);
 // memset(receBuffer, '\0', LONG_CONTENT_SIZE);
	int length=0;
  int client_socket=0;
	client_socket = connect_socket(SERVER_IP,SERVER_PORT);
	sprintf(buffer,"emailsertocli|%s",UserID);
	printf ("send message to server:%s\n",buffer);
	sendResult1 = send_msg(client_socket, buffer, LONG_CONTENT_SIZE);
	if (sendResult1<0){
		return NULL;
	}
  bzero(buffer, BUFFER_SIZE);
  length = recv(client_socket, buffer, BUFFER_SIZE, 0);
  if(length<0){
    printf("can't receive message from server!\n");
    return NULL;
  }else{
    	printf("receive message from server: %s\n",buffer);
  }
  //写一个解析字符串的函数
//  int getIntergrate = GetServerStringDisintergrate(buffer);
  /*if( getIntergrate < 0){
    print("string Disintergrate failed!\n");
    return -1;
  }else{
    printf("string disintergrate success!");
  }*/
  char* text = buffer;
  close_socket(client_socket);
  return text;
}
