#include <stdio.h>
#include "cgic.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int cgiMain(void)
{
	char device_name[64];
    char LaL[64];
    char lamp_id[10];	
    char maintainer_info[64];
    char device_ip[20];
    char phone[20];
    char username[20];
    char password[20];
    char gateway[20];
    char server_ip[20];
    char dns[20];
    char subnet_mask[20];
    char dhcp[20];
    char error[20];
	//回显信息到HTML网页cgiHeaderContentType("text/html");
    printf("<html>\n\n");
	printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n\n");
	printf("<p>\n\n");
    //获取表单中的name的值，存入name缓冲区
	// cgiFormString试图检索发送给指定字段的字符串。文本会被拷贝到指定的result buffer中，最多但不超过max-1个字节。null字符标记字符串的结束。
    if(cgiFormString("device_name", device_name, sizeof(device_name)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function device_name failed");
        exit(-1);
    }
	printf("设备名称:%s\n\n",device_name);
    printf("<br>\n\n");
	if(cgiFormString("device_name", device_name, sizeof(device_name)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function device_name failed");
        exit(-1);
    }
	if(cgiFormString("device_name", device_name, sizeof(device_name)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function device_name failed");
        exit(-1);
    }
	if(cgiFormString("device_name", device_name, sizeof(device_name)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function device_name failed");
        exit(-1);
    }
	if(cgiFormString("device_name", device_name, sizeof(device_name)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function device_name failed");
        exit(-1);
    }
	if(cgiFormString("device_name", device_name, sizeof(device_name)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function device_name failed");
        exit(-1);
    }
	if(cgiFormString("device_name", device_name, sizeof(device_name)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function device_name failed");
        exit(-1);
    }
	if(cgiFormString("device_name", device_name, sizeof(device_name)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function device_name failed");
        exit(-1);
    }
	if(cgiFormString("device_name", device_name, sizeof(device_name)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function device_name failed");
        exit(-1);
    }
	if(cgiFormString("device_name", device_name, sizeof(device_name)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function device_name failed");
        exit(-1);
    }
	if(cgiFormString("device_name", device_name, sizeof(device_name)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function device_name failed");
        exit(-1);
    }
	if(cgiFormString("device_name", device_name, sizeof(device_name)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function device_name failed");
        exit(-1);
    }
	if(cgiFormString("device_name", device_name, sizeof(device_name)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function device_name failed");
        exit(-1);
    }
	if(cgiFormString("device_name", device_name, sizeof(device_name)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function device_name failed");
        exit(-1);
    }
	if(cgiFormString("device_name", device_name, sizeof(device_name)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function device_name failed");
        exit(-1);
    }
	if(cgiFormString("device_name", device_name, sizeof(device_name)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function device_name failed");
        exit(-1);
    }
	if(cgiFormString("device_name", device_name, sizeof(device_name)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function device_name failed");
        exit(-1);
    }

	return 0;
}
