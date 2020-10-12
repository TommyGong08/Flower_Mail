#include"serverlib.h"
#include <mysql/mysql.h>
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

// * * * * * * * * * * * * * * * * 数  据  库  部  分 * * * * * * * * * * * * * * * * // 
int OpenSql(char *Host, char *User, char *PsdWd, char *DbName)
{
    if((Host == NULL) || (User == NULL) || (PsdWd == NULL) || (DbName == NULL))
    {
        return -1;
    }
    conn_ptr = mysql_init(&conn);
    if(conn_ptr == NULL)
    {
        return -1;
    }
    if(mysql_real_connect(&conn, Host, User, PsdWd, DbName, 0, NULL, 0))
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
int ExecSql(char *sqltext)
{
	if(sqltext == NULL)
	{
		return -1;
	}
	int i = -1;
	mysql_real_query(&conn, sqltext, (unsigned int)strlen(sqltext)); 
	i = mysql_affected_rows(&conn);
	return i;
}
int Insert(char *Rescmd)
{
	int iAdd = -1;				//增加
	//执行增加语句
	iAdd = ExecSql(Rescmd);
	if (iAdd > 0)
	{
		printf ("添加成功。\n");
        if(strstr(Rescmd,"EmailTable") != NULL)
        {
            return mysql_insert_id(&conn);
        }
	}
	else if (iAdd == 0)
	{
		printf ("受影响的记录数为0。\n");
	}
	else
	{
		printf ("主健冲突或者插入语句出错或者不存在目标表,未执行。\n");
	}
	return iAdd;
}
int Delete(char *Rescmd)
{
	int iDelete = -1;			//删除
	//执行删除语句
	iDelete = ExecSql(Rescmd);
	if (iDelete > 0)
	{
		printf ("删除成功。\n");
	}
	else if (iDelete == 0)
	{
		printf ("受影响的记录数为0。\n");
	}
	else
	{
		printf ("查询语句出错或者不存在目标表,未执行。\n");
	}
	return iDelete;
}
int Update(char *Rescmd)
{
	int iUpdate = -1;			//更新
	//更新更改语句
	iUpdate = ExecSql(Rescmd);
	if (iUpdate > 0)
	{
		printf ("更新成功。\n");
	}
	else if (iUpdate == 0)
	{
		printf ("受影响的记录数为0。\n");
	}
	else
	{
		printf ("更新语句出错或者不存在目标表,未执行。\n");
	}
	return iUpdate;
}
int SelectSql(char *sqltext)
{
	int i=mysql_query(&conn, sqltext);
    if( i==0 )
	{
		res_ptr = mysql_store_result(&conn);
		return mysql_num_rows(res_ptr);
	}
	else
    {
        return -1;
    }
}
int GetFields()
{
	if (res_ptr == NULL)
	{
		return -1;
	}
	return mysql_num_fields(res_ptr);
}
MYSQL_ROW GetNextRowData()
{
	if (res_ptr == NULL)
	{
		return NULL;
	}
	return mysql_fetch_row(res_ptr);
}
int Select(char *Rescmd, char *buffer)
{
	int iSelect = -1;			//查询
	int iFields = 0;
	int i = 0;
	MYSQL_ROW r = NULL;			//存放查找到的一行数据
	iSelect = SelectSql(Rescmd);	//查询语句正确且结果集不为空
	if (iSelect > 0)
	{
		//printf ("所查到的数据是:   ");
		iFields = GetFields ();
		while ((r = GetNextRowData ()))
		{
			char acTemp[BUFFER_SIZE] = {0};
			for (i = 0; i < iFields; i++)
			{
				strcat (buffer, r[i]);
				strcat (buffer, "|");
				//printf ("%s\t", r[i]);
			}
			strcat (buffer, "#");
		}
		strcat (buffer, "\0");
		//释放查询数据
		FreeResult ();
	}
	else if (iSelect == 0)
	{
		printf ("查询到的结果为空集。\n");
	}
	else
	{
		printf ("查询语句存在错误或者不存在目标表,未执行查询。\n");
	}
	return iSelect;
}
void FreeResult()
{
	mysql_free_result(res_ptr);
}
void CloseMysql()
{
    mysql_close(&conn);
}
// * * * * * * * * * * * * * * * * 数  据  库  部  分 * * * * * * * * * * * * * * * * // 

// * * * * * * * * * * * * * * * * * 通  讯  部  分  *  * * * * * * * * * * * * * * * //
int MakeDirectory(const char *pcFileName)
{  
    char DirName[BUFFER_SIZE];  
    strcpy(DirName, pcFileName);  
    int i,len = strlen(DirName);
    for(i=1; i<len; i++)  
    {  
        if(DirName[i]=='/')  
        {  
            DirName[i] = 0; 
            if(access(DirName, 0)!= 0)  
            {  
                if((mkdir(DirName, 0755)) == -1)  
                {   
                    printf( "Problem creating directory :%s\n",pcFileName );
                    return -1;
                }  
            } 
            DirName[i] = '/';  
        }  
    }
    return 0;  
} 
int MakeEmailIdDirectory(char *pcUserId)
{
    char  acUserDirectory[BUFFER_SIZE] = {0};
    sprintf(acUserDirectory,"./data/%s/",pcUserId);
	if( (access(acUserDirectory, 0)) == -1)
    {     
		if(MakeDirectory(acUserDirectory) == -1)
        {
            return -1;
        }
        char acTypeDirectory[BUFFER_SIZE] = {0};
        memset(acTypeDirectory,'\0',strlen(acTypeDirectory));  
        sprintf(acTypeDirectory,"./data/%s/1/",pcUserId); 
        if(MakeDirectory(acTypeDirectory) == -1)//create acTypeDirectory failed.
        {
            return -1;
        } 
        memset(acTypeDirectory,'\0',strlen(acTypeDirectory));  
        sprintf(acTypeDirectory,"./data/%s/2/",pcUserId);  
        if(MakeDirectory(acTypeDirectory) == -1)//create acTypeDirectory failed.
        {
            return -1;
        }
        memset(acTypeDirectory,'\0',strlen(acTypeDirectory));
        sprintf(acTypeDirectory,"./data/%s/3/",pcUserId);  
        if(MakeDirectory(acTypeDirectory) == -1)//create acTypeDirectory failed.
        {
            return -1;
        }
    }
    return 0;
}
int RecFileToUserID(char *userid, char *emailid, char *info)
{  
    char acDirectory[BUFFER_SIZE] = { 0 };
    char acFilename[BUFFER_SIZE] = { 0 };
    sprintf(acDirectory,"./data/%s/1/%s/", userid, emailid);
    sprintf(acFilename,"./data/%s/1/%s/message.txt",userid, emailid);
    if(MakeEmailIdDirectory(userid) == -1)
        return-1;
    if(MakeDirectory(acDirectory) == -1)
        return-1;
    FILE *fp = NULL;
    fp = fopen(acFilename, "w");
	if (fp == NULL)
	{
		printf ("File:\t%s Can Not Open To Write\n", acFilename);
        return -1;
	}
	fputs(info, fp);
    char ssql[BUFFER_SIZE] = { 0 };
    sprintf(ssql,"UPDATE EmailTable SET EmailPath= '%s' WHERE EmailID= '%s'", acDirectory, emailid);
    Update(ssql);
	fclose(fp);
    return 0;
}
int RecFileToRecID(char *recvid, char *emailid, char *info)
{
    char acDirectory[BUFFER_SIZE] = { 0 };
    char acFilename[BUFFER_SIZE] = { 0 };
    sprintf(acDirectory,"./data/%s/2/%s/", recvid, emailid);
    sprintf(acFilename,"./data/%s/2/%s/message.txt",recvid, emailid);
    if(MakeEmailIdDirectory(recvid) == -1)
        return-1;
    if(MakeDirectory(acDirectory) == -1)
        return-1;
    FILE *fp = NULL;
    fp = fopen(acFilename, "w");
	if (fp == NULL)
	{
		printf ("File:\t%s Can Not Open To Write\n", acFilename);
        return -1;
	}
	fputs(info, fp);
	fclose(fp);
    return 0;
}
char *SendToReceiver(char *Rescmd)
{
    int x = 0;
    int temp = 0;
    int flag = 0;
    char data[BUFFER_SIZE] = { 0 };
    char sql[BUFFER_SIZE] = { 0 };
    char buffer[BUFFER_SIZE] = { 0 };
    char buffer2[BUFFER_SIZE] = { 0 };
    char buffer3[BUFFER_SIZE] ={ 0 };
    char buffer4[BUFFER_SIZE] = { 0 };
    char buffer5[BUFFER_SIZE] = { 0 };
    sprintf(sql, "SELECT EmailID FROM EmailTable WHERE RecvID='%s'", Rescmd);
    Select(sql, buffer);
    while (buffer[temp] != '\0')
    {
        while ( buffer[flag] != '#' && buffer[flag] != '\0')
        {
            flag++;
        }
        memset(data, '\0', sizeof(data));
        strncpy(data, buffer + temp, flag - temp -1);
        flag++;
        temp = flag;
        memset(sql, '\0', sizeof(sql));
        sprintf(sql, "SELECT UserID,EmailID,Theme,EmailTime FROM EmailTable WHERE EmailID='%s'", data);
        memset(buffer2, '\0', sizeof(buffer2));
        Select(sql, buffer2);
        x = strlen(buffer2);
        buffer2[x-1] = '\0';
        memset(sql, '\0', sizeof(sql));
        sprintf(sql, "SELECT EmailPath FROM EmailTable WHERE EmailID='%s'", data);
        memset(buffer3, '\0', sizeof(buffer3));
        Select(sql, buffer3);
        x = strlen(buffer3);
        buffer3[x-2] = '\0';
        strcat(buffer3, "message.txt");
        FILE *fp =NULL;
        fp = fopen(buffer3, "r");
        if(fp == NULL)
        {
            printf("fopen error!\n");
            break;
        }
        memset(buffer4, '\0', sizeof(buffer4));
        fgets(buffer4, BUFFER_SIZE, fp);
        strcat(buffer4, "|");
        fclose(fp);
        strcat(buffer2,buffer4);
        strcat(buffer2, "#");
        strcat(buffer5, buffer2);
    }
    char *p=buffer5;
    return p;
}
int InsertIntoMysql(char *Rescmd)
{
    char emailid[BUFFER_SIZE] = { 0 };
    char theme[BUFFER_SIZE] = { 0 };
    char emailpath[BUFFER_SIZE] = { 0 };
    char emailtype[BUFFER_SIZE] = { 0 };
    char state[BUFFER_SIZE] = { 0 };
    char copysendid[BUFFER_SIZE] = { 0 };
    char secretsendid[BUFFER_SIZE] = { 0 };
    char emailtime[BUFFER_SIZE] = { 0 };
    char ifattachfile[BUFFER_SIZE] = { 0 };
    char attachfilename[BUFFER_SIZE] = { 0 };
    char attachfilepath[BUFFER_SIZE] = { 0 };
    char userid[BUFFER_SIZE] = { 0 };
    char recvid[BUFFER_SIZE] = { 0 };
    char Info[BUFFER_SIZE] = { 0 };
    char c3[BUFFER_SIZE] = { 0 }, c5[BUFFER_SIZE] ={ 0 }, c7[BUFFER_SIZE] ={ 0 }, c9[BUFFER_SIZE] ={ 0 };
    char c11[BUFFER_SIZE] = { 0 }, c13[BUFFER_SIZE] ={ 0 }, c15[BUFFER_SIZE] ={ 0 }, c17[BUFFER_SIZE] ={ 0 };
    char c19[BUFFER_SIZE] = { 0 }, c21[BUFFER_SIZE] ={ 0 }, c23[BUFFER_SIZE] ={ 0 }, c25[BUFFER_SIZE] ={ 0 };
    char c27[BUFFER_SIZE] = { 0 }, c29[BUFFER_SIZE] = { 0 };

    char *c1 = Rescmd;
    char *c2 = strchr(c1, '|');        
    strncpy(emailid, c1, c2 - c1);      
    c2++;
    strcpy(c3, c2);

    char *c4 = strchr(c3, '|');
    strncpy(theme, c3, c4 - c3);
    c4++;
    strcpy(c5, c4);
    
    char *c6 = strchr(c5, '|');
    strncpy(emailpath, c5, c6 - c5);
    c6++;
    strcpy(c7, c6);

    char *c8 = strchr(c7, '|');
    strncpy(emailtype, c7, c8 - c7);
    c8++;
    strcpy(c9, c8);

    char *c10 = strchr(c9, '|');
    strncpy(state, c9, c10 - c9);
    c10++;
    strcpy(c11, c10);

    char *c12 = strchr(c11, '|');
    strncpy(copysendid, c11, c12 - c11);
    c12++;
    strcpy(c13, c12);

    char *c14 = strchr(c13, '|');
    strncpy(secretsendid, c13, c14 - c13);
    c14++;
    strcpy(c15, c14);

    char *c16 = strchr(c15, '|');
    strncpy(emailtime, c15, c16 - c15);
    c16++;
    strcpy(c17, c16);

    char *c18 = strchr(c17, '|');
    strncpy(ifattachfile, c17, c18 - c17);
    c18++;
    strcpy(c19, c18);

    char *c20 = strchr(c19, '|');
    strncpy(attachfilename, c19, c20 - c19);
    c20++;
    strcpy(c21, c20);

    char *c22 = strchr(c21, '|');
    strncpy(attachfilepath, c21, c22 - c21);
    c22++;
    strcpy(c23, c22);

    char *c24 = strchr(c23, '|');
    strncpy(userid, c23, c24 - c23);
    c24++;
    strcpy(c25, c24);

    char *c26 = strchr(c25, '|');
    strncpy(recvid, c25, c26 - c25);
    c26++;
    strcpy(c27, c26);

    char *c28 = strchr(c27, '|');
    strncpy(Info, c27, c28 - c27);
    c28++;
    strcpy(c29, c28);

    int  iemailtype = atoi(emailtype);
    int  istate = atoi(state);
    int  iifattachfile = atoi(ifattachfile);

    //printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",emailid,theme,emailpath,emailtype,state,copysendid,secretsendid,emailtime,ifattachfile,attachfilename,attachfilepath,userid,recvid,Info);
    char sql[BUFFER_SIZE] = { 0 };
    memset(sql, '\0', sizeof(sql));
    sprintf(sql, "insert into EmailTable values('%s','%s','%s','%d','%d','%s','%s','%s','%d','%s','%s','%s','%s')", emailid,theme,emailpath,iemailtype,istate,copysendid,secretsendid,emailtime,iifattachfile,attachfilename,attachfilepath,userid,recvid);
    Insert(sql);
    int u = RecFileToUserID(userid, emailid, Info);
    int r = RecFileToRecID(recvid, emailid, Info);
    int c = RecFileToRecID(copysendid, emailid, Info);
    int m = RecFileToRecID(secretsendid, emailid, Info);
    return 0;
}
int RecAttachFile(char *Rescmd)
{
    int len = 0;
    int temp = 0;
    int flag = 0;
    int flag_f = 0;
    char ppath[BUFFER_SIZE] = { 0 };
	char sql[BUFFER_SIZE] = { 0 };
    char buffer[BUFFER_SIZE] ={ 0 };
    char data[BUFFER_SIZE] ={ 0 };
    char emailid[BUFFER_SIZE] = { 0 };
    char info[BUFFER_SIZE] = { 0 };
    char c3[BUFFER_SIZE] = { 0 };

    char *c1 = Rescmd;
    char *c2 = strchr(c1, '|');        
    strncpy(emailid, c1, c2 - c1);      
    c2++;
    strcpy(c3, c2);
    char *c4 = strchr(c3, '|');
    strncpy(info, c3, c4 - c3);

    sprintf(sql, "select UserID,RecvID,CopySendID,SecretSendID FROM EmailTable WHERE EmailID='%s'", emailid);
    Select(sql, buffer);
    len = strlen(buffer);
    buffer[len-1] = '\0';
    //printf("%s\n", buffer);
    while (buffer[temp] != '\0')
    {
        while ( buffer[flag] != '|' && buffer[flag] != '\0')
        {
            flag++;
        }
        memset(data, '\0', sizeof(data));
        strncpy(data, buffer + temp, flag - temp);
        flag++;
        temp = flag;
        memset(ppath, '\0', sizeof(ppath));
        sprintf(ppath, "./data/%s/3/%s/",data,emailid);
        MakeDirectory(ppath);
        sprintf(ppath, "./data/%s/3/%s/message.txt",data,emailid);
        if(flag_f == 0)
        {
            memset(sql, '\0', sizeof(sql));
            sprintf(sql,"UPDATE EmailTable SET AttachFilePath= '%s' WHERE EmailID= '%s'", ppath, emailid);
            Update(sql);
            flag_f = 1;
        }
        FILE *fp = NULL;
        fp = fopen(ppath, "w");
	    if (fp == NULL)
	    {
		    printf ("File:\t%s Can Not Open To Write\n", ppath);
            return -1;
	    }
	    fputs(info, fp);
        fclose(fp);
    }
    return 0;
}
char *SendAttachFile(char *Rescmd)
{
    char sql[BUFFER_SIZE] = { 0 };
    char buffer[BUFFER_SIZE] = { 0 };
    char buffer2[BUFFER_SIZE] = { 0 };
    sprintf(sql, "SELECT RecvID FROM EmailTable WHERE EmailID='%s'", Rescmd);
    Select(sql, buffer);
    int len = strlen(buffer);
    buffer[len-2] = '\0';
    char path[BUFFER_SIZE] = { 0 };
    sprintf(path, "./data/%s/3/%s/message.txt",buffer, Rescmd);
    FILE *fp =NULL;
    fp = fopen(path, "r");
    if(fp == NULL)
    {
        printf("fopen error!\n");
        return NULL;
    }
    fgets(buffer2, BUFFER_SIZE, fp);
    fclose(fp);
    char *p = buffer2;
    return p;
}
int DeleteMail(char *Rescmd)
{
    int len = 0;
    int temp = 0;
    int flag = 0;
    int captain = 0;
    char ppath[BUFFER_SIZE] = { 0 };
    char pppath[BUFFER_SIZE] = { 0 };
	char sql[BUFFER_SIZE] = { 0 };
    char buffer[BUFFER_SIZE] ={ 0 };
    char data[BUFFER_SIZE] ={ 0 };
    sprintf(sql, "select UserID,RecvID,CopySendID,SecretSendID FROM EmailTable WHERE EmailID='%s'", Rescmd);
    Select(sql, buffer);
    len = strlen(buffer);
    buffer[len-1] = '\0';
    //printf("%s\n", buffer);
    while (buffer[temp] != '\0')
    {
        while ( buffer[flag] != '|' && buffer[flag] != '\0')
        {
            flag++;
        }
        memset(data, '\0', sizeof(data));
        strncpy(data, buffer + temp, flag - temp);
        flag++;
        temp = flag;
        memset(ppath, '\0', sizeof(ppath));
        memset(pppath, '\0', sizeof(pppath));
        if(captain == 0)
        {
            sprintf(ppath, "./data/%s/1/%s/message.txt",data,Rescmd);
            sprintf(pppath, "./data/%s/1/%s",data,Rescmd);
            captain = 1;
        }
        else
        {
            sprintf(ppath, "./data/%s/2/%s/message.txt",data,Rescmd);
            sprintf(pppath, "./data/%s/2/%s",data,Rescmd);
        }
        //printf("%s\n", ppath);
        //printf("%s\n", pppath);
        if(remove(ppath) != 0)
        {
            printf("Faild To Remove Email!\n");
            return -1;
        }
        if(remove(pppath) != 0)
        {
            printf("Faild To Remove Email!\n");
            return -1;
        }
    }
    memset(sql, '\0', sizeof(sql));
    sprintf(sql, "DELETE FROM EmailTable WHERE EmailID='%s'", Rescmd);
    int g = Delete(sql);
    if(g > 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
int Register(char *Rescmd)
{
    char a[BUFFER_SIZE] = { 0 };
    memset(a, '\0',sizeof(a));
    int i = Select(Rescmd, a);
    if(i > 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
int RegisterInsert(char *Rescmd)
{
    char Passwd[BUFFER_SIZE] = { 0 };
    char Telephone[BUFFER_SIZE] = { 0 };
    char state[BUFFER_SIZE] = { 0 };
    char UserID[BUFFER_SIZE] = { 0 };
    int istate;
    char c3[BUFFER_SIZE] = { 0 }, c5[BUFFER_SIZE] = { 0 }, c7[BUFFER_SIZE] = { 0 }, c9[BUFFER_SIZE] = { 0 };
    char *c1 = Rescmd;
    char *c2 = strchr(c1, '|');        
    strncpy(UserID, c1, c2 - c1);      
    c2++;
    strcpy(c3, c2);

    char *c4 = strchr(c3, '|');
    strncpy(Passwd, c3, c4 - c3);
    c4++;
    strcpy(c5, c4);
    
    char *c6 = strchr(c5, '|');
    strncpy(state, c5, c6 - c5);
    c6++;
    strcpy(c7, c6);

    char *c8 = strchr(c7, '|');
    strncpy(Telephone, c7, c8 - c7);
    c8++;
    strcpy(c9, c8);
    istate = atoi(state);
    char sql[BUFFER_SIZE] = {0};
    sprintf(sql, "INSERT INTO UserTable VALUES ('%s','%s','%d','%s')", UserID, Passwd, istate, Telephone);
    if(Insert(sql) < 1)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
char *LoginSelect(char *Rescmd)
{
    char a[BUFFER_SIZE] = { 0 };
    memset(a, '\0',sizeof(a));
    int i = Select(Rescmd, a);
    int len = strlen(a);
    a[len - 2] = '\0';
    char *p = a;
    if(i > 0)
    {
        return p;
    }
    else
    {
        return NULL;
    }
}
char *GetContactInfo(char *Rescmd)
{
    int temp = 0;
    int flag = 0;
    char data[BUFFER_SIZE] = { 0 };
    char sql[BUFFER_SIZE] = { 0 };
    char buffer[BUFFER_SIZE] = { 0 };
    char buffer2[BUFFER_SIZE] = { 0 };
    sprintf(sql, "SELECT FriendID FROM ContactTable WHERE UserID='%s'", Rescmd);
    Select(sql, buffer);
    while (buffer[temp] != '\0')
    {
        while ( buffer[flag] != '#' && buffer[flag] != '\0')
        {
            flag++;
        }
        memset(data, '\0', sizeof(data));
        strncpy(data, buffer + temp, flag - temp -1);
        flag++;
        temp = flag;
        strcat(buffer2, data);
        strcat(buffer2, "#");
    }
    char *p=buffer2;
    return p;
}
// * * * * * * * * * * * * * * * * * 通  讯  部  分  *  * * * * * * * * * * * * * * * //