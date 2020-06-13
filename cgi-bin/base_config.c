#include <stdio.h>
#include "cgic.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
    // 获取表单中的name的值，存入name缓冲区
	// cgiFormString试图检索发送给指定字段的字符串。文本会被拷贝到指定的result buffer中，最多但不超过max-1个字节。null字符标记字符串的结束。
	if(cgiFormString("gateway", gateway, sizeof(gateway)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function gateway failed");
        //exit(-1);
    }
	printf("网关:%s\n\n",gateway);
    printf("<br>\n\n");
	if(cgiFormString("server_ip", server_ip, sizeof(server_ip)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function server_ip failed");
        exit(-1);
    }
	printf("服务器IP:%s\n\n",server_ip);
    printf("<br>\n\n");
	if(cgiFormString("dns", dns, sizeof(dns)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function dns failed");
        //exit(-1);
    }
	printf("DNS:%s\n\n",dns);
    printf("<br>\n\n");
	if(cgiFormString("subnet_mask", subnet_mask, sizeof(subnet_mask)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function subnet_mask failed");
        exit(-1);
    }
	printf("子网掩码:%s\n\n",subnet_mask);
    printf("<br>\n\n");
	if(cgiFormString("dhcp", dhcp, sizeof(dhcp)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function dhcp failed");
        exit(-1);
    }
	printf("是否开启DHCP:%s\n\n",dhcp);
    printf("<br>\n\n");
	if(cgiFormString("error", error, sizeof(error)) != cgiFormSuccess)
    {
        fprintf(stderr, "cgiFormString function error failed");
        //exit(-1);
    }
	printf("是否自动上报异常:%s\n\n",error);
    printf("<br>\n\n");

	// 写入base_info.json文件中
	//将umask值设置为0000，实际创建的文件权限即为下面的mode值

	/*	
	umask(0000);
	int fd = open("base_info.json",O_CREAT|O_TRUNC|O_RDWR,0777);

	char buf[4096] = {};
	sprintf(buf,"{\"info\":[{\"device_name\":\"%s\",\"LaL\":\"%s\",\"lamp_id\":\"%s\",\"maintainer_info\":\"%s\",\"device_ip\":\"%s\", \"phone\":\"%s\",\"username\":\"%s\",\"password\":\"%s\",\"gateway\":\"%s\",\"server_ip\":\"%s\",\"dns\":\"%s\",\"subnet_mask\":\"%s\", \"dhcp\":\"%s\",\"error\":\"%s\"}]}",device_name,LaL,lamp_id,maintainer_info,device_ip,phone,username,password,gateway,server_ip,dns,subnet_mask,dhcp,error);
	
	write(fd,buf,strlen(buf));	

	close(fd);
	*/

/***************************

	char buf[1024] = {};	// 将配置信息写入字符串，再写入文件
	// 修改IP地址(eth0为网卡名称)
	sprintf(buf,"sudo ifconfig eth0 %s netmask %s",device_ip,subnet_mask);
	system(buf);
	// 修改默认网关(eth0为网卡名称)
	sprintf(buf,"route add default gw %s dev eth0",gateway);
	system(buf);

	// 对系统文件进行操作
	system("sudo chmod 777 /etc/network/interfaces"); // 修改文件权限
	system("sudo chmod 777 /etc/resolvconf/resolv.conf.d/base");
	int fd_interfaces = open("/etc/network/interfaces",O_RDWR|O_TRUNC);	// 打开文件
	if(-1 == fd_interfaces)
	{
		printf("/etc/network/interfaces open failed\n");
	}

	int size = 0;
	int fd_base = open("/etc/resolvconf/resolv.conf.d/base",O_RDWR|O_TRUNC);
	sprintf(buf,"search localdomain\nnameserver %s\nnameserver %s",dns,dns);
	size = write(fd_base,buf, strlen(buf));
	close(fd_base);

	sprintf(buf,"auto lo\niface lo inet loopback\nauto eth0\niface eth0 inet static\naddress%s\nnetmask%s\ngateway%s\n",device_ip,subnet_mask,gateway);
	size = write(fd_interfaces,buf, strlen(buf));
	close(fd_interfaces);

******************************/

	printf("<p>相应参数配置完成</p>\n\n");

	//printf("<meta http-equiv=Refresh content=1;URL=../base_config.html>\n");   

	return 0;
}
