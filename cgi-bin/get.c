#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>
#include "cgic.h"

int cgiMain(void)
{
	char *lenstr;
	int fd_webdata=-1;

	if(lenstr=getenv("QUERY_STRING"))
	{
	}
	else
	{
	}
	
	printf("Content type: text/html\n\n");

	if(strstr(lenstr,"get") != NULL)
	{
		printf("<p>用p标签是解决有个报错问题， 标签中就是解析后的内容</p>");
	}
	//最后记得关闭文件
	close(fd_webdata); 

	return 0;
}

