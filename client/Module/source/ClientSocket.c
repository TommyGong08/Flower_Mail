#include"Struct.h"
#include"ClientSocket.h"
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


int connect_socket(char* server,int serverPort)
{
    int sockfd=0;
    struct sockaddr_in addr;
    struct hostent *phost;
    //向系统注册，通知系统建立一个通信端口
    //AF_INET表示使用IPV4协议
    //SOCK_STREAM表示使用TCP协议
    if( (sockfd=socket(AF_INET,SOCK_STREAM,0))<0 ){
	    herror("Init socket erro\n");
	    return -1;
    }
    bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(serverPort);
    addr.sin_addr.s_addr=inet_addr(server);
    //如果输入的是域名
    if(addr.sin_addr.s_addr == INADDR_NONE)
    {
         phost= (struct hostent*)gethostbyname(server);
	 if(phost == NULL)
         {
	    herror("Init socket s_addr erro \n");
	    return -1;
          }
	 addr.sin_addr.s_addr=((struct in_addr*)phost->h_addr)->s_addr;
    }
    if( connect(sockfd,(struct sockaddr*)&addr,sizeof(addr))<0 ){
	  return -1;
    }else{
	    return sockfd;
    }
}

int send_msg(int sockfd,char* sendBuff,int length)
{
    int sendSize=0;
    if( (sendSize=send(sockfd,sendBuff,length,0))<=0 )
    {
       herror("Send msg erro\n");
       return -1;
    }
    else
    {
	return sendSize;
    }
}

int  recv_msg(int sockfd,char* buffer,int bufflength)
{
    int flag=0;
    int reclength=0;
    memset(buffer,0,bufflength);
    for(flag=0;;){
      if( (reclength=read(sockfd,buffer+flag,bufflength-flag)) == -1 ){
	      herror("Recv msg erro\n");
	      return -1;
      }else if(reclength==0){
	      break;
      }else{
	      flag+=reclength;
	      reclength=0;
      }
      printf("flaginside=%d\n",flag);
    }
    //printf("buffer:%d\n",buffer);
    buffer[flag]='\0';
    return 0;
}

int close_socket(int sockfd)
{
    close(sockfd);
    return 0;
}