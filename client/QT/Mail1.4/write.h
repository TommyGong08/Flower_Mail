#ifndef WRITE_H
#define WRITE_H

typedef struct MailIn
{
  char *  EmailWriteID;          //邮件编写者ID
  char *  EmailID;               //邮件ID
  char *  EmailTheme;            //邮件主题
  char *  EmailPath;              //邮件在本地路径
  int   EmailType ;               //邮件类型 ： -2草稿，0发送，1抄送，2密送，3抄送+密送，
  int   EmailState;               //邮件状态 ：0保留，-1已读，1未读
  char *  EmailSender;           //邮件发送者
  char *  EmailReceiver;         //邮件接受者
  char *  CopySendID;             //抄送用户ID，以分号作为分割
  char *  SecretSendID;           //密送用户ID，以分号作为分割
  char *  EmailSystemTime;       //邮件发送、接受、恢复、草稿等用同一个系统时间
  int   IfAttachFile;            //有无附件，0表示有，-1表示无
  char *  AttachFilePath;        // 附件存储路径
}wr_mailinfo;

#endif // WRITE_H
