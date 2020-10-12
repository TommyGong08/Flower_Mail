#include "ClientSocket.h"
#include "Struct.h"
#ifndef LOGIN_H
#define LOGIN_H
#ifdef __cplusplus
extern "C" {
#endif
//判断输入的字符串
int CheckLoginInput(char* UserName, char* PsWd);

//将登陆的用户信息发送给服务器
int SendLoginUserInfoToServer(char* UserName , char* PsWd);

//把登陆发送给服务器
int SendLoginStateToServer(char* UserName);

//将退出消息发送给服务器
int SendLogOutInfoToServer(char* UserName);

//登陆成功后创建本地文件夹
int CreaterUserFolder(char* UserName);

//创建文件目录
int MakeDirectory(const char* FileName);


#ifdef __cplusplus
}
#endif

#endif
