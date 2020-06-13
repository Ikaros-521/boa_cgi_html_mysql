#include <stdio.h>
#include "cgic.h"
#include <string.h>
#include <stdlib.h>
int cgiMain() {
       fprintf(cgiOut,"Set-Cookie: %s=%s;  path=/\r\n","Data","abcd");
    //设置一个名为Data数据为"abcd"的Cookie
       cgiHeaderContentType("text/html");
       fprintf(cgiOut, "<HTML><HEAD>\n");
       fprintf(cgiOut, "<meta http-equiv=Refresh content=1;URL=../showCookie.html\n");   
//设置跳转到当前目录下的showCookie.html页面
       fprintf(cgiOut, "<TITLE>Cookie</TITLE></HEAD>\n");
       fprintf(cgiOut, "<BODY>");
       fprintf(cgiOut, "</BODY>\n");
       fprintf(cgiOut, "</HTML>\n");
       return 0;
}
