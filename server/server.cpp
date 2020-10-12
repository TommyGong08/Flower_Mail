#include"serverlib.h"
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h> 
#include<assert.h>

struct sockaddr_in server_addr;    //地址结构体，包含协议，地址，端口
struct sockaddr_in client_addr;    //用于接受客户端信息
char buffer[BUFFER_SIZE];          //数据缓冲区
char cmdType[BUFFER_SIZE];         //存放报头信息
char acTempData[BUFFER_SIZE];      //存放报头以外的信息
char *pcTempCmdType;               //存储信息缓冲区
int  server_socket;                //服务器套接字
int iDataNum;                      //接受recv函数返回值

void serSocket()                   //创建套接字
{
  if((server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
  {
	  printf("Create Socket Failed !\n");
    exit(1);
  }
  else
  {
    assert(server_socket != -1);
    printf("Create Socket Successfully !\n");
  } 
}
void serSockaddr()                 //地址结构体初始化
{
  bzero(&server_addr, sizeof(server_addr));	           //把一段内存区的内容全部设置为0
  server_addr.sin_addr.s_addr = inet_addr("0.0.0.0");  //主机IP地址,所有地址
  server_addr.sin_port = htons(SERVER_PORT);           //端口设置
  server_addr.sin_family = AF_INET;                    //IPV4地址
}
void serBind()                     //套接字绑定地址结构体
{
  if(bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
  {
    printf("Server Bind Failed !\n");
    exit(1);
  }
  else
  {
    printf("Server Bind Successfully !\n");
  }
  
}
void serListen()                   //监听
{
  if(listen(server_socket, 10) < 0)
  {
    printf("Server Listen Failed !\n");
    exit(1);
  }
  else
  {
    printf("Server Listen Successfully !\n");
    printf("Server Is Running Sucessfully !\n");
  }
}
void separateMes(int fd)           //处理从client收到的信息
{
    strncpy(cmdType, buffer, strlen(buffer) - strlen(pcTempCmdType));    //从buffer取出报头放进cmdType
    pcTempCmdType++;
    strcpy(acTempData, pcTempCmdType);      //报头以后的信息放到acTempData
    printf("string received from server (fd = %d)  excluding header: %s\n",fd, cmdType);
    printf("string received from server (fd = %d) excluding process: %s\n",fd, acTempData);
}
static void *start_routine(void *ptr)     //线程运行函数
{
  int fd = *(int *)ptr;
  pcTempCmdType = NULL;
  bzero(buffer, BUFFER_SIZE);
  bzero(cmdType, BUFFER_SIZE);
  bzero(acTempData, BUFFER_SIZE);
  printf("this is a new thread, you got connected! fd = %d.\n", fd);
  pcTempCmdType = NULL;
  bzero(cmdType, BUFFER_SIZE);
  bzero(buffer, BUFFER_SIZE);
  buffer[0] = '\0';
  cmdType[0] = '\0';
  acTempData[0] = '\0';
  char se[BUFFER_SIZE] = "Illeagal String.";
  if ((iDataNum = recv(fd, buffer, BUFFER_SIZE, 0)) < 0)      //recv接收消息,读取一条字符流
  {
	  printf ("Server Recieve Data Failed !\n");
    send(fd, se, strlen(se), 0);
	}
  buffer[iDataNum] = '\0';
  pcTempCmdType = strchr(buffer, '|');                            //取出|及以后的信息放进pcTempCmdType
  if(pcTempCmdType == NULL)
  {
    printf("There Is No Head In The String From Client!\n");
  }
  separateMes(fd);
  bzero(buffer, BUFFER_SIZE);
  //增删改查操作
  if(strcmp(cmdType, "select") == 0)
  {
    //执行查询语句，把查询结果返回给客户端
    int iSelect = Select(acTempData, buffer);
    if(iSelect > 0)
    {
      strcpy(buffer, "0");
    }
    else
    {
      strcpy(buffer, "-1");
    }
  }
  else if(strcmp(cmdType, "insert") == 0)
  {
    int iInsert = Insert(acTempData);
    if(iInsert > 0)
    {
      strcpy(buffer, "0");
    }
    else
    {
      strcpy(buffer, "-1");
    }
  }
  else if(strcmp(cmdType, "delete") == 0)
  {
    int iDelete = Delete(acTempData);
    if(iDelete > 0)
    {
      strcpy(buffer, "0");
    }
    else
    {
      strcpy(buffer, "-1");
    }
  }
  else if(strcmp(cmdType, "update") == 0)
  {
    int iUpdate = Update(acTempData);
    if(iUpdate > 0)
    {
      strcpy(buffer, "0");
    }
    else
    {
      strcpy(buffer, "-1");
    }
  }
  //注册、登录模块
  else if(strcmp(cmdType, "registerselect") == 0)
  {
    if(Register(acTempData) == 0)
    {
      strcpy(buffer, "0");
    }
    else
    {
      strcpy(buffer, "-1");
    }
  }
  else if(strcmp(cmdType, "registerinsert") == 0)
  {
    if(RegisterInsert(acTempData) == 0)
    {
      strcpy(buffer, "0");
    }
    else
    {
      strcpy(buffer, "-1");
    }
  }
  else if(strcmp(cmdType, "loginselect") == 0 )
  {
    char *buff = LoginSelect(acTempData);
    strcpy(buffer, buff);
  }
  else if(strcmp(cmdType, "logoutupdate") == 0)
  {
    int i = Update(acTempData);
    if(i > 0)
    {
      strcpy(buffer, "0");
    }
    else
    {
      strcpy(buffer, "-1");
    }
    
  }
  else if(strcmp(cmdType, "loginstateselect") == 0)
  {
    char sql[BUFFER_SIZE] = { 0 };
    char buff[BUFFER_SIZE] = { 0 };
    Select(acTempData, buff);
    int len = strlen(buff);
    char cstate = buff[len-3];
    buff[len-4] = '\0';
    if(cstate == '0')
    {
      strcpy(buffer, "-1");
    }
    else
    {
      sprintf(sql,"UPDATE UserTable SET state='%d' WHERE UserID='%s'",0,buff);
      Update(sql);
      strcpy(buffer, "0");
    }
  }
  //收、发、删除邮件模块
  else if(strcmp(cmdType, "emailclitoser") == 0)
  {
    if(InsertIntoMysql(acTempData) == 0)
    {
      strcpy(buffer, "0");
    }
    else
    {
        strcpy(buffer, "-1");
    }
  }
  else if(strcmp(cmdType, "emailsertocli") == 0)
  {
    char *buff =SendToReceiver(acTempData);
    strcpy(buffer, buff);
  }
  else if(strcmp(cmdType, "deleteemail") == 0)  
  {
    int i = DeleteMail(acTempData);
    if(i == 0)
    {
      strcpy(buffer, "0");
    }
    else
    {
      strcpy(buffer, "-1");
    }
    
  }
  else if(strcmp(cmdType, "changeemailstate") == 0)
  {
    int i = Update(acTempData);
    if(i > 0)
    {
      strcpy(buffer, "0");
    }
    else
    {
      strcpy(buffer, "-1");
    }
  }
  //通讯录模块
  else if(strcmp(cmdType, "contactinsert") ==0)
  {
    int i = Insert(acTempData);
    if(i > 0)
    {
      strcpy(buffer, "0");
    }
    else
    {
      strcpy(buffer, "-1");
    }
  }
  else if(strcmp(cmdType, "contactdelete") ==0)
  {
    int i = Delete(acTempData);
    if(i > 0)
    {
      strcpy(buffer, "0");
    }
    else
    {
      strcpy(buffer, "-1");
    }
  }
  else if(strcmp(cmdType, "getcontactinfo") == 0)
  {
    char *buff = GetContactInfo(acTempData);
    strcpy(buffer, buff);
  }
  //附件模块
  else if(strcmp(cmdType, "attachclitoser") == 0)
  {
    int i = RecAttachFile(acTempData);
    if(i == 0)
    {
      strcpy(buffer, "0");
    }
    else
    {
      strcpy(buffer, "-1");
    }
  } 
  else if(strcmp(cmdType, "attachsertocli") == 0)
	{
	  char *buff = SendAttachFile(acTempData);
    if(buff == NULL)
    {
      strcpy(buffer, "-1");
    }
    else
    {
      strcpy(buffer, buff);
    }
	}
  //无法识别指令
  else
  {
    strcpy(buffer, "Ileagal Input.");
    printf("Ileagal String From Client\n");
  }
  printf("String Sended To Client: %s\n", buffer);
  send(fd, buffer, strlen(buffer) , 0); 
}
int main()
{
  serSocket();
  serSockaddr();
  serBind();
  serListen();
  int state = OpenSql("101.200.180.91", "root", "Aa123456", "test1.0");
  if(state == 0)
  {
      printf("Open Mysql Successfully !\n");
  }
  while(1)                 //服务器端需要一直运行   
  {
    pthread_t thread;                  //定义线程thread,线程ID  
    socklen_t length = sizeof (client_addr);   //存取client_addr的大小
    int client_socket = accept (server_socket, (struct sockaddr *) &client_addr, (socklen_t *)&length);  
    if(client_socket < 0)
    {
      printf("[ERROR]: server accept error!\n");
      break;
    }
    printf("You Got a Connection From  %s\n", inet_ntoa(client_addr.sin_addr));
    if( pthread_create(&thread, NULL, start_routine, (void *)(&client_socket)) != 0)
    {
        fprintf(stderr,"pthread_create error!\n");
        break;
    }
  }
  int ret = shutdown(server_socket,SHUT_WR); //shut down the all or part of a full-duplex connection.
  assert(ret != -1);
  printf("Server shuts down\n");
  CloseMysql();
  return 0;
}