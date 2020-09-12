#ifndef WRITEMODULE_H
#define WRITEMODULE_H
#include"Struct.h"
#include"ClientSocket.h"

//写信模块，也是最重要的界面

//保存草稿到本地邮件
int SaveDraft(UserInfo* userInfos , char* text);
//从本地邮件中导入草稿
int LeadinDraft(UserInfo* userInfo , char* text);
//从本地得到附件
int GetAttachFile(char* AttachFilePath , char* text);

//保存附件内容,传入参数为文本text
int SaveAttachFile(MailInfo* EmainInfo , char* text);

//socket发送附件
int SendAttachFile();

//socket接受附件
int RecvAttachFile();

//发送邮件
int SendEmail(MailInfo*  EmailInfo, char* text);

#endif