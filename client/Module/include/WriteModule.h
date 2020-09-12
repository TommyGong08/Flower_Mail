#ifndef WRITEMODULE_H
#define WRITEMODULE_H
#include"Struct.h"
#include"ClientSocket.h"

//写信模块，也是最重要的界面

//发送邮件
int SendEmail(MailInfo*  EmailInfo, char* text);
//保存草稿到本地邮件
int SaveDraft(MailInfo* EmailInfo , char* text);
//从本地邮件中导入草稿
int LeadinDraft(UserInfo* userInfo);
//从本地得到附件
int GetAttachFile();

#endif