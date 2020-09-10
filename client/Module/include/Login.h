#ifndef LOGIN_H
#define LOGIN_H

//判断输入的字符串
int CheckLoginInput(char* UserName, char* PsWd);

//将登陆的用户信息发送给服务器
int SendUserInfoToServer(char* UserName , char* PsWd);

//客户端接受服务器返回的登陆指令，登陆成功在本地创建文件夹
int RecLoginResFromServer();

//登陆成功后创建本地文件夹
int CreaterUserFolder(char* UserInfo);

#endif