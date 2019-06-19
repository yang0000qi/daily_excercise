/*************************************************************************
	> File Name: control_prntf_line.c
	> Author: 
	> Mail: 
	> Created Time: 2019年06月17日 星期一 10时25分16秒
 ************************************************************************/

#include<stdio.h>

#define CURSOR_UP_LINES(n) printf("\e[%dA", n)

int lineno;
int cnt;
int main()
{

    int j=0,i=0;
    printf("*************\n");
    printf("\n");
    while(j++<100000) 
    {
        CURSOR_UP_LINES(lineno);
        lineno = 0;
        printf("this the %d st printf------\n",j);
        lineno++;
        printf("j = %d------\n",j);
        lineno++;
        int i=0;
        for(;i<10;i++)
        {
            printf("i=%d\n", i+j);
            lineno++;
        }
    }

    return 0;
}

