#include <stdio.h>   
#include <string.h>   
#include <unistd.h>   
#include <fcntl.h>   
#include <sys/stat.h>   
#include <stdlib.h>
#include "cgic.h" 
#include "sqlite3.h" 
#define SQL_SIZE 256 
int cgiMain(int argc, char **argv)
{
    char name[64];
    char age[4];
    char sex[8];
    char company[64];
    char profession[16];
    char idnumber[24];
    char qq[24];
    char email[64];
    char telephone[16];//回显信息到HTML网页cgiHeaderContentType("text/html");
    printf("<html>\n\n");
    printf("<p>\n\n");//获取表单中的name的值，存入name缓冲区
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
    if(cgiFormString("qq", qq, sizeof(qq)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function qq failed");
        printf("cgiFormString function qq failed");
        exit(-1);
    }
    printf("QQ号码:%s\n\n",qq);
    printf("<br>\n\n");
    printf("</p>\n\n");
    printf("</html>\n\n");//数据存储到数据库
    sqlite3 *db;
    int result;
    result = sqlite3_open("person.db", &db);
    if(result != SQLITE_OK)
    {
        printf("Fail to sqlite3_open person.db: %s.\n", sqlite3_errmsg(db));
        exit(-1);
    }
    char *errmsg;
    char sql[SQL_SIZE];
    bzero(sql, SQL_SIZE);
    strcpy(sql, "CREATE TABLE person(ID varchar(24) PRIMARY KEY,name text,age text, sex text, company text, profession text, qq text, email text, telephone text);");
    if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != 0)
    {
        printf("Fail to exec sql: %s.\n", errmsg);
        printf("\n%s\n",sql);
        exit(-1);
    }
    bzero(sql, SQL_SIZE);
    strcpy(sql, "INSERT INTO person values('1234567899876543', '天山老妖', '30', 'boy', '天山', '嵌入式工程师', '123455678', 'hello@qq.com', '123344');");
    if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != 0)
    {
        printf("Fail to exec sql: %s.\n\n", errmsg);
        printf("\n%s\n",sql);
        exit(-1);
    }
    result = sqlite3_close(db);
    if(result != 0)
    {
        fprintf(stderr, "Fail to sqlite3_open person.db : %s.\n", sqlite3_errmsg(db));
        exit(-1);
    }
    return 0;
}
