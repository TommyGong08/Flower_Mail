#ifndef RECEIVEMODULE_H
#define RECEIRVEMODULE_H
#include "Struct.h"
#include "ClientSocket.h"
//#define GET_MAIL_LIST 100
#ifdef __cplusplus
extern "C" {
#endif
//分解收件buffer
int GetServerStringDisintergrate(char* string);
//改变邮件状态
int ChangeEmailState(char * EmailID);
//删除邮件
int DeleteServerEmail(char * EmailID);
//从服务端和数据库获取附件内容
int GetAttachEmail(char* UserID,char* EmailID);
//从服务端和数据库获取邮件
char*  GetServerEmail(char* UserID);
#ifdef __cplusplus
}
#endif

//收件箱模块


#endif
