#include <stdio.h>   
#include <string.h>   
#include <unistd.h>   
#include <fcntl.h>   
#include <sys/stat.h> 
#include <time.h>  
#include "cgic.h" 

#define BufferLen 1024 
  
int cgiMain(void)
{       
	cgiFilePtr file;
	int targetFile;
	mode_t mode;
	char name[128] = {};
	char fileNameOnServer[64] = {};
	char buf[1024] = {};
	char contentType[1024] = {};
	char buffer[BufferLen];
	char *tmpStr = NULL;
	int size;
	int got,t;
	cgiHeaderContentType("text/html");       //取得html页面中file元素的值，应该是文件在客户机上的路径名

	if (cgiFormFileName("file", name, sizeof(name)) !=cgiFormSuccess)    
	{
		//fprintf(stderr,"could not retrieve filename\n");
		printf("could not retrieve filename\n");
		goto FAIL;
	}
	cgiFormFileSize("file", &size);       //取得文件类型，不过本例中并未使用

	cgiFormFileContentType("file", contentType,sizeof(contentType));       
	//目前文件存在于系统临时文件夹中，通常为/tmp，通过该命令打开临时文件。临时文件的名字与用户文件的名字不同，所以不能通过路径/tmp/userfilename的方式获得文件
	if(cgiFormFileOpen("file", &file) != cgiFormSuccess)
	{
		//fprintf(stderr,"could not open the file\n");
		printf("could not open the file\n");
		goto FAIL;       
	}
	t=-1;       //从路径名解析出用户文件名
	while(1)        
	{
		tmpStr = strstr(name+t+1,"//");
		if(NULL == tmpStr)
			tmpStr = strstr(name+t+1,"/");//if "//" is not path separator, try "/"
		if(NULL != tmpStr)
			t = (int)(tmpStr-name);
		else
			break;
	}
	strcpy(fileNameOnServer,name+t+1);
	mode = S_IRWXU|S_IRGRP|S_IROTH;       //在当前目录下建立新的文件，第一个参数实际上是路径名，此处的含义是在cgi程序所在的目录（当前目录））建立新文件
	sprintf(buf, "/root/%s", fileNameOnServer);
	targetFile = open(buf, O_RDWR|O_CREAT|O_TRUNC|O_APPEND, mode);
	if(targetFile<0)
	{
		//fprintf(stderr,"could not create the new file,%s\n",fileNameOnServer);
		printf("could not create the new file,%s\n",fileNameOnServer);
		goto FAIL;
	}       //从系统临时文件中读出文件内容，并放到刚创建的目标文件中
	while(cgiFormFileRead(file, buffer, BufferLen, &got)==cgiFormSuccess)
	{
		if(got>0)
			write(targetFile,buffer,got);
	}
	cgiFormFileClose(file);
	close(targetFile);
	goto END;
FAIL:       
	//fprintf(stderr,"Failed to upload");   
	printf("Failed to upload\n");       
	return 1;
END:       
	printf("File %s has been uploaded\n",fileNameOnServer);
	// sudo dos2unix filename (windows上传上来的文件换行不一样） 
	
	return 0;
}
