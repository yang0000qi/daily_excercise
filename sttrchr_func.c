/*************************************************************************
	> File Name: sttrchr_func.c
	> Author: 
	> Mail: 
	> Created Time: 2016年11月02日 星期三 14时29分45秒
    >sttrchr
    >找一个字符c在另一个字符串str中末次出现的位置,
    也就是从str的右侧开始查找字符c首次出现的位置，
    并返回从字符串中的这个位置起， 一直到字符串结束的所有字符。
    如果未能找到指定字符，那么函数将返回NULL
 ************************************************************************/

#include<stdio.h>
#include <string.h>  
#pragma warning (disable:4996)  
int main(void)  
{  
    char string[20];  
    char *ptr;  
    char c='r';  
    strcpy(string,"There are two rings");  
    ptr=strrchr(string,c);  
    //ptr=strchr(string,c);  
    if (ptr!=NULL)  
    {  
        printf("The character %c is at position:%s\n",c,ptr);  
    }  
    else  
    {  
        printf("The character was not found\n");  
    }  
//    getch();  
    return 0;  
}  
