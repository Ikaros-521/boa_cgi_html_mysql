#include <stdio.h>
#include "cgic.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mysql/mysql.h>
#include <stdbool.h>

#define SQL_SIZE 256 

int cgiMain(void)
{
    char username[20];
    char password[20];
    char email[40];
	//回显信息到HTML网页cgiHeaderContentType("text/html");
    printf("<html>\n\n");
	printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n\n");
	printf("<p>\n\n");
    
	if(cgiFormString("username", username, sizeof(username)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function username failed");
        //exit(-1);
    }
	printf("用户名:%s\n\n",username);
    printf("<br>\n\n");
	// password gateway server_ip dns subnet_mask dhcp error
	if(cgiFormString("password", password, sizeof(password)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function password failed");
        //exit(-1);
    }
	printf("密码:%s\n\n",password);
    printf("<br>\n\n");
/*
	if(cgiFormString("email", email, sizeof(email)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function email failed");
        //exit(-1);
    }
	printf("电子邮箱:%s\n\n",phone);
    printf("<br>\n\n");
*/

	/***  将用户信息写入MySQL数据库中  ***/ 
	//数据存储到数据库
	MYSQL* conn;
	bool isAutoCommit;
	
	// 初始化 MySQL
	conn = mysql_init(NULL);
    if(NULL == conn)
    {
        printf("errno:%d error:%s\n",mysql_errno(conn),mysql_error(conn));
        exit(-1);
    }
    
	char ip[16] = "127.0.0.1";
	char user[20] = "test";
	char passwd[20] = "test";
	char database[20] = "register";
	int port = 3306;

	// 尝试与运行在主机上的MySQL数据库引擎建立连接
	if(NULL == mysql_real_connect(conn,ip,user,passwd,database,port,NULL,0))
    {
        printf("---errno:%d error:%s\n\n",mysql_errno(conn),mysql_error(conn));
        exit(-1);
    }
	
	isAutoCommit = true;
	// 根据mysql的autocommit参数设置来决定是否自动提交
	mysql_autocommit(conn,isAutoCommit);

	// 设定数据库编码
	mysql_query(conn,"SET NAMES 'utf8'");
	mysql_query(conn,"SET CHARACTER SET utf8");
	mysql_query(conn,"SET CHARACTER_SET_RESULT = utf8");

    char cmd[SQL_SIZE];
	// 置字节字符串cmd的前SQL_SIZE个字节为零且包括‘\0’
    bzero(cmd, SQL_SIZE);
	// 创建user表
    // strcpy(cmd, "CREATE TABLE user(username varchar(20) PRIMARY KEY,password varchar(20));");

	// 将sql语句写入cmd变量
	sprintf(cmd, "INSERT INTO user values('%s', '%s');",username,password);

	printf("%s\n\n",cmd);

	// 向与指定的连接标识符关联的服务器中的当前活动数据库发送一条查询
	if(mysql_query(conn,cmd) != 0)
	{
		printf("errno:%d error:%s\n\n",mysql_errno(conn),mysql_error(conn));
		printf("<p>注册失败，请重新注册</p>\n\n");	
		sleep(1);
		printf("<meta http-equiv=Refresh content=1;URL=../register.html>\n");   	
	}
	//mysql_affected_rows(conn);

	printf("<p>注册成功</p>\n\n");	
	printf("<br>\n\n");
	printf("<p>您的用户名和密码为：</p>\n\n");	
	
	sprintf(cmd,"select * from user;");

	MYSQL_RES *res;
	MYSQL_ROW row;
	
	if(mysql_query(conn,cmd) != 0)
	{
		printf("errno:%d error:%s\n",mysql_errno(conn),mysql_error(conn));
		return -1;
	}
	
	int num_fields = mysql_field_count(conn);
	if(num_fields == 0)
	{
		printf("errno:%d error:%s\n",mysql_errno(conn),mysql_error(conn));
		return -1;	
	}
	
	res = mysql_store_result(conn);
	if(NULL == res)
	{
		printf("errno:%d error:%s\n",mysql_errno(conn),mysql_error(conn));
		return -1;
	}
	
	printf("<br>\n\n");
	printf("<br>\n\n");
	while((row = mysql_fetch_row(res)))
	{
		char arr[1000];
		int i = 0;
		for( ; i<num_fields; i++)
		{
			printf("%s ",row[i]);
		}
		printf("\n\n");
		printf("<br>\n\n");
	}
	
	mysql_free_result(res);

	sleep(1);

	printf("<meta http-equiv=Refresh content=1;URL=../login.html>\n");   

	return 0;
}
