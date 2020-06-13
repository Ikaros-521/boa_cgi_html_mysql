/*
sudo vim /etc/network/interfaces
auto eth0 #要设置的网卡
iface eth0 inet static #设置静态IP；如果是使用自动IP用dhcp，后面的不用设置，一般少用
addressxxx.xxx.xxx.xxx #IP地址
netmaskxxx.xxx.xxx.xxx #子网掩码
gatewayxxx.xxx.xxx.xxx #网关
sudo vim /etc/resolvconf/resolv.conf.d/base
search localdomain #如果本Server为DNS服务器，可以加上这一句，如果不是，可以不加
nameserver 172.16.3.4 #希望修改成的DNS
nameserver 172.16.3.3 #希望修改成的DNS

sudo /etc/init.d/networking restart #使网卡配置生效
sudo /etc/init.d/resolvconf restart #使DNS生效
*/
#include <stdio.h>
#include "cgic.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	system("sudo chmod 777 /etc/network/interfaces"); // 修改文件权限
	system("sudo chmod 777 /etc/resolvconf/resolv.conf.d/base");
	int fd_interfaces = open("/etc/network/interfaces",O_RDWR|O_TRUNC);	// 打开文件
	if(-1 == fd_interfaces)
	{
		printf("/etc/network/interfaces open failed\n");
	}
	
	char buf[1024] = {};	// 将配置信息写入字符串，再写入文件
	strcpy(buf,"auto lo\niface lo inet loopback\n");
	int size = write(fd_interfaces,buf, strlen(buf));
	strcpy(buf,"auto eth0\niface eth0 inet static\naddress192.168.1.100\nnetmask255.255.255.0\ngateway192.168.1.1\n");
	size = write(fd_interfaces,buf, strlen(buf));

	int fd_base = open("/etc/resolvconf/resolv.conf.d/base",O_RDWR|O_TRUNC);
	strcpy(buf,"search localdomain\nnameserver 172.16.3.4\nnameserver 172.16.3.3");
	size = write(fd_base,buf, strlen(buf));

	return 0;

	
}
