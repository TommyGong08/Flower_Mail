/*

author：龚海龙

*/
#include"Struct.h"
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


//保存草稿到本地邮件###SaveSendFile(success)
int SaveDraft(UserInfo* userInfo , char* text)
{
   FILE* fp = NULL;
   char path[50];
   sprintf(path,"../data/%s/draft/1.txt",userInfo->UserName);
   printf("\n%s\n",path);
   fp = fopen(path,"w");
   if(fp==NULL){
      return -1;
   }
   //写成文件
 //  int write_ = fwrite(text, sizeof (char),FILE_BUFFER_SIZE, fp);
   fputs(text , fp);
   fclose(fp);
   return 0;
}

//从本地草稿箱中导入草稿,存入text字符串中
char*  LeadinDraft(UserInfo* userInfo)
{
  FILE* fp = NULL;
  char buffer[FILE_BUFFER_SIZE];
  char path[50];
  sprintf(path,"../data/%s/draft/1.txt",userInfo->UserName);
  printf("\n%s\n",path);
  fp = fopen(path,"r");
  if(fp == NULL){
    printf("can't find file!");
  }                                                                                                                                                                               
   fseek(fp, 0, SEEK_SET);
   int read_ = fread(buffer, sizeof (char),FILE_BUFFER_SIZE, fp);
  if(read_ < 0){
    printf("File:\t%s Read Failed\n",path);
  }
   printf("%s\n", buffer);
   char* text = buffer;
   fclose(fp);
   return text;
}

//从本地文件夹删除草稿
int DeleteDraft(UserInfo* userInfo)
{
   char path[50];
   sprintf(path, "../data/%s/draft/1.txt",userInfo->UserName);
   if(remove(path) == 0){
      printf("remove draft success\n");
      return 0;
   }else {
      printf("remove draft failed\n");
      return -1;
   }
}

//从本地得到附件,读取到text中,(success)
char*  LeadinAttachFile(char* AtthachFilePath)
{
  FILE* fp = NULL;
  char buffer[FILE_BUFFER_SIZE];
  char path[50];
  sprintf(path,"%s",AtthachFilePath);
  //path为文件路径
  printf("\n%s\n",path);
  fp = fopen(path,"r");
  if(fp == NULL){
    printf("can't find file!");
  }
   fseek(fp, 0, SEEK_SET);
   int read_ = fread(buffer, sizeof (char),FILE_BUFFER_SIZE, fp);
  if(read_ < 0){
    printf("File:\t%s Read Failed\n",path);
  }
   printf("%s\n", buffer);
	 char* text = buffer;
   fclose(fp);
   return text;
}

//保存附件内容,传入参数为文本text
int SaveAttachFile(char* UserID,char* EmailID , char* text)
{
    FILE* fp = NULL;
   char path[50];
   sprintf(path,"../data/%s/attach/%s.txt",UserID,EmailID);
   printf("\n%s\n",path);
   fp=fopen(path,"w");
   if(fp==NULL){
      return -1;
   }
   //写成文件
   int write_ = fwrite (text, sizeof (char),FILE_BUFFER_SIZE, fp);
	if (write_ < 0)
	{
		printf ("File:\t%s Write Failed\n", path);
	}
   close(fp);
   return 0;
}

//socket发送附件,传入参数为本地附件地址
int SendAttachFile(char* emailID, char* attachFilePath)
{
   char buffer[BUFFER_SIZE]={0};
   char text[BUFFER_SIZE] = {0};
	int length=0;
  int client_socket=0;
  if(attachFilePath == NULL ){
		return -1;
  }
  int GetAttach = LeadinAttachFile(attachFilePath ,&text);//&text这里可能有bug
  if(GetAttach == 0){
     printf("get attached  file Success!");
  }else{
     printf("get attached file Failed!");
     return -1;
  }
	client_socket = connect_socket(SERVER_IP,SERVER_PORT);
	sprintf(buffer,"attachclitoser|AttachCliToSer|%s|%s#" , emailID , text);
	printf ("send message to server:%s\n",buffer);
	if(send_msg(client_socket,buffer,BUFFER_SIZE)<0){
		return -2;
  }
  bzero(buffer, BUFFER_SIZE);
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

int SendEmail(MailInfo*  EmailInfo, char* text)
{
   //要发送常规邮件、附件、抄送、密送
   char buffer[FILE_BUFFER_SIZE]={0};
	int length=0;
	char* msg=NULL;
	int client_socket=0;
   sprintf(buffer,"emailclitoser|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|",
                                 EmailInfo->EmailID,EmailInfo->EmailTheme,EmailInfo->EmailPath,EmailInfo->EmailType,
                                 EmailInfo->EmailState,EmailInfo->CopySendID,EmailInfo->SecretSendID,EmailInfo->EmailSystemTime,
                                 EmailInfo->IfAttachFile,EmailInfo->EmailID,EmailInfo->AttachFilePath,EmailInfo->EmailSender,
                                 EmailInfo->EmailReceiver,text);
	client_socket= connect_socket(SERVER_IP,SERVER_PORT);  
	printf ("string sended to server:%s\n",buffer);
	length=send_msg(client_socket,buffer,FILE_BUFFER_SIZE);
   if(length<0){
      printf("send Email Failed!\n");
		return -1;
   }
	bzero (buffer, FILE_BUFFER_SIZE);
   printf("SERVERIP=%s   SERVERPORT=%d",SERVER_IP,SERVER_PORT);
//	length = recv_msg(client_socket,buffer,FILE_BUFFER_SIZE);//从服务器端接受到emailId
   length = recv_msg(client_socket, buffer, LONG_CONTENT_SIZE);
   if(length < 0){
      printf("can't receive message from server!\n");
      return -1;
   }
   close_socket(client_socket);
   int send_attachfile = 0;
   //判断邮件类型，如果有附件
   if(EmailInfo->IfAttachFile==0){
       send_attachfile = SendAttachFile(EmailInfo->EmailID,EmailInfo->AttachFilePath);
       if(send_attachfile < 0){
          printf("send attached file Failed!\n");
          return -1;
       }else{
          printf("send attached file success!\n");
       }
   }
return 0;
}
