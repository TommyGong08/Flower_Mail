//*********************
//  author: 龚海龙
//  
//*********************

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define  SERVER_PORT  5789
#define  LISTEN_QUEUE_LENGTH 10
#define  BUFFER_SIZE 100
#define INET_ADDRESS  "101.200.180.91"
int main()
{
  //设置一个socket地址结构server_addr,代表服务器internet地址, 端口
  struct sockaddr_in server_addr;
  bzero (&server_addr, sizeof (server_addr));	//把一段内存区的内容全部设置为0
  server_addr.sin_family = AF_INET;                               //IPV4地址
  server_addr.sin_addr.s_addr = inet_addr(INET_ADDRESS);   
  //server_addr.sin_addr.s_addr = htons (INADDR_ANY);
  server_addr.sin_port = htons(SERVER_PORT);          //端口设置

  //创建一个套接字
  int server = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
  if(bind(server , ( struct sockaddr*)& server_addr  , sizeof(server_addr)) < 0){
    printf("[ERROR]:server bind fail!");
    exit(1);
  } 

  if(listen( server , LISTEN_QUEUE_LENGTH ) < 0){
    printf("[ERROR]:server listen fail!");
    exit(1);
  }
  printf(" Waiting for client ...\n");
  //服务器持续监听
  while(1)        
  {
    
    //定义客户端的socket地址结构client_addr
    struct sockaddr_in client_addr;
    socklen_t length = sizeof (client_addr);
      
    //创建一个新的套接字
    int new_server_socket = accept (server, (struct sockaddr *) &client_addr, &length);  
    if( new_server_socket < 0 ){
      printf("[ERROR]: server accept error!");
      break;
    }
    char buffer[BUFFER_SIZE];
    bzero (buffer, BUFFER_SIZE);
       
    //recv接收消息
    if (recv (new_server_socket, buffer, BUFFER_SIZE, 0) < 0){
	    printf ("Server Recieve Data Failed!\n");
	    break;
	  }
    printf("receive message %s\n", buffer);

    strcpy ( buffer,"server get message successfully");
    //发送buffer里的字符串给客户端
   if (send (new_server_socket, buffer,BUFFER_SIZE , 0) < 0){
	  printf ("Send File:\t Failed\n");
	  break;
	}
  close(new_server_socket);
  }
  close(server);
  exit(0);
}