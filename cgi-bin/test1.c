#include<stdio.h>
#include<stdlib.h>

int main(void)
{
        char *data;
        long m,n;
        printf("Content-type:text/html\n\n");
        data=getenv("QUERY_STRING");
        if (!data)
            printf("<P>get no datas and it's wrong.");
        else if(sscanf(data,"m=%ld&n=%ld",&m,&n)!=2)
            printf("<P>the input must be numbers");
        else
            printf("<P>%ld and %ld multi= %ld",m,n,m*n);
    return 0;
}

