#include <stdio.h>   
#include <string.h>   
#include <unistd.h>   
#include <fcntl.h>   
#include <sys/stat.h>   
#include <stdlib.h>
#include <mysql/mysql.h>
#include <stdbool.h>
#include "cgic.h" 
//#include "sql.h" 
#define SQL_SIZE 256 

int cgiMain(int argc, char **argv)
{
	// 存储数据的变量
    char name[64];
    char age[4];
    char sex[8];	
    char company[64];
    char profession[64];
    char idnumber[24];
    char qq[24];
    char email[64];
    char telephone[16];
    //回显信息到HTML网页cgiHeaderContentType("text/html");
    printf("<html>\n\n");
	printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n\n");
	printf("<p>\n\n");
    
	// 获取表单中的name的值，存入name缓冲区
	// cgiFormResultType cgiFormString( char *name, char *result, int max) 
	// cgiFormString试图检索发送给指定字段的字符串。文本会被拷贝到指定的result buffer中，最多但不超过max-1个字节。null字符标记字符串的结束。
    if(cgiFormString("name", name, sizeof(name)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function name failed");
        exit(-1);
    }
    printf("姓名:%s\n\n",name);
    printf("<br>\n\n");
    if(cgiFormString("age", age, sizeof(age)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function age failed");
        exit(-1);
    }
    printf("年龄:%s\n\n",age);
    printf("<br>\n\n");
    if(cgiFormString("sex", sex, sizeof(sex)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function sex failed");
        exit(-1);
    }
    printf("性别:%s\n\n",sex);
    printf("<br>\n\n");
    if(cgiFormString("company", company, sizeof(company)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function company failed");
        exit(-1);
    }
    printf("单位:%s\n\n",company);
    printf("<br>\n\n");
    if(cgiFormString("profession", profession, sizeof(profession)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function profession failed");
        exit(-1);
    }
    printf("职业:%s\n\n",profession);
    printf("<br>\n\n");
    if(cgiFormString("idnumber", idnumber, sizeof(idnumber)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function idnumber failed");
        exit(-1);
    }
    printf("身份证号码:%s\n\n",idnumber);
    printf("<br>\n\n");
	if(cgiFormString("qq", qq, sizeof(qq)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function qq failed");
        printf("cgiFormString function qq failed");
        exit(-1);
    }
    printf("QQ号码:%s\n\n",qq);
    printf("<br>\n\n");
    if(cgiFormString("email", email, sizeof(email)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function email failed");
        exit(-1);
    }
    printf("Email:%s\n\n",email);
    printf("<br>\n\n");
    if(cgiFormString("telephone", telephone, sizeof(telephone)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function telephone failed");
        exit(-1);
    }
    printf("Telepone:%s\n\n",telephone);
    printf("<br>\n\n");
    printf("</p>\n\n");
    printf("</html>\n\n");

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
	char database[20] = "person";
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
	// 创建person表
    // strcpy(cmd, "CREATE TABLE person(ID varchar(24) PRIMARY KEY,name varchar(64),age varchar(4), sex varchar(8), company varchar(64), profession varchar(64), qq varchar(24), email varchar(64), telephone varchar(16));");

	// 将sql语句写入cmd变量
	sprintf(cmd, "INSERT INTO person values('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s');",idnumber,name,age,sex,company,profession,qq,email,telephone);

	printf("%s\n\n",cmd);

	// 向与指定的连接标识符关联的服务器中的当前活动数据库发送一条查询
	if(mysql_query(conn,cmd) != 0)
	{
		printf("errno:%d error:%s\n\n",mysql_errno(conn),mysql_error(conn));
		exit(-1);
	}
	//mysql_affected_rows(conn);

	printf("增加成功\n\n");	


	sprintf(cmd,"select * from person;");

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


    return 0;
}

