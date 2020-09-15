/*

author：龚海龙

*/
#ifndef STRUCT_H
#define STRUCT_H
#define SHORT_CONTENT_SIZE 20
#define LONG_CONTENT_SIZE 500
#define BUFFER_SIZE 1024
#define FILE_BUFFER_SIZE 1024
#define SERVER_IP "101.200.180.91"
#define SERVER_PORT 5789
#define RES_LENGTH 1024
#define FILE_BUFFER_SIZE 1024
#define USER_ID_PASWD_SIZE 25       


//用户信息
typedef struct UserInfo                      
{
    char UserName[SHORT_CONTENT_SIZE];                 //用户名不超过20个字符
    char Password[SHORT_CONTENT_SIZE];                 //密码不超过20
    char Telephone[SHORT_CONTENT_SIZE];                //用户手机号码
    int    LoginState;                                           //用户登陆状态：1表示未登陆，0表示已经登陆
}UserInfo;

//邮件信息
typedef struct MailInfo
{
  char  EmailWriteID[SHORT_CONTENT_SIZE];          //邮件编写者ID
  char  EmailID[LONG_CONTENT_SIZE];               //邮件ID
  char  EmailTheme[SHORT_CONTENT_SIZE;             //邮件主题
  char EmailPath[LONG_CONTENT_SIZE];                //邮件在本地路径
  int     EmailType ;                                //邮件类型 ：0发送，1抄送，2密送，3抄送+密送，
  int     EmailState;                                //邮件状态 ：0保留，-1已读，1未读
  char  EmailSender[SHORT_CONTENT_SIZE];           //邮件发送者
  char  EmailReceiver[SHORT_CONTENT_SIZE];         //邮件接受者
  char  CopySendID[LONG_CONTENT_SIZE];             //抄送用户ID，以分号作为分割
  char  SecretSendID[LONG_CONTENT_SIZE];           //密送用户ID，以分号作为分割
  char  EmailSystemTime[SHORT_CONTENT_SIZE];       //邮件发送、接受、恢复、草稿等用同一个系统时间
  int      IfAttachFile;                              //有无附件，0表示有，-1表示无
  char  AttachFilePath[SHORT_CONTENT_SIZE];        // 附件存储路径
}MailInfo;



#endif