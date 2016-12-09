/*************************************************************************
	> File Name: printf_trace.c
	> Author: 
	> Mail: 
	> Created Time: Fri 09 Dec 2016 09:47:36 PM CST
 ************************************************************************/

#include<stdio.h>

int main()
{
     printf("%s(%d)-<%s>: ", __FILE__, __LINE__, __func__); 
    return 0;
}
