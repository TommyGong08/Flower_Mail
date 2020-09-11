### QT主界面中有几点需要说明：
## 收信模块：
1. 收件箱这个按钮自带刷新功能 
     每点一次"收件箱"按钮从数据库调用最新的收件信息 
     调用“GetEmailFromServerInterface()”，这个函数只是接口
     在此函数中调用GetServerEmail(),这个函数是socket，读取数据库

2. 有两个类型的按钮：“删除”，“已读”
有一个超链接：
点击主题栏能出现具体邮件内容 ，显示在右边的文本框，
文本框底部有”回复“按钮，点击“回复”按钮能跳转到写信界面，同时自动填充回复人ID 

3. 点击“删除”按钮：调用 “delete_email_interface()” 
点击“已读”按钮：调用“change_emai_state_interface(UserInfo* UserInfo,EmailInfo* EmailID)" 
以上两个函数都是接口函数 

## 通讯录模块 
点击“通讯录”后，调用“GetContactInfo(), 
此时右侧栏目： 
第一栏：输入联系人ID，有“确定”按钮 
点击“确定”按钮，直接调用 “AddContact (char * UserID,char * ContactID) ”
下面是通讯录列表，只用“用户ID”和“删除”按键两栏
点击“删除”按键：直接调用 “DeleteContact (char * UserID,int ContactID) ”

## 草稿模块
点击草稿箱跳转到写信界面，在写信的文本框中从本地文件夹的草稿文件夹中导入草稿
调用函数“LeadinDraft(UserInfo* userInfo, char* )”

## 写信模块
1. 第一栏上面可以填写收件人，也可以从最右侧的通讯录中选择
2. 下面有“抄送”，“密送”，“附件”三个功能,点击相应的按键在QT程序中标记邮件类型
    点击相应的按钮才出现相应的栏目，其中点击“附件”能够上传本地文字附件
3. 三个功能件下方是文本框
4. 文本框下面有三个按键“发送”按钮、“存草稿”和“关闭”， 
点击“发送”按钮，调用“send_func()”函数， 
在send_func()函数中调用“SendMainInterface()"
5. SendMainInterface() 函数相当于接口函数 (lsy负责) 
 功能是： 
 读取页面得到的信息，包括：发件人，收件人，
 判断邮件的功能（有无抄送、密送、附件）， 
 发送附件（如果有，从本地读取附件）， 
6. 点击“存草稿”按钮直接调用“SaveDraft(MailInfo* EmailInfo , char* text)；”
7. 点击“关闭”按钮，跳转到收件页面



