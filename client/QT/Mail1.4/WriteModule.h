#ifndef WRITEMODULE_H
#define WRITEMODULE_H

#ifdef __cplusplus
extern "C" {
#endif
int SaveDraft(char* UserName , char* text);
//从本地邮件中导入草稿
char*  LeadinDraft(char* UserName);
//从本地得到附件
char*  LeadinAttachFile(char* AtthachFilePath);
//保存附件内容,传入参数为文本text
int SaveAttachFile(char* UserID,char* EmailID , char* text);
//socket发送附件
int SendAttachFile();
//socket接受附件
int RecvAttachFile();
//发送邮件
int SendEmail(char* EmailID,char* EmailTheme,char* EmailPath, int EmailType,
                             int EmailState,char* CopySendID,char* SecretSendID,char* EmailSystemTime,
                               int  IfAttachFile, char* AttachFilePath,char* EmailSender,
                                 char* EmailReceiver,char* text);
#ifdef __cplusplus
}
#endif

#include"Struct.h"
#include"ClientSocket.h"

//写信模块，也是最重要的界面

//保存草稿到本地邮件


#endif
