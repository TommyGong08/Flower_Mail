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

//保存草稿到本地邮件###SaveSendFile
int SaveDraft(UserInfo* userInfo , char* text)
{
   FILE* fp = NULL;
   char path[50];
   sprintf(path,"../user/draft/%s.txt",userInfo->UserName);
   printf("\n%s\n",path);
   fp=fopen(path,"w");
   if(fp==NULL){
      return -1;
   }
   //写成文件
   int write_ = fwrite(text, sizeof (char),FILE_BUFFER_SIZE, fp);
	if (write_ < 0)
	{
		printf ("File:\t%s Write Failed\n", path);
	}
   fclose(fp);
   return 0;
}

//从本地邮件中导入草稿,存入text字符串中
int LeadinDraft(UserInfo* userInfo , char* text)
{
  FILE* fp = NULL;
  char buffer[FILE_BUFFER_SIZE];
  char path[50];
  sprintf(path,"../user/%s.draft",userInfo->UserName);
  printf("\n%s\n",path);
  fp = open(path,"r");
  if(fp == NULL){
    printf("can't find file!");
    return -1;
  }
   /* 查找文件的开头 */
   fseek(fp, 0, SEEK_SET);
   /* 读取并显示数据 */
   int read_ = fread(buffer, sizeof (char),FILE_BUFFER_SIZE, fp);
  if(read_ < 0){
    printf("File:\t%s Read Failed\n",path);
  }
   printf("%s\n", buffer);
   fclose(fp);
   return 0;
}

//从本地得到附件,读取到text中
int GetAttachFile(char* AtthachFilePath, char* text)
{
  FILE* fp = NULL;
  char buffer[FILE_BUFFER_SIZE];
  char path[50];
  sprintf(path,"%s",AtthachFilePath);
  printf("\n%s\n",path);
  fp = open(path,"r");
  if(fp == NULL){
    printf("can't find file!");
    return -1;
  }
   /* 查找文件的开头 */
   fseek(fp, 0, SEEK_SET);
   /* 读取并显示数据 */
   int read_ = fread(buffer, sizeof (char),FILE_BUFFER_SIZE, fp);
  if(read_ < 0){
    printf("File:\t%s Read Failed\n",path);
  }
   printf("%s\n", buffer);
   strcpy(text,buffer);
   fclose(fp);
   return 0;
}

//保存附件内容,传入参数为文本text
int SaveAttachFile(MailInfo* EmainInfo , char* text)
{
    FILE* fp = NULL;
   char path[50];
   sprintf(path,"../user/attach/%s.txt",EmainInfo->EmailID);
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

//socket发送附件
int SendAttachFile()
{

}

int SendEmail(MailInfo*  EmailInfo, char* text)
{
//要发送常规邮件、附件、抄送、密送

}
